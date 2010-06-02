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
       producerEffectPlayed(EffectEvent::create(EffectRefPtr(this), getTimeStamp()));
       inheritedBegin();
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
    producerEffectPaused(EffectEvent::create(EffectRefPtr(this), getTimeStamp()));
    inheritedPause();
}
void Effect::unpause()
{
    producerEffectUnpaused(EffectEvent::create(EffectRefPtr(this), getTimeStamp()));
    inheritedUnpause();
}
void Effect::end()
{
    producerEffectStopped(EffectEvent::create(EffectRefPtr(this), getTimeStamp()));
    inheritedEnd();
}

//
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Effect::producerEffectPlayed(const EffectEventUnrecPtr e)
{
    _Producer.produceEvent(EffectPlayedMethodId, e);
}

void Effect::producerEffectPaused(const EffectEventUnrecPtr e)
{
    _Producer.produceEvent(EffectPausedMethodId, e);
}

void Effect::producerEffectUnpaused(const EffectEventUnrecPtr e)
{
    _Producer.produceEvent(EffectUnpausedMethodId, e);
}

void Effect::producerEffectFinished(const EffectEventUnrecPtr e)
{
    _Producer.produceEvent(EffectFinishedMethodId, e);
}

void Effect::producerEffectStopped(const EffectEventUnrecPtr e)
{
    _Producer.produceEvent(EffectStoppedMethodId, e);
}

/*----------------------- constructors & destructors ----------------------*/

Effect::Effect(void) :
    Inherited()
{
}

Effect::Effect(const Effect &source) :
    Inherited(source)
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
