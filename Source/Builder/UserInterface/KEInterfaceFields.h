/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _KEINTERFACEFIELDS_H_
#define _KEINTERFACEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/OSGPointerSField.h>
#include <OpenSG/OSGPointerMField.h>


OSG_BEGIN_NAMESPACE

class Interface;

OSG_GEN_CONTAINERPTR(Interface);

/*! \ingroup GrpKabalaEngineFieldTraits
    \ingroup GrpLibOSGKabalaEngine
 */
template <>
struct FieldTraits<Interface *> :
    public FieldTraitsFCPtrBase<Interface *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<Interface *>  Self;

    enum                        { Convertible = NotConvertible };

    static KE_KABALAENGINE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFInterfacePtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFInterfacePtr"; }
};

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakInterfacePtr"; 
}

template<> inline
const Char8 *FieldTraits<Interface *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdInterfacePtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<Interface *,
                      RecordedRefCountPolicy  > SFRecInterfacePtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<Interface *,
                      UnrecordedRefCountPolicy> SFUnrecInterfacePtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<Interface *,
                      WeakRefCountPolicy      > SFWeakInterfacePtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<Interface *,
                      NoRefCountPolicy        > SFUncountedInterfacePtr;


/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<Interface *,
                      RecordedRefCountPolicy  > MFRecInterfacePtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<Interface *,
                      UnrecordedRefCountPolicy> MFUnrecInterfacePtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<Interface *,
                      WeakRefCountPolicy      > MFWeakInterfacePtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<Interface *,
                      NoRefCountPolicy        > MFUncountedInterfacePtr;




#else // these are the doxygen hacks

/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFRecInterfacePtr : 
    public PointerSField<Interface *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUnrecInterfacePtr : 
    public PointerSField<Interface *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFWeakInterfacePtr :
    public PointerSField<Interface *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUncountedInterfacePtr :
    public PointerSField<Interface *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFRecInterfacePtr :
    public PointerMField<Interface *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUnrecInterfacePtr :
    public PointerMField<Interface *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFWeakInterfacePtr :
    public PointerMField<Interface *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUncountedInterfacePtr :
    public PointerMField<Interface *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _KEINTERFACEFIELDS_H_ */
