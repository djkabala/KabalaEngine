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

#ifndef _KEREMOVESCENECOMMAND_H_
#define _KEREMOVESCENECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>
#include "Project/Scene/KESceneFields.h"

OSG_BEGIN_NAMESPACE

class RemoveSceneCommand;
typedef boost::shared_ptr<RemoveSceneCommand> RemoveSceneCommandPtr;

class KE_KABALAENGINE_DLLMAPPING RemoveSceneCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef RemoveSceneCommandPtr Ptr;

	RemoveSceneCommand(Scene* const SceneToRemove);

	RemoveSceneCommand(const RemoveSceneCommand& source);

	void operator =(const RemoveSceneCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    SceneRecPtr _RemovedScene;
    UInt32 _RemovedIndex;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RemoveSceneCommand(void);
	
	static RemoveSceneCommandPtr create(Scene* const SceneToRemove);
};

OSG_END_NAMESPACE

#include "KERemoveSceneCommand.inl"

#endif /* _KEREMOVESCENECOMMAND_H_ */
