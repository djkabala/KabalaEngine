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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEPhysicsImpulseEffect.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsImpulseEffectBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsImpulseEffect.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsImpulseEffect::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsImpulseEffect::initEffect()
{
}

void PhysicsImpulseEffect::inheritedBegin()
{
    Pnt3f Location;//get SO's loco
    Vec3f Impulse;
    for(UInt32 i(0) ; i<getMFPhysicsBodies()->size() ; ++i)
    {
        Vec3f Direction(getPhysicsBodies(i)->getPosition()-Location.subZero());

        Real32 Distance(Direction.length());
        Direction.normalize();

        getPhysicsBodies(i)->addForce(getPhysicsWorld()->impulseToForce(getPhysicsHandler()->getStepSize(), Direction*Impulse*(1.0f/Distance)));
        //The bodies need to be enabled because they may be auto-disabled when they
        //come to rest
        //The bodies are not re-enabled until a new collision is detected
        getPhysicsBodies(i)->setEnable(true);
    }
    
    finished();
}

bool PhysicsImpulseEffect::inheritedIsPlaying()
{
    return false;
}

bool PhysicsImpulseEffect::inheritedIsPaused()
{
    return false;
}

void PhysicsImpulseEffect::inheritedPause()
{
}

void PhysicsImpulseEffect::inheritedUnpause()
{
}

void PhysicsImpulseEffect::inheritedStop()
{
}

void PhysicsImpulseEffect::finished()
{
    Inherited::finished();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsImpulseEffect::PhysicsImpulseEffect(void) :
    Inherited()
{
}

PhysicsImpulseEffect::PhysicsImpulseEffect(const PhysicsImpulseEffect &source) :
    Inherited(source)
{
}

PhysicsImpulseEffect::~PhysicsImpulseEffect(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsImpulseEffect::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PhysicsImpulseEffect::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsImpulseEffect NI" << std::endl;
}

OSG_END_NAMESPACE
