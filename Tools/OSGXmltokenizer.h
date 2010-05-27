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
/*! \file xmltokenizer.h

  the stream tokenizer class

*/

// prevent multiple includes
#ifndef __xmltokenizer_h_
#define __xmltokenizer_h_

// needed includes
#include "OSGXmlpp.h"
#include <stack>
#include <iostream>


// namespace declaration
namespace xmlpp {


//! xml token
/*! an xmltoken is a representation for a literal character or a 
    generic string (not recognized as a literal) */
class xmltoken
{
   friend class xmlstream_iterator;
public:
   //! ctor
   xmltoken(){ isliteral=true; literal=0; generic.empty(); }
   //! ctor with init
   xmltoken( xml_char_type ch ){ isliteral=true; literal=ch; generic.empty(); }
   //! ctor with init
   xmltoken( xmlstring &str ):generic(str){ isliteral=false; literal=0; }

   //! returns if token is a literal
   bool is_literal(){ return isliteral; }
   //! returns literal char
   xml_char_type get_literal(){ return literal; }
   //! returns generic string
   xmlstring &get_generic(){ return generic; }

   // operators

   //! compare operator for literals
   bool operator ==(xml_char_type ch){ return !isliteral?false:ch==literal; }
   //! compare operator for literals
   bool operator !=(xml_char_type ch){ return !isliteral?true:ch!=literal; }

   //! compare operator for a generic string
   bool operator ==(xmlstring str){ return !isliteral?str==generic:false; }
   //! compare operator for a generic string
   bool operator !=(xmlstring str){ return !isliteral?str!=generic:true; }

   //! set generic string
   xmltoken &operator =(xmlstring &str){ generic.assign(str); isliteral=false; return *this; }
   //! set literal char
   xmltoken &operator =(xml_char_type ch){ literal=ch; isliteral=true; return *this; }

protected:
   //! indicates if token is a literal char
   bool isliteral;
   //! literal
   xml_char_type literal;
   //! pointer to string
   xmlstring generic;
};


//! base tokenizer class
/*! base class for iterating through xmltoken */
class xmltokenizer
{
public:
   //! ctor
   xmltokenizer(std::istream &is,xmllocation &loc):instr(is),location(loc){}
   virtual ~xmltokenizer(){}

   //! dereference operator
   xmltoken& operator*(){ return curtoken; }
   //! pointer access operator
   const xmltoken* operator->(){ return &curtoken; }
   //! advances in the xml stream
   xmltokenizer &operator++(){ get_next(); return *this; }
   //! advances in the xml stream
   xmltokenizer &operator++(int){ get_next(); return *this; }

   //! returns current token
   xmltoken& get(){ return curtoken; }

   //! puts the token back into the stream
   void put_back( xmltoken &token ){ tokenstack.push(token); }

   //! puts the last token back into the stream
   void put_back(){ tokenstack.push(curtoken); }

protected:

   //! internal: parses the next token
   virtual void get_next() = 0;

   // data members

   //! input stream
   std::istream &instr;

   //! location in the stream
   xmllocation &location;

   //! current token
   xmltoken curtoken;

   //! stack for put_back()'ed tokens
   std::stack<xmltoken> tokenstack;
};

//! xml input stream iterator
/*! an iterator through all xmltoken contained in the xml input stream */
class xmlstream_iterator:public xmltokenizer
{
public:
   //! ctor
   xmlstream_iterator(std::istream &is,xmllocation &loc);

protected:
   void get_next();

   // internally used to recognize chars in the stream
   bool is_literal( xml_char_type c );
   bool is_whitespace( xml_char_type c );
   bool is_newline( xml_char_type c );
   bool is_stringdelimiter( xml_char_type c ); // start-/endchar of a string

   //! cdata-mode doesn't care for whitespaces in generic strings
   bool cdata_mode;

   //! char which was put back internally
   int putback_char;
};

//! dtd input stream iterator
/*! an iterator through a dtd input stream */
class xmldtd_iterator:public xmltokenizer
{
public:
   //! ctor
   xmldtd_iterator(std::istream &is,xmllocation &loc);

protected:
   void get_next(){}
};


// namespace end
}

#endif
