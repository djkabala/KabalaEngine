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

#ifndef _KEDELETE_COMMAND_H_
#define _KEDELETE_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGUndoableCommand.h>

#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"

OSG_BEGIN_NAMESPACE

class DeleteCommand;
typedef boost::intrusive_ptr<DeleteCommand> DeleteCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING DeleteCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef DeleteCommandPtr Ptr;

    DeleteCommand(ApplicationPlayerPtr ApplicationPlayer,
                  HierarchyPanelPtr HierarchyPanel,
                  NodePtr DeleteNode);

	DeleteCommand(const DeleteCommand& source);

	void operator =(const DeleteCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	ApplicationPlayerPtr _ApplicationPlayer;
	HierarchyPanelPtr _HierarchyPanel;
	NodePtr _DeletedNode;
	NodePtr _Parent;
	UInt32 _IndexOfDeletion;
	

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~DeleteCommand(void);
	
    static DeleteCommandPtr create(ApplicationPlayerPtr ApplicationPlayer,
                                   HierarchyPanelPtr HierarchyPanel,
                                   NodePtr DeleteNode);
};

OSG_END_NAMESPACE

#include "KEDeleteCommand.inl"

#endif /* _KEDELETE_SCENE_BACKGROUNDCOMMAND_H_ */
