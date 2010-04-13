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
	_Parent = _ApplicationPlayer->getSelectedNode()->getParent();

	if(_Parent==_HierarchyPanel->getSceneGraphTreeModel()->getRootNode() && _HierarchyPanel->getSceneGraphTreeModel()->getRootNode()->getNChildren() <= 2) // 2 because the other child of root is bounding box
	{
		//std::cout<<"cant delete the only child.Tree becomes empty.\n";
	}
	else
	{
		_LastSelectedPathComponent = _HierarchyPanel->getSceneGraphTree()->getLastSelectedPathComponent();
		NodePtr _Temp = boost::any_cast<NodePtr>(_LastSelectedPathComponent);
		_LastSelectedPathComponentNode = _Temp;
		addRefCP(_LastSelectedPathComponentNode);

		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(_LastSelectedPathComponent);
	}
	
	_NodeInCutClipboard = _ApplicationPlayer->getNodeInCutClipboard() ;
	_ClonedNodeInCopyClipboard = _ApplicationPlayer->getClonedNodeInCopyClipboard() ;

	_ApplicationPlayer->setNodeInCutClipboard(NullFC);
	_ApplicationPlayer->setClonedNodeInCopyClipboard(NullFC);
	
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
	return Description;
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

		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(_LastSelectedPathComponentNode);
	
		_ApplicationPlayer->setNodeInCutClipboard(NullFC);
		_ApplicationPlayer->setClonedNodeInCopyClipboard(NullFC);
	}

}

void DeleteCommand::undo(void)
{
    Inherited::undo();
	//_TheIndex = _TheModel->addBackground(_RemovedBackground);

	if(_LastSelectedPathComponentNode!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_Parent),boost::any(_LastSelectedPathComponentNode));
		subRefCP(_LastSelectedPathComponentNode);

		_ApplicationPlayer->setNodeInCutClipboard(_NodeInCutClipboard);
		_ApplicationPlayer->setClonedNodeInCopyClipboard(_ClonedNodeInCopyClipboard);
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
		_NodeInCutClipboard = source._NodeInCutClipboard;
		_ClonedNodeInCutClipboard = source._ClonedNodeInCutClipboard;
		_ClonedNodeInCutClipboard = source._ClonedNodeInCopyClipboard;
		_ApplicationPlayer = source._ApplicationPlayer;
		_HierarchyPanel = source._HierarchyPanel;
		_LastSelectedPathComponent= source._LastSelectedPathComponent;
		_Parent= source._Parent;
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

