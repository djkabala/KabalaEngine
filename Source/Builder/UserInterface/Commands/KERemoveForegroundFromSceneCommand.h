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

#ifndef _KEREMOVEFOREGROUNDFROMSCENECOMMAND_H_
#define _KEREMOVEFOREGROUNDFROMSCENECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>
#include <OpenSG/OSGForegroundFields.h>
#include "Project/Scene/KESceneFields.h"

OSG_BEGIN_NAMESPACE

class RemoveForegroundFromSceneCommand;
typedef boost::shared_ptr<RemoveForegroundFromSceneCommand> RemoveForegroundFromSceneCommandPtr;

class KE_KABALAENGINE_DLLMAPPING RemoveForegroundFromSceneCommand: public UndoableCommand
{
private:
	RemoveForegroundFromSceneCommand(const RemoveForegroundFromSceneCommand& source);

	void operator =(const RemoveForegroundFromSceneCommand& source);

protected:
	typedef UndoableCommand Inherited;
	typedef RemoveForegroundFromSceneCommandPtr Ptr;

	RemoveForegroundFromSceneCommand(Scene* RootScene,
                                     Foreground* RemoveForeground);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    SceneRecPtr _RootScene;
    ForegroundRecPtr _RemovedForeground;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RemoveForegroundFromSceneCommand(void);
	
	static RemoveForegroundFromSceneCommandPtr create(Scene* RootScene,
                                                      Foreground* RemoveForeground);
};

OSG_END_NAMESPACE

#include "KERemoveForegroundFromSceneCommand.inl"

#endif /* _KEREMOVEFOREGROUNDFROMSCENECOMMAND_H_ */
