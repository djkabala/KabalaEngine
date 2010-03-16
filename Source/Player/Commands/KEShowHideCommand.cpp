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

ShowHideCommandPtr ShowHideCommand::create(HierarchyPanelPtr HierarchyPanel,ApplicationPlayerPtr ApplicationPlayer)
{
	return Ptr(new ShowHideCommand(HierarchyPanel,ApplicationPlayer));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ShowHideCommand::execute(void)
{
//	std::cout<<"changing the travmask"<<std::endl;
	_SelectedNode = _HierarchyPanel->_TheTreeSelectionListener._SelectedNode;
	maskval = _SelectedNode->getTravMask();
	if(!maskval)
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
		std::string caption(_ApplicationPlayer->ShowHideItem->getText());
		beginEditCP(_ApplicationPlayer->ShowHideItem);
		if(caption=="Show")
			_ApplicationPlayer->ShowHideItem->setText("Hide");
		else
			_ApplicationPlayer->ShowHideItem->setText("Show");
		endEditCP(_ApplicationPlayer->ShowHideItem);
}

std::string ShowHideCommand::getCommandDescription(void) const
{
	std::string caption;
	if(!maskval)caption = "Show";
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
		std::cout<<"trying to redo "<<std::endl;
		UInt32 maskval = _SelectedNode->getTravMask();
		if(!maskval)
		{
			_SelectedNode->setTravMask(UInt32(-1));
		}
		else	
		{
			_SelectedNode->setTravMask(0);
		}
		invertShowHideCaption();
	}
    //_TheModel->removeBackground(_TheIndex);
}

void ShowHideCommand::undo(void)
{
    if(_SelectedNode != NullFC)
	{
		Inherited::undo();
		std::cout<<"trying to redo "<<std::endl;
		UInt32 maskval = _SelectedNode->getTravMask();
		if(!maskval)
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
		_HierarchyPanel = source._HierarchyPanel;
		_ApplicationPlayer = source._ApplicationPlayer;
		_SelectedNode = source._SelectedNode;
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

