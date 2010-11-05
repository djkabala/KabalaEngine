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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEAddForegroundToSceneCommand.h"
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGNameAttachment.h>

#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneTreeModel.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AddForegroundToSceneCommand
A AddForegroundToSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType AddForegroundToSceneCommand::_Type("AddForegroundToSceneCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

AddForegroundToSceneCommandPtr AddForegroundToSceneCommand::create(const FieldContainerType& ForegroundType, Scene* RootScene)
{
	return Ptr(new AddForegroundToSceneCommand(ForegroundType,RootScene));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AddForegroundToSceneCommand::execute(void)
{
    _CreatedForeground = dynamic_pointer_cast<Foreground>(_ForegroundType.createContainer());
    setName(_CreatedForeground, _ForegroundType.getName());
    _RootScene->getPrimaryViewport()->addForeground(_CreatedForeground);

    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->foregroundAdded(_CreatedForeground);

	_HasBeenDone = true;
}

std::string AddForegroundToSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void AddForegroundToSceneCommand::redo(void)
{
    Inherited::redo();

    //Add the scene to the project
    _RootScene->getPrimaryViewport()->addForeground(_CreatedForeground);
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->foregroundAdded(_CreatedForeground);
}

void AddForegroundToSceneCommand::undo(void)
{
    Inherited::undo();

    //Remove scene from the project
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->foregroundWillBeRemoved(_CreatedForeground);
    _RootScene->getPrimaryViewport()->removeObjFromForegrounds(_CreatedForeground);
    dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneComponentTree()->getTreeModel()->foregroundRemoved(_CreatedForeground);
}


std::string AddForegroundToSceneCommand::getCommandDescription(void) const
{
	return std::string("Add ") + _ForegroundType.getName() + " to scene";
}

const CommandType &AddForegroundToSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AddForegroundToSceneCommand::~AddForegroundToSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

