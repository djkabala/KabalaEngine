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

#include "KEAnimationEffect.h"
#include "Project/SceneObject/KESceneObject.h"
#include "KEEffectEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimationEffectBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimationEffect.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimationEffect::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void AnimationEffect::initEffect()
{
}

void AnimationEffect::inheritedBegin()
{
    if(getAnimation() != NULL)
    { 
        getAnimation()->attachUpdateProducer(getParentSceneObject()->getParentScene());
        getAnimation()->start();
        _AnimationStoppedConnection = getAnimation()->connectAnimationStopped(boost::bind(&AnimationEffect::handleAnimationStopped, this, _1));
        _AnimationEndedConnection = getAnimation()->connectAnimationEnded(boost::bind(&AnimationEffect::handleAnimationEnded, this, _1));
    }
    else
    {
          SWARNING << "AnimationEffect::inheritedBegin(): Null Animation. Not set yet?";
    }
}

bool AnimationEffect::inheritedIsPlaying()
{
    return getAnimation()->isPlaying();
}

bool AnimationEffect::inheritedIsPaused()
{
    return getAnimation()->isPaused();
}

void AnimationEffect::inheritedPause()
{
    getAnimation()->pause(true);
}

void AnimationEffect::inheritedUnpause()
{
    getAnimation()->pause(false);
}

void AnimationEffect::inheritedStop()
{
    getAnimation()->stop();
}

void AnimationEffect::finished()
{
    getAnimation()->detachUpdateProducer();
    _AnimationStoppedConnection.disconnect();
    _AnimationEndedConnection.disconnect();
    Inherited::finished();
}

void AnimationEffect::resolveLinks(void)
{
    Inherited::resolveLinks();

    _AnimationStoppedConnection.disconnect();
    _AnimationEndedConnection.disconnect();
}

/*----------------------- Internal Listener methods -----------------------*/

void AnimationEffect::handleAnimationEnded(AnimationEventDetails* const details)
{
    finished();
}

void AnimationEffect::handleAnimationStopped(AnimationEventDetails* const details)
{
    finished();
}

/*----------------------- constructors & destructors ----------------------*/

AnimationEffect::AnimationEffect(void) :
    Inherited()
{
}

AnimationEffect::AnimationEffect(const AnimationEffect &source) :
    Inherited(source)
{
}

AnimationEffect::~AnimationEffect(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimationEffect::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AnimationEffect::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimationEffect NI" << std::endl;
}

OSG_END_NAMESPACE
