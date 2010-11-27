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
 **     class HelpPanel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OpenSG/OSGConfig.h>




#include "KEHelpPanelBase.h"
#include "KEHelpPanel.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::HelpPanel
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<HelpPanel *>::_type("HelpPanelPtr", "InterfacePtr");
#endif

OSG_FIELDTRAITS_GETTYPE(HelpPanel *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           HelpPanel *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           HelpPanel *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void HelpPanelBase::classDescInserter(TypeObject &oType)
{
}


HelpPanelBase::TypeObject HelpPanelBase::_type(
    HelpPanelBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&HelpPanelBase::createEmptyLocal),
    HelpPanel::initMethod,
    HelpPanel::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&HelpPanel::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"HelpPanel\"\n"
    "\tparent=\"Interface\"\n"
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

FieldContainerType &HelpPanelBase::getType(void)
{
    return _type;
}

const FieldContainerType &HelpPanelBase::getType(void) const
{
    return _type;
}

UInt32 HelpPanelBase::getContainerSize(void) const
{
    return sizeof(HelpPanel);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 HelpPanelBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void HelpPanelBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void HelpPanelBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
HelpPanelTransitPtr HelpPanelBase::createLocal(BitVector bFlags)
{
    HelpPanelTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<HelpPanel>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
HelpPanelTransitPtr HelpPanelBase::createDependent(BitVector bFlags)
{
    HelpPanelTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<HelpPanel>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
HelpPanelTransitPtr HelpPanelBase::create(void)
{
    HelpPanelTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<HelpPanel>(tmpPtr);
    }

    return fc;
}

HelpPanel *HelpPanelBase::createEmptyLocal(BitVector bFlags)
{
    HelpPanel *returnValue;

    newPtr<HelpPanel>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
HelpPanel *HelpPanelBase::createEmpty(void)
{
    HelpPanel *returnValue;

    newPtr<HelpPanel>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr HelpPanelBase::shallowCopyLocal(
    BitVector bFlags) const
{
    HelpPanel *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const HelpPanel *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr HelpPanelBase::shallowCopyDependent(
    BitVector bFlags) const
{
    HelpPanel *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const HelpPanel *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr HelpPanelBase::shallowCopy(void) const
{
    HelpPanel *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const HelpPanel *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

HelpPanelBase::HelpPanelBase(void) :
    Inherited()
{
}

HelpPanelBase::HelpPanelBase(const HelpPanelBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

HelpPanelBase::~HelpPanelBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void HelpPanelBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    HelpPanel *pThis = static_cast<HelpPanel *>(this);

    pThis->execSync(static_cast<HelpPanel *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *HelpPanelBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    HelpPanel *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const HelpPanel *>(pRefAspect),
                  dynamic_cast<const HelpPanel *>(this));

    return returnValue;
}
#endif

void HelpPanelBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
