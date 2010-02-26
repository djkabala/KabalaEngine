

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

    TheTree = Tree::create();
	TheTreeModel = SceneGraphTreeModel::create();

	beginEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setModel(TheTreeModel);
    endEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);

	//NodePtr SelectedNode = NullFC;// MainApplication::the()->getProject()->getOverlayNode()->getChild(0);
	//NodePtr SelectedNode = createHiglightNode(nodetohighlight,colorofhightlight);
  //  _TheTreeSelectionListener.setParams(TheTree,SelectedNode);
    TheTree->getSelectionModel()->addTreeSelectionListener(&_TheTreeSelectionListener);
	
	
    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    BorderLayoutConstraintsPtr SceneTreeConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);
        SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);

    TreeScrollPanel = ScrollPanel::create();
    beginEditCP(TreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
        TreeScrollPanel->setPreferredSize(Vec2s(350,300));
        TreeScrollPanel->setConstraints(SceneTreeConstraints);
        //TreeScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TreeScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
    TreeScrollPanel->setViewComponent(TheTree);
	/////////////////////////////////////////////////////////////////////////////////

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

	ShowHideItem->addActionListener(&_BasicListener);
	DeleteItem->addActionListener(&_BasicListener);
	CutItem->addActionListener(&_BasicListener);
	CopyItem->addActionListener(&_BasicListener);
	PasteItem->addActionListener(&_BasicListener);
	
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

	
	TabContentD = osg::Panel::create();

	NodeNameLabel = Label::create();
    beginEditCP(NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeNameLabel->setText("Name");
        NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeNameValueLabel = Label::create();
    beginEditCP(NodeNameValueLabel, Label::PreferredSizeFieldMask);
        NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeNameValueLabel, Label::PreferredSizeFieldMask);

    NodeCoreTypeLabel = Label::create();
    beginEditCP(NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeCoreTypeLabel->setText("Core Type");
        NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeCoreTypeValueLabel = Label::create();
    beginEditCP(NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);
        NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);

    NodeMinLabel = Label::create();
    beginEditCP(NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeMinLabel->setText("Min");
        NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeMinValueLabel = Label::create();
    beginEditCP(NodeMinValueLabel, Label::PreferredSizeFieldMask);
        NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeMinValueLabel, Label::PreferredSizeFieldMask);

    NodeMaxLabel = Label::create();
    beginEditCP(NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeMaxLabel->setText("Max");
        NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeMaxValueLabel = Label::create();
    beginEditCP(NodeMaxValueLabel, Label::PreferredSizeFieldMask);
        NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeMaxValueLabel, Label::PreferredSizeFieldMask);

    NodeCenterLabel = Label::create();
    beginEditCP(NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeCenterLabel->setText("Center");
        NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeCenterValueLabel = Label::create();
    beginEditCP(NodeCenterValueLabel, Label::PreferredSizeFieldMask);
        NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeCenterValueLabel, Label::PreferredSizeFieldMask);

    NodeTriCountLabel = Label::create();
    beginEditCP(NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeTriCountLabel->setText("TriCount");
        NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeTriCountValueLabel = Label::create();
    beginEditCP(NodeTriCountValueLabel, Label::PreferredSizeFieldMask);
        NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeTriCountValueLabel, Label::PreferredSizeFieldMask);

    NodeTravMaskLabel = Label::create();
    beginEditCP(NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeTravMaskLabel->setText("Traversal Mask");
        NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeTravMaskValueLabel = Label::create();
    beginEditCP(NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);
        NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);

    NodeOcclusionMaskLabel = Label::create();
    beginEditCP(NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeOcclusionMaskLabel->setText("Occlusion Mask");
        NodeOcclusionMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeOcclusionMaskValueLabel = Label::create();
    beginEditCP(NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);
        NodeOcclusionMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);

    NodeActiveLabel = Label::create();
    beginEditCP(NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeActiveLabel->setText("Active");
        NodeActiveLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeActiveValueLabel = Label::create();
    beginEditCP(NodeActiveValueLabel, Label::PreferredSizeFieldMask);
        NodeActiveValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeActiveValueLabel, Label::PreferredSizeFieldMask);
    
	////////////////////////// not addded
    GridLayoutPtr TabContentDLayout = osg::GridLayout::create();

    beginEditCP(TabContentDLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
	    TabContentDLayout->setRows(9);
        TabContentDLayout->setColumns(2);
        TabContentDLayout->setHorizontalGap(2);
        TabContentDLayout->setVerticalGap(2);
    endEditCP(TabContentDLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
	////////////////////////// not addded ended

	beginEditCP(TabContentD,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);

        TabContentD->setPreferredSize(Vec2f(100.0f, 200.0f));
        TabContentD->setLayout(TabContentDLayout);
        TabContentD->getChildren().push_back(NodeNameLabel);
        TabContentD->getChildren().push_back(NodeNameValueLabel);
        TabContentD->getChildren().push_back(NodeCoreTypeLabel);
        TabContentD->getChildren().push_back(NodeCoreTypeValueLabel);
        TabContentD->getChildren().push_back(NodeMinLabel);
        TabContentD->getChildren().push_back(NodeMinValueLabel);
        TabContentD->getChildren().push_back(NodeMaxLabel);
        TabContentD->getChildren().push_back(NodeMaxValueLabel);
        TabContentD->getChildren().push_back(NodeCenterLabel);
        TabContentD->getChildren().push_back(NodeCenterValueLabel);
        TabContentD->getChildren().push_back(NodeTriCountLabel);
        TabContentD->getChildren().push_back(NodeTriCountValueLabel);
        TabContentD->getChildren().push_back(NodeTravMaskLabel);
        TabContentD->getChildren().push_back(NodeTravMaskValueLabel);
        TabContentD->getChildren().push_back(NodeOcclusionMaskLabel);
        TabContentD->getChildren().push_back(NodeOcclusionMaskValueLabel);
        TabContentD->getChildren().push_back(NodeActiveLabel);
        TabContentD->getChildren().push_back(NodeActiveValueLabel);

	endEditCP(TabContentD,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);


	// creating the labels for the various tabs
	
	TabPanel1 = osg::Label::create();
    TabPanel2 = osg::Label::create();
    TabPanel3 = osg::Label::create();
	TabPanel4 = osg::Label::create();


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
    
	beginEditCP(TabPanel4, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel4->setText("Properties");
        TabPanel4->setBorders(NullFC);
        TabPanel4->setBackgrounds(NullFC);
    endEditCP(TabPanel4, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    

	// creating the tab panel
	InfoTabPanel= osg::TabPanel::create();
    beginEditCP(InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		//InfoTabPanel->setPreferredSize(MainApplication::the()->getMainWindowEventProducer()->getDesktopSize());
		InfoTabPanel->setPreferredSize(Vec2f(1200,200));
	    InfoTabPanel->addTab(TabPanel1, TabContentA);
        InfoTabPanel->addTab(TabPanel2, TabContentB);
        InfoTabPanel->addTab(TabPanel3, TabContentC);
		InfoTabPanel->addTab(TabPanel4, TabContentD);
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
	PanelFlowLayout2= osg::BorderLayout::create();

	PanelTopLeftConstraints1 = osg::BorderLayoutConstraints::create();
	PanelTopLeftConstraints2 = osg::BorderLayoutConstraints::create();

	beginEditCP(PanelTopLeftConstraints1, BorderLayoutConstraints::RegionFieldMask);
        PanelTopLeftConstraints1->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(PanelTopLeftConstraints1, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(PanelTopLeftConstraints2, BorderLayoutConstraints::RegionFieldMask);
        PanelTopLeftConstraints2->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    endEditCP(PanelTopLeftConstraints2, BorderLayoutConstraints::RegionFieldMask);


	TopLeftCardLayout = osg::CardLayout::create(); 
	TopLeftTreePanel = osg::Panel::create();

	ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();

	beginEditCP(ExampleButton1, Button::TextFieldMask);
        ExampleButton1->setText("Scene Graph");
    endEditCP(ExampleButton1, Button::TextFieldMask);

	beginEditCP(ExampleButton2, Button::TextFieldMask);
        ExampleButton2->setText("Lua Graph");
    endEditCP(ExampleButton2, Button::TextFieldMask);


	beginEditCP(TopLeftTreePanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
        TopLeftTreePanel->setLayout(TopLeftCardLayout);
        TopLeftTreePanel->getChildren().push_back(ExampleButton2);
		TopLeftTreePanel->getChildren().push_back(TreeScrollPanel);
        //TopLeftTreePanel->getChildren().push_back(ExampleButton1);
        TopLeftTreePanel->setConstraints(PanelTopLeftConstraints1);
    endEditCP(TopLeftTreePanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);


	// SplitPanelPaneltopleft panel elements creation
	ComboBoxModel = DefaultMutableComboBoxModel::create();
	ComboBoxModel->addElement(boost::any(std::string("Lua Graph")));
	ComboBoxModel->addElement(boost::any(std::string("Scene Graph")));
	ComboBoxPtr ComboBox = ComboBox::create();
	beginEditCP(ComboBox, ComboBox::ModelFieldMask | ComboBox::MinSizeFieldMask  | ComboBox::EditableFieldMask);
		ComboBox->setConstraints(PanelTopLeftConstraints2);
		ComboBox->setMinSize(Vec2f(100.0,20));
		ComboBox->setEditable(false);
		ComboBox->setModel(ComboBoxModel);
	endEditCP(ComboBox, ComboBox::ModelFieldMask);
	
	//ComboBox->addActionListener(&_BasicListener);
	_ComboBoxListener.set(ComboBox,TopLeftCardLayout,TopLeftTreePanel);
	ComboBoxModel->addSelectionListener(&_ComboBoxListener);
			
	// Determine where the ComboBox starts
	ComboBox->setSelectedIndex(0);

	pop = PopupMenu::create();
	//poptrigger = Button::create();

	//beginEditCP(poptrigger);
	//	poptrigger->setPopupMenu(pop);
	//	poptrigger->setConstraints(PanelTopLeftConstraints3);
	//endEditCP(poptrigger);

	setupPopupMenu();

	beginEditCP(SplitPanelPaneltopleft, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		SplitPanelPaneltopleft->getChildren().push_back(TopLeftTreePanel);
		SplitPanelPaneltopleft->getChildren().push_back(ComboBox);
		//SplitPanelPaneltopleft->getChildren().push_back(poptrigger);
		//SplitPanelPaneltopleft->setPopupMenu(pop);
		SplitPanelPaneltopleft->setLayout(PanelFlowLayout2);
    endEditCP(SplitPanelPaneltopleft, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);


	int SPACE_FOR_BUTTON = 200;

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
			if(TheTreeModel->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
			{
				TheTreeModel->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
			}
		}
		
    }
	
    _TheTreeSelectionListener.setParams(TheTree);
	_TheTreeSelectionListener.updateHighlight();
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
	else if(e->getSource() == ComboBox)
	{
		std::cout<<"COMBOBOX CHANGED"<<std::endl;
		int temp = ComboBox->getSelectedIndex();
		if(temp == 1)TopLeftCardLayout->last(TopLeftTreePanel);
		else TopLeftCardLayout->first(TopLeftTreePanel);

	}
	else if(e->getSource() == ShowHideItem)
	{
		//std::cout<<"Showing Item\n";
		UInt32 maskval = SelectedNode->getTravMask();
		if(!maskval)	SelectedNode->setTravMask(UInt32(-1));
		else	SelectedNode->setTravMask(0);
		invertShowHideCaption();

	}
	else if(e->getSource() == DeleteItem)
	{
		
		NodePtr parent = SelectedNode->getParent();
		if(parent!=NullFC)
		{
			std::cout<<TheTreeModel->getChildCount(parent)<<" - no of children of root of tree\n";
			if(parent==MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot() && TheTreeModel->getChildCount(parent) == 1)
			{
				std::cout<<"cant delete the only child.Tree becomes empty.\n";
			}
			else
			{
//				parent->subChild(SelectedNode);
//				TheTreeModel->removeNode(SelectedNode);

				//TheTreeModel->getPath(


				
/*				beginEditCP(TheTreeModel);
					TheTreeModel->setRoot(NullFC);
				endEditCP(TheTreeModel);

				beginEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
					TheTree->setModel(TheTreeModel);
				endEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);


				beginEditCP(TheTreeModel);
					TheTreeModel->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
				endEditCP(TheTreeModel);

				beginEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
					TheTree->setModel(TheTreeModel);
				endEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
*/
//				TheTreeModel->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());

				 //  need to update the treemodel

				//TheTreeModel->valueForPathChanged(SelectedNode,NullFC);
				//TheTreeModel->changed(1,0);
				//TheTreeModel->produceTreeStructureChanged(TheTreeModel->getPath(TheTreeModel->getInternalRoot()),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, boost::any(TheTreeModel->getInternalRoot())));
				//TheTreeModel->changed(UInt32(-1),0);
				//TheTree->removeSelectionRow(1);
				
				//TheTreeModel->produceTreeNodesRemoved(parent,
				/*TheTreeModel = NullFC;
				TheTreeModel=SceneGraphTreeModel::create();
				TheTreeModel->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
				beginEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
					TheTree->setModel(TheTreeModel);
				endEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
				*/
							
			}

		}
		else
		{
				std::cout<<"parent is null\n";
		}

	}
	
	else if(e->getSource() == CutItem)
	{
		std::cout<<"Cutting Item\n";
		//SelectedNode->setTravMask(0);
	}
	else if(e->getSource() == CopyItem)
	{
		std::cout<<"Copying Item\n";
		//SelectedNode->setTravMask(0);
	}
	else if(e->getSource() == PasteItem)
	{
		std::cout<<"Pasting Item\n";
		//SelectedNode->setTravMask(0);
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

void ApplicationPlayer::updateDebugSceneChange(void)
{
    updateGotoSceneMenuItems(MainApplication::the()->getProject());

	MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(0)->getForegrounds().push_back(DebuggerUIForeground);
}

ViewportPtr ApplicationPlayer::createDebugViewport(void)
{
    //Camera Transformation Node
	Matrix CameraTransformMatrix;
	CameraTransformMatrix.setTranslate(0.0f,0.0f, 5.0f);
	TransformPtr CameraBeaconTransform = Transform::create();
	beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
		CameraBeaconTransform->setMatrix(CameraTransformMatrix);
	endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
	beginEditCP(CameraBeaconNode, Node::CoreFieldMask);
		CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(CameraBeaconNode, Node::CoreFieldMask);

	//Camera
    PerspectiveCameraPtr DefaultCamera = PerspectiveCamera::create();
    beginEditCP(DefaultCamera);
        DefaultCamera->setBeacon(CameraBeaconNode);
        DefaultCamera->setFov   (deg2rad(60.f));
        DefaultCamera->setNear  (0.1f);
        DefaultCamera->setFar   (10000.f);
    endEditCP(DefaultCamera);

    // Make Main Scene Node and add the Torus
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(CameraBeaconNode);
    endEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Background
	PassiveBackgroundPtr DefaultBackground = PassiveBackground::create();

    ViewportPtr DebugViewport = Viewport::create();
    beginEditCP(DebugViewport);
        DebugViewport->setCamera                  (DefaultCamera);
        DebugViewport->setRoot                    (DefaultRootNode);
        DebugViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
        DebugViewport->setBackground              (DefaultBackground);
        //DebugViewport->getForegrounds().push_back    (UserInterfaceForeground);
    endEditCP(DebugViewport);

    return DebugViewport;
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
	_TheTreeSelectionListener(ApplicationPlayerPtr(this)),
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
	_highlightNodeListener(ApplicationPlayerPtr(this)),
	_ComboBoxListener(ApplicationPlayerPtr(this)),
	_TheTreeSelectionListener(ApplicationPlayerPtr(this)),
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

ApplicationPlayer::highlightNodeListener::highlightNodeListener(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void ApplicationPlayer::highlightNodeListener::update(const UpdateEventPtr e)
{
	if(_ApplicationPlayer->SelectedNode != NullFC)
    {
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// newly added
ApplicationPlayer::TheTreeSelectionListener::TheTreeSelectionListener(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
	_highlight = NullFC;  /// added for highlight node
	_highlightPoints = NullFC;
}

void ApplicationPlayer::TheTreeSelectionListener::setParams(TreePtr TheTree)//,NodePtr  SelectedNode)
{
	_TheTree=TheTree;
}




void ApplicationPlayer::TheTreeSelectionListener::setHighlight(NodePtr selectednode)
{
	_highlight = selectednode;
	highlightChanged();
}
NodePtr ApplicationPlayer::TheTreeSelectionListener::getHighlight()
{
	return _highlight;
}
void ApplicationPlayer::TheTreeSelectionListener::highlightChanged(void)
{
 // to do...
	SimpleMaterialPtr _highlightMaterial;
	
// FDEBUG (("SimpleSceneManager::updateHightlight() called\n"));

	// init as needed
	if(_highlightMaterial == NullFC)
	{
		_highlightMaterial = SimpleMaterial::create();
		
		beginEditCP(_highlightMaterial);
		_highlightMaterial->setDiffuse (Color3f(0,1,0));
		_highlightMaterial->setLit     (false);
		endEditCP(_highlightMaterial);
	}
	if(_ApplicationPlayer->highlightNode == NullFC)
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

		_ApplicationPlayer->highlightNode = Node::create();
		
		beginEditCP(_ApplicationPlayer->highlightNode);
		_ApplicationPlayer->highlightNode->setCore(geo);
		endEditCP(_ApplicationPlayer->highlightNode);
		addRefCP(_ApplicationPlayer->highlightNode);
	}

	
	// attach the hightlight node to the root if the highlight is active
	if(getHighlight() != NullFC)
	{
		if(_ApplicationPlayer->highlightNode->getParent() == NullFC)
		{
		beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->addChild(_ApplicationPlayer->highlightNode);
		endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		}
		
	}
	else
	{
		if(_ApplicationPlayer->highlightNode->getParent() != NullFC)
		{
		beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->subChild(_ApplicationPlayer->highlightNode);
		endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		}
	}
	// update the highlight geometry
	updateHighlight();
}


void ApplicationPlayer::TheTreeSelectionListener::updateHighlight(void)
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


void ApplicationPlayer::setLabelValuesToNull()
{
	    beginEditCP(NodeNameValueLabel, Label::TextFieldMask);
            NodeNameValueLabel->setText("");
        endEditCP(NodeNameValueLabel, Label::TextFieldMask);

        beginEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);
            NodeCoreTypeValueLabel->setText("");
        endEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);

        beginEditCP(NodeMinValueLabel, Label::TextFieldMask);
            NodeMinValueLabel->setText("");
        endEditCP(NodeMinValueLabel, Label::TextFieldMask);

        beginEditCP(NodeMaxValueLabel, Label::TextFieldMask);
            NodeMaxValueLabel->setText("");
        endEditCP(NodeMaxValueLabel, Label::TextFieldMask);

        beginEditCP(NodeCenterValueLabel, Label::TextFieldMask);
            NodeCenterValueLabel->setText("");
        endEditCP(NodeCenterValueLabel, Label::TextFieldMask);

        beginEditCP(NodeTriCountValueLabel, Label::TextFieldMask);
            NodeTriCountValueLabel->setText("");
        endEditCP(NodeTriCountValueLabel, Label::TextFieldMask);

        beginEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);
            NodeTravMaskValueLabel->setText("");
        endEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);
            NodeOcclusionMaskValueLabel->setText("");
        endEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeActiveValueLabel, Label::TextFieldMask);
            NodeActiveValueLabel->setText("");
        endEditCP(NodeActiveValueLabel, Label::TextFieldMask);
}

void ApplicationPlayer::setLabelValues(NodePtr SelectedNode)
{
		const Char8 *NodeName = getName(SelectedNode);

		beginEditCP(NodeNameValueLabel, Label::TextFieldMask);
            if(NodeName == NULL)
            {
                NodeNameValueLabel->setText("Unnamed Node");
            }
            else
            {
                NodeNameValueLabel->setText(NodeName);
            }
        endEditCP(NodeNameValueLabel, Label::TextFieldMask);
	
        beginEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);
            NodeCoreTypeValueLabel->setText(SelectedNode->getCore()->getType().getCName());
        endEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);
		

        DynamicVolume DyVol;
        SelectedNode->getWorldVolume(DyVol);
        Pnt3f Min,Max,Center;
        DyVol.getBounds(Min,Max);
        DyVol.getCenter(Center);

        std::string TempText("");

        TempText = boost::lexical_cast<std::string>(Min.x()) + ", " +boost::lexical_cast<std::string>(Min.x()) + ", " + boost::lexical_cast<std::string>(Min.x());
        beginEditCP(NodeMinValueLabel, Label::TextFieldMask);
            NodeMinValueLabel->setText(TempText);
        endEditCP(NodeMinValueLabel, Label::TextFieldMask);

        TempText = boost::lexical_cast<std::string>(Max.x()) + ", " +boost::lexical_cast<std::string>(Max.x()) + ", " + boost::lexical_cast<std::string>(Max.x());
        beginEditCP(NodeMaxValueLabel, Label::TextFieldMask);
            NodeMaxValueLabel->setText(TempText);
        endEditCP(NodeMaxValueLabel, Label::TextFieldMask);

        TempText = boost::lexical_cast<std::string>(Center.x()) + ", " +boost::lexical_cast<std::string>(Center.x()) + ", " + boost::lexical_cast<std::string>(Center.x());
        beginEditCP(NodeCenterValueLabel, Label::TextFieldMask);
            NodeCenterValueLabel->setText(TempText);
        endEditCP(NodeCenterValueLabel, Label::TextFieldMask);

        GeometryPrimitivesCounter PrimCounter;
        PrimCounter(SelectedNode);
        beginEditCP(NodeTriCountValueLabel, Label::TextFieldMask);
            NodeTriCountValueLabel->setText(boost::lexical_cast<std::string>(PrimCounter.getTriCount()));
        endEditCP(NodeTriCountValueLabel, Label::TextFieldMask);

        beginEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);
            NodeTravMaskValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getTravMask()));
        endEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);
            NodeOcclusionMaskValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getOcclusionMask()));
        endEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeActiveValueLabel, Label::TextFieldMask);
            NodeActiveValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getActive()));
        endEditCP(NodeActiveValueLabel, Label::TextFieldMask);
}


void ApplicationPlayer::TheTreeSelectionListener::selectedNodeChanged(void)
{
	
	setHighlight(_SelectedNode);
	
    //Update Details Panel
    if(_SelectedNode == NullFC)
    {
		
		_ApplicationPlayer->setLabelValuesToNull();
    }
    else
    {
		_ApplicationPlayer->SelectedNode=_SelectedNode;
		_ApplicationPlayer->setLabelValues(_SelectedNode);
    }
}

void ApplicationPlayer::invertShowHideCaption()
{
		std::string caption(ShowHideItem->getText());
		beginEditCP(ShowHideItem);
		if(caption=="Show")
			ShowHideItem->setText("Hide");
		else
			ShowHideItem->setText("Show");
		endEditCP(ShowHideItem);
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
