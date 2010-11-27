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

#include "KECopyCommand.h"

#include <OpenSG/OSGNameAttachment.h>
#include "Player/KEApplicationPlayer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CopyCommand
A CopyCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType CopyCommand::_Type("CopyCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

CopyCommandPtr CopyCommand::create(ApplicationPlayer* const ApplicationPlayer, Node* const CopyNode)
{
	return RefPtr(new CopyCommand(ApplicationPlayer, CopyNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CopyCommand::execute(void)
{
	_ApplicationPlayer->setClonedNodeInCopyClipboard(_CopyNode);
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

