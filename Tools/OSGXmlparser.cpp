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
/*! \file xmlparser.cpp

  member functions for the tokenizer and parser classes

*/

// needed includes
#include <stdio.h>
#include "OSGXmlparser.h"

// namespace declaration
namespace xmlpp {


// xmlparser methods

xmlparser::xmlparser( std::istream &inputstream, xmllocation &loc )
:instream(inputstream), tokenizer(inputstream,loc)
{
}

//! \todo: check if istream::fail() returns false when closed file
void xmlparser::parse_document( xmldocument &doc, xmlcontextptr &ctxptr )
{
   // set root nodename
   doc.contextptr = ctxptr;
   xmlstring rootstr("root");
   doc.nodenamehandle = ctxptr->insert_tagname( rootstr );

   if (instream.fail())
      throw xmlerror(xml_instream_error);

   bool handle = ctxptr->handle_events();

   // start parsing
   if (handle) ctxptr->get_eventhandler().start_document();
   parse_header( doc, ctxptr );
   parse_node( doc, ctxptr );
   if (handle) ctxptr->get_eventhandler().end_document();
}

// parses the header, ie processing instructions and doctype tag
//! \todo parse <!doctype> tag
//! \todo convert to uppercase!
void xmlparser::parse_header( xmldocument &doc, xmlcontextptr &ctxptr )
{
   while(1==1)
   {
      tokenizer++;
      xmltoken token1 = *tokenizer;
      if (token1 != '<')
         throw xmlerror( xml_opentag_expected );

      // token after opening < is a literal?
      tokenizer++;
      xmltoken token2 = *tokenizer;
      if (!token2.is_literal())
      {
         // generic string encountered: assume no pi and doctype tags
         tokenizer.put_back();
         tokenizer.put_back(token1);
         return;
      }

      // now check for the literal
      switch(token2.get_literal())
      {
         // comment or doctype tag
      case '!':
         {
            tokenizer++;
            xmltoken token3 = *tokenizer;

            if (!token3.is_literal())
            {
               // now a doctype tag or a comment may follow
               if (token3.get_generic().at(0) == '-' &&
                   token3.get_generic().at(1) == '-')
                   parse_comment(ctxptr);
               else
               {
                  xmlstring doctypestr(token3.get_generic());
                  //! todo convert to uppercase!
                  if (doctypestr == "DOCTYPE")
                  {
                     // TODO: parse doctype tag
                     // read the complete tag till the closing >

                     while (*(tokenizer++) != '>');
                  }
                  else
                     throw xmlerror( xml_unknown );
               }
            }
            else
               throw xmlerror( xml_pi_doctype_expected );

            break;
         }
      case '?':
         {
            tokenizer++;
            xmltoken token3 = *tokenizer;

            if (token3.is_literal())
               throw xmlerror( xml_pi_doctype_expected );

            // parse processing instruction
            xmlnode pinode( ctxptr );

            xmlstring tagname( token3.get_generic() );
            pinode.nodenamehandle = ctxptr->insert_tagname( tagname );

            parse_attributes( pinode.attributes );

            xmlnodeptr nodeptr( new xmlnode(pinode) );
            doc.procinstructions.push_back( nodeptr );

            if (ctxptr->handle_events()) ctxptr->get_eventhandler().processing_instruction(pinode);

            tokenizer++;
            if (*tokenizer != '?')
               throw xmlerror( xml_pi_doctype_expected );

            tokenizer++;
            if (*tokenizer != '>')
               throw xmlerror( xml_closetag_expected );
            break;
         }
      default:
         // unknown literal encountered
         throw xmlerror( xml_pi_doctype_expected );

      } // end switch

   } // end while
}

// parses the contents of the current node
//! \todo replace the EOF with an tokenizer.end() iterator
void xmlparser::parse_node( xmlnode &node, xmlcontextptr &ctxptr )
{
   node.contextptr = ctxptr;
   bool handle = ctxptr->handle_events();

   tokenizer++;
   xmltoken token1 = *tokenizer;

   // TODO: replace the EOF with an tokenizer.end() iterator
   if (token1 == xml_char_type(EOF))
      return;

   xmltoken token2;

   // loop when we encounter a comment
   bool again;
   do
   {
      again = false;

      // check if we have cdata
      if (!token1.is_literal())
      {
         xmlnode cdatanode( ctxptr );
         xmlstring cdataname("cdata");
         cdatanode.nodenamehandle = ctxptr->insert_tagname( cdataname );

         // parse cdata section(s) and return
         cdatanode.nodetype = xml_nt_cdata;
         cdatanode.cdata.empty();

         while(!token1.is_literal())
         {
            cdatanode.cdata += token1.get_generic();
            tokenizer++;
            token1 = *tokenizer;
         }
         tokenizer.put_back();

         // put node into nodelist
         xmlnodeptr nodeptr( new xmlnode(cdatanode) );
         node.nodelist.push_back( nodeptr );

         if (handle) ctxptr->get_eventhandler().got_cdata(cdatanode.cdata);

         return;
      }

      // no cdata, try to continue parsing node content

      if (token1 != '<')
         throw xmlerror(xml_opentag_cdata_expected);

      // get node name
      tokenizer++;
      token2 = *tokenizer;
      if (token2.is_literal())
      {
         // check the following literal
         switch(token2.get_literal())
         {
            // closing '</...>' follows
         case '/':
            // return, we have a closing node with no more content
            tokenizer.put_back();
            tokenizer.put_back( token1 );
            return;

            // comment follows
         case '!':
            parse_comment(ctxptr);

            // get next token
            tokenizer++;
            token1 = *tokenizer;

            // parse again, until we encounter some useful data
            again = true;
            break;

         default:
            throw xmlerror(xml_tagname_expected);
         }
      }
   } while (again);

   // insert tag name and set handle for it
   xmlstring tagname( token2.get_generic() );
   node.nodenamehandle = ctxptr->insert_tagname( tagname );

   // notify event handler
   if (handle) ctxptr->get_eventhandler().start_node(tagname);

   // parse attributes
   parse_attributes(node.attributes);

   if (handle) ctxptr->get_eventhandler().parsed_attributes(node.attributes);

   // check for single tag
   tokenizer++;
   xmltoken token3 = *tokenizer;
   if (token3 == '/' )
   {
      // node has finished
      tokenizer++;
      xmltoken token4 = *tokenizer;
      if (token4 != '>' )
         throw xmlerror(xml_closetag_expected);
      
      node.nodetype = xml_nt_leaf;

      if (handle) ctxptr->get_eventhandler().end_node(node); // akira said so
      
      // return, let the caller continue to parse
      return;
   }

   // now must follow a closing bracket
   if (token3 != '>')
      throw xmlerror(xml_closetag_expected);

   // loop to parse all subnodes
   while (1==1)
   {
      // try to parse end tag
      xmltoken token5 = *tokenizer++;
      if (token5.is_literal() && token5 == '<')
      {
         tokenizer++;
         if (*tokenizer != '/' )
         {
            // no end tag yet? put back token and continue parsing
            tokenizer.put_back();
            tokenizer.put_back(token5);
         }
         else
         {
            // end parsing subnodes
            break;
         }
      }
      else
         tokenizer.put_back();

      // create subnode
      xmlnode subnode( ctxptr );

      // parse possible sub nodes
      parse_node( subnode, ctxptr );

      // put node into nodelist
      xmlnodeptr nodeptr( new xmlnode(subnode) );
      node.nodelist.push_back( nodeptr );
   }

   tokenizer++;
   token1 = *tokenizer;
   if (token1.is_literal())
      throw xmlerror(xml_tagname_expected);

   // check if open and close tag names are identical
   if (token1.get_generic() != token2.get_generic() )
      throw xmlerror(xml_tagname_close_mismatch);

   tokenizer++;
   if (*tokenizer != '>')
      throw xmlerror(xml_opentag_expected);

   if (handle) ctxptr->get_eventhandler().end_node(node);
}

// parses tag attributes
void xmlparser::parse_attributes( xmlattributes &attr )
{
   while(1==1)
   {
      tokenizer++;
      xmltoken token1 = *tokenizer;

      if (token1.is_literal())
      {
         tokenizer.put_back();
         break;
      }

      // guru: get value name here
      xmlstring name = token1.get_generic();

      tokenizer++;
      if (*tokenizer != '=')
         throw xmlerror(xml_attr_equal_expected);

      tokenizer++;
      xmltoken token2 = *tokenizer;

      if (token2.is_literal())
         throw xmlerror(xml_attr_value_expected);

      // remove "" from attribute value
      xmlstring value( token2.get_generic() );
      value.erase(0,1);
      value.erase(value.length()-1,1);

      // insert attribute into the map
      // guru: we got the name already
      xmlattrmap::value_type attrpair(name, value);
      attr.insert(attrpair);
   }
}

void xmlparser::parse_comment( xmlcontextptr &/*ctxptr*/ )
{
   // get tokens until comment is over
   while (1==1)
   {
      tokenizer++;
      if (*tokenizer == "--")
      {
         tokenizer++;
         if (*tokenizer == '>')
            break;
      }
   }
}

// namespace end
};
