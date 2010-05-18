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

#ifndef _KECOPY_COMMAND_H_
#define _KECOPY_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>
#include "Player/KEApplicationPlayer.h"

OSG_BEGIN_NAMESPACE

class CopyCommand;
typedef boost::shared_ptr<CopyCommand> CopyCommandPtr;

class KE_KABALAENGINE_DLLMAPPING CopyCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef CopyCommandPtr RefPtr;

	enum cActions{NONE,CUT,COPY};

	CopyCommand(ApplicationPlayerRefPtr ApplicationPlayer, NodeRefPtr CopyNode);

	CopyCommand(const CopyCommand& source);

	void operator =(const CopyCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	virtual std::string getPresentationName(void) const;

	ApplicationPlayerRefPtr _ApplicationPlayer;
    NodeRefPtr _CopyNode;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CopyCommand(void);
	
	static CopyCommandPtr create(ApplicationPlayerRefPtr ApplicationPlayer, NodeRefPtr CopyNode);
};

OSG_END_NAMESPACE

#include "KECopyCommand.inl"

#endif /* _KEDELETE_SCENE_BACKGROUNDCOMMAND_H_ */

