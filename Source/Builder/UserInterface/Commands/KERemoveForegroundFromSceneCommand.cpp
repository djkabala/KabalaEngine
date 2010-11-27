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

#include "KERemoveForegroundFromSceneCommand.h"
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGNameAttachment.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RemoveForegroundFromSceneCommand
A RemoveForegroundFromSceneCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RemoveForegroundFromSceneCommand::_Type("RemoveForegroundFromSceneCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RemoveForegroundFromSceneCommandPtr RemoveForegroundFromSceneCommand::create(Scene* RootScene,
                                                                             Foreground* RemoveForeground)
{
	return Ptr(new RemoveForegroundFromSceneCommand(RootScene, RemoveForeground));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RemoveForegroundFromSceneCommand::execute(void)
{
    _RootScene->getPrimaryViewport()->removeObjFromForegrounds(_RemovedForeground);

	_HasBeenDone = true;
}

std::string RemoveForegroundFromSceneCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void RemoveForegroundFromSceneCommand::redo(void)
{
    Inherited::redo();

    _RootScene->getPrimaryViewport()->removeObjFromForegrounds(_RemovedForeground);
}

void RemoveForegroundFromSceneCommand::undo(void)
{
    Inherited::undo();

    _RootScene->getPrimaryViewport()->addForeground(_RemovedForeground);
}


std::string RemoveForegroundFromSceneCommand::getCommandDescription(void) const
{
	return std::string("Remove ") + _RemovedForeground->getType().getName() + " from scene";
}

const CommandType &RemoveForegroundFromSceneCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RemoveForegroundFromSceneCommand::~RemoveForegroundFromSceneCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

