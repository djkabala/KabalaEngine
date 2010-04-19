/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEHierarchyPanel.h"


#include "Player/KEApplicationPlayer.h"
#include "Player/HelperPanel/KEHelperPanel.h"
#include "Player/ContentPanel/KEContentPanel.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include <OpenSG/OSGTransform.h>

#include "Application/KEMainApplication.h"

#include <boost/filesystem/operations.hpp>
#include <OpenSG/UserInterface/OSGTreePath.h>
#include "boost/filesystem.hpp"

#include <OpenSG/UserInterface/OSGComboBox.h>
#include <OpenSG/UserInterface/OSGDerivedFieldContainerComboBoxModel.h>

#include "Player/Commands/KEShowHideCommand.h"
#include "Player/Commands/KEDeleteCommand.h"
#include "Player/Commands/KECutCommand.h"
#include "Player/Commands/KECopyCommand.h"
#include "Player/Commands/KEPasteCommand.h"
#include "Player/Commands/KENewCommand.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::HierarchyPanel
The HierarchyPanel. Stores the tree structure for the lua files and the scenegraph.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HierarchyPanel::initMethod (void)
{
}

void HierarchyPanel::createSceneGraphTree(void)
{
	_TheSceneGraphTree = Tree::create();
	_TheSceneGraphTreeModel = SceneGraphTreeModel::create();

	beginEditCP(_TheSceneGraphTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
        _TheSceneGraphTree->setPreferredSize(Vec2f(100, 500));
        _TheSceneGraphTree->setModel(_TheSceneGraphTreeModel);
    endEditCP(_TheSceneGraphTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);

	
    _TheSceneGraphTree->getSelectionModel()->addTreeSelectionListener(&_SceneGraphTreeSelectionListener);
	
	
    BorderLayoutConstraintsPtr SceneTreeConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);
	SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);

    _TheSceneGraphTreeScrollPanel = ScrollPanel::create();
    beginEditCP(_TheSceneGraphTreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
        _TheSceneGraphTreeScrollPanel->setPreferredSize(Vec2s(350,300));
        _TheSceneGraphTreeScrollPanel->setConstraints(SceneTreeConstraints);
    endEditCP(_TheSceneGraphTreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
    _TheSceneGraphTreeScrollPanel->setViewComponent(_TheSceneGraphTree);

	
	_SceneGraphTreeSelectionListener.setParams(_TheSceneGraphTree,_ApplicationPlayer);

	_NewNodeMenuModel = DerivedFieldContainerComboBoxModel::create();
    beginEditCP(_NewNodeMenuModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);
	_NewNodeMenuModel->getDerivedFieldContainerTypes().push_back(std::string(osg::NodeCore::getClassType().getCName()));
    endEditCP(_NewNodeMenuModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);

	_CreateNewNodeMenuButton = MenuButton::create();

	_CreateNewButtonConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(_CreateNewButtonConstraints, BorderLayoutConstraints::RegionFieldMask);
	_CreateNewButtonConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    endEditCP(_CreateNewButtonConstraints, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(_CreateNewNodeMenuButton, MenuButton::TextFieldMask | MenuButton::PreferredSizeFieldMask | MenuButton::ModelFieldMask | MenuButton::ConstraintsFieldMask);
        _CreateNewNodeMenuButton->setText("Create New Node");
        _CreateNewNodeMenuButton->setPreferredSize(Vec2f(120, 20));
        _CreateNewNodeMenuButton->setModel(_NewNodeMenuModel);
		_CreateNewNodeMenuButton->setConstraints(_CreateNewButtonConstraints);
    endEditCP(_CreateNewNodeMenuButton, MenuButton::TextFieldMask | MenuButton::PreferredSizeFieldMask | MenuButton::ModelFieldMask | MenuButton::ConstraintsFieldMask);
    
	_CreateNewNodeMenuButton->addMenuActionListener(&_TheMenuButtonActionListener);

	BorderLayoutPtr SceneGraphTreeLayout = osg::BorderLayout::create();

    beginEditCP(SceneGraphTreeLayout);
        // Nothing
    endEditCP(SceneGraphTreeLayout);

	_SceneGraphPanel = Panel::createEmpty();
	beginEditCP(_SceneGraphPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	_SceneGraphPanel->getChildren().push_back(_TheSceneGraphTreeScrollPanel);
	_SceneGraphPanel->getChildren().push_back(_CreateNewNodeMenuButton);
	_SceneGraphPanel->setLayout(SceneGraphTreeLayout);
	endEditCP(_SceneGraphPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);



/*	UInt32 NumFieldContainersFound(0);
    FieldContainerType* FoundType = NULL;
    FieldContainerEditorPtr DefaultEditor;
    for(UInt32 j(0) ; NumFieldContainersFound<FieldContainerFactory::the()->getNumTypes(); ++j)
    {
        FoundType = FieldContainerFactory::the()->findType(j);
        if(FoundType != NULL)
        {
			if(FoundType->isDerivedFrom(osg::NodeCore::getClassType())  && !FoundType->isAbstract())
            {
                //Add Editor

				std::cout<<"foundtype name:"<<FoundType->getName()<<std::endl;
				std::string ftname = (FoundType->getName()).str();
				NodeCorePtr core = FieldContainerFactory::the()->createNodeCore(ftname.c_str());
				NodePtr _Temp = Node::create();
				beginEditCP(_Temp,Node::CoreFieldMask);
				_Temp->setCore(core);	
				endEditCP(_Temp,Node::CoreFieldMask);
			
				setName(_Temp,ftname);
			
            }
            ++NumFieldContainersFound;
        }



    }

*/
//	_TheSceneGraphTree->addMouseListener(&_PlayerMouseListener2);

}
void HierarchyPanel::createPopUpMenu(void)
{

	_ShowHideItem = MenuItem::create();
	_ShowRecursiveItem = MenuItem::create();
	_DeleteItem = MenuItem::create();
	_CutItem = MenuItem::create();
	_CopyItem = MenuItem::create();
	_PasteItem = MenuItem::create();
	_PasteInstanceItem = MenuItem::create();
	_FocusCamera = MenuItem::create();

	// _HierarchyPanelPopupMenu up menu items

	beginEditCP(_ShowHideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ShowHideItem->setText("Hide");
    endEditCP(_ShowHideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_ShowRecursiveItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ShowRecursiveItem->setText("Show all below");
    endEditCP(_ShowRecursiveItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_DeleteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _DeleteItem->setText("Delete");
    endEditCP(_DeleteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_CutItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _CutItem->setText("Cut");
    endEditCP(_CutItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_CopyItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _CopyItem->setText("Copy");
    endEditCP(_CopyItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_PasteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _PasteItem->setText("Paste");
    endEditCP(_PasteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_PasteInstanceItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _PasteInstanceItem->setText("Paste Instance");
    endEditCP(_PasteInstanceItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_FocusCamera, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _FocusCamera->setText("Focus Camera All");
    endEditCP(_FocusCamera, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	_ShowHideItem->addActionListener(&_BasicListener);
	_ShowRecursiveItem->addActionListener(&_BasicListener);
	_DeleteItem->addActionListener(&_BasicListener);
	_CutItem->addActionListener(&_BasicListener);
	_CopyItem->addActionListener(&_BasicListener);
	_PasteItem->addActionListener(&_BasicListener);
	_PasteInstanceItem->addActionListener(&_BasicListener);
	_FocusCamera->addActionListener(&_BasicListener);

	_HierarchyPanelPopupMenu = PopupMenu::create();

	beginEditCP(_HierarchyPanelPopupMenu);
        _HierarchyPanelPopupMenu->addItem(_ShowHideItem);
        _HierarchyPanelPopupMenu->addItem(_ShowRecursiveItem);
        _HierarchyPanelPopupMenu->addSeparator();
        _HierarchyPanelPopupMenu->addItem(_CutItem);	
        _HierarchyPanelPopupMenu->addItem(_CopyItem);	
        _HierarchyPanelPopupMenu->addItem(_PasteItem);	
        _HierarchyPanelPopupMenu->addItem(_PasteInstanceItem);	
        _HierarchyPanelPopupMenu->addItem(_DeleteItem);	
        _HierarchyPanelPopupMenu->addSeparator();
        _HierarchyPanelPopupMenu->addItem(_FocusCamera);	
	endEditCP(_HierarchyPanelPopupMenu);
    _HierarchyPanelPopupMenu->addPopupMenuListener(&_TheSceneGraphPopupListener);

	beginEditCP(HierarchyPanelPtr(this),Panel::PopupMenuFieldMask);
	this->setPopupMenu(_HierarchyPanelPopupMenu);
	endEditCP(HierarchyPanelPtr(this),Panel::PopupMenuFieldMask);

}

void HierarchyPanel::setView(UInt32 Index)
{
    beginEditCP(_CardLayout, CardLayout::CardFieldMask);
        _CardLayout->setCard(Index);
    endEditCP(_CardLayout, CardLayout::CardFieldMask);
}

void HierarchyPanel::actionPerformed(const ActionEventPtr e)
{
	if(e->getSource() == _ShowHideItem)
	{
		 CommandPtr ShowHideItemCommand =
             ShowHideCommand::create(_SceneGraphTreeSelectionListener._SelectedNode,
                                     (_SceneGraphTreeSelectionListener._SelectedNode->getTravMask() ==0),
                                     false);
        _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
	}
    else if(e->getSource() == _ShowRecursiveItem)
	{
		 CommandPtr ShowHideItemCommand =
             ShowHideCommand::create(_SceneGraphTreeSelectionListener._SelectedNode,
                                     true,
                                     true);
        _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
	}
	else if(e->getSource() == _DeleteItem)
	{
		CommandPtr DeleteCommandPtr = DeleteCommand::create(_ApplicationPlayer,HierarchyPanelPtr(this),_ApplicationPlayer->getSelectedNode());
        _ApplicationPlayer->getCommandManager()->executeCommand(DeleteCommandPtr);
	}
	else if(e->getSource() == _FocusCamera)
	{
		//Reset the debug camera to point to the corresponding geometry
		changeDebugCameraPosition();
	}
	else if(e->getSource() == _CutItem)
	{
		CommandPtr CutCommandPtr =
            CutCommand::create(_ApplicationPlayer,_TheSceneGraphTreeModel,_ApplicationPlayer->getSelectedNode());
        _ApplicationPlayer->getCommandManager()->executeCommand(CutCommandPtr);
	}

	else if(e->getSource() == _CopyItem)
	{
	
		CommandPtr CopyCommandPtr = CopyCommand::create(_ApplicationPlayer,_ApplicationPlayer->getSelectedNode());
        _ApplicationPlayer->getCommandManager()->executeCommand(CopyCommandPtr);

	}
	else if(e->getSource() == _PasteItem)
	{
        CommandPtr ThePasteCommand;
        if(_ApplicationPlayer->getSelectedNode() != NullFC)
        {
            ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                                   HierarchyPanelPtr(this),
                                                   _ApplicationPlayer->getSelectedNode(),
                                                   true);
        }
        else
        {
            ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                                   HierarchyPanelPtr(this),
                                                   MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot(),
                                                   true);
        }

        _ApplicationPlayer->getCommandManager()->executeCommand(ThePasteCommand);
	}
	else if(e->getSource() == _PasteInstanceItem)
	{
        CommandPtr ThePasteCommand;
        if(_ApplicationPlayer->getSelectedNode() != NullFC)
        {
            ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                                   HierarchyPanelPtr(this),
                                                   _ApplicationPlayer->getSelectedNode(),
                                                   false);
        }
        else
        {
            ThePasteCommand = PasteCommand::create(_ApplicationPlayer,
                                                   HierarchyPanelPtr(this),
                                                   MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot(),
                                                   false);
        }

        _ApplicationPlayer->getCommandManager()->executeCommand(ThePasteCommand);
	}
}

void HierarchyPanel::createLuaGraphTree()
{
	_TheLuaGraphTree = Tree::create();
	_TheLuaGraphTreeModel = LuaGraphTreeModel::create();
	
	_TheLuaGraphTreeModel->setRoot(MainApplication::the()->getProject()->getLuaModulePath());

	beginEditCP(_TheLuaGraphTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
        _TheLuaGraphTree->setPreferredSize(Vec2f(100, 500));
        _TheLuaGraphTree->setModel(_TheLuaGraphTreeModel);
    endEditCP(_TheLuaGraphTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);

	_TheLuaGraphTree->getSelectionModel()->addTreeSelectionListener(&_LuaGraphTreeSelectionListener);

	BorderLayoutConstraintsPtr SceneTreeConstraints2 = osg::BorderLayoutConstraints::create();
    beginEditCP(SceneTreeConstraints2, BorderLayoutConstraints::RegionFieldMask);
        SceneTreeConstraints2->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(SceneTreeConstraints2, BorderLayoutConstraints::RegionFieldMask);

    _TheLuaGraphTreeScrollPanel = ScrollPanel::create();
    beginEditCP(_TheLuaGraphTreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
        _TheLuaGraphTreeScrollPanel->setPreferredSize(Vec2s(350,300));
        _TheLuaGraphTreeScrollPanel->setConstraints(SceneTreeConstraints2);
    endEditCP(_TheLuaGraphTreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
    _TheLuaGraphTreeScrollPanel->setViewComponent(_TheLuaGraphTree);

	
	_LuaGraphTreeSelectionListener.setParams(_TheLuaGraphTree,_ApplicationPlayer);

	//_PlayerMouseListener2.setParams(_ApplicationPlayer);

	_TheLuaGraphTree->addMouseListener(&_PlayerMouseListener2);
}

void HierarchyPanel::createPanel()
{
	_LayoutConstraints = osg::BorderLayoutConstraints::create();
	
	beginEditCP(_LayoutConstraints, BorderLayoutConstraints::RegionFieldMask);
        _LayoutConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(_LayoutConstraints, BorderLayoutConstraints::RegionFieldMask);


	_CardLayout = osg::CardLayout::create(); 

   
	beginEditCP(HierarchyPanelPtr(this), Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
        this->setLayout(_CardLayout);
        this->setConstraints(_LayoutConstraints);
    endEditCP(HierarchyPanelPtr(this), Panel::LayoutFieldMask | Panel::ChildrenFieldMask);

}


void HierarchyPanel::addTab(UInt32 tabno) // tabno defined by the enum variable
{
	_TabsAddedItr = _TabsAdded.find(tabno);
	if(_TabsAddedItr == _TabsAdded.end())
	{
		if(tabno == SCENEGRAPH)
		{
			if (_TheSceneGraphTreeScrollPanel == NullFC)
			{
				createSceneGraphTree();
			}
			beginEditCP(HierarchyPanelPtr(this),Panel::ChildrenFieldMask);
				this->getChildren().push_back(_SceneGraphPanel);
			endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

			_TabsAdded.insert(SCENEGRAPH);

		}
		else if(tabno == LUA)
		{
			if (_TheLuaGraphTreeScrollPanel == NullFC)
			{
				createLuaGraphTree();
			}
			beginEditCP(HierarchyPanelPtr(this),  Panel::ChildrenFieldMask);
				this->getChildren().push_back(_TheLuaGraphTreeScrollPanel);
			endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

			_TabsAdded.insert(LUA);
		}
	}
}

void HierarchyPanel::removeTab(UInt32 tabno)
{

	beginEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);
	_TabsAddedItr = _TabsAdded.find(tabno);

	if(_TabsAddedItr!= _TabsAdded.end())
	{
		switch(*_TabsAddedItr)
		{

			case SCENEGRAPH:	
				this->getChildren().erase(this->getChildren().find(ComponentPtr::dcast(_SceneGraphPanel)));
				break;
			case LUA:
				this->getChildren().erase(this->getChildren().find(ComponentPtr::dcast(_TheLuaGraphTreeScrollPanel)));
				break;
		}

	}
	else
	{
		std::cout<<"no such tab exists\n";
	}
	endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

}

void HierarchyPanel::createDefaultHierarchyPanel() // creates the panel with the LUA and SCENEGRAPH trees
{
	createPanel();
	addTab(SCENEGRAPH);
	addTab(LUA);
	createPopUpMenu();
}

void HierarchyPanel::updatePopupMenu(void)
{
	changeShowHideMenuItem();
    //Update Show/Hide
	beginEditCP(_ShowHideItem, MenuItem::EnabledFieldMask);
		_ShowHideItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_ShowHideItem, MenuItem::EnabledFieldMask);

    //Update Show Recursive
	beginEditCP(_ShowRecursiveItem, MenuItem::EnabledFieldMask);
		_ShowRecursiveItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_ShowRecursiveItem, MenuItem::EnabledFieldMask);

	//Update Paste
	beginEditCP(_PasteItem, MenuItem::EnabledFieldMask);
		_PasteItem->setEnabled(_ApplicationPlayer->getClonedNodeInCopyClipboard() != NullFC);
    endEditCP(_PasteItem, MenuItem::EnabledFieldMask);

	//Update Paste Instance
	beginEditCP(_PasteInstanceItem, MenuItem::EnabledFieldMask);
		_PasteInstanceItem->setEnabled(_ApplicationPlayer->getClonedNodeInCopyClipboard() != NullFC);
    endEditCP(_PasteInstanceItem, MenuItem::EnabledFieldMask);

	//Update Copy
	beginEditCP(_CopyItem, MenuItem::EnabledFieldMask);
		_CopyItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_CopyItem, MenuItem::EnabledFieldMask);

	//Update Cut
	beginEditCP(_CutItem, MenuItem::EnabledFieldMask);
		_CutItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_CutItem, MenuItem::EnabledFieldMask);

	//Update Delete
	beginEditCP(_DeleteItem, MenuItem::EnabledFieldMask);
		_DeleteItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_DeleteItem, MenuItem::EnabledFieldMask);

    //Update Camera Focusing
	beginEditCP(_FocusCamera, MenuItem::TextFieldMask);
        if(_SceneGraphTreeSelectionListener._SelectedNode != NullFC)
        {
            _FocusCamera->setText("Focus Camera Here");
        }
        else
        {
            _FocusCamera->setText("Focus Camera All");
        }
    endEditCP(_FocusCamera, MenuItem::TextFieldMask);

}

void HierarchyPanel::changeShowHideMenuItem(void)
{
	if(_ApplicationPlayer!=NullFC && _SceneGraphTreeSelectionListener._SelectedNode!=NullFC && _ShowHideItem!=NullFC)
	{
		UInt32 maskval = _SceneGraphTreeSelectionListener._SelectedNode->getTravMask();
		if(!maskval && (_ShowHideItem->getText()== "Hide"))
        {
            beginEditCP(_ShowHideItem,MenuItem::TextFieldMask);
                _ShowHideItem->setText("Show");
            endEditCP(_ShowHideItem,MenuItem::TextFieldMask);
        }
		else if(maskval && (_ShowHideItem->getText()== "Show"))
        {
            beginEditCP(_ShowHideItem,MenuItem::TextFieldMask);
                _ShowHideItem->setText("Hide");
            endEditCP(_ShowHideItem,MenuItem::TextFieldMask);
        }
	}
}

HierarchyPanel::LuaGraphTreeSelectionListener::LuaGraphTreeSelectionListener(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
	_ApplicationPlayer = NullFC;
	_TheTree=NullFC;
}

HierarchyPanel::SceneGraphTreeSelectionListener::SceneGraphTreeSelectionListener(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
	_ApplicationPlayer = NullFC;
	_TheTree=NullFC;
}

void HierarchyPanel::SceneGraphTreeSelectionListener::setParams(TreePtr TheTree,ApplicationPlayerPtr TheApplicationPlayer)//,NodePtr  _SelectedNode)
{
	_TheTree=TheTree;
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::LuaGraphTreeSelectionListener::setParams(TreePtr TheTree,ApplicationPlayerPtr TheApplicationPlayer)//,NodePtr  _SelectedNode)
{
	_TheTree=TheTree;
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::changeDebugCameraPosition(void)
{
	showAll(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getCamera(),
            _ApplicationPlayer->getSelectedNode(),
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0));
}

void HierarchyPanel::showAll(CameraPtr TheCameraOrig,
                             NodePtr Scene,
                             ViewportPtr LocalViewport)
{
    NodePtr FocusNode(Scene);
	if(FocusNode==NullFC)
	{
        FocusNode = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot();
    }

	if(TheCameraOrig!=NullFC)
	{
        PerspectiveCameraPtr TheCamera;
        if(TheCameraOrig->getType() == PerspectiveCamera::getClassType())
        {
            TheCamera = PerspectiveCamera::Ptr::dcast(TheCameraOrig);
        }

        //Make sure the volume is up to date for the FocusNode
        FocusNode->updateVolume();

        //Get the Minimum and Maximum bounds of the volume
        Vec3f min,max;
        DynamicVolume TheVol;
        FocusNode->getWorldVolume(TheVol);
        TheVol.getBounds( min, max );

        Vec3f d = max - min;
        if(d.length() < Eps) //The volume is 0
        {
            Pnt3f NodeOrigin(0.0f,0.0f,0.0f);
            FocusNode->getToWorld().mult(NodeOrigin);
            //Default to a 1x1x1 box volume
            min = NodeOrigin - Vec3f(1.0f,1.0f,1.0f);
            max = NodeOrigin + Vec3f(1.0f,1.0f,1.0f);
            d = max - min;
        }

        // try to be nice to people giving degrees...
        Real32 VertFov(TheCamera->getFov());
        if(VertFov > Pi)
        {
            VertFov = osgdegree2rad(VertFov);
        }

        //Get the horizontal feild of view
        Real32 HorFov = 2.0f * osgatan(static_cast<Real32>(LocalViewport->getPixelWidth())
                                       /(static_cast<Real32>(LocalViewport->getPixelHeight())/osgtan(VertFov*0.5f)));

        Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);

        //Get the camera world transformation
        Matrix CameraToWorld(TheCamera->getBeacon()->getToWorld());
        Matrix WorldToCamera(CameraToWorld);
        WorldToCamera.invert();

        //Get the 8 points of the bounding box in camera space
        Pnt3f p1(min),
              p2(max.x(), min.y(), min.z()),
              p3(max.x(), max.y(), min.z()),
              p4(max.x(), min.y(), max.z()),
              p5(min.x(), max.y(), min.z()),
              p6(min.x(), max.y(), max.z()),
              p7(min.x(), min.y(), max.z()),
              p8(max);

        p1 = WorldToCamera * p1;
        p2 = WorldToCamera * p2;
        p3 = WorldToCamera * p3;
        p4 = WorldToCamera * p4;
        p5 = WorldToCamera * p5;
        p6 = WorldToCamera * p6;
        p7 = WorldToCamera * p7;
        p8 = WorldToCamera * p8;

        //Get the min and max of the bounding volume relative camera space
        Vec3f BBMinCamera;
        Vec3f BBMaxCamera;
        BBMinCamera[0] = osgMin(p1.x(),
                         osgMin(p2.x(),
                         osgMin(p3.x(),
                         osgMin(p4.x(),
                         osgMin(p5.x(),
                         osgMin(p6.x(),
                         osgMin(p7.x(),p8.x())))))));

        BBMinCamera[1] = osgMin(p1.y(),
                         osgMin(p2.y(),
                         osgMin(p3.y(),
                         osgMin(p4.y(),
                         osgMin(p5.y(),
                         osgMin(p6.y(),
                         osgMin(p7.y(),p8.y())))))));

        BBMinCamera[2] = osgMin(p1.z(),
                         osgMin(p2.z(),
                         osgMin(p3.z(),
                         osgMin(p4.z(),
                         osgMin(p5.z(),
                         osgMin(p6.z(),
                         osgMin(p7.z(),p8.z())))))));

        BBMaxCamera[0] = osgMax(p1.x(),
                         osgMax(p2.x(),
                         osgMax(p3.x(),
                         osgMax(p4.x(),
                         osgMax(p5.x(),
                         osgMax(p6.x(),
                         osgMax(p7.x(),p8.x())))))));

        BBMaxCamera[1] = osgMax(p1.y(),
                         osgMax(p2.y(),
                         osgMax(p3.y(),
                         osgMax(p4.y(),
                         osgMax(p5.y(),
                         osgMax(p6.y(),
                         osgMax(p7.y(),p8.y())))))));

        BBMaxCamera[2] = osgMax(p1.z(),
                         osgMax(p2.z(),
                         osgMax(p3.z(),
                         osgMax(p4.z(),
                         osgMax(p5.z(),
                         osgMax(p6.z(),
                         osgMax(p7.z(),p8.z())))))));

        Pnt3f CamerAt(WorldToCamera * at);

        //Calculate the distance to move the camera back to make sure the bound
        //box is visible
        Real32 dist = 1.05f * ((BBMaxCamera.z()-CamerAt.z()) +
                              osgMax(((BBMaxCamera.y()-BBMinCamera.y()) / (2.0f * osgtan(VertFov *0.5f))),
                                     ((BBMaxCamera.x()-BBMinCamera.x()) / (2.0f * osgtan(HorFov  *0.5f)))));

        //Get the cameras current orientation
        Vec3f OrigY(0.0f,1.0f,0.0f),
              OrigZ(0.0f,0.0f,1.0f);
        CameraToWorld.mult(OrigY);
        CameraToWorld.mult(OrigZ);

        //Keep the same camera heading
        Pnt3f  from = at + (OrigZ * dist); 

        Matrix m;
        if(!MatrixLookAt(m, from, at, OrigY))
        {
            _ApplicationPlayer->moveDebugCamera(m);
        }

        //Scale the Motion Factor of the Navigator
        _ApplicationPlayer->getDebugSceneNavigator().setMotionFactor((d[0] + d[1] + d[2]) / 100.f);
	}
	else
	{
		SWARNING << "Camera is NullFC!" <<std::endl;
	}
}

void HierarchyPanel::setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::SceneGraphTreeSelectionListener::selectedNodeChanged(void)
{
    //Update Details Panel
    if(_SelectedNode == NullFC)
    {
		_ApplicationPlayer->getHelperPanel()->setLabelValuesToNull();
    }
    else
    {
		_ApplicationPlayer->getHelperPanel()->setLabelValues(_SelectedNode);
    }
    _ApplicationPlayer->setSelectedNode(_SelectedNode);
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuCanceled            (const  PopupMenuEventPtr e)
{
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuWillBecomeInvisible (const  PopupMenuEventPtr e)
{
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuWillBecomeVisible   (const  PopupMenuEventPtr e)
{
    _HierarchyPanel->updatePopupMenu();
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuContentsChanged     (const  PopupMenuEventPtr e)
{
}

HierarchyPanel::PlayerMouseListener2::PlayerMouseListener2(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel=TheHierarchyPanel;
}

HierarchyPanel::MenuButtonActionListener::MenuButtonActionListener(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel=TheHierarchyPanel;
}

void HierarchyPanel::PlayerMouseListener2::mouseClicked(const MouseEventPtr e)
{
   if(e->getButton() == e->BUTTON3)
   {
	   std::cout<<"right clicked!!!"<<std::endl;
   }
   if(e->getClickCount() == 2)
   {
		Path path = boost::any_cast<Path>(_HierarchyPanel->_TheLuaGraphTree->getLastSelectedPathComponent());
		
		if(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path))
		{
			std::string filename(path.string());
			std::cout<<"\nfile to open:"<<filename<<std::endl;
			_HierarchyPanel->_ApplicationPlayer->getContentPanel()->addTabWithText(path);
			//_ApplicationPlayer->_ContentPanel->addTabWithText(path);
		}
   }
}

void HierarchyPanel::MenuButtonActionListener::createNewNode(const ActionEventPtr e)
{
	MenuButtonPtr TheMenuButton(MenuButtonPtr::dcast(e->getSource()));
	if(TheMenuButton != NullFC)
	{
		try
		{	
			NodePtr SelectedNode(_HierarchyPanel->_ApplicationPlayer->getSelectedNode());
			if(SelectedNode == NullFC)
			{
				SelectedNode = _HierarchyPanel->_TheSceneGraphTreeModel->getRootNode();
			}

			FieldContainerType* FCType;

			FCType = boost::any_cast<FieldContainerType*>(TheMenuButton->getSelectionValue());
			
			CommandPtr NewCommandPtr = NewCommand::create(_HierarchyPanel,FCType);
			_HierarchyPanel->_ApplicationPlayer->getCommandManager()->executeCommand(NewCommandPtr);
		}	
		catch(boost::bad_any_cast &)
		{
			SWARNING << "badcast: " << std::endl;
		}
	}
	else
	{
		SWARNING << "TheMenuButton is null " << std::endl;
	}
}

void HierarchyPanel::LuaGraphTreeSelectionListener::selectionAdded(const TreeSelectionEventPtr e)
{
	//Get the selected Node
	try
	{
		_SelectedPath = boost::any_cast<Path>(_TheTree->getLastSelectedPathComponent());
	}
	catch (boost::bad_any_cast &)
	{
	}
	
}
void HierarchyPanel::SceneGraphTreeSelectionListener::selectionAdded(const TreeSelectionEventPtr e)
{
	//Get the selected Node
	try
	{
		_SelectedNode = boost::any_cast<NodePtr>(_TheTree->getLastSelectedPathComponent());
	}
	catch (boost::bad_any_cast &)
	{
		_SelectedNode = NullFC;
	}
	selectedNodeChanged();
}

void HierarchyPanel::SceneGraphTreeSelectionListener::selectionRemoved(const TreeSelectionEventPtr e)
{
	_SelectedNode = NullFC;
	selectedNodeChanged();
}

void HierarchyPanel::MenuButtonActionListener::actionPerformed(const ActionEventPtr e)
{
	createNewNode(e);
}

void HierarchyPanel::BasicListener::actionPerformed(const ActionEventPtr e)
{
    _HierarchyPanel->actionPerformed(e);
}

HierarchyPanel::BasicListener::~BasicListener()
{
}

HierarchyPanel::BasicListener::BasicListener(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HierarchyPanel::HierarchyPanel() :
    Inherited(),
	_SceneGraphTreeSelectionListener(HierarchyPanelPtr(this)),
	_LuaGraphTreeSelectionListener(HierarchyPanelPtr(this)),
	_PlayerMouseListener2(HierarchyPanelPtr(this)),
	_TheMenuButtonActionListener(HierarchyPanelPtr(this)),
	_BasicListener(HierarchyPanelPtr(this)),
	_TheSceneGraphPopupListener(HierarchyPanelPtr(this))
{
	_ApplicationPlayer = NullFC;
	
}

HierarchyPanel::HierarchyPanel(const HierarchyPanel &source) :
    Inherited(source),
	_SceneGraphTreeSelectionListener(HierarchyPanelPtr(this)),
	_LuaGraphTreeSelectionListener(HierarchyPanelPtr(this)),
	_PlayerMouseListener2(HierarchyPanelPtr(this)),
	_TheMenuButtonActionListener(HierarchyPanelPtr(this)),
	_BasicListener(HierarchyPanelPtr(this)),
	_TheSceneGraphPopupListener(HierarchyPanelPtr(this))
{
}

HierarchyPanel::~HierarchyPanel(void)
{
}


/*----------------------------- class specific ----------------------------*/

void HierarchyPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void HierarchyPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump HierarchyPanel NI" << std::endl;
}



OSG_END_NAMESPACE

