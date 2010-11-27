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

#include "KESceneViewportPanel.h"
#include <OpenSG/OSGCardLayout.h>
#include <OpenSG/OSGGLViewport.h>
#include "KESceneEditingViewport.h"

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
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneViewportPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneViewportPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneViewportPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SceneViewportPanel::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SplitModeSelectionCard = dynamic_cast<CardLayout*>(findContainer("KE.WorldBuilder.EditorViewport.Viewports.CardLayout", TheApplicationBuilder));

    _NoSplitViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.NoSplitPanel.MainGLViewport", TheApplicationBuilder));
    _OneByTwoLeftViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.OneByTwoSplitPanel.LeftGLViewport", TheApplicationBuilder));
    _OneByTwoRightViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.OneByTwoSplitPanel.RightGLViewport", TheApplicationBuilder));
    _TwoByOneTopViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.TwoByOneSplitPanel.TopGLViewport", TheApplicationBuilder));
    _TwoByOneBottomViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.TwoByOneSplitPanel.BottomGLViewport", TheApplicationBuilder));
    _TwoByTwoTopLeftViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.TwoByTwoSplitPanel.TopLeftGLViewport", TheApplicationBuilder));
    _TwoByTwoTopRightViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.TwoByTwoSplitPanel.TopRightGLViewport", TheApplicationBuilder));
    _TwoByTwoBottomLeftViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.TwoByTwoSplitPanel.BottomLeftGLViewport", TheApplicationBuilder));
    _TwoByTwoBottomRightViewport = dynamic_cast<SceneEditingViewport*>(findContainer("KE.WorldBuilder.EditorViewport.Viewport.TwoByTwoSplitPanel.BottomRightGLViewport", TheApplicationBuilder));
}

void SceneViewportPanel::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SplitModeSelectionCard = NULL;
    
    _NoSplitViewport = NULL;
    _OneByTwoLeftViewport = NULL;
    _OneByTwoRightViewport = NULL;
    _TwoByOneTopViewport = NULL;
    _TwoByOneBottomViewport = NULL;
    _TwoByTwoTopLeftViewport = NULL;
    _TwoByTwoTopRightViewport = NULL;
    _TwoByTwoBottomLeftViewport = NULL;
    _TwoByTwoBottomRightViewport = NULL;
}

void SceneViewportPanel::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    setSplitMode(SPLIT_NONE);

    _SceneSelectionConnection = TheApplicationBuilder->connectSelectionChanged(boost::bind(&SceneViewportPanel::handleSelectedSceneChanged, this, _1));
}
void SceneViewportPanel::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _SceneSelectionConnection.disconnect();
}

void SceneViewportPanel::setSplitMode(UInt32 Mode)
{
    dettachSplitModeViewports();

    _SplitMode = Mode;
    
    attachSplitModeViewports();

    _SplitModeSelectionCard->setCard(_SplitMode);
}

void SceneViewportPanel::focusNode(Node* TheNode)
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		_NoSplitViewport->focusNode(TheNode);
        break;
    case SPLIT_ONE_BY_TWO:
		_OneByTwoLeftViewport->focusNode(TheNode);
		_OneByTwoRightViewport->focusNode(TheNode);
        break;
    case SPLIT_TWO_BY_ONE:
		_TwoByOneTopViewport->focusNode(TheNode);
		_TwoByOneBottomViewport->focusNode(TheNode);
        break;
    case SPLIT_TWO_BY_TWO:
		_TwoByTwoTopLeftViewport->focusNode(TheNode);
		_TwoByTwoTopRightViewport->focusNode(TheNode);
		_TwoByTwoBottomLeftViewport->focusNode(TheNode);
		_TwoByTwoBottomRightViewport->focusNode(TheNode);
        break;
    }
}
    
void SceneViewportPanel::focusSelectedNodes(void)
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		_NoSplitViewport->focusSelectedNodes();
        break;
    case SPLIT_ONE_BY_TWO:
		_OneByTwoLeftViewport->focusSelectedNodes();
		_OneByTwoRightViewport->focusSelectedNodes();
        break;
    case SPLIT_TWO_BY_ONE:
		_TwoByOneTopViewport->focusSelectedNodes();
		_TwoByOneBottomViewport->focusSelectedNodes();
        break;
    case SPLIT_TWO_BY_TWO:
		_TwoByTwoTopLeftViewport->focusSelectedNodes();
		_TwoByTwoTopRightViewport->focusSelectedNodes();
		_TwoByTwoBottomLeftViewport->focusSelectedNodes();
		_TwoByTwoBottomRightViewport->focusSelectedNodes();
        break;
    }
}

void SceneViewportPanel::setStatisticsEnabled(bool enable)
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		_NoSplitViewport->setStatisticsEnabled(enable);
        break;
    case SPLIT_ONE_BY_TWO:
		_OneByTwoLeftViewport->setStatisticsEnabled(enable);
		_OneByTwoRightViewport->setStatisticsEnabled(enable);
        break;
    case SPLIT_TWO_BY_ONE:
		_TwoByOneTopViewport->setStatisticsEnabled(enable);
		_TwoByOneBottomViewport->setStatisticsEnabled(enable);
        break;
    case SPLIT_TWO_BY_TWO:
		_TwoByTwoTopLeftViewport->setStatisticsEnabled(enable);
		_TwoByTwoTopRightViewport->setStatisticsEnabled(enable);
		_TwoByTwoBottomLeftViewport->setStatisticsEnabled(enable);
		_TwoByTwoBottomRightViewport->setStatisticsEnabled(enable);
        break;
    }
}

bool SceneViewportPanel::getStatisticsEnabled(void) const
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		return _NoSplitViewport->getStatisticsEnabled();
        break;
    case SPLIT_ONE_BY_TWO:
		return _OneByTwoLeftViewport->getStatisticsEnabled();
        break;
    case SPLIT_TWO_BY_ONE:
		return _TwoByOneTopViewport->getStatisticsEnabled();
        break;
    case SPLIT_TWO_BY_TWO:
		return _TwoByTwoTopLeftViewport->getStatisticsEnabled();
        break;
    }
}

void SceneViewportPanel::selectNode(Node* SelectNode)
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		_NoSplitViewport->clearSelectedNodes();
        if(SelectNode != NULL)
        {
		    _NoSplitViewport->pushToSelectedNodes(SelectNode);
        }
        break;
    case SPLIT_ONE_BY_TWO:
		_OneByTwoLeftViewport->clearSelectedNodes();
		_OneByTwoRightViewport->clearSelectedNodes();
        if(SelectNode != NULL)
        {
		    _OneByTwoLeftViewport->pushToSelectedNodes(SelectNode);
		    _OneByTwoRightViewport->pushToSelectedNodes(SelectNode);
        }
        break;
    case SPLIT_TWO_BY_ONE:
		_TwoByOneTopViewport->clearSelectedNodes();
		_TwoByOneBottomViewport->clearSelectedNodes();
        if(SelectNode != NULL)
        {
		    _TwoByOneTopViewport->pushToSelectedNodes(SelectNode);
		    _TwoByOneBottomViewport->pushToSelectedNodes(SelectNode);
        }
        break;
    case SPLIT_TWO_BY_TWO:
		_TwoByTwoTopLeftViewport->clearSelectedNodes();
		_TwoByTwoTopRightViewport->clearSelectedNodes();
		_TwoByTwoBottomLeftViewport->clearSelectedNodes();
		_TwoByTwoBottomRightViewport->clearSelectedNodes();
        if(SelectNode != NULL)
        {
		    _TwoByTwoTopLeftViewport->pushToSelectedNodes(SelectNode);
		    _TwoByTwoTopRightViewport->pushToSelectedNodes(SelectNode);
		    _TwoByTwoBottomLeftViewport->pushToSelectedNodes(SelectNode);
		    _TwoByTwoBottomRightViewport->pushToSelectedNodes(SelectNode);
        }
        break;
    }
}

void SceneViewportPanel::setManipulatorType(ManipulatorManager::ManipulatorType Type)
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
        _NoSplitViewport->setManipulatorType(Type);
        break;
    case SPLIT_ONE_BY_TWO:
        _OneByTwoLeftViewport->setManipulatorType(Type);
        _OneByTwoRightViewport->setManipulatorType(Type);
        break;
    case SPLIT_TWO_BY_ONE:
        _TwoByOneTopViewport->setManipulatorType(Type);
        _TwoByOneBottomViewport->setManipulatorType(Type);
        break;
    case SPLIT_TWO_BY_TWO:
        _TwoByTwoTopLeftViewport->setManipulatorType(Type);
        _TwoByTwoTopRightViewport->setManipulatorType(Type);
        _TwoByTwoBottomLeftViewport->setManipulatorType(Type);
        _TwoByTwoBottomRightViewport->setManipulatorType(Type);
        break;
    }
}

ManipulatorManager::ManipulatorType SceneViewportPanel::getManipulatorType(void) const
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
        return _NoSplitViewport->getManipulatorType();
        break;
    case SPLIT_ONE_BY_TWO:
        return _OneByTwoLeftViewport->getManipulatorType();
        break;
    case SPLIT_TWO_BY_ONE:
        return _TwoByOneTopViewport->getManipulatorType();
        break;
    case SPLIT_TWO_BY_TWO:
        return _TwoByTwoTopLeftViewport->getManipulatorType();
        break;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SceneViewportPanel::handleSelectedSceneChanged(ListSelectionEventDetails* const details)
{
    attachSplitModeViewports();
}

void SceneViewportPanel::attachSplitModeViewports(void)
{
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		_NoSplitViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_NoSplitViewport->showAll();
        break;
    case SPLIT_ONE_BY_TWO:
		_OneByTwoLeftViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_OneByTwoLeftViewport->showAll();
		_OneByTwoRightViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_OneByTwoRightViewport->showAll();
        break;
    case SPLIT_TWO_BY_ONE:
		_TwoByOneTopViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_TwoByOneTopViewport->showAll();
		_TwoByOneBottomViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_TwoByOneBottomViewport->showAll();
        break;
    case SPLIT_TWO_BY_TWO:
		_TwoByTwoTopLeftViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_TwoByTwoTopLeftViewport->showAll();
		_TwoByTwoTopRightViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_TwoByTwoTopRightViewport->showAll();
		_TwoByTwoBottomLeftViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_TwoByTwoBottomLeftViewport->showAll();
		_TwoByTwoBottomRightViewport->setEditingScene(AppBuilder->getSelectedScene());
	    //_TwoByTwoBottomRightViewport->showAll();
        break;
    }
}

void SceneViewportPanel::dettachSplitModeViewports(void)
{
    switch(_SplitMode)
    {
    case SPLIT_NONE:
		_NoSplitViewport->setEditingScene(NULL);
        break;
    case SPLIT_ONE_BY_TWO:
		_OneByTwoLeftViewport->setEditingScene(NULL);
		_OneByTwoRightViewport->setEditingScene(NULL);
        break;
    case SPLIT_TWO_BY_ONE:
		_TwoByOneTopViewport->setEditingScene(NULL);
		_TwoByOneBottomViewport->setEditingScene(NULL);
        break;
    case SPLIT_TWO_BY_TWO:
		_TwoByTwoTopLeftViewport->setEditingScene(NULL);
		_TwoByTwoTopRightViewport->setEditingScene(NULL);
		_TwoByTwoBottomLeftViewport->setEditingScene(NULL);
		_TwoByTwoBottomRightViewport->setEditingScene(NULL);
        break;
    }
}

/*----------------------- constructors & destructors ----------------------*/

SceneViewportPanel::SceneViewportPanel(void) :
    Inherited()
{
}

SceneViewportPanel::SceneViewportPanel(const SceneViewportPanel &source) :
    Inherited(source)
{
}

SceneViewportPanel::~SceneViewportPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneViewportPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneViewportPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneViewportPanel NI" << std::endl;
}

OSG_END_NAMESPACE
