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

PasteCommandPtr PasteCommand::create(ApplicationPlayerPtr ApplicationPlayer,
                                     HierarchyPanelPtr HierarchyPanel,
                                     NodePtr ParentNode,
                                     bool DeepClone)
{
	return Ptr(new PasteCommand(ApplicationPlayer,HierarchyPanel,ParentNode,DeepClone));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PasteCommand::execute(void)
{
	NodePtr ClonedNodeInCopyClipboard = _ApplicationPlayer->getClonedNodeInCopyClipboard();

    if(_DeepClone)
    {
        _PastedNode = deepCloneTree(_ApplicationPlayer->getClonedNodeInCopyClipboard());
    }
    else
    {
        _PastedNode = cloneTree(_ApplicationPlayer->getClonedNodeInCopyClipboard());
    }

	std::string _Name=getName(_ApplicationPlayer->getClonedNodeInCopyClipboard());
	_Name+=" copy";
	setName(_PastedNode,_Name);

    if(_PastedNode!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_ParentNode),boost::any(_PastedNode));
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
    _HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_ParentNode),boost::any(_PastedNode));
    subRefCP(_PastedNode);
}

void PasteCommand::undo(void)
{
    Inherited::undo();
    addRefCP(_PastedNode);
    _HierarchyPanel->getSceneGraphTreeModel()->removeNode(boost::any(_PastedNode));
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

