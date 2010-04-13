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

#include "KENewCommand.h"

#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NewCommand
A NewCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType NewCommand::_Type("NewCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

NewCommandPtr NewCommand::create(HierarchyPanelPtr HierarchyPanel,FieldContainerType* FCType)
{
	return Ptr(new NewCommand(HierarchyPanel,FCType));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void NewCommand::execute(void)
{

	NodeCorePtr newCore = FieldContainerFactory::the()->createNodeCore(_FCType->getCName());

	_NewNode = Node::create();
	beginEditCP(_NewNode,Node::CoreFieldMask);
	_NewNode->setCore(newCore);	
	endEditCP(_NewNode,Node::CoreFieldMask);
	_Name = _FCType->getCName();
	_Name = "New "+_Name+" Node";
	setName(_NewNode,_Name);

	_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_HierarchyPanel->getApplicationPlayer()->getSelectedNode()),boost::any(_NewNode));
	
	_HasBeenDone = true;

}

std::string NewCommand::getCommandDescription(void) const
{
	std::string Description(_Name);
	
	return Description;
}

std::string NewCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void NewCommand::redo(void)
{
    Inherited::redo();

	if(_NewNode!=NullFC)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(boost::any(_HierarchyPanel->getApplicationPlayer()->getSelectedNode()),boost::any(_NewNode));
		subRefCP(_NewNode);
	}

}

void NewCommand::undo(void)
{
    Inherited::undo();

	if(_NewNode!=NullFC)
	{
		addRefCP(_NewNode);
		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(boost::any(_NewNode));
	}

}

const CommandType &NewCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

NewCommand::~NewCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NewCommand::operator =(const NewCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
		_HierarchyPanel = source._HierarchyPanel;
		_NewNode= source._NewNode;
		_FCType= source._FCType;
		_Name= source._Name;
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

