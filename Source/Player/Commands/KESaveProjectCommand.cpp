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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESaveProjectCommand.h"
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGNameAttachment.h>

#include "Application/KEMainApplication.h"
#include "Project/KEProject.h"
#include "Player/KEApplicationPlayer.h"
#include <boost/filesystem/operations.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SaveProjectCommand
A SaveProjectCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType SaveProjectCommand::_Type("SaveProjectCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SaveProjectCommandPtr SaveProjectCommand::create(bool OpenSaveDialog)
{
	return RefPtr(new SaveProjectCommand(OpenSaveDialog));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SaveProjectCommand::execute(void)
{
    Project* TheProject(MainApplication::the()->getProject());
    BoostPath FileToSave(TheProject->getFilePath());

    if(_OpenSaveDialog || !boost::filesystem::exists(FileToSave))
    {
        //Have the user select the file to import
        std::vector<WindowEventProducer::FileDialogFilter> Filters;

        //Filter by xml files
        Filters.push_back(WindowEventProducer::FileDialogFilter("Project Filetype","xml"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All (*.*)","*"));

        FileToSave = MainApplication::the()->getMainWindow()->saveFileDialog("Save Project",
            Filters,
            std::string(getName(TheProject)) + std::string(".xml"),
            BoostPath(".."),
            true);
    }
    if(!FileToSave.empty())
    {
        //Exit the Debugger
        bool isInDebugger(dynamic_cast<ApplicationPlayer*>(MainApplication::the()->getPlayerMode())->isDebugging());
        if(isInDebugger)
        {
            dynamic_cast<ApplicationPlayer*>(MainApplication::the()->getPlayerMode())->enableDebug(false);
        }

        //Get the extionsion of the file
        MainApplication::the()->saveProject(FileToSave);

        //Reenter the Debugger
        if(isInDebugger)
        {
            dynamic_cast<ApplicationPlayer*>(MainApplication::the()->getPlayerMode())->enableDebug(true);
        }
    }
}

std::string SaveProjectCommand::getCommandDescription(void) const
{
	std::string Description("Save Project");
	
	return Description;
}

std::string SaveProjectCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &SaveProjectCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SaveProjectCommand::~SaveProjectCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SaveProjectCommand::operator =(const SaveProjectCommand& source)
{
}

