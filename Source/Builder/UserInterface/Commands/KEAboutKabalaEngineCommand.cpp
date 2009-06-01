/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEAboutKabalaEngineCommand.h"
#include "Builder/UserInterface/KEAboutKEWindow.h"
#include "Builder/UserInterface/KEBuilderInterface.h"
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGUIDrawUtils.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AboutKabalaEngineCommand
A AboutKabalaEngineCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType AboutKabalaEngineCommand::_Type("AboutKabalaEngineCommand", "Command");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

AboutKabalaEngineCommandPtr AboutKabalaEngineCommand::create(ApplicationBuilderPtr TheApplicationBuilder)
{
	return Ptr(new AboutKabalaEngineCommand(TheApplicationBuilder));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AboutKabalaEngineCommand::execute(void)
{
	InternalWindowPtr ParentWindow = _TheApplicationBuilder->getInterface()->getParentWindow();
	InternalWindowPtr AboutWindow = createAboutKabalaEngineWindow();

	beginEditCP(AboutWindow, InternalWindow::PositionFieldMask);
       AboutWindow->setPosition(calculateAlignment(ParentWindow->getPosition(), ParentWindow->getSize(), AboutWindow->getPreferredSize(), 0.5f,0.5f));
    endEditCP(AboutWindow, InternalWindow::PositionFieldMask);

	ParentWindow->getDrawingSurface()->openWindow(AboutWindow);
}

std::string AboutKabalaEngineCommand::getCommandDescription(void) const
{
	return std::string("AboutKabalaEngine");
}

const CommandType &AboutKabalaEngineCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AboutKabalaEngineCommand::~AboutKabalaEngineCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

