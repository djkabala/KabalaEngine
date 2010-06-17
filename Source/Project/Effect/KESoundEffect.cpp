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

#include "KESoundEffect.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundEffectBase.cpp file.
// To modify it, please change the .fcd file (OSGSoundEffect.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundEffect::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SoundEffect::initEffect()
{
    theInternalSoundListener = InternalSoundListener(this);
}

void SoundEffect::inheritedBegin()
{
    SoundUnrecPtr sound = getSound();
    if(sound != NULL)
    {
        sound->addSoundListener(&theInternalSoundListener);
        sound->play();
    }
}

bool SoundEffect::inheritedIsPlaying()
{
    return getSound()->getNumPlayingChannels() != 0;
}

bool SoundEffect::inheritedIsPaused()
{
    return isPausedFlag;
}

void SoundEffect::inheritedPause()
{
    getSound()->setAllChannelPaused(true);
}

void SoundEffect::inheritedUnpause()
{
    getSound()->setAllChannelPaused(false);
}

void SoundEffect::inheritedStop()
{
    getSound()->stopAllChannels();
}

void SoundEffect::finished()
{
    getSound()->removeSoundListener(&theInternalSoundListener);
    Inherited::finished();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

SoundEffect::InternalSoundListener::InternalSoundListener(SoundEffect* parent)
{
    fx = parent;
}

void SoundEffect::InternalSoundListener::soundPlayed(const SoundEventUnrecPtr e)
{
}
void SoundEffect::InternalSoundListener::soundPaused(const SoundEventUnrecPtr e)
{
}
void SoundEffect::InternalSoundListener::soundUnpaused(const SoundEventUnrecPtr e)
{
}
void SoundEffect::InternalSoundListener::soundLooped(const SoundEventUnrecPtr e)
{
}
void SoundEffect::InternalSoundListener::soundEnded(const SoundEventUnrecPtr e)
{
    fx->finished();
}

void SoundEffect::InternalSoundListener::soundStopped(const SoundEventUnrecPtr e)
{
    fx->finished();
}

/*----------------------- constructors & destructors ----------------------*/

SoundEffect::SoundEffect(void) :
    Inherited()
{
}

SoundEffect::SoundEffect(const SoundEffect &source) :
    Inherited(source)
{
}

SoundEffect::~SoundEffect(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundEffect::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SoundEffect::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SoundEffect NI" << std::endl;
}

OSG_END_NAMESPACE
