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

#ifndef _KEEXPORTMODEL_COMMAND_H_
#define _KEEXPORTMODEL_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>
#include <OpenSG/OSGNodeFields.h>

OSG_BEGIN_NAMESPACE

class ExportModelCommand;
typedef boost::shared_ptr<ExportModelCommand> ExportModelCommandPtr;

class KE_KABALAENGINE_DLLMAPPING ExportModelCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef ExportModelCommandPtr RefPtr;

	ExportModelCommand(Node* const ExportNode);

	ExportModelCommand(const ExportModelCommand& source);

	void operator =(const ExportModelCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;

	NodeRefPtr _ExportNode;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~ExportModelCommand(void);
	
	static ExportModelCommandPtr create(Node* const ExportNode);
};

OSG_END_NAMESPACE

#include "KEExportModelCommand.inl"

#endif /* _KEEXPORTMODEL_SCENE_BACKGROUNDCOMMAND_H_ */
