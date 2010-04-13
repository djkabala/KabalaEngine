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

#include "KEShowHideCommand.h"

#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShowHideCommand
A ShowHideCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType ShowHideCommand::_Type("ShowHideCommand", "UndoableCommand");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

ShowHideCommandPtr ShowHideCommand::create(NodePtr _SelectedNode,MenuItemPtr _ShowHideItem)
{
	return Ptr(new ShowHideCommand(_SelectedNode,_ShowHideItem));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ShowHideCommand::execute(void)
{
	_Maskval = _SelectedNode->getTravMask();
	if(!_Maskval)
	{
		_SelectedNode->setTravMask(UInt32(-1));
	}
	else	
	{
		_SelectedNode->setTravMask(0);
	}
	invertShowHideCaption();

	_HasBeenDone = true;

}

void ShowHideCommand::invertShowHideCaption()
{
		std::string caption(_ShowHideItem->getText());
		beginEditCP(_ShowHideItem);
		if(caption=="Show")
			_ShowHideItem->setText("Hide");
		else
			_ShowHideItem->setText("Show");
		endEditCP(_ShowHideItem);
}

std::string ShowHideCommand::getCommandDescription(void) const
{
	std::string caption;
	if(!_Maskval)caption = "Show";
	else		caption = "Hide";
	return		caption;
}

std::string ShowHideCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void ShowHideCommand::redo(void)
{
	if(_SelectedNode != NullFC)
	{
		Inherited::redo();
		UInt32 _Maskval = _SelectedNode->getTravMask();
		if(!_Maskval)
		{
			_SelectedNode->setTravMask(UInt32(-1));
		}
		else	
		{
			_SelectedNode->setTravMask(0);
		}
		invertShowHideCaption();
	}
}

void ShowHideCommand::undo(void)
{
    if(_SelectedNode != NullFC)
	{
		Inherited::undo();
		UInt32 _Maskval = _SelectedNode->getTravMask();
		if(!_Maskval)
		{
			_SelectedNode->setTravMask(UInt32(-1));
		}
		else	
		{
			_SelectedNode->setTravMask(0);
		}
		invertShowHideCaption();
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
		_ShowHideItem = source._ShowHideItem;
		_SelectedNode = source._SelectedNode;
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

