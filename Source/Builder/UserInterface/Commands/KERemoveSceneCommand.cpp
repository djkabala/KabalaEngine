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

#include "KERemoveSceneCommand.h"
#include "Project/Scene/KEScene.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RemoveSceneCommand
A RemoveSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RemoveSceneCommand::_Type("RemoveSceneCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RemoveSceneCommandPtr RemoveSceneCommand::create(Scene* const SceneToRemove)
{
	return Ptr(new RemoveSceneCommand(SceneToRemove));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RemoveSceneCommand::execute(void)
{
    //Get the index of the scene
    for(UInt32 i(0) ; i<MainApplication::the()->getProject()->getMFScenes()->size() ; ++i)
    {
        if(MainApplication::the()->getProject()->getScenes(i) == _RemovedScene)
        {
            _RemovedIndex = i;
            break;
        }
    }

    MainApplication::the()->getProject()->removeObjFromScenes(_RemovedScene);
    commitChanges();

	_HasBeenDone = true;
}

std::string RemoveSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void RemoveSceneCommand::redo(void)
{
    Inherited::redo();

    //Add the scene to the project
    MainApplication::the()->getProject()->removeObjFromScenes(_RemovedScene);
    commitChanges();
}

void RemoveSceneCommand::undo(void)
{
    Inherited::undo();

    //Remove scene from the project
    MainApplication::the()->getProject()->insertIntoScenes(_RemovedIndex, _RemovedScene);
    commitChanges();
}

std::string RemoveSceneCommand::getCommandDescription(void) const
{
	return std::string("Remove scene");
}

const CommandType &RemoveSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RemoveSceneCommand::~RemoveSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

