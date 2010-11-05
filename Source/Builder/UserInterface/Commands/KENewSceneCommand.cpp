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

#include "KENewSceneCommand.h"
#include "Project/Scene/KEScene.h"
#include "Application/KEDefaults.h"
#include <boost/lexical_cast.hpp>
#include <OpenSG/OSGNameAttachment.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NewSceneCommand
A NewSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType NewSceneCommand::_Type("NewSceneCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

NewSceneCommandPtr NewSceneCommand::create(void)
{
	return Ptr(new NewSceneCommand());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void NewSceneCommand::execute(void)
{
    //Create a default scene
    _CreatedScene = createDefaultScene();

    std::string SceneName("Untitled Scene ");
    SceneName += boost::lexical_cast<std::string>(MainApplication::the()->getProject()->getMFScenes()->size());
    setName(_CreatedScene, SceneName);

    //Add the scene to the project
    MainApplication::the()->getProject()->pushToScenes(_CreatedScene);

    commitChanges();

	_HasBeenDone = true;
}

std::string NewSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void NewSceneCommand::redo(void)
{
    Inherited::redo();

    //Add the scene to the project
    MainApplication::the()->getProject()->pushToScenes(_CreatedScene);
    commitChanges();
}

void NewSceneCommand::undo(void)
{
    Inherited::undo();

    //Remove scene from the project
    MainApplication::the()->getProject()->removeObjFromScenes(_CreatedScene);
    commitChanges();
}


std::string NewSceneCommand::getCommandDescription(void) const
{
	return std::string("Create new scene");
}

const CommandType &NewSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

NewSceneCommand::~NewSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

