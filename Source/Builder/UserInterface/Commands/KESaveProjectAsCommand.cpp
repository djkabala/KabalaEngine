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

#include "KEConfig.h"

#include "KESaveProjectAsCommand.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <boost/filesystem/operations.hpp>

#include "Project/KEProject.h"
#include "Application/KEMainApplication.h"

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SaveProjectAsCommand
A SaveProjectAsCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType SaveProjectAsCommand::_Type("SaveProjectAsCommand", "Command");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SaveProjectAsCommandPtr SaveProjectAsCommand::create(ApplicationBuilderPtr TheApplicationBuilder)
{
	return Ptr(new SaveProjectAsCommand(TheApplicationBuilder));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SaveProjectAsCommand::execute(void)
{
	std::vector<WindowEventProducer::FileDialogFilter> KEProjectFileFilters;
	KEProjectFileFilters.push_back(WindowEventProducer::FileDialogFilter("Project File","*.xml"));
	KEProjectFileFilters.push_back(WindowEventProducer::FileDialogFilter("All Files","*.*"));


	//Project File
	Path InitialProjectFilePath(MainApplication::the()->getProject()->getFilePath());
	if(!boost::filesystem::exists(InitialProjectFilePath))
	{
		InitialProjectFilePath = Path("./KEProject.xml");
	}

	Path ProjectFilePath;
	ProjectFilePath = MainApplication::the()->getMainWindowEventProducer()->saveFileDialog("Save Project As ...",KEProjectFileFilters,InitialProjectFilePath,InitialProjectFilePath.parent_path(), true);

	MainApplication::the()->saveProject(ProjectFilePath);
}

std::string SaveProjectAsCommand::getCommandDescription(void) const
{
	return std::string("SaveProjectAs");
}

const CommandType &SaveProjectAsCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SaveProjectAsCommand::~SaveProjectAsCommand(void)
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

