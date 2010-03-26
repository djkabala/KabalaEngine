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

#include "KECopyCommand.h"

#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CopyCommand
A CopyCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType CopyCommand::_Type("CopyCommand", "Command");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

CopyCommandPtr CopyCommand::create(ApplicationPlayerPtr ApplicationPlayer)
{
	return Ptr(new CopyCommand(ApplicationPlayer));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CopyCommand::execute(void)
{
	_ApplicationPlayer->currentAction = COPY;
	_ApplicationPlayer->clonedNodeInCopyClipboard = osg::deepCloneTree(_ApplicationPlayer->SelectedNode);
	std::string name=getName(_ApplicationPlayer->SelectedNode);
	name+=" copy";
	setName(_ApplicationPlayer->clonedNodeInCopyClipboard,name);
}

std::string CopyCommand::getCommandDescription(void) const
{
	return std::string("Copy ");
}

std::string CopyCommand::getPresentationName(void) const
{
	return getCommandDescription();
}


const CommandType &CopyCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CopyCommand::~CopyCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CopyCommand::operator =(const CopyCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
		_ApplicationPlayer = source._ApplicationPlayer;

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

