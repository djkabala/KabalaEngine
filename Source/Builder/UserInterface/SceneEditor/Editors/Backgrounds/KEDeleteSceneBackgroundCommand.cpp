/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#include "KEDeleteSceneBackgroundCommand.h"

#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DeleteSceneBackgroundCommand
A DeleteSceneBackgroundCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType DeleteSceneBackgroundCommand::_Type("DeleteSceneBackgroundCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

DeleteSceneBackgroundCommandPtr DeleteSceneBackgroundCommand::create(SceneBackgroundsComboBoxModelPtr TheModel,UInt32 TheIndex)
{
	return Ptr(new DeleteSceneBackgroundCommand(TheModel, TheIndex));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DeleteSceneBackgroundCommand::execute(void)
{
	_RemovedBackground = BackgroundPtr::dcast(_TheModel->getBackground(_TheIndex));
    _TheModel->removeBackground(_TheIndex);
}

std::string DeleteSceneBackgroundCommand::getCommandDescription(void) const
{
	return std::string("Delete ") + getName(_TheModel->getBackground(_TheIndex));
}

std::string DeleteSceneBackgroundCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void DeleteSceneBackgroundCommand::redo(void)
{
    Inherited::redo();
    _TheModel->removeBackground(_TheIndex);
}

void DeleteSceneBackgroundCommand::undo(void)
{
    Inherited::undo();
	_TheIndex = _TheModel->addBackground(_RemovedBackground);
}

const CommandType &DeleteSceneBackgroundCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DeleteSceneBackgroundCommand::~DeleteSceneBackgroundCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeleteSceneBackgroundCommand::operator =(const DeleteSceneBackgroundCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
	    _TheModel = source._TheModel;
	    _TheIndex = source._TheIndex;
    }
}
/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

