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

#include "KEAddLightToSceneCommand.h"
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

/*! \class osg::AddLightToSceneCommand
A AddLightToSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType AddLightToSceneCommand::_Type("AddLightToSceneCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

AddLightToSceneCommandPtr AddLightToSceneCommand::create(const FieldContainerType& LightType, Scene* RootScene)
{
	return Ptr(new AddLightToSceneCommand(LightType,RootScene));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AddLightToSceneCommand::execute(void)
{

    //Make the Light Beacon node
    _CreatedLightBeaconNode = makeCoredNode<Transform>();
    setName(_CreatedLightBeaconNode, _LightType.getName() + "_Beacon_Node");

    //Make the Light node
    LightRecPtr NewLight = dynamic_pointer_cast<Light>(_LightType.createContainer());
    NewLight->setBeacon(_CreatedLightBeaconNode);
    setName(NewLight, _LightType.getName() + "_NodeCore");
    _CreatedLightNode = Node::create();
    setName(_CreatedLightNode, _LightType.getName() + "_Node");
    _CreatedLightNode->setCore(NewLight);

    //Get the Root node
    NodeRecPtr RootNode = _RootScene->getPrimaryViewport()->getRoot();

    //Move all of the child nodes on the root onto children of the light node
    while(RootNode->getNChildren() != 0)
    {
        _CreatedLightNode->addChild(RootNode->getChild(0));
    }
    _CreatedLightNode->addChild(_CreatedLightBeaconNode);

    //Add the Light node to the root
    RootNode->addChild(_CreatedLightNode);

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightAdded(dynamic_cast<Light*>(_CreatedLightNode->getCore()));

    _HasBeenDone = true;
}

std::string AddLightToSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void AddLightToSceneCommand::redo(void)
{
    Inherited::redo();


    //Get the Root node
    NodeRecPtr RootNode = _RootScene->getPrimaryViewport()->getRoot();

    //Move all of the child nodes on the root onto children of the light node
    while(RootNode->getNChildren() != 0)
    {
        _CreatedLightNode->addChild(RootNode->getChild(0));
    }
    _CreatedLightNode->addChild(_CreatedLightBeaconNode);

    //Add the Light node to the root
    RootNode->addChild(_CreatedLightNode);
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightAdded(dynamic_cast<Light*>(_CreatedLightNode->getCore()));
}

void AddLightToSceneCommand::undo(void)
{
    Inherited::undo();

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightWillBeRemoved(dynamic_cast<Light*>(_CreatedLightNode->getCore()));
    //Get the Root node
    NodeRecPtr RootNode = _RootScene->getPrimaryViewport()->getRoot();

    //Move all of the child nodes on the root onto children of the light node
    while(_CreatedLightNode->getNChildren() != 0)
    {
        RootNode->addChild(_CreatedLightNode->getChild(0));
    }

    //Add the Light node to the root
    RootNode->subChild(_CreatedLightBeaconNode);

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->lightRemoved(dynamic_cast<Light*>(_CreatedLightNode->getCore()));
}


std::string AddLightToSceneCommand::getCommandDescription(void) const
{
	return std::string("Add ") + _LightType.getName() + " to scene";
}

const CommandType &AddLightToSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AddLightToSceneCommand::~AddLightToSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

