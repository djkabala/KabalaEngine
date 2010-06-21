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

#ifndef _KEIMPORTMODEL_COMMAND_H_
#define _KEIMPORTMODEL_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGUndoableCommand.h>

#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"

OSG_BEGIN_NAMESPACE

class ImportModelCommand;
typedef boost::shared_ptr<ImportModelCommand> ImportModelCommandPtr;

class KE_KABALAENGINE_DLLMAPPING ImportModelCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef ImportModelCommandPtr RefPtr;

	ImportModelCommand(HierarchyPanelRefPtr HierarchyPanel,NodeUnrecPtr NodeToAddTo);

	ImportModelCommand(const ImportModelCommand& source);

	void operator =(const ImportModelCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	HierarchyPanelRefPtr _HierarchyPanel;
	NodeRefPtr _NewNode;
    NodeUnrecPtr _NodeToAddTo;


public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~ImportModelCommand(void);
	
	static ImportModelCommandPtr create(HierarchyPanelRefPtr HierarchyPanel,NodeUnrecPtr NodeToAddTo);
};

OSG_END_NAMESPACE

#include "KEImportModelCommand.inl"

#endif /* _KEIMPORTMODEL_SCENE_BACKGROUNDCOMMAND_H_ */
