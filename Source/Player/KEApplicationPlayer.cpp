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
#include <OpenSG/OSGTransform.h>
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

InternalWindowPtr MainInternalWindow;		
GraphicsPtr DebuggerGraphics;				
UIForegroundPtr DebuggerUIForeground;		
UIDrawingSurfacePtr DebuggerDrawingSurface;	

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
        //TODO: Check if te Debug Interface has already been created
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
	 // debug interface creation
	DebuggerGraphics = osg::Graphics2D::create();

	/*************************************************** Menu creation *******************************************************************/
	// the menu items
	ResetItem = MenuItem::create();				
    ForceQuitItem = MenuItem::create();			
	
	UndoItem = MenuItem::create();				
    RedoItem = MenuItem::create();			

    NextItem = MenuItem::create();				
    PrevItem = MenuItem::create();				
    FirstItem = MenuItem::create();				
    LastItem = MenuItem::create();				
    _SceneSubItem = Menu::create();				

	FlyNavigatorItem = MenuItem::create();		
    TrackballNavigatorItem = MenuItem::create();

    BasicItem = MenuItem::create();				
    RenderItem = MenuItem::create();			
    PhysicsItem = MenuItem::create();
    ParticleSystemItem = MenuItem::create();	
	AnimationItem = MenuItem::create();
	PauseActiveUpdatesItem = MenuItem::create();
	DrawBoundingVolumesItem = MenuItem::create();
	FrustrumCullingItem = MenuItem::create();
	DrawPhysicsCharacteristicsItem = MenuItem::create();

	ShowHideItem = MenuItem::create();
	DeleteItem = MenuItem::create();
	CutItem = MenuItem::create();
	CopyItem = MenuItem::create();
	PasteItem = MenuItem::create();

	// setting the fields of the menu items
	beginEditCP(ResetItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        ResetItem->setText("Reset");
		ResetItem->setAcceleratorKey(KeyEvent::KEY_E);
        ResetItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        ResetItem->setMnemonicKey(KeyEvent::KEY_E);
    endEditCP(ResetItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(ForceQuitItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        ForceQuitItem ->setText("Force Quit");
		ForceQuitItem ->setAcceleratorKey(KeyEvent::KEY_Q);
        ForceQuitItem ->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        ForceQuitItem ->setMnemonicKey(KeyEvent::KEY_Q);
    endEditCP(ForceQuitItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(UndoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        UndoItem->setText("Undo");
		UndoItem->setAcceleratorKey(KeyEvent::KEY_U);
        UndoItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        UndoItem->setMnemonicKey(KeyEvent::KEY_U);
    endEditCP(UndoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
 
	beginEditCP(RedoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        RedoItem->setText("Redo");
		RedoItem->setAcceleratorKey(KeyEvent::KEY_R);
        RedoItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        RedoItem->setMnemonicKey(KeyEvent::KEY_R);
    endEditCP(RedoItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
 
    beginEditCP(NextItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        NextItem ->setText("Next");
		NextItem ->setAcceleratorKey(KeyEvent::KEY_TAB);
		//NextItem ->setAcceleratorModifiers(!KeyEvent::KEY_MODIFIER_SHIFT);
	endEditCP(NextItem , MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(PrevItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        PrevItem->setText("Previous");
	    PrevItem->setAcceleratorKey(KeyEvent::KEY_TAB);
        PrevItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_SHIFT);
    endEditCP(PrevItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

    beginEditCP(FirstItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        FirstItem->setText("First");
		FirstItem->setAcceleratorKey(KeyEvent::KEY_F);
        FirstItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        FirstItem->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(FirstItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(LastItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        LastItem->setText("Last");
		LastItem->setAcceleratorKey(KeyEvent::KEY_L);
        LastItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        LastItem->setMnemonicKey(KeyEvent::KEY_L);
    endEditCP(LastItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_SceneSubItem, Menu::TextFieldMask);
        _SceneSubItem->setText("Scenes");
    endEditCP(_SceneSubItem, Menu::TextFieldMask);
    
	beginEditCP(FlyNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        FlyNavigatorItem->setText("FlyNavigator ");
		FlyNavigatorItem->setAcceleratorKey(KeyEvent::KEY_N);
        FlyNavigatorItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        FlyNavigatorItem->setMnemonicKey(KeyEvent::KEY_N);
    endEditCP(FlyNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(TrackballNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        TrackballNavigatorItem->setText("TrackballNavigator ");
		TrackballNavigatorItem->setAcceleratorKey(KeyEvent::KEY_T);
        TrackballNavigatorItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        TrackballNavigatorItem->setMnemonicKey(KeyEvent::KEY_T);
    endEditCP(TrackballNavigatorItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(BasicItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        BasicItem->setText("Basic ");
	    BasicItem->setAcceleratorKey(KeyEvent::KEY_B);
        BasicItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        BasicItem->setMnemonicKey(KeyEvent::KEY_B);
    endEditCP(BasicItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(RenderItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        RenderItem->setText("Render ");
	    RenderItem->setAcceleratorKey(KeyEvent::KEY_R);
        RenderItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        RenderItem->setMnemonicKey(KeyEvent::KEY_R);
    endEditCP(RenderItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(PhysicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        PhysicsItem->setText("Physics ");
        PhysicsItem->setAcceleratorKey(KeyEvent::KEY_Y);
        PhysicsItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        PhysicsItem->setMnemonicKey(KeyEvent::KEY_Y);
    endEditCP(PhysicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(ParticleSystemItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        ParticleSystemItem->setText("ParticleSystem ");
        ParticleSystemItem->setAcceleratorKey(KeyEvent::KEY_Z);
        ParticleSystemItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        ParticleSystemItem->setMnemonicKey(KeyEvent::KEY_Z);
    endEditCP(ParticleSystemItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(AnimationItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        AnimationItem->setText("Animation ");
        AnimationItem->setAcceleratorKey(KeyEvent::KEY_A);
        AnimationItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        AnimationItem->setMnemonicKey(KeyEvent::KEY_A);
    endEditCP(AnimationItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

		beginEditCP(PauseActiveUpdatesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        PauseActiveUpdatesItem->setText("Pause Active Updates");
        PauseActiveUpdatesItem->setAcceleratorKey(KeyEvent::KEY_SPACE);
        //PauseActiveUpdatesItem->setMnemonicKey(KeyEvent::KEY_SPACE);
    endEditCP(PauseActiveUpdatesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(DrawBoundingVolumesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        DrawBoundingVolumesItem->setText("Draw Bounding Volumes");
        DrawBoundingVolumesItem->setAcceleratorKey(KeyEvent::KEY_V);
        DrawBoundingVolumesItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL | KeyEvent::KEY_MODIFIER_SHIFT);
        DrawBoundingVolumesItem->setMnemonicKey(KeyEvent::KEY_V);
    endEditCP(DrawBoundingVolumesItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(FrustrumCullingItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        FrustrumCullingItem->setText("Disable Frustrum Culling ");
        FrustrumCullingItem->setAcceleratorKey(KeyEvent::KEY_F);
        FrustrumCullingItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        FrustrumCullingItem->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(FrustrumCullingItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        DrawPhysicsCharacteristicsItem->setText("Draw Physics Characteristics ");
        DrawPhysicsCharacteristicsItem->setAcceleratorKey(KeyEvent::KEY_P);
        DrawPhysicsCharacteristicsItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        DrawPhysicsCharacteristicsItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	// pop up menu items

	beginEditCP(ShowHideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        ShowHideItem->setText("Hide");
        //ShowItem->setAcceleratorKey(KeyEvent::KEY_S);
        //ShowItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        //ShowItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(ShowHideItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(DeleteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        DeleteItem->setText("Delete");
        //ShowItem->setAcceleratorKey(KeyEvent::KEY_S);
        //ShowItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        //ShowItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(DeleteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(CutItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        CutItem->setText("Cut");
        //ShowItem->setAcceleratorKey(KeyEvent::KEY_S);
        //ShowItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        //ShowItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(CutItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(CopyItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        CopyItem->setText("Copy");
        //ShowItem->setAcceleratorKey(KeyEvent::KEY_S);
        //ShowItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        //ShowItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(CopyItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(PasteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        PasteItem->setText("Paste");
        //ShowItem->setAcceleratorKey(KeyEvent::KEY_S);
        //ShowItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        //ShowItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(PasteItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

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

	OpenFileButton = Button::create();

	beginEditCP(OpenFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	OpenFileButton->setText("Open File");
	OpenFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(OpenFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	
	OpenFileButton->addActionListener(&_BasicListener);
		
	SaveFileButton = Button::create();

	beginEditCP(SaveFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	SaveFileButton->setText("Save File");
	SaveFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(SaveFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);

	SaveFileButton->addActionListener(&_BasicListener);

	/*CloseFileButton = Button::create();

	beginEditCP(CloseFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);
	CloseFileButton->setText("Close File");
	CloseFileButton->setPreferredSize(Vec2f(100,50));
	endEditCP(CloseFileButton,Button::TextFieldMask,Button::PreferredSizeFieldMask);

	CloseFileButton->addActionListener(&_BasicListener);
	*/

	modeComboBox = ComboBox::create();

	Toolbar = Panel::create();
	
	beginEditCP(Toolbar,Panel::PreferredSizeFieldMask);
	Toolbar->setPreferredSize(Vec2f(200,60));
	endEditCP(Toolbar,Panel::PreferredSizeFieldMask);


	beginEditCP(ToolbarLayout);
        // NOTHING : )
	endEditCP(ToolbarLayout); 

	ToolbarLayout = osg::SpringLayout::create();


	ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, modeComboBox, 5, SpringLayoutConstraints::NORTH_EDGE, Toolbar);  
    ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, modeComboBox, -5, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, modeComboBox, -140, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, modeComboBox, -5, SpringLayoutConstraints::SOUTH_EDGE, Toolbar);

	ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, SaveFileButton, 5, SpringLayoutConstraints::NORTH_EDGE, Toolbar);  
    ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, SaveFileButton, -150, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, SaveFileButton, -285, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, SaveFileButton, -5, SpringLayoutConstraints::SOUTH_EDGE, Toolbar);
    	
	ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, OpenFileButton, 5, SpringLayoutConstraints::NORTH_EDGE, Toolbar);  
    ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, OpenFileButton, -295, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, OpenFileButton, -430, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, OpenFileButton, -5, SpringLayoutConstraints::SOUTH_EDGE, Toolbar);
   
/*	ToolbarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CloseFileButton, 5, SpringLayoutConstraints::NORTH_EDGE, Toolbar);  
    ToolbarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CloseFileButton, -440, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CloseFileButton, -575, SpringLayoutConstraints::EAST_EDGE, Toolbar);
	ToolbarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CloseFileButton, -5, SpringLayoutConstraints::SOUTH_EDGE, Toolbar);
  */  
	//ToolbarLayout = osg::FlowLayout::create();

	beginEditCP(Toolbar,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	Toolbar->getChildren().push_back(modeComboBox);
	Toolbar->getChildren().push_back(SaveFileButton);
	Toolbar->getChildren().push_back(OpenFileButton);
	//Toolbar->getChildren().push_back(CloseFileButton);
	Toolbar->setLayout(ToolbarLayout);
	endEditCP(Toolbar,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);


	// creation of menus and addition of menu items to them
	ProjectMenu = Menu::create();
    ProjectMenu->addItem(ResetItem);
	ProjectMenu->addSeparator();
    ProjectMenu->addItem(ForceQuitItem);
    
	EditMenu = Menu::create();
    EditMenu->addItem(UndoItem);
	EditMenu->addItem(RedoItem);
    
	
	SceneMenu = Menu::create();
    SceneMenu->addItem(NextItem);
    SceneMenu->addItem(PrevItem);
	SceneMenu->addItem(FirstItem);
	SceneMenu->addItem(LastItem);
	SceneMenu->addSeparator();
	SceneMenu->addItem(_SceneSubItem);
	

	NavigatorMenu = Menu::create();
    NavigatorMenu->addItem(FlyNavigatorItem);
    NavigatorMenu->addItem(TrackballNavigatorItem);

	StatisticsMenu = Menu::create();
    StatisticsMenu->addItem(BasicItem);
    StatisticsMenu->addItem(RenderItem);
	StatisticsMenu->addItem(PhysicsItem);
	StatisticsMenu->addItem(ParticleSystemItem);
	StatisticsMenu->addItem(AnimationItem);

	ToggleMenu = Menu::create();
	ToggleMenu->addItem(PauseActiveUpdatesItem);
	ToggleMenu->addItem(DrawBoundingVolumesItem);
	ToggleMenu->addItem(FrustrumCullingItem);
	ToggleMenu->addItem(DrawPhysicsCharacteristicsItem);

	// setting the fields for the menus 
	beginEditCP(ProjectMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        ProjectMenu->setText("Project");
        ProjectMenu->setMnemonicKey(KeyEvent::KEY_P);
	endEditCP(ProjectMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(EditMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        EditMenu->setText("Edit");
        EditMenu->setMnemonicKey(KeyEvent::KEY_D);
	endEditCP(EditMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(SceneMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        SceneMenu->setText("Scene");
        SceneMenu->setMnemonicKey(KeyEvent::KEY_S);
	endEditCP(SceneMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(NavigatorMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        NavigatorMenu->setText("Navigator");
        NavigatorMenu->setMnemonicKey(KeyEvent::KEY_N);
	endEditCP(NavigatorMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(StatisticsMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        StatisticsMenu->setText("Statistics");
        StatisticsMenu->setMnemonicKey(KeyEvent::KEY_S);
	endEditCP(StatisticsMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(ToggleMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        ToggleMenu->setText("Toggle");
        ToggleMenu->setMnemonicKey(KeyEvent::KEY_S);
	endEditCP(ToggleMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

	// adding actionlisteners to each of the menuitems
	ResetItem->addActionListener(&_BasicListener);
	ForceQuitItem->addActionListener(&_BasicListener);
	
	NextItem->addActionListener(&_BasicListener);
	PrevItem->addActionListener(&_BasicListener);
	FirstItem->addActionListener(&_BasicListener);
	LastItem->addActionListener(&_BasicListener);
	FlyNavigatorItem->addActionListener(&_BasicListener);
	TrackballNavigatorItem->addActionListener(&_BasicListener);
	BasicItem->addActionListener(&_BasicListener);
    RenderItem->addActionListener(&_BasicListener);
    PhysicsItem->addActionListener(&_BasicListener);
	ParticleSystemItem->addActionListener(&_BasicListener);
	AnimationItem->addActionListener(&_BasicListener);
	PauseActiveUpdatesItem->addActionListener(&_BasicListener);
	DrawBoundingVolumesItem->addActionListener(&_BasicListener);
	FrustrumCullingItem->addActionListener(&_BasicListener);
	DrawPhysicsCharacteristicsItem->addActionListener(&_BasicListener);
	ProjectMenu->addActionListener(&_BasicListener);
	EditMenu->addActionListener(&_BasicListener);
	SceneMenu->addActionListener(&_BasicListener);	
	NavigatorMenu->addActionListener(&_BasicListener);
	StatisticsMenu->addActionListener(&_BasicListener);
	ToggleMenu->addActionListener(&_BasicListener);

//	_CutActionListener = CommandActionListenerForPlayer(CutCommand::create(), _TheCommandManager);
//	_CopyActionListener = CommandActionListenerForPlayer(CopyCommand::create(), _TheCommandManager);
//	_PasteActionListener = CommandActionListenerForPlayer(PasteCommand::create(), _TheCommandManager);
//	_DeleteActionListener = CommandActionListenerForPlayer(DeleteCommand::create(), _TheCommandManager);
//	_ShowHideActionListener = CommandActionListenerForPlayer(ShowHideCommand::create(_HierarchyPanel,ApplicationPlayerPtr(this)), _TheCommandManager);
	_UndoActionListener = CommandActionListenerForPlayer(UndoCommandOfPlayer::create(ApplicationPlayerPtr(this)), _TheCommandManager);
	_RedoActionListener = CommandActionListenerForPlayer(RedoCommandOfPlayer::create(ApplicationPlayerPtr(this)), _TheCommandManager);


	ShowHideItem->addActionListener(&_BasicListener);
	DeleteItem->addActionListener(&_BasicListener);
	CutItem->addActionListener(&_BasicListener);
	CopyItem->addActionListener(&_BasicListener);
	PasteItem->addActionListener(&_BasicListener);
	
	UndoItem->addActionListener(&_UndoActionListener);
	RedoItem->addActionListener(&_RedoActionListener);

	// Creation of the menubar and addition of the menus to it
	MainMenuBar = MenuBar::create();
    MainMenuBar->addMenu(ProjectMenu);
	MainMenuBar->addMenu(EditMenu);
	MainMenuBar->addMenu(SceneMenu);
	MainMenuBar->addMenu(NavigatorMenu);
	MainMenuBar->addMenu(StatisticsMenu);
	MainMenuBar->addMenu(ToggleMenu);
  
	SplitPanelPaneltopleft = osg::Panel::create();
    
	//ToolbarLayout2= osg::BorderLayout::create();

/*	PanelTopLeftConstraints2 = osg::BorderLayoutConstraints::create();

	
	beginEditCP(PanelTopLeftConstraints2, BorderLayoutConstraints::RegionFieldMask);
        PanelTopLeftConstraints2->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    endEditCP(PanelTopLeftConstraints2, BorderLayoutConstraints::RegionFieldMask);
*/
	beginEditCP(_HierarchyPanel,Panel::PreferredSizeFieldMask);
		_HierarchyPanel->setPreferredSize(Vec2f(400,700));
	endEditCP(_HierarchyPanel,Panel::PreferredSizeFieldMask);

	// SplitPanelPaneltopleft panel elements creation
	ComboBoxModel = DefaultMutableComboBoxModel::create();
	ComboBoxModel->addElement(boost::any(std::string("Scene Graph")));
	ComboBoxModel->addElement(boost::any(std::string("Lua Graph")));
	
	beginEditCP(modeComboBox, ComboBox::ModelFieldMask | ComboBox::MinSizeFieldMask  | ComboBox::EditableFieldMask);
//		modeComboBox->setConstraints(PanelTopLeftConstraints2);
		modeComboBox->setMinSize(Vec2f(100.0,20));
		modeComboBox->setEditable(false);
		modeComboBox->setModel(ComboBoxModel);
	endEditCP(modeComboBox, ComboBox::ModelFieldMask);
	
	//modeComboBox->addActionListener(&_BasicListener);
	_ComboBoxListener.set(modeComboBox,_HierarchyPanel->TopLeftCardLayout,_HierarchyPanel);//->TopLeftTreePanel);
	ComboBoxModel->addSelectionListener(&_ComboBoxListener);
			
	// Determine where the modeComboBox starts
	modeComboBox->setSelectedIndex(0);
	
	pop = PopupMenu::create();
	
	
	HierarchyPanelLayout = osg::SpringLayout::create();

	HierarchyPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _HierarchyPanel, 5, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPaneltopleft);  
    HierarchyPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HierarchyPanel, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPaneltopleft);
	HierarchyPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HierarchyPanel, 5, SpringLayoutConstraints::WEST_EDGE, SplitPanelPaneltopleft);
	HierarchyPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _HierarchyPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, SplitPanelPaneltopleft);
   

	setupPopupMenu();

	beginEditCP(SplitPanelPaneltopleft, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		SplitPanelPaneltopleft->getChildren().push_back(_HierarchyPanel);//->TopLeftTreePanel);
		//SplitPanelPaneltopleft->getChildren().push_back(modeComboBox);
		//SplitPanelPaneltopleft->getChildren().push_back(poptrigger);
		SplitPanelPaneltopleft->setPopupMenu(pop);
		SplitPanelPaneltopleft->setLayout(HierarchyPanelLayout);
    endEditCP(SplitPanelPaneltopleft, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	/*************************************************** SplitPanel creation **********************************************************************/

	ToolbarandContentConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(ToolbarandContentConstraints, BorderLayoutConstraints::RegionFieldMask);
        ToolbarandContentConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(ToolbarandContentConstraints, BorderLayoutConstraints::RegionFieldMask);

	ToolbarandContentPanel = osg::SplitPanel::create();

	beginEditCP(ToolbarandContentPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        ToolbarandContentPanel->setConstraints(ToolbarandContentConstraints);
        ToolbarandContentPanel->setMinComponent(Toolbar);
		ToolbarandContentPanel->setMaxComponent(_ContentPanel);
        ToolbarandContentPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        ToolbarandContentPanel->setDividerPosition(.05); 
        // location from the left/top
        ToolbarandContentPanel->setDividerSize(1);
        ToolbarandContentPanel->setExpandable(false);
        //ToolbarandContentPanel->setMaxDividerPosition(.25);
        //ToolbarandContentPanel->setMinDividerPosition(.15);
    endEditCP(ToolbarandContentPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);


	SplitPanelConstraints2 = osg::BorderLayoutConstraints::create();
	
	beginEditCP(SplitPanelConstraints2, BorderLayoutConstraints::RegionFieldMask);
        SplitPanelConstraints2->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(SplitPanelConstraints2, BorderLayoutConstraints::RegionFieldMask);

	TopHalfSplitPanel = osg::SplitPanel::create();

	beginEditCP(TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        TopHalfSplitPanel->setConstraints(SplitPanelConstraints2);
        TopHalfSplitPanel->setMinComponent(SplitPanelPaneltopleft);
		TopHalfSplitPanel->setMaxComponent(ToolbarandContentPanel);
        TopHalfSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
        TopHalfSplitPanel->setDividerPosition(.25); 
        // location from the left/top
        TopHalfSplitPanel->setDividerSize(1);
        TopHalfSplitPanel->setExpandable(true);
        TopHalfSplitPanel->setMaxDividerPosition(.25);
        TopHalfSplitPanel->setMinDividerPosition(.15);
    endEditCP(TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);

	SplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(SplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(SplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
    
	SplitPanel = osg::SplitPanel::create();

	beginEditCP(SplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        SplitPanel->setConstraints(SplitPanelConstraints);
        SplitPanel->setMaxComponent(_HelperPanel);//->SplitPanelPanel);
		SplitPanel->setMinComponent(TopHalfSplitPanel);
        SplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        SplitPanel->setDividerPosition(.75); 
        // location from the left/top
        SplitPanel->setDividerSize(5);
        // SplitPanel->setExpandable(false);
        SplitPanel->setMaxDividerPosition(.95);
        SplitPanel->setMinDividerPosition(.15);
    endEditCP(SplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
	/*************************************************** END SplitPanel creation **********************************************************************/
	
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
	   MainInternalWindow->getChildren().push_back(SplitPanel);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setMenuBar(MainMenuBar);
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::MenuBarFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	MainInternalWindow->setFocusedComponent(_HelperPanel->CodeTextArea);

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
            SceneName = "Untitled Scene ";
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
			if(_HierarchyPanel->TheTreeModel->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
			{
				_HierarchyPanel->TheTreeModel->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
			}
		}
		
    }
	
    _HierarchyPanel->_TheTreeSelectionListener.setParams(_HierarchyPanel->TheTree,ApplicationPlayerPtr(this));
	_HierarchyPanel->_TheTreeSelectionListener.updateHighlight();
	beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    	DebuggerDrawingSurface->setEventProducer(MainApplication::the()->getMainWindowEventProducer());
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	_DebugViewport = createDebugViewport();

	MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(_DebugViewport);
	
	//MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().push_back(DebuggerUIForeground);
}


void ApplicationPlayer::detachDebugInterface(void)
{
	beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        DebuggerDrawingSurface->setEventProducer(NullFC);
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	osg::MFViewportPtr::iterator SearchItor(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().find(_DebugViewport));
	if(SearchItor != MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().end())
	{
		// remove viewport
		MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().erase(SearchItor);
	}

}

void ApplicationPlayer::enableDebug(bool EnableDebug)
{
    _IsDebugActive = EnableDebug;
    if(_IsDebugActive)
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
    else
    {
		detachDebugInterface();

        //Attach Listeners to the project
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
	if(e->getSource() == ResetItem)
	{
		//Reset the Project
            MainApplication::the()->getProject()->reset();
            MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getLastActiveScene());
	}
	else if(e->getSource() == ForceQuitItem)
	{
			MainApplication::the()->exit();
	}

	else if(e->getSource() == NextItem)
	{
			MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().find(MainApplication::the()->getProject()->getActiveScene()));
			SearchItor++;
			if(SearchItor == MainApplication::the()->getProject()->getScenes().end())
				SearchItor = MainApplication::the()->getProject()->getScenes().begin();
			MainApplication::the()->getProject()->setActiveScene(*SearchItor);
    
	}
	else if(e->getSource() == PrevItem)
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
	else if(e->getSource() == FirstItem)
	{
		MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
        MainApplication::the()->getProject()->setActiveScene(*SearchItor);

	}

	else if(e->getSource() == LastItem)
	{

		UInt32 SceneNumber = MainApplication::the()->getProject()->getScenes().size();
		MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
        SearchItor = SearchItor + SceneNumber - 1;
		MainApplication::the()->getProject()->setActiveScene(*SearchItor);
	}
	else if(e->getSource() == FlyNavigatorItem )
	{
		MainApplication::the()->getProject()->toggleFlyNavigation();
	}
	else if(e->getSource() == TrackballNavigatorItem )
	{
	
	}
	else if(e->getSource() == BasicItem)
	{
		toggleStatForeground(_DebugBasicStatForeground);
	}
	else if(e->getSource() == RenderItem)
	{
		toggleStatForeground(_DebugRenderStatForeground);
	}
	else if(e->getSource() == PhysicsItem)
	{
		toggleStatForeground(_DebugPhysicsStatForeground);
	}
	else if(e->getSource() == ParticleSystemItem)
	{
		toggleStatForeground(_DebugParticleSystemStatForeground);
	}
	else if(e->getSource() == AnimationItem)
	{
		toggleStatForeground(_DebugAnimationStatForeground);
	}
	else if(e->getSource() == PauseActiveUpdatesItem)
	{
		MainApplication::the()->getProject()->togglePauseActiveUpdates();
        
        //Update the Menu Item
        beginEditCP(PauseActiveUpdatesItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getProject()->getPauseActiveUpdates())
        {
            PauseActiveUpdatesItem->setText("Unpause Active Updates");
        }
        else
        {
            PauseActiveUpdatesItem->setText("Pause Active Updates");
        }
        endEditCP(PauseActiveUpdatesItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == DrawBoundingVolumesItem)
	{
		toggleDrawBoundingVolumes();

        //Update the Menu Item
        beginEditCP(DrawBoundingVolumesItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->getVolumeDrawing())
        {
            DrawBoundingVolumesItem->setText("Hide Bounding Volumes");
        }
        else
        {
            DrawBoundingVolumesItem->setText("Draw Bounding Volumes");
        }
        endEditCP(DrawBoundingVolumesItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == FrustrumCullingItem)
	{
		toggleFrustumCulling();

        //Update the Menu Item
        beginEditCP(FrustrumCullingItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->getFrustumCulling())
        {
            FrustrumCullingItem->setText("Disable Frustrum Culling");
        }
        else
        {
            FrustrumCullingItem->setText("Enable Frustrum Culling");
        }
        endEditCP(FrustrumCullingItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == DrawPhysicsCharacteristicsItem)
	{
		toggleDrawPhysicsCharacteristics();

        //Update the Menu Item
        //Add the Physics Drawable Node to the project
        beginEditCP(DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask);
        if(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->findChild(getPhysicsDrawableNode()) < 0)
        {
            DrawPhysicsCharacteristicsItem->setText("Draw Physics Characteristics");
        }
        else
        {
            DrawPhysicsCharacteristicsItem->setText("Hide Physics Characteristics");
        }
        endEditCP(DrawPhysicsCharacteristicsItem, MenuItem::TextFieldMask);
	}
	else if(e->getSource() == modeComboBox)
	{
		int temp = modeComboBox->getSelectedIndex();
		if(temp == 1)
        {
            _HierarchyPanel->TopLeftCardLayout->last(_HierarchyPanel);//->TopLeftTreePanel);
        }
        else
        {
            _HierarchyPanel->TopLeftCardLayout->first(_HierarchyPanel);//->TopLeftTreePanel);
        }
	}
	else if(e->getSource() == OpenFileButton)
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
	else if(e->getSource() == SaveFileButton)
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
	else if(e->getSource() == ShowHideItem)
	{
		 CommandPtr ShowHideItemCommand = ShowHideCommand::create(_HierarchyPanel,ApplicationPlayerPtr(this));
        _TheCommandManager->executeCommand(ShowHideItemCommand);
	}
/*	else if(e->getSource() == CloseFileButton)
	{
		_ContentPanel->closeCurrentWindow();
	}*/
	else if(e->getSource() == DeleteItem)
	{
		CommandPtr DeleteCommandPtr = DeleteCommand::create(ApplicationPlayerPtr(this),_HierarchyPanel);
        _TheCommandManager->executeCommand(DeleteCommandPtr);
	}
	
	else if(e->getSource() == CutItem)
	{

		CommandPtr CutCommandPtr = CutCommand::create(ApplicationPlayerPtr(this),_HierarchyPanel);
        _TheCommandManager->executeCommand(CutCommandPtr);
	
	}

	else if(e->getSource() == CopyItem)
	{
	
		CommandPtr CopyCommandPtr = CopyCommand::create(ApplicationPlayerPtr(this));
        _TheCommandManager->executeCommand(CopyCommandPtr);

	}
	else if(e->getSource() == PasteItem)
	{

		CommandPtr PasteCommandPtr = PasteCommand::create(ApplicationPlayerPtr(this),_HierarchyPanel);
        _TheCommandManager->executeCommand(PasteCommandPtr);

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
			MainInternalWindow->setFocusedComponent(_HelperPanel->CodeTextArea);
			_HelperPanel->InfoTabPanel->setSelectedIndex(0);

		}

		if(e->getKey() == KeyEvent::KEY_S && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
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
	if(_HierarchyPanel->TheTreeModel->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
	{
		_HierarchyPanel->TheTreeModel->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
	}
	
	//_HierarchyPanel->_TheTreeSelectionListener.setParams(_HierarchyPanel->TheTree,ApplicationPlayerPtr(this));
	_HierarchyPanel->_TheTreeSelectionListener.updateHighlight();
	
}

void ApplicationPlayer::updateDebugSceneChange(void)
{
	//Make sure the Debug Viewport is on top
	MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(_DebugViewport);
	MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(_DebugViewport);


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
		SWARNING<<"Just blocked the input"<<std::endl;
	}

}

ViewportPtr ApplicationPlayer::createDebugViewport(void)
{

	CameraPtr OriginalCamera = MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getCamera();

	CameraPtr DebugCamera = CameraPtr::dcast(OriginalCamera->shallowCopy());
	
    //Camera Transformation Node	
	TransformPtr DebugBeaconTransform = Transform::create();
    beginEditCP(DebugBeaconTransform, Transform::MatrixFieldMask);
		DebugBeaconTransform->setMatrix(OriginalCamera->getBeacon()->getToWorld());
    endEditCP(DebugBeaconTransform, Transform::MatrixFieldMask);

	NodePtr DebugBeacon = osg::Node::create();
    beginEditCP(DebugBeacon, Node::CoreFieldMask);
        DebugBeacon->setCore(DebugBeaconTransform);
    endEditCP(DebugBeacon, Node::CoreFieldMask);

    //Debug Root Node
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(DebugBeacon);//CameraBeaconNode);
    endEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Background
	PassiveBackgroundPtr DefaultBackground = PassiveBackground::create();

    ViewportPtr DebugViewport = Viewport::create();
	
	beginEditCP(DebugViewport);
        DebugViewport->setCamera                  (DebugCamera);
        DebugViewport->setRoot                    (DefaultRootNode);
        DebugViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
        DebugViewport->setBackground              (DefaultBackground);
        DebugViewport->getForegrounds().push_back (DebuggerUIForeground);
    endEditCP(DebugViewport);

    return DebugViewport;
}

void ApplicationPlayer::updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager)
{
	
	beginEditCP(UndoItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
		UndoItem->setEnabled(_TheUndoManager->canUndo());
		if(_TheUndoManager->canUndo())
		{
			UndoItem->setText(TheUndoManager->getUndoPresentationName());
		}
		else
		{
			UndoItem->setText("Undo");
		}
	endEditCP(UndoItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
	
	beginEditCP(RedoItem, MenuItem::EnabledFieldMask);
		RedoItem->setEnabled(TheUndoManager->canRedo());
		if(_TheUndoManager->canRedo())
		{
			RedoItem->setText(_TheUndoManager->getRedoPresentationName());
		}
		else
		{
			RedoItem->setText("Redo");
		}
	endEditCP(RedoItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
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
//	_CutActionListener(NULL,NULL),
//	_CopyActionListener(NULL,NULL),
//	_PasteActionListener(NULL,NULL),
	//_DeleteActionListener(NULL,NULL),
	//_ShowHideActionListener(NULL,NULL),
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
//	_CutActionListener(NULL,NULL),
//	_CopyActionListener(NULL,NULL),
//	_PasteActionListener(NULL,NULL),
//	_DeleteActionListener(NULL,NULL),
//	_ShowHideActionListener(NULL,NULL),
	_UndoActionListener(NULL,NULL),
	_RedoActionListener(NULL,NULL),
	_CommandManagerListener(ApplicationPlayerPtr(this))
{
	_TheUndoManager = UndoManager::create();
	//_TheUndoManager->addChangeListener(_CommandManagerListener);
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
	if(_ApplicationPlayer->SelectedNode != NullFC)		// selected node is the node that is being selected.
    {													// highlight node is the pointer to the bounding box for the selected node
	 std::string coreName= _ApplicationPlayer->SelectedNode->getCore()->getTypeName();

		// calc the world bbox of the highlight object
		#ifndef OSG_2_PREP
		DynamicVolume vol;
		#else
		BoxVolume      vol;
		#endif
		_ApplicationPlayer->SelectedNode->getWorldVolume(vol);

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


		beginEditCP(_ApplicationPlayer->highlightNode->getCore(), Geometry::PositionsFieldMask);
		GeometryPtr::dcast(_ApplicationPlayer->highlightNode->getCore())->setPositions(temphighlightPoints);
		endEditCP  (_ApplicationPlayer->highlightNode->getCore(), Geometry::PositionsFieldMask);


    }
}


void ApplicationPlayer::setupPopupMenu()
{
		beginEditCP(pop);
		pop->addItem(ShowHideItem);
		pop->addSeparator();
		pop->addItem(CutItem);	
		pop->addItem(CopyItem);	
		pop->addItem(PasteItem);	
		pop->addItem(DeleteItem);	
		endEditCP(pop);
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
        beginEditCP(_ApplicationPlayer->SplitPanelPaneltopleft);
            _ApplicationPlayer->SplitPanelPaneltopleft->setPopupMenu(_ApplicationPlayer->pop);
        endEditCP(_ApplicationPlayer->SplitPanelPaneltopleft);
        _ApplicationPlayer->_ContentPanel->setVisible(false);

    }
    else 
    {
        beginEditCP(_ApplicationPlayer->SplitPanelPaneltopleft);
            _ApplicationPlayer->SplitPanelPaneltopleft->setPopupMenu(NullFC);
        endEditCP(_ApplicationPlayer->SplitPanelPaneltopleft);

        _TopLeftCardLayout->last(_TopLeftTreePanel);
        _ApplicationPlayer->_ContentPanel->setVisible(true);
    }
}

void ApplicationPlayer::ComboBoxListener::set(ComboBoxPtr ComboBoxP,CardLayoutPtr TopLeftCardLayout,PanelPtr TopLeftTreePanel)
{
    _ComboBox = ComboBoxP;
    _TopLeftCardLayout = TopLeftCardLayout;
    _TopLeftTreePanel = TopLeftTreePanel;
}

ApplicationPlayer::ComboBoxListener::ComboBoxListener(ApplicationPlayerPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
    _ComboBox = NullFC;
    _TopLeftCardLayout = NullFC;
    _TopLeftTreePanel = NullFC;
}
