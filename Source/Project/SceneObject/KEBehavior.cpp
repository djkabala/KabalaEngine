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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "Project/Scene/KEScene.h"

#include "KEBehavior.h"
#include "KEBehaviorFactory.h"
#include <OpenSG/OSGEvent.h>
#include <OpenSG/OSGEventListener.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBehaviorBase.cpp file.
// To modify it, please change the .fcd file (OSGBehavior.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               * 
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 * 
\***************************************************************************/

void Behavior::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Behavior::addedToSceneObject(SceneObjectUnrecPtr rootSceneObject)
{
	initialize(rootSceneObject);
}

void Behavior::DepFieldContainerListener::eventProduced(const EventUnrecPtr e, UInt32 ID)
{
	_Behavior->depFieldContainerProducedMethod(e, ID);
}

void Behavior::DepBehaviorListener::eventProduced(const EventUnrecPtr e, UInt32 ID)
{
	_Behavior->depBehaviorProducedMethod(e, ID);
}

void Behavior::checkListenerAttachment()
{
	attachListeners(dynamic_cast<SceneObject*>(_sfSceneObject.getValue())->getParentScene()->editEventProducer());
}

void Behavior::attachListeners (EventProducerPtr eventProducer)
{
	initialized = true;

	for(UInt32 i = 0; i < theBehaviorType->_bDependencies.size(); i++)
	{
		if(theBehaviorType->_bDependencies[i]->attachedScene == dynamic_cast<SceneObject*>(_sfSceneObject.getValue())->getParentScene())
		{
			for(UInt32 c = 0; c < theBehaviorType->_bEventLinks.size(); c++)
			{
				for(UInt32 d = 0; d < theBehaviorType->_bDependencies[i]->_bEvents.size(); d++)
				{
					if(theBehaviorType->_bDependencies[i]->hasEvent(theBehaviorType->_bEventLinks[c]))
					{
						eventProducer->attachEventListener(&_DepBehaviorListener,theBehaviorType->_bDependencies[i]->findEventID(theBehaviorType->_bEventLinks[c]));
					}
				}
			}
		}
		else
		{
			initialized = false;
		}
	}
}

SceneObject* Behavior::getParentSceneObject(void) const
{
    return dynamic_cast<SceneObject*>(_sfSceneObject.getValue());
}

void Behavior::produceEvent(std::string name, GenericEventRefPtr eventData)
{
    if(!getBehaviorType()->hasEvent(name))
    {
        SWARNING << "Behavior::produceEvent: There is no event named " << name << endLog;
        return;
    }
    
    if(getBehaviorType()->attachedScene == NULL)
    {
        SWARNING << "Behavior::produceEvent: The attached scene is null " << endLog;
        return;
    }
    
    if(eventData == NULL){
        getBehaviorType()->attachedScene->produceGenericEvent(  name,
                                                                GenericEvent::create(BehaviorRefPtr(this), getTimeStamp()));
    }
    else
    {
        getBehaviorType()->attachedScene->produceGenericEvent(  name,
                                                                eventData);
    }
}

void Behavior::produceEvent(UInt32 id, GenericEventRefPtr eventData)
{
    if(!getBehaviorType()->hasEvent(getBehaviorType()->findEventName(id)))
    {
        SWARNING << "Behavior::produceEvent: There is no event with id " << id << endLog;
        return;
    }
    
    if(getBehaviorType()->attachedScene == NULL)
    {
        SWARNING << "Behavior::produceEvent: The attached scene is null " << endLog;
        return;
    }
    
    if(eventData == NULL){
        getBehaviorType()->attachedScene->produceGenericEvent(  id,
                                                                GenericEvent::create(BehaviorRefPtr(this), getTimeStamp()));
    }
    else
    {
        getBehaviorType()->attachedScene->produceGenericEvent(  id,
                                                                eventData);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Behavior::Behavior(void) :
    Inherited(),
	_DepBehaviorListener(BehaviorUnrecPtr(this)),
    _DepFieldContainerListener(BehaviorUnrecPtr(this)),
	initialized(false)
{
}

Behavior::Behavior(const Behavior &source) :
    Inherited(source),
	_DepBehaviorListener(BehaviorUnrecPtr(this)),
    _DepFieldContainerListener(BehaviorUnrecPtr(this)),
	initialized(false)
{
}

Behavior::~Behavior(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Behavior::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Behavior::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Behavior NI" << std::endl;
}

OSG_END_NAMESPACE
