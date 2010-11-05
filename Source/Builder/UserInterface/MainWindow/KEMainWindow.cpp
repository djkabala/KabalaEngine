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

#include "KEMainWindow.h"
#include <OpenSG/OSGInternalWindow.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGLight.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGCardLayout.h>
#include <OpenSG/OSGParticleSystem.h>
#include <OpenSG/OSGLabel.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGInternalWindow.h>
#include <OpenSG/OSGNameAttachment.h>
#include "Project/Scene/KEScene.h"

#include <OpenSG/OSGFCFileHandler.h>
#include "Application/KEMainApplication.h"
#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"


#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"
#include "Builder/UserInterface/MainWindow/Editors/SceneEditor/KESceneEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/BackgroundEditor/KEBackgroundEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/CameraEditor/KECameraEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/ForegroundEditor/KEForegroundEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/LightEditor/KELightEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/ParticleSystemEditor/KEParticleSystemEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/SceneObjectEditor/KESceneObjectEditor.h"
#include "Builder/UserInterface/MainWindow/Editors/ViewportEditor/KEViewportEditor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMainWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGMainWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MainWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MainWindow::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    createMainWindow();

    _EditorCardLayout = dynamic_cast<CardLayout*>(findContainer("KE.WorldBuilder.Editor.CardLayout", TheApplicationBuilder));
    _EditorSceneNameLabel = dynamic_cast<Label*>(findContainer("KE.WorldBuilder.Editor.SceneNameLabel", TheApplicationBuilder));
    _EditorTypeLabel = dynamic_cast<Label*>(findContainer("KE.WorldBuilder.Editor.Label", TheApplicationBuilder));

    MainMenuRecPtr TheMenu = MainMenu::create();
    MainToolbarRecPtr TheToolbar = MainToolbar::create();
    StatusBarRecPtr TheStatusBar = StatusBar::create();
    HelpPanelRecPtr TheHelpPanel = HelpPanel::create();
    SceneComponentTreeRecPtr TheSceneComponentTree = SceneComponentTree::create();
    SceneNavigationPanelRecPtr TheSceneNavigationPanel = SceneNavigationPanel::create();
    SceneViewportPanelRecPtr TheSceneViewportPanel = SceneViewportPanel::create();
    SceneViewportToolbarRecPtr TheSceneViewportToolbar = SceneViewportToolbar::create();
    
    SceneEditorRecPtr TheSceneEditor = SceneEditor::create();
    BackgroundEditorRecPtr TheBackgroundEditor = BackgroundEditor::create();
    CameraEditorRecPtr TheCameraEditor = CameraEditor::create();
    ForegroundEditorRecPtr TheForegroundEditor = ForegroundEditor::create();
    LightEditorRecPtr TheLightEditor = LightEditor::create();
    ParticleSystemEditorRecPtr TheParticleSystemEditor = ParticleSystemEditor::create();
    SceneObjectEditorRecPtr TheSceneObjectEditor = SceneObjectEditor::create();
    ViewportEditorRecPtr TheViewportEditor = ViewportEditor::create();

    setMenu(TheMenu);
    setToolbar(TheToolbar);
    setStatusBar(TheStatusBar);
    setHelpPanel(TheHelpPanel);
    setSceneComponentTree(TheSceneComponentTree);
    setSceneNavigationPanel(TheSceneNavigationPanel);
    setSceneViewportPanel(TheSceneViewportPanel);
    setSceneViewportToolbar(TheSceneViewportToolbar);
    
    setSceneEditor(TheSceneEditor);
    setBackgroundEditor(TheBackgroundEditor);
    setCameraEditor(TheCameraEditor);
    setForegroundEditor(TheForegroundEditor);
    setLightEditor(TheLightEditor);
    setParticleSystemEditor(TheParticleSystemEditor);
    setSceneObjectEditor(TheSceneObjectEditor);
    setViewportEditor(TheViewportEditor);

    getMenu()->                createInterface(TheApplicationBuilder);
    getToolbar()->             createInterface(TheApplicationBuilder);
    getStatusBar()->           createInterface(TheApplicationBuilder);
    getHelpPanel()->           createInterface(TheApplicationBuilder);
    getSceneComponentTree()->  createInterface(TheApplicationBuilder);
    getSceneNavigationPanel()->createInterface(TheApplicationBuilder);
    getSceneViewportPanel()->  createInterface(TheApplicationBuilder);
    getSceneViewportToolbar()->createInterface(TheApplicationBuilder);
    
    getSceneEditor()->         createInterface(TheApplicationBuilder);
    getBackgroundEditor()->    createInterface(TheApplicationBuilder);
    getCameraEditor()->        createInterface(TheApplicationBuilder);
    getForegroundEditor()->    createInterface(TheApplicationBuilder);
    getLightEditor()->         createInterface(TheApplicationBuilder);
    getParticleSystemEditor()->createInterface(TheApplicationBuilder);
    getSceneObjectEditor()->   createInterface(TheApplicationBuilder);
    getViewportEditor()->      createInterface(TheApplicationBuilder);
}

void MainWindow::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _MainWindow = NULL;

    getMenu()->                destroyInterface(TheApplicationBuilder);
    getToolbar()->             destroyInterface(TheApplicationBuilder);
    getStatusBar()->           destroyInterface(TheApplicationBuilder);
    getHelpPanel()->           destroyInterface(TheApplicationBuilder);
    getSceneComponentTree()->  destroyInterface(TheApplicationBuilder);
    getSceneNavigationPanel()->destroyInterface(TheApplicationBuilder);
    getSceneViewportPanel()->  destroyInterface(TheApplicationBuilder);
    getSceneViewportToolbar()->destroyInterface(TheApplicationBuilder);
    
    getSceneEditor()->         destroyInterface(TheApplicationBuilder);
    getBackgroundEditor()->    destroyInterface(TheApplicationBuilder);
    getCameraEditor()->        destroyInterface(TheApplicationBuilder);
    getForegroundEditor()->    destroyInterface(TheApplicationBuilder);
    getLightEditor()->         destroyInterface(TheApplicationBuilder);
    getParticleSystemEditor()->destroyInterface(TheApplicationBuilder);
    getSceneObjectEditor()->   destroyInterface(TheApplicationBuilder);
    getViewportEditor()->      destroyInterface(TheApplicationBuilder);
}

void MainWindow::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    getMenu()->                attachInterface(TheApplicationBuilder);
    getToolbar()->             attachInterface(TheApplicationBuilder);
    getStatusBar()->           attachInterface(TheApplicationBuilder);
    getHelpPanel()->           attachInterface(TheApplicationBuilder);
    getSceneComponentTree()->  attachInterface(TheApplicationBuilder);
    getSceneNavigationPanel()->attachInterface(TheApplicationBuilder);
    getSceneViewportPanel()->  attachInterface(TheApplicationBuilder);
    getSceneViewportToolbar()->attachInterface(TheApplicationBuilder);
    
    getSceneEditor()->         attachInterface(TheApplicationBuilder);
    getBackgroundEditor()->    attachInterface(TheApplicationBuilder);
    getCameraEditor()->        attachInterface(TheApplicationBuilder);
    getForegroundEditor()->    attachInterface(TheApplicationBuilder);
    getLightEditor()->         attachInterface(TheApplicationBuilder);
    getParticleSystemEditor()->attachInterface(TheApplicationBuilder);
    getSceneObjectEditor()->   attachInterface(TheApplicationBuilder);
    getViewportEditor()->      attachInterface(TheApplicationBuilder);
    
    _SceneSelectionConnection = TheApplicationBuilder->connectSelectionChanged(boost::bind(&MainWindow::handleSelectedSceneChanged, this, _1));
}

void MainWindow::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    getMenu()->                dettachInterface(TheApplicationBuilder);
    getToolbar()->             dettachInterface(TheApplicationBuilder);
    getStatusBar()->           dettachInterface(TheApplicationBuilder);
    getHelpPanel()->           dettachInterface(TheApplicationBuilder);
    getSceneComponentTree()->  dettachInterface(TheApplicationBuilder);
    getSceneNavigationPanel()->dettachInterface(TheApplicationBuilder);
    getSceneViewportPanel()->  dettachInterface(TheApplicationBuilder);
    getSceneViewportToolbar()->dettachInterface(TheApplicationBuilder);
    
    getSceneEditor()->         dettachInterface(TheApplicationBuilder);
    getBackgroundEditor()->    dettachInterface(TheApplicationBuilder);
    getCameraEditor()->        dettachInterface(TheApplicationBuilder);
    getForegroundEditor()->    dettachInterface(TheApplicationBuilder);
    getLightEditor()->         dettachInterface(TheApplicationBuilder);
    getParticleSystemEditor()->dettachInterface(TheApplicationBuilder);
    getSceneObjectEditor()->   dettachInterface(TheApplicationBuilder);
    getViewportEditor()->      dettachInterface(TheApplicationBuilder);
}
    
void MainWindow::hideEditor(void)
{
    _EditorCardLayout->setCard(0);
    _EditorTypeLabel->setText("");
}

void MainWindow::showBackgroundEditor(Background* const TheBackground)
{
    _EditorCardLayout->setCard(getBackgroundEditor()->getCardIndex());
    _EditorTypeLabel->setText(getBackgroundEditor()->getEditorTypeText());

    dynamic_cast<BackgroundEditor*>(getBackgroundEditor())->attachBackground(TheBackground);
}

void MainWindow::showBasicEditor(Scene* const TheScene)
{
    _EditorCardLayout->setCard(getSceneEditor()->getCardIndex());
    _EditorTypeLabel->setText(getSceneEditor()->getEditorTypeText());

    dynamic_cast<SceneEditor*>(getSceneEditor())->attachScene(TheScene);
}

void MainWindow::showForegroundEditor(Foreground* const TheForeground)
{
    _EditorCardLayout->setCard(getForegroundEditor()->getCardIndex());
    _EditorTypeLabel->setText(getForegroundEditor()->getEditorTypeText());

    dynamic_cast<ForegroundEditor*>(getForegroundEditor())->attachForeground(TheForeground);
}

void MainWindow::showLightEditor(Light* const TheLight)
{
    _EditorCardLayout->setCard(getLightEditor()->getCardIndex());
    _EditorTypeLabel->setText(getLightEditor()->getEditorTypeText());

    dynamic_cast<LightEditor*>(getLightEditor())->attachLight(TheLight);
}

void MainWindow::showCameraEditor(Camera* const TheCamera)
{
    _EditorCardLayout->setCard(getCameraEditor()->getCardIndex());
    _EditorTypeLabel->setText(getCameraEditor()->getEditorTypeText());

    dynamic_cast<CameraEditor*>(getCameraEditor())->attachCamera(TheCamera);
}

void MainWindow::showParticleSystemEditor(ParticleSystem* const TheParticleSystem)
{
    _EditorCardLayout->setCard(getParticleSystemEditor()->getCardIndex());
    _EditorTypeLabel->setText(getParticleSystemEditor()->getEditorTypeText());

    dynamic_cast<ParticleSystemEditor*>(getParticleSystemEditor())->attachParticleSystem(TheParticleSystem);
}

void MainWindow::showViewportEditor(Viewport* const TheViewport)
{
    _EditorCardLayout->setCard(getViewportEditor()->getCardIndex());
    _EditorTypeLabel->setText(getViewportEditor()->getEditorTypeText());

    dynamic_cast<ViewportEditor*>(getViewportEditor())->attachViewport(TheViewport);
}

void MainWindow::showWindowEditor(InternalWindow* const TheWindow)
{
}

void MainWindow::showSceneObjectEditor(SceneObject* const TheSceneObject)
{
    _EditorCardLayout->setCard(getSceneObjectEditor()->getCardIndex());
    _EditorTypeLabel->setText(getSceneObjectEditor()->getEditorTypeText());

    dynamic_cast<SceneObjectEditor*>(getSceneObjectEditor())->attachSceneObject(TheSceneObject);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MainWindow::handleSelectedSceneChanged(ListSelectionEventDetails* const details)
{
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());
    const Char8* SceneName(getName(AppBuilder->getSelectedScene()));
    _EditorSceneNameLabel->setText(SceneName ? SceneName : "[Unnamed]");

    //Reset the Tree selection
    getSceneComponentTree()->clearSelection();

    //Set the Start scene
    MainApplication::the()->getProject()->setInitialScene(AppBuilder->getSelectedScene());
}

void MainWindow::createMainWindow(void)
{
    BoostPath WindowDefinitionPath(MainApplication::the()->getSettings().get<BoostPath>("builder.ui.main_window.path"));

    if(!WindowDefinitionPath.is_complete())
    {
        WindowDefinitionPath = MainApplication::the()->getSettings().get<BoostPath>("basic.data.directory") / WindowDefinitionPath;
    }

    loadMainWindow(WindowDefinitionPath);
}

void MainWindow::loadMainWindow(const BoostPath& WindowDefinitionFile)
{
    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(WindowDefinitionFile);

    for(FCFileType::FCPtrStore::iterator Itor(NewContainers.begin()) ; Itor!= NewContainers.end() ; ++Itor)
    {
        if((*Itor)->getType() == InternalWindow::getClassType())
        {
            _MainWindow = dynamic_pointer_cast<InternalWindow>(*Itor);
        }
    }
    if(_MainWindow != NULL)
    {
        SFATAL << "Failed to load Builder MainWindow definition from file: " << WindowDefinitionFile << std::endl;
    }
}

/*----------------------- constructors & destructors ----------------------*/

MainWindow::MainWindow(void) :
    Inherited()
{
}

MainWindow::MainWindow(const MainWindow &source) :
    Inherited(source)
{
}

MainWindow::~MainWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MainWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MainWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MainWindow NI" << std::endl;
}

OSG_END_NAMESPACE
