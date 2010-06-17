/*
   xmlpp - an xml parser and validator written in C++
   copyright (c) 2000-2001 Michael Fink

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA  02111-1307  USA.

*/
/*! \file xmlpp.cpp

  contains the methods of the xmlpp classes

*/

// needed includes
#include "OSGXmlpp.h"
#include "OSGXmlparser.h"
//#include <cstdio>
//#include <cstdarg>

// namespace declaration
namespace xmlpp {


// macro for keeping the errorcode switch short and easy
#define XMLERRORCODE(x,y)  case x: err = y; break;

// xmlerror methods
//! \todo perhaps more language independency would be good :)
xmlstring xmlerror::get_strerror() const
{
   const char *err = 0;
   switch(errorcode)
   {
      XMLERRORCODE(xml_unknown,"unspecified or unknown error");
      XMLERRORCODE(xml_instream_error,"error in the infile stream");
      XMLERRORCODE(xml_opentag_expected,"expected an open tag literal '<'");
      XMLERRORCODE(xml_opentag_cdata_expected,"expected a '<' or cdata");
      XMLERRORCODE(xml_closetag_expected,"expected an '>' closing tag literal");
      XMLERRORCODE(xml_pi_doctype_expected,"expected a processing instruction or doctype tag");
      XMLERRORCODE(xml_tagname_expected,"expected a tag name after '<' or '</'");
      XMLERRORCODE(xml_closetag_slash_expected,"expected a '/' after closing tag literal '<'");
      XMLERRORCODE(xml_tagname_close_mismatch,"tag name from start and end tag mismatch");
      XMLERRORCODE(xml_attr_equal_expected,"expected '=' after attribute name");
      XMLERRORCODE(xml_attr_value_expected,"expected value after 'a' in attribute");
      XMLERRORCODE(xml_save_invalid_nodetype,"invalid nodetype encountered while saving");
      XMLERRORCODE(xml_dummy,"dummy error code (this error should never been seen)");
   }

   xmlstring errorstr(err);
//   errorstr.assign(err);
   return errorstr;
}


// xmlcontext methods

xmlcontext::xmlcontext()
:eventhandler(new xmleventhandler)
{
   init = false;
   nexthandle = 0;
   handleevents = false;
}

xmlcontext::~xmlcontext()
{
}

xmlstring xmlcontext::get_entity( xmlstring &entname )
{
   if (!init) init_context();

   xmlentitymap::const_iterator iter = entities.find( entname );
   return ( iter == entities.end() ? entname : iter->second );
}

xmlstring xmlcontext::get_tagname( xmltagnamehandle handle )
{
   if (!init) init_context();
   xmltagnamemap::const_iterator iter = tagnames.find( handle );

   xmlstring empty("");
   return ( iter == tagnames.end() ? empty : iter->second );
}

xmltagnamehandle xmlcontext::insert_tagname( xmlstring &tagname )
{
   if (!init) init_context();

   // bugfix: first search, if the tagname is already in the list
   // since usually there are not much different tagnames, the search
   // shouldn't slow down parsing too much
   xmltagnamemap::const_iterator iter,stop;
   iter = tagnames.begin();
   stop = tagnames.end();

   for(;iter!=stop;iter++)
   if ((*iter).second == tagname )
   {
      return (*iter).first;
   }   

   // insert new tagname
   xmltagnamemap::value_type keyvaluepair(nexthandle,tagname);
   tagnames.insert(keyvaluepair);

   return nexthandle++;
}


// xmlattributes methods

xmlstring xmlattributes::get(xmlstring &key)
{
   xmlattrmap::const_iterator iter;

   // try to find the key in the map
   iter = find( key );
   xmlstring empty("");
   return iter == end() ? empty : iter->first;
}

void xmlattributes::set(xmlstring &key, xmlstring &value)
{
   xmlattrmap::iterator iter;

   // try to find the key in the map
   iter = find( key );
   if (iter != end())
      (*iter).second = value;
   else
   {
      // insert, because the key-value pair was not found
      xmlattrmap::value_type pa(key,value);
      this->insert(pa);
   }
}


// xmlnode methods

xmlnode::xmlnode( const xmlnode &node )
{
   nodenamehandle = node.nodenamehandle;
   contextptr = node.contextptr;
   nodetype = node.nodetype;
   attributes = node.attributes;
   cdata = node.cdata;
   nodelist = node.nodelist;
}

xmlnode &xmlnode::operator =( const xmlnode &node )
{
   nodenamehandle = node.nodenamehandle;
   contextptr = node.contextptr;
   nodetype = node.nodetype;
   attributes = node.attributes;
   cdata = node.cdata;
   nodelist = node.nodelist;
   return *this;
}

xmlstring xmlnode::get_name()
{
   return contextptr->get_tagname( nodenamehandle );
}

void xmlnode::set_name( xmlstring &nname )
{
   nodenamehandle = contextptr->insert_tagname(nname);
}

/*! \note currently no path-like childname can be passed, like in e.g. msxml */
xmlnodeptr xmlnode::get_firstchild(xmlstring &childname)
{
   // possible speedup: first search if a handle to the childname is existing

   xmlnodelist::const_iterator iter,stop;
   iter = nodelist.begin();
   stop = nodelist.end();

   // search for first occurance of node
   while(iter!=stop)
   {
      xmlnodeptr np = *(iter++);
      if (np->get_name() == childname)
         return np;
   };

   // no valid child found
   return xmlnodeptr(NULL);
}

/*! \note currently no path-like childname can be passed, like in e.g. msxml */
xmlnodelist xmlnode::select_nodes(xmlstring &nodename)
{
   xmlnodelist nlist;

   xmlnodelist::const_iterator iter,stop;
   iter = nodelist.begin();
   stop = nodelist.end();

   // search for all occurances of nodename and insert them into the new list
   while(iter!=stop)
   {
      xmlnodeptr np = *(iter++);
      if (np->get_name() == nodename)
         nlist.push_back(np);
   };

   return nlist;
}

/*! \exception throws xmlpp::xmlerror when a streaming or parsing error occur */
void xmlnode::load( std::istream &instream, xmlcontextptr &ctxptr )
{
   xmlparser parser(instream,ctxptr->get_location());
   parser.parse_node( *this, ctxptr );
}

/*! \exception throws xmlpp::xmlerror when a streaming or parsing error occur */
void xmlnode::save( std::ostream &outstream, int indent )
{
   // output indendation spaces
   for(int i=0;i<indent;i++)
      outstream << ' ';

   // output cdata
   if (nodetype == xml_nt_cdata)
   {
      outstream << cdata.c_str() << std::endl;
      return;
   }

   // output tag name
   outstream << '<' << contextptr->get_tagname(nodenamehandle).c_str();

   // output all attributes
   xmlattrmap::const_iterator iter, stop;
   iter = attributes.begin();
   stop = attributes.end();

   for(;iter!=stop;iter++)
   {
      xmlattrmap::value_type attr = *iter;
      outstream << ' ' << attr.first.c_str() << '='
         << '\"' << attr.second.c_str() << '\"';
   }

   // depending on the nodetype, do output
   switch(nodetype)
   {
   case xml_nt_node:
      {
         outstream << '>' << std::endl;

         // output all subnodes
         xmlnodelist::const_iterator iter,stop;
         iter = nodelist.begin();
         stop = nodelist.end();
         
         for(;iter!=stop;iter++)
            (*iter)->save(outstream,indent+1);

         // output indendation spaces
         for(int i=0;i<indent;i++)
            outstream << ' ';

         // output closing tag
         outstream << '<' << '/'
            << contextptr->get_tagname(nodenamehandle).c_str() << '>' << std::endl;
      }
      break;
   case xml_nt_leaf:
      // a leaf has no subnodes
      outstream << '/' << '>' << std::endl;
      break;
   default:
      // unknown nodetype
      throw xmlerror( xml_save_invalid_nodetype );
   }
}


// xmldocument methods

/*! \exception throws xmlpp::xmlerror when a streaming or parsing error occur */
void xmldocument::load( std::istream &instream, xmlcontextptr &ctxptr )
{
   xmlparser parser(instream,ctxptr->get_location());
   parser.parse_document( *this, ctxptr );
}

//! \todo implement: print <!doctype> tag;
/*! \exception throws xmlpp::xmlerror when a streaming or parsing error occur */
void xmldocument::save( std::ostream &outstream )
{
   // output all processing instructions
   xmlnodelist::const_iterator iter,stop;
   iter = procinstructions.begin();
   stop = procinstructions.end();

   for(;iter!=stop;iter++)
   {
      xmlnodeptr np = *iter;
      
      // output pi tag
      outstream << "<?" << np->get_name().c_str();

      // output all attributes
      xmlattrmap::const_iterator aiter, astop;
      aiter = attributes.begin();
      astop = attributes.end();

      for(;aiter!=astop;aiter++)
      {
         xmlattrmap::value_type attr = *aiter;
         outstream << ' ' << attr.first.c_str() << '='
            << '\"' << attr.second.c_str() << '\"';
      }
      // output closing brace      
      outstream << "?>" << std::endl;
   }

   // output <!doctype> tag

   // left to do ...


   // call save() method of the first (and hopefully only) node in xmldocument
   (*nodelist.begin())->save(outstream,0);   
}

// namespace end
}
