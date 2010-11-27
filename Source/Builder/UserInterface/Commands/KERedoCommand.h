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

#ifndef _KEREDOCOMMAND_H_
#define _KEREDOCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>
#include <OpenSG/OSGUndoManager.h>

OSG_BEGIN_NAMESPACE

class RedoCommand;
typedef boost::shared_ptr<RedoCommand> RedoCommandPtr;

class KE_KABALAENGINE_DLLMAPPING RedoCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef RedoCommandPtr Ptr;

	RedoCommand(UndoManagerPtr TheUndoManager);

	RedoCommand(const RedoCommand& source);

	void operator =(const RedoCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	UndoManagerPtr _UndoManager;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RedoCommand(void);
	
	static RedoCommandPtr create(UndoManagerPtr TheUndoManager);
};

OSG_END_NAMESPACE

#include "KERedoCommand.inl"

#endif /* _KEREDOCOMMAND_H_ */
