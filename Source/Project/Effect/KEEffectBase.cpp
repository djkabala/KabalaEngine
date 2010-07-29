/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  Robert Goetz (rdgoetz@iastate.edu)                            *
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
 **     class Effect!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OpenSG/OSGConfig.h>



#include <OpenSG/OSGFieldContainer.h>   // ParentSceneObject Class

#include "KEEffectBase.h"
#include "KEEffect.h"

#include <boost/bind.hpp>

#include <OpenSG/OSGEvent.h>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Effect
    The SceneObject.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var FieldContainer * EffectBase::_sfParentSceneObject
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<Effect *>::_type("EffectPtr", "AttachmentContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(Effect *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           Effect *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           Effect *,
                           0);

DataType &FieldTraits< Effect *, 1 >::getType(void)
{
    return FieldTraits<Effect *, 0>::getType();
}


OSG_EXPORT_PTR_MFIELD(ChildPointerMField,
                      Effect *,
                      UnrecordedRefCountPolicy,
                      1);


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void EffectBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFParentFieldContainerPtr::Description(
        SFParentFieldContainerPtr::getClassType(),
        "ParentSceneObject",
        "",
        ParentSceneObjectFieldId, ParentSceneObjectFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast     <FieldEditMethodSig>(&Effect::invalidEditField),
        static_cast     <FieldGetMethodSig >(&Effect::invalidGetField));

    oType.addInitialDesc(pDesc);
    pDesc = new SFEventProducerPtr::Description(
        SFEventProducerPtr::getClassType(),
        "EventProducer",
        "Event Producer",
        EventProducerFieldId,EventProducerFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast     <FieldEditMethodSig>(&Effect::editHandleEventProducer),
        static_cast     <FieldGetMethodSig >(&Effect::getHandleEventProducer));

    oType.addInitialDesc(pDesc);
}


EffectBase::TypeObject EffectBase::_type(
    EffectBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    NULL,
    Effect::initMethod,
    Effect::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&Effect::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"Effect\"\n"
    "\tparent=\"AttachmentContainer\"\n"
    "\tlibrary=\"KabalaEngine\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"abstract\"\n"
    "\tsystemcomponent=\"false\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"false\"\n"
    "\tlibnamespace=\"KE\"\n"
    "    childFields=\"multi\"\n"
    "    authors=\"Robert Goetz (rdgoetz@iastate.edu)                            \"\n"
    ">\n"
    "The SceneObject.\n"
    "    <Field\n"
    "\t\tname=\"ParentSceneObject\"\n"
    "\t\ttype=\"FieldContainer\"\n"
    "\t\tcategory=\"parentpointer\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"none\"\n"
    "\t\tdefaultValue=\"NULL\"\n"
    "        doRefCount=\"false\"\n"
    "        passFieldMask=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "    <ProducedMethod\n"
    "\t\tname=\"EffectBegan\"\n"
    "\t\ttype=\"EffectEvent\"\n"
    "\t>\n"
    "\t</ProducedMethod>\n"
    "\t<ProducedMethod\n"
    "\t\tname=\"EffectPaused\"\n"
    "\t\ttype=\"EffectEvent\"\n"
    "\t>\n"
    "\t</ProducedMethod>\n"
    "\t<ProducedMethod\n"
    "\t\tname=\"EffectUnpaused\"\n"
    "\t\ttype=\"EffectEvent\"\n"
    "\t>\n"
    "\t</ProducedMethod>\n"
    "\t<ProducedMethod\n"
    "\t\tname=\"EffectFinished\"\n"
    "\t\ttype=\"EffectEvent\"\n"
    "\t>\n"
    "\t</ProducedMethod>\n"
    "\t<ProducedMethod\n"
    "\t\tname=\"EffectStopped\"\n"
    "\t\ttype=\"EffectEvent\"\n"
    "\t>\n"
    "\t</ProducedMethod>\n"
    "</FieldContainer>\n",
    "The SceneObject.\n"
    );

//! Effect Produced Methods

MethodDescription *EffectBase::_methodDesc[] =
{
    new MethodDescription("EffectBegan", 
                    "",
                     EffectBeganMethodId, 
                     SFUnrecEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("EffectPaused", 
                    "",
                     EffectPausedMethodId, 
                     SFUnrecEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("EffectUnpaused", 
                    "",
                     EffectUnpausedMethodId, 
                     SFUnrecEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("EffectFinished", 
                    "",
                     EffectFinishedMethodId, 
                     SFUnrecEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("EffectStopped", 
                    "",
                     EffectStoppedMethodId, 
                     SFUnrecEventPtr::getClassType(),
                     FunctorAccessMethod())
};

EventProducerType EffectBase::_producerType(
    "EffectProducerType",
    "EventProducerType",
    "",
    InitEventProducerFunctor(),
    _methodDesc,
    sizeof(_methodDesc));

/*------------------------------ get -----------------------------------*/

FieldContainerType &EffectBase::getType(void)
{
    return _type;
}

const FieldContainerType &EffectBase::getType(void) const
{
    return _type;
}

const EventProducerType &EffectBase::getProducerType(void) const
{
    return _producerType;
}

UInt32 EffectBase::getContainerSize(void) const
{
    return sizeof(Effect);
}

/*------------------------- decorator get ------------------------------*/







/*------------------------------ access -----------------------------------*/

UInt32 EffectBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ParentSceneObjectFieldMask & whichField))
    {
        returnValue += _sfParentSceneObject.getBinSize();
    }
    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
    {
        returnValue += _sfEventProducer.getBinSize();
    }

    return returnValue;
}

void EffectBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentSceneObjectFieldMask & whichField))
    {
        _sfParentSceneObject.copyToBin(pMem);
    }
    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
    {
        _sfEventProducer.copyToBin(pMem);
    }
}

void EffectBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentSceneObjectFieldMask & whichField))
    {
        _sfParentSceneObject.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
    {
        _sfEventProducer.copyFromBin(pMem);
    }
}




/*------------------------- constructors ----------------------------------*/

EffectBase::EffectBase(void) :
    _Producer(&getProducerType()),
    Inherited(),
    _sfParentSceneObject      (NULL)
    ,_sfEventProducer(&_Producer)
{
}

EffectBase::EffectBase(const EffectBase &source) :
    _Producer(&source.getProducerType()),
    Inherited(source),
    _sfParentSceneObject      (NULL)
    ,_sfEventProducer(&_Producer)
{
}


/*-------------------------- destructors ----------------------------------*/

EffectBase::~EffectBase(void)
{
}
/*-------------------------------------------------------------------------*/
/* Parent linking                                                          */

bool EffectBase::linkParent(
    FieldContainer * const pParent,
    UInt16           const childFieldId,
    UInt16           const parentFieldId )
{
    if(parentFieldId == ParentSceneObjectFieldId)
    {
        FieldContainer * pTypedParent =
            dynamic_cast< FieldContainer * >(pParent);

        if(pTypedParent != NULL)
        {
            FieldContainer *pOldParent =
                _sfParentSceneObject.getValue         ();

            UInt16 oldChildFieldId =
                _sfParentSceneObject.getParentFieldPos();

            if(pOldParent != NULL)
            {
                pOldParent->unlinkChild(this, oldChildFieldId);
            }

            editSField(ParentSceneObjectFieldMask);

            _sfParentSceneObject.setValue(static_cast<FieldContainer *>(pParent), childFieldId);

            return true;
        }

        return false;
    }

    return Inherited::linkParent(pParent, childFieldId, parentFieldId);
}

bool EffectBase::unlinkParent(
    FieldContainer * const pParent,
    UInt16           const parentFieldId)
{
    if(parentFieldId == ParentSceneObjectFieldId)
    {
        FieldContainer * pTypedParent =
            dynamic_cast< FieldContainer * >(pParent);

        if(pTypedParent != NULL)
        {
            if(_sfParentSceneObject.getValue() == pParent)
            {
                editSField(ParentSceneObjectFieldMask);

                _sfParentSceneObject.setValue(NULL, 0xFFFF);

                return true;
            }

            FWARNING(("EffectBase::unlinkParent: "
                      "Child <-> Parent link inconsistent.\n"));

            return false;
        }

        return false;
    }

    return Inherited::unlinkParent(pParent, parentFieldId);
}



GetFieldHandlePtr EffectBase::getHandleParentSceneObject (void) const
{
    SFParentFieldContainerPtr::GetHandlePtr returnValue;

    return returnValue;
}

EditFieldHandlePtr EffectBase::editHandleParentSceneObject(void)
{
    EditFieldHandlePtr returnValue;

    return returnValue;
}


GetFieldHandlePtr EffectBase::getHandleEventProducer        (void) const
{
    SFEventProducerPtr::GetHandlePtr returnValue(
        new  SFEventProducerPtr::GetHandle(
             &_sfEventProducer,
             this->getType().getFieldDesc(EventProducerFieldId),
             const_cast<EffectBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr EffectBase::editHandleEventProducer       (void)
{
    SFEventProducerPtr::EditHandlePtr returnValue(
        new  SFEventProducerPtr::EditHandle(
             &_sfEventProducer,
             this->getType().getFieldDesc(EventProducerFieldId),
             this));


    editSField(EventProducerFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void EffectBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Effect *pThis = static_cast<Effect *>(this);

    pThis->execSync(static_cast<Effect *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void EffectBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
