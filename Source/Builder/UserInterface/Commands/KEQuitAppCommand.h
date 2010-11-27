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

#ifndef _KEQUITAPPCOMMAND_H_
#define _KEQUITAPPCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>

OSG_BEGIN_NAMESPACE

class QuitAppCommand;
typedef boost::shared_ptr<QuitAppCommand> QuitAppCommandPtr;

class KE_KABALAENGINE_DLLMAPPING QuitAppCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef QuitAppCommandPtr Ptr;

	QuitAppCommand(void);

	QuitAppCommand(const QuitAppCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~QuitAppCommand(void);
	
	static QuitAppCommandPtr create(void);
};

OSG_END_NAMESPACE

#include "KEQuitAppCommand.inl"

#endif /* _KEQUITAPPCOMMAND_H_ */
