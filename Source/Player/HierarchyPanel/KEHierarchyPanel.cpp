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

	_CreateNewNodeMenuButton = MenuButton::create();

	_CreateNewButtonConstraints = OSG::BorderLayoutConstraints::create();

	_CreateNewButtonConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);

    _CreateNewNodeMenuButton->setText("Create New Node");
    _CreateNewNodeMenuButton->setPreferredSize(Vec2f(120, 20));
    _CreateNewNodeMenuButton->setModel(_NewNodeMenuModel);
	_CreateNewNodeMenuButton->setConstraints(_CreateNewButtonConstraints);
    
    _NewNodeMenuButtonActionConnection = _CreateNewNodeMenuButton->connectMenuActionPerformed(boost::bind(&HierarchyPanel::handleNewNodeMenuButtonAction, this, _1));

	BorderLayoutRefPtr SceneGraphTreeLayout = OSG::BorderLayout::create();

        // Nothing

	_SceneGraphPanel = Panel::createEmpty();
	_SceneGraphPanel->pushToChildren(_TheSceneGraphTreeScrollPanel);
	_SceneGraphPanel->pushToChildren(_CreateNewNodeMenuButton);
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

	_GraphOpMenu = Menu::create();
	_LodGraphOpItem = MenuItem::create();
	_GeoMergeGraphOpItem = MenuItem::create();
	_SplitGraphOpItem = MenuItem::create();
	_PruneGraphOpItem = MenuItem::create();
	_XformPushGraphOpItem = MenuItem::create();
	_MaterialGroupGraphOpItem = MenuItem::create();
	_SharePtrGraphOpItem = MenuItem::create(); 

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
        _HierarchyPanelPopupMenu->addItem(_ImportItem);	
        _HierarchyPanelPopupMenu->addItem(_ExportItem);	
        _HierarchyPanelPopupMenu->addSeparator();
        _HierarchyPanelPopupMenu->addItem(_FocusCamera);	
	_SceneGraphPopupMenuWillBecomeVisibleConnection = _HierarchyPanelPopupMenu->connectPopupMenuWillBecomeVisible(boost::bind(&HierarchyPanel::handleSceneGraphPopupMenuWillBecomeVisible, this, _1));

	setPopupMenu(_HierarchyPanelPopupMenu);
	_GraphOpMenu->setText("Graph Ops");
	_LodGraphOpItem->setText("LOD Graph Op");
	_GeoMergeGraphOpItem->setText("Geo Merge Graph Op");
	_SplitGraphOpItem->setText("Split Graph Op");
	_PruneGraphOpItem->setText("Prune Graph Op");
	_XformPushGraphOpItem->setText("Transform Push Graph Op");
	_MaterialGroupGraphOpItem->setText("Material Group Graph Op");
	_SharePtrGraphOpItem->setText("Share Ptr Graph Op");


	_ShowHideItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_ShowRecursiveItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_DeleteItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_ImportItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_ExportItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_CutItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_CopyItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_PasteItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_PasteInstanceItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_FocusCamera->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));

	_LodGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_GeoMergeGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_SplitGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_PruneGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_XformPushGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_MaterialGroupGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));
	_SharePtrGraphOpItem->connectActionPerformed(boost::bind(&HierarchyPanel::handleBasicAction, this, _1));

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
    _HierarchyPanelPopupMenu->addItem(_ImportItem);	
    _HierarchyPanelPopupMenu->addItem(_ExportItem);	
    _HierarchyPanelPopupMenu->addSeparator();
    _HierarchyPanelPopupMenu->addItem(_FocusCamera);

	_GraphOpMenu->addItem(_LodGraphOpItem);
	_GraphOpMenu->addItem(_GeoMergeGraphOpItem);
	_GraphOpMenu->addItem(_SplitGraphOpItem);
	_GraphOpMenu->addItem(_PruneGraphOpItem);
	_GraphOpMenu->addItem(_XformPushGraphOpItem);
	_GraphOpMenu->addItem(_MaterialGroupGraphOpItem);
	_GraphOpMenu->addItem(_SharePtrGraphOpItem);

	this->setPopupMenu(_HierarchyPanelPopupMenu);

}

void HierarchyPanel::setView(UInt32 Index)
{
        _CardLayout->setCard(Index);
}

void HierarchyPanel::sgShowHideToggleSelectedNode(void)
{
	 CommandPtr ShowHideItemCommand =
         ShowHideCommand::create(_SelectedNode,
                                 (_SelectedNode->getTravMask() ==0),
                                 false);
    _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
}

void HierarchyPanel::sgImportIntoSelectedNode(void)
{
    NodeRecPtr NodeToAddTo = _ApplicationPlayer->getSelectedNode();
    if(NodeToAddTo == NULL)
    {
        NodeToAddTo =  getSceneGraphTreeModel()->getRootNode();
    }
	CommandPtr TheImportModelCommand = ImportModelCommand::create(HierarchyPanelRefPtr(this),NodeToAddTo);
    _ApplicationPlayer->getCommandManager()->executeCommand(TheImportModelCommand);
}

void HierarchyPanel::sgExportSelectedNode(void)
{
    NodeRecPtr NodeToExport = _ApplicationPlayer->getSelectedNode();
    if(NodeToExport == NULL)
    {
        NodeToExport =  getSceneGraphTreeModel()->getRootNode();
    }
	CommandPtr TheExportModelCommand = ExportModelCommand::create(NodeToExport);
    _ApplicationPlayer->getCommandManager()->executeCommand(TheExportModelCommand);
}

void HierarchyPanel::sgFocusCameraOnSelectedNode(void)
{
	//Reset the debug camera to point to the corresponding geometry
	changeDebugCameraPosition();
}

void HierarchyPanel::sgCutSelectedNode(void)
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

void HierarchyPanel::sgCopySelectedNode(void)
{
	CommandPtr CopyCommandPtr = CopyCommand::create(_ApplicationPlayer,_ApplicationPlayer->getSelectedNode());
    _ApplicationPlayer->getCommandManager()->executeCommand(CopyCommandPtr);

}

void HierarchyPanel::sgPasteOntoSelectedNode(void)
{
    CommandPtr ThePasteCommand;
    if(_ApplicationPlayer->getSelectedNode() != NULL)
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               HierarchyPanelRefPtr(this),
                                               _ApplicationPlayer->getSelectedNode(),
                                               true);
    }
    else
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               HierarchyPanelRefPtr(this),
                                               MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot(),
                                               true);
    }

    _ApplicationPlayer->getCommandManager()->executeCommand(ThePasteCommand);
}

void HierarchyPanel::sgPasteInstOntoSelectedNode(void)
{
    CommandPtr ThePasteCommand;
    if(_ApplicationPlayer->getSelectedNode() != NULL)
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               HierarchyPanelRefPtr(this),
                                               _ApplicationPlayer->getSelectedNode(),
                                               false);
    }
    else
    {
        ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                               HierarchyPanelRefPtr(this),
                                               MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot(),
                                               false);
    }

    _ApplicationPlayer->getCommandManager()->executeCommand(ThePasteCommand);
}

void HierarchyPanel::sgShowHideSelectedNodeRecursize(void)
{
	 CommandPtr ShowHideItemCommand =
         ShowHideCommand::create(_SelectedNode,
                                 true,
                                 true);
    _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
}

void HierarchyPanel::sgDeleteSelectedNode(void)
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
	CommandPtr DeleteCommandPtr = DeleteCommand::create(_ApplicationPlayer,HierarchyPanelRefPtr(this),_ApplicationPlayer->getSelectedNode());
    _ApplicationPlayer->getCommandManager()->executeCommand(DeleteCommandPtr);
    _TheSceneGraphTree->setSelectionRow(NewSelectedRow);
}

void HierarchyPanel::sgRunLODGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = LODSetupCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::sgRunGeoMergeGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = GeoMergeGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::sgRunSplitGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = SplitGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::sgRunPruneGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = PruneGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::sgRunXformPushGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = TransformPushGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::sgRunMaterialGroupGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = MaterialGroupGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}

void HierarchyPanel::sgRunSharePtrGraphOp(void)
{
	NodeUnrecPtr GraphOpNode = _ApplicationPlayer->getSelectedNode();
	if(GraphOpNode == NULL)
	{
		GraphOpNode =  getSceneGraphTreeModel()->getRootNode();
	}
	CommandPtr TheGraphOpCommand = SharePtrGraphOpCommand::create(GraphOpNode);
	_ApplicationPlayer->getCommandManager()->executeCommand(TheGraphOpCommand);
}


void HierarchyPanel::handleBasicAction(ActionEventDetails* const details)
{
	if(details->getSource() == _ShowHideItem)
	{
        sgShowHideToggleSelectedNode();
	}
    else if(details->getSource() == _ShowRecursiveItem)
	{
        sgShowHideSelectedNodeRecursize();
	}
	else if(details->getSource() == _DeleteItem)
	{
        sgDeleteSelectedNode();
	}
	else if(details->getSource() == _ImportItem)
	{
        sgImportIntoSelectedNode();
	}
	else if(details->getSource() == _ExportItem)
	{
        sgExportSelectedNode();
	}
	else if(details->getSource() == _FocusCamera)
	{
        sgFocusCameraOnSelectedNode();
	}
	else if(details->getSource() == _CutItem)
	{
        sgCutSelectedNode();
	}

	else if(details->getSource() == _CopyItem)
	{
        sgCopySelectedNode();
	}
	else if(details->getSource() == _PasteItem)
	{
        sgPasteOntoSelectedNode();
	}
	else if(details->getSource() == _PasteInstanceItem)
	{
		sgPasteInstOntoSelectedNode();
	}
	else if(details->getSource() == _LodGraphOpItem)
	{
		sgRunLODGraphOp();
	}
	else if(details->getSource() == _GeoMergeGraphOpItem)
	{
		sgRunGeoMergeGraphOp();
	}
	else if(details->getSource() == _SplitGraphOpItem)
	{
		sgRunSplitGraphOp();
	}
	else if(details->getSource() == _PruneGraphOpItem)
	{
		sgRunPruneGraphOp();
	}
	else if(details->getSource() == _XformPushGraphOpItem)
	{
		sgRunXformPushGraphOp();
	}
	else if(details->getSource() == _MaterialGroupGraphOpItem)
	{
		sgRunMaterialGroupGraphOp();
	}
	else if(details->getSource() == _SharePtrGraphOpItem)
	{
		sgRunSharePtrGraphOp();
	}
}

void HierarchyPanel::createLuaGraphTree()
{
	_TheLuaGraphTree = Tree::create();
	_TheLuaGraphTreeModel = LuaGraphTreeModel::create();
	
	_TheLuaGraphTreeModel->setRoot(MainApplication::the()->getProject()->getLuaModulePath());

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
            sgCopySelectedNode();
            break;
        case KeyEventDetails::KEY_V:
            sgPasteOntoSelectedNode();
            break;
        case KeyEventDetails::KEY_I:
            sgImportIntoSelectedNode();
            break;
        case KeyEventDetails::KEY_H:
            sgShowHideToggleSelectedNode();
            break;
        case KeyEventDetails::KEY_X:
            sgCutSelectedNode();
            break;
        }
    }
    else
    {
        switch(details->getKey())
        {
        case KeyEventDetails::KEY_BACK_SPACE:
        case KeyEventDetails::KEY_DELETE:
            sgDeleteSelectedNode();
            break;
        case KeyEventDetails::KEY_F:
            sgFocusCameraOnSelectedNode();
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
    _HighlightNode = NULL;
    _CardLayout = NULL;
    _LayoutConstraints = NULL;
    _ApplicationPlayer = NULL;
    _NewNodeMenuModel = NULL;
    _CreateNewNodeMenuButton = NULL;
    _SceneGraphPanel = NULL;
    _CreateNewButtonConstraints = NULL;
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
