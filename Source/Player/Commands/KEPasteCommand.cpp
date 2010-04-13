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

	_CurrentAction = _ApplicationPlayer->getCurrentAction();
	_NodeInCutClipboard = _ApplicationPlayer->getNodeInCutClipboard();
	_ClonedNodeInCopyClipboard = _ApplicationPlayer->getClonedNodeInCopyClipboard();
	_SelectedNode = _ApplicationPlayer->getSelectedNode();

	if(_ApplicationPlayer->getCurrentAction() == CUT && _ApplicationPlayer->getNodeInCutClipboard()!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_ApplicationPlayer->getSelectedNode()),boost::any(_ApplicationPlayer->getNodeInCutClipboard()));
		subRefCP(_ApplicationPlayer->getNodeInCutClipboard());
		_ApplicationPlayer->setNodeInCutClipboard(NullFC);
	}
	else if(_ApplicationPlayer->getCurrentAction() == COPY && _ApplicationPlayer->getClonedNodeInCopyClipboard()!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_ApplicationPlayer->getSelectedNode()),boost::any(_ApplicationPlayer->getClonedNodeInCopyClipboard()));
		_ApplicationPlayer->setClonedNodeInCopyClipboard(NullFC);
	}
	_ApplicationPlayer->setCurrentAction(NONE);

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
	if(_CurrentAction == CUT && _NodeInCutClipboard!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_SelectedNode),boost::any(_NodeInCutClipboard));
		subRefCP(_NodeInCutClipboard);
		_ApplicationPlayer->setNodeInCutClipboard(NullFC);
	}
	else if(_ApplicationPlayer->getCurrentAction() == COPY && _ApplicationPlayer->getClonedNodeInCopyClipboard()!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_SelectedNode),boost::any(_ClonedNodeInCopyClipboard));
		subRefCP(_ClonedNodeInCopyClipboard);
		_ApplicationPlayer->setClonedNodeInCopyClipboard(NullFC);
	}
	_ApplicationPlayer->setCurrentAction(NONE);
}

void PasteCommand::undo(void)
{
    Inherited::undo();
	if(_CurrentAction == CUT && _NodeInCutClipboard!=NullFC)
	{
		addRefCP(_NodeInCutClipboard);
		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(boost::any(_NodeInCutClipboard));
		_ApplicationPlayer->setNodeInCutClipboard(_NodeInCutClipboard);
	}
	else if(_CurrentAction == COPY && _ClonedNodeInCopyClipboard!=NullFC)
	{
		addRefCP(_ClonedNodeInCopyClipboard);
		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(boost::any(_ClonedNodeInCopyClipboard));
		_ApplicationPlayer->setClonedNodeInCopyClipboard(_ClonedNodeInCopyClipboard);
	}
	_ApplicationPlayer->setCurrentAction(_CurrentAction);

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

