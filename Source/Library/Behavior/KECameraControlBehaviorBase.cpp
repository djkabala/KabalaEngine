/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com),                            *
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
 **     class CameraControlBehavior!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OpenSG/OSGConfig.h>




#include "KECameraControlBehaviorBase.h"
#include "KECameraControlBehavior.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CameraControlBehavior
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<CameraControlBehavior *>::_type("CameraControlBehaviorPtr", "BehaviorPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(CameraControlBehavior *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           CameraControlBehavior *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           CameraControlBehavior *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void CameraControlBehaviorBase::classDescInserter(TypeObject &oType)
{
}


CameraControlBehaviorBase::TypeObject CameraControlBehaviorBase::_type(
    CameraControlBehaviorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&CameraControlBehaviorBase::createEmptyLocal),
    CameraControlBehavior::initMethod,
    CameraControlBehavior::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&CameraControlBehavior::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"CameraControlBehavior\"\n"
    "\tparent=\"Behavior\"\n"
    "\tlibrary=\"KabalaEngine\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"false\"\n"
    "\tparentsystemcomponent=\"false\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"false\"\n"
    "\tlibnamespace=\"KE\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com),                            \"\n"
    ">\n"
    "   \n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CameraControlBehaviorBase::getType(void)
{
    return _type;
}

const FieldContainerType &CameraControlBehaviorBase::getType(void) const
{
    return _type;
}

UInt32 CameraControlBehaviorBase::getContainerSize(void) const
{
    return sizeof(CameraControlBehavior);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 CameraControlBehaviorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void CameraControlBehaviorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void CameraControlBehaviorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
CameraControlBehaviorTransitPtr CameraControlBehaviorBase::createLocal(BitVector bFlags)
{
    CameraControlBehaviorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CameraControlBehavior>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CameraControlBehaviorTransitPtr CameraControlBehaviorBase::createDependent(BitVector bFlags)
{
    CameraControlBehaviorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CameraControlBehavior>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CameraControlBehaviorTransitPtr CameraControlBehaviorBase::create(void)
{
    CameraControlBehaviorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<CameraControlBehavior>(tmpPtr);
    }

    return fc;
}

CameraControlBehavior *CameraControlBehaviorBase::createEmptyLocal(BitVector bFlags)
{
    CameraControlBehavior *returnValue;

    newPtr<CameraControlBehavior>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CameraControlBehavior *CameraControlBehaviorBase::createEmpty(void)
{
    CameraControlBehavior *returnValue;

    newPtr<CameraControlBehavior>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr CameraControlBehaviorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CameraControlBehavior *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CameraControlBehavior *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CameraControlBehaviorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CameraControlBehavior *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CameraControlBehavior *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CameraControlBehaviorBase::shallowCopy(void) const
{
    CameraControlBehavior *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const CameraControlBehavior *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

CameraControlBehaviorBase::CameraControlBehaviorBase(void) :
    Inherited()
{
}

CameraControlBehaviorBase::CameraControlBehaviorBase(const CameraControlBehaviorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

CameraControlBehaviorBase::~CameraControlBehaviorBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void CameraControlBehaviorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CameraControlBehavior *pThis = static_cast<CameraControlBehavior *>(this);

    pThis->execSync(static_cast<CameraControlBehavior *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CameraControlBehaviorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CameraControlBehavior *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CameraControlBehavior *>(pRefAspect),
                  dynamic_cast<const CameraControlBehavior *>(this));

    return returnValue;
}
#endif

void CameraControlBehaviorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
