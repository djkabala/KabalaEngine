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
/*! \file shared_ptr.hpp

  the shared_ptr template class from the boost library.
  cut'n'pasted from the file smart_ptr.hpp
  the boost::shared_ptr<T> is a reference counting smart pointer.
  read the copyright notice below

*/

// prevent multiple includes
#ifndef BOOST_SMART_PTR_HPP
#define BOOST_SMART_PTR_HPP

//  Boost smart_ptr.hpp header file  -----------------------------------------//

// (C) Copyright Greg Colvin and Beman Dawes 1998, 1999. Permission to copy,
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its
// suitability for any purpose.

// needed includes
#ifdef __sgi
#include <c_locale.h>            // for std::size_t
#else
#include <cstddef>            // for std::size_t
#endif
#include <memory>             // for std::auto_ptr
#include <algorithm>          // for std::swap
#include <functional>         // for std::less

//! namespace of the boost library
namespace boost {

// shared_ptr --------------------------------------------------------------//

//! reference counting smart pointer
/*! An enhanced relative of scoped_ptr with reference counted copy semantics.
    The object pointed to is deleted when the last shared_ptr pointing to it
    is destroyed or reset. */

template<typename T> class shared_ptr {
  public:
   typedef T element_type;

   explicit shared_ptr(T* p =0) : px(p) {
      try { pn = new long(1); }  // fix: prevent leak if new throws
      catch (...) { delete p; throw; } 
   }

   shared_ptr(const shared_ptr& r) : px(r.px) { ++*(pn = r.pn); }  // never throws

   ~shared_ptr() { dispose(); }

   shared_ptr& operator=(const shared_ptr& r) {
      share(r.px,r.pn);
      return *this;
   }

#if !defined( BOOST_NO_MEMBER_TEMPLATES )
   template<typename Y>
      shared_ptr(const shared_ptr<Y>& r) : px(r.px) {  // never throws 
         ++*(pn = r.pn); 
      }

   template<typename Y>
      shared_ptr(std::auto_ptr<Y>& r) { 
         pn = new long(1); // may throw
         px = r.release(); // fix: moved here to stop leak if new throws
      } 

   template<typename Y>
      shared_ptr& operator=(const shared_ptr<Y>& r) { 
         share(r.px,r.pn);
         return *this;
      }

   template<typename Y>
      shared_ptr& operator=(std::auto_ptr<Y>& r) {
         // code choice driven by guarantee of "no effect if new throws"
         if (*pn == 1) { delete px; }
         else { // allocate new reference counter
           long * tmp = new long(1); // may throw
           --*pn; // only decrement once danger of new throwing is past
           pn = tmp;
         } // allocate new reference counter
         px = r.release(); // fix: moved here so doesn't leak if new throws 
         return *this;
      }
#else
      shared_ptr(std::auto_ptr<T>& r) { 
         pn = new long(1); // may throw
         px = r.release(); // fix: moved here to stop leak if new throws
      } 

      shared_ptr& operator=(std::auto_ptr<T>& r) {
         // code choice driven by guarantee of "no effect if new throws"
         if (*pn == 1) { delete px; }
         else { // allocate new reference counter
           long * tmp = new long(1); // may throw
           --*pn; // only decrement once danger of new throwing is past
           pn = tmp;
         } // allocate new reference counter
         px = r.release(); // fix: moved here so doesn't leak if new throws 
         return *this;
      }
#endif

   void reset(T* p=0) {
      if ( px == p ) return;  // fix: self-assignment safe
      if (--*pn == 0) { delete px; }
      else { // allocate new reference counter
        try { pn = new long; }  // fix: prevent leak if new throws
        catch (...) {
          ++*pn;  // undo effect of --*pn above to meet effects guarantee 
          delete p;
          throw;
        } // catch
      } // allocate new reference counter
      *pn = 1;
      px = p;
   } // reset

   T& operator*() const          { return *px; }  // never throws
   T* operator->() const         { return px; }  // never throws
   T* get() const                { return px; }  // never throws
 #ifdef BOOST_SMART_PTR_CONVERSION
   // get() is safer! Define BOOST_SMART_PTR_CONVERSION at your own risk!
   operator T*() const           { return px; }  // never throws 
 #endif

   long use_count() const        { return *pn; }  // never throws
   bool unique() const           { return *pn == 1; }  // never throws

   void swap(shared_ptr<T>& other)  // never throws
     { std::swap(px,other.px); std::swap(pn,other.pn); }

// Tasteless as this may seem, making all members public allows member templates
// to work in the absence of member template friends. (Matthew Langston)
// Don't split this line into two; that causes problems for some GCC 2.95.2 builds
#if defined(BOOST_NO_MEMBER_TEMPLATES) || !defined( BOOST_NO_MEMBER_TEMPLATE_FRIENDS )
   private:
#endif

   T*     px;     // contained pointer
   long*  pn;     // ptr to reference counter

// Don't split this line into two; that causes problems for some GCC 2.95.2 builds
#if !defined( BOOST_NO_MEMBER_TEMPLATES ) && !defined( BOOST_NO_MEMBER_TEMPLATE_FRIENDS )
   template<typename Y> friend class shared_ptr;
#endif

   void dispose() { if (--*pn == 0) { delete px; delete pn; } }

   void share(T* rpx, long* rpn) {
      if (pn != rpn) {
         dispose();
         px = rpx;
         ++*(pn = rpn);
      }
   } // share
};  // shared_ptr

template<typename T, typename U>
  inline bool operator==(const shared_ptr<T>& a, const shared_ptr<U>& b)
    { return a.get() == b.get(); }

template<typename T, typename U>
  inline bool operator!=(const shared_ptr<T>& a, const shared_ptr<U>& b)
    { return a.get() != b.get(); }
/*
template<class _K, class _Pr, class _A> inline
   bool operator!=(const set<_K, _Pr, _A>& _X,
      const set<_K, _Pr, _A>& _Y)
   {return (!(_X == _Y)); }
*/

} // namespace boost


//  specializations for things in namespace std  ---------------------------//

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace std {

// Specialize std::swap to use the fast, non-throwing swap that's provided
// as a member function instead of using the default algorithm which creates
// a temporary and uses assignment.

template<typename T>
  inline void swap(boost::shared_ptr<T>& a, boost::shared_ptr<T>& b)
    { a.swap(b); }

// Specialize std::less so we can use shared pointers and arrays as keys in
// associative collections.

// It's still a controversial question whether this is better than supplying
// a full range of comparison operators (<, >, <=, >=).

template<typename T>
  struct less< boost::shared_ptr<T> >
    : binary_function<boost::shared_ptr<T>, boost::shared_ptr<T>, bool>
  {
    bool operator()(const boost::shared_ptr<T>& a,
        const boost::shared_ptr<T>& b) const
      { return less<T*>()(a.get(),b.get()); }
  };

} // namespace std

#endif

#endif
