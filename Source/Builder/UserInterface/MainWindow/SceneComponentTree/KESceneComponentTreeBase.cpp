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
 **     class SceneComponentTree!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OpenSG/OSGConfig.h>




#include "KESceneComponentTreeBase.h"
#include "KESceneComponentTree.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SceneComponentTree
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<SceneComponentTree *>::_type("SceneComponentTreePtr", "InterfacePtr");
#endif

OSG_FIELDTRAITS_GETTYPE(SceneComponentTree *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           SceneComponentTree *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           SceneComponentTree *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void SceneComponentTreeBase::classDescInserter(TypeObject &oType)
{
}


SceneComponentTreeBase::TypeObject SceneComponentTreeBase::_type(
    SceneComponentTreeBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&SceneComponentTreeBase::createEmptyLocal),
    SceneComponentTree::initMethod,
    SceneComponentTree::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&SceneComponentTree::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"SceneComponentTree\"\n"
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

FieldContainerType &SceneComponentTreeBase::getType(void)
{
    return _type;
}

const FieldContainerType &SceneComponentTreeBase::getType(void) const
{
    return _type;
}

UInt32 SceneComponentTreeBase::getContainerSize(void) const
{
    return sizeof(SceneComponentTree);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 SceneComponentTreeBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void SceneComponentTreeBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void SceneComponentTreeBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
SceneComponentTreeTransitPtr SceneComponentTreeBase::createLocal(BitVector bFlags)
{
    SceneComponentTreeTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<SceneComponentTree>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
SceneComponentTreeTransitPtr SceneComponentTreeBase::createDependent(BitVector bFlags)
{
    SceneComponentTreeTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<SceneComponentTree>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
SceneComponentTreeTransitPtr SceneComponentTreeBase::create(void)
{
    SceneComponentTreeTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<SceneComponentTree>(tmpPtr);
    }

    return fc;
}

SceneComponentTree *SceneComponentTreeBase::createEmptyLocal(BitVector bFlags)
{
    SceneComponentTree *returnValue;

    newPtr<SceneComponentTree>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
SceneComponentTree *SceneComponentTreeBase::createEmpty(void)
{
    SceneComponentTree *returnValue;

    newPtr<SceneComponentTree>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr SceneComponentTreeBase::shallowCopyLocal(
    BitVector bFlags) const
{
    SceneComponentTree *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SceneComponentTree *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr SceneComponentTreeBase::shallowCopyDependent(
    BitVector bFlags) const
{
    SceneComponentTree *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const SceneComponentTree *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr SceneComponentTreeBase::shallowCopy(void) const
{
    SceneComponentTree *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const SceneComponentTree *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

SceneComponentTreeBase::SceneComponentTreeBase(void) :
    Inherited()
{
}

SceneComponentTreeBase::SceneComponentTreeBase(const SceneComponentTreeBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

SceneComponentTreeBase::~SceneComponentTreeBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void SceneComponentTreeBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    SceneComponentTree *pThis = static_cast<SceneComponentTree *>(this);

    pThis->execSync(static_cast<SceneComponentTree *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *SceneComponentTreeBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    SceneComponentTree *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const SceneComponentTree *>(pRefAspect),
                  dynamic_cast<const SceneComponentTree *>(this));

    return returnValue;
}
#endif

void SceneComponentTreeBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
