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

#include "KENewCommand.h"

#include <OpenSG/OSGNameAttachment.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NewCommand
A NewCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType NewCommand::_Type("NewCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

NewCommandPtr NewCommand::create(HierarchyPanelRefPtr HierarchyPanel,FieldContainerType* FCType)
{
	return RefPtr(new NewCommand(HierarchyPanel,FCType));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void NewCommand::execute(void)
{

	NodeCoreRefPtr newCore = dynamic_pointer_cast<NodeCore>(FieldContainerFactory::the()->createContainer(_FCType->getCName()));

	_NewNode = Node::create();
	_NewNode->setCore(newCore);	
	_Name = _FCType->getCName();
	_Name = "New "+_Name+" Node";
	setName(_NewNode,_Name);

    _NodeToAddTo = _HierarchyPanel->getApplicationPlayer()->getSelectedNode();
    if(_NodeToAddTo == NULL)
    {
        _NodeToAddTo =  _HierarchyPanel->getSceneGraphTreeModel()->getRootNode();
    }
	if(_NodeToAddTo!=NULL)
	{
	    _HierarchyPanel->getSceneGraphTreeModel()->addNode(_NodeToAddTo,_NewNode);
    }
	
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

	if(_NewNode!=NULL)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(_NodeToAddTo,_NewNode);
	}

}

void NewCommand::undo(void)
{
    Inherited::undo();

	if(_NewNode!=NULL)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(_NewNode);
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

