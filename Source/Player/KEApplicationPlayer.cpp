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
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>

#include "KEApplicationPlayer.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"
#include "Application/KEMainApplication.h"
#include <OpenSG/UserInterface/OSGFlowLayout.h>

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
}


void ApplicationPlayer::dettachApplication(void)
{
	MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_PlayerKeyListener);
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
        FrustrumCullingItem->setText("Frustrum Culling ");
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

	// creation of menus and addition of menu items to them
	ProjectMenu = Menu::create();
    ProjectMenu->addItem(ResetItem);
	ProjectMenu->addSeparator();
    ProjectMenu->addItem(ForceQuitItem);
    
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
	SceneMenu->addActionListener(&_BasicListener);	
	NavigatorMenu->addActionListener(&_BasicListener);
	StatisticsMenu->addActionListener(&_BasicListener);
	ToggleMenu->addActionListener(&_BasicListener);
	
	// Creation of the menubar and addition of the menus to it
	MainMenuBar = MenuBar::create();
    MainMenuBar->addMenu(ProjectMenu);
	MainMenuBar->addMenu(SceneMenu);
	MainMenuBar->addMenu(NavigatorMenu);
	MainMenuBar->addMenu(StatisticsMenu);
	MainMenuBar->addMenu(ToggleMenu);
    
	/*************************************************** END Menu creation *******************************************************************/
	/*************************************************** Tab Panel creation *******************************************************************/
	
	// Create a CodeTextArea
    CodeTextArea = osg::TextArea::create();

    beginEditCP(CodeTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask ); //| FocusedFieldMask
        //CodeTextArea->setPreferredSize(Vec2f(300, 200));
        //CodeTextArea->setMinSize(Vec2f(300, 100));
        //CodeTextArea->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        //CodeTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        //CodeTextArea->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        // Determine the font and initial text
        CodeTextArea->setText("");
		//setFocused(true);
//        CodeTextArea->setFont(ExampleFont);
        // This will select the "a" from above
        //CodeTextArea->setSelectionStart(2);
        //CodeTextArea->setSelectionEnd(3);
        //CodeTextArea->setCaretPosition(2);
        //CodeTextArea->setLineWrap(false);
		//CodeTextArea->setEditable(false);
    endEditCP(CodeTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
	
	
    // Create a ScrollPanel
    TabContentA = ScrollPanel::create();
    beginEditCP(TabContentA, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentA->setPreferredSize(Vec2f(300,1200));
        TabContentA->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		endEditCP(TabContentA, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the CodeTextArea to the ScrollPanel so it is displayed
	TabContentA->setViewComponent(CodeTextArea);
	// Create an ErrorTextArea	
	ErrorTextArea = osg::TextArea::create();

    beginEditCP(ErrorTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
        //ErrorTextArea->setPreferredSize(Vec2f(300, 1200));
        //ErrorTextArea->setMinSize(Vec2f(300, 300));
        //ErrorTextArea->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        //ErrorTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        //ErrorTextArea->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        // Determine the font and initial text
        ErrorTextArea->setText("Error List");
//        ErrorTextArea->setFont(ExampleFont);
        // This will select the "a" from above
        //ErrorTextArea->setSelectionStart(2);
        //ErrorTextArea->setSelectionEnd(3);
        //ErrorTextArea->setCaretPosition(2);
        //ErrorTextArea->setLineWrap(false);
		ErrorTextArea->setEditable(false);
    endEditCP(ErrorTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
        
    // Create a ScrollPanel
    TabContentB = ScrollPanel::create();
    beginEditCP(TabContentB, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentB->setPreferredSize(Vec2f(200,1200));
        TabContentB->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TabContentB, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the ErrorTextArea to the ScrollPanel so it is displayed
	TabContentB->setViewComponent(ErrorTextArea);

	// Create a StackTraceTextArea
	StackTraceTextArea = osg::TextArea::create();

    beginEditCP(StackTraceTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
        //StackTraceTextArea->setPreferredSize(Vec2f(300, 200));
        //StackTraceTextArea->setMinSize(Vec2f(300, 300));
        //StackTraceTextArea->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        //StackTraceTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        //StackTraceTextArea->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        // Determine the font and initial text
        StackTraceTextArea->setText("Stack Trace");
//        StackTraceTextArea->setFont(ExampleFont);
        // This will select the "a" from above
        //StackTraceTextArea->setSelectionStart(2);
        //StackTraceTextArea->setSelectionEnd(3);
        //StackTraceTextArea->setCaretPosition(2);
        //StackTraceTextArea->setLineWrap(false);
		StackTraceTextArea->setEditable(false);
    endEditCP(StackTraceTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
        
    // Create a ScrollPanel
    TabContentC = ScrollPanel::create();
    beginEditCP(TabContentC, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentC->setPreferredSize(Vec2f(200,1200));
        TabContentC->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TabContentC, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the StackTraceTextArea to the ScrollPanel so it is displayed
	TabContentC->setViewComponent(StackTraceTextArea);

	// creating the labels for the various tabs
	
	TabPanel1 = osg::Label::create();
    TabPanel2 = osg::Label::create();
    TabPanel3 = osg::Label::create();


	// set the fields of the labels
	beginEditCP(TabPanel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel1->setText("Lua Console");
        TabPanel1->setBorders(NullFC);
        TabPanel1->setBackgrounds(NullFC);
	endEditCP(TabPanel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	beginEditCP(TabPanel2, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel2->setText("Error");
        TabPanel2->setBorders(NullFC);
        TabPanel2->setBackgrounds(NullFC);
    endEditCP(TabPanel2, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	LuaManager::the()->addLuaListener(&_LuaErrorListener);
        
    beginEditCP(TabPanel3, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel3->setText("Stack");
        TabPanel3->setBorders(NullFC);
        TabPanel3->setBackgrounds(NullFC);
    endEditCP(TabPanel3, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	// creating the tab panel
	InfoTabPanel= osg::TabPanel::create();
    beginEditCP(InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		//InfoTabPanel->setPreferredSize(MainApplication::the()->getMainWindowEventProducer()->getDesktopSize());
		InfoTabPanel->setPreferredSize(Vec2f(1200,200));
	    InfoTabPanel->addTab(TabPanel1, TabContentA);
        InfoTabPanel->addTab(TabPanel2, TabContentB);
        InfoTabPanel->addTab(TabPanel3, TabContentC);
		InfoTabPanel->setTabAlignment(0.5f);
        InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    InfoTabPanel->setSelectedIndex(0);
	
	executeBtn=osg::Button::create();

	beginEditCP(executeBtn,Button::TextFieldMask);// | Button::AcceleratorKeyFieldMask | Button::AcceleratorModifiersFieldMask | Button::MnemonicKeyFieldMask);
		executeBtn->setText("EXECUTE");
		executeBtn->setPreferredSize(Vec2f(100,30));
		//executeBtn->setAcceleratorKey(KeyEvent::KEY_X);
        //executeBtn->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
		//executeBtn->setMnemonicKey(KeyEvent::KEY_X);
	endEditCP(executeBtn,Button::TextFieldMask);

	executeBtn->addActionListener(&_BasicListener);

	ListSelectionModelPtr HistoryListSelectionModel(new DefaultListSelectionModel);
// 52
	HistoryListModel = DefaultListModel::create();

	updateListBox();
	
	HistoryList = List::create();
	beginEditCP(HistoryList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
	    HistoryList->setPreferredSize(Vec2f(100, 100));
	    HistoryList->setOrientation(List::VERTICAL_ORIENTATION);
		//HistoryList->setOrientation(List::HORIZONTAL_ORIENTATION);
		HistoryList->setModel(HistoryListModel);
	endEditCP(HistoryList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);

	//HistoryList.setMode(DefaultListSelectionModel::SINGLE_SELECTION);

	HistoryList->setSelectionModel(HistoryListSelectionModel);

	HistoryScrollPanel = ScrollPanel::create();
	beginEditCP(HistoryScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
		HistoryScrollPanel->setPreferredSize(Vec2f(100,100));
		HistoryScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		//HistoryScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
	endEditCP(HistoryScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	HistoryScrollPanel->setViewComponent(HistoryList);
	
	historyLabel = osg::Label::create();
	historyLabel2 = osg::Label::create();


	// set the fields of the labels

	beginEditCP(historyLabel, Label::TextFieldMask);
        historyLabel->setText("History");
   	endEditCP(historyLabel, Label::TextFieldMask);
    beginEditCP(historyLabel2, Label::TextFieldMask);
        historyLabel2->setText("History2");
   	endEditCP(historyLabel2, Label::TextFieldMask);

	// Creating a panel for adding the tabpanel to it and setting springlayout as the layout
	SplitPanelPanel = osg::Panel::create();
	SplitPanelPaneltopleft = osg::Panel::create();
    
	PanelFlowLayout = osg::SpringLayout::create();
	PanelFlowLayout2= osg::FlowLayout::create();
    
	beginEditCP(PanelFlowLayout2, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask | FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        PanelFlowLayout2->setHorizontalGap(3.0f);
        PanelFlowLayout2->setVerticalGap(3.0f);
		PanelFlowLayout2->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
        PanelFlowLayout2->setMajorAxisAlignment(0.5f);
        PanelFlowLayout2->setMinorAxisAlignment(1.0f);
    endEditCP(PanelFlowLayout2, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask | FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
    


	int SPACE_FOR_BUTTON = 200;

	beginEditCP(PanelFlowLayout2);
        // NOTHING : )
    endEditCP(PanelFlowLayout2); 

    // OverlayLayout has no options to edit!
    beginEditCP(PanelFlowLayout);
        // NOTHING : )
    endEditCP(PanelFlowLayout); 

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InfoTabPanel, 5, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InfoTabPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, SplitPanelPanel); 
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InfoTabPanel, -1*SPACE_FOR_BUTTON, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InfoTabPanel, 5, SpringLayoutConstraints::WEST_EDGE, SplitPanelPanel);  

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, historyLabel, 5, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, historyLabel, 25, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPanel); 
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, historyLabel, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, historyLabel, 5, SpringLayoutConstraints::EAST_EDGE, InfoTabPanel);  

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, HistoryScrollPanel, 5, SpringLayoutConstraints::SOUTH_EDGE, historyLabel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, HistoryScrollPanel, -5, SpringLayoutConstraints::NORTH_EDGE, executeBtn); 
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, HistoryScrollPanel, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, HistoryScrollPanel, 5, SpringLayoutConstraints::EAST_EDGE, InfoTabPanel);  

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, executeBtn, 15, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, executeBtn, -15, SpringLayoutConstraints::SOUTH_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, executeBtn, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, executeBtn, 5, SpringLayoutConstraints::EAST_EDGE, InfoTabPanel);  
    
	
	beginEditCP(SplitPanelPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		SplitPanelPanel->getChildren().push_back(InfoTabPanel);
		SplitPanelPanel->getChildren().push_back(historyLabel);
		SplitPanelPanel->getChildren().push_back(HistoryScrollPanel);		
		SplitPanelPanel->getChildren().push_back(executeBtn);
        SplitPanelPanel->setLayout(PanelFlowLayout);
        //SplitPanelPanel->setLayout(PanelFlowLayout);
    endEditCP(SplitPanelPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	// SplitPanelPaneltopleft panel elements creation
	ComboBoxModel = DefaultMutableComboBoxModel::create();
	ComboBoxModel->addElement(boost::any(std::string("Scene Graph")));
	ComboBoxModel->addElement(boost::any(std::string("Lua Graph")));
	ComboBoxPtr ComboBox = ComboBox::create();
	beginEditCP(ComboBox, ComboBox::ModelFieldMask | ComboBox::MinSizeFieldMask  | ComboBox::EditableFieldMask);
		ComboBox->setMinSize(Vec2f(100.0,20));
		ComboBox->setEditable(false);
		ComboBox->setModel(ComboBoxModel);
	endEditCP(ComboBox, ComboBox::ModelFieldMask);
	
	// Determine where the ComboBox starts
	ComboBox->setSelectedIndex(0);


	beginEditCP(SplitPanelPaneltopleft, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		//SplitPanelPaneltopleft->getChildren().push_back(historyLabel2);
		SplitPanelPaneltopleft->getChildren().push_back(ComboBox);
		SplitPanelPaneltopleft->setLayout(PanelFlowLayout2);
    endEditCP(SplitPanelPaneltopleft, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	/*************************************************** END Tab Panel creation *******************************************************************/
	/*************************************************** SplitPanel creation **********************************************************************/

	SplitPanelConstraints2 = osg::BorderLayoutConstraints::create();
	
	beginEditCP(SplitPanelConstraints2, BorderLayoutConstraints::RegionFieldMask);
        SplitPanelConstraints2->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(SplitPanelConstraints2, BorderLayoutConstraints::RegionFieldMask);

	TopHalfSplitPanel = osg::SplitPanel::create();

	beginEditCP(TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        TopHalfSplitPanel->setConstraints(SplitPanelConstraints2);
        TopHalfSplitPanel->setMinComponent(SplitPanelPaneltopleft);
		//TopHalfSplitPanel->setMinComponent(SplitPanelPanel);
        TopHalfSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
        TopHalfSplitPanel->setDividerPosition(.25); 
        // location from the left/top
        TopHalfSplitPanel->setDividerSize(1);
        TopHalfSplitPanel->setExpandable(true);
        TopHalfSplitPanel->setMaxDividerPosition(.25);
        TopHalfSplitPanel->setMinDividerPosition(.15);
    endEditCP(TopHalfSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
	
	// Creation of the splitpanel ,the only component of which is the SplitPanelPanel created previously
/*	SplitPanelPanel2 = osg::Panel::create();

	beginEditCP(SplitPanelPanel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		SplitPanelPanel2->getChildren().push_back(TopHalfSplitPanel);
		SplitPanelPanel2->setLayout(PanelFlowLayout2);
        //SplitPanelPanel2->setLayout(PanelFlowLayout);
    endEditCP(SplitPanelPanel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
*/
	SplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(SplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(SplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
    
	SplitPanel = osg::SplitPanel::create();

	beginEditCP(SplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        SplitPanel->setConstraints(SplitPanelConstraints);
        SplitPanel->setMaxComponent(SplitPanelPanel);
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
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setMenuBar(MainMenuBar);
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::MenuBarFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	MainInternalWindow->setFocusedComponent(CodeTextArea);

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
	beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    	DebuggerDrawingSurface->setEventProducer(MainApplication::the()->getMainWindowEventProducer());
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    	
	MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().push_back(DebuggerUIForeground);
}


void ApplicationPlayer::detachDebugInterface(void)
{
	beginEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        DebuggerDrawingSurface->setEventProducer(NullFC);
    endEditCP(DebuggerDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	// if the debuginterface foreground is present in the list of foreground objects then delete it (the if condition if not mentioned would throw an exception)
	if((find(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().begin(),MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().end(),DebuggerUIForeground))!=MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().end())
	MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().erase(find(MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().begin(),MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().end(),DebuggerUIForeground));
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
	if(e->getSource() == executeBtn)
	{
		LuaManager::the()->runScript(std::string(CodeTextArea->getText()));
		list_of_commands.push_back(std::string(CodeTextArea->getText()));
		updateListBox();
	}
	else if(e->getSource() == ResetItem)
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
	}
	else if(e->getSource() == DrawBoundingVolumesItem)
	{
		toggleDrawBoundingVolumes();
	}
	else if(e->getSource() == FrustrumCullingItem)
	{
		toggleFrustumCulling();
	}
	else if(e->getSource() == DrawPhysicsCharacteristicsItem)
	{
		toggleDrawPhysicsCharacteristics();
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
		// shortcut to execute Lua code
		if(e->getKey() == KeyEvent::KEY_X && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
		{
			LuaManager::the()->runScript(std::string(CodeTextArea->getText()));
			list_of_commands.push_back(std::string(CodeTextArea->getText()));
			updateListBox();
			
		}
		if(e->getKey() == KeyEvent::KEY_C && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
		{
			MainInternalWindow->setFocusedComponent(CodeTextArea);
			InfoTabPanel->setSelectedIndex(0);

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
    NodePtr CurrentRoot(MainApplication::the()->getProject()->getActiveNode());
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
    MFForegroundPtr::iterator SearchItor(MainApplication::the()->getProject()->getActiveForegrounds().find(TheForeground));
    if( SearchItor != MainApplication::the()->getProject()->getActiveForegrounds().end())
    {
        //If the Stat foreground is present then switch it off
        beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
    }
    else
    {
        //If not present then switch all other stat foregrounds off
        hideAllStatForegrounds();
        //and switch it on
        beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
            MainApplication::the()->getProject()->getActiveForegrounds().push_back(TheForeground);
        endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
        MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->setStatistics(&TheForeground->getCollector());
    }
}

void ApplicationPlayer::hideAllStatForegrounds(void)
{
    
    MFForegroundPtr::iterator SearchItor;

    beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
        //Hide Basic Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugBasicStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Render Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugRenderStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Physics Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugPhysicsStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Particle System Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugParticleSystemStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Animation Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugAnimationStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
    endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
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

void ApplicationPlayer::updateDebugSceneChange(void)
{
    updateGotoSceneMenuItems(MainApplication::the()->getProject());

	MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().push_back(DebuggerUIForeground);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationPlayer::ApplicationPlayer(void) :
    Inherited(),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
	_BasicListener(ApplicationPlayerPtr(this)),
	_GotoSceneItemListener(ApplicationPlayerPtr(this)),
	_ProjectListener(ApplicationPlayerPtr(this)),
	_LuaErrorListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false),
    _PhysDrawable(NullFC),
    _PhysDrawableNode(NullFC),
    _WasMouseHidden(false),
    _WasMouseAttached(false)
{
    initDebugStatForegrounds();
}

ApplicationPlayer::ApplicationPlayer(const ApplicationPlayer &source) :
    Inherited(source),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
	_BasicListener(ApplicationPlayerPtr(this)),
	_GotoSceneItemListener(ApplicationPlayerPtr(this)),
	_ProjectListener(ApplicationPlayerPtr(this)),
	_LuaErrorListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false),
    _DebugBasicStatForeground(source._DebugBasicStatForeground),
    _DebugRenderStatForeground(source._DebugRenderStatForeground),
    _DebugPhysicsStatForeground(source._DebugPhysicsStatForeground),
    _DebugParticleSystemStatForeground(source._DebugParticleSystemStatForeground),
    _DebugAnimationStatForeground(source._DebugAnimationStatForeground),
    _PhysDrawable(NullFC),
    _PhysDrawableNode(NullFC),
    _WasMouseHidden(false),
    _WasMouseAttached(false)

{
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

ApplicationPlayer::LuaErrorListener::LuaErrorListener(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer=TheApplicationPlayer;
}

void ApplicationPlayer::LuaErrorListener::error(const LuaErrorEventPtr e)
{
    std::string ErrorType("");
    switch(e->getStatus())
    {
        case LUA_ERRSYNTAX:
            //Syntax Error
            ErrorType = "Lua Syntax Error";
            break;
        case LUA_ERRMEM:
            //Memory Allocation Error
            ErrorType = "Lua Memory Allocation Error";
            break;
        case LUA_ERRRUN:
            //Memory Allocation Error
            ErrorType = "Lua Runtime Error";
            break;
        case LUA_ERRERR:
            //Memory Allocation Error
            ErrorType = "Lua Error in Error Handler";
            break;
        default:
            //Unknown
            ErrorType = "Lua Unknown Error";
            break;
    }
    _ApplicationPlayer->ErrorTextArea->clear();
    if(_ApplicationPlayer->ErrorTextArea->getText().size() != 0)
    {
        _ApplicationPlayer->ErrorTextArea->write("\n");
    }
    _ApplicationPlayer->ErrorTextArea->write(ErrorType + ":\n    " + e->getErrorString());

    //Select the Error Tab
    _ApplicationPlayer->InfoTabPanel->setSelectedIndex(1);

    //Fill Stack Trace
    if(e->getStackTraceEnabled() && 
            (e->getStatus() == LUA_ERRMEM ||
             e->getStatus() == LUA_ERRERR ||
             e->getStatus() == LUA_ERRRUN))
    {
        std::stringstream ss;
        ss << "Lua Stack Trace: " << std::endl;

        MFString::StorageType::const_iterator ListItor(e->getMFStackTrace()->begin());
        for(; ListItor != e->getMFStackTrace()->end() ; ++ListItor)
        {
            ss << "     " << (*ListItor) << std::endl;
        }
        _ApplicationPlayer->StackTraceTextArea->clear();
        _ApplicationPlayer->StackTraceTextArea->write(ss.str());
    }
}

void ApplicationPlayer::updateListBox(void)
{
	// clear off 
	HistoryListModel->clear();
	
	for(int i=list_of_commands.size()-1;i>=0;i--)
	{
		HistoryListModel->pushBack(boost::any(list_of_commands[i]));
		//std::cout<<list_of_commands[i]<<"***";
	}
	std::cout<<std::endl;
}

