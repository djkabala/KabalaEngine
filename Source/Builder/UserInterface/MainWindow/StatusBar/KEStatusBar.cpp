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

#include "KEStatusBar.h"

#include <OpenSG/OSGButton.h>
#include <OpenSG/OSGLabel.h>
#include <OpenSG/OSGProgressBar.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStatusBarBase.cpp file.
// To modify it, please change the .fcd file (OSGStatusBar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StatusBar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void StatusBar::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _IconButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.StatusBar.IconButton", TheApplicationBuilder));
    _StatusLabel = dynamic_cast<Label*>(findContainer("KE.WorldBuilder.StatusBar.DescriptionLabel", TheApplicationBuilder));
    _ProgressBar = dynamic_cast<ProgressBar*>(findContainer("KE.WorldBuilder.StatusBar.ProgressBar", TheApplicationBuilder));
}

void StatusBar::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _IconButton = NULL;
    _StatusLabel = NULL;
    _ProgressBar = NULL;
}

void StatusBar::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    clearStatus();
}

void StatusBar::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    clearStatus();
}

void StatusBar::setProgressEnable(bool Enable)
{
    _ProgressBar->setEnabled(Enable);
}

void StatusBar::setStatusText(const std::string& Text)
{
    _StatusLabel->setText(Text);
}

void StatusBar::setStatusIcon(UInt16 IconEnum)
{
    //TODO: Implement
}

void StatusBar::setProgress(Int32 Progress)
{
    _ProgressBar->setValue(Progress);
}

void StatusBar::clearStatus(void)
{
    setProgressEnable(false);
    setStatusText("");
    setStatusIcon(STATUS_NONE);
    setProgress(0);
}

bool StatusBar::getProgressEnable(void) const
{
    return _ProgressBar->getEnabled();
}

const std::string& StatusBar::getStatusText(void) const
{
    return _StatusLabel->getText();
}

UInt16 StatusBar::getStatusIcon(void) const
{
    //TODO: Implement
    return STATUS_NONE;
}

Int32 StatusBar::getProgress(void) const
{
    return _ProgressBar->getValue();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StatusBar::StatusBar(void) :
    Inherited()
{
}

StatusBar::StatusBar(const StatusBar &source) :
    Inherited(source)
{
}

StatusBar::~StatusBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StatusBar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void StatusBar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StatusBar NI" << std::endl;
}

OSG_END_NAMESPACE
