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

#include "KELoadProjectCommand.h"
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LoadProjectCommand
A LoadProjectCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType LoadProjectCommand::_Type("LoadProjectCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

LoadProjectCommandPtr LoadProjectCommand::create(void)
{
	return RefPtr(new LoadProjectCommand());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LoadProjectCommand::execute(void)
{
    //Have the user select the file to import
    std::vector<WindowEventProducer::FileDialogFilter> Filters;

    Filters.push_back(WindowEventProducer::FileDialogFilter("Project Filetypes","xml"));
    Filters.push_back(WindowEventProducer::FileDialogFilter("All (*.*)","*"));

	std::vector<BoostPath> FilesToOpen;
    FilesToOpen = MainApplication::the()->getMainWindow()->openFileDialog("Open a Project.",
        Filters,
        BoostPath("."),
        false);

    if(FilesToOpen.size() > 0)
    {
        //Exit the Debugger
        bool isInDebugger(dynamic_cast<ApplicationPlayer*>(MainApplication::the()->getPlayerMode())->isDebugging());
        if(isInDebugger)
        {
            dynamic_cast<ApplicationPlayer*>(MainApplication::the()->getPlayerMode())->enableDebug(false);
        }

        //If started then stop the current project
        ProjectRecPtr PrevProject(MainApplication::the()->getProject());
        bool isProjectRunning(PrevProject != NULL && PrevProject->isRunning());
        if(PrevProject != NULL)
        {
            if(PrevProject->isRunning())
            {
                PrevProject->stop();
            }
        }

        //Set the current project to NULL
        MainApplication::the()->setProject(NULL);

        //ApplicationMode* InitialMode(MainApplication::the()->getCurrentMode());
        //MainApplication::the()->setCurrentMode(MainApplication::the()->getStartScreenMode());

        //Try loading the file using the XML file handler
        MainApplication::the()->loadProject(FilesToOpen[0]);

        //Get the new project
        ProjectRecPtr NewProject(MainApplication::the()->getProject());

        //Restart the project
        if(NewProject != NULL && isProjectRunning)
        {
            NewProject->start();
        }

        //if(InitialMode != MainApplication::the()->getCurrentMode())
        //{
            //MainApplication::the()->setCurrentMode(InitialMode);
        //}

        //Reenter the Debugger
        if(isInDebugger)
        {
            dynamic_cast<ApplicationPlayer*>(MainApplication::the()->getPlayerMode())->enableDebug(true);
        }
    }
}

std::string LoadProjectCommand::getCommandDescription(void) const
{
	std::string Description("Load Project");
	
	return Description;
}

std::string LoadProjectCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &LoadProjectCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LoadProjectCommand::~LoadProjectCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LoadProjectCommand::operator =(const LoadProjectCommand& source)
{
}

