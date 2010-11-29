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
 **     class SceneForegroundsEditor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define KE_COMPILESCENEFOREGROUNDSEDITORINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "KESceneForegroundsEditorBase.h"
#include "KESceneForegroundsEditor.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector SceneForegroundsEditorBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 



FieldContainerType SceneForegroundsEditorBase::_type(
    "SceneForegroundsEditor",
    "SceneComponentEditor",
    NULL,
    reinterpret_cast<PrototypeCreateF>(&SceneForegroundsEditorBase::createEmpty),
    SceneForegroundsEditor::initMethod,
    NULL,
    0);

//OSG_FIELD_CONTAINER_DEF(SceneForegroundsEditorBase, SceneForegroundsEditorPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &SceneForegroundsEditorBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &SceneForegroundsEditorBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr SceneForegroundsEditorBase::shallowCopy(void) const 
{ 
    SceneForegroundsEditorPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const SceneForegroundsEditor *>(this)); 

    return returnValue; 
}

UInt32 SceneForegroundsEditorBase::getContainerSize(void) const 
{ 
    return sizeof(SceneForegroundsEditor); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void SceneForegroundsEditorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<SceneForegroundsEditorBase *>(&other),
                          whichField);
}
#else
void SceneForegroundsEditorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((SceneForegroundsEditorBase *) &other, whichField, sInfo);
}
void SceneForegroundsEditorBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void SceneForegroundsEditorBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

SceneForegroundsEditorBase::SceneForegroundsEditorBase(void) :
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

SceneForegroundsEditorBase::SceneForegroundsEditorBase(const SceneForegroundsEditorBase &source) :
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

SceneForegroundsEditorBase::~SceneForegroundsEditorBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 SceneForegroundsEditorBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void SceneForegroundsEditorBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);


}

void SceneForegroundsEditorBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void SceneForegroundsEditorBase::executeSyncImpl(      SceneForegroundsEditorBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);


}
#else
void SceneForegroundsEditorBase::executeSyncImpl(      SceneForegroundsEditorBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);



}

void SceneForegroundsEditorBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<SceneForegroundsEditorPtr>::_type("SceneForegroundsEditorPtr", "SceneComponentEditorPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(SceneForegroundsEditorPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(SceneForegroundsEditorPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
