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


#ifndef _KEBACKGROUNDEDITORFIELDS_H_
#define _KEBACKGROUNDEDITORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/OSGPointerSField.h>
#include <OpenSG/OSGPointerMField.h>


OSG_BEGIN_NAMESPACE

class BackgroundEditor;

OSG_GEN_CONTAINERPTR(BackgroundEditor);

/*! \ingroup GrpKabalaEngineFieldTraits
    \ingroup GrpLibOSGKabalaEngine
 */
template <>
struct FieldTraits<BackgroundEditor *> :
    public FieldTraitsFCPtrBase<BackgroundEditor *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<BackgroundEditor *>  Self;

    enum                        { Convertible = NotConvertible };

    static KE_KABALAENGINE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFBackgroundEditorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFBackgroundEditorPtr"; }
};

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakBackgroundEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<BackgroundEditor *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdBackgroundEditorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<BackgroundEditor *,
                      RecordedRefCountPolicy  > SFRecBackgroundEditorPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<BackgroundEditor *,
                      UnrecordedRefCountPolicy> SFUnrecBackgroundEditorPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<BackgroundEditor *,
                      WeakRefCountPolicy      > SFWeakBackgroundEditorPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<BackgroundEditor *,
                      NoRefCountPolicy        > SFUncountedBackgroundEditorPtr;


/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<BackgroundEditor *,
                      RecordedRefCountPolicy  > MFRecBackgroundEditorPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<BackgroundEditor *,
                      UnrecordedRefCountPolicy> MFUnrecBackgroundEditorPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<BackgroundEditor *,
                      WeakRefCountPolicy      > MFWeakBackgroundEditorPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<BackgroundEditor *,
                      NoRefCountPolicy        > MFUncountedBackgroundEditorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFRecBackgroundEditorPtr : 
    public PointerSField<BackgroundEditor *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUnrecBackgroundEditorPtr : 
    public PointerSField<BackgroundEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFWeakBackgroundEditorPtr :
    public PointerSField<BackgroundEditor *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUncountedBackgroundEditorPtr :
    public PointerSField<BackgroundEditor *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFRecBackgroundEditorPtr :
    public PointerMField<BackgroundEditor *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUnrecBackgroundEditorPtr :
    public PointerMField<BackgroundEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFWeakBackgroundEditorPtr :
    public PointerMField<BackgroundEditor *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUncountedBackgroundEditorPtr :
    public PointerMField<BackgroundEditor *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _KEBACKGROUNDEDITORFIELDS_H_ */
