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

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Application/KEMainApplication.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class QuitAppCommand;
typedef boost::intrusive_ptr<QuitAppCommand> QuitAppCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING QuitAppCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef QuitAppCommandPtr Ptr;

	QuitAppCommand(MainApplicationPtr TheMainApp);

	QuitAppCommand(const QuitAppCommand& source);

	void operator =(const QuitAppCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	MainApplicationPtr _TheMainApp;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~QuitAppCommand(void);
	
	static QuitAppCommandPtr create(MainApplicationPtr TheMainApp);
};

KE_END_NAMESPACE

#include "KEQuitAppCommand.inl"

#endif /* _KEQUITAPPCOMMAND_H_ */
