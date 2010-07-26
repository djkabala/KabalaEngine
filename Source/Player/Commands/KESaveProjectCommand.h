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

#ifndef _KESAVEPROJECT_COMMAND_H_
#define _KESAVEPROJECT_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>

OSG_BEGIN_NAMESPACE

class SaveProjectCommand;
typedef boost::shared_ptr<SaveProjectCommand> SaveProjectCommandPtr;

class KE_KABALAENGINE_DLLMAPPING SaveProjectCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef SaveProjectCommandPtr RefPtr;

	SaveProjectCommand(bool OpenSaveDialog = false);

	SaveProjectCommand(const SaveProjectCommand& source);

	void operator =(const SaveProjectCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;

    bool _OpenSaveDialog;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~SaveProjectCommand(void);
	
	static SaveProjectCommandPtr create(bool OpenSaveDialog = false);
};

OSG_END_NAMESPACE

#include "KESaveProjectCommand.inl"

#endif /* _KESAVEPROJECT_SCENE_BACKGROUNDCOMMAND_H_ */
