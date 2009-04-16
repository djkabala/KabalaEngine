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

#ifndef _KEPLAYPROJECTCOMMAND_H_
#define _KEPLAYPROJECTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Application/KEMainApplication.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class PlayProjectCommand;
typedef boost::intrusive_ptr<PlayProjectCommand> PlayProjectCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING PlayProjectCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef PlayProjectCommandPtr Ptr;

	PlayProjectCommand(MainApplicationPtr TheMainApp);

	PlayProjectCommand(const PlayProjectCommand& source);

	void operator =(const PlayProjectCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	MainApplicationPtr _TheMainApp;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~PlayProjectCommand(void);
	
	static PlayProjectCommandPtr create(MainApplicationPtr TheMainApp);
};

KE_END_NAMESPACE

#include "KEPlayProjectCommand.inl"

#endif /* _KEPLAYPROJECTCOMMAND_H_ */
