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

#ifndef _KERENAME_SCENE_BACKGROUNDCOMMAND_H_
#define _KERENAME_SCENE_BACKGROUNDCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGUndoableCommand.h>
#include "KESceneBackgroundsComboBoxModel.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class RenameSceneBackgroundCommand;
typedef boost::intrusive_ptr<RenameSceneBackgroundCommand> RenameSceneBackgroundCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING RenameSceneBackgroundCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef RenameSceneBackgroundCommandPtr Ptr;

	RenameSceneBackgroundCommand(SceneBackgroundsComboBoxModelPtr TheModel,UInt32 Index, std::string NewName);

	RenameSceneBackgroundCommand(const RenameSceneBackgroundCommand& source);

	void operator =(const RenameSceneBackgroundCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);
	virtual bool isSignificant(void) const;
    
	//This UndoableEdit should absorb anEdit if it can.
	virtual bool addEdit(const UndoableEditPtr anEdit);

	SceneBackgroundsComboBoxModelPtr _TheModel;
    UInt32 _Index;
    std::string _NewName;
	std::string _PreviousName;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RenameSceneBackgroundCommand(void);
	
	static RenameSceneBackgroundCommandPtr create(SceneBackgroundsComboBoxModelPtr TheModel,UInt32 Index, std::string NewName);
};

KE_END_NAMESPACE

#include "KERenameSceneBackgroundCommand.inl"

#endif /* _KERENAME_SCENE_BACKGROUNDCOMMAND_H_ */
