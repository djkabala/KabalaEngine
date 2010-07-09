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

#include "KEEffect.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGEffectBase.cpp file.
// To modify it, please change the .fcd file (OSGEffect.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Effect::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection Effect::addEffectListener(EffectListenerPtr Listener)
{
    _EffectListeners.insert(Listener);

    return EventConnection(boost::bind(&Effect::isEffectListenerAttached, this, Listener),
                           boost::bind(&Effect::removeEffectListener, this, Listener));
}

void Effect::removeEffectListener(EffectListenerPtr Listener)
{
    EffectListenerSetItor EraseIter(_EffectListeners.find(Listener));
    if(EraseIter != _EffectListeners.end())
    {
        _EffectListeners.erase(EraseIter);
    }
}

void Effect::begin()
{
    if(!effectIsInitialized)
    {
        effectIsInitialized = true;
        commitChanges();//magic?
        initEffect();
    }

    if(isPausedFlag)
    {
        SWARNING << "Effect::begin() :The effect is paused. Use unpause() instead of begin()";
    }
    else
    {
        inheritedBegin();
        producerEffectBegan(EffectEvent::create(EffectUnrecPtr(this), getTimeStamp()));
        isPlayingFlag = true;
    }
}

bool Effect::isPlaying()
{
    return inheritedIsPlaying();
}

bool Effect::isPaused()
{
    return inheritedIsPaused();
}

void Effect::pause()
{
    if(!isPlayingFlag)
    {
        SWARNING << "Effect::pause() : The effect is not playing. Can't pause something that isn't started yet.";
    }
    else
    {
        if(isPausedFlag)
        {
            SWARNING << "Effect::pause() : The effect is already paused. It will be re-paused anyway, but this shouldn't be happening.";
        }

        isPausedFlag = true;
        inheritedPause();
        producerEffectPaused(EffectEvent::create(EffectUnrecPtr(this), getTimeStamp()));
    }
}
void Effect::unpause()
{
    if(!isPausedFlag)
    {
        SWARNING << "Effect::unpause() : The effect is not paused. Can't unpause something that isn't paused.";
    }
    else
    {
        isPausedFlag = false;
        inheritedUnpause();
        
        producerEffectUnpaused(EffectEvent::create(EffectUnrecPtr(this), getTimeStamp()));
    }
}

void Effect::stop()
{
    isPlayingFlag = false;
    inheritedStop();
    producerEffectStopped(EffectEvent::create(EffectUnrecPtr(this), getTimeStamp()));
}

//
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Effect::finished()
{
    isPlayingFlag = false;
    EffectEventUnrecPtr fxe = EffectEvent::create(EffectUnrecPtr(this),getTimeStamp());
    producerEffectFinished(fxe);
}

void Effect::producerEffectBegan(const EffectEventUnrecPtr e)
{
    EffectListenerSet ListenerSet(_EffectListeners);
    for(EffectListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->effectBegan(e);
    }
    _Producer.produceEvent(EffectBeganMethodId, e);
}

void Effect::producerEffectPaused(const EffectEventUnrecPtr e)
{
    EffectListenerSet ListenerSet(_EffectListeners);
    for(EffectListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->effectPaused(e);
    }
    _Producer.produceEvent(EffectPausedMethodId, e);
}

void Effect::producerEffectUnpaused(const EffectEventUnrecPtr e)
{
    EffectListenerSet ListenerSet(_EffectListeners);
    for(EffectListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->effectUnpaused(e);
    }
    _Producer.produceEvent(EffectUnpausedMethodId, e);
}

void Effect::producerEffectFinished(const EffectEventUnrecPtr e)
{
    EffectListenerSet ListenerSet(_EffectListeners);
    for(EffectListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->effectFinished(e);
    }
    _Producer.produceEvent(EffectFinishedMethodId, e);
}

void Effect::producerEffectStopped(const EffectEventUnrecPtr e)
{
    EffectListenerSet ListenerSet(_EffectListeners);
    for(EffectListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->effectStopped(e);
    }
    _Producer.produceEvent(EffectStoppedMethodId, e);
}

/*----------------------- constructors & destructors ----------------------*/

Effect::Effect(void) :
    Inherited(),
    effectIsInitialized(false),
    isPlayingFlag(false),
    isPausedFlag(false)
{
}

Effect::Effect(const Effect &source) :
    Inherited(source),
    effectIsInitialized(false),
    isPlayingFlag(false),
    isPausedFlag(false)
{
}

Effect::~Effect(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Effect::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Effect::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Effect NI" << std::endl;
}

OSG_END_NAMESPACE
