/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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
 **     Do not change this file, changes should be done in the derived      **
 **     class BackgroundsListComponentGenerator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define KE_COMPILEBACKGROUNDSLISTCOMPONENTGENERATORINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "KEBackgroundsListComponentGeneratorBase.h"
#include "KEBackgroundsListComponentGenerator.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  BackgroundsListComponentGeneratorBase::IconSizeFieldMask = 
    (TypeTraits<BitVector>::One << BackgroundsListComponentGeneratorBase::IconSizeFieldId);

const OSG::BitVector BackgroundsListComponentGeneratorBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var Vec2f           BackgroundsListComponentGeneratorBase::_sfIconSize
    
*/

//! BackgroundsListComponentGenerator description

FieldDescription *BackgroundsListComponentGeneratorBase::_desc[] = 
{
    new FieldDescription(SFVec2f::getClassType(), 
                     "IconSize", 
                     IconSizeFieldId, IconSizeFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&BackgroundsListComponentGeneratorBase::editSFIconSize))
};


FieldContainerType BackgroundsListComponentGeneratorBase::_type(
    "BackgroundsListComponentGenerator",
    "ListComponentGenerator",
    NULL,
    reinterpret_cast<PrototypeCreateF>(&BackgroundsListComponentGeneratorBase::createEmpty),
    BackgroundsListComponentGenerator::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(BackgroundsListComponentGeneratorBase, BackgroundsListComponentGeneratorPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &BackgroundsListComponentGeneratorBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &BackgroundsListComponentGeneratorBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr BackgroundsListComponentGeneratorBase::shallowCopy(void) const 
{ 
    BackgroundsListComponentGeneratorPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const BackgroundsListComponentGenerator *>(this)); 

    return returnValue; 
}

UInt32 BackgroundsListComponentGeneratorBase::getContainerSize(void) const 
{ 
    return sizeof(BackgroundsListComponentGenerator); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void BackgroundsListComponentGeneratorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<BackgroundsListComponentGeneratorBase *>(&other),
                          whichField);
}
#else
void BackgroundsListComponentGeneratorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((BackgroundsListComponentGeneratorBase *) &other, whichField, sInfo);
}
void BackgroundsListComponentGeneratorBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void BackgroundsListComponentGeneratorBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

BackgroundsListComponentGeneratorBase::BackgroundsListComponentGeneratorBase(void) :
    _sfIconSize               (Vec2f(30.0,30.0)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

BackgroundsListComponentGeneratorBase::BackgroundsListComponentGeneratorBase(const BackgroundsListComponentGeneratorBase &source) :
    _sfIconSize               (source._sfIconSize               ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

BackgroundsListComponentGeneratorBase::~BackgroundsListComponentGeneratorBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 BackgroundsListComponentGeneratorBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (IconSizeFieldMask & whichField))
    {
        returnValue += _sfIconSize.getBinSize();
    }


    return returnValue;
}

void BackgroundsListComponentGeneratorBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (IconSizeFieldMask & whichField))
    {
        _sfIconSize.copyToBin(pMem);
    }


}

void BackgroundsListComponentGeneratorBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (IconSizeFieldMask & whichField))
    {
        _sfIconSize.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void BackgroundsListComponentGeneratorBase::executeSyncImpl(      BackgroundsListComponentGeneratorBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (IconSizeFieldMask & whichField))
        _sfIconSize.syncWith(pOther->_sfIconSize);


}
#else
void BackgroundsListComponentGeneratorBase::executeSyncImpl(      BackgroundsListComponentGeneratorBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (IconSizeFieldMask & whichField))
        _sfIconSize.syncWith(pOther->_sfIconSize);



}

void BackgroundsListComponentGeneratorBase::execBeginEditImpl (const BitVector &whichField, 
                                                 UInt32     uiAspect,
                                                 UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

}
#endif



OSG_END_NAMESPACE

#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<BackgroundsListComponentGeneratorPtr>::_type("BackgroundsListComponentGeneratorPtr", "ListComponentGeneratorPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(BackgroundsListComponentGeneratorPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(BackgroundsListComponentGeneratorPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE

