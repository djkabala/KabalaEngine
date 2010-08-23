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
#include <OpenSG/OSGEventDetails.h>

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

void Behavior::addedToSceneObject(SceneObject* const rootSceneObject)
{
	initialize(rootSceneObject);
}

void Behavior::handleDepBehaviorEvent(EventDetails* const details, UInt32 ID)
{
	depBehaviorProducedEvent(details, ID);
}

void Behavior::handleDepFieldContainerEvent(EventDetails* const details, UInt32 ID)
{
	depFieldContainerProducedEvent(details, ID);
}

void Behavior::checkListenerAttachment()
{
	attachHandlers(getParentSceneObject()->getParentScene());
}

void Behavior::attachHandlers (Scene* const eventProducer)
{
	initialized = true;

	for(UInt32 i = 0; i < theBehaviorType->_bDependencies.size(); i++)
	{
		if(theBehaviorType->_bDependencies[i]->attachedScene == getParentSceneObject()->getParentScene())
		{
			for(UInt32 c = 0; c < theBehaviorType->_bEventLinks.size(); c++)
			{
				for(UInt32 d = 0; d < theBehaviorType->_bDependencies[i]->_bEvents.size(); d++)
				{
					if(theBehaviorType->_bDependencies[i]->hasEvent(theBehaviorType->_bEventLinks[c]))
					{
                        UInt32 EventID(theBehaviorType->_bDependencies[i]->findEventID(theBehaviorType->_bEventLinks[c]));
                        eventProducer->connectGenericEvent(EventID,
                                                           boost::bind(&Behavior::handleDepBehaviorEvent, this, _1, EventID));
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

void Behavior::produceEvent(std::string name, GenericEventDetails* const eventData)
{
    if(!getBehaviorType()->hasEvent(name))
    {
        SWARNING << "Behavior::produceEvent: There is no event named " << name << endLog;
        return;
    }
    
    if(getBehaviorType()->getAttachedScene() == NULL)
    {
        SWARNING << "Behavior::produceEvent: The attached scene is null " << endLog;
        return;
    }
    
    if(eventData == NULL)
    {
        GenericEventDetailsUnrecPtr details = GenericEventDetails::create(this, getTimeStamp());
        getBehaviorType()->getAttachedScene()->produceGenericEvent(name, details);
    }
    else
    {
        getBehaviorType()->getAttachedScene()->produceGenericEvent(  name,
                                                                     eventData);
    }
}

void Behavior::produceEvent(UInt32 id, GenericEventDetails* const eventData)
{
    if(!getBehaviorType()->hasEvent(getBehaviorType()->findEventName(id)))
    {
        SWARNING << "Behavior::produceEvent: There is no event with id " << id << endLog;
        return;
    }
    
    if(getBehaviorType()->getAttachedScene() == NULL)
    {
        SWARNING << "Behavior::produceEvent: The attached scene is null " << endLog;
        return;
    }
    
    if(eventData == NULL){
        GenericEventDetailsUnrecPtr details = GenericEventDetails::create(this, getTimeStamp());
        getBehaviorType()->getAttachedScene()->produceGenericEvent(id, details);
    }
    else
    {
        getBehaviorType()->getAttachedScene()->produceGenericEvent(  id,
                                                                     eventData);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Behavior::Behavior(void) :
    Inherited(),
	initialized(false)
{
}

Behavior::Behavior(const Behavior &source) :
    Inherited(source),
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
