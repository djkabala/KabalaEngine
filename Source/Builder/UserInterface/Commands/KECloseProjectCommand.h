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

#ifndef _KECLOSEPROJECTCOMMAND_H_
#define _KECLOSEPROJECTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Builder/KEApplicationBuilder.h"

OSG_BEGIN_NAMESPACE

class CloseProjectCommand;
typedef boost::intrusive_ptr<CloseProjectCommand> CloseProjectCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING CloseProjectCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef CloseProjectCommandPtr Ptr;

	CloseProjectCommand(ApplicationBuilderPtr TheApplicationBuilder);

	CloseProjectCommand(const CloseProjectCommand& source);

	void operator =(const CloseProjectCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	ApplicationBuilderPtr _TheApplicationBuilder;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CloseProjectCommand(void);
	
	static CloseProjectCommandPtr create(ApplicationBuilderPtr TheApplicationBuilder);
};

OSG_END_NAMESPACE

#include "KECloseProjectCommand.inl"

#endif /* _KECLOSEPROJECTCOMMAND_H_ */
