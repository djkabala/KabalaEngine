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
 **     class ViewportEditor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OpenSG/OSGConfig.h>




#include "KEViewportEditorBase.h"
#include "KEViewportEditor.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ViewportEditor
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ViewportEditor *>::_type("ViewportEditorPtr", "EditorInterfacePtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ViewportEditor *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ViewportEditor *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ViewportEditor *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ViewportEditorBase::classDescInserter(TypeObject &oType)
{
}


ViewportEditorBase::TypeObject ViewportEditorBase::_type(
    ViewportEditorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ViewportEditorBase::createEmptyLocal),
    ViewportEditor::initMethod,
    ViewportEditor::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ViewportEditor::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ViewportEditor\"\n"
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

FieldContainerType &ViewportEditorBase::getType(void)
{
    return _type;
}

const FieldContainerType &ViewportEditorBase::getType(void) const
{
    return _type;
}

UInt32 ViewportEditorBase::getContainerSize(void) const
{
    return sizeof(ViewportEditor);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 ViewportEditorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void ViewportEditorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void ViewportEditorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
ViewportEditorTransitPtr ViewportEditorBase::createLocal(BitVector bFlags)
{
    ViewportEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ViewportEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ViewportEditorTransitPtr ViewportEditorBase::createDependent(BitVector bFlags)
{
    ViewportEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ViewportEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ViewportEditorTransitPtr ViewportEditorBase::create(void)
{
    ViewportEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ViewportEditor>(tmpPtr);
    }

    return fc;
}

ViewportEditor *ViewportEditorBase::createEmptyLocal(BitVector bFlags)
{
    ViewportEditor *returnValue;

    newPtr<ViewportEditor>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ViewportEditor *ViewportEditorBase::createEmpty(void)
{
    ViewportEditor *returnValue;

    newPtr<ViewportEditor>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ViewportEditorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ViewportEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ViewportEditor *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ViewportEditorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ViewportEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ViewportEditor *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ViewportEditorBase::shallowCopy(void) const
{
    ViewportEditor *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ViewportEditor *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

ViewportEditorBase::ViewportEditorBase(void) :
    Inherited()
{
}

ViewportEditorBase::ViewportEditorBase(const ViewportEditorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

ViewportEditorBase::~ViewportEditorBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void ViewportEditorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ViewportEditor *pThis = static_cast<ViewportEditor *>(this);

    pThis->execSync(static_cast<ViewportEditor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ViewportEditorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ViewportEditor *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ViewportEditor *>(pRefAspect),
                  dynamic_cast<const ViewportEditor *>(this));

    return returnValue;
}
#endif

void ViewportEditorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE