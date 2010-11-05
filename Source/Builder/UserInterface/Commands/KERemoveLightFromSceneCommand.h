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

#ifndef _KEREMOVELIGHTFROMSCENECOMMAND_H_
#define _KEREMOVELIGHTFROMSCENECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>
#include <OpenSG/OSGNodeFields.h>
#include "Project/Scene/KESceneFields.h"

OSG_BEGIN_NAMESPACE

class RemoveLightFromSceneCommand;
typedef boost::shared_ptr<RemoveLightFromSceneCommand> RemoveLightFromSceneCommandPtr;

class KE_KABALAENGINE_DLLMAPPING RemoveLightFromSceneCommand: public UndoableCommand
{
private:
	RemoveLightFromSceneCommand(const RemoveLightFromSceneCommand& source);

	void operator =(const RemoveLightFromSceneCommand& source);

protected:
	typedef UndoableCommand Inherited;
	typedef RemoveLightFromSceneCommandPtr Ptr;

	RemoveLightFromSceneCommand(Scene* const RootScene,
                                Node* const  RemoveLightNode);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    SceneRecPtr _RootScene;
    NodeRecPtr _RemovedLightNode,
               _RemovedLightBeaconNode;

    NodeRecPtr _LightParent,
               _LightBeaconParent;

    UInt32 _RemoveLightBeaconNodeIndex,
           _RemoveLightNodeIndex;

    std::vector<NodeRecPtr> _FormerChildren;
public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RemoveLightFromSceneCommand(void);
	
	static RemoveLightFromSceneCommandPtr create(Scene* const RootScene,
                                                 Node* const  RemoveLightNode);
};

OSG_END_NAMESPACE

#include "KERemoveLightFromSceneCommand.inl"

#endif /* _KEREMOVELIGHTFROMSCENECOMMAND_H_ */
