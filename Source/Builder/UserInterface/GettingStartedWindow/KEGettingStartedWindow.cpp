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

#include "KEGettingStartedWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGettingStartedWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGGettingStartedWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GettingStartedWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GettingStartedWindow::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

void GettingStartedWindow::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

void GettingStartedWindow::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

void GettingStartedWindow::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GettingStartedWindow::GettingStartedWindow(void) :
    Inherited()
{
}

GettingStartedWindow::GettingStartedWindow(const GettingStartedWindow &source) :
    Inherited(source)
{
}

GettingStartedWindow::~GettingStartedWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GettingStartedWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GettingStartedWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GettingStartedWindow NI" << std::endl;
}

OSG_END_NAMESPACE
