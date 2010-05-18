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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEProjectEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGProjectEventBase.cpp file.
// To modify it, please change the .fcd file (OSGProjectEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProjectEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ProjectEventTransitPtr ProjectEvent::create(FieldContainerRefPtr Source,
                                            Time TimeStamp)
{
    ProjectEvent* TheEvent(ProjectEvent::createEmpty());

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);

    return ProjectEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProjectEvent::ProjectEvent(void) :
    Inherited()
{
}

ProjectEvent::ProjectEvent(const ProjectEvent &source) :
    Inherited(source)
{
}

ProjectEvent::~ProjectEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ProjectEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ProjectEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ProjectEvent NI" << std::endl;
}

OSG_END_NAMESPACE
