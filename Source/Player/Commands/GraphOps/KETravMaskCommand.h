/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *  authors: David Kabala, Dan Guilliams (djkabala/dan.guilliams@gmail.com)  *
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

#ifndef _KETRAVMASK_COMMAND_H_
#define _KETRAVMASK_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>

#include "Player/KEApplicationPlayerFields.h"
#include "Player/HierarchyPanel/KEHierarchyPanelFields.h"
#include <OpenSG/OSGDialogWindowEventDetailsFields.h>
#include <OpenSG/OSGUIDrawingSurfaceFields.h>

OSG_BEGIN_NAMESPACE

class TravMaskCommand;
typedef boost::shared_ptr<TravMaskCommand> TravMaskCommandPtr;

class KE_KABALAENGINE_DLLMAPPING TravMaskCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef TravMaskCommandPtr RefPtr;

	TravMaskCommand(Node* const RootNode,
                    UIDrawingSurface* const DrawingSurface);

	TravMaskCommand(const TravMaskCommand& source);

	void operator =(const TravMaskCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;

	NodeRefPtr _RootNode;
	UIDrawingSurfaceRefPtr _DrawingSurface;

    std::string _SearchString;
    UInt32      _NewTravMask;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;

    static void handleChooseTravMaskDialogClosed(DialogWindowEventDetails* const details,
                                                       const std::string& SearchString,
                                                       Node* const RootNode);

    static void handleChooseMatchStringDialogClosed(DialogWindowEventDetails* const details,
                                                          UIDrawingSurface* const DrawingSurface,
                                                          Node* const RootNode);
	
    static const CommandType &getClassType(void);

	virtual ~TravMaskCommand(void);
	
	static TravMaskCommandPtr create(Node* const RootNode,
                                     UIDrawingSurface* const DrawingSurface);
};

OSG_END_NAMESPACE

#include "KETravMaskCommand.inl"

#endif /* _KETRAVMASK_COMMAND_H_ */
