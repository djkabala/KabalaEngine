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

#ifndef _KESAVEPROJECTCOMMAND_H_
#define _KESAVEPROJECTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>
#include "Builder/KEApplicationBuilderFields.h"

OSG_BEGIN_NAMESPACE

class SaveProjectCommand;
typedef boost::shared_ptr<SaveProjectCommand> SaveProjectCommandPtr;

class KE_KABALAENGINE_DLLMAPPING SaveProjectCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef SaveProjectCommandPtr Ptr;

	SaveProjectCommand(ApplicationBuilder* const TheApplicationBuilder);

	SaveProjectCommand(const SaveProjectCommand& source);

	void operator =(const SaveProjectCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	ApplicationBuilder* _TheApplicationBuilder;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~SaveProjectCommand(void);
	
	static SaveProjectCommandPtr create(ApplicationBuilder* const TheApplicationBuilder);
};

OSG_END_NAMESPACE

#include "KESaveProjectCommand.inl"

#endif /* _KESAVEPROJECTCOMMAND_H_ */
