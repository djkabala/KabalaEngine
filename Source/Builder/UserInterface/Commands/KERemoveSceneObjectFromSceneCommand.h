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

#ifndef _KEREMOVESCENEOBJECTFROMSCENECOMMAND_H_
#define _KEREMOVESCENEOBJECTFROMSCENECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>
#include "Project/Scene/KESceneFields.h"
#include "Project/SceneObject/KESceneObjectFields.h"

OSG_BEGIN_NAMESPACE

class RemoveSceneObjectFromSceneCommand;
typedef boost::shared_ptr<RemoveSceneObjectFromSceneCommand> RemoveSceneObjectFromSceneCommandPtr;

class KE_KABALAENGINE_DLLMAPPING RemoveSceneObjectFromSceneCommand: public UndoableCommand
{
private:
	RemoveSceneObjectFromSceneCommand(const RemoveSceneObjectFromSceneCommand& source);

	void operator =(const RemoveSceneObjectFromSceneCommand& source);

protected:
	typedef UndoableCommand Inherited;
	typedef RemoveSceneObjectFromSceneCommandPtr Ptr;

	RemoveSceneObjectFromSceneCommand(Scene* const RootScene,
                                      SceneObject* const RemoveSceneObject);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    SceneRecPtr _RootScene;
    SceneObjectRecPtr _RemovedSceneObject;
    NodeRecPtr  _PrevParentNode;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RemoveSceneObjectFromSceneCommand(void);
	
	static RemoveSceneObjectFromSceneCommandPtr create(Scene* const RootScene,
                                                       SceneObject* const RemoveSceneObject);
};

OSG_END_NAMESPACE

#include "KERemoveSceneObjectFromSceneCommand.inl"

#endif /* _KEREMOVESCENEOBJECTFROMSCENECOMMAND_H_ */
