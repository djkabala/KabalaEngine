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

#include "Application/KEMainApplication.h"

#include <boost/filesystem/operations.hpp>
#include <OpenSG/OSGTreePath.h>
#include "boost/filesystem.hpp"

#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGDerivedFieldContainerComboBoxModel.h>

#include "Player/Commands/KEShowHideCommand.h"
#include "Player/Commands/KEDeleteCommand.h"
#include "Player/Commands/KECutCommand.h"
#include "Player/Commands/KECopyCommand.h"
#include "Player/Commands/KEPasteCommand.h"
#include "Player/Commands/KENewCommand.h"

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

	
    _TheSceneGraphTree->getSelectionModel()->addTreeSelectionListener(&_SceneGraphTreeSelectionListener);
	
	
    BorderLayoutConstraintsRefPtr SceneTreeConstraints = OSG::BorderLayoutConstraints::create();
	SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    _TheSceneGraphTreeScrollPanel = ScrollPanel::create();
        _TheSceneGraphTreeScrollPanel->setPreferredSize(Vec2f(350,300));
        _TheSceneGraphTreeScrollPanel->setConstraints(SceneTreeConstraints);
    _TheSceneGraphTreeScrollPanel->setViewComponent(_TheSceneGraphTree);

	
	_SceneGraphTreeSelectionListener.setParams(_TheSceneGraphTree,_ApplicationPlayer);

	_NewNodeMenuModel = DerivedFieldContainerComboBoxModel::create();
	_NewNodeMenuModel->editMFDerivedFieldContainerTypes()->push_back(std::string(OSG::NodeCore::getClassType().getCName()));

	_CreateNewNodeMenuButton = MenuButton::create();

	_CreateNewButtonConstraints = OSG::BorderLayoutConstraints::create();

	_CreateNewButtonConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);

        _CreateNewNodeMenuButton->setText("Create New Node");
        _CreateNewNodeMenuButton->setPreferredSize(Vec2f(120, 20));
        _CreateNewNodeMenuButton->setModel(_NewNodeMenuModel);
		_CreateNewNodeMenuButton->setConstraints(_CreateNewButtonConstraints);
    
	_CreateNewNodeMenuButton->addMenuActionListener(&_TheMenuButtonActionListener);

	BorderLayoutRefPtr SceneGraphTreeLayout = OSG::BorderLayout::create();

        // Nothing

	_SceneGraphPanel = Panel::createEmpty();
	_SceneGraphPanel->pushToChildren(_TheSceneGraphTreeScrollPanel);
	_SceneGraphPanel->pushToChildren(_CreateNewNodeMenuButton);
	_SceneGraphPanel->setLayout(SceneGraphTreeLayout);



/*	UInt32 NumFieldContainersFound(0);
    FieldContainerType* FoundType = NULL;
    FieldContainerEditorRefPtr DefaultEditor;
    for(UInt32 j(0) ; NumFieldContainersFound<FieldContainerFactory::the()->getNumTypes(); ++j)
    {
        FoundType = FieldContainerFactory::the()->findType(j);
        if(FoundType != NULL)
        {
			if(FoundType->isDerivedFrom(OSG::NodeCore::getClassType())  && !FoundType->isAbstract())
            {
                //Add Editor

				std::string ftname = (FoundType->getName()).str();
				NodeCoreRefPtr core = FieldContainerFactory::the()->createNodeCore(ftname.c_str());
				NodeRefPtr _Temp = Node::create();
				_Temp->setCore(core);	
			
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

        _ShowHideItem->setText("Hide");

        _ShowRecursiveItem->setText("Show all below");

        _DeleteItem->setText("Delete");

        _CutItem->setText("Cut");

        _CopyItem->setText("Copy");

        _PasteItem->setText("Paste");

        _PasteInstanceItem->setText("Paste Instance");

        _FocusCamera->setText("Focus Camera All");

	_ShowHideItem->addActionListener(&_BasicListener);
	_ShowRecursiveItem->addActionListener(&_BasicListener);
	_DeleteItem->addActionListener(&_BasicListener);
	_CutItem->addActionListener(&_BasicListener);
	_CopyItem->addActionListener(&_BasicListener);
	_PasteItem->addActionListener(&_BasicListener);
	_PasteInstanceItem->addActionListener(&_BasicListener);
	_FocusCamera->addActionListener(&_BasicListener);

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
        _HierarchyPanelPopupMenu->addItem(_FocusCamera);	
    _HierarchyPanelPopupMenu->addPopupMenuListener(&_TheSceneGraphPopupListener);

	this->setPopupMenu(_HierarchyPanelPopupMenu);

}

void HierarchyPanel::setView(UInt32 Index)
{
        _CardLayout->setCard(Index);
}

void HierarchyPanel::actionPerformed(const ActionEventUnrecPtr e)
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
		CommandPtr DeleteCommandPtr = DeleteCommand::create(_ApplicationPlayer,HierarchyPanelRefPtr(this),_ApplicationPlayer->getSelectedNode());
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
	else if(e->getSource() == _PasteInstanceItem)
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
}

void HierarchyPanel::createLuaGraphTree()
{
	_TheLuaGraphTree = Tree::create();
	_TheLuaGraphTreeModel = LuaGraphTreeModel::create();
	
	_TheLuaGraphTreeModel->setRoot(MainApplication::the()->getProject()->getLuaModulePath());

        _TheLuaGraphTree->setPreferredSize(Vec2f(100, 500));
        _TheLuaGraphTree->setModel(_TheLuaGraphTreeModel);

	_TheLuaGraphTree->getSelectionModel()->addTreeSelectionListener(&_LuaGraphTreeSelectionListener);

	BorderLayoutConstraintsRefPtr SceneTreeConstraints2 = OSG::BorderLayoutConstraints::create();
        SceneTreeConstraints2->setRegion(BorderLayoutConstraints::BORDER_WEST);

    _TheLuaGraphTreeScrollPanel = ScrollPanel::create();
        _TheLuaGraphTreeScrollPanel->setPreferredSize(Vec2f(350,300));
        _TheLuaGraphTreeScrollPanel->setConstraints(SceneTreeConstraints2);
    _TheLuaGraphTreeScrollPanel->setViewComponent(_TheLuaGraphTree);

	
	_LuaGraphTreeSelectionListener.setParams(_TheLuaGraphTree,_ApplicationPlayer);

	//_PlayerMouseListener2.setParams(_ApplicationPlayer);

	_TheLuaGraphTree->addMouseListener(&_PlayerMouseListener2);
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
		if(tabno == SCENEGRAPH)
		{
			if (_TheSceneGraphTreeScrollPanel == NULL)
			{
				createSceneGraphTree();
			}
				this->pushToChildren(_SceneGraphPanel);

			_TabsAdded.insert(SCENEGRAPH);

		}
		else if(tabno == LUA)
		{
			if (_TheLuaGraphTreeScrollPanel == NULL)
			{
				createLuaGraphTree();
			}
				this->pushToChildren(_TheLuaGraphTreeScrollPanel);

			_TabsAdded.insert(LUA);
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

			case SCENEGRAPH:	
				this->removeObjFromChildren(dynamic_pointer_cast<Component>(_SceneGraphPanel));
				break;
			case LUA:
				this->removeObjFromChildren(dynamic_pointer_cast<Component>(_TheLuaGraphTreeScrollPanel));
				break;
		}

	}

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
		_ShowHideItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NULL);

    //Update Show Recursive
		_ShowRecursiveItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NULL);

	//Update Paste
		_PasteItem->setEnabled(_ApplicationPlayer->getClonedNodeInCopyClipboard() != NULL);

	//Update Paste Instance
		_PasteInstanceItem->setEnabled(_ApplicationPlayer->getClonedNodeInCopyClipboard() != NULL);

	//Update Copy
		_CopyItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NULL);

	//Update Cut
		_CutItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NULL);

	//Update Delete
		_DeleteItem->setEnabled(_SceneGraphTreeSelectionListener._SelectedNode != NULL);

    //Update Camera Focusing
        if(_SceneGraphTreeSelectionListener._SelectedNode != NULL)
        {
            _FocusCamera->setText("Focus Camera Here");
        }
        else
        {
            _FocusCamera->setText("Focus Camera All");
        }

}

void HierarchyPanel::changeShowHideMenuItem(void)
{
	if(_ApplicationPlayer!=NULL && _SceneGraphTreeSelectionListener._SelectedNode!=NULL && _ShowHideItem!=NULL)
	{
		UInt32 maskval = _SceneGraphTreeSelectionListener._SelectedNode->getTravMask();
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

HierarchyPanel::LuaGraphTreeSelectionListener::LuaGraphTreeSelectionListener(HierarchyPanelRefPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
	_ApplicationPlayer = NULL;
	_TheTree=NULL;
}

HierarchyPanel::SceneGraphTreeSelectionListener::SceneGraphTreeSelectionListener(HierarchyPanelRefPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
	_ApplicationPlayer = NULL;
	_TheTree=NULL;
}

void HierarchyPanel::SceneGraphTreeSelectionListener::setParams(TreeRefPtr TheTree,ApplicationPlayerRefPtr TheApplicationPlayer)//,NodeRefPtr  _SelectedNode)
{
	_TheTree=TheTree;
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::LuaGraphTreeSelectionListener::setParams(TreeRefPtr TheTree,ApplicationPlayerRefPtr TheApplicationPlayer)//,NodeRefPtr  _SelectedNode)
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

void HierarchyPanel::showAll(CameraRefPtr TheCameraOrig,
                             NodeRefPtr Scene,
                             ViewportRefPtr LocalViewport)
{
    NodeRefPtr FocusNode(Scene);
	if(FocusNode==NULL)
	{
        FocusNode = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot();
    }

	if(TheCameraOrig!=NULL)
	{
        PerspectiveCameraRefPtr TheCamera;
        if(TheCameraOrig->getType() == PerspectiveCamera::getClassType())
        {
            TheCamera = dynamic_pointer_cast<PerspectiveCamera>(TheCameraOrig);
        }

        //Make sure the volume is up to date for the FocusNode
        FocusNode->updateVolume();

        //Get the Minimum and Maximum bounds of the volume
        Vec3f min,max;
        BoxVolume TheVol;
        FocusNode->getWorldVolume(TheVol);
        TheVol.getBounds( min, max );

        Vec3f d = max - min;
        if(d.length() < Eps) //The volume is 0
        {
            Pnt3f NodeOrigin(0.0f,0.0f,0.0f);
            FocusNode->getToWorld().mult(NodeOrigin, NodeOrigin);
            //Default to a 1x1x1 box volume
            min = Vec3f(NodeOrigin) - Vec3f(1.0f,1.0f,1.0f);
            max = Vec3f(NodeOrigin) + Vec3f(1.0f,1.0f,1.0f);
            d = max - min;
        }

        // try to be nice to people giving degrees...
        Real32 VertFov(TheCamera->getFov());
        if(VertFov > Pi)
        {
            VertFov = osgDegree2Rad(VertFov);
        }

        //Get the horizontal feild of view
        Real32 HorFov = 2.0f * osgATan(static_cast<Real32>(LocalViewport->getPixelWidth())
                                       /(static_cast<Real32>(LocalViewport->getPixelHeight())/osgTan(VertFov*0.5f)));

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
                              osgMax(((BBMaxCamera.y()-BBMinCamera.y()) / (2.0f * osgTan(VertFov *0.5f))),
                                     ((BBMaxCamera.x()-BBMinCamera.x()) / (2.0f * osgTan(HorFov  *0.5f)))));

        //Get the cameras current orientation
        Vec3f OrigY(0.0f,1.0f,0.0f),
              OrigZ(0.0f,0.0f,1.0f);
        CameraToWorld.mult(OrigY, OrigY);
        CameraToWorld.mult(OrigZ, OrigZ);

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
		SWARNING << "Camera is NULL!" <<std::endl;
	}
}

void HierarchyPanel::setApplicationPlayer(ApplicationPlayerRefPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::SceneGraphTreeSelectionListener::selectedNodeChanged(void)
{
    //Update Details Panel
    if(_SelectedNode == NULL)
    {
		_ApplicationPlayer->getHelperPanel()->setLabelValuesToNull();
    }
    else
    {
		_ApplicationPlayer->getHelperPanel()->setLabelValues(_SelectedNode);
    }
    _ApplicationPlayer->setSelectedNode(_SelectedNode);
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuCanceled            (const  PopupMenuEventUnrecPtr e)
{
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuWillBecomeInvisible (const  PopupMenuEventUnrecPtr e)
{
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuWillBecomeVisible   (const  PopupMenuEventUnrecPtr e)
{
    _HierarchyPanel->updatePopupMenu();
}

void HierarchyPanel::SceneGraphPopupListener::popupMenuContentsChanged     (const  PopupMenuEventUnrecPtr e)
{
}

HierarchyPanel::PlayerMouseListener2::PlayerMouseListener2(HierarchyPanelRefPtr TheHierarchyPanel)
{
	_HierarchyPanel=TheHierarchyPanel;
}

HierarchyPanel::MenuButtonActionListener::MenuButtonActionListener(HierarchyPanelRefPtr TheHierarchyPanel)
{
	_HierarchyPanel=TheHierarchyPanel;
}

void HierarchyPanel::PlayerMouseListener2::mouseClicked(const MouseEventUnrecPtr e)
{
   if(e->getClickCount() == 2)
   {
		BoostPath path = boost::any_cast<BoostPath>(_HierarchyPanel->_TheLuaGraphTree->getLastSelectedPathComponent());
		
		if(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path))
		{
			std::string filename(path.string());
			_HierarchyPanel->_ApplicationPlayer->getContentPanel()->addTabWithText(path);
			//_ApplicationPlayer->_ContentPanel->addTabWithText(path);
		}
   }
}

void HierarchyPanel::MenuButtonActionListener::createNewNode(const ActionEventUnrecPtr e)
{
	MenuButtonRefPtr TheMenuButton(dynamic_cast<MenuButton*>(e->getSource()));
	if(TheMenuButton != NULL)
	{
		try
		{	
			NodeRefPtr SelectedNode(_HierarchyPanel->_ApplicationPlayer->getSelectedNode());
			if(SelectedNode == NULL)
			{
				SelectedNode = _HierarchyPanel->_TheSceneGraphTreeModel->getRootNode();
			}

			FieldContainerType* FCType;

			FCType = boost::any_cast<FieldContainerType*>(TheMenuButton->getSelectionValue());
			
			CommandPtr NewCommandPtr = NewCommand::create(_HierarchyPanel,FCType);
			_HierarchyPanel->_ApplicationPlayer->getCommandManager()->executeCommand(NewCommandPtr);
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

void HierarchyPanel::LuaGraphTreeSelectionListener::selectionAdded(const TreeSelectionEventUnrecPtr e)
{
	//Get the selected Node
	try
	{
		_SelectedPath = boost::any_cast<BoostPath>(_TheTree->getLastSelectedPathComponent());
	}
	catch (boost::bad_any_cast &)
	{
	}
	
}
void HierarchyPanel::SceneGraphTreeSelectionListener::selectionAdded(const TreeSelectionEventUnrecPtr e)
{
	//Get the selected Node
	try
	{
		_SelectedNode = boost::any_cast<NodeUnrecPtr>(_TheTree->getLastSelectedPathComponent());
	}
	catch (boost::bad_any_cast &ex)
	{
        SWARNING << ex.what() << std::endl;
		_SelectedNode = NULL;
	}
	selectedNodeChanged();
}

void HierarchyPanel::SceneGraphTreeSelectionListener::selectionRemoved(const TreeSelectionEventUnrecPtr e)
{
	_SelectedNode = NULL;
	selectedNodeChanged();
}

void HierarchyPanel::MenuButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
	createNewNode(e);
}

void HierarchyPanel::BasicListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _HierarchyPanel->actionPerformed(e);
}

HierarchyPanel::BasicListener::~BasicListener()
{
}

HierarchyPanel::BasicListener::BasicListener(HierarchyPanelRefPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HierarchyPanel::HierarchyPanel(void) :
    Inherited(),
	_SceneGraphTreeSelectionListener(HierarchyPanelRefPtr(this)),
	_LuaGraphTreeSelectionListener(HierarchyPanelRefPtr(this)),
	_PlayerMouseListener2(HierarchyPanelRefPtr(this)),
	_TheMenuButtonActionListener(HierarchyPanelRefPtr(this)),
	_BasicListener(HierarchyPanelRefPtr(this)),
	_TheSceneGraphPopupListener(HierarchyPanelRefPtr(this))
{
	_ApplicationPlayer = NULL;
}

HierarchyPanel::HierarchyPanel(const HierarchyPanel &source) :
    Inherited(source),
	_SceneGraphTreeSelectionListener(HierarchyPanelRefPtr(this)),
	_LuaGraphTreeSelectionListener(HierarchyPanelRefPtr(this)),
	_PlayerMouseListener2(HierarchyPanelRefPtr(this)),
	_TheMenuButtonActionListener(HierarchyPanelRefPtr(this)),
	_BasicListener(HierarchyPanelRefPtr(this)),
	_TheSceneGraphPopupListener(HierarchyPanelRefPtr(this))
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
