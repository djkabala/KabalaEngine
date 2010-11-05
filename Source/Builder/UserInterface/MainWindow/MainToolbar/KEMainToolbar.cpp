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

#include "KEMainToolbar.h"
#include <OpenSG/OSGButton.h>
#include "Builder/KEApplicationBuilder.h"
#include "Project/KEProject.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

#include "Builder/UserInterface/Commands/KEOpenProjectCommand.h"
#include "Builder/UserInterface/Commands/KESaveProjectAsCommand.h"
#include "Builder/UserInterface/Commands/KENewProjectCommand.h"
#include "Builder/UserInterface/Commands/KEPlayProjectCommand.h"
#include "Builder/UserInterface/Commands/KERedoCommand.h"
#include "Builder/UserInterface/Commands/KEUndoCommand.h"
#include "Builder/UserInterface/Commands/KEAboutKabalaEngineCommand.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMainToolbarBase.cpp file.
// To modify it, please change the .fcd file (OSGMainToolbar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MainToolbar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MainToolbar::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _OpenButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.OpenButton", TheApplicationBuilder));
    _SaveButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.SaveButton", TheApplicationBuilder));
    _NewButton  = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.NewButton",  TheApplicationBuilder));
    _UndoButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.UndoButton", TheApplicationBuilder));
    _RedoButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.RedoButton", TheApplicationBuilder));
    _PlayButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.PlayButton", TheApplicationBuilder));
    _HelpButton = dynamic_cast<Button*>(findContainer("KE.WorldBuilder.MainToolbar.HelpButton", TheApplicationBuilder));
}

void MainToolbar::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _OpenButton = NULL;
    _SaveButton = NULL;
    _NewButton = NULL;
    _UndoButton = NULL;
    _RedoButton = NULL;
    _PlayButton = NULL;
    _HelpButton = NULL;
}

void MainToolbar::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TheCommandManager = TheApplicationBuilder->getCommandManager();
    _UndoManager = TheApplicationBuilder->getUndoManager();
    updateUndoRedoInterfaces();

    _OpenButtonConnection = _OpenButton->connectActionPerformed(boost::bind(&MainToolbar::handleOpenButton, this, _1));
    _SaveButtonConnection = _SaveButton->connectActionPerformed(boost::bind(&MainToolbar::handleSaveButton, this, _1));
    _NewButtonConnection = _NewButton->connectActionPerformed(boost::bind(&MainToolbar::handleNewButton, this, _1));
    _UndoButtonConnection = _UndoButton->connectActionPerformed(boost::bind(&MainToolbar::handleUndoButton, this, _1));
    _RedoButtonConnection = _RedoButton->connectActionPerformed(boost::bind(&MainToolbar::handleRedoButton, this, _1));
    _PlayButtonConnection = _PlayButton->connectActionPerformed(boost::bind(&MainToolbar::handlePlayButton, this, _1));
    _HelpButtonConnection = _HelpButton->connectActionPerformed(boost::bind(&MainToolbar::handleHelpButton, this, _1));
    _UndoChangeConnection = _UndoManager->connectStateChanged(boost::bind(&MainToolbar::handleUndoChange, this, _1));

    _NewButton->setEnabled(false);

}

void MainToolbar::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _OpenButtonConnection.disconnect();
    _SaveButtonConnection.disconnect();
    _NewButtonConnection.disconnect();
    _UndoButtonConnection.disconnect();
    _RedoButtonConnection.disconnect();
    _PlayButtonConnection.disconnect();
    _HelpButtonConnection.disconnect();
    _UndoChangeConnection.disconnect();

    _UndoManager = UndoManagerPtr();
    _TheCommandManager = CommandManagerPtr();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MainToolbar::handleOpenButton(ActionEventDetails* const details)
{
    CommandPtr OpenProjectItemCommand = OpenProjectCommand::create();
    _TheCommandManager->executeCommand(OpenProjectItemCommand);
}

void MainToolbar::handleSaveButton(ActionEventDetails* const details)
{
    /*CommandPtr SaveProjectItemCommand = SaveProjectCommand::create();
    _TheCommandManager->executeCommand(SaveProjectItemCommand);*/
    CommandPtr SaveProjectAsItemCommand = SaveProjectAsCommand::create();
    _TheCommandManager->executeCommand(SaveProjectAsItemCommand);
}

void MainToolbar::handleNewButton(ActionEventDetails* const details)
{
    CommandPtr NewProjectItemCommand = NewProjectCommand::create();
    _TheCommandManager->executeCommand(NewProjectItemCommand);
}

void MainToolbar::handleUndoButton(ActionEventDetails* const details)
{
    CommandPtr UndoItemCommand = UndoCommand::create(_UndoManager);
    _TheCommandManager->executeCommand(UndoItemCommand);
}

void MainToolbar::handleRedoButton(ActionEventDetails* const details)
{
    CommandPtr RedoItemCommand = RedoCommand::create(_UndoManager);
    _TheCommandManager->executeCommand(RedoItemCommand);
}

void MainToolbar::handlePlayButton(ActionEventDetails* const details)
{
    CommandPtr PlayProjectItemCommand = PlayProjectCommand::create();
    _TheCommandManager->executeCommand(PlayProjectItemCommand);
}

void MainToolbar::handleHelpButton(ActionEventDetails* const details)
{
    CommandPtr AboutKabalaEngineItemCommand = AboutKabalaEngineCommand::create();
    _TheCommandManager->executeCommand(AboutKabalaEngineItemCommand);
}

void MainToolbar::handleUndoChange(ChangeEventDetails* const details)
{
    updateUndoRedoInterfaces();
}

void MainToolbar::updateUndoRedoInterfaces(void)
{
    _UndoButton->setEnabled(_UndoManager->canUndo());
    if(_UndoManager->canUndo())
    {
        _UndoButton->setToolTipText(_UndoManager->getUndoPresentationName());
    }
    else
    {
        _UndoButton->setToolTipText("Undo");
    }

    _RedoButton->setEnabled(_UndoManager->canRedo());
    if(_UndoManager->canRedo())
    {
        _RedoButton->setToolTipText(_UndoManager->getRedoPresentationName());
    }
    else
    {
        _RedoButton->setToolTipText("Redo");
    }
}

/*----------------------- constructors & destructors ----------------------*/

MainToolbar::MainToolbar(void) :
    Inherited()
{
}

MainToolbar::MainToolbar(const MainToolbar &source) :
    Inherited(source)
{
}

MainToolbar::~MainToolbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MainToolbar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MainToolbar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MainToolbar NI" << std::endl;
}

OSG_END_NAMESPACE
