/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
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

#ifndef _KEUNDOCOMMANDFORPLAYER_H_
#define _KEUNDOCOMMANDFORPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Player/KEApplicationPlayer.h"

OSG_BEGIN_NAMESPACE

class UndoCommandOfPlayer;
typedef boost::intrusive_ptr<UndoCommandOfPlayer> UndoCommandOfPlayerPtr;

class KE_KABALAENGINELIB_DLLMAPPING UndoCommandOfPlayer: public Command
{
protected:
	typedef Command Inherited;
	typedef UndoCommandOfPlayerPtr Ptr;

	UndoCommandOfPlayer(ApplicationPlayerPtr ApplicationPlayer);

	UndoCommandOfPlayer(const UndoCommandOfPlayer& source);

	void operator =(const UndoCommandOfPlayer& source);

	static CommandType _Type;
	
	virtual void execute(void);

	ApplicationPlayerPtr _ApplicationPlayer;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~UndoCommandOfPlayer(void);
	
	static UndoCommandOfPlayerPtr create(ApplicationPlayerPtr ApplicationPlayer);
};

OSG_END_NAMESPACE

#include "KEUndoCommandOfPlayer.inl"

#endif /* _KEUNDOCOMMAND_H_ */
