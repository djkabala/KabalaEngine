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
	UInt32 GenericMethodID = rootSceneObject->getScene()->registerNewGenericMethod(TheBehaviorType->getName()+"GenericMethod");
}

void Behavior::addedToSceneObject(SceneObjectUnrecPtr rootSceneObject)
{
	setSceneObject(rootSceneObject);

	initialize(rootSceneObject);
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
	_Behavior->depBehaviorProducedMethod(e, e->getTypeId());
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
