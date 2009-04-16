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

#ifndef _KESAVEPROJECTASCOMMAND_H_
#define _KESAVEPROJECTASCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Builder/KEApplicationBuilder.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class SaveProjectAsCommand;
typedef boost::intrusive_ptr<SaveProjectAsCommand> SaveProjectAsCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING SaveProjectAsCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef SaveProjectAsCommandPtr Ptr;

	SaveProjectAsCommand(ApplicationBuilderPtr TheApplicationBuilder);

	SaveProjectAsCommand(const SaveProjectAsCommand& source);

	void operator =(const SaveProjectAsCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	ApplicationBuilderPtr _TheApplicationBuilder;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~SaveProjectAsCommand(void);
	
	static SaveProjectAsCommandPtr create(ApplicationBuilderPtr TheApplicationBuilder);
};

KE_END_NAMESPACE

#include "KESaveProjectAsCommand.inl"

#endif /* _KESAVEPROJECTASCOMMAND_H_ */
