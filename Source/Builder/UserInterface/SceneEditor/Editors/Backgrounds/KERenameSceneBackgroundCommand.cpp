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

#include "KEConfig.h"

#include "KERenameSceneBackgroundCommand.h"

#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGSimpleAttachments.h>

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RenameSceneBackgroundCommand
A RenameSceneBackgroundCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RenameSceneBackgroundCommand::_Type("RenameSceneBackgroundCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RenameSceneBackgroundCommandPtr RenameSceneBackgroundCommand::create(SceneBackgroundsComboBoxModelPtr TheModel,UInt32 Index, std::string NewName)
{
	return Ptr(new RenameSceneBackgroundCommand(TheModel, Index, NewName));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RenameSceneBackgroundCommand::execute(void)
{
	_HasBeenDone = true;

	//Get Previous Name
	try
	{
		const Char8* Name = getName(boost::any_cast<BackgroundPtr>(_TheModel->getElementAt(_Index)));
		_PreviousName = Name;
	}
	catch(boost::bad_any_cast&)
	{
	}
        
	_TheModel->renameBackground(_Index, _NewName);
}

bool RenameSceneBackgroundCommand::addEdit(const UndoableEditPtr anEdit)
{
    if(dcast(anEdit) != NULL &&
        dcast(anEdit)->getType() == RenameSceneBackgroundCommand::getClassType())
    {
        _NewName = dynamic_cast<RenameSceneBackgroundCommand*>(anEdit.get())->_NewName;
        return true;
    }
    else
    {
        return false;
    }
}

std::string RenameSceneBackgroundCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

std::string RenameSceneBackgroundCommand::getCommandDescription(void) const
{
	return std::string("Set Background Name to: ") + _NewName;
}

void RenameSceneBackgroundCommand::redo(void)
{
	Inherited::redo();
	_TheModel->renameBackground(_Index, _NewName);
}

void RenameSceneBackgroundCommand::undo(void)
{
	Inherited::undo();
	_TheModel->renameBackground(_Index, _PreviousName);
}

bool RenameSceneBackgroundCommand::isSignificant(void) const
{
	return _PreviousName.compare(_NewName) != 0;
}

const CommandType &RenameSceneBackgroundCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RenameSceneBackgroundCommand::~RenameSceneBackgroundCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RenameSceneBackgroundCommand::operator =(const RenameSceneBackgroundCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
	    _TheModel = source._TheModel;
	    _Index = source._Index;
	    _NewName = source._NewName;
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

