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

#include "KEOpenProjectCommand.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Application/KEMainApplication.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::OpenProjectCommand
A OpenProjectCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType OpenProjectCommand::_Type("OpenProjectCommand", "Command");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

OpenProjectCommandPtr OpenProjectCommand::create(ApplicationBuilderPtr TheApplicationBuilder)
{
	return Ptr(new OpenProjectCommand(TheApplicationBuilder));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void OpenProjectCommand::execute(void)
{
	std::vector<WindowEventProducer::FileDialogFilter> KEProjectFileFilters;
	KEProjectFileFilters.push_back(WindowEventProducer::FileDialogFilter("Project File","xml"));
	KEProjectFileFilters.push_back(WindowEventProducer::FileDialogFilter("All Files","*"));

	std::vector<Path> Paths;
	Paths = MainApplication::the()->getMainWindowEventProducer()->openFileDialog("Open Project ...",KEProjectFileFilters,Path("."), false);

	if(Paths.size() > 0)
	{
		MainApplication::the()->loadProject(Paths.front());
	}
}

std::string OpenProjectCommand::getCommandDescription(void) const
{
	return std::string("OpenProject");
}

const CommandType &OpenProjectCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

OpenProjectCommand::~OpenProjectCommand(void)
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

