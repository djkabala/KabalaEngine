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

#include "KEUndoCommandOfPlayer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::UndoCommandOfPlayer
A UndoCommandOfPlayer. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType UndoCommandOfPlayer::_Type("UndoCommandOfPlayer", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

UndoCommandOfPlayerRefPtr UndoCommandOfPlayer::create(ApplicationPlayerRefPtr ApplicationPlayer)
{
	return RefPtr(new UndoCommandOfPlayer(ApplicationPlayer));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UndoCommandOfPlayer::execute(void)
{
	_ApplicationPlayer->getUndoManager()->undo();
}

std::string UndoCommandOfPlayer::getCommandDescription(void) const
{
	return std::string("Undo");
}

const CommandType &UndoCommandOfPlayer::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UndoCommandOfPlayer::~UndoCommandOfPlayer(void)
{
}

/*----------------------------- class specific ----------------------------*/


