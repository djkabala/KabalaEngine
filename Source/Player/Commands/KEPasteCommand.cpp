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

#include "KEPasteCommand.h"

#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PasteCommand
A PasteCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType PasteCommand::_Type("PasteCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

PasteCommandPtr PasteCommand::create(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel)
{
	return Ptr(new PasteCommand(ApplicationPlayer,HierarchyPanel));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PasteCommand::execute(void)
{

	_currentAction = _ApplicationPlayer->currentAction;
	_nodeInCutClipboard = _ApplicationPlayer->nodeInCutClipboard;
	_clonedNodeInCopyClipboard = _ApplicationPlayer->clonedNodeInCopyClipboard;
	_SelectedNode = _ApplicationPlayer->SelectedNode;

	if(_ApplicationPlayer->currentAction == CUT && _ApplicationPlayer->nodeInCutClipboard!=NullFC)
	{
		_HierarchyPanel->TheTreeModel->addNode(boost::any(_ApplicationPlayer->SelectedNode),boost::any(_ApplicationPlayer->nodeInCutClipboard));
		subRefCP(_ApplicationPlayer->nodeInCutClipboard);
		_ApplicationPlayer->nodeInCutClipboard = NullFC;
	}
	else if(_ApplicationPlayer->currentAction == COPY && _ApplicationPlayer->clonedNodeInCopyClipboard!=NullFC)
	{
		_HierarchyPanel->TheTreeModel->addNode(boost::any(_ApplicationPlayer->SelectedNode),boost::any(_ApplicationPlayer->clonedNodeInCopyClipboard));
		_ApplicationPlayer->clonedNodeInCopyClipboard = NullFC;
	}
	_ApplicationPlayer->currentAction = NONE;

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
	if(_currentAction == CUT && _nodeInCutClipboard!=NullFC)
	{
		_HierarchyPanel->TheTreeModel->addNode(boost::any(_SelectedNode),boost::any(_nodeInCutClipboard));
		subRefCP(_nodeInCutClipboard);
		_ApplicationPlayer->nodeInCutClipboard = NullFC;
	}
	else if(_ApplicationPlayer->currentAction == COPY && _ApplicationPlayer->clonedNodeInCopyClipboard!=NullFC)
	{
		_HierarchyPanel->TheTreeModel->addNode(boost::any(_SelectedNode),boost::any(_clonedNodeInCopyClipboard));
		subRefCP(_clonedNodeInCopyClipboard);
		_ApplicationPlayer->clonedNodeInCopyClipboard = NullFC;
	}
	_ApplicationPlayer->currentAction = NONE;
}

void PasteCommand::undo(void)
{
    Inherited::undo();
	if(_currentAction == CUT && _nodeInCutClipboard!=NullFC)
	{
		addRefCP(_nodeInCutClipboard);
		_HierarchyPanel->TheTreeModel->removeNode(boost::any(_nodeInCutClipboard));
		_ApplicationPlayer->nodeInCutClipboard = _nodeInCutClipboard;
	}
	else if(_currentAction == COPY && _clonedNodeInCopyClipboard!=NullFC)
	{
		addRefCP(_clonedNodeInCopyClipboard);
		_HierarchyPanel->TheTreeModel->removeNode(boost::any(_clonedNodeInCopyClipboard));
		_ApplicationPlayer->clonedNodeInCopyClipboard = _clonedNodeInCopyClipboard;
	}
	_ApplicationPlayer->currentAction = _currentAction;

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

