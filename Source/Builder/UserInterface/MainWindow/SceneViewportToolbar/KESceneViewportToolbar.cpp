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

#include "KESceneViewportToolbar.h"

#include <OpenSG/OSGButton.h>
#include <OpenSG/OSGToggleButton.h>
#include <OpenSG/OSGMenuButton.h>

#include "Application/KEMainApplication.h"

#include "Project/KEProject.h"
#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneViewportToolbarBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneViewportToolbar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneViewportToolbar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SceneViewportToolbar::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SplitScrenMenuButton = dynamic_cast<MenuButton*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.SplitViewButton", TheApplicationBuilder));
    _FullScreenButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.FullScreenButton", TheApplicationBuilder));
    _ConfigurationButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.ConfigureButton", TheApplicationBuilder));
    _FocusButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.FocusCameraButton", TheApplicationBuilder));
    _TranslateButton = dynamic_cast<ToggleButton*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.TranslateButton", TheApplicationBuilder));
    _RotateButton = dynamic_cast<ToggleButton*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.RotateButton", TheApplicationBuilder));
    _ScaleButton = dynamic_cast<ToggleButton*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.ScaleButton", TheApplicationBuilder));
    _StatisticsButton = dynamic_cast<ToggleButton*>(findContainer("KE.WorldBuilder.EditorViewport.Toolbar.StatisticsButton", TheApplicationBuilder));
}

void SceneViewportToolbar::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SplitScrenMenuButton = NULL;
    _FullScreenButton = NULL;
    _ConfigurationButton = NULL;
    _FocusButton = NULL;
    _TranslateButton = NULL;
    _RotateButton = NULL;
    _ScaleButton = NULL;
    _StatisticsButton = NULL;
}

void SceneViewportToolbar::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SplitSelectionConnection = _SplitScrenMenuButton->connectMenuActionPerformed(boost::bind(&SceneViewportToolbar::handleSplitSelection, this, _1));;
    _FullscreenButtonConnection = _FullScreenButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleFullscreenButton, this, _1));
    _ConfigurationButtonConnection = _ConfigurationButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleConfigurationButton, this, _1));
    _FocusButtonConnection = _FocusButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleFocusButton, this, _1));
    _TranslateButtonConnection = _TranslateButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleTranslateButton, this, _1));
    _RotateButtonConnection = _RotateButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleRotateButton, this, _1));
    _ScaleButtonConnection = _ScaleButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleScaleButton, this, _1));
    _StatisticsButtonConnection = _StatisticsButton->connectActionPerformed(boost::bind(&SceneViewportToolbar::handleStatisticsButton, this, _1));

    _FullScreenButton->setEnabled(false);
    _ConfigurationButton->setEnabled(false);
}

void SceneViewportToolbar::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SplitSelectionConnection.disconnect();
    _FullscreenButtonConnection.disconnect();
    _ConfigurationButtonConnection.disconnect();
    _FocusButtonConnection.disconnect();
    _TranslateButtonConnection.disconnect();
    _RotateButtonConnection.disconnect();
    _ScaleButtonConnection.disconnect();
    _StatisticsButtonConnection.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void SceneViewportToolbar::handleSplitSelection(ActionEventDetails* const details)
{
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());
    //Tell the SceneViewport Panel to split
    AppBuilder->getMainWindow()->getSceneViewportPanel()->setSplitMode(_SplitScrenMenuButton->getSelectionIndex());
}

void SceneViewportToolbar::handleFullscreenButton(ActionEventDetails* const details)
{
    //Tell the Builder to Fullscreen
}

void SceneViewportToolbar::handleConfigurationButton(ActionEventDetails* const details)
{
    //Open the Configuration Window
}

void SceneViewportToolbar::handleFocusButton(ActionEventDetails* const details)
{
    //Tell the 
    SceneViewportPanelUnrecPtr ViewportPanel = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportPanel();
    ViewportPanel->focusSelectedNodes();
}

void SceneViewportToolbar::handleTranslateButton(ActionEventDetails* const details)
{
    //Enable/Disable Translation GUI
    setTranslationEditing(_TranslateButton->getSelected());
}

void SceneViewportToolbar::handleRotateButton(ActionEventDetails* const details)
{
    //Enable/Disable Rotation GUI
    setRotationEditing(_RotateButton->getSelected());
}

void SceneViewportToolbar::handleScaleButton(ActionEventDetails* const details)
{
    //Enable/Disable Scale GUI
    setScaleEditing(_ScaleButton->getSelected());
}

void SceneViewportToolbar::handleStatisticsButton(ActionEventDetails* const details)
{
    //Bring up the statistics panels
    SceneViewportPanelUnrecPtr ViewportPanel = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportPanel();
    ViewportPanel->setStatisticsEnabled(_StatisticsButton->getSelected());
}

void SceneViewportToolbar::setTranslationEditing(bool Enabled)
{
    _RotateButton->setSelected(false);
    _ScaleButton->setSelected(false);
    if(_TranslateButton->getSelected() != Enabled)
    {
        _TranslateButton->setSelected(Enabled);
    }
    if(Enabled)
    {

        SceneViewportPanelUnrecPtr ViewportPanel = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportPanel();

        if(ViewportPanel->getManipulatorType() != ManipulatorManager::TRANSLATE)
        {
            ViewportPanel->setManipulatorType(ManipulatorManager::TRANSLATE);
            dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportToolbar()->setTranslationEditing(true);

        }
    }
}

void SceneViewportToolbar::setRotationEditing(bool Enabled)
{
    _TranslateButton->setSelected(false);
    _ScaleButton->setSelected(false);
    if(_RotateButton->getSelected() != Enabled)
    {
        _RotateButton->setSelected(Enabled);
    }
    if(Enabled)
    {
        SceneViewportPanelUnrecPtr ViewportPanel = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportPanel();

        if(ViewportPanel->getManipulatorType() != ManipulatorManager::ROTATE)
        {
            ViewportPanel->setManipulatorType(ManipulatorManager::ROTATE);
            dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportToolbar()->setRotationEditing(true);
        }
    }
}

void SceneViewportToolbar::setScaleEditing(bool Enabled)
{
    _RotateButton->setSelected(false);
    _TranslateButton->setSelected(false);
    if(_ScaleButton->getSelected() != Enabled)
    {
        _ScaleButton->setSelected(Enabled);
    }
    if(Enabled)
    {
        SceneViewportPanelUnrecPtr ViewportPanel = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportPanel();

        if(ViewportPanel->getManipulatorType() != ManipulatorManager::SCALE)
        {
            ViewportPanel->setManipulatorType(ManipulatorManager::SCALE);
            dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportToolbar()->setScaleEditing(true);
        }
    }
}

void SceneViewportToolbar::disableTransformationEditing(void)
{
    _RotateButton->setSelected(false);
    _TranslateButton->setSelected(false);
    _ScaleButton->setSelected(false);
}


/*----------------------- constructors & destructors ----------------------*/

SceneViewportToolbar::SceneViewportToolbar(void) :
    Inherited()
{
}

SceneViewportToolbar::SceneViewportToolbar(const SceneViewportToolbar &source) :
    Inherited(source)
{
}

SceneViewportToolbar::~SceneViewportToolbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneViewportToolbar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneViewportToolbar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneViewportToolbar NI" << std::endl;
}

OSG_END_NAMESPACE
