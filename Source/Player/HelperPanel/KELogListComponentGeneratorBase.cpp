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
 **     class LogListComponentGenerator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "KELogListComponentGeneratorBase.h"
#include "KELogListComponentGenerator.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LogListComponentGenerator
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<LogListComponentGenerator *>::_type("LogListComponentGeneratorPtr", "DefaultListComponentGeneratorPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(LogListComponentGenerator *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           LogListComponentGenerator *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           LogListComponentGenerator *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void LogListComponentGeneratorBase::classDescInserter(TypeObject &oType)
{
}


LogListComponentGeneratorBase::TypeObject LogListComponentGeneratorBase::_type(
    LogListComponentGeneratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&LogListComponentGeneratorBase::createEmptyLocal),
    LogListComponentGenerator::initMethod,
    LogListComponentGenerator::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&LogListComponentGenerator::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"LogListComponentGenerator\"\n"
    "\tparent=\"DefaultListComponentGenerator\"\n"
    "\tlibrary=\"KabalaEngine\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"false\"\n"
    "\tisNodeCore=\"false\"\n"
    "\tauthors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &LogListComponentGeneratorBase::getType(void)
{
    return _type;
}

const FieldContainerType &LogListComponentGeneratorBase::getType(void) const
{
    return _type;
}

UInt32 LogListComponentGeneratorBase::getContainerSize(void) const
{
    return sizeof(LogListComponentGenerator);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 LogListComponentGeneratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void LogListComponentGeneratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void LogListComponentGeneratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
LogListComponentGeneratorTransitPtr LogListComponentGeneratorBase::createLocal(BitVector bFlags)
{
    LogListComponentGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<LogListComponentGenerator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
LogListComponentGeneratorTransitPtr LogListComponentGeneratorBase::createDependent(BitVector bFlags)
{
    LogListComponentGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<LogListComponentGenerator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
LogListComponentGeneratorTransitPtr LogListComponentGeneratorBase::create(void)
{
    LogListComponentGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<LogListComponentGenerator>(tmpPtr);
    }

    return fc;
}

LogListComponentGenerator *LogListComponentGeneratorBase::createEmptyLocal(BitVector bFlags)
{
    LogListComponentGenerator *returnValue;

    newPtr<LogListComponentGenerator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
LogListComponentGenerator *LogListComponentGeneratorBase::createEmpty(void)
{
    LogListComponentGenerator *returnValue;

    newPtr<LogListComponentGenerator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr LogListComponentGeneratorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    LogListComponentGenerator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LogListComponentGenerator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr LogListComponentGeneratorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    LogListComponentGenerator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const LogListComponentGenerator *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr LogListComponentGeneratorBase::shallowCopy(void) const
{
    LogListComponentGenerator *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const LogListComponentGenerator *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

LogListComponentGeneratorBase::LogListComponentGeneratorBase(void) :
    Inherited()
{
}

LogListComponentGeneratorBase::LogListComponentGeneratorBase(const LogListComponentGeneratorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

LogListComponentGeneratorBase::~LogListComponentGeneratorBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void LogListComponentGeneratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    LogListComponentGenerator *pThis = static_cast<LogListComponentGenerator *>(this);

    pThis->execSync(static_cast<LogListComponentGenerator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *LogListComponentGeneratorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    LogListComponentGenerator *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const LogListComponentGenerator *>(pRefAspect),
                  dynamic_cast<const LogListComponentGenerator *>(this));

    return returnValue;
}
#endif

void LogListComponentGeneratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE