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


#ifndef _KEASSETSTOREFIELDS_H_
#define _KEASSETSTOREFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/OSGPointerSField.h>
#include <OpenSG/OSGPointerMField.h>


OSG_BEGIN_NAMESPACE

class AssetStore;

OSG_GEN_CONTAINERPTR(AssetStore);

/*! \ingroup GrpKabalaEngineFieldTraits
    \ingroup GrpLibOSGKabalaEngine
 */
template <>
struct FieldTraits<AssetStore *> :
    public FieldTraitsFCPtrBase<AssetStore *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<AssetStore *>  Self;

    enum                        { Convertible = NotConvertible };

    static KE_KABALAENGINE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFAssetStorePtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFAssetStorePtr"; }
};

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAssetStorePtr"; 
}

template<> inline
const Char8 *FieldTraits<AssetStore *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAssetStorePtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<AssetStore *,
                      RecordedRefCountPolicy  > SFRecAssetStorePtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<AssetStore *,
                      UnrecordedRefCountPolicy> SFUnrecAssetStorePtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<AssetStore *,
                      WeakRefCountPolicy      > SFWeakAssetStorePtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<AssetStore *,
                      NoRefCountPolicy        > SFUncountedAssetStorePtr;


/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<AssetStore *,
                      RecordedRefCountPolicy  > MFRecAssetStorePtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<AssetStore *,
                      UnrecordedRefCountPolicy> MFUnrecAssetStorePtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<AssetStore *,
                      WeakRefCountPolicy      > MFWeakAssetStorePtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<AssetStore *,
                      NoRefCountPolicy        > MFUncountedAssetStorePtr;




#else // these are the doxygen hacks

/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFRecAssetStorePtr : 
    public PointerSField<AssetStore *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUnrecAssetStorePtr : 
    public PointerSField<AssetStore *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFWeakAssetStorePtr :
    public PointerSField<AssetStore *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUncountedAssetStorePtr :
    public PointerSField<AssetStore *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFRecAssetStorePtr :
    public PointerMField<AssetStore *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUnrecAssetStorePtr :
    public PointerMField<AssetStore *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFWeakAssetStorePtr :
    public PointerMField<AssetStore *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUncountedAssetStorePtr :
    public PointerMField<AssetStore *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _KEASSETSTOREFIELDS_H_ */
