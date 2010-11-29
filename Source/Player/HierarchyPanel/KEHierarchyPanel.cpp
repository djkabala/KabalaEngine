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

#include "KEHierarchyPanel.h"

#include "Player/KEApplicationPlayer.h"
#include "Player/HelperPanel/KEHelperPanel.h"
#include "Player/ContentPanel/KEContentPanel.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGNameAttachment.h> // FOR ATTACHING NAMES TO NODES ETC.

#include "Application/KEMainApplication.h"

#include <boost/filesystem/operations.hpp>
#include <OpenSG/OSGTreePath.h>
#include "boost/filesystem.hpp"

#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGTree.h>
#include <OpenSG/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/OSGBorderLayoutConstraints.h>
#include <OpenSG/OSGScrollPanel.h>
#include <OpenSG/OSGMenuButton.h>
#include <OpenSG/OSGBorderLayout.h>
#include <OpenSG/OSGCardLayout.h>

#include <OpenSG/OSGGridBagLayout.h>
#include <OpenSG/OSGGridBagLayoutConstraints.h>


#include <OpenSG/OSGTextEditor.h>

#include <OpenSG/OSGPhysics.h>

#include "Player/LuaGraphTreeModel/KELuaGraphTreeModel.h"

#include "Player/Commands/KEShowHideCommand.h"
#include "Player/Commands/KEDeleteCommand.h"
#include "Player/Commands/KECutCommand.h"
#include "Player/Commands/KECopyCommand.h"
#include "Player/Commands/KEPasteCommand.h"
#include "Player/Commands/KENewCommand.h"
#include "Player/Commands/KEImportModelCommand.h"
#include "Player/Commands/KEExportModelCommand.h"
#include "Player/Commands/GraphOps/KEGeoMergeGraphOpCommand.h"
#include "Player/Commands/GraphOps/KEMaterialGroupGraphOpCommand.h"
#include "Player/Commands/GraphOps/KEPruneGraphOpCommand.h"
#include "Player/Commands/GraphOps/KESharePtrGraphOpCommand.h"
#include "Player/Commands/GraphOps/KETransformPushGraphOpCommand.h"
#include "Player/Commands/GraphOps/KESplitGraphOpCommand.h"
#include "Player/Commands/GraphOps/KELODSetupCommand.h"
#include "Player/Commands/GraphOps/KETravMaskCommand.h"
#include "Player/Commands/GraphOps/KEAttachColGeomGraphOpCommand.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHierarchyPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGHierarchyPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HierarchyPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void HierarchyPanel::handleLoadButtonAction(ActionEventDetails* const details)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
	Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));


	std::vector<BoostPath> FilesToOpen;
	FilesToOpen = MainApplication::the()->getMainWindow()->openFileDialog("Open File Window",
												Filters,
												BoostPath(".."),
												false);

    if(FilesToOpen.size() > 0)
    {
	    _ApplicationPlayer->getTextEditor()->loadFile(FilesToOpen[0]);
    }
}

void HierarchyPanel::handleSaveButtonAction(ActionEventDetails* const details)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
	Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));

	BoostPath SavePath = MainApplication::the()->getMainWindow()->saveFileDialog("Save File Window",
														Filters,
														std::string("newFile.lua"),
														BoostPath(".."),
														true);
	if(SavePath.string() != "")
    {
	    _ApplicationPlayer->getTextEditor()->saveFile(SavePath);
    }

}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void HierarchyPanel::createSceneGraphTree(void)
{
	_TheSceneGraphTree = Tree::create();
	_TheSceneGraphTreeModel = SceneGraphTreeModel::create();

    _TheSceneGraphTree->setPreferredSize(Vec2f(100, 500));
    _TheSceneGraphTree->setModel(_TheSceneGraphTreeModel);

	
    _SceneGraphTreeKeyTypedConnection = _TheSceneGraphTree->connectKeyTyped(boost::bind(&HierarchyPanel::handleSceneGraphTreeKeyTyped, this, _1));
    _SceneGraphTreeSelectionAddedConnection = _TheSceneGraphTree->getSelectionModel()->connectSelectionAdded(boost::bind(&HierarchyPanel::handleSceneGraphTreeSelectionAdded, this, _1));
    _SceneGraphTreeSelectionRemovedConnection = _TheSceneGraphTree->getSelectionModel()->connectSelectionRemoved(boost::bind(&HierarchyPanel::handleSceneGraphTreeSelectionRemoved, this, _1));

    BorderLayoutConstraintsRefPtr SceneTreeConstraints = OSG::BorderLayoutConstraints::create();
	SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    _TheSceneGraphTreeScrollPanel = ScrollPanel::create();
    _TheSceneGraphTreeScrollPanel->setPreferredSize(Vec2f(350,300));
    _TheSceneGraphTreeScrollPanel->setConstraints(SceneTreeConstraints);
    _TheSceneGraphTreeScrollPanel->setViewComponent(_TheSceneGraphTree);

	_NewNodeMenuModel = DerivedFieldContainerComboBoxModel::create();
	_NewNodeMenuModel->editMFDerivedFieldContainerTypes()->push_back(std::string(OSG::NodeCore::getClassType().getCName()));

	BorderLayoutConstraintsRefPtr _ButtonPanelLayoutConstraints = OSG::BorderLayoutConstraints::create();
	_ButtonPanelLayoutConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);

	_ButtonPanel = Panel::create();
	
	_ButtonPanelLayout = OSG::GridBagLayout::create();

	_ButtonPanelLayout->setColumns(3);
	_ButtonPanelLayout->setRows(1);

	_ButtonPanel->setLayout(_ButtonPanelLayout);
	_ButtonPanel->setConstraints(_ButtonPanelLayoutConstraints);


	_CreateNewNodeButtonConstraints = OSG::GridBagLayoutConstraints::create();
	_SaveFileButtonConstraints = OSG::GridBagLayoutConstraints::create();
	_LoadFileButtonConstraints = OSG::GridBagLayoutConstraints::create();

	_CreateNewNodeButtonConstraints->setGridX(0);
	_CreateNewNodeButtonConstraints->setGridY(0);
	_SaveFileButtonConstraints->setGridX(1);
	_SaveFileButtonConstraints->setGridY(0);
	_LoadFileButtonConstraints->setGridX(2);
	_LoadFileButtonConstraints->setGridY(0);

	
	_CreateNewNodeMenuButton = MenuButton::create();
	
			
	_CreateNewNodeMenuButton->setText("Create New Node");
    _CreateNewNodeMenuButton->setPreferredSize(Vec2f(40, 20));
    _CreateNewNodeMenuButton->setModel(_NewNodeMenuModel);
	_CreateNewNodeMenuButton->setConstraints(_CreateNewNodeButtonConstraints);
	
    
    _NewNodeMenuButtonActionConnection = _CreateNewNodeMenuButton->connectMenuActionPerformed(boost::bind(&HierarchyPanel::handleNewNodeMenuButtonAction, this, _1));

	
	_LoadFileButton = Button::create();
	_LoadFileButton->setText("Load File");
	_LoadFileButton->setPreferredSize(Vec2f(40, 20));
	_LoadFileButton->setConstraints(_LoadFileButtonConstraints);
	_LoadFileButton->connectActionPerformed(boost::bind(&HierarchyPanel::handleLoadButtonAction,this, _1));

	
	_SaveFileButton = Button::create();
	_SaveFileButton->setText("Save File");
	_SaveFileButton->setPreferredSize(Vec2f(40, 20));
	_SaveFileButton->setConstraints(_SaveFileButtonConstraints);
	_SaveFileButton->connectActionPerformed(boost::bind(&HierarchyPanel::handleSaveButtonAction,this, _1));

	_ButtonPanel->pushToChildren(_CreateNewNodeMenuButton);
	_ButtonPanel->pushToChildren(_LoadFileButton);
	_ButtonPanel->pushToChildren(_SaveFileButton);
	_ButtonPanel->setPreferredSize(Vec2f(120,20));

	BorderLayoutRefPtr SceneGraphTreeLayout = OSG::BorderLayout::create();

        // Nothing

	_SceneGraphPanel = Panel::createEmpty();
	_SceneGraphPanel->pushToChildren(_TheSceneGraphTreeScrollPanel);
	_SceneGraphPanel->pushToChildren(_ButtonPanel);
	_SceneGraphPanel->setLayout(SceneGraphTreeLayout);
}

void HierarchyPanel::createPopUpMenu(void)
{

	_ShowHideItem = MenuItem::create();
	_ShowRecursiveItem = MenuItem::create();
	_DeleteItem = MenuItem::create();
	_ImportItem = MenuItem::create();
	_ExportItem = MenuItem::create();
	_CutItem = MenuItem::create();
	_CopyItem = MenuItem::create();
	_PasteItem = MenuItem::create();
	_PasteInstanceItem = MenuItem::create();
	_FocusCamera = MenuItem::create();
    _OpenEditor = MenuItem::create();

	_GraphOpMenu = Menu::create();
	_MaskGraphOpItem = MenuItem::create();
	_LodGraphOpItem = MenuItem::create();
	_GeoMergeGraphOpItem = MenuItem::create();
	_SplitGraphOpItem = MenuItem::create();
	_PruneGraphOpItem = MenuItem::create();
	_XformPushGraphOpItem = MenuItem::create();
	_MaterialGroupGraphOpItem = MenuItem::create();
	_SharePtrGraphOpItem = MenuItem::create(); 
	_AttachColGeomOpItem = MenuItem::create();

    //Physics Menus
    _PhysicsMenu = Menu::create();
	_PhysicsBodyItem = MenuItem::create();

    //Geoms
    _PhysicsGeomMenu = Menu::create();
	_PhysicsSphereGeomItem = MenuItem::create();
	_PhysicsBoxGeomItem = MenuItem::create();
	_PhysicsCapsuleGeomItem = MenuItem::create();
	_PhysicsPlaneGeomItem = MenuItem::create();
	_PhysicsRayGeomItem = MenuItem::create();
	_PhysicsTriMeshGeomItem = MenuItem::create();

    //Spaces
	_PhysicsSpaceItem = MenuItem::create();

    //Joints
    _PhysicsJointMenu = Menu::create();
	_PhysicsAMotorJointItem = MenuItem::create();
	_PhysicsBallJointItem = MenuItem::create();
	_PhysicsHinge2JointItem = MenuItem::create();
	_PhysicsHingeJointItem = MenuItem::create();
	_PhysicsLMotorJointItem = MenuItem::create();
	_PhysicsPistonJointItem = MenuItem::create();
	_PhysicsPlane2DJointItem = MenuItem::create();
	_PhysicsPRJointItem = MenuItem::create();
	_PhysicsPUJointItem = MenuItem::create();
	_PhysicsSliderJointItem = MenuItem::create();
	_PhysicsUniversalJointItem = MenuItem::create();

	// _HierarchyPanelPopupMenu up menu items

    _ShowHideItem->setText("Hide");
    _ShowRecursiveItem->setText("Show all below");
    _DeleteItem->setText("Delete");
    _ImportItem->setText("Import");
    _ExportItem->setText("Export");
    _CutItem->setText("Cut");
    _CopyItem->setText("Copy");
    _PasteItem->setText("Paste");
    _PasteInstanceItem->setText("Paste Instance");
    _FocusCamera->setText("Focus Camera All");
    _OpenEditor->setText("Open Editor");

    //Graph Op Menu Items Text
	_GraphOpMenu->setText("Graph Ops");
	_MaskGraphOpItem->setText("Traversal Mask Graph Op");
	_LodGraphOpItem->setText("LOD Graph Op");
	_GeoMergeGraphOpItem->setText("Geo Merge Graph Op");
	_SplitGraphOpItem->setText("Split Graph Op");
	_PruneGraphOpItem->setText("Prune Graph Op");
	_XformPushGraphOpItem->setText("Transform Push Graph Op");
	_MaterialGroupGraphOpItem->setText("Material Group Graph Op");
	_SharePtrGraphOpItem->setText("Share Ptr Graph Op");
	_AttachColGeomOpItem->setText("Attach Col Geom Graph Op");

    //Physics Menu Items Text
	_PhysicsMenu->setText("Physics");
	_PhysicsBodyItem->setText("Add Dynamics Body");
	_PhysicsGeomMenu->setText("Collision Geometry");
	_PhysicsJointMenu->setText("Joints");

    //Physics Geom Menu Items Text
	_PhysicsSphereGeomItem->setText("Sphere");
	_PhysicsBoxGeomItem->setText("Box");
	_PhysicsCapsuleGeomItem->setText("Capsule");
	_PhysicsPlaneGeomItem->setText("Plane");
	_PhysicsRayGeomItem->setText("Ray");
	_PhysicsTriMeshGeomItem->setText("Triangle Mesh");
	_PhysicsSpaceItem->setText("Space");

    //Physics Joint Menu Items Text
	_PhysicsAMotorJointItem->setText("Angular Motor");
	_PhysicsBallJointItem->setText("Ball");
	_PhysicsHinge2JointItem->setText("Two Hinges");
	_PhysicsHingeJointItem->setText("Hinge");
	_PhysicsLMotorJointItem->setText("Linear Motor");
	_PhysicsPistonJointItem->setText("Piston");
	_PhysicsPlane2DJointItem->setText("2D Plane");
	_PhysicsPRJointItem->setText("Prismatic and Rotoide");
	_PhysicsPUJointItem->setText("Prismatic and Universal ");
	_PhysicsSliderJointItem->setText("Slider");
	_PhysicsUniversalJointItem->setText("Universal");

	_ShowHideItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleShowHideToggleSelectedNode, this, _1));
	_ShowRecursiveItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleShowHideSelectedNodeRecursize, this, _1));
	_DeleteItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleDeleteSelectedNode, this, _1));
	_ImportItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleImportIntoSelectedNode, this, _1));
	_ExportItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleExportSelectedNode, this, _1));
	_CutItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleCutSelectedNode, this, _1));
	_CopyItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleCopySelectedNode, this, _1));
	_PasteItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePasteOntoSelectedNode, this, _1));
	_PasteInstanceItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePasteInstOntoSelectedNode, this, _1));
	_FocusCamera->connectActionPerformed(boost::bind(&HierarchyPanel::handleFocusCameraOnSelectedNode, this, _1));
    _OpenEditor->connectActionPerformed(boost::bind(&HierarchyPanel::handleOpenEditorMenuItem, this, _1));

    //Graph Op MenuItem Connections
	_MaskGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunTravMaskGraphOp, this, _1));
	_LodGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunLODGraphOp, this, _1));
	_GeoMergeGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunGeoMergeGraphOp, this, _1));
	_SplitGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunSplitGraphOp, this, _1));
	_PruneGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunPruneGraphOp, this, _1));
	_XformPushGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunXformPushGraphOp, this, _1));
	_MaterialGroupGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunMaterialGroupGraphOp, this, _1));
	_SharePtrGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunSharePtrGraphOp, this, _1));
	_AttachColGeomOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleRunAttachColGeomGraphOp, this, _1));

    //Physics MenuItem connections
    _PhysicsBodyItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsBodyMenuItem, this, _1));

    //Physics Geom MenuItem connections
    _PhysicsSphereGeomItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsSphereGeomMenuItem, this, _1));
    _PhysicsBoxGeomItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsBoxGeomMenuItem, this, _1));
    _PhysicsCapsuleGeomItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsCapsuleGeomMenuItem, this, _1));
    _PhysicsPlaneGeomItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsPlaneGeomMenuItem, this, _1));
    _PhysicsRayGeomItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsRayGeomMenuItem, this, _1));
    _PhysicsTriMeshGeomItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsTriMeshGeomMenuItem, this, _1));
    _PhysicsSpaceItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsSpaceMenuItem, this, _1));

    //Physics Joint MenuItem connections
    _PhysicsAMotorJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsAMotorJointMenuItem, this, _1));
    _PhysicsBallJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsBallJointMenuItem, this, _1));
    _PhysicsHinge2JointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsHinge2JointMenuItem, this, _1));
    _PhysicsHingeJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsHingeJointMenuItem, this, _1));
    _PhysicsLMotorJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsLMotorJointMenuItem, this, _1));
    _PhysicsPistonJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsPistonJointMenuItem, this, _1));
    _PhysicsPlane2DJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsPlane2DJointMenuItem, this, _1));
    _PhysicsPRJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsPRJointMenuItem, this, _1));
    _PhysicsPUJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsPUJointMenuItem, this, _1));
    _PhysicsSliderJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsSliderJointMenuItem, this, _1));
    _PhysicsUniversalJointItem->connectActionPerformed(boost::bind(&HierarchyPanel::handlePhysicsUniversalJointMenuItem, this, _1));

	_HierarchyPanelPopupMenu = PopupMenu::create();

    _HierarchyPanelPopupMenu->addItem(_ShowHideItem);
    _HierarchyPanelPopupMenu->addItem(_ShowRecursiveItem);
    _HierarchyPanelPopupMenu->addSeparator();
    _HierarchyPanelPopupMenu->addItem(_CutItem);	
    _HierarchyPanelPopupMenu->addItem(_CopyItem);	
    _HierarchyPanelPopupMenu->addItem(_PasteItem);	
    _HierarchyPanelPopupMenu->addItem(_PasteInstanceItem);	
	_HierarchyPanelPopupMenu->addItem(_DeleteItem);	
	_HierarchyPanelPopupMenu->addSeparator();
	_HierarchyPanelPopupMenu->addItem(_GraphOpMenu);
	_HierarchyPanelPopupMenu->addSeparator();
	_HierarchyPanelPopupMenu->addItem(_PhysicsMenu);	
    _HierarchyPanelPopupMenu->addSeparator();
    _HierarchyPanelPopupMenu->addItem(_ImportItem);	
    _HierarchyPanelPopupMenu->addItem(_ExportItem);	
    _HierarchyPanelPopupMenu->addSeparator();
    _HierarchyPanelPopupMenu->addItem(_FocusCamera);
    _HierarchyPanelPopupMenu->addSeparator();
    _HierarchyPanelPopupMenu->addItem(_OpenEditor);	

    //Graph Op Menu
	_GraphOpMenu->addItem(_MaskGraphOpItem);
	_GraphOpMenu->addItem(_LodGraphOpItem);
	_GraphOpMenu->addItem(_GeoMergeGraphOpItem);
	_GraphOpMenu->addItem(_SplitGraphOpItem);
	_GraphOpMenu->addItem(_PruneGraphOpItem);
	_GraphOpMenu->addItem(_XformPushGraphOpItem);
	_GraphOpMenu->addItem(_MaterialGroupGraphOpItem);
	_GraphOpMenu->addItem(_SharePtrGraphOpItem);
	_GraphOpMenu->addItem(_AttachColGeomOpItem);
    
    //Physics Menu
	_PhysicsMenu->addItem(_PhysicsBodyItem);
	_PhysicsMenu->addItem(_PhysicsGeomMenu);
	_PhysicsMenu->addItem(_PhysicsJointMenu);
    
    //Physics Geom Menu
	_PhysicsGeomMenu->addItem(_PhysicsSphereGeomItem);
	_PhysicsGeomMenu->addItem(_PhysicsBoxGeomItem);
	_PhysicsGeomMenu->addItem(_PhysicsCapsuleGeomItem);
	_PhysicsGeomMenu->addItem(_PhysicsPlaneGeomItem);
	_PhysicsGeomMenu->addItem(_PhysicsRayGeomItem);
	_PhysicsGeomMenu->addItem(_PhysicsTriMeshGeomItem);
	_PhysicsGeomMenu->addItem(_PhysicsSpaceItem);
    
    //Physics Joint Menu
	_PhysicsJointMenu->addItem(_PhysicsBallJointItem);
	_PhysicsJointMenu->addItem(_PhysicsHingeJointItem);
	_PhysicsJointMenu->addItem(_PhysicsPistonJointItem);
	_PhysicsJointMenu->addItem(_PhysicsSliderJointItem);
	_PhysicsJointMenu->addItem(_PhysicsUniversalJointItem);
	_PhysicsJointMenu->addItem(_PhysicsLMotorJointItem);
	_PhysicsJointMenu->addItem(_PhysicsAMotorJointItem);
	_PhysicsJointMenu->addItem(_PhysicsHinge2JointItem);
	_PhysicsJointMenu->addItem(_PhysicsPRJointItem);
	_PhysicsJointMenu->addItem(_PhysicsPUJointItem);
	_PhysicsJointMenu->addItem(_PhysicsPlane2DJointItem);

	_SceneGraphPopupMenuWillBecomeVisibleConnection = _HierarchyPanelPopupMenu->connectPopupMenuWillBecomeVisible(boost::bind(&HierarchyPanel::handleSceneGraphPopupMenuWillBecomeVisible, this, _1));

	setPopupMenu(_HierarchyPanelPopupMenu);

}

void HierarchyPanel::setView(UInt32 Index)
{
    _CardLayout->setCard(Index);
}

void HierarchyPanel::handleShowHideToggleSelectedNode(EventDetails* const details)
{
	 CommandPtr ShowHideItemCommand =
         ShowHideCommand::create(_SelectedNode,
                                 (_SelectedNode->getTravMask() ==0),
                                 false);
    _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
}

void HierarchyPanel::handleImportIntoSelectedNode(EventDetails* const details)
{
    NodeRecPtr NodeToAddTo = _ApplicationPlayer->getSelectedNode();
    if(NodeToAddTo == NULL)
    {
        NodeToAddTo =  getSceneGraphTreeModel()->getRootNode();
    }
	CommandPtr TheImportModelCommand = ImportModelCommand::create(this,
                                                                  NodeToAddTo,
                                                                  MainApplication::the()->getProject()->getActiveScene());
    _ApplicationPlayer->getCommandManager()->executeCommand(TheImportModelCommand);
}

void HierarchyPanel::handleExportSelectedNode(EventDetails* const details)
{
    NodeRecPtr NodeToExport = _ApplicationPlayer->getSelectedNode();
    if(NodeToExport == NULL)
    {
        NodeToExport =  getSceneGraphTreeModel()->getRootNode();
    }
	CommandPtr TheExportModelCommand = ExportModelCommand::create(NodeToExport);
    _ApplicationPlayer->getCommandManager()->executeCommand(TheExportModelCommand);
}

void HierarchyPanel::handleFocusCameraOnSelectedNode(EventDetails* const details)
{
	//Reset the debug camera to point to the corresponding geometry
	changeDebugCameraPosition();
}

void HierarchyPanel::handleCutSelectedNode(EventDetails* const details)
{
    UInt32 NewSelectedRow(0);
    if(!_TheSceneGraphTree->isSelectionEmpty())
    {
        NewSelectedRow = _TheSceneGraphTree->getMinSelectionRow();
        if(NewSelectedRow != 0)
        {
            --NewSelectedRow;
        }
        else
        {
            ++NewSelectedRow;
        }
    }
	CommandPtr CutCommandPtr =
        CutCommand::create(_ApplicationPlayer,_TheSceneGraphTreeModel,_ApplicationPlayer->getSelectedNode());
    _ApplicationPlayer->getCommandManager()->executeCommand(CutCommandPtr);
    _TheSceneGraphTree->setSelectionRow(NewSelectedRow);
}

void HierarchyPanel::handleCopySelectedNode(EventDetails* const details)
{
	CommandPtr CopyCommandPtr = CopyCommand::create(_ApplicationPlayer,_ApplicationPlayer->getSelectedNode());
    _ApplicationPlayer->getCommandManager()->executeCommand(CopyCommandPtr);

}

void HierarchyPanel::handlePasteOntoSelectedNode(EventDetails* const details)
{
    CommandPtr ThePasteCommand;
    if(_ApplicationPlayer->getSelectedNode() != NULL)
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               this,
                                               _ApplicationPlayer->getSelectedNode(),
                                               true);
    }
    else
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               this,
                                               MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot(),
                                               true);
    }

    _ApplicationPlayer->getCommandManager()->executeCommand(ThePasteCommand);
}

void HierarchyPanel::handlePasteInstOntoSelectedNode(EventDetails* const details)
{
    CommandPtr ThePasteCommand;
    if(_ApplicationPlayer->getSelectedNode() != NULL)
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               this,
                                               _ApplicationPlayer->getSelectedNode(),
                                               false);
    }
    else
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               this,
                                               MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot(),
                                               false);
    }

    _ApplicationPlayer->getCommandManager()->executeCommand(ThePasteCommand);
}

void HierarchyPanel::handleShowHideSelectedNodeRecursize(EventDetails* const details)
{
	 CommandPtr ShowHideItemCommand =
         ShowHideCommand::create(_SelectedNode,
                                 true,
                                 true);
    _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
}

void HierarchyPanel::handleDeleteSelectedNode(EventDetails* const details)
{
    UInt32 NewSelectedRow(0);
    if(!_TheSceneGraphTree->isSelectionEmpty())
    {
        NewSelectedRow = _TheSceneGraphTree->getMinSelectionRow();
        if(NewSelectedRow != 0)
        {
            --NewSelectedRow;
        }
        else
        {
            ++NewSelectedRow;
        }
    }
	CommandPtr DeleteCommandPtr = DeleteCommand::create(_ApplicationPlayer,this,_ApplicationPlayer->getSelectedNode());
    _ApplicationPlayer->getCommandManager()->executeCommand(DeleteCommandPtr);
    _TheSceneGraphTree->setSelectionRow(NewSelectedRow);
}

void HierarchyPanel::handleRunLODGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = LODSetupCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunTravMaskGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheTravMaskCommand = TravMaskCommand::create(GraphOpNode, _ApplicationPlayer->getDebuggerDrawingSurface());
	_ApplicationPlayer->getCommandManager()->executeCommand(TheTravMaskCommand);
}

void HierarchyPanel::handleRunGeoMergeGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = GeoMergeGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunSplitGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = SplitGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunPruneGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = PruneGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunXformPushGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = TransformPushGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunMaterialGroupGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = MaterialGroupGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunSharePtrGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = SharePtrGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleRunAttachColGeomGraphOp(EventDetails* const details)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = AttachColGeomGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::handleOpenEditorMenuItem(EventDetails* const details)
{
    if(_SelectedNode != NULL)
    {
        _ApplicationPlayer->openEditor(_SelectedNode);
    }
}

//Physics Menu Item Handlers
void HierarchyPanel::handlePhysicsBodyMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsSphereGeomMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsBoxGeomMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsCapsuleGeomMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsPlaneGeomMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsRayGeomMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsTriMeshGeomMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsSpaceMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsAMotorJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsBallJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsHinge2JointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsHingeJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsLMotorJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsPistonJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsPlane2DJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsPRJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsPUJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsSliderJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::handlePhysicsUniversalJointMenuItem(EventDetails* const details)
{
}

void HierarchyPanel::createLuaGraphTree()
{
	_TheLuaGraphTree = Tree::create();
	_TheLuaGraphTreeModel = LuaGraphTreeModel::create();
	
	//_TheLuaGraphTreeModel->setRoot(MainApplication::the()->getProject()->getLuaModulePath());

        _TheLuaGraphTree->setPreferredSize(Vec2f(100, 500));
        _TheLuaGraphTree->setModel(_TheLuaGraphTreeModel);

	_LuaGraphTreeSelectionAddedConnection = _TheLuaGraphTree->getSelectionModel()->connectSelectionAdded(boost::bind(&HierarchyPanel::handleLuaGraphTreeSelectionAdded, this, _1));

	BorderLayoutConstraintsRefPtr SceneTreeConstraints2 = OSG::BorderLayoutConstraints::create();
    SceneTreeConstraints2->setRegion(BorderLayoutConstraints::BORDER_WEST);

    _TheLuaGraphTreeScrollPanel = ScrollPanel::create();
        _TheLuaGraphTreeScrollPanel->setPreferredSize(Vec2f(350,300));
        _TheLuaGraphTreeScrollPanel->setConstraints(SceneTreeConstraints2);
    _TheLuaGraphTreeScrollPanel->setViewComponent(_TheLuaGraphTree);

	_LuaGraphTreeMouseClickedConnection = _TheLuaGraphTree->connectMouseClicked(boost::bind(&HierarchyPanel::handleLuaGraphTreeMouseClicked, this, _1));
}

void HierarchyPanel::createPanel()
{
	_LayoutConstraints = OSG::BorderLayoutConstraints::create();
	
        _LayoutConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);


	_CardLayout = OSG::CardLayout::create(); 

   
        this->setLayout(_CardLayout);
        this->setConstraints(_LayoutConstraints);

}


void HierarchyPanel::addTab(UInt32 tabno) // tabno defined by the enum variable
{
	_TabsAddedItr = _TabsAdded.find(tabno);
	if(_TabsAddedItr == _TabsAdded.end())
	{
		if(tabno == SCENEGRAPH_TAB)
		{
			if (_TheSceneGraphTreeScrollPanel == NULL)
			{
				createSceneGraphTree();
			}
				this->pushToChildren(_SceneGraphPanel);

			_TabsAdded.insert(SCENEGRAPH_TAB);

		}
		else if(tabno == LUA_TAB)
		{
			if (_TheLuaGraphTreeScrollPanel == NULL)
			{
				createLuaGraphTree();
			}
				this->pushToChildren(_TheLuaGraphTreeScrollPanel);

			_TabsAdded.insert(LUA_TAB);
		}
	}
}

void HierarchyPanel::removeTab(UInt32 tabno)
{

	_TabsAddedItr = _TabsAdded.find(tabno);

	if(_TabsAddedItr!= _TabsAdded.end())
	{
		switch(*_TabsAddedItr)
		{

			case SCENEGRAPH_TAB:	
				this->removeObjFromChildren(dynamic_pointer_cast<Component>(_SceneGraphPanel));
				break;
			case LUA_TAB:
				this->removeObjFromChildren(dynamic_pointer_cast<Component>(_TheLuaGraphTreeScrollPanel));
				break;
		}

	}

}

void HierarchyPanel::createDefaultHierarchyPanel() // creates the panel with the LUA_TAB and SCENEGRAPH_TAB trees
{
	createPanel();
	addTab(SCENEGRAPH_TAB);
	addTab(LUA_TAB);
	createPopUpMenu();
}

void HierarchyPanel::updatePopupMenu(void)
{
	changeShowHideMenuItem();
    //Update Show/Hide
    _ShowHideItem->setEnabled(_SelectedNode != NULL);

    //Update Show Recursive
    _ShowRecursiveItem->setEnabled(_SelectedNode != NULL);

    //Update Paste
    _PasteItem->setEnabled(_ApplicationPlayer->getClonedNodeInCopyClipboard() != NULL);

    //Update Paste Instance
    _PasteInstanceItem->setEnabled(_ApplicationPlayer->getClonedNodeInCopyClipboard() != NULL);

    //Update Copy
    _CopyItem->setEnabled(_SelectedNode != NULL);

    //Update Cut
    _CutItem->setEnabled(_SelectedNode != NULL);

    //Update Delete
    _DeleteItem->setEnabled(_SelectedNode != NULL);

    //Update Camera Focusing
    if(_SelectedNode != NULL)
    {
        _FocusCamera->setText("Focus Camera Here");
    }
    else
    {
        _FocusCamera->setText("Focus Camera All");
    }
    _GraphOpMenu->setEnabled(_SelectedNode != NULL);


    updatePhysicsMenuItems();
}

void HierarchyPanel::updatePhysicsMenuItems(void)
{
    if(_SelectedNode == NULL)
    {
        if(_PhysicsMenu->getEnabled()) { _PhysicsMenu->setEnabled(false); }
    }
    else
    {
        if(!_PhysicsMenu->getEnabled()) { _PhysicsMenu->setEnabled(true); }
        //Body
        //Determine if this node can have a Physics body attached to it
        if(_SelectedNode->getCore()->getType() == Transform::getClassType())
        {
            if(!_PhysicsBodyItem->getEnabled()) { _PhysicsBodyItem->setEnabled(true); }

            //Determine if this node already has a Physics Body attached
            PhysicsBody* Body = dynamic_cast<PhysicsBody*>(_SelectedNode->findAttachment(PhysicsBody::getClassType()));
            if(Body == NULL)
            {
                _PhysicsBodyItem->setText("Add Dynamics Body");
            }
            else
            {
                _PhysicsBodyItem->setText("Remove Dynamics Body");
            }
        }
        else
        {
            if(_PhysicsBodyItem->getEnabled()) { _PhysicsBodyItem->setEnabled(false); }
        }

        //Geoms
        if(!_PhysicsBodyItem->getEnabled()) { _PhysicsBodyItem->setEnabled(true); }

        //Determine if this node already has Physics Geoms attached
        PhysicsGeom* Geom = dynamic_cast<PhysicsGeom*>(_SelectedNode->findAttachment(PhysicsGeom::getClassType()));
        if(Geom == NULL)
        {
            _PhysicsSphereGeomItem->setText("Add Sphere");
            _PhysicsBoxGeomItem->setText("Add Box");
            _PhysicsCapsuleGeomItem->setText("Add Capsule");
            _PhysicsPlaneGeomItem->setText("Add Plane");
            _PhysicsRayGeomItem->setText("Add Ray");
            _PhysicsTriMeshGeomItem->setText("Add Triangle Mesh");
            _PhysicsSpaceItem->setText("Add Space");
            
            if(!_PhysicsSphereGeomItem->getEnabled()) { _PhysicsSphereGeomItem->setEnabled(true); }
            if(!_PhysicsBoxGeomItem->getEnabled()) { _PhysicsBoxGeomItem->setEnabled(true); }
            if(!_PhysicsCapsuleGeomItem->getEnabled()) { _PhysicsCapsuleGeomItem->setEnabled(true); }
            if(!_PhysicsPlaneGeomItem->getEnabled()) { _PhysicsPlaneGeomItem->setEnabled(true); }
            if(!_PhysicsRayGeomItem->getEnabled()) { _PhysicsRayGeomItem->setEnabled(true); }
            if(!_PhysicsTriMeshGeomItem->getEnabled()) { _PhysicsTriMeshGeomItem->setEnabled(true); }
            if(!_PhysicsSpaceItem->getEnabled()) { _PhysicsSpaceItem->setEnabled(true); }
        }
        else
        {
            _PhysicsSphereGeomItem->setText("Remove Sphere");
            _PhysicsBoxGeomItem->setText("Remove Box");
            _PhysicsCapsuleGeomItem->setText("Remove Capsule");
            _PhysicsPlaneGeomItem->setText("Remove Plane");
            _PhysicsRayGeomItem->setText("Remove Ray");
            _PhysicsTriMeshGeomItem->setText("Remove Triangle Mesh");
            _PhysicsSpaceItem->setText("Remove Space");

            if(_PhysicsSphereGeomItem->getEnabled()) { _PhysicsSphereGeomItem->setEnabled(false); }
            if(_PhysicsBoxGeomItem->getEnabled()) { _PhysicsBoxGeomItem->setEnabled(false); }
            if(_PhysicsCapsuleGeomItem->getEnabled()) { _PhysicsCapsuleGeomItem->setEnabled(false); }
            if(_PhysicsPlaneGeomItem->getEnabled()) { _PhysicsPlaneGeomItem->setEnabled(false); }
            if(_PhysicsRayGeomItem->getEnabled()) { _PhysicsRayGeomItem->setEnabled(false); }
            if(_PhysicsTriMeshGeomItem->getEnabled()) { _PhysicsTriMeshGeomItem->setEnabled(false); }
            if(_PhysicsSpaceItem->getEnabled()) { _PhysicsSpaceItem->setEnabled(false); }
            
            if(Geom->getType() == PhysicsSphereGeom::getClassType()) { _PhysicsSphereGeomItem->setEnabled(true); }
            if(Geom->getType() == PhysicsBoxGeom::getClassType()) { _PhysicsBoxGeomItem->setEnabled(true); }
            if(Geom->getType() == PhysicsCapsuleGeom::getClassType()) { _PhysicsCapsuleGeomItem->setEnabled(true); }
            if(Geom->getType() == PhysicsPlaneGeom::getClassType()) { _PhysicsPlaneGeomItem->setEnabled(true); }
            if(Geom->getType() == PhysicsRayGeom::getClassType()) { _PhysicsRayGeomItem->setEnabled(true); }
            if(Geom->getType() == PhysicsTriMeshGeom::getClassType()) { _PhysicsTriMeshGeomItem->setEnabled(true); }
            if(Geom->getType() == PhysicsSpace::getClassType()) { _PhysicsSpaceItem->setEnabled(true); }
        }

        //Joints
    }
}

void HierarchyPanel::changeShowHideMenuItem(void)
{
	if(_ApplicationPlayer!=NULL && _SelectedNode!=NULL && _ShowHideItem!=NULL)
	{
		UInt32 maskval = _SelectedNode->getTravMask();
		if(!maskval && (_ShowHideItem->getText()== "Hide"))
        {
            _ShowHideItem->setText("Show");
        }
		else if(maskval && (_ShowHideItem->getText()== "Show"))
        {
            _ShowHideItem->setText("Hide");
        }
	}
}

void HierarchyPanel::changeDebugCameraPosition(void)
{
    _ApplicationPlayer->focusSelectedNode();
}

void HierarchyPanel::setApplicationPlayer(ApplicationPlayer* const TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::selectedNodeChanged(void)
{
    //Update Details Panel
    _ApplicationPlayer->setSelectedNode(_SelectedNode);
    _ApplicationPlayer->getHelperPanel()->updateSelectedNode();
}

void HierarchyPanel::handleSceneGraphPopupMenuWillBecomeVisible(PopupMenuEventDetails* const details)
{
    updatePopupMenu();
}

void HierarchyPanel::handleLuaGraphTreeMouseClicked(MouseEventDetails* const details)
{
   if(details->getClickCount() == 2)
   {
		BoostPath path = boost::any_cast<BoostPath>(_TheLuaGraphTree->getLastSelectedPathComponent());
		
		if(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path))
		{
			std::string filename(path.string());
			_ApplicationPlayer->getContentPanel()->addTabWithText(path);
			//_ApplicationPlayer->_ContentPanel->addTabWithText(path);
		}
   }
}

void HierarchyPanel::handleNewNodeMenuButtonAction(ActionEventDetails* const details)
{
	MenuButtonRefPtr TheMenuButton(dynamic_cast<MenuButton*>(details->getSource()));
	if(TheMenuButton != NULL)
	{
		try
		{	
			NodeRefPtr SelectedNode(_ApplicationPlayer->getSelectedNode());
			if(SelectedNode == NULL)
			{
				SelectedNode = _TheSceneGraphTreeModel->getRootNode();
			}

			FieldContainerType* FCType;

			FCType = boost::any_cast<FieldContainerType*>(TheMenuButton->getSelectionValue());
			
			CommandPtr NewCommandPtr = NewCommand::create(this,FCType);
			_ApplicationPlayer->getCommandManager()->executeCommand(NewCommandPtr);
		}	
		catch(boost::bad_any_cast &ex)
		{
			SWARNING << ex.what() << std::endl;
		}
	}
	else
	{
		SWARNING << "TheMenuButton is null " << std::endl;
	}
}

void HierarchyPanel::handleLuaGraphTreeSelectionAdded(TreeSelectionEventDetails* const details)
{	
}
void HierarchyPanel::handleSceneGraphTreeSelectionAdded(TreeSelectionEventDetails* const details)
{
	//Get the selected Node
	try
	{
		_SelectedNode = boost::any_cast<NodeUnrecPtr>(_TheSceneGraphTree->getLastSelectedPathComponent());
	}
	catch (boost::bad_any_cast &ex)
	{
        SWARNING << ex.what() << std::endl;
		_SelectedNode = NULL;
	}
	selectedNodeChanged();
}

void HierarchyPanel::handleSceneGraphTreeSelectionRemoved(TreeSelectionEventDetails* const details)
{
	_SelectedNode = NULL;
	selectedNodeChanged();
}
        
void HierarchyPanel::handleSceneGraphTreeKeyTyped(KeyEventDetails* const details)
{
    if(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        switch(details->getKey())
        {
        case KeyEventDetails::KEY_C:
            handleCopySelectedNode(details);
            break;
        case KeyEventDetails::KEY_V:
            handlePasteOntoSelectedNode(details);
            break;
        case KeyEventDetails::KEY_I:
            handleImportIntoSelectedNode(details);
            break;
        case KeyEventDetails::KEY_H:
            handleShowHideToggleSelectedNode(details);
            break;
        case KeyEventDetails::KEY_X:
            handleCutSelectedNode(details);
            break;
        }
    }
    else
    {
        switch(details->getKey())
        {
        case KeyEventDetails::KEY_BACK_SPACE:
        case KeyEventDetails::KEY_DELETE:
            handleDeleteSelectedNode(details);
            break;
        case KeyEventDetails::KEY_F:
            handleFocusCameraOnSelectedNode(details);
            break;
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void HierarchyPanel::resolveLinks(void)
{
    Inherited::resolveLinks();

    _TheSceneGraphTreeModel = NULL;
    _TheLuaGraphTreeModel = NULL;
    _TheSceneGraphTree = NULL;
    _TheLuaGraphTree = NULL;
    _SelectedNode = NULL;
    _TheSceneGraphTreeScrollPanel = NULL;
    _TheLuaGraphTreeScrollPanel = NULL;
	_ButtonPanel = NULL;
    _HighlightNode = NULL;
    _CardLayout = NULL;
	_ButtonPanelLayout = NULL;
    _LayoutConstraints = NULL;
    _ApplicationPlayer = NULL;
    _NewNodeMenuModel = NULL;
    _CreateNewNodeMenuButton = NULL;
	_LoadFileButton = NULL;
	_SaveFileButton = NULL;
    _SceneGraphPanel = NULL;
    _CreateNewNodeButtonConstraints = NULL;
	_SaveFileButtonConstraints = NULL;
	_LoadFileButtonConstraints = NULL;
    _HierarchyPanelPopupMenu = NULL;
    _ShowHideItem  = NULL;
    _ShowRecursiveItem  = NULL;
    _CutItem  = NULL;
    _CopyItem  = NULL;
    _PasteItem  = NULL;
    _PasteInstanceItem  = NULL;
    _DeleteItem  = NULL;
    _ImportItem  = NULL;
    _ExportItem  = NULL;
    _FocusCamera  = NULL;

    _LuaGraphTreeSelectionAddedConnection.disconnect();
    _SceneGraphTreeSelectionAddedConnection.disconnect();
    _SceneGraphTreeSelectionRemovedConnection.disconnect();
    _SceneGraphTreeKeyTypedConnection.disconnect();
    _LuaGraphTreeMouseClickedConnection.disconnect();
    _NewNodeMenuButtonActionConnection.disconnect();
    _SceneGraphPopupMenuWillBecomeVisibleConnection.disconnect();
}
/*----------------------- constructors & destructors ----------------------*/

HierarchyPanel::HierarchyPanel(void) :
    Inherited()
{
	_ApplicationPlayer = NULL;
}

HierarchyPanel::HierarchyPanel(const HierarchyPanel &source) :
    Inherited(source)
{
}

HierarchyPanel::~HierarchyPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HierarchyPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HierarchyPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump HierarchyPanel NI" << std::endl;
}

OSG_END_NAMESPACE
