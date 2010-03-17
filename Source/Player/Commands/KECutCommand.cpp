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

#include "KECutCommand.h"

#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CutCommand
A CutCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType CutCommand::_Type("CutCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

CutCommandPtr CutCommand::create(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel)
{
	return Ptr(new CutCommand(ApplicationPlayer,HierarchyPanel));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CutCommand::execute(void)
{

	NodePtr parent = _ApplicationPlayer->SelectedNode->getParent();
	if(parent==_HierarchyPanel->TheTreeModel->getRootNode() && _HierarchyPanel->TheTreeModel->getRootNode()->getNChildren() <= 2)
	{
		//std::cout<<"\nCant cut the only remaining Item\n"<<std::endl;
	}
	else
	{
		_currentAction = _ApplicationPlayer->currentAction;
		_ApplicationPlayer->currentAction = CUT;

		_nodeInClipboardBeforeCut = _ApplicationPlayer->nodeInCutClipboard ;
		_ApplicationPlayer->nodeInCutClipboard = _ApplicationPlayer->SelectedNode;
		_nodeInClipboardAfterCut = _ApplicationPlayer->nodeInCutClipboard ;

		_parentOfCutNode = _ApplicationPlayer->SelectedNode->getParent();
		
		addRefCP(_nodeInClipboardAfterCut);
		_HierarchyPanel->TheTreeModel->removeNode(boost::any(_nodeInClipboardAfterCut));
	}
	
	_HasBeenDone = true;
}

std::string CutCommand::getCommandDescription(void) const
{
	return std::string("Cut ");// + getName(_TheModel->getBackground(_TheIndex));
}

std::string CutCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void CutCommand::redo(void)
{
    Inherited::redo();

	_ApplicationPlayer->currentAction = CUT;
	_ApplicationPlayer->nodeInCutClipboard = _ApplicationPlayer->SelectedNode;

	addRefCP(_nodeInClipboardAfterCut);
	_HierarchyPanel->TheTreeModel->removeNode(boost::any(_nodeInClipboardAfterCut));
}

void CutCommand::undo(void)
{
    Inherited::undo();
	_ApplicationPlayer->currentAction = _currentAction;
	_ApplicationPlayer->nodeInCutClipboard = _nodeInClipboardBeforeCut;
	_HierarchyPanel->TheTreeModel->addNode(boost::any(_parentOfCutNode),boost::any(_nodeInClipboardAfterCut));
	subRefCP(_nodeInClipboardAfterCut);
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
		_HierarchyPanel = source._HierarchyPanel;
		_nodeInClipboardBeforeCut= source._nodeInClipboardBeforeCut;
		_nodeInClipboardAfterCut= source._nodeInClipboardAfterCut;
		_parentOfCutNode= source._parentOfCutNode;
		_currentAction= source._currentAction;

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

