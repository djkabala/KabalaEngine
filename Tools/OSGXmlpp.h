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
/*! \file xmlpp.h

  the main declaration header

*/

// prevent multiple includes
#ifndef __xmlpp_h_
#define __xmlpp_h_

// needed includes
#include "OSGXmlconfig.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
#include "OSGShared_ptr.h"   // the boost::shared_ptr class


//! namespace of the xmlpp project
namespace xmlpp {


//! basic char type
typedef char xml_char_type;
//! string class typedef
typedef std::basic_string<xml_char_type> xmlstring;
//! string smart pointer
typedef boost::shared_ptr<xmlstring> xmlstringptr;


//! xml parsing error codes enumeration
enum xmlerrorcode 
{
      //! unspecified or unknown error
   xml_unknown = 0,
      //! error in the infile stream
   xml_instream_error,

      //! expected an open tag literal '<'
   xml_opentag_expected,
      //! expected a '<' or cdata
   xml_opentag_cdata_expected,
      //! expected a '>' closing tag literal
   xml_closetag_expected,
      //! expected a processing instruction or doctype tag
   xml_pi_doctype_expected,
      //! expected a tag name after '<' or '</'
   xml_tagname_expected,
      //! expected a '/' after closing tag literal '<'
   xml_closetag_slash_expected,
      //! tag name from start and end tag mismatch
   xml_tagname_close_mismatch,

      //! expected '=' after attribute name
   xml_attr_equal_expected,
      //! expected value after an '=' in attribute
   xml_attr_value_expected,

      //! invalid nodetype encountered while saving
   xml_save_invalid_nodetype,

      //! dummy error code
   xml_dummy
};


// classes

//! xml error class
/*! contains an xmlerrorcode and is thrown while parsing xml input */
class XMLPP_API xmlerror
{
public:
   //! constructor
   xmlerror( xmlerrorcode code ){ errorcode = code; }
   //! returns the error code
   xmlerrorcode get_error() const { return errorcode; }
   //! returns the string representation of the error code
   xmlstring get_strerror() const;
protected:
   xmlerrorcode errorcode;
};


//! xml stream position
/*! represents the position in the xml input stream; usable if load()
    throws an error on parsing xml content */
class XMLPP_API xmllocation
{
public:
   //! ctor
   xmllocation(){ reset(); }

   //! returns current line
   int get_line() const { return line; }
   //! returns current position in a line
   int get_pos() const { return pos; }

   //! advances a char
   void step( int chars = 1 ){ pos+=chars; }
   //! indicates entering a new line
   void newline(){ line++; pos=1; }
   //! reset location
   void reset(){ line=pos=1; }

protected:
   int line,pos;
};


// typedefs

//! handle to a tagname string in a tagname map
typedef int xmltagnamehandle;
//! maps the tagname string to a handle
typedef std::map<xmltagnamehandle,xmlstring> xmltagnamemap;
//! maps an entity to a string representation
typedef std::map<xmlstring,xmlstring> xmlentitymap;
//! smart pointer for xmlcontext
typedef boost::shared_ptr<class xmlcontext> xmlcontextptr;
//! smart pointer to the event handler
typedef boost::shared_ptr<class xmleventhandler> xmleventhandlerptr;


//! xml parsing context class
/*! the class is the parsing context for the parsed xml document.
    the class has a tagname lookup table and an entity map */
class XMLPP_API xmlcontext
{
public:
   //! ctor
   xmlcontext();
   //! dtor
   virtual ~xmlcontext();

   //! returns the entity representation for the named entity
   xmlstring get_entity( xmlstring &entname );

   //! returns the tagname by the tagname handle
   xmlstring get_tagname( xmltagnamehandle handle );

   //! inserts a tag name and returns a tag name handle to the string
   xmltagnamehandle insert_tagname( xmlstring &tagname );

   //! returns the current location in the xml stream
   xmllocation &get_location(){ return location; }

   //! called once when the context instance starts up; overwrite to customize
   /*! note that the base member should always be called, to set init to true; */
   virtual void init_context(){ init = true; }

   // event handling methods

   //! sets the event handler; enables handling events
   void set_eventhandler(xmleventhandlerptr ehptr);
   //! returns the currently used eventhandler (per reference)
   xmleventhandler &get_eventhandler(){ return *eventhandler.get(); }
   //! returns if a valid event handler is set
   bool handle_events() const { return handleevents; }

protected:
   //! indicates if init_context() was already called
   bool init;
   //! next available tagname handle
   int nexthandle;
   //! the tagname map matches xmltagnamehandles to the real xmlstring's
   xmltagnamemap tagnames;
   //! the entity map contains entity codes and their string representations
   xmlentitymap entities;
   //! location of the xml input stream
   xmllocation location;
   //! indicates if the event handler is used
   bool handleevents;
   //! current parsing event handler
   xmleventhandlerptr eventhandler;
};


//! node type enumeration
enum xmlnodetype 
{
      //! normal node, can contain subnodes
   xml_nt_node,
      //! a leaf node, which contains no further nodes, eg. <img/>
   xml_nt_leaf,
      //! document root node
   xml_nt_document,
      //! cdata node, which only contains char data
   xml_nt_cdata
};


// typedefs
//! smart pointer to node
typedef boost::shared_ptr<class xmlnode> xmlnodeptr;
//! list of node smart pointer
typedef std::list<xmlnodeptr> xmlnodelist;
//! attribute map 
typedef std::map<xmlstring, xmlstring> xmlattrmap;


#ifdef __sgi
#pragma set woff 1375
#endif

//! xml tag attribute map
/*! contains all attributes and values a tag has, represented in a map */
class XMLPP_API xmlattributes: public std::map<xmlstring, xmlstring>
{
   friend class xmlparser;
public:
   //! ctor
   xmlattributes(){}

   //! returns attribute value by name
   xmlstring get(xmlstring &key);
   //! sets new attribute value
   void set(xmlstring &key, xmlstring &value);
};

#ifdef __sgi
#pragma reset woff 1375
#endif

//! xml node
class XMLPP_API xmlnode
{
   friend class xmlparser;
protected:
   //! ctor
   xmlnode(){ nodetype = xml_nt_node; }
public:
   //! ctor, takes xml context pointer
   explicit xmlnode( xmlcontextptr pctx ){ nodetype=xml_nt_node; contextptr=pctx; }
   //! dtor
   ~xmlnode(){}
   //! copy constructor
   xmlnode( const xmlnode &node );
   //! assign operator
   xmlnode &operator =( const xmlnode &node );

   // access to node info

   //! returns type of node
   xmlnodetype get_type() const { return nodetype; }
   //! returns the node name
   xmlstring get_name();

   //! returns attribute map of the node
   xmlattributes &get_attrmap(){ return attributes; }
   //! returns attribute value for given attribute
   xmlstring get_attribute( xmlstring &attr ){ return attributes.get(attr); }

   //! returns cdata string
   const xmlstring &get_cdata(){ return cdata; }

   // node data manipulation

   //! sets new nodetype
   void set_type( xmlnodetype ntype ){ nodetype=ntype; }
   //! returns the node name
   void set_name( xmlstring &nname );
   //! sets new cdata
   void set_cdata( xmlstring &ncdata ){ cdata=ncdata; }
   //! sets new attribute value
   void set_attribute( xmlstring &attr, xmlstring &value ){ attributes.set(attr,value); }
   //! inserts a node into the subnodelist
   void insert( xmlnode &node){ xmlnodeptr nodeptr(new xmlnode(node)); nodelist.push_back(nodeptr); }

   // navigation through the nodes

   //! returns subnode list
   xmlnodelist &get_nodelist(){ return nodelist; }
   //! returns the first child with the given name
   xmlnodeptr get_firstchild(xmlstring &childname);
   //! select some nodes and put it into a separate nodelist
   xmlnodelist select_nodes(xmlstring &nodename);

   // load/save functions

   //! loads xml node from input stream
   void load( std::istream &instream, xmlcontextptr &ctxptr );
   //! saves node to xml output stream
   void save( std::ostream &outstream, int indent=0 );

protected:
   //! handle to the real tag name
   xmltagnamehandle nodenamehandle;

   //! smart pointer to the context class
   xmlcontextptr contextptr;

   //! nodetype
   xmlnodetype nodetype;

   //! attributes of the tag
   xmlattributes attributes;

   //! char data
   xmlstring cdata;

   //! stl list with subnodes
   xmlnodelist nodelist;
};


#ifdef __sgi
#pragma set woff 1375
#endif

//! xml document
class XMLPP_API xmldocument: public xmlnode
{
   friend class xmlparser;
public:
   //! ctor
   xmldocument(){ nodetype = xml_nt_document; }
   //! ctor, takes xml context pointer
   explicit xmldocument( xmlcontextptr pctx ){ nodetype = xml_nt_document; contextptr=pctx; }

   //! returns a list of processing instruction nodes
   xmlnodelist &get_pi_list(){ return procinstructions; }
   //! returns a list of document type definition rules to check the xml file
   xmlnodelist &get_dtd_list(){ return dtdrules; }

   //! loads xml node from input stream
   void load( std::istream &instream, xmlcontextptr &ctxptr );
   //! saves node to xml output stream
   void save( std::ostream &outstream );

protected:
   //! node list of parsed processing instructions
   xmlnodelist procinstructions;
   //! node list of document type definition rules
   xmlnodelist dtdrules;
};

#ifdef __sgi
#pragma reset woff 1375
#endif

//! xml parsing event handler
class XMLPP_API xmleventhandler
{
public:
   //! ctor
   xmleventhandler(){}
   //! virtual dtor
   virtual ~xmleventhandler(){}

   //! called when parsing of an xml document starts
   virtual void start_document(){}
   //! called when ended parsing a document
   virtual void end_document(){}

   //! called when parsing a processing instruction
   virtual void processing_instruction( xmlnode &/*pinode*/ ){}

   //! called when start parsing a node
   virtual void start_node( xmlstring &/*nodename*/ ){}
   //! called when an attribute list was parsed
   virtual void parsed_attributes( xmlattributes &/*attr*/){}
   //! called when parsing of a node was finished
   virtual void end_node( xmlnode &/*node*/ ){}

   //! called when a cdata section ended
   virtual void got_cdata( xmlstring &/*cdata*/ ){}
};


//! sets the eventhandler class
inline void xmlcontext::set_eventhandler(xmleventhandlerptr ehptr)
{
   eventhandler=ehptr; handleevents=true;
}


// namespace end
}

#endif
