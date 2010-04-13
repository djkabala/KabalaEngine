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

CutCommandPtr CutCommand::create(ApplicationPlayerPtr ApplicationPlayer,SceneGraphTreeModelPtr SceneGraphTreeModel)
{
	return Ptr(new CutCommand(ApplicationPlayer,SceneGraphTreeModel));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CutCommand::execute(void)
{

	NodePtr parent = _ApplicationPlayer->getSelectedNode()->getParent();
	if(parent==_SceneGraphTreeModel->getRootNode() && _SceneGraphTreeModel->getRootNode()->getNChildren() <= 2)
	{
		//std::cout<<"\nCant cut the only remaining Item\n"<<std::endl;
	}
	else
	{
		_CurrentAction = _ApplicationPlayer->getCurrentAction();
		_ApplicationPlayer->setCurrentAction(CUT);

		_NodeInClipboardBeforeCut = _ApplicationPlayer->getNodeInCutClipboard() ;
		_ApplicationPlayer->setNodeInCutClipboard(_ApplicationPlayer->getSelectedNode());
		_NodeInClipboardAfterCut = _ApplicationPlayer->getNodeInCutClipboard() ;

		_ParentOfCutNode = _ApplicationPlayer->getSelectedNode()->getParent();
		
		addRefCP(_NodeInClipboardAfterCut);
		_SceneGraphTreeModel->removeNode(boost::any(_NodeInClipboardAfterCut));
	}
	
	_HasBeenDone = true;
}

std::string CutCommand::getCommandDescription(void) const
{
	return std::string("Cut ");
}

std::string CutCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void CutCommand::redo(void)
{
    Inherited::redo();

	_ApplicationPlayer->setCurrentAction(CUT);
	_ApplicationPlayer->setNodeInCutClipboard(_ApplicationPlayer->getSelectedNode());

	addRefCP(_NodeInClipboardAfterCut);
	_SceneGraphTreeModel->removeNode(boost::any(_NodeInClipboardAfterCut));
}

void CutCommand::undo(void)
{
    Inherited::undo();
	_ApplicationPlayer->setCurrentAction(_CurrentAction);
	_ApplicationPlayer->setNodeInCutClipboard(_NodeInClipboardBeforeCut);
	_SceneGraphTreeModel->addNode(boost::any(_ParentOfCutNode),boost::any(_NodeInClipboardAfterCut));
	subRefCP(_NodeInClipboardAfterCut);
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
		_NodeInClipboardBeforeCut= source._NodeInClipboardBeforeCut;
		_NodeInClipboardAfterCut= source._NodeInClipboardAfterCut;
		_ParentOfCutNode= source._ParentOfCutNode;
		_CurrentAction= source._CurrentAction;

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

