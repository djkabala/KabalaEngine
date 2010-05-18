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

#include "KEApplicationPlayer.h"
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGDrawable.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGStringUtils.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGSpotLight.h>
//#include <OpenSG/OSGOcclusionCullingTreeBuilder.h>
#include <OpenSG/OSGSimpleGeometryExt.h>
//#include <OpenSG/OSGGeometryUtils.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/OSGWindowUtils.h>

#include "Application/KEMainApplication.h"
#include <OpenSG/OSGFlowLayout.h>
#include <OpenSG/OSGSceneGraphTreeModel.h>

#include "Player/HierarchyPanel/KEHierarchyPanel.h"
#include "Player/HelperPanel/KEHelperPanel.h"
#include "Player/ContentPanel/KEContentPanel.h"

#include "Player/Commands/KEUndoCommandOfPlayer.h"
#include "Player/Commands/KERedoCommandOfPlayer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGApplicationPlayerBase.cpp file.
// To modify it, please change the .fcd file (OSGApplicationPlayer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationPlayer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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
    ProjectRefPtr TheProject(MainApplication::the()->getProject());
    updateWindowTitle();
    MainApplication::the()->getMainWindow()->addKeyListener(&_PlayerKeyListener);
    MainApplication::the()->getMainWindow()->addUpdateListener(&_highlightNodeListener);
}


void ApplicationPlayer::dettachApplication(void)
{
    MainApplication::the()->getMainWindow()->removeKeyListener(&_PlayerKeyListener);
    MainApplication::the()->getMainWindow()->removeUpdateListener(&_highlightNodeListener);
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
    if(MainApplication::the()->getProject() != NULL)
    {
        createDebugInterface();							// Allocate memory to the various pointers in the debug interface when the ApplicationPlayer is started

        createGotoSceneMenuItems(MainApplication::the()->getProject());

        MainApplication::the()->getProject()->start();

        enableDebug(false);
    }
}

void ApplicationPlayer::stop(void)
{
    if(MainApplication::the()->getProject() != NULL)
    {
        MainApplication::the()->getProject()->stop();
    }
}


void ApplicationPlayer::createDebugInterface(void)
{
    //Check if te Debug Interface has already been created
    if(DebuggerGraphics != NULL)
    {
        return;
    }

    // debug interface creation
    DebuggerGraphics = OSG::Graphics2D::create();

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
    _ResetItem->setText("Reset");
    _ResetItem->setAcceleratorKey(KeyEvent::KEY_E);
    _ResetItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _ResetItem->setMnemonicKey(KeyEvent::KEY_E);

    _ForceQuitItem ->setText("Force Quit");
    _ForceQuitItem ->setAcceleratorKey(KeyEvent::KEY_Q);
    _ForceQuitItem ->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _ForceQuitItem ->setMnemonicKey(KeyEvent::KEY_Q);

    _UndoItem->setText("Undo");
    _UndoItem->setAcceleratorKey(KeyEvent::KEY_Z);
    _UndoItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _UndoItem->setMnemonicKey(KeyEvent::KEY_U);

    _RedoItem->setText("Redo");
    _RedoItem->setAcceleratorKey(KeyEvent::KEY_Z);
    _RedoItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL |
                                       KeyEvent::KEY_MODIFIER_SHIFT);
    _RedoItem->setMnemonicKey(KeyEvent::KEY_R);

    _NextItem ->setText("Next");
    _NextItem ->setAcceleratorKey(KeyEvent::KEY_TAB);
    //_NextItem ->setAcceleratorModifiers(!KeyEvent::KEY_MODIFIER_SHIFT);

    _PrevItem->setText("Previous");
    _PrevItem->setAcceleratorKey(KeyEvent::KEY_TAB);
    _PrevItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_SHIFT);

    _FirstItem->setText("First");
    _FirstItem->setAcceleratorKey(KeyEvent::KEY_F);
    _FirstItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _FirstItem->setMnemonicKey(KeyEvent::KEY_F);

    _LastItem->setText("Last");
    _LastItem->setAcceleratorKey(KeyEvent::KEY_L);
    _LastItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _LastItem->setMnemonicKey(KeyEvent::KEY_L);

    _SceneSubItem->setText("Scenes");

    _FlyNavigatorItem->setText("FlyNavigator ");
    _FlyNavigatorItem->setAcceleratorKey(KeyEvent::KEY_N);
    _FlyNavigatorItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _FlyNavigatorItem->setMnemonicKey(KeyEvent::KEY_N);

    _TrackballNavigatorItem->setText("TrackballNavigator ");
    _TrackballNavigatorItem->setAcceleratorKey(KeyEvent::KEY_T);
    _TrackballNavigatorItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _TrackballNavigatorItem->setMnemonicKey(KeyEvent::KEY_T);

    _BasicItem->setText("Basic ");
    _BasicItem->setAcceleratorKey(KeyEvent::KEY_B);
    _BasicItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _BasicItem->setMnemonicKey(KeyEvent::KEY_B);

    _RenderItem->setText("Render ");
    _RenderItem->setAcceleratorKey(KeyEvent::KEY_R);
    _RenderItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _RenderItem->setMnemonicKey(KeyEvent::KEY_R);

    _PhysicsItem->setText("Physics ");
    _PhysicsItem->setMnemonicKey(KeyEvent::KEY_Y);

    _ParticleSystemItem->setText("ParticleSystem ");
    _ParticleSystemItem->setMnemonicKey(KeyEvent::KEY_Z);

    _AnimationItem->setText("Animation ");
    _AnimationItem->setMnemonicKey(KeyEvent::KEY_A);

    _PauseActiveUpdatesItem->setText("Pause Active Updates");
    _PauseActiveUpdatesItem->setAcceleratorKey(KeyEvent::KEY_SPACE);
    //_PauseActiveUpdatesItem->setMnemonicKey(KeyEvent::KEY_SPACE);

    _DrawBoundingVolumesItem->setText("Draw Bounding Volumes");
    _DrawBoundingVolumesItem->setAcceleratorKey(KeyEvent::KEY_V);
    _DrawBoundingVolumesItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL | KeyEvent::KEY_MODIFIER_SHIFT);
    _DrawBoundingVolumesItem->setMnemonicKey(KeyEvent::KEY_V);

    _FrustrumCullingItem->setText("Disable Frustrum Culling ");
    _FrustrumCullingItem->setAcceleratorKey(KeyEvent::KEY_F);
    _FrustrumCullingItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _FrustrumCullingItem->setMnemonicKey(KeyEvent::KEY_F);

    _DrawPhysicsCharacteristicsItem->setText("Draw Physics Characteristics ");
    _DrawPhysicsCharacteristicsItem->setAcceleratorKey(KeyEvent::KEY_P);
    _DrawPhysicsCharacteristicsItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    _DrawPhysicsCharacteristicsItem->setMnemonicKey(KeyEvent::KEY_P);


    /*
       HideItem->setText("Hide Item");
    // HideItem->setAcceleratorKey(KeyEvent::KEY_H);
    // HideItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
    // HideItem->setMnemonicKey(KeyEvent::KEY_P);
    */	
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // creation of the Tree
    _HelperPanel = HelperPanel::create();

    _HelperPanel->setupInfoTabPanel();
    _HelperPanel->setupHistoryList();
    _HelperPanel->setupRest();
    //	MainApplication::the()->getMainWindow()->addKeyListener(&(_HelperPanel->_PlayerKeyListener));


    _HierarchyPanel = HierarchyPanel::create();
    _HierarchyPanel->setApplicationPlayer(ApplicationPlayerRefPtr(this));
    _HierarchyPanel->createDefaultHierarchyPanel();

    _ContentPanel = ContentPanel::create();
    _ContentPanel->setApplicationPlayer(ApplicationPlayerRefPtr(this));

    BorderLayoutConstraintsRefPtr ContentConstraints = OSG::BorderLayoutConstraints::create();

    ContentConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    _ContentPanel->setConstraints(ContentConstraints);
    _ContentPanel->init();

    _OpenFileButton = Button::create();

    _OpenFileButton->setText("Open File");
    //_OpenFileButton->setPreferredSize(Vec2f(100,50));

    _OpenFileButton->addActionListener(&_BasicListener);

    _SaveFileButton = Button::create();

    _SaveFileButton->setText("Save File");
    //_SaveFileButton->setPreferredSize(Vec2f(100,50));

    _SaveFileButton->addActionListener(&_BasicListener);

    /*_CloseFileButton = Button::create();

      _CloseFileButton->setText("Close File");
      _CloseFileButton->setPreferredSize(Vec2f(100,50));

      _CloseFileButton->addActionListener(&_BasicListener);
      */

    _ModeComboBox = ComboBox::create();


    BorderLayoutConstraintsRefPtr ToolbarConstraints = OSG::BorderLayoutConstraints::create();

    ToolbarConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);

    _Toolbar = Panel::create();

    _Toolbar->setConstraints(ToolbarConstraints);
    _Toolbar->setPreferredSize(Vec2f(200,40));

    FlowLayoutRefPtr ToolbarLayout = OSG::FlowLayout::create();
    ToolbarLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
    ToolbarLayout->setMajorAxisAlignment(1.0);

    _Toolbar->pushToChildren(_OpenFileButton);
    _Toolbar->pushToChildren(_SaveFileButton);
    _Toolbar->pushToChildren(_ModeComboBox);
    _Toolbar->setLayout(ToolbarLayout);


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
    _ProjectMenu->setText("Project");
    _ProjectMenu->setMnemonicKey(KeyEvent::KEY_P);

    _EditMenu->setText("Edit");
    _EditMenu->setMnemonicKey(KeyEvent::KEY_D);

    _SceneMenu->setText("Scene");
    _SceneMenu->setMnemonicKey(KeyEvent::KEY_C);

    _NavigatorMenu->setText("Navigator");
    _NavigatorMenu->setMnemonicKey(KeyEvent::KEY_N);

    _StatisticsMenu->setText("Statistics");
    _StatisticsMenu->setMnemonicKey(KeyEvent::KEY_T);

    _ToggleMenu->setText("Toggle");
    _ToggleMenu->setMnemonicKey(KeyEvent::KEY_G);

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

    _UndoActionListener = CommandActionListenerForPlayer(UndoCommandOfPlayer::create(ApplicationPlayerRefPtr(this)), _TheCommandManager);
    _RedoActionListener = CommandActionListenerForPlayer(RedoCommandOfPlayer::create(ApplicationPlayerRefPtr(this)), _TheCommandManager);


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

    //ToolbarLayout2= OSG::BorderLayout::create();

    _HierarchyPanel->setPreferredSize(Vec2f(400,700));

    _ModeComboBoxModel = DefaultMutableComboBoxModel::create();
    _ModeComboBoxModel->addElement(boost::any(std::string("Scene Graph")));
    _ModeComboBoxModel->addElement(boost::any(std::string("Lua Graph")));

    _ModeComboBox->setMinSize(Vec2f(100.0,20));
    _ModeComboBox->setEditable(false);
    _ModeComboBox->setModel(_ModeComboBoxModel);

    //_ModeComboBox->addActionListener(&_BasicListener);
    _ModeComboBoxModel->addSelectionListener(&_ComboBoxListener);

    // Determine where the _ModeComboBox starts
    _ModeComboBox->setSelectedIndex(0);

    setupPopupMenu();

    /*************************************************** _DebugWindowSplitPanel creation **********************************************************************/

    BorderLayoutRefPtr ToolbarAndContentPanelLayout = BorderLayout::create();

    _ToolbarAndContentPanel = OSG::Panel::createEmpty();

    _ToolbarAndContentPanel->setLayout(ToolbarAndContentPanelLayout);
    _ToolbarAndContentPanel->pushToChildren(_Toolbar);
    _ToolbarAndContentPanel->pushToChildren(_ContentPanel);

    _TopHalfSplitPanel = OSG::SplitPanel::create();

    _TopHalfSplitPanel->setMinComponent(_HierarchyPanel);
    _TopHalfSplitPanel->setMaxComponent(_ToolbarAndContentPanel);
    _TopHalfSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
    _TopHalfSplitPanel->setDividerPosition(350.0f); 
    // location from the left/top
    _TopHalfSplitPanel->setDividerSize(5);
    //_TopHalfSplitPanel->setExpandable(true);
    _TopHalfSplitPanel->setMaxDividerPosition(.85);
    _TopHalfSplitPanel->setMinDividerPosition(150.0f);

    _DebugWindowSplitPanelConstraints = OSG::BorderLayoutConstraints::create();

    _DebugWindowSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    _DebugWindowSplitPanel = OSG::SplitPanel::create();

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
    /*************************************************** END _DebugWindowSplitPanel creation **********************************************************************/

    /*************************************************** MainInternalWindow creation*************************************************************/

    BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();

    // Nothing

    // Create The Main InternalWindow


    MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(_DebugWindowSplitPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(NULL);
    MainInternalWindow->setBorders(NULL);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setMenuBar(_MainMenuBar);
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    MainInternalWindow->setFocusedComponent(_HelperPanel->_CodeTextArea);

    /*************************************************** END MainInternalWindow creation*************************************************************/


    // Create the DrawingSurface Object
    DebuggerDrawingSurface = UIDrawingSurface::create();
    DebuggerDrawingSurface->setGraphics(DebuggerGraphics);

    DebuggerDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    DebuggerUIForeground = OSG::UIForeground::create();

    DebuggerUIForeground->setDrawingSurface(DebuggerDrawingSurface);

    //Create the Viewport
    _DebugViewport = createDebugViewport();

    //Create the Debug Camera Animation Group
    createDebugCameraAnim();
}

void ApplicationPlayer::updateGotoSceneMenuItems(ProjectRefPtr TheProject)
{
    SceneRefPtr CurrentlyActiveScene = TheProject->getActiveScene();
    SceneRefPtr GotoItemScene;
    MenuItemRefPtr GotoItem;

    //Disable the Goto Menu Item for the currently active Scene
    for(UInt32 i(0) ; i<_SceneSubItem->getNumItems() ; ++i)
    {
        GotoItem = _SceneSubItem->getItem(i);
        GotoItemScene = TheProject->getSceneByName(GotoItem->getText());
        if(CurrentlyActiveScene == GotoItemScene
           && GotoItem->getEnabled())
        {
            GotoItem->setEnabled(false);
        }
        else if(CurrentlyActiveScene != GotoItemScene
                && !GotoItem->getEnabled())
        {
            GotoItem->setEnabled(true);
        }
    }
}

void ApplicationPlayer::createGotoSceneMenuItems(ProjectRefPtr TheProject)
{
    //Clear all of the previous Items
    _SceneSubItem->removeAllItems();

    //Make a Menu Item for each of the scenes
    const Char8* SceneCharName(NULL);
    std::string SceneName;
    MenuItemRefPtr NewSceneItem;
    for(UInt32 i(0) ; i<TheProject->getMFScenes()->size() ; ++i)
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
        NewSceneItem->setText(SceneName);
        //Attach the Goto Listener
        NewSceneItem->addActionListener(&_GotoSceneItemListener);

        //Add the Scene Menu Item to the SubMenu
        _SceneSubItem->addItem(NewSceneItem);
    }
}

void ApplicationPlayer::attachDebugInterface(void)
{
    if( MainApplication::the()->getProject()->getActiveScene()->getMFViewports()->size() == 0 ||
        MainApplication::the()->getProject()->getActiveScene()->getViewports(0) == NULL)
    {
        SWARNING << "ApplicationPlayer::attachDebugInterface(): No Viewports in current scene.  There should be at least one defined." << std::endl;
    }
    else
    {
        if(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot() == NULL)
        {
            SWARNING << "ApplicationPlayer::attachDebugInterface(): No root for current viewport!" << std::endl;
        }
        else
        {
            if(_HierarchyPanel->getSceneGraphTreeModel()->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
            {
                SWARNING << "Setting Root of SceneGraph tree model" <<
                    std::endl;
                _HierarchyPanel->getSceneGraphTreeModel()->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
            }
        }

    }

    updateHighlightNode();
    DebuggerDrawingSurface->setEventProducer(MainApplication::the()->getMainWindow());

    attachDebugViewport();

    //MainApplication::the()->getMainWindow()->getPort(0)->addForeground(DebuggerUIForeground);
}


void ApplicationPlayer::detachDebugInterface(void)
{

    DebuggerDrawingSurface->setEventProducer(NULL);

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
        _CommandManagerListener.setApplicationPlayer(ApplicationPlayerRefPtr(this));
        updateUndoRedoInterfaces(_TheUndoManager);

        //Update Title
        updateWindowTitle();

        //Turn on Input Blocking
        setSceneInputBlocking(true);

        _WasMouseHidden = !MainApplication::the()->getMainWindow()->getShowCursor();
        if(_WasMouseHidden)
        {
            MainApplication::the()->getMainWindow()->setShowCursor(true);
        }
        _WasMouseAttached = !MainApplication::the()->getMainWindow()->getAttachMouseToCursor();

        if(_WasMouseAttached)
        {
            MainApplication::the()->getMainWindow()->setAttachMouseToCursor(true);
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
            MainApplication::the()->getMainWindow()->setShowCursor(false);
        }
        if(_WasMouseAttached)
        {
            MainApplication::the()->getMainWindow()->setAttachMouseToCursor(false);
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
    MainApplication::the()->getMainWindow()->setTitle(MainWindowTitle);
}

void ApplicationPlayer::actionPerformed(const ActionEventUnrecPtr e)
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
        Int32 SceneIndex(MainApplication::the()->getProject()->getMFScenes()->findIndex(MainApplication::the()->getProject()->getActiveScene()));
        SceneIndex = (SceneIndex+1) % MainApplication::the()->getProject()->getMFScenes()->size();

        MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getScenes(SceneIndex));
    }
    else if(e->getSource() == _PrevItem)
    {
        Int32 SceneIndex(MainApplication::the()->getProject()->getMFScenes()->findIndex(MainApplication::the()->getProject()->getActiveScene()));

        if(SceneIndex == 0)
        {
            SceneIndex = MainApplication::the()->getProject()->getMFScenes()->size();
        }
        --SceneIndex;

        MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getScenes(SceneIndex));
    }
    else if(e->getSource() == _FirstItem)
    {
        MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getScenes(0));
    }

    else if(e->getSource() == _LastItem)
    {
        UInt32 SceneNumber = MainApplication::the()->getProject()->getMFScenes()->size() - 1;
        MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getScenes(SceneNumber));
    }
    else if(e->getSource() == _FlyNavigatorItem )
    {
        //TODO: Implement
    }
    else if(e->getSource() == _TrackballNavigatorItem )
    {
        //TODO: Implement
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
        if(MainApplication::the()->getProject()->getPauseActiveUpdates())
        {
            _PauseActiveUpdatesItem->setText("Unpause Active Updates");
        }
        else
        {
            _PauseActiveUpdatesItem->setText("Pause Active Updates");
        }
    }
    else if(e->getSource() == _DrawBoundingVolumesItem)
    {
        toggleDrawBoundingVolumes();

        //Update the Menu Item
        if(MainApplication::the()->getMainWindow()->getRenderAction()->getVolumeDrawing())
        {
            _DrawBoundingVolumesItem->setText("Hide Bounding Volumes");
        }
        else
        {
            _DrawBoundingVolumesItem->setText("Draw Bounding Volumes");
        }
    }
    else if(e->getSource() == _FrustrumCullingItem)
    {
        toggleFrustumCulling();

        //Update the Menu Item
        if(MainApplication::the()->getMainWindow()->getRenderAction()->getFrustumCulling())
        {
            _FrustrumCullingItem->setText("Disable Frustrum Culling");
        }
        else
        {
            _FrustrumCullingItem->setText("Enable Frustrum Culling");
        }
    }
    else if(e->getSource() == _DrawPhysicsCharacteristicsItem)
    {
        toggleDrawPhysicsCharacteristics();

        //Update the Menu Item
        //Add the Physics Drawable Node to the project
        if(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->findChild(getPhysicsDrawableNode()) < 0)
        {
            _DrawPhysicsCharacteristicsItem->setText("Draw Physics Characteristics");
        }
        else
        {
            _DrawPhysicsCharacteristicsItem->setText("Hide Physics Characteristics");
        }
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


        std::vector<BoostPath> FilesToOpen;
        FilesToOpen = MainApplication::the()->getMainWindow()->openFileDialog("Open File Window",
                                                                                           Filters,
                                                                                           BoostPath(".."),
                                                                                           true);

        for(std::vector<BoostPath>::iterator Itor(FilesToOpen.begin()) ; Itor != FilesToOpen.end(); ++Itor)
        {
            _ContentPanel->addTabWithText(*Itor);
        }
    }
    else if(e->getSource() == _SaveFileButton)
    {
        std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

        BoostPath SavePath = MainApplication::the()->getMainWindow()->saveFileDialog("Save File Window",
                                                                                                  Filters,
                                                                                                  std::string("NewLuaFile.lua"),
                                                                                                  BoostPath(".."),
                                                                                                  true);

        _ContentPanel->saveTextFile(SavePath);
    }
    else
    {
        //do nothing
    }
}



void ApplicationPlayer::keyTyped(const KeyEventUnrecPtr e)
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
            if(SceneNumber < MainApplication::the()->getProject()->getMFScenes()->size())
            {
                MainApplication::the()->getProject()->setActiveScene(MainApplication::the()->getProject()->getScenes(SceneNumber));
            }
        }

        //if(e->getKey() == KeyEvent::KEY_1 && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
        //{
            //MainInternalWindow->setFocusedComponent(_HelperPanel->_CodeTextArea);
            //_HelperPanel->_InfoTabPanel->setSelectedIndex(0);

        //}

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
    for(UInt32 i(0) ; i<MainApplication::the()->getProject()->getMFScenes()->size(); ++i)
    {
        MainApplication::the()->getProject()->getScenes(i)->blockInput(block);
    }
    updateWindowTitle();
}

void ApplicationPlayer::toggleDrawBoundingVolumes(void)
{
    MainApplication::the()->getMainWindow()->getRenderAction()->setVolumeDrawing(!MainApplication::the()->getMainWindow()->getRenderAction()->getVolumeDrawing());
}

void ApplicationPlayer::toggleDrawPhysicsCharacteristics(void)
{
    NodeRefPtr CurrentRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
    NodeRefPtr PhysNode(getPhysicsDrawableNode());

    //Get the Root Node of the Project
    _PhysDrawable->setRoot(CurrentRoot);

    //Add the Physics Drawable Node to the project
    if(CurrentRoot->findChild(PhysNode) < 0)
    {
        CurrentRoot->addChild(PhysNode);
    }
    else
    {
        CurrentRoot->subChild(PhysNode);
    }
}


NodeRefPtr ApplicationPlayer::getPhysicsDrawableNode(void)
{
    if(_PhysDrawable == NULL)
    {
        //Make The Physics Characteristics Core
        _PhysDrawable = PhysicsCharacteristicsDrawable::create();
    }
    if(_PhysDrawableNode == NULL)
    {
        //Make The Physics Characteristics Node
        _PhysDrawableNode = Node::create();
        _PhysDrawableNode->setCore(_PhysDrawable);
    }
    return _PhysDrawableNode;
}

void ApplicationPlayer::gotoScene(SceneRefPtr TheScene)
{
    MainApplication::the()->getProject()->setActiveScene(TheScene);
}

void ApplicationPlayer::toggleFrustumCulling(void)
{
    MainApplication::the()->getMainWindow()->getRenderAction()->setFrustumCulling(!MainApplication::the()->getMainWindow()->getRenderAction()->getFrustumCulling());
}

void ApplicationPlayer::toggleStatForeground(StatisticsForegroundRefPtr TheForeground)
{
    Int32 Index(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getMFForegrounds()->findIndex(TheForeground));
    if(Index != -1)
    {
        //If the Stat foreground is present then switch it off
        MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->removeFromForegrounds(Index);
    }
    else
    {
        //If not present then switch all other stat foregrounds off
        hideAllStatForegrounds();

        //and switch it on
        MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->addForeground(TheForeground);

        MainApplication::the()->getMainWindow()->getRenderAction()->setStatCollector(TheForeground->getCollector());
    }
}

void ApplicationPlayer::hideAllStatForegrounds(void)
{

    //Hide Basic Stat Foreground if present
    MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->removeObjFromForegrounds(_DebugBasicStatForeground);

    //Hide Render Stat Foreground if present
    MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->removeObjFromForegrounds(_DebugRenderStatForeground);

    //Hide Physics Stat Foreground if present
    MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->removeObjFromForegrounds(_DebugPhysicsStatForeground);

    //Hide Particle System Stat Foreground if present
    MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->removeObjFromForegrounds(_DebugParticleSystemStatForeground);

    //Hide Animation Stat Foreground if present
    MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->removeObjFromForegrounds(_DebugAnimationStatForeground);
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

    //Rendering Statistics
    _DebugRenderStatForeground = SimpleStatisticsForeground::create();
    _DebugRenderStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
    _DebugRenderStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
    _DebugRenderStatForeground->setSize(StatFontSize);
    _DebugRenderStatForeground->setColor(StatColor);
    _DebugRenderStatForeground->setShadowColor(StatShadowColor);
    _DebugRenderStatForeground->setBgColor(StatBackgroundColor);
    _DebugRenderStatForeground->setBorderColor(StatBorderColor);
    //Drawing Statistics
    _DebugRenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    _DebugRenderStatForeground->addElement(RenderAction::statTravTime, "Trav FPS: %r.3f");
    _DebugRenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
    _DebugRenderStatForeground->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
    _DebugRenderStatForeground->addElement(RenderAction::statTravTime, "TravTime: %.3f s");

    //Nodes
    _DebugRenderStatForeground->addElement(RenderPartition::statCullTestedNodes, "%d Nodes culltested");
    _DebugRenderStatForeground->addElement(RenderPartition::statCulledNodes, "%d Nodes culled");
    _DebugRenderStatForeground->addElement(RenderAction::statNMatrices, "%d matrix changes");
    _DebugRenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
    //_DebugRenderStatForeground->addElement(RenderAction::statNTransGeometries, "%d transparent Nodes drawn");

    //Materials
    //_DebugRenderStatForeground->addElement(RenderAction::statNMaterials, "%d material changes");
    _DebugRenderStatForeground->addElement(RenderAction::statNShaders, "%d shader changes");
    _DebugRenderStatForeground->addElement(RenderAction::statNShaderParams, "%d shader param changes");

    //Drawn primities
    _DebugRenderStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
    _DebugRenderStatForeground->addElement(Drawable::statNLines, "%d lines drawn");
    _DebugRenderStatForeground->addElement(Drawable::statNPoints, "%d points drawn");
    _DebugRenderStatForeground->addElement(Drawable::statNPrimitives,"%d primitive groups drawn");
    _DebugRenderStatForeground->addElement(Drawable::statNVertices, "%d vertices transformed");
    _DebugRenderStatForeground->addElement(Drawable::statNGeoBytes, "%d bytes of geometry used");

    //Textures
    _DebugRenderStatForeground->addElement(TextureObjChunk::statNTextures, "%d textures used");
    _DebugRenderStatForeground->addElement(TextureObjChunk::statNTexBytes, "%d bytes of texture used");

    //Lights
    _DebugRenderStatForeground->addElement(PointLight::statNPointLights,
                                           "%d point lights");
    _DebugRenderStatForeground->addElement(DirectionalLight::statNDirectionalLights,
                                           "%d directional lights");
    _DebugRenderStatForeground->addElement(SpotLight::statNSpotLights,
                                           "%d spot lights");

    //Occlusion
    //_DebugRenderStatForeground->addElement(OcclusionTestingTreeBuilder::statNOccNodes,
                                           //"%d nodes occlusion tested");
    //_DebugRenderStatForeground->addElement(OcclusionTestingTreeBuilder::statNOccTests,
                                           //"%d occlusion tests");
    //_DebugRenderStatForeground->addElement(OcclusionTestingTreeBuilder::statNOccInvisible,
                                           //"%d nodes found invisible from occ");
    //_DebugRenderStatForeground->addElement(OcclusionTestingTreeBuilder::statNOccSuccessTestPer,
                                           //"%r successful occlusion tests");
    //_DebugRenderStatForeground->addElement(OcclusionTestingTreeBuilder::statNOccTriangles,
                                           //"%d tris culled");

    //Physics Statistics
    _DebugPhysicsStatForeground = SimpleStatisticsForeground::create();
    _DebugPhysicsStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
    _DebugPhysicsStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
    _DebugPhysicsStatForeground->setSize(StatFontSize);
    _DebugPhysicsStatForeground->setColor(StatColor);
    _DebugPhysicsStatForeground->setShadowColor(StatShadowColor);
    _DebugPhysicsStatForeground->setBgColor(StatBackgroundColor);
    _DebugPhysicsStatForeground->setBorderColor(StatBorderColor);
    _DebugPhysicsStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");

    //Particle System Statistics
    _DebugParticleSystemStatForeground = SimpleStatisticsForeground::create();
    _DebugParticleSystemStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
    _DebugParticleSystemStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
    _DebugParticleSystemStatForeground->setSize(StatFontSize);
    _DebugParticleSystemStatForeground->setColor(StatColor);
    _DebugParticleSystemStatForeground->setShadowColor(StatShadowColor);
    _DebugParticleSystemStatForeground->setBgColor(StatBackgroundColor);
    _DebugParticleSystemStatForeground->setBorderColor(StatBorderColor);
    _DebugParticleSystemStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");

    //Animation Statistics
    _DebugAnimationStatForeground = SimpleStatisticsForeground::create();
    _DebugAnimationStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
    _DebugAnimationStatForeground->setVerticalAlign(SimpleStatisticsForeground::Middle);
    _DebugAnimationStatForeground->setSize(StatFontSize);
    _DebugAnimationStatForeground->setColor(StatColor);
    _DebugAnimationStatForeground->setShadowColor(StatShadowColor);
    _DebugAnimationStatForeground->setBgColor(StatBackgroundColor);
    _DebugAnimationStatForeground->setBorderColor(StatBorderColor);
    _DebugAnimationStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
}

void ApplicationPlayer::updateDebugUI(void)
{
    updateGotoSceneMenuItems(MainApplication::the()->getProject());
    //TODO: Update the Scene Node Tree
    if(_HierarchyPanel->getSceneGraphTreeModel()->getRootNode() != MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot())
    {
        _HierarchyPanel->getSceneGraphTreeModel()->setRoot(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
    }

    updateHighlightNode();

}

void ApplicationPlayer::updateDebugSceneChange(void)
{
    //Update the UI for the debug interface
    updateDebugUI();

    _WasMouseHidden = !MainApplication::the()->getMainWindow()->getShowCursor();
    if(_WasMouseHidden)
    {
        MainApplication::the()->getMainWindow()->setShowCursor(true);
    }
    _WasMouseAttached = !MainApplication::the()->getMainWindow()->getAttachMouseToCursor();

    if(_WasMouseAttached)
    {
        MainApplication::the()->getMainWindow()->setAttachMouseToCursor(true);
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
    MainApplication::the()->getMainWindow()->subPortByObj(_DebugViewport);

    //Put the original Camera back on the Scene's Viewport
    MainApplication::the()->getMainWindow()->getPort(0)->setCamera(_SceneViewportCamera);
}

void ApplicationPlayer::updateDebugViewport(void)
{
    //Update The Camera
    _SceneViewportCamera = MainApplication::the()->getMainWindow()->getPort(0)->getCamera();

    _DebugCamera = dynamic_pointer_cast<Camera>(_SceneViewportCamera->shallowCopy());
    _DebugCamera->setBeacon(_DebugCameraBeacon);

    //Put the Camera Beacon to the beacon of the scene's camera
    _DebugSceneNavigator.set(_SceneViewportCamera->getBeacon()->getToWorld());

    //Put the Debug Camera on the Scene's Viewport
    MainApplication::the()->getMainWindow()->getPort(0)->setCamera(_DebugCamera);

    _DebugViewport->setCamera(_DebugCamera);

    //Make sure the Debug Viewport is on top
    MainApplication::the()->getMainWindow()->subPortByObj(_DebugViewport);
    MainApplication::the()->getMainWindow()->addPort(_DebugViewport);
}

void ApplicationPlayer::attachDebugViewport(void)
{
    updateDebugViewport();
}

ViewportRefPtr ApplicationPlayer::createDebugViewport(void)
{
    LineChunkRefPtr WorkspaceGridLineChunk = LineChunk::create();
    WorkspaceGridLineChunk->setWidth(1.0f);
    WorkspaceGridLineChunk->setSmooth(true);

    BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
    TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    ChunkMaterialRefPtr WorkspaceGridMaterial = ChunkMaterial::create();
    WorkspaceGridMaterial->addChunk (TheBlendChunk);
    WorkspaceGridMaterial->addChunk (WorkspaceGridLineChunk);

    MaterialGroupRefPtr GridMatGroup = MaterialGroup::create();
    GridMatGroup->setMaterial(WorkspaceGridMaterial);

    //Create the Workspace Grid
    _WorkspaceGrid = Node::create();

    _WorkspaceGrid->setCore(GridMatGroup);
    //TODO:Readd
    //_WorkspaceGrid->addChild(makeGrid(100.0f, 100.0f, 1.0, Color3f(0.7f,0.7f,0.7f)));

    //Create the Highlight Node
    createHighlightNode();

    //Camera Transformation Node	
    _DebugBeaconTransform = Transform::create();

    _DebugCameraBeacon = OSG::Node::create();
    _DebugCameraBeacon->setCore(_DebugBeaconTransform);

    //Debug Root Node
    NodeRefPtr DefaultRootNode = OSG::Node::create();
    DefaultRootNode->setCore(OSG::Group::create());
    DefaultRootNode->addChild(_DebugCameraBeacon);
    DefaultRootNode->addChild(_HighlightNode);
    DefaultRootNode->addChild(_WorkspaceGrid);

    //Background
    PassiveBackgroundRefPtr DefaultBackground = PassiveBackground::create();

    ViewportRefPtr DebugViewport = Viewport::create();

    DebugViewport->setRoot                    (DefaultRootNode);
    DebugViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
    DebugViewport->setBackground              (DefaultBackground);
    DebugViewport->addForeground              (DebuggerUIForeground);

    _DebugSceneNavigator.setMode(Navigator::TRACKBALL);
    _DebugSceneNavigator.setViewport(DebugViewport);
    _DebugSceneNavigator.setCameraTransformation(_DebugCameraBeacon);

    return DebugViewport;
}

void ApplicationPlayer::moveDebugCamera(const Matrix& Transform)
{
    if(_DebugCamera!=NULL)
    {
        _DebugCameraAnimationGroup->stop();

        //Update The Camera Animation Values
        _DebugCameraTransformationKeyframes->clear();
        _DebugCameraTransformationKeyframes->addKeyframe(_DebugBeaconTransform->getMatrix(),0.0f);
        _DebugCameraTransformationKeyframes->addKeyframe(Transform,1.0f);

        //_DebugCameraFovKeyframes->clear();
        //_DebugCameraFovKeyframes->addKeyframe(dynamic_pointer_cast<PerspectiveCamera>(_SceneViewportCamera)->getFov(),0.0f);
        //_DebugCameraFovKeyframes->addKeyframe(dynamic_pointer_cast<PerspectiveCamera>(_SceneViewportCamera)->getFov()
        //* 1.5f,0.5f);
        //_DebugCameraFovKeyframes->addKeyframe(dynamic_pointer_cast<PerspectiveCamera>(_SceneViewportCamera)->getFov(),1.0f);

        //Attach the Debug Camera Animation
        _DebugCameraTransAnimation->setAnimatedField(_DebugBeaconTransform,
                                                     Transform::MatrixFieldId);

        //_DebugCameraFovAnimation->setAnimatedField(_DebugCamera,
        //PerspectiveCamera::FovFieldId);

        _DebugCameraAnimationGroup->attachUpdateProducer(MainApplication::the()->getMainWindow()->editEventProducer());

        //Start the Animation
        _DebugCameraAnimationGroup->start();

        //Set The Navigator
        _DebugSceneNavigator.set(Transform);
    }
    else
    {
        if(_DebugCamera==NULL)
        {
            SWARNING << "Debug Camera is NULL." << std::endl;
        }
    }
}

void ApplicationPlayer::createDebugCameraAnim(void)
{
    //Transformation Animation
    _DebugCameraTransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();

    KeyframeAnimatorRefPtr DebugCameraTransformationAnimator = KeyframeAnimator::create();
    DebugCameraTransformationAnimator->setKeyframeSequence(_DebugCameraTransformationKeyframes);

    _DebugCameraTransAnimation = FieldAnimation::create();
    _DebugCameraTransAnimation->setAnimator(DebugCameraTransformationAnimator);
    _DebugCameraTransAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    _DebugCameraTransAnimation->setCycling(1);

    //Fov Animation
    //_DebugCameraFovKeyframes = KeyframeNumbersSequenceReal32::create();

    //KeyframeAnimatorRefPtr DebugCameraFovAnimator = KeyframeAnimator::create();
    //DebugCameraFovAnimator->setKeyframeSequence(_DebugCameraFovKeyframes);

    //_DebugCameraFovAnimation = FieldAnimation::create();
    //_DebugCameraFovAnimation->setAnimator(DebugCameraFovAnimator);
    //_DebugCameraFovAnimation->setInterpolationType(LINEAR_INTERPOLATION);
    //_DebugCameraFovAnimation->setCycling(1);

    //Animation Group
    _DebugCameraAnimationGroup = AnimationGroup::create();
    _DebugCameraAnimationGroup->pushToAnimations(_DebugCameraTransAnimation);
    //_DebugCameraAnimationGroup->pushToAnimations(_DebugCameraFovAnimation);
}

void ApplicationPlayer::resetDebugCamera(void)
{
    //Put the Camera Beacon to the beacon of the scene's camera
    _DebugSceneNavigator.set(_SceneViewportCamera->getBeacon()->getToWorld());
}

void ApplicationPlayer::updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager)
{

    _UndoItem->setEnabled(_TheUndoManager->canUndo());
    if(_TheUndoManager->canUndo())
    {
        _UndoItem->setText(TheUndoManager->getUndoPresentationName());
    }
    else
    {
        _UndoItem->setText("Undo");
    }

    _RedoItem->setEnabled(TheUndoManager->canRedo());
    if(_TheUndoManager->canRedo())
    {
        _RedoItem->setText(_TheUndoManager->getRedoPresentationName());
    }
    else
    {
        _RedoItem->setText("Redo");
    }
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
	_PlayerKeyListener(ApplicationPlayerRefPtr(this)),
	_BasicListener(ApplicationPlayerRefPtr(this)),
	_highlightNodeListener(ApplicationPlayerRefPtr(this)),
	_ComboBoxListener(ApplicationPlayerRefPtr(this)),
	_GotoSceneItemListener(ApplicationPlayerRefPtr(this)),
	_ProjectListener(ApplicationPlayerRefPtr(this)),
    _IsDebugActive(false),
    _PhysDrawable(NULL),
    _PhysDrawableNode(NULL),
    _WasMouseHidden(false),
    _WasMouseAttached(false),
	_UndoActionListener(),
	_RedoActionListener(),
	_CommandManagerListener(ApplicationPlayerRefPtr(this))
{
	_TheUndoManager = UndoManager::create();
	_TheCommandManager = CommandManager::create(_TheUndoManager);
	initDebugStatForegrounds();
}

ApplicationPlayer::ApplicationPlayer(const ApplicationPlayer &source) :
    Inherited(source),
	_PlayerKeyListener(ApplicationPlayerRefPtr(this)),
	_BasicListener(ApplicationPlayerRefPtr(this)),
	_highlightNodeListener(ApplicationPlayerRefPtr(this)),
	_ComboBoxListener(ApplicationPlayerRefPtr(this)),
	_GotoSceneItemListener(ApplicationPlayerRefPtr(this)),
	_ProjectListener(ApplicationPlayerRefPtr(this)),
    _IsDebugActive(false),
    _DebugBasicStatForeground(source._DebugBasicStatForeground),
    _DebugRenderStatForeground(source._DebugRenderStatForeground),
    _DebugPhysicsStatForeground(source._DebugPhysicsStatForeground),
    _DebugParticleSystemStatForeground(source._DebugParticleSystemStatForeground),
    _DebugAnimationStatForeground(source._DebugAnimationStatForeground),
    _PhysDrawable(NULL),
    _PhysDrawableNode(NULL),
    _WasMouseHidden(false),
    _WasMouseAttached(false),
	_UndoActionListener(),
	_RedoActionListener(),
	_CommandManagerListener(ApplicationPlayerRefPtr(this))
{
	_TheUndoManager = UndoManager::create();
	_TheCommandManager = CommandManager::create(_TheUndoManager);
}

ApplicationPlayer::~ApplicationPlayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationPlayer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ApplicationPlayer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ApplicationPlayer NI" << std::endl;
}

ApplicationPlayer::CommandManagerListener::CommandManagerListener(ApplicationPlayerRefPtr ApplicationPlayer)
{
    _ApplicationPlayer = ApplicationPlayer;
}

void ApplicationPlayer::CommandManagerListener::stateChanged(const ChangeEventUnrecPtr e)
{
    _ApplicationPlayer->updateUndoRedoInterfaces(_ApplicationPlayer->_TheUndoManager);
}

void ApplicationPlayer::CommandManagerListener::setApplicationPlayer(ApplicationPlayerRefPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
    _ApplicationPlayer->_TheUndoManager->addChangeListener(this);
}


void ApplicationPlayer::PlayerKeyListener::keyTyped(const KeyEventUnrecPtr e)
{
    _ApplicationPlayer->keyTyped(e);
}

void ApplicationPlayer::BasicListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _ApplicationPlayer->actionPerformed(e);
}

void ApplicationPlayer::GotoSceneItemListener::actionPerformed(const ActionEventUnrecPtr e)
{
    SceneRefPtr TheScene(MainApplication::the()->getProject()->getSceneByName(dynamic_cast<MenuItem*>(e->getSource())->getText()));

    if(TheScene != NULL)
    {
        _ApplicationPlayer->gotoScene(TheScene);
    }
}

void ApplicationPlayer::ProjectListener::eventProduced(const EventUnrecPtr e, UInt32 EventProducedId)
{
    switch(EventProducedId)
    {
        case Project::SceneChangedMethodId:
            _ApplicationPlayer->updateDebugSceneChange();
            break;
    }
}

ApplicationPlayer::highlightNodeListener::highlightNodeListener(ApplicationPlayerRefPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
}

void ApplicationPlayer::highlightNodeListener::update(const UpdateEventUnrecPtr e)
{
    _ApplicationPlayer->updateHighlightNode();
}

void ApplicationPlayer::updateWireframeNode(void)
{
    //Clone the sub-tree rooted at the selected node
    if(_SelectedNode != NULL)
    {
        NodeRefPtr ClonedTree(cloneTree(_SelectedNode));
        if(_WireframeNode->getNChildren() > 0)
        {
            _WireframeNode->replaceChild(0, ClonedTree);
        }
        else
        {
            _WireframeNode->addChild(ClonedTree);
        }
    }

    //Update the transformation for the wireframe node
    if(_SelectedNode != NULL &&
       _SelectedNode->getParent() != NULL)
    {
        _WireframeTransform->setMatrix(_SelectedNode->getParent()->getToWorld());
    }
}

void ApplicationPlayer::updateHighlightNode(void)
{
    getDebugSceneNavigator().updateCameraTransformation();

    // attach the hightlight node to the root if the highlight is active
    if(_SelectedNode == NULL)
    {
        _HighlightNode->setTravMask(0);
    }
    else
    {
        _HighlightNode->setTravMask(UInt32(-1));
    }

    if(_SelectedNode != NULL)		// selected node is the node that is being selected.
    {													// highlight node is the pointer to the bounding box for the selected node
        std::string coreName= _SelectedNode->getCore()->getTypeName();

        // calc the world bbox of the highlight object
        BoxVolume      vol;
        _SelectedNode->getWorldVolume(vol);

        Pnt3f min,max;
        vol.getBounds(min, max);

        //Get The Local Coordinate System
        Matrix NodeMatrix = _SelectedNode->getToWorld();
        Pnt3f NodeOrigin(NodeMatrix * Pnt3f(0.0f,0.0f,0.0f));
        Vec3f NodeXDir(NodeMatrix * Vec3f(1.0f,0.0f,0.0f)),
              NodeYDir(NodeMatrix * Vec3f(0.0f,1.0f,0.0f)),
              NodeZDir(NodeMatrix * Vec3f(0.0f,0.0f,1.0f));

        //If the Volume is Zero, use a volume of size 1.0
        if(min == max)
        {
            min = NodeOrigin - Vec3f(0.5f,0.5f,0.5f);
            max = NodeOrigin + Vec3f(0.5f,0.5f,0.5f);
        }

        //Get the side lengths of the volume
        Vec3f  Sides(max - min);

        if(dynamic_cast<Geometry*>(_HighlightNode->getCore())->getPositions() == NULL)
        {
            GeoPnt3fPropertyUnrecPtr Positions = GeoPnt3fProperty::create();
            dynamic_cast<Geometry*>(_HighlightNode->getCore())->setPositions(Positions);
        }

        GeoPnt3fPropertyUnrecPtr temphighlightPoints =
            dynamic_cast<GeoPnt3fProperty*>(dynamic_cast<Geometry*>(_HighlightNode->getCore())->getPositions());

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

        //Update the transformation for the wireframe node
        if(_SelectedNode != NULL &&
           _SelectedNode->getParent() != NULL)
        {
            _WireframeTransform->setMatrix(_SelectedNode->getParent()->getToWorld());
        }
    }
}

void ApplicationPlayer::createHighlightNode(void)
{
    //Create the Material for the Highlight
    LineChunkRefPtr HighlightMatLineChunk = LineChunk::create();
    HighlightMatLineChunk->setWidth(2.0f);
    HighlightMatLineChunk->setSmooth(true);

    BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
    TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    ChunkMaterialRefPtr HighlightMaterial = ChunkMaterial::create();
    HighlightMaterial->addChunk (TheBlendChunk);
    HighlightMaterial->addChunk (HighlightMatLineChunk);

    //Create the Geometry for the highlight
    GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
    //Volume bound box
    type->push_back(GL_LINE_STRIP);
    type->push_back(GL_LINES);

    //Local Coordinage axis
    type->push_back(GL_LINES);

    GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
    //Volume bound box
    lens->push_back(10);
    lens->push_back(6);

    //Local Coordinage axis
    lens->push_back(6);

    GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();

    //Volume bound box
    index->push_back(0);
    index->push_back(1);
    index->push_back(3);
    index->push_back(2);
    index->push_back(0);
    index->push_back(4);
    index->push_back(5);
    index->push_back(7);
    index->push_back(6);
    index->push_back(4);

    index->push_back(1);
    index->push_back(5);
    index->push_back(2);
    index->push_back(6);
    index->push_back(3);
    index->push_back(7);

    //Local Coordinage axis
    index->push_back(8);
    index->push_back(9);
    index->push_back(10);
    index->push_back(11);
    index->push_back(12);
    index->push_back(13);

    GeoPnt3fPropertyRefPtr highlightPoints = GeoPnt3fProperty::create();
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

    //Colors
    Color4f BoundBoxColor(0.0f,1.0f,1.0,1.0f);
    Color4f XAxisColor   (1.0f,0.0f,0.0,1.0f);
    Color4f YAxisColor   (0.0f,1.0f,0.0,1.0f);
    Color4f ZAxisColor   (0.0f,0.0f,1.0,1.0f);

    GeoVec4fPropertyRefPtr highlightColors = GeoVec4fProperty::create();
    //Volume bound box
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);

    //Local Coordinage axis
    highlightColors->push_back(XAxisColor);
    highlightColors->push_back(XAxisColor);
    highlightColors->push_back(YAxisColor);
    highlightColors->push_back(YAxisColor);
    highlightColors->push_back(ZAxisColor);
    highlightColors->push_back(ZAxisColor);

    GeometryRefPtr geo=Geometry::create();
    geo->setTypes     (type);
    geo->setLengths   (lens);
    geo->setIndices   (index);
    geo->setPositions (highlightPoints);
    geo->setColors    (highlightColors);
    geo->setMaterial  (HighlightMaterial);

    //Create the Material for the Mesh Highlight
    LineChunkRefPtr WireframeMatLineChunk = LineChunk::create();
    WireframeMatLineChunk->setWidth(1.0f);
    WireframeMatLineChunk->setSmooth(true);

    PolygonChunkRefPtr WireframeMatPolygonChunk = PolygonChunk::create();
    WireframeMatPolygonChunk->setCullFace(GL_NONE);
    WireframeMatPolygonChunk->setFrontMode(GL_LINE);
    WireframeMatPolygonChunk->setBackMode(GL_LINE);
    WireframeMatPolygonChunk->setOffsetFactor(1.0f);
    WireframeMatPolygonChunk->setOffsetBias(0.01f);
    WireframeMatPolygonChunk->setOffsetFill(true);

    Color4f WireframeColor(1.0f,0.0f,1.0f,1.0f);
    MaterialChunkRefPtr WireframeMatMaterialChunk = MaterialChunk::create();
    WireframeMatMaterialChunk->setAmbient (Color4f(0.0f,0.0f,0.0f,1.0f));
    WireframeMatMaterialChunk->setDiffuse (Color4f(0.0f,0.0f,0.0f,1.0f));
    WireframeMatMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
    WireframeMatMaterialChunk->setEmission(WireframeColor);
    WireframeMatMaterialChunk->setLit(true);

    ChunkMaterialRefPtr WireframeMaterial = ChunkMaterial::create();
    WireframeMaterial->addChunk (TheBlendChunk);
    WireframeMaterial->addChunk (WireframeMatPolygonChunk);
    WireframeMaterial->addChunk (WireframeMatMaterialChunk);
    WireframeMaterial->addChunk (WireframeMatLineChunk);

    //MaterialGroup
    MaterialGroupRefPtr WireframeMaterialGroup = MaterialGroup::create(); 
    WireframeMaterialGroup->setMaterial(WireframeMaterial);

    //Mesh Highlight Node
    _WireframeNode = Node::create();
    setName(_WireframeNode,"DEBUG_MODE_MESH_HIGHLIGHT_NODE");
    _WireframeNode->setCore(WireframeMaterialGroup);

    //Mesh Highlight Transformation Node
    _WireframeTransform = Transform::create();

    NodeRefPtr WireframeTransfromationNode = Node::create();
    WireframeTransfromationNode->setCore(_WireframeTransform);
    WireframeTransfromationNode->addChild(_WireframeNode);

    //Highlight Node
    _HighlightNode = Node::create();
    setName(_HighlightNode,"DEBUG_MODE_HIGHLIGHT_NODE");

    _HighlightNode->setCore(geo);
    _HighlightNode->addChild(WireframeTransfromationNode);
}

void ApplicationPlayer::selectNode(const Pnt2f& ViewportPoint)
{
    Line ViewRay;
    ViewportRefPtr TheViewport(MainApplication::the()->getProject()->getActiveScene()->getViewports(0));
    TheViewport->getCamera()->calcViewRay( ViewRay, ViewportPoint.x(), ViewportPoint.y(), *TheViewport);

    IntersectAction *CastRayAction = IntersectAction::create();

    CastRayAction->setLine( ViewRay );
    CastRayAction->apply( TheViewport->getRoot() );             

    //Get the Tree Model
    SceneGraphTreeModelRefPtr SceneModel(_HierarchyPanel->getSceneGraphTreeModel());
    TreeRefPtr SceneTree(_HierarchyPanel->getSceneGraphTree());
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

void ApplicationPlayer::ComboBoxListener::selectionChanged(const ComboBoxSelectionEventUnrecPtr e)
{
    _ApplicationPlayer->setDebugView(e->getCurrentIndex());
}

ApplicationPlayer::ComboBoxListener::ComboBoxListener(ApplicationPlayerRefPtr TheApplicationPlayer)
{
    _ApplicationPlayer = TheApplicationPlayer;
}

OSG_END_NAMESPACE
