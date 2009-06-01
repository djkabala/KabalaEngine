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

#ifndef _KECREATE_SCENE_BACKGROUNDCOMMAND_H_
#define _KECREATE_SCENE_BACKGROUNDCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGUndoableCommand.h>
#include "KESceneBackgroundsComboBoxModel.h"

OSG_BEGIN_NAMESPACE

class CreateSceneBackgroundCommand;
typedef boost::intrusive_ptr<CreateSceneBackgroundCommand> CreateSceneBackgroundCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING CreateSceneBackgroundCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef CreateSceneBackgroundCommandPtr Ptr;

	CreateSceneBackgroundCommand(SceneBackgroundsComboBoxModelPtr TheModel,FieldContainerType* FCType);

	CreateSceneBackgroundCommand(const CreateSceneBackgroundCommand& source);

	void operator =(const CreateSceneBackgroundCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	SceneBackgroundsComboBoxModelPtr _TheModel;
    FieldContainerType* _FCType;
    Int32 _CreatedIndex;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CreateSceneBackgroundCommand(void);
	
	static CreateSceneBackgroundCommandPtr create(SceneBackgroundsComboBoxModelPtr TheModel,FieldContainerType* FCType);
};

OSG_END_NAMESPACE

#include "KECreateSceneBackgroundCommand.inl"

#endif /* _KECREATE_SCENE_BACKGROUNDCOMMAND_H_ */
