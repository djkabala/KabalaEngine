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

#ifndef _KEPASTE_COMMAND_H_
#define _KEPASTE_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGUndoableCommand.h>


#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"

OSG_BEGIN_NAMESPACE

class PasteCommand;
typedef boost::intrusive_ptr<PasteCommand> PasteCommandPtr;

class KE_KABALAENGINELIB_DLLMAPPING PasteCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef PasteCommandPtr Ptr;

	enum cActions{NONE,CUT,COPY};

	PasteCommand(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel);

	PasteCommand(const PasteCommand& source);

	void operator =(const PasteCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	ApplicationPlayerPtr _ApplicationPlayer;
	HierarchyPanelPtr _HierarchyPanel;

	UInt32 _currentAction;
	NodePtr _nodeInCutClipboard;
	NodePtr _clonedNodeInCopyClipboard;
	NodePtr _SelectedNode;


public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~PasteCommand(void);
	
	static PasteCommandPtr create(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel);
};

OSG_END_NAMESPACE

#include "KEPasteCommand.inl"

#endif /* _KEDELETE_SCENE_BACKGROUNDCOMMAND_H_ */
