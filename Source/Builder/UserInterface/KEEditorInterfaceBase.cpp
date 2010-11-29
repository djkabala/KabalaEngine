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
 **     class EditorInterface!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define KE_COMPILEEDITORINTERFACEINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "KEEditorInterfaceBase.h"
#include "KEEditorInterface.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector EditorInterfaceBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 



FieldContainerType EditorInterfaceBase::_type(
    "EditorInterface",
    "Interface",
    NULL,
    NULL, 
    EditorInterface::initMethod,
    NULL,
    0);

//OSG_FIELD_CONTAINER_DEF(EditorInterfaceBase, EditorInterfacePtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &EditorInterfaceBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &EditorInterfaceBase::getType(void) const 
{
    return _type;
} 


UInt32 EditorInterfaceBase::getContainerSize(void) const 
{ 
    return sizeof(EditorInterface); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void EditorInterfaceBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<EditorInterfaceBase *>(&other),
                          whichField);
}
#else
void EditorInterfaceBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((EditorInterfaceBase *) &other, whichField, sInfo);
}
void EditorInterfaceBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void EditorInterfaceBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

EditorInterfaceBase::EditorInterfaceBase(void) :
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

EditorInterfaceBase::EditorInterfaceBase(const EditorInterfaceBase &source) :
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

EditorInterfaceBase::~EditorInterfaceBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 EditorInterfaceBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void EditorInterfaceBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);


}

void EditorInterfaceBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void EditorInterfaceBase::executeSyncImpl(      EditorInterfaceBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);


}
#else
void EditorInterfaceBase::executeSyncImpl(      EditorInterfaceBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);



}

void EditorInterfaceBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<EditorInterfacePtr>::_type("EditorInterfacePtr", "InterfacePtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(EditorInterfacePtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(EditorInterfacePtr, KE_KABALAENGINELIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
