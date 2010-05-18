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

#include "KERedoCommandOfPlayer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::RedoCommandOfPlayer
A RedoCommandOfPlayer. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RedoCommandOfPlayer::_Type("RedoCommandOfPlayer", "Command");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RedoCommandOfPlayerRefPtr RedoCommandOfPlayer::create(ApplicationPlayerRefPtr ApplicationPlayer)
{
	return RefPtr(new RedoCommandOfPlayer(ApplicationPlayer));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RedoCommandOfPlayer::execute(void)
{
	_ApplicationPlayer->getUndoManager()->redo();
}

std::string RedoCommandOfPlayer::getCommandDescription(void) const
{
	return std::string("Redo");
}

const CommandType &RedoCommandOfPlayer::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RedoCommandOfPlayer::~RedoCommandOfPlayer(void)
{
}

/*----------------------------- class specific ----------------------------*/


