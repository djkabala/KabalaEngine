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

CutCommandPtr CutCommand::create(ApplicationPlayerPtr ApplicationPlayer,
                                 SceneGraphTreeModelPtr SceneGraphTreeModel,
                                 NodePtr CutNode)
{
	return Ptr(new CutCommand(ApplicationPlayer,SceneGraphTreeModel, CutNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CutCommand::execute(void)
{
    //Delete the Node
	_Parent = _CutNode->getParent();
    addRefCP(_CutNode);

    _IndexOfCut = _Parent->findChild(_CutNode);

	_ApplicationPlayer->setClonedNodeInCopyClipboard(_CutNode);

	_SceneGraphTreeModel->removeNode(boost::any(_CutNode));
	
	_HasBeenDone = true;
}

std::string CutCommand::getCommandDescription(void) const
{
	std::string Description("Cut Node");
	if(_CutNode != NullFC)
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

	_SceneGraphTreeModel->removeNode(boost::any(_CutNode));
}

void CutCommand::undo(void)
{
    Inherited::undo();
	_SceneGraphTreeModel->insertNode(boost::any(_Parent),boost::any(_CutNode), _IndexOfCut);
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
    if(_HasBeenDone)
    {
        subRefCP(_CutNode);
    }
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

