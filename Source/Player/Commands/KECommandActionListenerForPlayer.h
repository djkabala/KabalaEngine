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

#ifndef _KECOMMANDACTIONLISTENERFORPLAYER_H_
#define _KECOMMANDACTIONLISTENERFORPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include <OpenSG/UserInterface/OSGCommandManager.h>
#include <OpenSG/UserInterface/OSGActionListener.h>

OSG_BEGIN_NAMESPACE

class KE_KABALAENGINELIB_DLLMAPPING CommandActionListenerForPlayer : public ActionListener
{
protected:
	typedef ActionListener Inherited;

	CommandPtr _TheCommand;
	CommandManagerPtr _TheCommandManager;
public:

	virtual void actionPerformed(const ActionEventPtr e);

	virtual ~CommandActionListenerForPlayer(void);

	CommandActionListenerForPlayer(CommandPtr TheCommand, CommandManagerPtr TheCommandManager);

	CommandActionListenerForPlayer(const CommandActionListenerForPlayer& source);

	void operator =(const CommandActionListenerForPlayer& source);
};

OSG_END_NAMESPACE

#include "KECommandActionListenerForPlayer.inl"

#endif /* _KECOMMANDACTIONLISTENER_H_ */
