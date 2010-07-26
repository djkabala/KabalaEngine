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

#include "KESequentialEffectGroup.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSequentialEffectGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGSequentialEffectGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SequentialEffectGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SequentialEffectGroup::initEffect()
{
    theInternalEffectListener = InternalEffectListener(this);
}

void SequentialEffectGroup::inheritedBegin()
{
    Inherited::inheritedBegin();
    
    activeEffectIndex = UInt32(0);
    
    getEffectList(activeEffectIndex)->addEffectListener(&theInternalEffectListener);

    getEffectList(activeEffectIndex)->begin();//effect begin.
}

bool SequentialEffectGroup::inheritedIsPlaying()
{
    return getEffectList(activeEffectIndex)->isPlaying();
}

bool SequentialEffectGroup::inheritedIsPaused()
{
    return getEffectList(activeEffectIndex)->isPaused();
}

void SequentialEffectGroup::inheritedPause()
{
    getEffectList(activeEffectIndex)->pause();
}

void SequentialEffectGroup::inheritedUnpause()
{
    getEffectList(activeEffectIndex)->unpause();
}

void SequentialEffectGroup::inheritedStop()
{
    getEffectList(activeEffectIndex)->stop();
    getEffectList(activeEffectIndex)->removeEffectListener(&theInternalEffectListener);
    activeEffectIndex = getMFEffectList()->size();//put this at the end.
}

void SequentialEffectGroup::finished()
{
    Inherited::finished();
}

void SequentialEffectGroup::handleEffectFinished()
{
    activeEffectIndex++;
    if(activeEffectIndex < getMFEffectList()->size())
    {
        getEffectList(activeEffectIndex-1)->removeEffectListener(&theInternalEffectListener);
        getEffectList(activeEffectIndex)->addEffectListener(&theInternalEffectListener);
        getEffectList(activeEffectIndex)->begin();
    }
    else
    {
        finished();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SequentialEffectGroup::SequentialEffectGroup(void) :
    Inherited()
{
}

SequentialEffectGroup::SequentialEffectGroup(const SequentialEffectGroup &source) :
    Inherited(source)
{
}

SequentialEffectGroup::~SequentialEffectGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SequentialEffectGroup::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SequentialEffectGroup::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SequentialEffectGroup NI" << std::endl;
}

OSG_END_NAMESPACE
