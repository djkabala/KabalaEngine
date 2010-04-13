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
 **     class BehaviorType!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define KE_COMPILEBEHAVIORTYPEINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "KEBehaviorTypeBase.h"
#include "KEBehaviorType.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  BehaviorTypeBase::NameFieldMask = 
    (TypeTraits<BitVector>::One << BehaviorTypeBase::NameFieldId);

const OSG::BitVector  BehaviorTypeBase::DescriptionFieldMask = 
    (TypeTraits<BitVector>::One << BehaviorTypeBase::DescriptionFieldId);

const OSG::BitVector  BehaviorTypeBase::IDFieldMask = 
    (TypeTraits<BitVector>::One << BehaviorTypeBase::IDFieldId);

const OSG::BitVector BehaviorTypeBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var std::string     BehaviorTypeBase::_sfName
    
*/
/*! \var std::string     BehaviorTypeBase::_mfDescription
    
*/
/*! \var UInt32          BehaviorTypeBase::_sfID
    
*/

//! BehaviorType description

FieldDescription *BehaviorTypeBase::_desc[] = 
{
    new FieldDescription(SFString::getClassType(), 
                     "Name", 
                     NameFieldId, NameFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&BehaviorTypeBase::editSFName)),
    new FieldDescription(MFString::getClassType(), 
                     "Description", 
                     DescriptionFieldId, DescriptionFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&BehaviorTypeBase::editMFDescription)),
    new FieldDescription(SFUInt32::getClassType(), 
                     "ID", 
                     IDFieldId, IDFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&BehaviorTypeBase::editSFID))
};


FieldContainerType BehaviorTypeBase::_type(
    "BehaviorType",
    "AttachmentContainer",
    NULL,
    reinterpret_cast<PrototypeCreateF>(&BehaviorTypeBase::createEmpty),
    BehaviorType::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(BehaviorTypeBase, BehaviorTypePtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &BehaviorTypeBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &BehaviorTypeBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr BehaviorTypeBase::shallowCopy(void) const 
{ 
    BehaviorTypePtr returnValue; 

    newPtr(returnValue, dynamic_cast<const BehaviorType *>(this)); 

    return returnValue; 
}

UInt32 BehaviorTypeBase::getContainerSize(void) const 
{ 
    return sizeof(BehaviorType); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void BehaviorTypeBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<BehaviorTypeBase *>(&other),
                          whichField);
}
#else
void BehaviorTypeBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((BehaviorTypeBase *) &other, whichField, sInfo);
}
void BehaviorTypeBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void BehaviorTypeBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

    _mfDescription.terminateShare(uiAspect, this->getContainerSize());
}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

BehaviorTypeBase::BehaviorTypeBase(void) :
    _sfName                   (), 
    _mfDescription            (), 
    _sfID                     (), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

BehaviorTypeBase::BehaviorTypeBase(const BehaviorTypeBase &source) :
    _sfName                   (source._sfName                   ), 
    _mfDescription            (source._mfDescription            ), 
    _sfID                     (source._sfID                     ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

BehaviorTypeBase::~BehaviorTypeBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 BehaviorTypeBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
    {
        returnValue += _sfName.getBinSize();
    }

    if(FieldBits::NoField != (DescriptionFieldMask & whichField))
    {
        returnValue += _mfDescription.getBinSize();
    }

    if(FieldBits::NoField != (IDFieldMask & whichField))
    {
        returnValue += _sfID.getBinSize();
    }


    return returnValue;
}

void BehaviorTypeBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
    {
        _sfName.copyToBin(pMem);
    }

    if(FieldBits::NoField != (DescriptionFieldMask & whichField))
    {
        _mfDescription.copyToBin(pMem);
    }

    if(FieldBits::NoField != (IDFieldMask & whichField))
    {
        _sfID.copyToBin(pMem);
    }


}

void BehaviorTypeBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
    {
        _sfName.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (DescriptionFieldMask & whichField))
    {
        _mfDescription.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (IDFieldMask & whichField))
    {
        _sfID.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void BehaviorTypeBase::executeSyncImpl(      BehaviorTypeBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
        _sfName.syncWith(pOther->_sfName);

    if(FieldBits::NoField != (DescriptionFieldMask & whichField))
        _mfDescription.syncWith(pOther->_mfDescription);

    if(FieldBits::NoField != (IDFieldMask & whichField))
        _sfID.syncWith(pOther->_sfID);


}
#else
void BehaviorTypeBase::executeSyncImpl(      BehaviorTypeBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (NameFieldMask & whichField))
        _sfName.syncWith(pOther->_sfName);

    if(FieldBits::NoField != (IDFieldMask & whichField))
        _sfID.syncWith(pOther->_sfID);


    if(FieldBits::NoField != (DescriptionFieldMask & whichField))
        _mfDescription.syncWith(pOther->_mfDescription, sInfo);


}

void BehaviorTypeBase::execBeginEditImpl (const BitVector &whichField, 
                                                 UInt32     uiAspect,
                                                 UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (DescriptionFieldMask & whichField))
        _mfDescription.beginEdit(uiAspect, uiContainerSize);

}
#endif



OSG_END_NAMESPACE

#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<BehaviorTypePtr>::_type("BehaviorTypePtr", "AttachmentContainerPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(BehaviorTypePtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(BehaviorTypePtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);


OSG_END_NAMESPACE
