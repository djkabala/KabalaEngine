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

void Effect::begin()
{
    if(!effectIsInitialized)
    {
        if(getParentSceneObject() != NULL)
        {
            effectIsInitialized = true;
            initEffect();
        }
        else
        {
            SWARNING << "Effect::begin() :The effect is not associated with a Scene Object yet.";
        }
    }

    if(isPausedFlag)
    {
        SWARNING << "Effect::begin() :The effect is paused. Use unpause() instead of begin()";
    }
    else if(effectIsInitialized)
    {
        inheritedBegin();
        produceEffectBegan();
        isPlayingFlag = true;
    }
    else
    {
        SWARNING << "Effect::begin() : The effect is not initialized yet.";
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
        produceEffectPaused();
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
        
        produceEffectUnpaused();
    }
}

void Effect::stop()
{
    isPlayingFlag = false;
    inheritedStop();
    produceEffectStopped();
}

//
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Effect::finished()
{
    isPlayingFlag = false;
    produceEffectFinished();
}

void Effect::produceEffectBegan(void)
{
    EffectEventDetailsUnrecPtr details = EffectEventDetails::create(this, getTimeStamp());

    Inherited::produceEffectBegan(details);
}

void Effect::produceEffectPaused(void)
{
    EffectEventDetailsUnrecPtr details = EffectEventDetails::create(this, getTimeStamp());

    Inherited::produceEffectPaused(details);
}

void Effect::produceEffectUnpaused(void)
{
    EffectEventDetailsUnrecPtr details = EffectEventDetails::create(this, getTimeStamp());

    Inherited::produceEffectUnpaused(details);
}

void Effect::produceEffectFinished(void)
{
    EffectEventDetailsUnrecPtr details = EffectEventDetails::create(this, getTimeStamp());

    Inherited::produceEffectFinished(details);
}

void Effect::produceEffectStopped(void)
{
    EffectEventDetailsUnrecPtr details = EffectEventDetails::create(this, getTimeStamp());

    Inherited::produceEffectStopped(details);
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
