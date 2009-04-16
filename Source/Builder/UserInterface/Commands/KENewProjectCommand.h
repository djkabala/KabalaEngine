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

#ifndef _KENEWPROJECTCOMMAND_H_
#define _KENEWPROJECTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Builder/KEApplicationBuilder.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class NewProjectCommand;
typedef boost::intrusive_ptr<NewProjectCommand> NewProjectCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING NewProjectCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef NewProjectCommandPtr Ptr;

	NewProjectCommand(ApplicationBuilderPtr TheApplicationBuilder);

	NewProjectCommand(const NewProjectCommand& source);

	void operator =(const NewProjectCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	ApplicationBuilderPtr _TheApplicationBuilder;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~NewProjectCommand(void);
	
	static NewProjectCommandPtr create(ApplicationBuilderPtr TheApplicationBuilder);
};

KE_END_NAMESPACE

#include "KENewProjectCommand.inl"

#endif /* _KENEWPROJECTCOMMAND_H_ */
