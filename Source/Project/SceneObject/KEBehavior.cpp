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

#include "KEBehavior.h"

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
	setSceneObject(rootSceneObject);

	setInitialized(true);

	//getEventProducer(getSceneObject()->getScene())->attachEventListener(
}

void Behavior::addedToSceneObject(SceneObjectUnrecPtr rootSceneObject)
{

	initialize(rootSceneObject);

	for(UInt32 i = 0; i < rootSceneObject.getScene()->getSceneObjects().size(); i++)
	{
		for(UInt32 c = 0; c < rootSceneObject.getScene()->getSceneObjects(i)->getBehaviors().size(); i++)
		{
			checkForBehaviorDependancy(OSG::BehaviorUnrecPtr(this));
			checkForBehaviorDependant(OSG::BehaviorUnrecPtr(this));
		}
	}
}

void Behavior::checkForBehaviorDependancy(BehaviorUnrecPtr behavior)
{
	for(UInt32 i = 0; i < getDependencyTypes().size(); i++)
	{
		if(getDependencyTypes(i) == behavior.getBehaviorType())
		{
			setupDependency(behavior);
		}
	}
}

void Behavior::checkForBehaviorDependant(BehaviorUnrecPtr behavior)
{
	for(UInt32 i = 0; i < getDependantTypes().size(); i++)
	{
		if(getDependantTypes(i) == behavior.getBehaviorType())
		{
			setupDependant(behavior);
		}
	}
}

void Behavior::setupDependency(BehaviorUnrecPtr behavior)
{
}
void Behavior::setupDependant(BehaviorUnrecPtr behavior)
{
}

void Behavior::depBehaviorProducedMethod(EventUnrecPtr e, UInt32 ID)
{
}

void Behavior::DepBehaviorListener::eventProduced(const EventUnrecPtr e)
{
	_Behavior->depBehaviorProducedMethod(e, GenericEventPtr::dcast(e)->getTypeId());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Behavior::Behavior(void) :
    Inherited(),
	_DepBehaviorListener(BehaviorUnrecPtr(this))
{
}

Behavior::Behavior(const Behavior &source) :
    Inherited(source),
	_DepBehaviorListener(BehaviorUnrecPtr(this))
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
