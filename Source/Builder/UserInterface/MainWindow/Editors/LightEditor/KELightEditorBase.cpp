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
 **     Do not change this file, changes should be done in the derived      **
 **     class LightEditor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OpenSG/OSGConfig.h>




#include "KELightEditorBase.h"
#include "KELightEditor.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LightEditor
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<LightEditor *>::_type("LightEditorPtr", "EditorInterfacePtr");
#endif

OSG_FIELDTRAITS_GETTYPE(LightEditor *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           LightEditor *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           LightEditor *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void LightEditorBase::classDescInserter(TypeObject &oType)
{
}


LightEditorBase::TypeObject LightEditorBase::_type(
    LightEditorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&LightEditorBase::createEmptyLocal),
    LightEditor::initMethod,
    LightEditor::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&LightEditor::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"LightEditor\"\n"
    "\tparent=\"EditorInterface\"\n"
    "\tlibrary=\"KabalaEngine\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"false\"\n"
    "\tparentsystemcomponent=\"false\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"false\"\n"
    "\tlibnamespace=\"KE\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &LightEditorBase::getType(void)
{
    return _type;
}

const FieldContainerType &LightEditorBase::getType(void) const
{
    return _type;
}

UInt32 LightEditorBase::getContainerSize(void) const
{
    return sizeof(LightEditor);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 LightEditorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void LightEditorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void LightEditorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
LightEditorTransitPtr LightEditorBase::createLocal(BitVector bFlags)
{
    LightEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<LightEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
LightEditorTransitPtr LightEditorBase::createDependent(BitVector bFlags)
{
    LightEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<LightEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
LightEditorTransitPtr LightEditorBase::create(void)
{
    LightEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<LightEditor>(tmpPtr);
    }

    return fc;
}

LightEditor *LightEditorBase::createEmptyLocal(BitVector bFlags)
{
    LightEditor *returnValue;

    newPtr<LightEditor>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
LightEditor *LightEditorBase::createEmpty(void)
{
    LightEditor *returnValue;

    newPtr<LightEditor>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr LightEditorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    LightEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LightEditor *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr LightEditorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    LightEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LightEditor *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr LightEditorBase::shallowCopy(void) const
{
    LightEditor *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const LightEditor *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

LightEditorBase::LightEditorBase(void) :
    Inherited()
{
}

LightEditorBase::LightEditorBase(const LightEditorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

LightEditorBase::~LightEditorBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void LightEditorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    LightEditor *pThis = static_cast<LightEditor *>(this);

    pThis->execSync(static_cast<LightEditor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *LightEditorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    LightEditor *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const LightEditor *>(pRefAspect),
                  dynamic_cast<const LightEditor *>(this));

    return returnValue;
}
#endif

void LightEditorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
