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

#include "KECutCommand.h"

#include <OpenSG/OSGNameAttachment.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CutCommand
A CutCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType CutCommand::_Type("CutCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

CutCommandPtr CutCommand::create(ApplicationPlayer* const ApplicationPlayer,
                                 SceneGraphTreeModel* const SceneGraphTreeModel,
                                 Node* const CutNode)
{
	return RefPtr(new CutCommand(ApplicationPlayer,SceneGraphTreeModel, CutNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CutCommand::execute(void)
{
    //Delete the Node
	_Parent = _CutNode->getParent();

    _IndexOfCut = _Parent->findChild(_CutNode);

	_ApplicationPlayer->setClonedNodeInCopyClipboard(_CutNode);

	_SceneGraphTreeModel->removeNode(_CutNode);
	
	_HasBeenDone = true;
}

std::string CutCommand::getCommandDescription(void) const
{
	std::string Description("Cut Node");
	if(_CutNode != NULL)
	{
		const Char8 * ContainerName(getName(_CutNode));
		if(ContainerName != NULL)
		{
			Description += std::string(": ") + ContainerName;
		}
	}
	return Description;
}

std::string CutCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void CutCommand::redo(void)
{
    Inherited::redo();

	_SceneGraphTreeModel->removeNode(_CutNode);
}

void CutCommand::undo(void)
{
    Inherited::undo();
	_SceneGraphTreeModel->insertNode(_Parent,_CutNode, _IndexOfCut);
}

const CommandType &CutCommand::getType(void) const
{
	return _Type;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CutCommand::~CutCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CutCommand::operator =(const CutCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
		_ApplicationPlayer = source._ApplicationPlayer;
		_SceneGraphTreeModel = source._SceneGraphTreeModel;
    }
}

