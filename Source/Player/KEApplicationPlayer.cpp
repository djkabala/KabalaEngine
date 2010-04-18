/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGDrawable.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGMaterialGroup.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

#include "KEApplicationPlayer.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"
#include "Application/KEMainApplication.h"
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGSceneGraphTreeModel.h>

#include "Player/HierarchyPanel/KEHierarchyPanel.h"
#include "Player/HelperPanel/KEHelperPanel.h"
#include "Player/ContentPanel/KEContentPanel.h"

OSG_USING_NAMESPACE


//  the ptrs for the debug interface

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ApplicationPlayer
The ApplicationPlayer. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationPlayer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void ApplicationPlayer::reset(void)
{
}

void ApplicationPlayer::attachApplication(void)
{
	Inherited::attachApplication();

	//Main Window Titlebar
	ProjectPtr TheProject(MainApplication::the()->getProject());
    updateWindowTitle();
	MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&_PlayerKeyListener);
	MainApplication::the()->getMainWindowEventProducer()->addUpdateListener(&_highlightNodeListener);
}


void ApplicationPlayer::dettachApplication(void)
{
	MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_PlayerKeyListener);
	MainApplication::the()->getMainWindowEventProducer()->removeUpdateListener(&_highlightNodeListener);
	Inherited::dettachApplication();
}

void ApplicationPlayer::attachInterface(void)
{
}

void ApplicationPlayer::attachListeners(void)
{
}

void ApplicationPlayer::start(void)
{
	if(MainApplication::the()->getProject() != NullFC)
	{
		createDebugInterface();							// Allocate memory to the various pointers in the debug interface when the ApplicationPlayer is started

        createGotoSceneMenuItems(MainApplication::the()->getProject());

		MainApplication::the()->getProject()->start();
        
		enableDebug(false);
	}
}

void ApplicationPlayer::stop(void)
{
	if(MainApplication::the()->getProject() != NullFC)
	{
		MainApplication::the()->getProject()->stop();
	}
}


void ApplicationPlayer::createDebugInterface(void)
{
    //Check if te Debug Interface has already been created
    if(DebuggerGraphics != NullFC)
    {
        return;
    }

	 // debug interface creation
	DebuggerGraphics = osg::Graphics2D::create();

	/*************************************************** Menu creation *******************************************************************/
	// the menu items
	_ResetItem = MenuItem::create();				
    _ForceQuitItem = MenuItem::create();			
	
	_UndoItem = MenuItem::create();				
    _RedoItem = MenuItem::create();			

    _NextItem = MenuItem::create();				
    _PrevItem = MenuItem::create();				
    _FirstItem = MenuItem::create();				
    _LastItem = MenuItem::create();				
    _SceneSubItem = Menu::create();				

	_FlyNavigatorItem = MenuItem::create();		
    _TrackballNavigatorItem = MenuItem::create();

    _BasicItem = MenuItem::create();				
    _RenderItem = MenuItem::create();			
    _PhysicsItem = MenuItem::create();
    _ParticleSystemItem = MenuItem::create();	
	_AnimationItem = MenuItem::create();
	_PauseActiveUpdatesItem = MenuItem::create();
	_DrawBoundingVolumesItem = MenuItem::create();
	_FrustrumCullingItem = MenuItem::create();
	_DrawPhysicsCharacteristicsItem = MenuItem::create();


	// setting the fields of the menu items
	beginEditCP(_ResetItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ResetItem->setText("Reset");
		_ResetItem->setAcceleratorKey(KeyEvent::KEY_E);
        _ResetItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _ResetItem->setMnemonicKey(KeyEvent::KEY_E);
    endEditCP(_ResetItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(_ForceQuitItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ForceQuitItem ->setText("Force Quit");
		_ForceQuitItem ->setAcceleratorKey(KeyEvent::KEY_Q);
        _ForceQuitItem ->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _ForceQuitItem ->setMnemonicKey(KeyEvent::KEY_Q);
    endEditCP(_ForceQuitItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_UndoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _UndoItem->setText("Undo");
		_UndoItem->setAcceleratorKey(KeyEvent::KEY_U);
        _UndoItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _UndoItem->setMnemonicKey(KeyEvent::KEY_U);
    endEditCP(_UndoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
 
	beginEditCP(_RedoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _RedoItem->setText("Redo");
		_RedoItem->setAcceleratorKey(KeyEvent::KEY_R);
        _RedoItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _RedoItem->setMnemonicKey(KeyEvent::KEY_R);
    endEditCP(_RedoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
 
    beginEditCP(_NextItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _NextItem ->setText("Next");
		_NextItem ->setAcceleratorKey(KeyEvent::KEY_TAB);
		//_NextItem ->setAcceleratorModifiers(!KeyEvent::KEY_MODIFIER_SHIFT);
	endEditCP(_NextItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(_PrevItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _PrevItem->setText("Previous");
	    _PrevItem->setAcceleratorKey(KeyEvent::KEY_TAB);
        _PrevItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_SHIFT);
    endEditCP(_PrevItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

    beginEditCP(_FirstItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _FirstItem->setText("First");
		_FirstItem->setAcceleratorKey(KeyEvent::KEY_F);
        _FirstItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _FirstItem->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(_FirstItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_LastItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _LastItem->setText("Last");
		_LastItem->setAcceleratorKey(KeyEvent::KEY_L);
        _LastItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _LastItem->setMnemonicKey(KeyEvent::KEY_L);
    endEditCP(_LastItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_SceneSubItem, Menu::TextFieldMask);
        _SceneSubItem->setText("Scenes");
    endEditCP(_SceneSubItem, Menu::TextFieldMask);
    
	beginEditCP(_FlyNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _FlyNavigatorItem->setText("FlyNavigator ");
		_FlyNavigatorItem->setAcceleratorKey(KeyEvent::KEY_N);
        _FlyNavigatorItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _FlyNavigatorItem->setMnemonicKey(KeyEvent::KEY_N);
    endEditCP(_FlyNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_TrackballNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _TrackballNavigatorItem->setText("TrackballNavigator ");
		_TrackballNavigatorItem->setAcceleratorKey(KeyEvent::KEY_T);
        _TrackballNavigatorItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _TrackballNavigatorItem->setMnemonicKey(KeyEvent::KEY_T);
    endEditCP(_TrackballNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_BasicItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _BasicItem->setText("Basic ");
	    _BasicItem->setAcceleratorKey(KeyEvent::KEY_B);
        _BasicItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _BasicItem->setMnemonicKey(KeyEvent::KEY_B);
    endEditCP(_BasicItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_RenderItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _RenderItem->setText("Render ");
	    _RenderItem->setAcceleratorKey(KeyEvent::KEY_R);
        _RenderItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _RenderItem->setMnemonicKey(KeyEvent::KEY_R);
    endEditCP(_RenderItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_PhysicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _PhysicsItem->setText("Physics ");
        _PhysicsItem->setAcceleratorKey(KeyEvent::KEY_Y);
        _PhysicsItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _PhysicsItem->setMnemonicKey(KeyEvent::KEY_Y);
    endEditCP(_PhysicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_ParticleSystemItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ParticleSystemItem->setText("ParticleSystem ");
        _ParticleSystemItem->setAcceleratorKey(KeyEvent::KEY_Z);
        _ParticleSystemItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _ParticleSystemItem->setMnemonicKey(KeyEvent::KEY_Z);
    endEditCP(_ParticleSystemItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_AnimationItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _AnimationItem->setText("Animation ");
        _AnimationItem->setAcceleratorKey(KeyEvent::KEY_A);
        _AnimationItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _AnimationItem->setMnemonicKey(KeyEvent::KEY_A);
    endEditCP(_AnimationItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

		beginEditCP(_PauseActiveUpdatesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _PauseActiveUpdatesItem->setText("Pause Active Updates");
        _PauseActiveUpdatesItem->setAcceleratorKey(KeyEvent::KEY_SPACE);
        //_PauseActiveUpdatesItem->setMnemonicKey(KeyEvent::KEY_SPACE);
    endEditCP(_PauseActiveUpdatesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_DrawBoundingVolumesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _DrawBoundingVolumesItem->setText("Draw Bounding Volumes");
        _DrawBoundingVolumesItem->setAcceleratorKey(KeyEvent::KEY_V);
        _DrawBoundingVolumesItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL | KeyEvent::KEY_MODIFIER_SHIFT);
        _DrawBoundingVolumesItem->setMnemonicKey(KeyEvent::KEY_V);
    endEditCP(_DrawBoundingVolumesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_FrustrumCullingItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _FrustrumCullingItem->setText("Disable Frustrum Culling ");
        _FrustrumCullingItem->setAcceleratorKey(KeyEvent::KEY_F);
        _FrustrumCullingItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _FrustrumCullingItem->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(_FrustrumCullingItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _DrawPhysicsCharacteristicsItem->setText("Draw Physics Characteristics ");
        _DrawPhysicsCharacteristicsItem->setAcceleratorKey(KeyEvent::KEY_P);
        _DrawPhysicsCharacteristicsItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _DrawPhysicsCharacteristicsItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(_DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);


/*
	beginEditCP(HideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        HideItem->setText("Hide Item");
       // HideItem->setAcceleratorKey(KeyEvent::KEY_H);
       // HideItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
       // HideItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(HideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
*/	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// creation of the Tree
	_HelperPanel = HelperPanel::create();

	_HelperPanel->setupInfoTabPanel();
	_HelperPanel->setupHistoryList();
	_HelperPanel->setupRest();
//	MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&(_HelperPanel->_PlayerKeyListener));


	_HierarchyPanel = HierarchyPanel::create();
	_HierarchyPanel->setApplicationPlayer(ApplicationPlayerPtr(this));
	_HierarchyPanel->createDefaultHierarchyPanel();

	_ContentPanel = ContentPanel::create();
	_ContentPanel->setApplicationPlayer(ApplicationPlayerPtr(this));

	BorderLayoutConstraintsPtr ContentConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(ContentConstraints, BorderLayoutConstraints::RegionFieldMask);
        ContentConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(ContentConstraints, BorderLayoutConstraints::RegionFieldMask);
	
	beginEditCP(_ContentPanel, Panel::ConstraintsFieldMask);
        _ContentPanel->setConstraints(ContentConstraints);
	endEditCP(_ContentPanel, Panel::ConstraintsFieldMask);
    _ContentPanel->init();

	_OpenFileButton = Button::create();

	beginEditCP(_OpenFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	_OpenFileButton->setText("Open File");
	//_OpenFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(_OpenFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	
	_OpenFileButton->addActionListener(&_BasicListener);
		
	_SaveFileButton = Button::create();

	beginEditCP(_SaveFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	_SaveFileButton->setText("Save File");
	//_SaveFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(_SaveFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);

	_SaveFileButton->addActionListener(&_BasicListener);

	/*_CloseFileButton = Button::create();

	beginEditCP(_CloseFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	_CloseFileButton->setText("Close File");
	_CloseFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(_CloseFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);

	_CloseFileButton->addActionListener(&_BasicListener);
	*/

	_ModeComboBox = ComboBox::create();


	BorderLayoutConstraintsPtr ToolbarConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(ToolbarConstraints, BorderLayoutConstraints::RegionFieldMask);
        ToolbarConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    endEditCP(ToolbarConstraints, BorderLayoutConstraints::RegionFieldMask);

	_Toolbar = Panel::create();
	
	beginEditCP(_Toolbar,Panel::PreferredSizeFieldMask);
        _Toolbar->setConstraints(ToolbarConstraints);
        _Toolbar->setPreferredSize(Vec2f(200,40));
	endEditCP(_Toolbar,Panel::PreferredSizeFieldMask);

	FlowLayoutPtr ToolbarLayout = osg::FlowLayout::create();
	beginEditCP(ToolbarLayout,FlowLayout::OrientationFieldMask |
                               FlowLayout::MajorAxisAlignmentFieldMask);
        ToolbarLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        ToolbarLayout->setMajorAxisAlignment(1.0);
	endEditCP(ToolbarLayout,FlowLayout::OrientationFieldMask |
                               FlowLayout::MajorAxisAlignmentFieldMask);

	beginEditCP(_Toolbar,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        _Toolbar->getChildren().push_back(_OpenFileButton);
        _Toolbar->getChildren().push_back(_SaveFileButton);
        _Toolbar->getChildren().push_back(_ModeComboBox);
        _Toolbar->setLayout(ToolbarLayout);
	endEditCP(_Toolbar,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);


	// creation of menus and addition of menu items to them
	_ProjectMenu = Menu::create();
    _ProjectMenu->addItem(_ResetItem);
	_ProjectMenu->addSeparator();
    _ProjectMenu->addItem(_ForceQuitItem);
    
	_EditMenu = Menu::create();
    _EditMenu->addItem(_UndoItem);
	_EditMenu->addItem(_RedoItem);
    
	
	_SceneMenu = Menu::create();
    _SceneMenu->addItem(_NextItem);
    _SceneMenu->addItem(_PrevItem);
	_SceneMenu->addItem(_FirstItem);
	_SceneMenu->addItem(_LastItem);
	_SceneMenu->addSeparator();
	_SceneMenu->addItem(_SceneSubItem);
	

	_NavigatorMenu = Menu::create();
    _NavigatorMenu->addItem(_FlyNavigatorItem);
    _NavigatorMenu->addItem(_TrackballNavigatorItem);

	_StatisticsMenu = Menu::create();
    _StatisticsMenu->addItem(_BasicItem);
    _StatisticsMenu->addItem(_RenderItem);
	_StatisticsMenu->addItem(_PhysicsItem);
	_StatisticsMenu->addItem(_ParticleSystemItem);
	_StatisticsMenu->addItem(_AnimationItem);

	_ToggleMenu = Menu::create();
	_ToggleMenu->addItem(_PauseActiveUpdatesItem);
	_ToggleMenu->addItem(_DrawBoundingVolumesItem);
	_ToggleMenu->addItem(_FrustrumCullingItem);
	_ToggleMenu->addItem(_DrawPhysicsCharacteristicsItem);

	// setting the fields for the menus 
	beginEditCP(_ProjectMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ProjectMenu->setText("Project");
        _ProjectMenu->setMnemonicKey(KeyEvent::KEY_P);
	endEditCP(_ProjectMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_EditMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _EditMenu->setText("Edit");
        _EditMenu->setMnemonicKey(KeyEvent::KEY_D);
	endEditCP(_EditMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_SceneMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _SceneMenu->setText("Scene");
        _SceneMenu->setMnemonicKey(KeyEvent::KEY_C);
	endEditCP(_SceneMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_NavigatorMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _NavigatorMenu->setText("Navigator");
        _NavigatorMenu->setMnemonicKey(KeyEvent::KEY_N);
	endEditCP(_NavigatorMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_StatisticsMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _StatisticsMenu->setText("Statistics");
        _StatisticsMenu->setMnemonicKey(KeyEvent::KEY_T);
	endEditCP(_StatisticsMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_ToggleMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ToggleMenu->setText("Toggle");
        _ToggleMenu->setMnemonicKey(KeyEvent::KEY_G);
	endEditCP(_ToggleMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

	// adding actionlisteners to each of the menuitems
	_ResetItem->addActionListener(&_BasicListener);
	_ForceQuitItem->addActionListener(&_BasicListener);
	
	_NextItem->addActionListener(&_BasicListener);
	_PrevItem->addActionListener(&_BasicListener);
	_FirstItem->addActionListener(&_BasicListener);
	_LastItem->addActionListener(&_BasicListener);
	_FlyNavigatorItem->addActionListener(&_BasicListener);
	_TrackballNavigatorItem->addActionListener(&_BasicListener);
	_BasicItem->addActionListener(&_BasicListener);
    _RenderItem->addActionListener(&_BasicListener);
    _PhysicsItem->addActionListener(&_BasicListener);
	_ParticleSystemItem->addActionListener(&_BasicListener);
	_AnimationItem->addActionListener(&_BasicListener);
	_PauseActiveUpdatesItem->addActionListener(&_BasicListener);
	_DrawBoundingVolumesItem->addActionListener(&_BasicListener);
	_FrustrumCullingItem->addActionListener(&_BasicListener);
	_DrawPhysicsCharacteristicsItem->addActionListener(&_BasicListener);
	_ProjectMenu->addActionListener(&_BasicListener);
	_EditMenu->addActionListener(&_BasicListener);
	_SceneMenu->addActionListener(&_BasicListener);	
	_NavigatorMenu->addActionListener(&_BasicListener);
	_StatisticsMenu->addActionListener(&_BasicListener);
	_ToggleMenu->addActionListener(&_BasicListener);

	_UndoActionListener = CommandActionListenerForPlayer(UndoCommandOfPlayer::create(ApplicationPlayerPtr(this)), _TheCommandManager);
	_RedoActionListener = CommandActionListenerForPlayer(RedoCommandOfPlayer::create(ApplicationPlayerPtr(this)), _TheCommandManager);

	
	_UndoItem->addActionListener(&_UndoActionListener);
	_RedoItem->addActionListener(&_RedoActionListener);

	// Creation of the menubar and addition of the menus to it
	_MainMenuBar = MenuBar::create();
    _MainMenuBar->addMenu(_ProjectMenu);
	_MainMenuBar->addMenu(_EditMenu);
	_MainMenuBar->addMenu(_SceneMenu);
	_MainMenuBar->addMenu(_NavigatorMenu);
	_MainMenuBar->addMenu(_StatisticsMenu);
	_MainMenuBar->addMenu(_ToggleMenu);
  
	//ToolbarLayout2= osg::BorderLayout::create();

	beginEditCP(_HierarchyPanel,Panel::PreferredSizeFieldMask);
		_HierarchyPanel->setPreferredSize(Vec2f(400,700));
	endEditCP(_HierarchyPanel,Panel::PreferredSizeFieldMask);

	_ModeComboBoxModel = DefaultMutableComboBoxModel::create();
	_ModeComboBoxModel->addElement(boost::any(std::string("Scene Graph")));
	_ModeComboBoxModel->addElement(boost::any(std::string("Lua Graph")));
	
	beginEditCP(_ModeComboBox, ComboBox::ModelFieldMask | ComboBox::MinSizeFieldMask  | ComboBox::EditableFieldMask);
		_ModeComboBox->setMinSize(Vec2f(100.0,20));
		_ModeComboBox->setEditable(false);
		_ModeComboBox->setModel(_ModeComboBoxModel);
	endEditCP(_ModeComboBox, ComboBox::ModelFieldMask);
	
	//_ModeComboBox->addActionListener(&_BasicListener);
	_ModeComboBoxModel->addSelectionListener(&_ComboBoxListener);
			
	// Determine where the _ModeComboBox starts
	_ModeComboBox->setSelectedIndex(0);
	
	setupPopupMenu();

	/*************************************************** _DebugWindowSplitPanel creation **********************************************************************/

    BorderLayoutPtr ToolbarAndContentPanelLayout = BorderLayout::create();

	_ToolbarAndContentPanel = osg::Panel::createEmpty();

	beginEditCP(_ToolbarAndContentPanel, Panel::ChildrenFieldMask |
                Panel::LayoutFieldMask);
        _ToolbarAndContentPanel->setLayout(ToolbarAndContentPanelLayout);
        _ToolbarAndContentPanel->getChildren().push_back(_Toolbar);
		_ToolbarAndContentPanel->getChildren().push_back(_ContentPanel);
	endEditCP(_ToolbarAndContentPanel, Panel::ChildrenFieldMask |
                Panel::LayoutFieldMask);

	_TopHalfSplitPanel = osg::SplitPanel::create();

	beginEditCP(_TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        _TopHalfSplitPanel->setMinComponent(_HierarchyPanel);
		_TopHalfSplitPanel->setMaxComponent(_ToolbarAndContentPanel);
        _TopHalfSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
        _TopHalfSplitPanel->setDividerPosition(350.0f); 
        // location from the left/top
        _TopHalfSplitPanel->setDividerSize(5);
        //_TopHalfSplitPanel->setExpandable(true);
        _TopHalfSplitPanel->setMaxDividerPosition(.85);
        _TopHalfSplitPanel->setMinDividerPosition(150.0f);
    endEditCP(_TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);

	_DebugWindowSplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(_DebugWindowSplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        _DebugWindowSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(_DebugWindowSplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
    
	_DebugWindowSplitPanel = osg::SplitPanel::create();

	beginEditCP(_DebugWindowSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        _DebugWindowSplitPanel->setConstraints(_DebugWindowSplitPanelConstraints);
        _DebugWindowSplitPanel->setMaxComponent(_HelperPanel);//->SplitPanelPanel);
		_DebugWindowSplitPanel->setMinComponent(_TopHalfSplitPanel);
        _DebugWindowSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        _DebugWindowSplitPanel->setDividerPosition(.75); 
        // location from the left/top
        _DebugWindowSplitPanel->setDividerSize(5);
        // _DebugWindowSplitPanel->setExpandable(false);
        _DebugWindowSplitPanel->setMaxDividerPosition(.95);
        _DebugWindowSplitPanel->setMinDividerPosition(.15);
    endEditCP(_DebugWindowSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
	/*************************************************** END _DebugWindowSplitPanel creation **********************************************************************/
	
	/*************************************************** MainInternalWindow creation*************************************************************/
	
	BorderLayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();

    beginEditCP(MainInternalWindowLayout);
        // Nothing
    endEditCP(MainInternalWindowLayout);

    // Create The Main InternalWindow


    MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::MenuBarFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
	   MainInternalWindow->getChildren().push_back(_DebugWindowSplitPanel);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(NullFC);
       MainInternalWindow->setBorders(NullFC);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setMenuBar(_MainMenuBar);
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::MenuBarFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	MainInternalWindow->setFocusedComponent(_HelperPanel->_CodeTextArea);

	/*************************************************** END MainInternalWindow creation*************************************************************/
	
	
	// Create the DrawingSurface Object
	DebuggerDrawingSurface = UIDrawingSurface::create();
    beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        DebuggerDrawingSurface->setGraphics(DebuggerGraphics);
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	DebuggerDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    DebuggerUIForeground = osg::UIForeground::create();

    beginEditCP(DebuggerUIForeground, UIForeground::DrawingSurfaceFieldMask);
        DebuggerUIForeground->setDrawingSurface(DebuggerDrawingSurface);
    endEditCP(DebuggerUIForeground, UIForeground::DrawingSurfaceFieldMask);

    //Create the Viewport
    _DebugViewport = createDebugViewport();
    addRefCP(_DebugViewport);

    //Create the Debug Camera Animation Group
    createDebugCameraAnim();
}

void ApplicationPlayer::updateGotoSceneMenuItems(ProjectPtr TheProject)
{
    ScenePtr CurrentlyActiveScene = TheProject->getActiveScene();
    ScenePtr GotoItemScene;
    MenuItemPtr GotoItem;

    //Disable the Goto Menu Item for the currently active Scene
    for(UInt32 i(0) ; i<_SceneSubItem->getNumItems() ; ++i)
    {
        GotoItem = _SceneSubItem->getItem(i);
        GotoItemScene = TheProject->getSceneByName(GotoItem->getText());
        if(CurrentlyActiveScene == GotoItemScene
                && GotoItem->getEnabled())
        {
            beginEditCP(GotoItem, MenuItem::EnabledFieldMask);
                GotoItem->setEnabled(false);
            endEditCP(GotoItem, MenuItem::EnabledFieldMask);
        }
        else if(CurrentlyActiveScene != GotoItemScene
                && !GotoItem->getEnabled())
        {
            beginEditCP(GotoItem, MenuItem::EnabledFieldMask);
                GotoItem->setEnabled(true);
            endEditCP(GotoItem, MenuItem::EnabledFieldMask);
        }
    }
}

void ApplicationPlayer::createGotoSceneMenuItems(ProjectPtr TheProject)
{
    //Clear all of the previous Items
    _SceneSubItem->removeAllItems();

    //Make a Menu Item for each of the scenes
    const Char8* SceneCharName(NULL);
    std::string SceneName;
    MenuItemPtr NewSceneItem;
    for(UInt32 i(0) ; i<TheProject->getScenes().size() ; ++i)
    {
        //Get the Name of the Scene
        SceneCharName = getName(TheProject->getScenes(i));

        if(SceneCharName == NULL)
        {
            SceneName = "UNTITLED SCENE";
        }
        else
        {
            SceneName = SceneCharName;
        }
        
        //Create the menu Item
        NewSceneItem = MenuItem::create();
        beginEditCP(NewSceneItem, MenuItem::TextFieldMask);
            NewSceneItem->setText(SceneName);
        endEditCP(NewSceneItem, MenuItem::TextFieldMask);
        //Attach the Goto Listener
        NewSceneItem->addActionListener(&_GotoSceneItemListener);

        //Add the Scene Menu Item to the SubMenu
        _SceneSubItem->addItem(NewSceneItem);
    }
}

void ApplicationPlayer::attachDebugInterface(void)
{
	if( MainApplication::the()->getProject()->getActiveScene()->getMFViewports()->size() == 0 ||
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0) == NullFC)
	{
		SWARNING << "ApplicationPlayer::attachDebugInterface(): No Viewports in current scene.  There should be at least one defined." << std::endl;
	}
	else
	{
		if(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot() == NullFC)
		{
			SWARNING << "ApplicationPlayer::attachDebugInterface(): No root for current viewport!" << std::endl;
		}
		else
		{
			if(_HierarchyPanel->getSceneGraphTreeModel()->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
			{
				_HierarchyPanel->getSceneGraphTreeModel()->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
			}
		}
		
    }
	
    _HierarchyPanel->_SceneGraphTreeSelectionListener.setParams(_HierarchyPanel->getSceneGraphTree(),ApplicationPlayerPtr(this));
	updateHighlightNode();
	beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    	DebuggerDrawingSurface->setEventProducer(MainApplication::the()->getMainWindowEventProducer());
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);

    attachDebugViewport();
	
	//MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().push_back(DebuggerUIForeground);
}


void ApplicationPlayer::detachDebugInterface(void)
{

	beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        DebuggerDrawingSurface->setEventProducer(NullFC);
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
    detachDebugViewport();
}

void ApplicationPlayer::enableDebug(bool EnableDebug)
{
    if(EnableDebug && !_IsDebugActive)
    {
        //Attach the Interface
		attachDebugInterface();

        updateGotoSceneMenuItems(MainApplication::the()->getProject());

        //Attach Listeners to the project
        MainApplication::the()->getProject()->editEventProducer()->attachEventListener(&_ProjectListener, Project::SceneChangedMethodId);
		_CommandManagerListener.setApplicationPlayer(ApplicationPlayerPtr(this));
		updateUndoRedoInterfaces(_TheUndoManager);

        //Update Title
        updateWindowTitle();

        //Turn on Input Blocking
        setSceneInputBlocking(true);

        _WasMouseHidden = !MainApplication::the()->getMainWindowEventProducer()->getShowCursor();
        if(_WasMouseHidden)
        {
            MainApplication::the()->getMainWindowEventProducer()->setShowCursor(true);
        }
        _WasMouseAttached = !MainApplication::the()->getMainWindowEventProducer()->getAttachMouseToCursor();
		
        if(_WasMouseAttached)
        {
            MainApplication::the()->getMainWindowEventProducer()->setAttachMouseToCursor(true);
        }
    }
    else if(!EnableDebug && _IsDebugActive)
    {
		detachDebugInterface();

        //dettach Listeners to the project
        MainApplication::the()->getProject()->editEventProducer()->detachEventListener(&_ProjectListener, Project::SceneChangedMethodId);

        //Turn off Input Blocking
        setSceneInputBlocking(false);

        //Update Title
        updateWindowTitle();

        if(_WasMouseHidden)
        {
            MainApplication::the()->getMainWindowEventProducer()->setShowCursor(false);
        }
        if(_WasMouseAttached)
        {
            MainApplication::the()->getMainWindowEventProducer()->setAttachMouseToCursor(false);
        }
    }
    _IsDebugActive = EnableDebug;
}

void ApplicationPlayer::updateWindowTitle(void)
{
    std::string MainWindowTitle(MainApplication::the()->getProject()->getMainWindowTitle());
    if(_IsDebugActive)
    {
        MainWindowTitle += "(Debug)";
    }
    if(MainApplication::the()->getProject()->isInputBlocked())
    {
        MainWindowTitle += "(Input Blocked)";
    }
    MainApplication::the()->getMainWindowEventProducer()->setTitle(MainWindowTitle);
}

void ApplicationPlayer::actionPerformed(const ActionEventPtr e)
{
	if(e->getSource() == _ResetItem)
	{
		//Reset the Project
            MainApplication::the()->getProject()->reset();
            MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getLastActiveScene());
	}
	else if(e->getSource() == _ForceQuitItem)
	{
			MainApplication::the()->exit();
	}

	else if(e->getSource() == _NextItem)
	{
			MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().find(MainApplication::the()->getProject()->getActiveScene()));
			SearchItor++;
			if(SearchItor == MainApplication::the()->getProject()->getScenes().end())
				SearchItor = MainApplication::the()->getProject()->getScenes().begin();
			MainApplication::the()->getProject()->setActiveScene(*SearchItor);
    
	}
	else if(e->getSource() == _PrevItem)
	{
			MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().find(MainApplication::the()->getProject()->getActiveScene()));
            if(SearchItor != MainApplication::the()->getProject()->getScenes().end())
            {
                if(SearchItor == MainApplication::the()->getProject()->getScenes().begin())
                {
                    SearchItor = MainApplication::the()->getProject()->getScenes().end();
                }
                if(MainApplication::the()->getProject()->getScenes().size() > 1)
                {	
                    --SearchItor;
                }
            }
            else
            {
                SearchItor = MainApplication::the()->getProject()->getScenes().begin();
            }
            MainApplication::the()->getProject()->setActiveScene(*SearchItor);
	}
	else if(e->getSource() == _FirstItem)
	{
		MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
        MainApplication::the()->getProject()->setActiveScene(*SearchItor);

	}

	else if(e->getSource() == _LastItem)
	{

		UInt32 SceneNumber = MainApplication::the()->getProject()->getScenes().size();
		MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
        SearchItor = SearchItor + SceneNumber - 1;
		MainApplication::the()->getProject()->setActiveScene(*SearchItor);
	}
	else if(e->getSource() == _FlyNavigatorItem )
	{
		MainApplication::the()->getProject()->toggleFlyNavigation();
	}
	else if(e->getSource() == _TrackballNavigatorItem )
	{
	
	}
	else if(e->getSource() == _BasicItem)
	{
		toggleStatForeground(_DebugBasicStatForeground);
	}
	else if(e->getSource() == _RenderItem)
	{
		toggleStatForeground(_DebugRenderStatForeground);
	}
	else if(e->getSource() == _PhysicsItem)
	{
		toggleStatForeground(_DebugPhysicsStatForeground);
	}
	else if(e->getSource() == _ParticleSystemItem)
	{
		toggleStatForeground(_DebugParticleSystemStatForeground);
	}
	else if(e->getSource() == _AnimationItem)
	{
		toggleStatForeground(_DebugAnimationStatForeground);
	}
	else if(e->getSource() == _PauseActiveUpdatesItem)
	{
		MainApplication::the()->getProject()->togglePauseActiveUpdates();
        
        //Update the Menu Item
        beginEditCP(_PauseActiveUpdatesItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getProject()->getPauseActiveUpdates())
        {
            _PauseActiveUpdatesItem->setText("Unpause Active Updates");
        }
        else
        {
            _PauseActiveUpdatesItem->setText("Pause Active Updates");
        }
        endEditCP(_PauseActiveUpdatesItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == _DrawBoundingVolumesItem)
	{
		toggleDrawBoundingVolumes();

        //Update the Menu Item
        beginEditCP(_DrawBoundingVolumesItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->getVolumeDrawing())
        {
            _DrawBoundingVolumesItem->setText("Hide Bounding Volumes");
        }
        else
        {
            _DrawBoundingVolumesItem->setText("Draw Bounding Volumes");
        }
        endEditCP(_DrawBoundingVolumesItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == _FrustrumCullingItem)
	{
		toggleFrustumCulling();

        //Update the Menu Item
        beginEditCP(_FrustrumCullingItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->getFrustumCulling())
        {
            _FrustrumCullingItem->setText("Disable Frustrum Culling");
        }
        else
        {
            _FrustrumCullingItem->setText("Enable Frustrum Culling");
        }
        endEditCP(_FrustrumCullingItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == _DrawPhysicsCharacteristicsItem)
	{
		toggleDrawPhysicsCharacteristics();

        //Update the Menu Item
        //Add the Physics Drawable Node to the project
        beginEditCP(_DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->findChild(getPhysicsDrawableNode()) < 0)
        {
            _DrawPhysicsCharacteristicsItem->setText("Draw Physics Characteristics");
        }
        else
        {
            _DrawPhysicsCharacteristicsItem->setText("Hide Physics Characteristics");
        }
        endEditCP(_DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == _ModeComboBox)
	{
        int index = _ModeComboBox->getSelectedIndex();
        _HierarchyPanel->setView(index);
        _ContentPanel->setView(index);
	}
	else if(e->getSource() == _OpenFileButton)
	{
		
		std::vector<WindowEventProducer::FileDialogFilter> Filters;
		Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		
		std::vector<Path> FilesToOpen;
		FilesToOpen = MainApplication::the()->getMainWindowEventProducer()->openFileDialog("Open File Window",
			Filters,
			Path(".."),
			true);

        for(std::vector<Path>::iterator Itor(FilesToOpen.begin()) ; Itor != FilesToOpen.end(); ++Itor)
        {
			_ContentPanel->addTabWithText(*Itor);
        }
	}
	else if(e->getSource() == _SaveFileButton)
	{
		std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		Path SavePath = MainApplication::the()->getMainWindowEventProducer()->saveFileDialog("Save File Window",
			Filters,
			std::string("NewLuaFile.lua"),
			Path(".."),
			true);
        
		_ContentPanel->saveTextFile(SavePath);
	}
	else
	{
		//do nothing
	}
}



void ApplicationPlayer::keyTyped(const KeyEventPtr e)
{
    if(e->getKey() == KeyEvent::KEY_D && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL && e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
    {
        enableDebug(!_IsDebugActive);
        return;
    }

    if(_IsDebugActive)
    {

	
        if(isNumericKey(static_cast<KeyEvent::Key>(e->getKey())) && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL && e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
            //Switch To scene #
            UInt32 SceneNumber(boost::lexical_cast<UInt32>(KeyEvent::getCharFromKey(e->getKey(),0)));
            if(SceneNumber < MainApplication::the()->getProject()->getScenes().size())
            {
                MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
                SearchItor = SearchItor + SceneNumber;
                MainApplication::the()->getProject()->setActiveScene(*SearchItor);
            }
        }
		
		if(e->getKey() == KeyEvent::KEY_1 && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
		{
			MainInternalWindow->setFocusedComponent(_HelperPanel->_CodeTextArea);
			_HelperPanel->_InfoTabPanel->setSelectedIndex(0);

		}

		if(e->getKey() == KeyEvent::KEY_T && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
		{
			_ContentPanel->setIsSplit(!_ContentPanel->getIsSplit());
		}

        //Pause Active Updates
        //else if(e->getKey() == KeyEvent::KEY_SPACE)
        //{
            //MainApplication::the()->getProject()->togglePauseActiveUpdates();
        //}

        ////Toggle Input Blocking
        else if(e->getKey() == KeyEvent::KEY_I && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
        {
            toggleSceneInputBlocking();
        }

        //Scene Activation
        if(e->getKey() == KeyEvent::KEY_E && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
        {
            //Reset the Project
            MainApplication::the()->getProject()->reset();
            MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getLastActiveScene());
        }
    }
}

void ApplicationPlayer::toggleSceneInputBlocking(void)
{
    setSceneInputBlocking(!MainApplication::the()->getProject()->isInputBlocked());
}

void ApplicationPlayer::setSceneInputBlocking(bool block)
{
    MainApplication::the()->getProject()->blockInput(block);
    for(UInt32 i(0) ; i<MainApplication::the()->getProject()->getScenes().size(); ++i)
    {
        MainApplication::the()->getProject()->getScenes(i)->blockInput(block);
    }
    updateWindowTitle();
}

void ApplicationPlayer::toggleDrawBoundingVolumes(void)
{
    MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->setVolumeDrawing(!MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->getVolumeDrawing());
}

void ApplicationPlayer::toggleDrawPhysicsCharacteristics(void)
{
    NodePtr CurrentRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
    NodePtr PhysNode(getPhysicsDrawableNode());

    //Get the Root Node of the Project
    beginEditCP(_PhysDrawable, PhysicsCharacteristicsDrawable::RootFieldMask);
        _PhysDrawable->setRoot(CurrentRoot);
    endEditCP(_PhysDrawable, PhysicsCharacteristicsDrawable::RootFieldMask);

    //Add the Physics Drawable Node to the project
    beginEditCP(CurrentRoot, Node::ChildrenFieldMask);
        if(CurrentRoot->findChild(PhysNode) < 0)
        {
            CurrentRoot->addChild(PhysNode);
        }
        else
        {
            CurrentRoot->subChild(PhysNode);
        }
    endEditCP(CurrentRoot, Node::ChildrenFieldMask);
}


NodePtr ApplicationPlayer::getPhysicsDrawableNode(void)
{
    if(_PhysDrawable == NullFC)
    {
        //Make The Physics Characteristics Core
        _PhysDrawable = PhysicsCharacteristicsDrawable::create();
    }
    if(_PhysDrawableNode == NullFC)
    {
        //Make The Physics Characteristics Node
        _PhysDrawableNode = Node::create();
        beginEditCP(_PhysDrawableNode, Node::CoreFieldMask);
            _PhysDrawableNode->setCore(_PhysDrawable);
        endEditCP  (_PhysDrawableNode, Node::CoreFieldMask);
        addRefCP(_PhysDrawableNode);
    }
    return _PhysDrawableNode;
}

void ApplicationPlayer::gotoScene(ScenePtr TheScene)
{
    MainApplication::the()->getProject()->setActiveScene(TheScene);
}

void ApplicationPlayer::toggleFrustumCulling(void)
{
    MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->setFrustumCulling(!MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->getFrustumCulling());
}

void ApplicationPlayer::toggleStatForeground(StatisticsForegroundPtr TheForeground)
{
    MFForegroundPtr::iterator SearchItor(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().find(TheForeground));
    if( SearchItor != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().end())
    {
        //If the Stat foreground is present then switch it off
        beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0), Viewport::ForegroundsFieldMask);
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().erase(SearchItor);
        endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0), Viewport::ForegroundsFieldMask);
    }
    else
    {
        //If not present then switch all other stat foregrounds off
        hideAllStatForegrounds();

        //and switch it on
        beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0), Viewport::ForegroundsFieldMask);
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().push_back(TheForeground);
        endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0), Viewport::ForegroundsFieldMask);

        MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->setStatistics(&TheForeground->getCollector());
    }
}

void ApplicationPlayer::hideAllStatForegrounds(void)
{
    
    MFForegroundPtr::iterator SearchItor;

    beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0), Viewport::ForegroundsFieldMask);
        //Hide Basic Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().find(_DebugBasicStatForeground)) != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().erase(SearchItor);
        }
        //Hide Render Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().find(_DebugRenderStatForeground)) != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().erase(SearchItor);
        }
        //Hide Physics Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().find(_DebugPhysicsStatForeground)) != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().erase(SearchItor);
        }
        //Hide Particle System Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().find(_DebugParticleSystemStatForeground)) != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().erase(SearchItor);
        }
        //Hide Animation Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().find(_DebugAnimationStatForeground)) != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getForegrounds().erase(SearchItor);
        }
    endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0), Viewport::ForegroundsFieldMask);
}

void ApplicationPlayer::initDebugStatForegrounds(void)
{
    Color4f StatColor(0.9f,0.9f,0.9f,0.8f),
            StatShadowColor(0.0f,0.0f,0.0f,0.8f),
            StatBorderColor(0.9f,0.9f,0.9f,0.8f),
            StatBackgroundColor(0.0f,0.0f,0.0f,0.7f);

    UInt32 StatFontSize(25);

    //Basic Statistics
    _DebugBasicStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugBasicStatForeground);
		_DebugBasicStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
		_DebugBasicStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
        _DebugBasicStatForeground->setSize(StatFontSize);
        _DebugBasicStatForeground->setColor(StatColor);
        _DebugBasicStatForeground->setShadowColor(StatShadowColor);
        _DebugBasicStatForeground->setBgColor(StatBackgroundColor);
        _DebugBasicStatForeground->setBorderColor(StatBorderColor);
        _DebugBasicStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        _DebugBasicStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugBasicStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
    endEditCP(_DebugBasicStatForeground);
    addRefCP(_DebugBasicStatForeground);
    
    //Rendering Statistics
    _DebugRenderStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugRenderStatForeground);
		_DebugRenderStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
		_DebugRenderStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
        _DebugRenderStatForeground->setSize(StatFontSize);
        _DebugRenderStatForeground->setColor(StatColor);
        _DebugRenderStatForeground->setShadowColor(StatShadowColor);
        _DebugRenderStatForeground->setBgColor(StatBackgroundColor);
        _DebugRenderStatForeground->setBorderColor(StatBorderColor);
		_DebugRenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        _DebugRenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugRenderStatForeground->addElement(DrawActionBase::statTravTime, "TravTime: %.3f s");
        _DebugRenderStatForeground->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
        _DebugRenderStatForeground->addElement(DrawActionBase::statCullTestedNodes, "%d Nodes culltested");
        _DebugRenderStatForeground->addElement(DrawActionBase::statCulledNodes, "%d Nodes culled");
        _DebugRenderStatForeground->addElement(RenderAction::statNMaterials, "%d material changes");
        _DebugRenderStatForeground->addElement(RenderAction::statNMatrices, "%d matrix changes");
        _DebugRenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugRenderStatForeground->addElement(RenderAction::statNTransGeometries, "%d transparent Nodes drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNLines, "%d lines drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNPoints, "%d points drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNPrimitives,"%d primitive groups drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNVertices, "%d vertices transformed");
        _DebugRenderStatForeground->addElement(Drawable::statNGeoBytes, "%d bytes of geometry used");
        _DebugRenderStatForeground->addElement(RenderAction::statNTextures, "%d textures used");
        _DebugRenderStatForeground->addElement(RenderAction::statNTexBytes, "%d bytes of texture used");
    endEditCP(_DebugRenderStatForeground);
    addRefCP(_DebugRenderStatForeground);
    
    //Physics Statistics
    _DebugPhysicsStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugPhysicsStatForeground);
		_DebugPhysicsStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
		_DebugPhysicsStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
        _DebugPhysicsStatForeground->setSize(StatFontSize);
        _DebugPhysicsStatForeground->setColor(StatColor);
        _DebugPhysicsStatForeground->setShadowColor(StatShadowColor);
        _DebugPhysicsStatForeground->setBgColor(StatBackgroundColor);
        _DebugPhysicsStatForeground->setBorderColor(StatBorderColor);
        _DebugPhysicsStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugPhysicsStatForeground);
    addRefCP(_DebugPhysicsStatForeground);
    
    //Particle System Statistics
    _DebugParticleSystemStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugParticleSystemStatForeground);
		_DebugParticleSystemStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
		_DebugParticleSystemStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
        _DebugParticleSystemStatForeground->setSize(StatFontSize);
        _DebugParticleSystemStatForeground->setColor(StatColor);
        _DebugParticleSystemStatForeground->setShadowColor(StatShadowColor);
        _DebugParticleSystemStatForeground->setBgColor(StatBackgroundColor);
        _DebugParticleSystemStatForeground->setBorderColor(StatBorderColor);
        _DebugParticleSystemStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugParticleSystemStatForeground);
    addRefCP(_DebugParticleSystemStatForeground);
    
    //Animation Statistics
    _DebugAnimationStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugAnimationStatForeground);
		_DebugAnimationStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
		_DebugAnimationStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
        _DebugAnimationStatForeground->setSize(StatFontSize);
        _DebugAnimationStatForeground->setColor(StatColor);
        _DebugAnimationStatForeground->setShadowColor(StatShadowColor);
        _DebugAnimationStatForeground->setBgColor(StatBackgroundColor);
        _DebugAnimationStatForeground->setBorderColor(StatBorderColor);
        _DebugAnimationStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugAnimationStatForeground);
    addRefCP(_DebugAnimationStatForeground);
}

void ApplicationPlayer::updateDebugUI(void)
{
    updateGotoSceneMenuItems(MainApplication::the()->getProject());
	//TODO: Update the Scene Node Tree
	if(_HierarchyPanel->getSceneGraphTreeModel()->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
	{
		_HierarchyPanel->getSceneGraphTreeModel()->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
	}
	
	//_HierarchyPanel->_SceneGraphTreeSelectionListener.setParams(_HierarchyPanel->_TheSceneGraphTree,ApplicationPlayerPtr(this));
	updateHighlightNode();
	
}

void ApplicationPlayer::updateDebugSceneChange(void)
{
	//Update the UI for the debug interface
	updateDebugUI();

	_WasMouseHidden = !MainApplication::the()->getMainWindowEventProducer()->getShowCursor();
	if(_WasMouseHidden)
	{
		MainApplication::the()->getMainWindowEventProducer()->setShowCursor(true);
	}
	_WasMouseAttached = !MainApplication::the()->getMainWindowEventProducer()->getAttachMouseToCursor();

	if(_WasMouseAttached)
	{
		MainApplication::the()->getMainWindowEventProducer()->setAttachMouseToCursor(true);
	}

	if(_IsDebugActive)
	{
		setSceneInputBlocking(true);
	}
    
    updateDebugViewport();
    
}

void ApplicationPlayer::detachDebugViewport(void)
{
	//Make sure the Debug Viewport is on top
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(_DebugViewport);

    //Put the original Camera back on the Scene's Viewport
    beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0),Viewport::CameraFieldMask);
        MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->setCamera(_SceneViewportCamera);
    endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0),Viewport::CameraFieldMask);
}

void ApplicationPlayer::updateDebugViewport(void)
{
    //Update The Camera
	_SceneViewportCamera = MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getCamera();

	_DebugCamera = CameraPtr::dcast(_SceneViewportCamera->shallowCopy());
    beginEditCP(_DebugCamera, Camera::BeaconFieldMask);
        _DebugCamera->setBeacon(_DebugCameraBeacon);
    endEditCP(_DebugCamera, Camera::BeaconFieldMask);

    //Put the Camera Beacon to the beacon of the scene's camera
    _DebugSceneNavigator.set(_SceneViewportCamera->getBeacon()->getToWorld());

    //Put the Debug Camera on the Scene's Viewport
    beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0),Viewport::CameraFieldMask);
        MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->setCamera(_DebugCamera);
    endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0),Viewport::CameraFieldMask);

	beginEditCP(_DebugViewport, Viewport::CameraFieldMask);
        _DebugViewport->setCamera(_DebugCamera);
	endEditCP(_DebugViewport, Viewport::CameraFieldMask);

	//Make sure the Debug Viewport is on top
    beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(),
                Window::PortFieldMask);
        MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(_DebugViewport);
        MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(_DebugViewport);
    endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(),
                Window::PortFieldMask);
}

void ApplicationPlayer::attachDebugViewport(void)
{
    updateDebugViewport();
}

ViewportPtr ApplicationPlayer::createDebugViewport(void)
{
    //Create the Highlight Node
    createHighlightNode();

    //Camera Transformation Node	
	_DebugBeaconTransform = Transform::create();

	_DebugCameraBeacon = osg::Node::create();
    beginEditCP(_DebugCameraBeacon, Node::CoreFieldMask);
        _DebugCameraBeacon->setCore(_DebugBeaconTransform);
    endEditCP(_DebugCameraBeacon, Node::CoreFieldMask);

    //Debug Root Node
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(_DebugCameraBeacon);
        DefaultRootNode->addChild(_HighlightNode);
    endEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Background
	PassiveBackgroundPtr DefaultBackground = PassiveBackground::create();

    ViewportPtr DebugViewport = Viewport::create();
	
	beginEditCP(DebugViewport);
        DebugViewport->setRoot                    (DefaultRootNode);
        DebugViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
        DebugViewport->setBackground              (DefaultBackground);
        DebugViewport->getForegrounds().push_back (DebuggerUIForeground);
    endEditCP(DebugViewport);

    _DebugSceneNavigator.setMode(Navigator::TRACKBALL);
    _DebugSceneNavigator.setViewport(DebugViewport);
    _DebugSceneNavigator.setCameraTransformation(_DebugCameraBeacon);

    return DebugViewport;
}

void ApplicationPlayer::moveDebugCamera(const Matrix& Transform)
{
    if(_DebugCamera!=NullFC)
    {
        _DebugCameraAnimationGroup->stop();

        //Update The Camera Animation Values
        _DebugCameraTransformationKeyframes->clear();
        _DebugCameraTransformationKeyframes->addKeyframe(_DebugBeaconTransform->getMatrix(),0.0f);
        _DebugCameraTransformationKeyframes->addKeyframe(Transform,1.0f);

        //_DebugCameraFovKeyframes->clear();
        //_DebugCameraFovKeyframes->addKeyframe(PerspectiveCamera::Ptr::dcast(_SceneViewportCamera)->getFov(),0.0f);
        //_DebugCameraFovKeyframes->addKeyframe(PerspectiveCamera::Ptr::dcast(_SceneViewportCamera)->getFov()
                                              //* 1.5f,0.5f);
        //_DebugCameraFovKeyframes->addKeyframe(PerspectiveCamera::Ptr::dcast(_SceneViewportCamera)->getFov(),1.0f);

        //Attach the Debug Camera Animation
        _DebugCameraTransAnimation->setAnimatedField(_DebugBeaconTransform,
                                                     Transform::MatrixFieldId);

        //_DebugCameraFovAnimation->setAnimatedField(_DebugCamera,
                                                   //PerspectiveCamera::FovFieldId);

        _DebugCameraAnimationGroup->attachUpdateProducer(MainApplication::the()->getMainWindowEventProducer()->editEventProducer());

        //Start the Animation
        _DebugCameraAnimationGroup->start();

        //Set The Navigator
        _DebugSceneNavigator.set(Transform);
    }
    else
    {
        if(_DebugCamera==NullFC)
        {
            SWARNING << "Debug Camera is NullFC." << std::endl;
        }
    }
}

void ApplicationPlayer::createDebugCameraAnim(void)
{
    //Transformation Animation
    _DebugCameraTransformationKeyframes = KeyframeTransformationsSequence44f::create();

    KeyframeAnimatorPtr DebugCameraTransformationAnimator = KeyframeAnimator::create();
    beginEditCP(DebugCameraTransformationAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        DebugCameraTransformationAnimator->setKeyframeSequence(_DebugCameraTransformationKeyframes);
    endEditCP(DebugCameraTransformationAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    _DebugCameraTransAnimation = FieldAnimation::create();
    beginEditCP(_DebugCameraTransAnimation);
        _DebugCameraTransAnimation->setAnimator(DebugCameraTransformationAnimator);
        _DebugCameraTransAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        _DebugCameraTransAnimation->setCycling(1);
    endEditCP(_DebugCameraTransAnimation);
    
    //Fov Animation
    //_DebugCameraFovKeyframes = KeyframeNumbersSequenceReal32::create();

    //KeyframeAnimatorPtr DebugCameraFovAnimator = KeyframeAnimator::create();
    //beginEditCP(DebugCameraFovAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        //DebugCameraFovAnimator->setKeyframeSequence(_DebugCameraFovKeyframes);
    //endEditCP(DebugCameraFovAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //_DebugCameraFovAnimation = FieldAnimation::create();
    //beginEditCP(_DebugCameraFovAnimation);
        //_DebugCameraFovAnimation->setAnimator(DebugCameraFovAnimator);
        //_DebugCameraFovAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        //_DebugCameraFovAnimation->setCycling(1);
    //endEditCP(_DebugCameraFovAnimation);

    //Animation Group
    _DebugCameraAnimationGroup = AnimationGroup::create();
    beginEditCP(_DebugCameraAnimationGroup);
        _DebugCameraAnimationGroup->getAnimations().push_back(_DebugCameraTransAnimation);
        //_DebugCameraAnimationGroup->getAnimations().push_back(_DebugCameraFovAnimation);
    endEditCP(_DebugCameraAnimationGroup);
    addRefCP(_DebugCameraAnimationGroup);
}

void ApplicationPlayer::resetDebugCamera(void)
{
    //Put the Camera Beacon to the beacon of the scene's camera
    _DebugSceneNavigator.set(_SceneViewportCamera->getBeacon()->getToWorld());
}

void ApplicationPlayer::updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager)
{
	
	beginEditCP(_UndoItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
		_UndoItem->setEnabled(_TheUndoManager->canUndo());
		if(_TheUndoManager->canUndo())
		{
			_UndoItem->setText(TheUndoManager->getUndoPresentationName());
		}
		else
		{
			_UndoItem->setText("Undo");
		}
	endEditCP(_UndoItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
	
	beginEditCP(_RedoItem, MenuItem::EnabledFieldMask);
		_RedoItem->setEnabled(TheUndoManager->canRedo());
		if(_TheUndoManager->canRedo())
		{
			_RedoItem->setText(_TheUndoManager->getRedoPresentationName());
		}
		else
		{
			_RedoItem->setText("Redo");
		}
	endEditCP(_RedoItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
}


void ApplicationPlayer::setDebugView(UInt32 Index)
{
    _HierarchyPanel->setView(Index);
    _ContentPanel->setView(Index);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationPlayer::ApplicationPlayer(void) :
    Inherited(),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
	_BasicListener(ApplicationPlayerPtr(this)),
	_highlightNodeListener(ApplicationPlayerPtr(this)),
	_ComboBoxListener(ApplicationPlayerPtr(this)),
	_GotoSceneItemListener(ApplicationPlayerPtr(this)),
	_ProjectListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false),
    _PhysDrawable(NullFC),
    _PhysDrawableNode(NullFC),
    _WasMouseHidden(false),
    _WasMouseAttached(false),
	_UndoActionListener(NULL,NULL),
	_RedoActionListener(NULL,NULL),
	_CommandManagerListener(ApplicationPlayerPtr(this))
{
	_TheUndoManager = UndoManager::create();
	_TheCommandManager = CommandManager::create(_TheUndoManager);
	initDebugStatForegrounds();
}

ApplicationPlayer::ApplicationPlayer(const ApplicationPlayer &source) :
    Inherited(source),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
	_BasicListener(ApplicationPlayerPtr(this)),
	_highlightNodeListener(ApplicationPlayerPtr(this)),
	_ComboBoxListener(ApplicationPlayerPtr(this)),
	_GotoSceneItemListener(ApplicationPlayerPtr(this)),
	_ProjectListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false),
    _DebugBasicStatForeground(source._DebugBasicStatForeground),
    _DebugRenderStatForeground(source._DebugRenderStatForeground),
    _DebugPhysicsStatForeground(source._DebugPhysicsStatForeground),
    _DebugParticleSystemStatForeground(source._DebugParticleSystemStatForeground),
    _DebugAnimationStatForeground(source._DebugAnimationStatForeground),
    _PhysDrawable(NullFC),
    _PhysDrawableNode(NullFC),
    _WasMouseHidden(false),
    _WasMouseAttached(false),
	_UndoActionListener(NULL,NULL),
	_RedoActionListener(NULL,NULL),
	_CommandManagerListener(ApplicationPlayerPtr(this))
{
	_TheUndoManager = UndoManager::create();
	_TheCommandManager = CommandManager::create(_TheUndoManager);
}

ApplicationPlayer::~ApplicationPlayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationPlayer::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ApplicationPlayer::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ApplicationPlayer NI" << std::endl;
}

ApplicationPlayer::CommandManagerListener::CommandManagerListener(ApplicationPlayerPtr ApplicationPlayer)
{
	_ApplicationPlayer = ApplicationPlayer;
}

void ApplicationPlayer::CommandManagerListener::stateChanged(const ChangeEventPtr e)
{
	_ApplicationPlayer->updateUndoRedoInterfaces(_ApplicationPlayer->_TheUndoManager);
}

void ApplicationPlayer::CommandManagerListener::setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
	_ApplicationPlayer->_TheUndoManager->addChangeListener(this);
}


void ApplicationPlayer::PlayerKeyListener::keyTyped(const KeyEventPtr e)
{
    _ApplicationPlayer->keyTyped(e);
}

void ApplicationPlayer::BasicListener::actionPerformed(const ActionEventPtr e)
{
    _ApplicationPlayer->actionPerformed(e);
}

void ApplicationPlayer::GotoSceneItemListener::actionPerformed(const ActionEventPtr e)
{
    ScenePtr TheScene(MainApplication::the()->getProject()->getSceneByName(MenuItemPtr::dcast(e->getSource())->getText()));

    if(TheScene != NullFC)
    {
        _ApplicationPlayer->gotoScene(TheScene);
    }
}

void ApplicationPlayer::ProjectListener::eventProduced(const EventPtr e, UInt32 EventProducedId)
{
    switch(EventProducedId)
    {
        case Project::SceneChangedMethodId:
            _ApplicationPlayer->updateDebugSceneChange();
            break;
    }
}

ApplicationPlayer::highlightNodeListener::highlightNodeListener(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void ApplicationPlayer::highlightNodeListener::update(const UpdateEventPtr e)
{
    _ApplicationPlayer->updateHighlightNode();
}

void ApplicationPlayer::updateWireframeNode(void)
{
    //Clone the sub-tree rooted at the selected node
    if(_SelectedNode != NullFC)
    {
        NodePtr ClonedTree(cloneTree(_SelectedNode));
        beginEditCP(_WireframeNode, Node::ChildrenFieldMask);
            if(_WireframeNode->getNChildren() > 0)
            {
                _WireframeNode->replaceChild(0, ClonedTree);
            }
            else
            {
                _WireframeNode->addChild(ClonedTree);
            }
        endEditCP(_WireframeNode, Node::ChildrenFieldMask);
    }

    //Update the transformation for the wireframe node
    beginEditCP(_WireframeTransform, Transform::MatrixFieldMask);
        if(_SelectedNode != NullFC &&
           _SelectedNode->getParent() != NullFC)
        {
            _WireframeTransform->setMatrix(_SelectedNode->getParent()->getToWorld());
        }
    endEditCP(_WireframeTransform, Transform::MatrixFieldMask);
}

void ApplicationPlayer::updateHighlightNode(void)
{
    getDebugSceneNavigator().updateCameraTransformation();

	// attach the hightlight node to the root if the highlight is active
    beginEditCP(_HighlightNode, Node::TravMaskFieldMask);
        if(_SelectedNode == NullFC)
        {
            _HighlightNode->setTravMask(0);
        }
        else
        {
            _HighlightNode->setTravMask(UInt32(-1));
        }
    endEditCP(_HighlightNode, Node::TravMaskFieldMask);

	if(_SelectedNode != NullFC)		// selected node is the node that is being selected.
    {													// highlight node is the pointer to the bounding box for the selected node
	 std::string coreName= _SelectedNode->getCore()->getTypeName();

		// calc the world bbox of the highlight object
		#ifndef OSG_2_PREP
		DynamicVolume vol;
		#else
		BoxVolume      vol;
		#endif
		_SelectedNode->getWorldVolume(vol);

		Pnt3f min,max;
		vol.getBounds(min, max);

        //Get The Local Coordinate System
        Matrix NodeMatrix = _SelectedNode->getToWorld();
        Pnt3f NodeOrigin(0.0f,0.0f,0.0f);
        Vec3f NodeXDir(1.0f,0.0f,0.0f),
              NodeYDir(0.0f,1.0f,0.0f),
              NodeZDir(0.0f,0.0f,1.0f);

        NodeMatrix.mult(NodeOrigin);
        NodeMatrix.mult(NodeXDir);
        NodeMatrix.mult(NodeYDir);
        NodeMatrix.mult(NodeZDir);

        //If the Volume is Zero, use a volume of size 1.0
        if(min == max)
        {
            min = NodeOrigin - Vec3f(0.5f,0.5f,0.5f);
            max = NodeOrigin + Vec3f(0.5f,0.5f,0.5f);
        }

        //Get the side lengths of the volume
        Vec3f  Sides(max - min);

        if(GeometryPtr::dcast(_HighlightNode->getCore())->getPositions() == NullFC)
        {
            beginEditCP(_HighlightNode->getCore(), Geometry::PositionsFieldMask);
                GeometryPtr::dcast(_HighlightNode->getCore())->setPositions(GeoPositions3f::create());
            endEditCP  (_HighlightNode->getCore(), Geometry::PositionsFieldMask);
        }

		GeoPositions3fPtr temphighlightPoints =
            GeoPositions3fPtr::dcast(GeometryPtr::dcast(_HighlightNode->getCore())->getPositions());

		beginEditCP(temphighlightPoints);
            //Update Bounding Box
            temphighlightPoints->setValue(Pnt3f(min[0], min[1], min[2]), 0);
            temphighlightPoints->setValue(Pnt3f(max[0], min[1], min[2]), 1);
            temphighlightPoints->setValue(Pnt3f(min[0], max[1], min[2]), 2);
            temphighlightPoints->setValue(Pnt3f(max[0], max[1], min[2]), 3);
            temphighlightPoints->setValue(Pnt3f(min[0], min[1], max[2]), 4);
            temphighlightPoints->setValue(Pnt3f(max[0], min[1], max[2]), 5);
            temphighlightPoints->setValue(Pnt3f(min[0], max[1], max[2]), 6);
            temphighlightPoints->setValue(Pnt3f(max[0], max[1], max[2]), 7);

            //Update Local Coordinate Axis
            Real32 AxisScaling(Sides.maxValue() * 0.55f);
            temphighlightPoints->setValue(NodeOrigin, 8);
            temphighlightPoints->setValue(NodeOrigin + (NodeXDir* AxisScaling), 9);
            temphighlightPoints->setValue(NodeOrigin, 10);
            temphighlightPoints->setValue(NodeOrigin + (NodeYDir* AxisScaling), 11);
            temphighlightPoints->setValue(NodeOrigin, 12);
            temphighlightPoints->setValue(NodeOrigin + (NodeZDir* AxisScaling), 13);
		endEditCP(temphighlightPoints);

        //Update the transformation for the wireframe node
        beginEditCP(_WireframeTransform, Transform::MatrixFieldMask);
            if(_SelectedNode != NullFC &&
               _SelectedNode->getParent() != NullFC)
            {
                _WireframeTransform->setMatrix(_SelectedNode->getParent()->getToWorld());
            }
        endEditCP(_WireframeTransform, Transform::MatrixFieldMask);
    }
}

void ApplicationPlayer::createHighlightNode(void)
{
    //Create the Material for the Highlight
    LineChunkPtr HighlightMatLineChunk = LineChunk::create();
    beginEditCP(HighlightMatLineChunk);
        HighlightMatLineChunk->setWidth(2.0f);
        HighlightMatLineChunk->setSmooth(true);
    endEditCP(HighlightMatLineChunk);

    BlendChunkPtr TheBlendChunk = BlendChunk::create();
    beginEditCP(TheBlendChunk);
        TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    endEditCP(TheBlendChunk);

    ChunkMaterialPtr HighlightMaterial = ChunkMaterial::create();
    beginEditCP(HighlightMaterial);
        HighlightMaterial->addChunk (TheBlendChunk);
        HighlightMaterial->addChunk (HighlightMatLineChunk);
    endEditCP(HighlightMaterial);
    
    //Create teh Geometry for the highlight
    GeoPTypesPtr type = GeoPTypesUI8::create();
    beginEditCP(type);
        //Volume bound box
        type->push_back(GL_LINE_STRIP);
        type->push_back(GL_LINES);

        //Local Coordinage axis
        type->push_back(GL_LINES);
    endEditCP(type);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();
    beginEditCP(lens);
        //Volume bound box
        lens->push_back(10);
        lens->push_back(6);

        //Local Coordinage axis
        lens->push_back(6);
    endEditCP(lens);

    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
    beginEditCP(index);
        //Volume bound box
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

        //Local Coordinage axis
        index->getFieldPtr()->push_back(8);
        index->getFieldPtr()->push_back(9);
        index->getFieldPtr()->push_back(10);
        index->getFieldPtr()->push_back(11);
        index->getFieldPtr()->push_back(12);
        index->getFieldPtr()->push_back(13);
    endEditCP(index);

    GeoPositions3fPtr highlightPoints = GeoPositions3f::create();
    beginEditCP(highlightPoints);
        //Volume bound box
        highlightPoints->push_back(Pnt3f(-1, -1, -1));
        highlightPoints->push_back(Pnt3f( 1, -1, -1));
        highlightPoints->push_back(Pnt3f(-1,  1, -1));
        highlightPoints->push_back(Pnt3f( 1,  1, -1));
        highlightPoints->push_back(Pnt3f(-1, -1,  1));
        highlightPoints->push_back(Pnt3f( 1, -1,  1));
        highlightPoints->push_back(Pnt3f(-1,  1,  1));
        highlightPoints->push_back(Pnt3f( 1,  1,  1));

        //Local Coordinage axis
        highlightPoints->push_back(Pnt3f( 0,  0,  0));
        highlightPoints->push_back(Pnt3f( 1,  0,  0));
        highlightPoints->push_back(Pnt3f( 0,  0,  0));
        highlightPoints->push_back(Pnt3f( 0,  1,  0));
        highlightPoints->push_back(Pnt3f( 0,  0,  0));
        highlightPoints->push_back(Pnt3f( 0,  0,  1));
    endEditCP(highlightPoints);

    //Colors
    Color4f BoundBoxColor(0.0f,1.0f,1.0,1.0f);
    Color4f XAxisColor   (1.0f,0.0f,0.0,1.0f);
    Color4f YAxisColor   (0.0f,1.0f,0.0,1.0f);
    Color4f ZAxisColor   (0.0f,0.0f,1.0,1.0f);

    GeoColors4fPtr highlightColors = GeoColors4f::create();
    beginEditCP(highlightColors);
        //Volume bound box
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);
        highlightColors->getFieldPtr()->push_back(BoundBoxColor);

        //Local Coordinage axis
        highlightColors->getFieldPtr()->push_back(XAxisColor);
        highlightColors->getFieldPtr()->push_back(XAxisColor);
        highlightColors->getFieldPtr()->push_back(YAxisColor);
        highlightColors->getFieldPtr()->push_back(YAxisColor);
        highlightColors->getFieldPtr()->push_back(ZAxisColor);
        highlightColors->getFieldPtr()->push_back(ZAxisColor);
    endEditCP(highlightColors);

    GeometryPtr geo=Geometry::create();
    beginEditCP(geo);
        geo->setTypes     (type);
        geo->setLengths   (lens);
        geo->setIndices   (index);
        geo->setPositions (highlightPoints);
        geo->setColors    (highlightColors);
        geo->setMaterial  (HighlightMaterial);
    endEditCP(geo);

    //Create the Material for the Mesh Highlight
    LineChunkPtr WireframeMatLineChunk = LineChunk::create();
    beginEditCP(WireframeMatLineChunk);
        WireframeMatLineChunk->setWidth(1.0f);
        WireframeMatLineChunk->setSmooth(true);
    endEditCP(WireframeMatLineChunk);

    PolygonChunkPtr WireframeMatPolygonChunk = PolygonChunk::create();
    beginEditCP(WireframeMatPolygonChunk);
        WireframeMatPolygonChunk->setCullFace(GL_NONE);
        WireframeMatPolygonChunk->setFrontMode(GL_LINE);
        WireframeMatPolygonChunk->setBackMode(GL_LINE);
        WireframeMatPolygonChunk->setOffsetFactor(1.0f);
        WireframeMatPolygonChunk->setOffsetBias(0.01f);
        WireframeMatPolygonChunk->setOffsetFill(true);
    endEditCP(WireframeMatPolygonChunk);

    Color4f WireframeColor(1.0f,0.0f,1.0f,1.0f);
    MaterialChunkPtr WireframeMatMaterialChunk = MaterialChunk::create();
    beginEditCP(WireframeMatMaterialChunk);
        WireframeMatMaterialChunk->setAmbient (Color4f(0.0f,0.0f,0.0f,1.0f));
        WireframeMatMaterialChunk->setDiffuse (Color4f(0.0f,0.0f,0.0f,1.0f));
        WireframeMatMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        WireframeMatMaterialChunk->setEmission(WireframeColor);
        WireframeMatMaterialChunk->setLit(true);
    endEditCP(WireframeMatMaterialChunk);

    ChunkMaterialPtr WireframeMaterial = ChunkMaterial::create();
    beginEditCP(WireframeMaterial);
        WireframeMaterial->addChunk (TheBlendChunk);
        WireframeMaterial->addChunk (WireframeMatPolygonChunk);
        WireframeMaterial->addChunk (WireframeMatMaterialChunk);
        WireframeMaterial->addChunk (WireframeMatLineChunk);
    endEditCP(WireframeMaterial);

    //MaterialGroup
    MaterialGroupPtr WireframeMaterialGroup = MaterialGroup::create(); 
    beginEditCP(WireframeMaterialGroup);
        WireframeMaterialGroup->setMaterial(WireframeMaterial);
    endEditCP(WireframeMaterialGroup);

    //Mesh Highlight Node
    _WireframeNode = Node::create();
    setName(_WireframeNode,"DEBUG_MODE_MESH_HIGHLIGHT_NODE");
    beginEditCP(_WireframeNode);
        _WireframeNode->setCore(WireframeMaterialGroup);
    endEditCP(_WireframeNode);

    //Mesh Highlight Transformation Node
    _WireframeTransform = Transform::create();

    NodePtr WireframeTransfromationNode = Node::create();
    beginEditCP(WireframeTransfromationNode);
        WireframeTransfromationNode->setCore(_WireframeTransform);
        WireframeTransfromationNode->addChild(_WireframeNode);
    endEditCP(WireframeTransfromationNode);

    //Highlight Node
    _HighlightNode = Node::create();
    setName(_HighlightNode,"DEBUG_MODE_HIGHLIGHT_NODE");
    
    beginEditCP(_HighlightNode);
        _HighlightNode->setCore(geo);
        _HighlightNode->addChild(WireframeTransfromationNode);
    endEditCP(_HighlightNode);
    addRefCP(_HighlightNode);
}

void ApplicationPlayer::selectNode(const Pnt2f& ViewportPoint)
{
    Line ViewRay;
    ViewportPtr TheViewport(MainApplication::the()->getProject()->getActiveScene()->getViewports(0));
    TheViewport->getCamera()->calcViewRay( ViewRay, ViewportPoint.x(), ViewportPoint.y(), *TheViewport);

    IntersectAction *CastRayAction = IntersectAction::create();

    CastRayAction->setLine( ViewRay );
    CastRayAction->apply( TheViewport->getRoot() );             

    //Get the Tree Model
    SceneGraphTreeModelPtr SceneModel(_HierarchyPanel->getSceneGraphTreeModel());
    TreePtr SceneTree(_HierarchyPanel->getSceneGraphTree());
    if ( CastRayAction->didHit() )
    {
        TreePath ThePath(SceneModel->getPathForNode(CastRayAction->getHitObject()));
        SceneTree->expandPath(ThePath);
        SceneTree->scrollPathToVisible(ThePath);
        SceneTree->setSelectionPath(ThePath);
    }
    else
    {
        SceneTree->clearSelection();
    }
}

void ApplicationPlayer::setupPopupMenu()
{
	
}

ApplicationPlayer::highlightNodeListener::~highlightNodeListener()
{

}

void ApplicationPlayer::ComboBoxListener::selectionChanged(const ComboBoxSelectionEventPtr e)
{
    _ApplicationPlayer->setDebugView(e->getCurrentIndex());
}

ApplicationPlayer::ComboBoxListener::ComboBoxListener(ApplicationPlayerPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
}

