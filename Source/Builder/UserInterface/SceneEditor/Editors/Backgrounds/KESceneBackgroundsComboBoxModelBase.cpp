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
 **     class SceneBackgroundsComboBoxModel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define KE_COMPILESCENEBACKGROUNDSCOMBOBOXMODELINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "KESceneBackgroundsComboBoxModelBase.h"
#include "KESceneBackgroundsComboBoxModel.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  SceneBackgroundsComboBoxModelBase::EditingSceneFieldMask = 
    (TypeTraits<BitVector>::One << SceneBackgroundsComboBoxModelBase::EditingSceneFieldId);

const OSG::BitVector SceneBackgroundsComboBoxModelBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var ScenePtr        SceneBackgroundsComboBoxModelBase::_sfEditingScene
    
*/

//! SceneBackgroundsComboBoxModel description

FieldDescription *SceneBackgroundsComboBoxModelBase::_desc[] = 
{
    new FieldDescription(SFScenePtr::getClassType(), 
                     "EditingScene", 
                     EditingSceneFieldId, EditingSceneFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SceneBackgroundsComboBoxModelBase::editSFEditingScene))
};


FieldContainerType SceneBackgroundsComboBoxModelBase::_type(
    "SceneBackgroundsComboBoxModel",
    "AbstractComboBoxModel",
    NULL,
    reinterpret_cast<PrototypeCreateF>(&SceneBackgroundsComboBoxModelBase::createEmpty),
    SceneBackgroundsComboBoxModel::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(SceneBackgroundsComboBoxModelBase, SceneBackgroundsComboBoxModelPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &SceneBackgroundsComboBoxModelBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &SceneBackgroundsComboBoxModelBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr SceneBackgroundsComboBoxModelBase::shallowCopy(void) const 
{ 
    SceneBackgroundsComboBoxModelPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const SceneBackgroundsComboBoxModel *>(this)); 

    return returnValue; 
}

UInt32 SceneBackgroundsComboBoxModelBase::getContainerSize(void) const 
{ 
    return sizeof(SceneBackgroundsComboBoxModel); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void SceneBackgroundsComboBoxModelBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<SceneBackgroundsComboBoxModelBase *>(&other),
                          whichField);
}
#else
void SceneBackgroundsComboBoxModelBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((SceneBackgroundsComboBoxModelBase *) &other, whichField, sInfo);
}
void SceneBackgroundsComboBoxModelBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void SceneBackgroundsComboBoxModelBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

SceneBackgroundsComboBoxModelBase::SceneBackgroundsComboBoxModelBase(void) :
    _sfEditingScene           (ScenePtr(NullFC)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

SceneBackgroundsComboBoxModelBase::SceneBackgroundsComboBoxModelBase(const SceneBackgroundsComboBoxModelBase &source) :
    _sfEditingScene           (source._sfEditingScene           ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

SceneBackgroundsComboBoxModelBase::~SceneBackgroundsComboBoxModelBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 SceneBackgroundsComboBoxModelBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (EditingSceneFieldMask & whichField))
    {
        returnValue += _sfEditingScene.getBinSize();
    }


    return returnValue;
}

void SceneBackgroundsComboBoxModelBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (EditingSceneFieldMask & whichField))
    {
        _sfEditingScene.copyToBin(pMem);
    }


}

void SceneBackgroundsComboBoxModelBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (EditingSceneFieldMask & whichField))
    {
        _sfEditingScene.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void SceneBackgroundsComboBoxModelBase::executeSyncImpl(      SceneBackgroundsComboBoxModelBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (EditingSceneFieldMask & whichField))
        _sfEditingScene.syncWith(pOther->_sfEditingScene);


}
#else
void SceneBackgroundsComboBoxModelBase::executeSyncImpl(      SceneBackgroundsComboBoxModelBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (EditingSceneFieldMask & whichField))
        _sfEditingScene.syncWith(pOther->_sfEditingScene);



}

void SceneBackgroundsComboBoxModelBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<SceneBackgroundsComboBoxModelPtr>::_type("SceneBackgroundsComboBoxModelPtr", "AbstractComboBoxModelPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(SceneBackgroundsComboBoxModelPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(SceneBackgroundsComboBoxModelPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
