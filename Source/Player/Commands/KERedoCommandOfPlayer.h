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

#ifndef _KEREDOCOMMANDFORPLAYER_H_
#define _KEREDOCOMMANDFORPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Player/KEApplicationPlayer.h"

OSG_BEGIN_NAMESPACE

class RedoCommandOfPlayer;
typedef boost::intrusive_ptr<RedoCommandOfPlayer> RedoCommandOfPlayerPtr;

class KE_KABALAENGINELIB_DLLMAPPING RedoCommandOfPlayer: public Command
{
protected:
	typedef Command Inherited;
	typedef RedoCommandOfPlayerPtr Ptr;

	RedoCommandOfPlayer(ApplicationPlayerPtr ApplicationPlayer);

	RedoCommandOfPlayer(const RedoCommandOfPlayer& source);

	void operator =(const RedoCommandOfPlayer& source);

	static CommandType _Type;
	
	virtual void execute(void);

	ApplicationPlayerPtr _ApplicationPlayer;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RedoCommandOfPlayer(void);
	
	static RedoCommandOfPlayerPtr create(ApplicationPlayerPtr ApplicationPlayer);
};

OSG_END_NAMESPACE

#include "KERedoCommandOfPlayer.inl"

#endif /* _KEUNDOCOMMAND_H_ */
