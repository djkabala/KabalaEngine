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

#include "KEAddSceneObjectToSceneCommand.h"
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGLight.h>

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

#include <OpenSG/OSGPhysicsBody.h>
#include <OpenSG/OSGPhysicsBoxGeom.h>
#include <OpenSG/OSGPhysicsSpace.h>
#include <OpenSG/OSGPhysicsWorld.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AddSceneObjectToSceneCommand
A AddSceneObjectToSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType AddSceneObjectToSceneCommand::_Type("AddSceneObjectToSceneCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

AddSceneObjectToSceneCommandPtr AddSceneObjectToSceneCommand::create(Scene* const RootScene)
{
	return Ptr(new AddSceneObjectToSceneCommand(RootScene));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AddSceneObjectToSceneCommand::execute(void)
{

    //Have the user select the file to import
    std::vector<WindowEventProducer::FileDialogFilter> Filters;
    std::list< const Char8 * > ReadableModelSuff;
    SceneFileHandler::the()->getSuffixList(ReadableModelSuff, SceneFileType::OSG_READ_SUPPORTED);
    //Determine all of the readable model filetypes
    Filters.push_back(WindowEventProducer::FileDialogFilter("All Model filetypes",""));
    std::string AllModelSuffixes;
    std::string AllModelSuffixesDesc("All Model filetypes (");
    for(std::list<const Char8*>::const_iterator SuffixItor(ReadableModelSuff.begin()) ; SuffixItor != ReadableModelSuff.end() ; ++SuffixItor)
    {
        if(!AllModelSuffixes.empty())
        {
            AllModelSuffixes += ",";
            AllModelSuffixesDesc += ", ";
        }
        AllModelSuffixes += *SuffixItor;
        AllModelSuffixesDesc = AllModelSuffixesDesc + "*." + *SuffixItor;
        Filters.push_back(WindowEventProducer::FileDialogFilter(std::string(SceneFileHandler::the()->getFileType(*SuffixItor)->getName()) +  " (*." + *SuffixItor + ")",*SuffixItor));
    }
    AllModelSuffixesDesc += ")";
    Filters[0] = WindowEventProducer::FileDialogFilter(AllModelSuffixesDesc,AllModelSuffixes);
    Filters.push_back(WindowEventProducer::FileDialogFilter("All (*.*)","*"));

	std::vector<BoostPath> FilesToOpen;
    FilesToOpen = MainApplication::the()->getMainWindow()->openFileDialog("Import a model file.",
                                                                          Filters,
                                                                          BoostPath("C:\\Users\\David\\Documents\\Work\\Study\\Models"),
                                                                          false);

	NodeRecPtr NewNode;

    if(FilesToOpen.size() > 0)
    {
        //Try loading the file using the FC file handler
        FCFileType::FCPtrStore NewContainers;
        NewContainers = FCFileHandler::the()->read(FilesToOpen[0]);

        FCFileType::FCPtrStore::iterator Itor;
        for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
        {
            //Grab the root node
            if( (*Itor)->getType() == (Node::getClassType()) && 
                (dynamic_pointer_cast<Node>(*Itor)->getParent() == NULL))
            {
                NewNode = (dynamic_pointer_cast<Node>(*Itor));
            }
        }

        if(NewNode == NULL)
        {
            //Try loading the file using the SceneFileHandler
            NewNode = SceneFileHandler::the()->read(FilesToOpen[0].string().c_str(), NULL);
        }
   }
    else
    {
        return;
    }
    FilePathAttachment::setFilePath(NewNode,FilesToOpen[0]);

    commitChanges();
    NewNode->updateVolume();
    BoxVolume TheNodeVolume;
    NewNode->getWorldVolume(TheNodeVolume);

    Pnt3f Min,Max;
    TheNodeVolume.getBounds(Min,Max);
    Vec3f Lengths(Max-Min);
    Pnt3f Center(Min.subZero() + Lengths * 0.5f);

    //create ODE data
    PhysicsBodyRecPtr boxBody = PhysicsBody::create(_RootScene->getPhysicsWorld());

    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());
    boxBody->setGravityMode(false);
    //boxBody->setMassCenterOfGravity(Center.subZero());

    PhysicsBoxGeomRecPtr boxGeom = PhysicsBoxGeom::create();
    boxGeom->setBody(boxBody);
    boxGeom->setSpace(_RootScene->getPhysicsHandler()->getSpaces(0));
    boxGeom->setLengths(Lengths);
    boxGeom->setOffsetPosition(Center.subZero());
        boxGeom->setCategoryBits(0);
        boxGeom->setCollideBits(0);

    NodeRecPtr TransformNode = makeCoredNode<Transform>();
    TransformNode->addChild(NewNode);
    TransformNode->addAttachment(boxGeom);
    TransformNode->addAttachment(boxBody);


    _CreatedSceneObject = SceneObject::create();
    _CreatedSceneObject->setNode(TransformNode);
    setName(_CreatedSceneObject, FilesToOpen[0].stem());
    _RootScene->pushToSceneObjects(_CreatedSceneObject);

    //Add the Node to the Root of the scene
    _NodeAddedTo = _RootScene->getPrimaryViewport()->getRoot();

    while(_NodeAddedTo->getNChildren() > 0 &&
          _NodeAddedTo->getChild(0)->getCore()->getType().isDerivedFrom(Light::getClassType()))
    {
        if(_NodeAddedTo->getNChildren() > 0 &&
            _NodeAddedTo->getChild(0)->getCore()->getType().isDerivedFrom(Light::getClassType()))
        {
            _NodeAddedTo = _NodeAddedTo->getChild(0);
        }
    }

    if(_NodeAddedTo != NULL)
    {
        _NodeAddedTo->addChild(_CreatedSceneObject->getNode());
    }
    else
    {
        return;
    }

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectAdded(_CreatedSceneObject);

	_HasBeenDone = true;
}

std::string AddSceneObjectToSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void AddSceneObjectToSceneCommand::redo(void)
{
    Inherited::redo();

    _RootScene->pushToSceneObjects(_CreatedSceneObject);

    //Add the Node to the Root of the scene
    _NodeAddedTo->addChild(_CreatedSceneObject->getNode());

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectAdded(_CreatedSceneObject);
}

void AddSceneObjectToSceneCommand::undo(void)
{
    Inherited::undo();

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectWillBeRemoved(_CreatedSceneObject);
    _RootScene->removeObjFromSceneObjects(_CreatedSceneObject);

    //Remove the Node from the Root of the scene
    _NodeAddedTo->subChild(_CreatedSceneObject->getNode());

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->sceneObjectRemoved(_CreatedSceneObject);
}


std::string AddSceneObjectToSceneCommand::getCommandDescription(void) const
{
	return std::string("Add Scene Object to Scene");
}

const CommandType &AddSceneObjectToSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AddSceneObjectToSceneCommand::~AddSceneObjectToSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

