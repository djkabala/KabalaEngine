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

#include "KEAnimationEffect.h"
#include "Project/Scene/KEScene.h"

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

void AnimationEffect::begin()
{
    //note, there;s 
    if(theUpdateProducer)
        theUpdateProducer = dynamic_pointer_cast<SceneObjectPtr>(_sfParentSceneObject.getValue())->getEventProducer();
    _sfTheAnimation.getValue()->attachUpdateProducer(theUpdateProducer);
    _sfTheAnimation.getValue()->start();
}

bool AnimationEffect::isPlaying()
{
    return _sfTheAnimation.getValue()->isPlaying();
}

bool AnimationEffect::isPaused()
{
    return _sfTheAnimation.getValue()->isPaused();
}

void AnimationEffect::pause()
{
    _sfTheAnimation.getValue()->pause(true);
}

void AnimationEffect::unpause()
{
    _sfTheAnimation.getValue()->pause(false);
}

void AnimationEffect::end()
{
    _sfTheAnimation.getValue()->stop();
}

/*----------------------- constructors & destructors ----------------------*/

AnimationEffect::AnimationEffect(void) :
    theUpdateProducer(NULL),
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
