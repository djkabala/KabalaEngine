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
/*! \file xmlparser.h

  definitions for the parsing classes

*/

// prevent multiple includes
#ifndef __xmlparser_h_
#define __xmlparser_h_

// needed includes
#include "OSGXmlpp.h"
#include "OSGXmltokenizer.h"

// namespace declaration
namespace xmlpp {


//! xml parser implementation class
class xmlparser
{
public:
   //! ctor
   xmlparser( std::istream &inputstream, xmllocation &loc );

   //! parses the node as the document root
   void parse_document( xmldocument &doc, xmlcontextptr &ctxptr );
   
   //! parses a node, without processing instructions
   void parse_node( xmlnode &node, xmlcontextptr &ctxptr );

protected:
   //! parses xml header, such as processing instructions, doctype etc.
   void parse_header( xmldocument &doc, xmlcontextptr &ctxptr );

   //! parses an xml tag attribute list
   void parse_attributes( xmlattributes &attr );

   //! parses a <!-- --> comment 
   void parse_comment( xmlcontextptr &ctxptr );

protected:
   //! input stream
   std::istream &instream;
   //! stream iterator
   xmlstream_iterator tokenizer;
};

// namespace end
}

#endif
