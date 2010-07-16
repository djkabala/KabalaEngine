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
#include <OpenSG/OSGContainerUtils.h>
#include <OpenSG/OSGParticleSystem.h>
#include "KEParticleSystemEffect.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleSystemEffectBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleSystemEffect.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemEffect::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleSystemEffect::initEffect()
{
    theUpdateProducer = getEventProducer(dynamic_cast<FieldContainer *>(const_cast<Scene *>(getParentSceneObject()->getParentScene())));
    theInternalParticleSystemListener = InternalParticleSystemListener(this);
    theInternalUpdateListener = InternalUpdateListener(this);
}

void ParticleSystemEffect::inheritedBegin()
{
    ParticleSystemUnrecPtr ps = getTheSystem();
    if(ps != NULL)
    {
        ps->assignGenerators(*getMFGenerators());
        ps->attachUpdateProducer(theUpdateProducer);
        ps->addParticleSystemListener(&theInternalParticleSystemListener);
        theUpdateProducer->attachEventListener(&theInternalUpdateListener, std::string("Update"));
    }
    else
    {
        SWARNING << "ParticleSystemEffect::inheritedBegin(): Null Particle System. Not set yet?";
    }

    lifetime = Real32(0.0f);
}

bool ParticleSystemEffect::inheritedIsPlaying()
{
    return isPlayingFlag;
}

bool ParticleSystemEffect::inheritedIsPaused()
{
    return isPausedFlag;
}

void ParticleSystemEffect::inheritedPause()
{
    getTheSystem()->detachUpdateProducer();
    theUpdateProducer->detachEventListener(&theInternalUpdateListener, std::string("Update"));
}

void ParticleSystemEffect::inheritedUnpause()
{
    getTheSystem()->attachUpdateProducer(theUpdateProducer);
    theUpdateProducer->attachEventListener(&theInternalUpdateListener, std::string("Update"));
}

void ParticleSystemEffect::inheritedStop()
{
    endSystem();
}

void ParticleSystemEffect::finished()
{
    ParticleSystemUnrecPtr ps = getTheSystem();
    ps->detachUpdateProducer();
    ps->removeParticleSystemListener(&theInternalParticleSystemListener);
    theUpdateProducer->detachEventListener(&theInternalUpdateListener, std::string("Update"));
    Inherited::finished();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ParticleSystemEffect::updateLifetime(Time elps)
{
    lifetime += elps;
}

bool ParticleSystemEffect::checkTimeoutEndCondition(void)
{
    return (getLifespan() >= 0.0f && lifetime > getLifespan());
}

bool ParticleSystemEffect::checkVolumeEndCondition(void)
{
    Pnt3r min = getTheSystem()->getVolume().getMin();
    Pnt3r max = getTheSystem()->getVolume().getMax();
    Vec3r diff = max - min;
    //assert max>min warn bad
    if(getMaxVolume() >= 0.0f)
    {
        return diff.x()*diff.y()*diff.z() > getMaxVolume() || diff.x()*diff.y()*diff.z() < getMinVolume();
    }
    else
    {
        return diff.x()*diff.y()*diff.z() < getMinVolume();
    }
}

bool ParticleSystemEffect::checkParticleCountEndCondition(void)
{
    if(getMaxParticles() >= 0.0f)
    {
        return getTheSystem()->getNumParticles() > getMaxParticles() || getTheSystem()->getNumParticles() <= getMinParticles();
    }
    else
    {
        return getMaxParticles() < getMinParticles();
    }
    return false;
}

void ParticleSystemEffect::endSystem()
{
    getTheSystem()->removeParticleSystemListener(&theInternalParticleSystemListener);
    theUpdateProducer->detachEventListener(&theInternalUpdateListener, std::string("Update"));
    killSystem();

    finished();
}

void ParticleSystemEffect::killSystem()
{
    getTheSystem()->detachUpdateProducer();
    getTheSystem()->clearGenerators();
    Int64 i(static_cast<Int64>(this->getTheSystem()->getNumParticles())-1);

    for(; i>=0; --i)
    {
        getTheSystem()->killParticle(i);
    }
}

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemEffect::ParticleSystemEffect(void) :
    Inherited()
{
}

ParticleSystemEffect::ParticleSystemEffect(const ParticleSystemEffect &source) :
    Inherited(source)
{ 
}

ParticleSystemEffect::~ParticleSystemEffect(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystemEffect::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleSystemEffect::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystemEffect NI" << std::endl;
}

/*----------------------------- Internal Listener Functions ----------------------------*/

//Update Listener

ParticleSystemEffect::InternalUpdateListener::InternalUpdateListener(ParticleSystemEffect* parent)
{
    fx = parent;
}

void ParticleSystemEffect::InternalUpdateListener::eventProduced(const EventUnrecPtr EventDetails, UInt32 ProducedEventId)
{
    fx->updateLifetime(dynamic_pointer_cast<UpdateEvent>(EventDetails)->getElapsedTime());
}

//Particle System Listener

ParticleSystemEffect::InternalParticleSystemListener::InternalParticleSystemListener(ParticleSystemEffect* parent)
{
    fx = parent;
}

void ParticleSystemEffect::InternalParticleSystemListener::systemUpdated(const ParticleSystemEventUnrecPtr e)
{
    if(fx->checkTimeoutEndCondition() || fx->checkParticleCountEndCondition() || fx->checkVolumeEndCondition())
    {
        fx->endSystem();
    }
}

void ParticleSystemEffect::InternalParticleSystemListener::volumeChanged(const ParticleSystemEventUnrecPtr e)
{
}

void ParticleSystemEffect::InternalParticleSystemListener::particleKilled(const ParticleEventUnrecPtr e)
{
}

void ParticleSystemEffect::InternalParticleSystemListener::particleStolen(const ParticleEventUnrecPtr e)
{
}

void ParticleSystemEffect::InternalParticleSystemListener::particleGenerated(const ParticleEventUnrecPtr e)
{
}

OSG_END_NAMESPACE
