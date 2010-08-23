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

#ifndef _KECUT_COMMAND_H_
#define _KECUT_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>

#include "Player/KEApplicationPlayer.h"
#include <OpenSG/OSGSceneGraphTreeModel.h>

OSG_BEGIN_NAMESPACE

class CutCommand;
typedef boost::shared_ptr<CutCommand> CutCommandPtr;

class KE_KABALAENGINE_DLLMAPPING CutCommand: public UndoableCommand
{
protected:
	enum cActions{NONE,CUT,COPY};

	typedef UndoableCommand Inherited;
	typedef CutCommandPtr RefPtr;

    CutCommand(ApplicationPlayer* const ApplicationPlayer,
               SceneGraphTreeModel* const SceneGraphTreeModel,
               Node* const CutNode);

	CutCommand(const CutCommand& source);

	void operator =(const CutCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);


	ApplicationPlayerRefPtr _ApplicationPlayer;  
	SceneGraphTreeModelRefPtr _SceneGraphTreeModel;
	
	NodeRefPtr _CutNode;
	NodeRefPtr _Parent;
	UInt32 _IndexOfCut;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CutCommand(void);
	
    static CutCommandPtr create(ApplicationPlayer* const ApplicationPlayer,
                                SceneGraphTreeModel* const SceneGraphTreeModel,
                                Node* const CutNode);
};

OSG_END_NAMESPACE

#include "KECutCommand.inl"

#endif /* _KEDELETE_SCENE_BACKGROUNDCOMMAND_H_ */
