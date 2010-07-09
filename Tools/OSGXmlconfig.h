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
/*! \file xmlconfig.h

  system dependent stuff

*/

// prevent multiple includes
#ifndef __xmlconfig_h_
#define __xmlconfig_h_

// needed includes

// -----------------------------------
// win32 configuration
#ifdef WIN32

// define's for the boost::shared_ptr
# define BOOST_NO_MEMBER_TEMPLATES
# define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// switch some warnings off
# pragma warning( disable: 4786 4275 4251 )

// export/import #define's for building a win32 dll
//# ifdef XMLPP_EXPORTS
#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEBASELIB
#     define XMLPP_API __declspec(dllexport)
#   else
#     define XMLPP_API __declspec(dllimport)
#   endif
#else
#  define XMLPP_API
#endif

//# ifdef XMLPP_NOEXPORTS
//#  undef XMLPP_API
//#  define XMLPP_API
//# endif

// includes building of the httpinstream class
#define XMLPP_WITH_CUSTOM_IOSTREAM

#endif

// -----------------------------------
// unix/linux configuration
#ifndef WIN32 

// dummy define
# define XMLPP_API

// defines for the boost library
# define BOOST_NO_MEMBER_TEMPLATE_FRIENDS

// includes building of the httpinstream class
#define XMLPP_WITH_CUSTOM_IOSTREAM

#endif


// -----------------------------------
#endif
