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

#ifndef _KECOPY_COMMAND_H_
#define _KECOPY_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGCommand.h>
#include "Player/KEApplicationPlayer.h"

OSG_BEGIN_NAMESPACE

class CopyCommand;
typedef boost::intrusive_ptr<CopyCommand> CopyCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING CopyCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef CopyCommandPtr Ptr;

	enum cActions{NONE,CUT,COPY};

	CopyCommand(ApplicationPlayerPtr ApplicationPlayer);

	CopyCommand(const CopyCommand& source);

	void operator =(const CopyCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

	virtual std::string getPresentationName(void) const;

	ApplicationPlayerPtr _ApplicationPlayer;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CopyCommand(void);
	
	static CopyCommandPtr create(ApplicationPlayerPtr ApplicationPlayer);
};

OSG_END_NAMESPACE

#include "KECopyCommand.inl"

#endif /* _KEDELETE_SCENE_BACKGROUNDCOMMAND_H_ */
