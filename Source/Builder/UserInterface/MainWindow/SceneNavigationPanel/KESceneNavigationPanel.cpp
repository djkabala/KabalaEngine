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

#include "KESceneNavigationPanel.h"

#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGFocusEventDetails.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGButton.h>
#include <OpenSG/OSGPanel.h>
#include <OpenSG/OSGLabel.h>
#include <OpenSG/OSGTextureLayer.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGUIViewport.h>

#include "Builder/KEApplicationBuilder.h"
#include "Project/KEProject.h"
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


#include "Project/Scene/KESceneDrawUtils.h"

#include "Builder/UserInterface/Commands/KENewSceneCommand.h"
#include "Builder/UserInterface/Commands/KERemoveSceneCommand.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneNavigationPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneNavigationPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneNavigationPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SceneNavigationPanel::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _CreateSceneButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.SceneViewLabelPanel.NewSceneButton", TheApplicationBuilder));
    _DefaultSceneThumbPanel = dynamic_cast<Panel*>(findContainer("KE.WorldBuilder.SceneView.MiniPreviewPanel", TheApplicationBuilder));
    _SceneNavigationPanel = dynamic_cast<Panel*>(findContainer("KE.WorldBuilder.SceneView.TableNavigationPanel", TheApplicationBuilder));

    _SceneNavigationViewport = dynamic_cast<UIViewport*>(findContainer("KE.WorldBuilder.SceneViewTableViewport", TheApplicationBuilder));
}

void SceneNavigationPanel::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _CreateSceneButton = NULL;
    _DefaultSceneThumbPanel = NULL;
    _SceneNavigationPanel = NULL;
}

void SceneNavigationPanel::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    createSceneThumbnails();

    _TheCommandManager = TheApplicationBuilder->getCommandManager();

    attachSceneThumbs();

    _CreateSceneConnection = _CreateSceneButton->connectActionPerformed(boost::bind(&SceneNavigationPanel::handleCreateSceneButton, this, _1));

    _ScenesChangedConnection = MainApplication::the()->getProject()->connectScenesChanged(boost::bind(&SceneNavigationPanel::handleScenesChanged, this, _1));

    _SceneSelectionConnection = TheApplicationBuilder->connectSelectionChanged(boost::bind(&SceneNavigationPanel::handleSelectedSceneChanged, this, _1));

    handleSceneDeselected(NULL);
    handleSceneSelected(TheApplicationBuilder->getSelectedScene());
    
    updatePreferredSize();
}

void SceneNavigationPanel::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _CreateSceneConnection.disconnect();
    _ScenesChangedConnection.disconnect();
    _SceneSelectionConnection.disconnect();

    dettachSceneThumbs();
    
    _TheCommandManager = CommandManagerPtr();
}

void SceneNavigationPanel::selectScene(Scene* const TheScene)
{
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->selectScene(TheScene);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void SceneNavigationPanel::attachSceneThumbs(void)
{
    for(SceneToThumbMapConstItor Itor(_SceneToThumbMap.begin()) ; 
        Itor != _SceneToThumbMap.end();
        ++Itor)
    {
        //Connect Rollover
        _SceneThumbConnections.push_back(Itor->second._Panel->connectFocusGained(boost::bind(&SceneNavigationPanel::handleSceneThumbFocused, this, _1, Itor->first)));

        //Connect Remove Button
        _SceneThumbConnections.push_back(Itor->second._RemoveButton->connectActionPerformed(boost::bind(&SceneNavigationPanel::handleSceneRemoved, this, _1, Itor->first)));
        
        //Connect Focus
        _SceneThumbConnections.push_back(Itor->second._Panel->connectMouseEntered(boost::bind(&SceneNavigationPanel::handleSceneThumbEntered, this, _1, Itor->first)));
        _SceneThumbConnections.push_back(Itor->second._Panel->connectMouseExited(boost::bind(&SceneNavigationPanel::handleSceneThumbExited, this, _1, Itor->first)));
    }
}

void SceneNavigationPanel::dettachSceneThumbs(void)
{
    for(UInt32 i(0) ; i<_SceneThumbConnections.size() ; ++i)
    {
        _SceneThumbConnections[i].disconnect();
    }
    _SceneThumbConnections.clear();
}

PanelTransitPtr SceneNavigationPanel::createSceneThumbnail(Scene* const TheScene)
{
    PanelUnrecPtr ThumbPanel = dynamic_pointer_cast<Panel>(deepClone(_DefaultSceneThumbPanel));
    ThumbPanel->setBorders(NULL);
    commitChanges();
    return PanelTransitPtr(ThumbPanel);
}

void SceneNavigationPanel::createSceneThumbnails(void)
{
    clearSceneThumbnails();

    //For all of the scenes
    ProjectRecPtr TheProject(MainApplication::the()->getProject());
    for(UInt32 i(0) ; i<TheProject->getMFScenes()->size() ; ++i)
    {
        //Create a Thumbnail panel for this scene
        PanelRecPtr ThumbPanel = createSceneThumbnail(TheProject->getScenes(i));

        ThumbComp ThumbComponents;
        ThumbComponents._Panel = ThumbPanel;

        //Name Label
        ThumbComponents._NameLabel = dynamic_cast<Label*>(ThumbPanel->getNamedDecendents("KE.WorldBuilder.SceneView.MiniPreviewPanel.Label").front());
        
        //Remove Button
        ThumbComponents._RemoveButton = dynamic_cast<Button*>(ThumbPanel->getNamedDecendents("KE.WorldBuilder.SceneView.MiniPreviewPanel.RemoveButton").front());
        ThumbComponents._RemoveButton->setVisible(false);

        //ThumbButton
        ThumbComponents._ThumbButton = dynamic_cast<Button*>(ThumbPanel->getNamedDecendents("KE.WorldBuilder.SceneView.MiniPreviewPanel.ThumbnailButton").front());
        TextureLayerRecPtr ThumbTextureLayer = dynamic_cast<TextureLayer*>(ThumbComponents._ThumbButton->getBackground());
        ThumbComponents._ThumbButton->setBackgrounds(ThumbTextureLayer);
        ThumbComponents._ThumbButton->setEnabled(false);

        _SceneToThumbMap.insert(SceneToThumbMap::value_type(TheProject->getScenes(i),ThumbComponents));

        //Add to the Navigation Panel
        _SceneNavigationPanel->pushToChildren(ThumbPanel);
        
        updateSceneThumbnail(TheProject->getScenes(i));
    }
}

void SceneNavigationPanel::clearSceneThumbnails(void)
{
    //Remove all of the connections
    for(UInt32 i(0) ; i<_SceneThumbConnections.size() ; ++i)
    {
        _SceneThumbConnections[i].disconnect();
    }
    _SceneThumbConnections.clear();

    //Remove all of the Panels
    _SceneNavigationPanel->clearChildren();
    _SceneToThumbMap.clear();
}

void SceneNavigationPanel::updateSceneThumbnail(Scene* const TheScene)
{
    //Update the Label
    const Char8* Name(getName(TheScene));
    _SceneToThumbMap[TheScene]._NameLabel->setText(Name ? Name : "[Unnamed]");

    //Update the Scene render Thumb
    ButtonRecPtr TheButton(_SceneToThumbMap[TheScene]._ThumbButton);

    TextureObjChunkRecPtr ThumbTexture = dynamic_cast<TextureObjChunk*>(dynamic_cast<TextureLayer*>(TheButton->getBackground())->getTexture());
    ThumbTexture->setMinFilter(GL_LINEAR);

    ImageRecPtr ThumbImage(ThumbTexture->getImage());
    Vec2s NewSize(osgMax<Int16>(32,TheButton->getPreferredSize().x()),
                  osgMax<Int16>(32,TheButton->getPreferredSize().y()));
    if(ThumbImage == NULL ||
       ThumbImage->getWidth() != NewSize.x() ||
       ThumbImage->getHeight() != NewSize.y())
    {
        ThumbImage = Image::create();
        ThumbImage->set(Image::OSG_RGB_PF,NewSize.x(),NewSize.y());
        ThumbTexture->setImage(ThumbImage);
    }

    WindowEventProducerRecPtr TheMainWindow = dynamic_cast<WindowEventProducer*>(MainApplication::the()->getMainWindow());
    
    renderSceneToTexture(TheScene,
                         ThumbTexture,
                         TheMainWindow,
                         TheMainWindow->getRenderAction());
}

void SceneNavigationPanel::handleCreateSceneButton(ActionEventDetails* const details)
{
    CommandPtr NewSceneItemCommand = NewSceneCommand::create();
    _TheCommandManager->executeCommand(NewSceneItemCommand);

    //Select the newly created scene
    selectScene(MainApplication::the()->getProject()->getMFScenes()->back());
    updateSceneThumbnail(MainApplication::the()->getProject()->getMFScenes()->back());
}


void SceneNavigationPanel::handleSceneSelected(Scene* const TheScene)
{
    if(TheScene != NULL)
    {
        _SceneToThumbMap[TheScene]._ThumbButton->setEnabled(true);
    }
}

void SceneNavigationPanel::handleSceneDeselected(Scene* const TheScene)
{
    for(SceneToThumbMapConstItor Itor(_SceneToThumbMap.begin()) ; 
        Itor != _SceneToThumbMap.end();
        ++Itor)
    {
        if(Itor->second._ThumbButton->getEnabled())
        {
            Itor->second._ThumbButton->setEnabled(false);
            handleSceneChanged(Itor->first);
        }
    }
}

void SceneNavigationPanel::handleSceneAddRemove(Scene* const TheScene)
{
    updatePreferredSize();
}

void SceneNavigationPanel::handleSceneChanged(Scene* const TheScene)
{
    updateSceneThumbnail(TheScene);
}

void SceneNavigationPanel::handleSelectedSceneChanged(ListSelectionEventDetails* const details)
{
    //Deselect the previous selection
    handleSceneDeselected(NULL);

    //Select the current selection
    handleSceneSelected(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene());
}

void SceneNavigationPanel::handleScenesChanged(ProjectEventDetails* const details)
{
    dettachSceneThumbs();
    createSceneThumbnails();
    attachSceneThumbs();
    handleSceneDeselected(NULL);
    handleSceneSelected(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene());
    updatePreferredSize();
}

void SceneNavigationPanel::handleSceneThumbFocused(FocusEventDetails* const details,
                             Scene* const TheScene)
{
    selectScene(TheScene);
}

void SceneNavigationPanel::handleSceneRemoved(ActionEventDetails* const details,
                        Scene* const TheScene)
{
    CommandPtr RemoveSceneItemCommand = RemoveSceneCommand::create(TheScene);
    _TheCommandManager->executeCommand(RemoveSceneItemCommand);
}

void SceneNavigationPanel::handleSceneThumbEntered(MouseEventDetails* const details,
                         Scene* const TheScene)
{
    //Show the Remove Button
    _SceneToThumbMap[TheScene]._RemoveButton->setVisible(true);

    //Perhaps make bigger 
    //_SceneToThumbMap[TheScene]._Panel->setPreferredSize(_DefaultSceneThumbPanel->getPreferredSize() + Vec2f(5.0f,5.0f));
}

void SceneNavigationPanel::handleSceneThumbExited(MouseEventDetails* const details,
                         Scene* const TheScene)
{
    //Hide the Remove Button
    _SceneToThumbMap[TheScene]._RemoveButton->setVisible(false);

    //Return to size
    //_SceneToThumbMap[TheScene]._Panel->setPreferredSize(_DefaultSceneThumbPanel->getPreferredSize());
}

void SceneNavigationPanel::updatePreferredSize(void)
{
    _SceneNavigationPanel->setPreferredSize(Vec2f(_SceneNavigationViewport->getSize().x(), 
                                                  150.0f * osgFloor<Real32>((1.0f + MainApplication::the()->getProject()->getMFScenes()->size())/2.0f)) );
}


/*----------------------- constructors & destructors ----------------------*/

SceneNavigationPanel::SceneNavigationPanel(void) :
    Inherited()
{
}

SceneNavigationPanel::SceneNavigationPanel(const SceneNavigationPanel &source) :
    Inherited(source)
{
}

SceneNavigationPanel::~SceneNavigationPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneNavigationPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneNavigationPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneNavigationPanel NI" << std::endl;
}

OSG_END_NAMESPACE
