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

#include "KEMainMenu.h"
#include <OpenSG/OSGMenuItem.h>
#include "Application/KEMainApplication.h"
#include "Builder/KEApplicationBuilder.h"
#include "Project/KEProject.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

#include "Builder/UserInterface/Commands/KEOpenProjectCommand.h"
#include "Builder/UserInterface/Commands/KESaveProjectAsCommand.h"
#include "Builder/UserInterface/Commands/KECloseProjectCommand.h"
#include "Builder/UserInterface/Commands/KENewProjectCommand.h"
#include "Builder/UserInterface/Commands/KEPlayProjectCommand.h"
#include "Builder/UserInterface/Commands/KERedoCommand.h"
#include "Builder/UserInterface/Commands/KEUndoCommand.h"
#include "Builder/UserInterface/Commands/KEQuitAppCommand.h"
#include "Builder/UserInterface/Commands/KEAboutKabalaEngineCommand.h"
#include "Builder/UserInterface/Commands/KEOpenCreditsCommand.h"

#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMainMenuBase.cpp file.
// To modify it, please change the .fcd file (OSGMainMenu.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MainMenu::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MainMenu::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _OpenMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.OpenMenuItem", TheApplicationBuilder));
    _SaveMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.SaveProjectMenuItem", TheApplicationBuilder));
    _SaveAsMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.SaveProjectAsMenuItem", TheApplicationBuilder));
    _CloseMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.CloseMenuItem", TheApplicationBuilder));
    _SettingsMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.SettingsMenuItem", TheApplicationBuilder));
    _NewMenuItem = dynamic_cast<MenuItem*> (findContainer("KE.WorldBuilder.MainMenu.NewProjectMenuItem", TheApplicationBuilder));
    _QuitMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.QuitMenuItem", TheApplicationBuilder));
    _RecentProjectsMenu = dynamic_cast<Menu*>(findContainer("KE.WorldBuilder.MainMenu.RecentProjectsMenu", TheApplicationBuilder));
 
    _UndoMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.UndoMenuItem", TheApplicationBuilder));
    _RedoMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.RedoMenuItem", TheApplicationBuilder));
    
    _PlayMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.PlayMenuItem", TheApplicationBuilder));
    _ProjectAdvancedSettingsMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.ProjectAdvancedSettingsMenuItem", TheApplicationBuilder));
    _ProjectPropertiesMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.ProjectPropertiesMenuItem", TheApplicationBuilder));
    
    _HelpMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.HelpMenuItem", TheApplicationBuilder));
    _CreditsMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.CreditsMenuItem", TheApplicationBuilder));
    _AboutMenuItem = dynamic_cast<MenuItem*>(findContainer("KE.WorldBuilder.MainMenu.AboutMenuItem", TheApplicationBuilder));
}

void MainMenu::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _OpenMenuItem = NULL;
    _SaveMenuItem = NULL;
    _SaveAsMenuItem = NULL;
    _CloseMenuItem = NULL;
    _SettingsMenuItem = NULL;
    _RecentProjectsMenu = NULL;
    _NewMenuItem = NULL;
    _QuitMenuItem = NULL;
    _ProjectPropertiesMenuItem = NULL;

    _UndoMenuItem = NULL;
    _RedoMenuItem = NULL;

    _PlayMenuItem = NULL;
    _ProjectAdvancedSettingsMenuItem = NULL;
    _ProjectPropertiesMenuItem = NULL;

    _HelpMenuItem = NULL;
    _AboutMenuItem = NULL;
    _CreditsMenuItem = NULL;
}

void MainMenu::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TheCommandManager = TheApplicationBuilder->getCommandManager();
    _UndoManager = TheApplicationBuilder->getUndoManager();
    updateUndoRedoInterfaces();

    disconnectRecentProjectMenuItems();
    createRecentProjectMenuItems();
    connectRecentProjectMenuItems();

    _OpenMenuItemConnection = _OpenMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleOpenMenuItem, this, _1));
    _SaveMenuItemConnection = _SaveMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleSaveMenuItem, this, _1));
    _SaveAsMenuItemConnection = _SaveAsMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleSaveAsMenuItem, this, _1));
    _CloseMenuItemConnection = _CloseMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleCloseMenuItem, this, _1));
    _SettingsMenuItemConnection = _SettingsMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleSettingsMenuItem, this, _1));
    _NewMenuItemConnection = _NewMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleNewMenuItem, this, _1));
    _QuitMenuItemConnection = _QuitMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleQuitMenuItem, this, _1));

    _UndoMenuItemConnection = _UndoMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleUndoMenuItem, this, _1));
    _RedoMenuItemConnection = _RedoMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleRedoMenuItem, this, _1));

    _PlayMenuItemConnection = _PlayMenuItem->connectActionPerformed(boost::bind(&MainMenu::handlePlayMenuItem, this, _1));
    _ProjectAdvancedSettingsMenuItemConnection = _ProjectAdvancedSettingsMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleProjectAdvancedSettingsMenuItem, this, _1));
    _ProjectPropertiesMenuItemConnection = _ProjectPropertiesMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleProjectPropertiesMenuItem, this, _1));

    _HelpMenuItemConnection = _HelpMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleHelpMenuItem, this, _1));
    _AboutMenuItemConnection = _AboutMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleAboutMenuItem, this, _1));
    _CreditsMenuItemConnection = _CreditsMenuItem->connectActionPerformed(boost::bind(&MainMenu::handleCreditsMenuItem, this, _1));

    _UndoChangeConnection = _UndoManager->connectStateChanged(boost::bind(&MainMenu::handleUndoChange, this, _1));

    _SettingsMenuItem->setEnabled(false);
    _ProjectPropertiesMenuItem->setEnabled(false);
    _HelpMenuItem->setEnabled(false);
    _CloseMenuItem->setEnabled(false);
    _NewMenuItem->setEnabled(false);
}

void MainMenu::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    
    disconnectRecentProjectMenuItems();

    _OpenMenuItemConnection.disconnect();
    _SaveMenuItemConnection.disconnect();
    _SaveAsMenuItemConnection.disconnect();
    _CloseMenuItemConnection.disconnect();
    _SettingsMenuItemConnection.disconnect();
    _NewMenuItemConnection.disconnect();
    _QuitMenuItemConnection.disconnect();

    _UndoMenuItemConnection.disconnect();
    _RedoMenuItemConnection.disconnect();

    _PlayMenuItemConnection.disconnect();
    _ProjectAdvancedSettingsMenuItemConnection.disconnect();
    _ProjectPropertiesMenuItemConnection.disconnect();


    _HelpMenuItemConnection.disconnect();
    _AboutMenuItemConnection.disconnect();
    _CreditsMenuItemConnection.disconnect();

    _UndoChangeConnection.disconnect();

    _UndoManager = UndoManagerPtr();
    _TheCommandManager = CommandManagerPtr();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MainMenu::updateRecentProjectsMenu(void)
{
}

void MainMenu::handleOpenMenuItem(ActionEventDetails* const details)
{
    CommandPtr OpenProjectItemCommand = OpenProjectCommand::create();
    _TheCommandManager->executeCommand(OpenProjectItemCommand);
}

void MainMenu::handleSaveMenuItem(ActionEventDetails* const details)
{
    /*CommandPtr SaveProjectItemCommand = SaveProjectCommand::create();
    _TheCommandManager->executeCommand(SaveProjectItemCommand);*/
    CommandPtr SaveProjectAsItemCommand = SaveProjectAsCommand::create();
    _TheCommandManager->executeCommand(SaveProjectAsItemCommand);
}

void MainMenu::handleSaveAsMenuItem(ActionEventDetails* const details)
{
    CommandPtr SaveProjectAsItemCommand = SaveProjectAsCommand::create();
    _TheCommandManager->executeCommand(SaveProjectAsItemCommand);
}

void MainMenu::handleCloseMenuItem(ActionEventDetails* const details)
{
    CommandPtr CloseProjectItemCommand = CloseProjectCommand::create();
    _TheCommandManager->executeCommand(CloseProjectItemCommand);
}

void MainMenu::handleSettingsMenuItem(ActionEventDetails* const details)
{
    //CommandPtr OpenProjectItemCommand = OpenProjectCommand::create();
    //_TheCommandManager->executeCommand(OpenProjectItemCommand);
}

void MainMenu::handleNewMenuItem(ActionEventDetails* const details)
{
    CommandPtr NewProjectItemCommand = NewProjectCommand::create();
    _TheCommandManager->executeCommand(NewProjectItemCommand);
}

void MainMenu::handleQuitMenuItem(ActionEventDetails* const details)
{
    CommandPtr QuitAppItemCommand = QuitAppCommand::create();
    _TheCommandManager->executeCommand(QuitAppItemCommand);
}

void MainMenu::handleUndoMenuItem(ActionEventDetails* const details)
{
    CommandPtr UndoItemCommand = UndoCommand::create(_UndoManager);
    _TheCommandManager->executeCommand(UndoItemCommand);
}

void MainMenu::handleRedoMenuItem(ActionEventDetails* const details)
{
    CommandPtr RedoItemCommand = RedoCommand::create(_UndoManager);
    _TheCommandManager->executeCommand(RedoItemCommand);
}

void MainMenu::handlePlayMenuItem(ActionEventDetails* const details)
{
    CommandPtr PlayProjectItemCommand = PlayProjectCommand::create();
    _TheCommandManager->executeCommand(PlayProjectItemCommand);
}

void MainMenu::handleProjectAdvancedSettingsMenuItem(ActionEventDetails* const details)
{
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->openEditor();
}

void MainMenu::handleProjectPropertiesMenuItem(ActionEventDetails* const details)
{
    /*CommandPtr OpenProjectItemCommand = OpenProjectCommand::create();
    _TheCommandManager->executeCommand(OpenProjectItemCommand);*/
}

void MainMenu::handleHelpMenuItem(ActionEventDetails* const details)
{
    /*CommandPtr OpenProjectItemCommand = OpenProjectCommand::create();
    _TheCommandManager->executeCommand(OpenProjectItemCommand);*/
}

void MainMenu::handleCreditsMenuItem(ActionEventDetails* const details)
{
    CommandPtr OpenCreditsItemCommand = OpenCreditsCommand::create();
    _TheCommandManager->executeCommand(OpenCreditsItemCommand);
}

void MainMenu::handleAboutMenuItem(ActionEventDetails* const details)
{
    CommandPtr AboutKabalaEngineItemCommand = AboutKabalaEngineCommand::create();
    _TheCommandManager->executeCommand(AboutKabalaEngineItemCommand);
}

void MainMenu::handleUndoChange(ChangeEventDetails* const details)
{
    updateUndoRedoInterfaces();
}

void MainMenu::handleRecentProjectMenuItem(ActionEventDetails* const details,
                                           UInt32 Index)
{
}

void MainMenu::updateUndoRedoInterfaces(void)
{
    _UndoMenuItem->setEnabled(_UndoManager->canUndo());
    if(_UndoManager->canUndo())
    {
        _UndoMenuItem->setText(_UndoManager->getUndoPresentationName());
    }
    else
    {
        _UndoMenuItem->setText("Undo");
    }

    _RedoMenuItem->setEnabled(_UndoManager->canRedo());
    if(_UndoManager->canRedo())
    {
        _RedoMenuItem->setText(_UndoManager->getRedoPresentationName());
    }
    else
    {
        _RedoMenuItem->setText("Redo");
    }
}

void MainMenu::createRecentProjectMenuItems(void)
{
    //Clear all of the previous Items
    _RecentProjectsMenu->removeAllItems();

    //Make a Menu Item for each of the recent projects
    std::vector<BoostPath> RecentProjects;
    try
    {
        RecentProjects = MainApplication::the()->getSettings().get_vec<BoostPath>("basic.recent_projects.files");
    }
    catch(boost::property_tree::ptree_bad_path&)
    {
    }
    
    MenuItemRecPtr NewRecentProjectItem;
    for(UInt32 i(0) ; i<RecentProjects.size() ; ++i)
    {
        //Create the menu Item
        NewRecentProjectItem = MenuItem::create();
        NewRecentProjectItem->setText(boost::lexical_cast<std::string>(i+1) + " " + RecentProjects[i].filename());

        //Add the RecentProject Menu Item to the SubMenu
        _RecentProjectsMenu->addItem(NewRecentProjectItem);
    }
}

void MainMenu::updateRecentProjectMenuItems(void)
{
    disconnectRecentProjectMenuItems();
    createRecentProjectMenuItems();
    connectRecentProjectMenuItems();
}

void MainMenu::disconnectRecentProjectMenuItems(void)
{
    for(UInt32 i(0) ; i<_RecentProjectMenuItemConnections.size() ; ++i)
    {
        _RecentProjectMenuItemConnections[i].disconnect();
    }
    _RecentProjectMenuItemConnections.clear();
}

void MainMenu::connectRecentProjectMenuItems(void)
{
    for(UInt32 i(0) ; i<_RecentProjectsMenu->getNumItems() ; ++i)
    {
        _RecentProjectMenuItemConnections.push_back(_RecentProjectsMenu->getItem(i)->connectActionPerformed(boost::bind(&MainMenu::handleRecentProjectMenuItem, this, _1, i)));
    }
}
/*----------------------- constructors & destructors ----------------------*/

MainMenu::MainMenu(void) :
    Inherited()
{
}

MainMenu::MainMenu(const MainMenu &source) :
    Inherited(source)
{
}

MainMenu::~MainMenu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MainMenu::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MainMenu::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MainMenu NI" << std::endl;
}

OSG_END_NAMESPACE
