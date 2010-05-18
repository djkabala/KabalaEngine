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

#ifndef _KECOMMANDACTIONLISTENERFORPLAYER_H_
#define _KECOMMANDACTIONLISTENERFORPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>
#include <OpenSG/OSGCommandManager.h>
#include <OpenSG/OSGActionListener.h>

OSG_BEGIN_NAMESPACE

class KE_KABALAENGINE_DLLMAPPING CommandActionListenerForPlayer : public ActionListener
{
protected:
	typedef ActionListener Inherited;

	CommandPtr _TheCommand;
	CommandManagerPtr _TheCommandManager;
public:

	virtual void actionPerformed(const ActionEventUnrecPtr e);

	virtual ~CommandActionListenerForPlayer(void);

	CommandActionListenerForPlayer(void);

	CommandActionListenerForPlayer(CommandPtr TheCommand, CommandManagerPtr TheCommandManager);

	CommandActionListenerForPlayer(const CommandActionListenerForPlayer& source);

	void operator =(const CommandActionListenerForPlayer& source);
};

OSG_END_NAMESPACE

#include "KECommandActionListenerForPlayer.inl"

#endif /* _KECOMMANDACTIONLISTENER_H_ */
