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
#include "KEBehaviorType.h"
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

void Behavior::initialize(SceneObjectUnrecPtr rootSceneObject)
{
	TheBehaviorType->registerWithScene(rootSceneObject->getParentScene());
	attachListeners(rootSceneObject->getParentScene()->editEventProducer());
}

void Behavior::addedToSceneObject(SceneObjectUnrecPtr rootSceneObject)
{
	initialize(rootSceneObject);
}

void Behavior::depBehaviorProducedMethod(EventUnrecPtr e, UInt32 ID)
{
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

	for(UInt32 i = 0; TheBehaviorType->_bDependencies.size(); i++)
	{
		if(TheBehaviorType->_bDependencies[i]->attachedScene == dynamic_cast<SceneObject*>(_sfSceneObject.getValue())->getParentScene())
		{
			for(UInt32 c = 0; TheBehaviorType->_bEventLinks.size(); c++)
			{
				for(UInt32 d = 0; TheBehaviorType->_bDependencies[i]->_bEvents.size(); d++)
				{
					if(TheBehaviorType->_bDependencies[i]->hasEvent(TheBehaviorType->_bEventLinks[c]))
					{
						eventProducer->attachEventListener(&_DepBehaviorListener,TheBehaviorType->_bDependencies[i]->findEventID(TheBehaviorType->_bEventLinks[c]));
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Behavior::Behavior(void) :
    Inherited(),
	_DepBehaviorListener(BehaviorUnrecPtr(this)),
	initialized(false)
{
}

Behavior::Behavior(const Behavior &source) :
    Inherited(source),
	_DepBehaviorListener(BehaviorUnrecPtr(this)),
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
