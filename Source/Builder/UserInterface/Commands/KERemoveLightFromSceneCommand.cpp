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

#include "KERemoveLightFromSceneCommand.h"
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGLight.h>
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

/*! \class osg::RemoveLightFromSceneCommand
A RemoveLightFromSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RemoveLightFromSceneCommand::_Type("RemoveLightFromSceneCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RemoveLightFromSceneCommandPtr RemoveLightFromSceneCommand::create(Scene* const RootScene,
                                                                   Node* const  RemoveLightNode)
{
	return Ptr(new RemoveLightFromSceneCommand(RootScene, RemoveLightNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RemoveLightFromSceneCommand::execute(void)
{
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightWillBeRemoved(dynamic_cast<Light*>(_RemovedLightNode->getCore()));

    //Get Parent of the Light Node
    _LightParent = _RemovedLightNode->getParent();

    //Get the Index of the Light Node in it's Parent
    _RemoveLightNodeIndex = _LightParent->findChild(_RemovedLightNode);

    //Remove the Light Node
    _LightParent->subChild(_RemovedLightNode);

    //Get the Beacon of the Light Node
    _RemovedLightBeaconNode = dynamic_cast<Light*>(_RemovedLightNode->getCore())->getBeacon();
    
    _LightBeaconParent = _RemovedLightBeaconNode->getParent();

    _RemoveLightBeaconNodeIndex = _LightBeaconParent->findChild(_RemovedLightBeaconNode);

    //Remove the Light BeaconNode
    _LightBeaconParent->subChild(_RemovedLightBeaconNode);

    for(UInt32 i(0) ; i<_RemovedLightNode->getNChildren() ; ++i)
    {
        _FormerChildren.push_back(_RemovedLightNode->getChild(i));
    }
    while(_RemovedLightNode->getNChildren() != 0)
    {
        _LightParent->addChild(_RemovedLightNode->getChild(_RemovedLightNode->getNChildren()-1));
    }

	_HasBeenDone = true;
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightRemoved(dynamic_cast<Light*>(_RemovedLightNode->getCore()));
}

std::string RemoveLightFromSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void RemoveLightFromSceneCommand::redo(void)
{
    Inherited::redo();

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightWillBeRemoved(dynamic_cast<Light*>(_RemovedLightNode->getCore()));

    //Remove the Light Node
    _LightParent->subChild(_RemovedLightNode);
    
    //Remove the Light BeaconNode
    _LightBeaconParent->subChild(_RemovedLightBeaconNode);

    while(_RemovedLightNode->getNChildren() != 0)
    {
        _LightParent->addChild(_RemovedLightNode->getChild(_RemovedLightNode->getNChildren()-1));
    }
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightRemoved(dynamic_cast<Light*>(_RemovedLightNode->getCore()));
}

void RemoveLightFromSceneCommand::undo(void)
{
    Inherited::undo();

    //Put the Children back on the Light
    for(UInt32 i(0) ; i<_FormerChildren.size() ; ++i)
    {
        _RemovedLightNode->addChild(_FormerChildren[i]);
    }

    //Put the Light back in the correct index of it's parent
    _LightParent->insertChild(_RemoveLightNodeIndex, _RemovedLightNode);

    //Put the Light Beacon back in the correct index of it's parent
    _LightBeaconParent->insertChild(_RemoveLightBeaconNodeIndex, _RemovedLightBeaconNode);

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightAdded(dynamic_cast<Light*>(_RemovedLightNode->getCore()));
}


std::string RemoveLightFromSceneCommand::getCommandDescription(void) const
{
	return std::string("Remove ") + _RemovedLightNode->getCore()->getType().getName() + " from scene";
}

const CommandType &RemoveLightFromSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RemoveLightFromSceneCommand::~RemoveLightFromSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

