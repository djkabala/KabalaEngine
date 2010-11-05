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

#include "KERemoveSceneObjectFromSceneCommand.h"
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGNameAttachment.h>

#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneTreeModel.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RemoveSceneObjectFromSceneCommand
A RemoveSceneObjectFromSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RemoveSceneObjectFromSceneCommand::_Type("RemoveSceneObjectFromSceneCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RemoveSceneObjectFromSceneCommandPtr RemoveSceneObjectFromSceneCommand::create(Scene* const RootScene,
                                                                               SceneObject* const RemoveSceneObject)
{
	return Ptr(new RemoveSceneObjectFromSceneCommand(RootScene, RemoveSceneObject));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RemoveSceneObjectFromSceneCommand::execute(void)
{
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectWillBeRemoved(_RemovedSceneObject);
    _RootScene->removeObjFromSceneObjects(_RemovedSceneObject);
    _PrevParentNode = _RemovedSceneObject->getNode()->getParent();
    //_RemovedSceneObject->getNode()->setTravMask(0);
    _PrevParentNode->subChild(_RemovedSceneObject->getNode());
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectRemoved(_RemovedSceneObject);

	_HasBeenDone = true;
}

std::string RemoveSceneObjectFromSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void RemoveSceneObjectFromSceneCommand::redo(void)
{
    Inherited::redo();

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectWillBeRemoved(_RemovedSceneObject);
    _RootScene->removeObjFromSceneObjects(_RemovedSceneObject);
    //_RemovedSceneObject->getNode()->setTravMask(0);
    _PrevParentNode->subChild(_RemovedSceneObject->getNode());
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectRemoved(_RemovedSceneObject);
}

void RemoveSceneObjectFromSceneCommand::undo(void)
{
    Inherited::undo();

    _RootScene->pushToSceneObjects(_RemovedSceneObject);
    //_RemovedSceneObject->getNode()->setTravMask(1);
    _PrevParentNode->addChild(_RemovedSceneObject->getNode());
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectAdded(_RemovedSceneObject);
}


std::string RemoveSceneObjectFromSceneCommand::getCommandDescription(void) const
{
	return std::string("Remove Scene Object from Scene");
}

const CommandType &RemoveSceneObjectFromSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RemoveSceneObjectFromSceneCommand::~RemoveSceneObjectFromSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

