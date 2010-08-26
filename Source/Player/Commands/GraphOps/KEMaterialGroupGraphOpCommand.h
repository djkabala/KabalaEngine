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

#ifndef _KEMATERIALGROUPGRAPHOP_COMMAND_H_
#define _KEMATERIALGROUPGRAPHOP_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGCommand.h>

#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"

OSG_BEGIN_NAMESPACE

class MaterialGroupGraphOpCommand;
typedef boost::shared_ptr<MaterialGroupGraphOpCommand> MaterialGroupGraphOpCommandPtr;

class KE_KABALAENGINE_DLLMAPPING MaterialGroupGraphOpCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef MaterialGroupGraphOpCommandPtr RefPtr;

	MaterialGroupGraphOpCommand(NodeUnrecPtr RootNode);

	MaterialGroupGraphOpCommand(const MaterialGroupGraphOpCommand& source);

	void operator =(const MaterialGroupGraphOpCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;

	NodeRefPtr _RootNode;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~MaterialGroupGraphOpCommand(void);
	
	static MaterialGroupGraphOpCommandPtr create(NodeUnrecPtr RootNode);
};

OSG_END_NAMESPACE

#include "KEMaterialGroupGraphOpCommand.inl"

#endif /* _KEMATERIALGROUPGRAPHOP_COMMAND_H_ */
