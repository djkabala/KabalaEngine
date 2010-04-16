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
#include <OpenSG/OSGSimpleMaterial.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

#include "KEApplicationPlayer.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"
#include "Application/KEMainApplication.h"
#include <OpenSG/UserInterface/OSGFlowLayout.h>

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
	_ContentPanel->init();

	_OpenFileButton = Button::create();

	beginEditCP(_OpenFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	_OpenFileButton->setText("Open File");
	_OpenFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(_OpenFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	
	_OpenFileButton->addActionListener(&_BasicListener);
		
	_SaveFileButton = Button::create();

	beginEditCP(_SaveFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	_SaveFileButton->setText("Save File");
	_SaveFileButton->setPreferredSize(Vec2f(100,50));
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

	_Toolbar = Panel::create();
	
	beginEditCP(_Toolbar,Panel::PreferredSizeFieldMask);
	_Toolbar->setPreferredSize(Vec2f(200,60));
	endEditCP(_Toolbar,Panel::PreferredSizeFieldMask);


	beginEditCP(_ToolbarLayout);
        // NOTHING : )
	endEditCP(_ToolbarLayout); 

	_ToolbarLayout = osg::SpringLayout::create();


	_ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _ModeComboBox, 5, SpringLayoutConstraints::NORTH_EDGE, _Toolbar);  
    _ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ModeComboBox, -5, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _ModeComboBox, -140, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _ModeComboBox, -5, SpringLayoutConstraints::SOUTH_EDGE, _Toolbar);

	_ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _SaveFileButton, 5, SpringLayoutConstraints::NORTH_EDGE, _Toolbar);  
    _ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaveFileButton, -150, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SaveFileButton, -285, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _SaveFileButton, -5, SpringLayoutConstraints::SOUTH_EDGE, _Toolbar);
    	
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _OpenFileButton, 5, SpringLayoutConstraints::NORTH_EDGE, _Toolbar);  
    _ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _OpenFileButton, -295, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _OpenFileButton, -430, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _OpenFileButton, -5, SpringLayoutConstraints::SOUTH_EDGE, _Toolbar);
   
/*	_ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _CloseFileButton, 5, SpringLayoutConstraints::NORTH_EDGE, _Toolbar);  
    _ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _CloseFileButton, -440, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _CloseFileButton, -575, SpringLayoutConstraints::EAST_EDGE, _Toolbar);
	_ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _CloseFileButton, -5, SpringLayoutConstraints::SOUTH_EDGE, _Toolbar);
  */  
	//_ToolbarLayout = osg::FlowLayout::create();

	beginEditCP(_Toolbar,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	_Toolbar->getChildren().push_back(_ModeComboBox);
	_Toolbar->getChildren().push_back(_SaveFileButton);
	_Toolbar->getChildren().push_back(_OpenFileButton);
	//_Toolbar->getChildren().push_back(_CloseFileButton);
	_Toolbar->setLayout(_ToolbarLayout);
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
  
	_TopLeftPanel = osg::Panel::create();
    
	//ToolbarLayout2= osg::BorderLayout::create();

	beginEditCP(_HierarchyPanel,Panel::PreferredSizeFieldMask);
		_HierarchyPanel->setPreferredSize(Vec2f(400,700));
	endEditCP(_HierarchyPanel,Panel::PreferredSizeFieldMask);

	// _TopLeftPanel panel elements creation
	_ModeComboBoxModel = DefaultMutableComboBoxModel::create();
	_ModeComboBoxModel->addElement(boost::any(std::string("Scene Graph")));
	_ModeComboBoxModel->addElement(boost::any(std::string("Lua Graph")));
	
	beginEditCP(_ModeComboBox, ComboBox::ModelFieldMask | ComboBox::MinSizeFieldMask  | ComboBox::EditableFieldMask);
		_ModeComboBox->setMinSize(Vec2f(100.0,20));
		_ModeComboBox->setEditable(false);
		_ModeComboBox->setModel(_ModeComboBoxModel);
	endEditCP(_ModeComboBox, ComboBox::ModelFieldMask);
	
	//_ModeComboBox->addActionListener(&_BasicListener);
	_ComboBoxListener.set(_ModeComboBox,_HierarchyPanel->getCardLayout(),_HierarchyPanel);//->TopLeftTreePanel);
	_ModeComboBoxModel->addSelectionListener(&_ComboBoxListener);
			
	// Determine where the _ModeComboBox starts
	_ModeComboBox->setSelectedIndex(0);
	
	
	
	
	_TopLeftPanelLayout = osg::SpringLayout::create();

	_TopLeftPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _HierarchyPanel, 5, SpringLayoutConstraints::NORTH_EDGE, _TopLeftPanel);  
    _TopLeftPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HierarchyPanel, -5, SpringLayoutConstraints::EAST_EDGE, _TopLeftPanel);
	_TopLeftPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HierarchyPanel, 5, SpringLayoutConstraints::WEST_EDGE, _TopLeftPanel);
	_TopLeftPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _HierarchyPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, _TopLeftPanel);
   

	setupPopupMenu();

	beginEditCP(_TopLeftPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		_TopLeftPanel->getChildren().push_back(_HierarchyPanel);//->TopLeftTreePanel);
		//_TopLeftPanel->getChildren().push_back(_ModeComboBox);
		//_TopLeftPanel->getChildren().push_back(poptrigger);
		//_TopLeftPanel->setPopupMenu(_HierarchyPanelPopupMenu);
		_TopLeftPanel->setLayout(_TopLeftPanelLayout);
    endEditCP(_TopLeftPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	/*************************************************** _DebugWindowSplitPanel creation **********************************************************************/

	_ToolbarAndContentConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(_ToolbarAndContentConstraints, BorderLayoutConstraints::RegionFieldMask);
        _ToolbarAndContentConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(_ToolbarAndContentConstraints, BorderLayoutConstraints::RegionFieldMask);

	_ToolbarAndContentPanel = osg::SplitPanel::create();

	beginEditCP(_ToolbarAndContentPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        _ToolbarAndContentPanel->setConstraints(_ToolbarAndContentConstraints);
        _ToolbarAndContentPanel->setMinComponent(_Toolbar);
		_ToolbarAndContentPanel->setMaxComponent(_ContentPanel);
        _ToolbarAndContentPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        _ToolbarAndContentPanel->setDividerPosition(.05); 
        // location from the left/top
        _ToolbarAndContentPanel->setDividerSize(1);
        _ToolbarAndContentPanel->setExpandable(false);
        //_ToolbarAndContentPanel->setMaxDividerPosition(.25);
        //_ToolbarAndContentPanel->setMinDividerPosition(.15);
    endEditCP(_ToolbarAndContentPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);


	_TopHalfSplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(_TopHalfSplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        _TopHalfSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(_TopHalfSplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
    
	_TopHalfSplitPanel = osg::SplitPanel::create();

	beginEditCP(_TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
		_TopHalfSplitPanel->setConstraints(_TopHalfSplitPanelConstraints);
        _TopHalfSplitPanel->setMinComponent(_TopLeftPanel);
		_TopHalfSplitPanel->setMaxComponent(_ToolbarAndContentPanel);
        _TopHalfSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
        _TopHalfSplitPanel->setDividerPosition(.25); 
        // location from the left/top
        _TopHalfSplitPanel->setDividerSize(1);
        _TopHalfSplitPanel->setExpandable(true);
        _TopHalfSplitPanel->setMaxDividerPosition(.25);
        _TopHalfSplitPanel->setMinDividerPosition(.15);
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
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.0));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);


    MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::MenuBarFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
	   MainInternalWindow->getChildren().push_back(_DebugWindowSplitPanel);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
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
	_HierarchyPanel->_SceneGraphTreeSelectionListener.updateHighlight();
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
		int _Temp = _ModeComboBox->getSelectedIndex();
		if(_Temp == 1)
        {
            _HierarchyPanel->getCardLayout()->last(_HierarchyPanel);//->TopLeftTreePanel);
        }
        else
        {
            _HierarchyPanel->getCardLayout()->first(_HierarchyPanel);//->TopLeftTreePanel);
        }
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
    //MFForegroundPtr::iterator SearchItor(MainApplication::the()->getProject()->getActiveForegrounds().find(TheForeground));
    //if( SearchItor != MainApplication::the()->getProject()->getActiveForegrounds().end())
    //{
        ////If the Stat foreground is present then switch it off
        //beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
            //MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        //endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
    //}
    //else
    //{
        ////If not present then switch all other stat foregrounds off
        //hideAllStatForegrounds();
        ////and switch it on
        //beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
            //MainApplication::the()->getProject()->getActiveForegrounds().push_back(TheForeground);
        //endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
        //MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->setStatistics(&TheForeground->getCollector());
    //}
}

void ApplicationPlayer::hideAllStatForegrounds(void)
{
    
    MFForegroundPtr::iterator SearchItor;

    //beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
        ////Hide Basic Stat Foreground if present
        //if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugBasicStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        //{
            //MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        //}
        ////Hide Render Stat Foreground if present
        //if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugRenderStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        //{
            //MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        //}
        ////Hide Physics Stat Foreground if present
        //if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugPhysicsStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        //{
            //MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        //}
        ////Hide Particle System Stat Foreground if present
        //if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugParticleSystemStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        //{
            //MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        //}
        ////Hide Animation Stat Foreground if present
        //if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugAnimationStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        //{
            //MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        //}
    //endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
}

void ApplicationPlayer::initDebugStatForegrounds(void)
{
    //Basic Statistics
    _DebugBasicStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugBasicStatForeground);
        _DebugBasicStatForeground->setSize(25);
        _DebugBasicStatForeground->setColor(Color4f(0,1,0,0.7));
		_DebugBasicStatForeground->addElement(RenderAction::statDrawTime, " ");
        _DebugBasicStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        _DebugBasicStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugBasicStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
    endEditCP(_DebugBasicStatForeground);
    addRefCP(_DebugBasicStatForeground);
    
    //Rendering Statistics
    _DebugRenderStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugRenderStatForeground);
        _DebugRenderStatForeground->setSize(25);
		//_DebugRenderStatForeground->setPosition(Pnt2f(10,30));
        _DebugRenderStatForeground->setColor(Color4f(0,1,0,0.7));
		_DebugRenderStatForeground->addElement(RenderAction::statDrawTime," ");
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
        _DebugPhysicsStatForeground->setSize(25);
		//_DebugPhysicsStatForeground->setPosition(Pnt2f(10,30));
        _DebugPhysicsStatForeground->setColor(Color4f(0,1,0,0.7));
		_DebugPhysicsStatForeground->addElement(RenderAction::statDrawTime," ");
        _DebugPhysicsStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugPhysicsStatForeground);
    addRefCP(_DebugPhysicsStatForeground);
    
    //Particle System Statistics
    _DebugParticleSystemStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugParticleSystemStatForeground);
        _DebugParticleSystemStatForeground->setSize(25);
        _DebugParticleSystemStatForeground->setColor(Color4f(0,1,0,0.7));
		_DebugParticleSystemStatForeground->addElement(RenderAction::statDrawTime," ");
		//_DebugParticleSystemStatForeground->setPosition(Pnt2f(10,30));
        _DebugParticleSystemStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugParticleSystemStatForeground);
    addRefCP(_DebugParticleSystemStatForeground);
    
    //Animation Statistics
    _DebugAnimationStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugAnimationStatForeground);
        _DebugAnimationStatForeground->setSize(25);
        _DebugAnimationStatForeground->setColor(Color4f(0,1,0,0.7));
		//_DebugAnimationStatForeground->setPosition(Pnt2f(10,30));
		_DebugAnimationStatForeground->addElement(RenderAction::statDrawTime," ");
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
	_HierarchyPanel->_SceneGraphTreeSelectionListener.updateHighlight();
	
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
    beginEditCP(_DebugBeaconTransform, Transform::MatrixFieldMask);
		_DebugBeaconTransform->setMatrix(_SceneViewportCamera->getBeacon()->getToWorld());
    endEditCP(_DebugBeaconTransform, Transform::MatrixFieldMask);

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
    beginEditCP(_DebugBeaconTransform, Transform::MatrixFieldMask);
		_DebugBeaconTransform->setMatrix(_SceneViewportCamera->getBeacon()->getToWorld());
    endEditCP(_DebugBeaconTransform, Transform::MatrixFieldMask);
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
	if(_ApplicationPlayer->_SelectedNode != NullFC)		// selected node is the node that is being selected.
    {													// highlight node is the pointer to the bounding box for the selected node
	 std::string coreName= _ApplicationPlayer->_SelectedNode->getCore()->getTypeName();

		// calc the world bbox of the highlight object
		#ifndef OSG_2_PREP
		DynamicVolume vol;
		#else
		BoxVolume      vol;
		#endif
		_ApplicationPlayer->_SelectedNode->getWorldVolume(vol);

		Pnt3f min,max;
		vol.getBounds(min, max);

		GeoPositions3fPtr temphighlightPoints = GeoPositions3f::create();

		beginEditCP(temphighlightPoints);
		temphighlightPoints->push_back(Pnt3f(min[0], min[1], min[2]));
		temphighlightPoints->push_back(Pnt3f(max[0], min[1], min[2]));
		temphighlightPoints->push_back(Pnt3f(min[0], max[1], min[2]));
		temphighlightPoints->push_back(Pnt3f(max[0], max[1], min[2]));
		temphighlightPoints->push_back(Pnt3f(min[0], min[1], max[2]));
		temphighlightPoints->push_back(Pnt3f(max[0], min[1], max[2]));
		temphighlightPoints->push_back(Pnt3f(min[0], max[1], max[2]));
		temphighlightPoints->push_back(Pnt3f(max[0], max[1], max[2]));
		endEditCP(temphighlightPoints);


		beginEditCP(_ApplicationPlayer->_HighlightNode->getCore(), Geometry::PositionsFieldMask);
		GeometryPtr::dcast(_ApplicationPlayer->_HighlightNode->getCore())->setPositions(temphighlightPoints);
		endEditCP  (_ApplicationPlayer->_HighlightNode->getCore(), Geometry::PositionsFieldMask);


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
    int index = _ComboBox->getSelectedIndex();
    if(index == 0)
    {
        _TopLeftCardLayout->first(_TopLeftTreePanel);
        /*beginEditCP(_ApplicationPlayer->_TopLeftPanel);
            _ApplicationPlayer->_TopLeftPanel->setPopupMenu(_ApplicationPlayer->_HierarchyPanelPopupMenu);
        endEditCP(_ApplicationPlayer->_TopLeftPanel);*/
        _ApplicationPlayer->_ContentPanel->setVisible(false);
    }
    else 
    {
        /*beginEditCP(_ApplicationPlayer->_TopLeftPanel);
            _ApplicationPlayer->_TopLeftPanel->setPopupMenu(NullFC);
        endEditCP(_ApplicationPlayer->_TopLeftPanel);*/

        _TopLeftCardLayout->last(_TopLeftTreePanel);
        _ApplicationPlayer->_ContentPanel->setVisible(true);
    }
}

void ApplicationPlayer::ComboBoxListener::set(ComboBoxPtr ComboBoxP,CardLayoutPtr _CardLayout,PanelPtr TopLeftTreePanel)
{
    _ComboBox = ComboBoxP;
    _TopLeftCardLayout = _CardLayout;
    _TopLeftTreePanel = TopLeftTreePanel;
}

ApplicationPlayer::ComboBoxListener::ComboBoxListener(ApplicationPlayerPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
    _ComboBox = NullFC;
    _TopLeftCardLayout = NullFC;
    _TopLeftTreePanel = NullFC;
}
