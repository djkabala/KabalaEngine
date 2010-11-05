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

#ifndef _KEADDSCENEOBJECTTOSCENECOMMAND_H_
#define _KEADDSCENEOBJECTTOSCENECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>
#include "Project/Scene/KESceneFields.h"
#include "Project/SceneObject/KESceneObjectFields.h"

OSG_BEGIN_NAMESPACE

class AddSceneObjectToSceneCommand;
typedef boost::shared_ptr<AddSceneObjectToSceneCommand> AddSceneObjectToSceneCommandPtr;

class KE_KABALAENGINE_DLLMAPPING AddSceneObjectToSceneCommand: public UndoableCommand
{
private:
	AddSceneObjectToSceneCommand(const AddSceneObjectToSceneCommand& source);

	void operator =(const AddSceneObjectToSceneCommand& source);

protected:
	typedef UndoableCommand Inherited;
	typedef AddSceneObjectToSceneCommandPtr Ptr;

	AddSceneObjectToSceneCommand(Scene* const RootScene);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    SceneRecPtr _RootScene;
    SceneObjectRecPtr _CreatedSceneObject;
    NodeRecPtr _NodeAddedTo;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~AddSceneObjectToSceneCommand(void);
	
	static AddSceneObjectToSceneCommandPtr create(Scene* const RootScene);
};

OSG_END_NAMESPACE

#include "KEAddSceneObjectToSceneCommand.inl"

#endif /* _KEADDSCENEOBJECTTOSCENECOMMAND_H_ */
