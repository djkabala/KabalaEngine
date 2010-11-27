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

#ifndef _KECREDITSKABALAENGINECOMMAND_H_
#define _KECREDITSKABALAENGINECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>
#include "Builder/KEApplicationBuilderFields.h"

OSG_BEGIN_NAMESPACE

class OpenCreditsCommand;
typedef boost::shared_ptr<OpenCreditsCommand> OpenCreditsCommandPtr;

class KE_KABALAENGINE_DLLMAPPING OpenCreditsCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef OpenCreditsCommandPtr Ptr;

	OpenCreditsCommand(void);

	OpenCreditsCommand(const OpenCreditsCommand& source);

	void operator =(const OpenCreditsCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~OpenCreditsCommand(void);
	
	static OpenCreditsCommandPtr create(void);
};

OSG_END_NAMESPACE

#include "KEOpenCreditsCommand.inl"

#endif /* _KECREDITSKABALAENGINECOMMAND_H_ */
