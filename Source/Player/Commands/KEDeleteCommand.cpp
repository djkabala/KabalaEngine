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

#include "KEDeleteCommand.h"

#include <OpenSG/OSGNameAttachment.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DeleteCommand
A DeleteCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType DeleteCommand::_Type("DeleteCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

DeleteCommandPtr DeleteCommand::create(ApplicationPlayerRefPtr ApplicationPlayer,HierarchyPanelRefPtr HierarchyPanel,
                                 NodeRefPtr DeleteNode)
{
	return RefPtr(new DeleteCommand(ApplicationPlayer,HierarchyPanel,DeleteNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DeleteCommand::execute(void)
{
    //Delete the Node
	_Parent = _DeletedNode->getParent();

    _IndexOfDeletion = _Parent->findChild(_DeletedNode);
	
    _HierarchyPanel->getSceneGraphTreeModel()->removeNode(_DeletedNode);
	_HasBeenDone = true;
}

std::string DeleteCommand::getCommandDescription(void) const
{
	std::string Description("Delete Node");
	if(_DeletedNode != NULL)
	{
		const Char8 * ContainerName(getName(_DeletedNode));
		if(ContainerName != NULL)
		{
			Description += std::string(": ") + ContainerName;
		}
	}
	return Description;
}

std::string DeleteCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void DeleteCommand::redo(void)
{
    Inherited::redo();
    _HierarchyPanel->getSceneGraphTreeModel()->removeNode(_DeletedNode);
}

void DeleteCommand::undo(void)
{
    Inherited::undo();

    _HierarchyPanel->getSceneGraphTreeModel()->insertNode(boost::any(_Parent),boost::any(_DeletedNode),_IndexOfDeletion);
		
}

const CommandType &DeleteCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DeleteCommand::~DeleteCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeleteCommand::operator =(const DeleteCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
		_ApplicationPlayer = source._ApplicationPlayer;
		_HierarchyPanel = source._HierarchyPanel;
		_DeletedNode = source._DeletedNode;
    }
}

