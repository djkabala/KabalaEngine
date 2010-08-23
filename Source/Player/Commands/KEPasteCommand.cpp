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

#include "KEPasteCommand.h"

#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSceneGraphTreeModel.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PasteCommand
A PasteCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType PasteCommand::_Type("PasteCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

PasteCommandPtr PasteCommand::create(ApplicationPlayer* const ApplicationPlayer,
                                     HierarchyPanel* const HierarchyPanel,
                                     Node* const ParentNode,
                                     bool DeepClone)
{
	return RefPtr(new PasteCommand(ApplicationPlayer,HierarchyPanel,ParentNode,DeepClone));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PasteCommand::execute(void)
{
	NodeRefPtr ClonedNodeInCopyClipboard = _ApplicationPlayer->getClonedNodeInCopyClipboard();

    if(_DeepClone)
    {
        _PastedNode = deepCloneTree(_ApplicationPlayer->getClonedNodeInCopyClipboard());
    }
    else
    {
        _PastedNode = cloneTree(_ApplicationPlayer->getClonedNodeInCopyClipboard());
    }

    const Char8* NameChar = getName(_ApplicationPlayer->getClonedNodeInCopyClipboard());
    std::string _Name= (NameChar == NULL ? "UNNAMED NODE" : NameChar);
	_Name+=" copy";
	setName(_PastedNode,_Name);

    if(_PastedNode!=NULL)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(_ParentNode,_PastedNode);
	}

	_HasBeenDone = true;
}

std::string PasteCommand::getCommandDescription(void) const
{
	return std::string("Paste ");// + getName(_TheModel->getBackground(_TheIndex));
}

std::string PasteCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void PasteCommand::redo(void)
{
    Inherited::redo();
    _HierarchyPanel->getSceneGraphTreeModel()->addNode(_ParentNode,_PastedNode);
}

void PasteCommand::undo(void)
{
    Inherited::undo();
    _HierarchyPanel->getSceneGraphTreeModel()->removeNode(_PastedNode);
}

const CommandType &PasteCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PasteCommand::~PasteCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PasteCommand::operator =(const PasteCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
	 /*   _TheModel = source._TheModel;
	    _TheIndex = source._TheIndex;*/
    }
}

