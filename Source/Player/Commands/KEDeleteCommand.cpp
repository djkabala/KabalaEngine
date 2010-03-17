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

#include "KEDeleteCommand.h"

#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DeleteCommand
A DeleteCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType DeleteCommand::_Type("DeleteCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

DeleteCommandPtr DeleteCommand::create(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel)
{
	return Ptr(new DeleteCommand(ApplicationPlayer,HierarchyPanel));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DeleteCommand::execute(void)
{
	_parent = _ApplicationPlayer->SelectedNode->getParent();

	if(_parent==_HierarchyPanel->TheTreeModel->getRootNode() && _HierarchyPanel->TheTreeModel->getRootNode()->getNChildren() <= 2) // 2 because the other child of root is bounding box
	{
		//std::cout<<"cant delete the only child.Tree becomes empty.\n";
	}
	else
	{
		_LastSelectedPathComponent = _HierarchyPanel->TheTree->getLastSelectedPathComponent();
		NodePtr temp = boost::any_cast<NodePtr>(_LastSelectedPathComponent);
		_LastSelectedPathComponentNode = temp;
		addRefCP(_LastSelectedPathComponentNode);

		_HierarchyPanel->TheTreeModel->removeNode(_LastSelectedPathComponent);
	}
	
	_nodeInCutClipboard = _ApplicationPlayer->nodeInCutClipboard ;
	_clonedNodeInCopyClipboard = _ApplicationPlayer->clonedNodeInCopyClipboard ;

	_ApplicationPlayer->nodeInCutClipboard = NullFC;
	_ApplicationPlayer->clonedNodeInCopyClipboard = NullFC;
	
	_HasBeenDone = true;


}

std::string DeleteCommand::getCommandDescription(void) const
{
	std::string Description("Delete Node");
	if(_LastSelectedPathComponentNode != NullFC)
	{
		const Char8 * ContainerName(getName(_LastSelectedPathComponentNode));
		if(ContainerName != NULL)
		{
			Description += std::string(": ") + ContainerName;
		}
	}
	return Description;// + getName(_TheModel->getBackground(_TheIndex));
}

std::string DeleteCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void DeleteCommand::redo(void)
{
    Inherited::redo();
    //_TheModel->removeBackground(_TheIndex);
	if(_LastSelectedPathComponentNode!=NullFC)
	{
		addRefCP(_LastSelectedPathComponentNode);

		_HierarchyPanel->TheTreeModel->removeNode(_LastSelectedPathComponentNode);
	
		_ApplicationPlayer->nodeInCutClipboard = NullFC;
		_ApplicationPlayer->clonedNodeInCopyClipboard = NullFC;
	}

}

void DeleteCommand::undo(void)
{
    Inherited::undo();
	//_TheIndex = _TheModel->addBackground(_RemovedBackground);

	if(_LastSelectedPathComponentNode!=NullFC)
	{
		_HierarchyPanel->TheTreeModel->addNode(boost::any(_parent),boost::any(_LastSelectedPathComponentNode));
		subRefCP(_LastSelectedPathComponentNode);

		_ApplicationPlayer->nodeInCutClipboard = _nodeInCutClipboard;
		_ApplicationPlayer->clonedNodeInCopyClipboard = _clonedNodeInCopyClipboard;
	}
		
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
		_nodeInCutClipboard = source._nodeInCutClipboard;
		_clonedNodeInCutClipboard = source._clonedNodeInCutClipboard;
		_clonedNodeInCutClipboard = source._clonedNodeInCopyClipboard;
		_ApplicationPlayer = source._ApplicationPlayer;
		_HierarchyPanel = source._HierarchyPanel;
		_LastSelectedPathComponent= source._LastSelectedPathComponent;
		_parent= source._parent;
		_LastSelectedPathComponentNode = source._LastSelectedPathComponentNode;
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

