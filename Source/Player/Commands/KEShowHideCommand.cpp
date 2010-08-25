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

#include "KEShowHideCommand.h"
#include "KEUtils.h"

#include <OpenSG/OSGNameAttachment.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ShowHideCommand
A ShowHideCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType ShowHideCommand::_Type("ShowHideCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

ShowHideCommandPtr ShowHideCommand::create(Node* const SelectedNode, bool Show, bool Recursive)
{
	return RefPtr(new ShowHideCommand(SelectedNode,Show,Recursive));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ShowHideCommand::execute(void)
{
    _ChangedNodes.clear();
    if(_Recursive)
    {
	    recurseSetTravMasRecord(_SelectedNode, (_Show ? UInt32(-1) : 0), _ChangedNodes);
    }
    else if(_SelectedNode->getTravMask() != (_Show ? UInt32(-1) : 0))
    {
        _ChangedNodes.push_back(std::pair<NodeRefPtr, UInt32>(_SelectedNode, _SelectedNode->getTravMask()));
        _SelectedNode->setTravMask((_Show ? UInt32(-1) : 0));
    }
    else
    {
        //Insignificant change
    }

	_HasBeenDone = true;

}

std::string ShowHideCommand::getCommandDescription(void) const
{
	std::string caption;
	if(_Recursive)
    {
        caption += "Recursive ";
    }

	if(_Show)
    {
        caption += "Show";
    }
	else
    {
        caption += "Hide";
    }

	return caption;
}

std::string ShowHideCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void ShowHideCommand::redo(void)
{
    Inherited::redo();
    execute();
}

void ShowHideCommand::undo(void)
{
    Inherited::undo();
    for(UInt32 i = 0; i < _ChangedNodes.size(); ++i)
    {
            _ChangedNodes[i].first->setTravMask(_ChangedNodes[i].second);
    }
}

const CommandType &ShowHideCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShowHideCommand::~ShowHideCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShowHideCommand::operator =(const ShowHideCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
		_SelectedNode = source._SelectedNode;
		_Recursive = source._Recursive;
		_Show = source._Show;
    }
}

