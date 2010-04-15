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
	_SceneGraphTreeSelectionListener.updateHighlight();


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

	_SceneGraphPanel = Panel::create();
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
	_DeleteItem = MenuItem::create();
	_CutItem = MenuItem::create();
	_CopyItem = MenuItem::create();
	_PasteItem = MenuItem::create();

	// _HierarchyPanelPopupMenu up menu items

	beginEditCP(_ShowHideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ShowHideItem->setText("Hide");
    endEditCP(_ShowHideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

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

	_ShowHideItem->addActionListener(&_BasicListener);
	_DeleteItem->addActionListener(&_BasicListener);
	_CutItem->addActionListener(&_BasicListener);
	_CopyItem->addActionListener(&_BasicListener);
	_PasteItem->addActionListener(&_BasicListener);

	_HierarchyPanelPopupMenu = PopupMenu::create();

	beginEditCP(_HierarchyPanelPopupMenu);
	_HierarchyPanelPopupMenu->addItem(_ShowHideItem);
	_HierarchyPanelPopupMenu->addSeparator();
	_HierarchyPanelPopupMenu->addItem(_CutItem);	
	_HierarchyPanelPopupMenu->addItem(_CopyItem);	
	_HierarchyPanelPopupMenu->addItem(_PasteItem);	
	_HierarchyPanelPopupMenu->addItem(_DeleteItem);	
	endEditCP(_HierarchyPanelPopupMenu);

	beginEditCP(HierarchyPanelPtr(this),Panel::PopupMenuFieldMask);
	this->setPopupMenu(_HierarchyPanelPopupMenu);
	endEditCP(HierarchyPanelPtr(this),Panel::PopupMenuFieldMask);

}

void HierarchyPanel::actionPerformed(const ActionEventPtr e)
{
	if(e->getSource() == _ShowHideItem)
	{
		 CommandPtr ShowHideItemCommand = ShowHideCommand::create(this->_SceneGraphTreeSelectionListener._SelectedNode,_ShowHideItem);
        _ApplicationPlayer->getCommandManager()->executeCommand(ShowHideItemCommand);
	}
	else if(e->getSource() == _DeleteItem)
	{
		CommandPtr DeleteCommandPtr = DeleteCommand::create(_ApplicationPlayer,HierarchyPanelPtr(this));
        _ApplicationPlayer->getCommandManager()->executeCommand(DeleteCommandPtr);
	}
	else if(e->getSource() == _CutItem)
	{
		CommandPtr CutCommandPtr = CutCommand::create(_ApplicationPlayer,_TheSceneGraphTreeModel);
        _ApplicationPlayer->getCommandManager()->executeCommand(CutCommandPtr);
	}

	else if(e->getSource() == _CopyItem)
	{
	
		CommandPtr CopyCommandPtr = CopyCommand::create(_ApplicationPlayer);
        _ApplicationPlayer->getCommandManager()->executeCommand(CopyCommandPtr);

	}
	else if(e->getSource() == _PasteItem)
	{

		CommandPtr PasteCommandPtr = PasteCommand::create(_ApplicationPlayer,HierarchyPanelPtr(this));
        _ApplicationPlayer->getCommandManager()->executeCommand(PasteCommandPtr);
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
        _LayoutConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
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
				std::cout<<"the scenegraph tree hasnt been created yet.. so creating tree";
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
				std::cout<<"the luafile tree hasnt been created yet.. so creating tree";
				createLuaGraphTree();
			}
			beginEditCP(HierarchyPanelPtr(this),  Panel::ChildrenFieldMask);
				this->getChildren().push_back(_TheLuaGraphTreeScrollPanel);
			endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

			_TabsAdded.insert(LUA);
		}
		else
		{
			std::cout<<"undefined number in addtab of HierarchyPanel";
		}
	}
	else
	{
		std::cout<<"tab already exists\n";
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
	beginEditCP(_ShowHideItem, MenuItem::EnabledFieldMask);
		_ShowHideItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_ShowHideItem, MenuItem::EnabledFieldMask);

	//Update Paste
	beginEditCP(_PasteItem, MenuItem::EnabledFieldMask);
		_PasteItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NullFC);
    endEditCP(_PasteItem, MenuItem::EnabledFieldMask);

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
}

void HierarchyPanel::changeShowHideMenuItem(void)
{

	if(_ApplicationPlayer!=NullFC && _SelectedNode!=NullFC && _ShowHideItem!=NullFC)
	{
		UInt32 maskval = _SelectedNode->getTravMask();
		//std::cout<<"maskval:"<<maskval<<std::endl;	
		if(!maskval)
		{
			if(_ShowHideItem->getText()== "Hide")
			{
				//std::cout<<"changing from hide to show"<<std::endl;
				beginEditCP(_ShowHideItem,MenuItem::TextFieldMask);
				_ShowHideItem->setText("Show");
				endEditCP(_ShowHideItem,MenuItem::TextFieldMask);
			}
			else
			{
				//std::cout<<"its already 'show'";
			}
		}
		else 
		{
			if(_ShowHideItem->getText()== "Show")
			{
				//std::cout<<"changing from show to hide"<<std::endl;
				beginEditCP(_ShowHideItem,MenuItem::TextFieldMask);
				_ShowHideItem->setText("Hide");
				endEditCP(_ShowHideItem,MenuItem::TextFieldMask);
			}
			else
			{
				//std::cout<<"its already 'hide'";
			}
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
	_highlight = NullFC;
	_highlightPoints = NullFC;
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

void HierarchyPanel::SceneGraphTreeSelectionListener::setHighlight(NodePtr selectednode)
{
	
	_highlight = selectednode;
	highlightChanged();
}
NodePtr HierarchyPanel::SceneGraphTreeSelectionListener::getHighlight()
{
	return _highlight;
}
void HierarchyPanel::SceneGraphTreeSelectionListener::highlightChanged(void)
{
 
	// change the ShowHideMenuItem's text 
	
	SimpleMaterialPtr _highlightMaterial;
	
	
// SWARNING << "SimpleSceneManager::updateHightlight() called\n";

	// init as needed
	if(_highlightMaterial == NullFC)
	{
		_highlightMaterial = SimpleMaterial::create();
		
		beginEditCP(_highlightMaterial);
		_highlightMaterial->setDiffuse (Color3f(0,1,0));
		_highlightMaterial->setLit     (false);
		endEditCP(_highlightMaterial);
	}
	if(_ApplicationPlayer->getHighlightNode() == NullFC)
	{
		GeoPTypesPtr type = GeoPTypesUI8::create();
		beginEditCP(type);
		type->push_back(GL_LINE_STRIP);
		type->push_back(GL_LINES);
		endEditCP(type);

		GeoPLengthsPtr lens = GeoPLengthsUI32::create();
		beginEditCP(lens);
		lens->push_back(10);
		lens->push_back(6);
		endEditCP(lens);

		GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
		beginEditCP(index);
		index->getFieldPtr()->push_back(0);
		index->getFieldPtr()->push_back(1);
		index->getFieldPtr()->push_back(3);
		index->getFieldPtr()->push_back(2);
		index->getFieldPtr()->push_back(0);
		index->getFieldPtr()->push_back(4);
		index->getFieldPtr()->push_back(5);
		index->getFieldPtr()->push_back(7);
		index->getFieldPtr()->push_back(6);
		index->getFieldPtr()->push_back(4);

		index->getFieldPtr()->push_back(1);
		index->getFieldPtr()->push_back(5);
		index->getFieldPtr()->push_back(2);
		index->getFieldPtr()->push_back(6);
		index->getFieldPtr()->push_back(3);
		index->getFieldPtr()->push_back(7);
		endEditCP(index);

		_highlightPoints = GeoPositions3f::create();
		beginEditCP(_highlightPoints);
		_highlightPoints->push_back(Pnt3f(-1, -1, -1));
		_highlightPoints->push_back(Pnt3f( 1, -1, -1));
		_highlightPoints->push_back(Pnt3f(-1,  1, -1));
		_highlightPoints->push_back(Pnt3f( 1,  1, -1));
		_highlightPoints->push_back(Pnt3f(-1, -1,  1));
		_highlightPoints->push_back(Pnt3f( 1, -1,  1));
		_highlightPoints->push_back(Pnt3f(-1,  1,  1));
		_highlightPoints->push_back(Pnt3f( 1,  1,  1));
		endEditCP(_highlightPoints);
		addRefCP(_highlightPoints);

		GeometryPtr geo=Geometry::create();
		beginEditCP(geo);
		geo->setTypes     (type);
		geo->setLengths   (lens);
		geo->setIndices   (index);
		geo->setPositions (_highlightPoints);
		geo->setMaterial  (_highlightMaterial);  /// billa
		endEditCP(geo);
		addRefCP(geo);

		_ApplicationPlayer->setHighlightNode(Node::create());
		setName(_ApplicationPlayer->getHighlightNode(),"DEBUG_MODE_BOUNDING_BOX");
		
		beginEditCP(_ApplicationPlayer->getHighlightNode());
		_ApplicationPlayer->getHighlightNode()->setCore(geo);
		endEditCP(_ApplicationPlayer->getHighlightNode());
		addRefCP(_ApplicationPlayer->getHighlightNode());
	}

	
	// attach the hightlight node to the root if the highlight is active
	if(getHighlight() != NullFC)
	{
		if(_ApplicationPlayer->getHighlightNode()->getParent() == NullFC)
		{
		beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->addChild(_ApplicationPlayer->getHighlightNode());

		endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		}
		
	}
	else
	{
		if(_ApplicationPlayer->getHighlightNode()->getParent() != NullFC)
		{
		beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->subChild(_ApplicationPlayer->getHighlightNode());
		endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		}
	}
	// update the highlight geometry
	updateHighlight();
}

void HierarchyPanel::SceneGraphTreeSelectionListener::changeDebugCameraPosition(void)
{
	

	showAll(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getCamera(),_ApplicationPlayer->getSelectedNode());
	//showAll(_ApplicationPlayer->getDebugViewport()->getCamera(),_ApplicationPlayer->getSelectedNode());

	/*
	if(_highlight==NullFC)
	return;

	// calc the world bbox of the highlight object
	#ifndef OSG_2_PREP
	DynamicVolume vol;
	#else
	BoxVolume      vol;
	#endif
	_highlight->getWorldVolume(vol);

	Pnt3f min,max;
	vol.getBounds(min, max);

	
	NodePtr _DebugBeacon = _ApplicationPlayer->_DebugBeacon;
	TransformPtr DebugCameraTransform = osg::TransformPtr::dcast(_DebugBeacon->getCore());

	Matrix CameraTransformMatrix;
	CameraTransformMatrix.setTranslate(0.0f,25.0f, 105.0f);
	
	beginEditCP(DebugCameraTransform, Transform::MatrixFieldMask);
		DebugCameraTransform->setMatrix(CameraTransformMatrix);
	endEditCP(DebugCameraTransform, Transform::MatrixFieldMask);
	
	
	beginEditCP(_DebugBeacon, Node::CoreFieldMask);
		_DebugBeacon->setCore(DebugCameraTransform);
	endEditCP(_DebugBeacon, Node::CoreFieldMask);

	beginEditCP(_ApplicationPlayer->_DebugBeacon, Node::CoreFieldMask);
		_ApplicationPlayer->_DebugBeacon->setCore(DebugCameraTransform);
	endEditCP(_ApplicationPlayer->_DebugBeacon, Node::CoreFieldMask);
	
	*/
}



void HierarchyPanel::SceneGraphTreeSelectionListener::showAll(CameraPtr TheCameraOrig, NodePtr Scene, Vec3f Up)
{

	if(Scene!=NullFC && TheCameraOrig!=NullFC)
	{
		if(getName(Scene))
		{
			std::cout<<"Selected node is : "<<getName(Scene)<<std::endl;
		}
		else
		{
			std::cout<<"Selected node is : Unnamed node"<<std::endl;
		}

		std::string coreType = Scene->getCore()->getTypeName();

		//if(coreType == "Geometry")
		//{

			PerspectiveCameraPtr TheCamera;
			if(TheCameraOrig->getType() == PerspectiveCamera::getClassType())
			{
				TheCamera = PerspectiveCamera::Ptr::dcast(TheCameraOrig);
			}

			//Make sure the volume is up to date for the Scene
			Scene->updateVolume();

			//Get the Minimum and Maximum bounds of the volume
			DynamicVolume _DyVol;
			Scene->getWorldVolume(_DyVol);

			Vec3f min,max;
			_DyVol.getBounds( min, max );
			Vec3f d = max - min;

			if(d.length() < Eps) //The volume is 0
			{
				SWARNING << "The volume of selected geometry is zero" ;
				//Default to a 1x1x1 box volume
				min.setValues(-0.5f,-0.5f,-0.5f);
				max.setValues( 0.5f, 0.5f, 0.5f);
				d = max - min;
			}

			Real32 dist = osgMax(d[0],d[1]) / (2 * osgtan(TheCamera->getFov() / 2.f));

			Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);
			Pnt3f from=at;
			from[2]-=(100+dist+fabs(max[2]-min[2])*0.5f); 

			//std::cout<<"at : "<<at[0]<<","<<at[1]<<","<<at[2]<<std::endl;
			//std::cout<<"from : "<<from[0]<<","<<from[1]<<","<<from[2]<<std::endl;

			//If the Camera Beacon is a node with a transfrom core
			if(TheCamera->getBeacon() != NullFC &&
				TheCamera->getBeacon()->getCore() != NullFC &&
				TheCamera->getBeacon()->getCore()->getType().isDerivedFrom(Transform::getClassType()))
			{
				Matrix m;

				if(!MatrixLookAt(m, from, at, Up))
				{
					beginEditCP(TheCamera->getBeacon()->getCore(), Transform::MatrixFieldMask);
						Transform::Ptr::dcast(TheCamera->getBeacon()->getCore())->setMatrix(m);
					endEditCP(TheCamera->getBeacon()->getCore(), Transform::MatrixFieldMask);
				}
			}

			//Set the camera to go from 1% of the object to 10 times its size
			/*Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);
			beginEditCP(TheCamera,  PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask);
				TheCamera->setNear (diag / 100.f);
				TheCamera->setFar  (10 * diag);
			endEditCP(TheCamera, PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask);
			*/
		//}
		//else
		//{
		//	SWARNING << "Selected node not a geometry node"<<std::endl;
		//}
	}
	else
	{

		if(Scene==NullFC)SWARNING << "Scene is NullFC!" <<std::endl;
		else SWARNING << "Camera is NullFC!" <<std::endl;
		
	}
}


void HierarchyPanel::SceneGraphTreeSelectionListener::updateHighlight(void)
{
	if(_highlight==NullFC)
	return;

	// calc the world bbox of the highlight object
	#ifndef OSG_2_PREP
	DynamicVolume vol;
	#else
	BoxVolume      vol;
	#endif
	_highlight->getWorldVolume(vol);

	Pnt3f min,max;
	vol.getBounds(min, max);

	beginEditCP(_highlightPoints);
	_highlightPoints->setValue(Pnt3f(min[0], min[1], min[2]), 0);
	_highlightPoints->setValue(Pnt3f(max[0], min[1], min[2]), 1);
	_highlightPoints->setValue(Pnt3f(min[0], max[1], min[2]), 2);
	_highlightPoints->setValue(Pnt3f(max[0], max[1], min[2]), 3);
	_highlightPoints->setValue(Pnt3f(min[0], min[1], max[2]), 4);
	_highlightPoints->setValue(Pnt3f(max[0], min[1], max[2]), 5);
	_highlightPoints->setValue(Pnt3f(min[0], max[1], max[2]), 6);
	_highlightPoints->setValue(Pnt3f(max[0], max[1], max[2]), 7);
	endEditCP(_highlightPoints);


}

void HierarchyPanel::setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::SceneGraphTreeSelectionListener::selectedNodeChanged(void)
{

	//Update Right Click Menu
	_HierarchyPanel->updatePopupMenu();
	
	setHighlight(_SelectedNode);
	
    //Update Details Panel
    if(_SelectedNode == NullFC)
    {
		_ApplicationPlayer->getHelperPanel()->setLabelValuesToNull();
    }
    else
    {
		_ApplicationPlayer->setSelectedNode(_SelectedNode);
		_ApplicationPlayer->getHelperPanel()->setLabelValues(_SelectedNode);
		//Reset the debug camera to point to the corresponding geometry
		changeDebugCameraPosition();
    }

	

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
			NodePtr _SelectedNode(_HierarchyPanel->_ApplicationPlayer->getSelectedNode());
			if(_SelectedNode == NullFC)
			{
				_SelectedNode = _HierarchyPanel->_TheSceneGraphTreeModel->getRootNode();
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
	_BasicListener(HierarchyPanelPtr(this))
{
	_ApplicationPlayer = NullFC;
	
}

HierarchyPanel::HierarchyPanel(const HierarchyPanel &source) :
    Inherited(source),
	_SceneGraphTreeSelectionListener(HierarchyPanelPtr(this)),
	_LuaGraphTreeSelectionListener(HierarchyPanelPtr(this)),
	_PlayerMouseListener2(HierarchyPanelPtr(this)),
	_TheMenuButtonActionListener(HierarchyPanelPtr(this)),
	_BasicListener(HierarchyPanelPtr(this))
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

