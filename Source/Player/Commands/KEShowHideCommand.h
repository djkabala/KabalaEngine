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

#ifndef _KESHOWHIDE_COMMAND_H_
#define _KESHOWHIDE_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGUndoableCommand.h>
#include <OpenSG/OSGNode.h>
#include <vector>

OSG_BEGIN_NAMESPACE

class ShowHideCommand;
typedef boost::intrusive_ptr<ShowHideCommand> ShowHideCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING ShowHideCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef ShowHideCommandPtr Ptr;

	ShowHideCommand(NodePtr SelectedNode, bool Show, bool Recursive);

	ShowHideCommand(const ShowHideCommand& source);

	void operator =(const ShowHideCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	NodePtr _SelectedNode;
	bool _Show;
	bool _Recursive;
	std::vector<std::pair<NodePtr, UInt32> > _ChangedNodes;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~ShowHideCommand(void);
	
	static ShowHideCommandPtr create(NodePtr SelectedNode, bool Show,bool Recursive);
};

OSG_END_NAMESPACE

#include "KEShowHideCommand.inl"

#endif /* _KEDELETE_SCENE_BACKGROUNDCOMMAND_H_ */
