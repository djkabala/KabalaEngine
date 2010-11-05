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

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESceneComponentTree.h"
#include <OpenSG/OSGTree.h>
#include <OpenSG/OSGMenuButton.h>
#include <OpenSG/OSGLight.h>
#include "KESceneComponentTreeComponentGenerator.h"
#include "KESceneTreeModel.h"

#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"


#include "Builder/UserInterface/Commands/KEAddForegroundToSceneCommand.h"
#include "Builder/UserInterface/Commands/KEAddLightToSceneCommand.h"
#include "Builder/UserInterface/Commands/KEAddSceneObjectToSceneCommand.h"
#include "Builder/UserInterface/Commands/KERemoveForegroundFromSceneCommand.h"
#include "Builder/UserInterface/Commands/KERemoveLightFromSceneCommand.h"
#include "Builder/UserInterface/Commands/KERemoveSceneObjectFromSceneCommand.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneComponentTreeBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneComponentTree.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneComponentTree::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SceneComponentTree::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _ComponentTree = dynamic_cast<Tree*>(findContainer("KE.WorldBuilder.SceneTreeNavigation.Tree", TheApplicationBuilder));

    _ComponentTreeModel = SceneTreeModel::create();
    SceneComponentTreeComponentGeneratorRecPtr CompModelGen;
    CompModelGen = dynamic_cast<SceneComponentTreeComponentGenerator*>(findContainer("KE.WorldBuilder.SceneTreeNavigation.TreeComponentGenerator", TheApplicationBuilder));
    CompModelGen->setSceneComponentTree(this);

    _ComponentTree->setCellGenerator(CompModelGen);
}

void SceneComponentTree::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _ComponentTree = NULL;
}

void SceneComponentTree::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TheCommandManager = TheApplicationBuilder->getCommandManager();
    _ComponentTreeModel->setRoot(TheApplicationBuilder->getSelectedScene());
    _ComponentTree->setModel(_ComponentTreeModel);
        
    _SceneSelectionConnection = TheApplicationBuilder->connectSelectionChanged(boost::bind(&SceneComponentTree::handleSelectedSceneChanged, this, _1));

    _SceneTreeKeyTypedConnection = _ComponentTree->connectKeyTyped(boost::bind(&SceneComponentTree::handleSceneTreeKeyTyped, this, _1));
    _SceneTreeSelectionAddedConnection = _ComponentTree->getSelectionModel()->connectSelectionAdded(boost::bind(&SceneComponentTree::handleSceneTreeSelectionAdded, this, _1));
    _SceneTreeSelectionRemovedConnection = _ComponentTree->getSelectionModel()->connectSelectionRemoved(boost::bind(&SceneComponentTree::handleSceneTreeSelectionRemoved, this, _1));

    TheApplicationBuilder->getMainWindow()->hideEditor();
}

void SceneComponentTree::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SceneSelectionConnection.disconnect();
    _SceneTreeKeyTypedConnection.disconnect();
    _SceneTreeSelectionAddedConnection.disconnect();
    _SceneTreeSelectionRemovedConnection.disconnect();
    _TheCommandManager = CommandManagerPtr();
}

void SceneComponentTree::selectSceneObject(SceneObject* const ObjToSelect)
{
    //Get the path to the SceneObject
    TreePath ThePath(_ComponentTreeModel->getSceneObjectPath(ObjToSelect));
    _ComponentTree->expandPath(ThePath);
    _ComponentTree->scrollPathToVisible(ThePath);
    _ComponentTree->setSelectionPath(ThePath);
}

void SceneComponentTree::selectCamera(void)
{
    //Get the path to the camera
    TreePath ThePath(_ComponentTreeModel->getCameraPath());
    _ComponentTree->expandPath(ThePath);
    _ComponentTree->scrollPathToVisible(ThePath);
    _ComponentTree->setSelectionPath(ThePath);
}

void SceneComponentTree::selectLight(Light* const LightToSelect)
{
    //Get the path to the Light
    TreePath ThePath(_ComponentTreeModel->getLightPath(LightToSelect));
    _ComponentTree->expandPath(ThePath);
    _ComponentTree->scrollPathToVisible(ThePath);
    _ComponentTree->setSelectionPath(ThePath);
}

void SceneComponentTree::clearSelection(void)
{
    _ComponentTree->clearSelection();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SceneComponentTree::handleSelectedSceneChanged(ListSelectionEventDetails* const details)
{
    _ComponentTreeModel->setRoot(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene());
}

void  SceneComponentTree::handleSceneTreeKeyTyped(KeyEventDetails* const details)
{
    //Depending on what is selected do things
}

void  SceneComponentTree::handleSceneTreeSelectionAdded(TreeSelectionEventDetails* const details)
{
    
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());

    //Get the selected value
    boost::any SelectedComp = _ComponentTree->getLastSelectedPathComponent();

    if(SelectedComp.type() == typeid(Scene* const))
    {
    }
    else if(SelectedComp.type() == typeid(Foreground* const))
    {
        AppBuilder->getMainWindow()->showForegroundEditor(boost::any_cast<Foreground* const>(SelectedComp));
    }
    else if(SelectedComp.type() == typeid(Light* const))
    {
        AppBuilder->getMainWindow()->showLightEditor(boost::any_cast<Light* const>(SelectedComp));

        NodeUnrecPtr TheLightNode = dynamic_cast<Node*>(boost::any_cast<Light* const>(SelectedComp)->getParents().front());

        NodeUnrecPtr TheBeacon(boost::any_cast<Light* const>(SelectedComp)->getBeacon());

        //Select that node in the Viewports
        AppBuilder->getMainWindow()->getSceneViewportPanel()->selectNode(TheBeacon);
    }
    else if(SelectedComp.type() == typeid(SceneObject* const))
    {
        AppBuilder->getMainWindow()->showSceneObjectEditor(boost::any_cast<SceneObject* const>(SelectedComp));

        SceneObjectUnrecPtr TheSceneObject = boost::any_cast<SceneObject* const>(SelectedComp);

        //Select that node in the Viewports
        AppBuilder->getMainWindow()->getSceneViewportPanel()->selectNode(TheSceneObject->getNode());
    }
    else if(SelectedComp.type() == typeid(UInt32))
    {
        UInt32 Value(boost::any_cast<UInt32>(SelectedComp));
        switch(Value)
        {
        case SceneTreeModel::BasicComponent:              //Basic
            AppBuilder->getMainWindow()->showBasicEditor(AppBuilder->getSelectedScene());

            break;
        case SceneTreeModel::BackgroundComponent:              //Background
            AppBuilder->getMainWindow()->showBackgroundEditor(AppBuilder->getSelectedScene()->getPrimaryViewport()->getBackground());

            break;
        case SceneTreeModel::CameraComponent:              //Camera
            {
                //Select that node in the Viewports
                CameraUnrecPtr TheCamera = AppBuilder->getSelectedScene()->getPrimaryViewport()->getCamera();

                //Select that node in the Viewports
                AppBuilder->getMainWindow()->getSceneViewportPanel()->selectNode(TheCamera->getBeacon());
                            
                AppBuilder->getMainWindow()->showCameraEditor(TheCamera);
            }
            break;
        case SceneTreeModel::ForegroundsComponent:              //Foregrounds
        case SceneTreeModel::SceneObjectsComponent:              //SceneObjects
        case SceneTreeModel::LightsComponent:              //Lights
        case SceneTreeModel::DynamicsComponent:              //Dynamics
            AppBuilder->getMainWindow()->hideEditor();
            break;
        }
    }

    //Set the correct editor

    //Select the SceneObject/Light/Camera
}

void  SceneComponentTree::handleSceneTreeSelectionRemoved(TreeSelectionEventDetails* const details)
{
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());
    AppBuilder->getMainWindow()->hideEditor();
    AppBuilder->getMainWindow()->getSceneViewportPanel()->selectNode(NULL);
}

void SceneComponentTree::handleAddForeground(ActionEventDetails* const details,
                                             MenuButton* const TheMenuButton)
{
    //Create the coresponding Foreground type
    const FieldContainerType* ForeType(boost::any_cast<FieldContainerType*>(TheMenuButton->getSelectionValue()));

    //Push a foreground of that type to the viewport of the selected scene
    CommandPtr AddForegroundToSceneItemCommand = 
        AddForegroundToSceneCommand::create(*ForeType, dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene());

    _TheCommandManager->executeCommand(AddForegroundToSceneItemCommand);

}

void SceneComponentTree::handleAddLight(ActionEventDetails* const details,
                                             MenuButton* const TheMenuButton)
{
    //Create the coresponding Light type
    const FieldContainerType* LightType(boost::any_cast<FieldContainerType*>(TheMenuButton->getSelectionValue()));

    //Push a light of that type to the viewport of the selected scene
    //Push a beacon for a light of that type to the viewport of the selected scene
    CommandPtr AddLightToSceneItemCommand = 
        AddLightToSceneCommand::create(*LightType, dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene());
    _TheCommandManager->executeCommand(AddLightToSceneItemCommand);
}

void SceneComponentTree::handleAddSceneObject(ActionEventDetails* const details)
{
    //Create a new scene object
    CommandPtr AddSceneObjectToSceneItemCommand = 
        AddSceneObjectToSceneCommand::create(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene());
    _TheCommandManager->executeCommand(AddSceneObjectToSceneItemCommand);
}

void SceneComponentTree::handleRemoveForeground(ActionEventDetails* const details,
                                                Foreground* const TheForeground)
{
    CommandPtr RemoveForegroundFromSceneItemCommand = 
        RemoveForegroundFromSceneCommand::create(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene(),
                                                 TheForeground);
    _TheCommandManager->executeCommand(RemoveForegroundFromSceneItemCommand);
}

void SceneComponentTree::handleRemoveLight(ActionEventDetails* const details,
                                           Light* const TheLight)
{
    CommandPtr RemoveLightFromSceneItemCommand = 
        RemoveLightFromSceneCommand::create(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene(),
                                                 dynamic_cast<Node*>(TheLight->getParents().front()));
    _TheCommandManager->executeCommand(RemoveLightFromSceneItemCommand);
}

void SceneComponentTree::handleRemoveSceneObject(ActionEventDetails* const details,
                                                 SceneObject* const TheSceneObject)
{
    CommandPtr RemoveSceneObjectFromSceneItemCommand = 
        RemoveSceneObjectFromSceneCommand::create(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene(),
                                                 TheSceneObject);
    _TheCommandManager->executeCommand(RemoveSceneObjectFromSceneItemCommand);
}


/*----------------------- constructors & destructors ----------------------*/

SceneComponentTree::SceneComponentTree(void) :
    Inherited()
{
}

SceneComponentTree::SceneComponentTree(const SceneComponentTree &source) :
    Inherited(source)
{
}

SceneComponentTree::~SceneComponentTree(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneComponentTree::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneComponentTree::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneComponentTree NI" << std::endl;
}

OSG_END_NAMESPACE
