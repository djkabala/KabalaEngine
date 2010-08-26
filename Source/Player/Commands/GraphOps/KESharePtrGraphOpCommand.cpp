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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESharePtrGraphOpCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGSharePtrGraphOp.h>

#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ExportModelCommand
A ExportModelCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType SharePtrGraphOpCommand::_Type("SharePtrGraphOpCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SharePtrGraphOpCommandPtr SharePtrGraphOpCommand::create(NodeUnrecPtr RootNode)
{
	return RefPtr(new SharePtrGraphOpCommand(RootNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SharePtrGraphOpCommand::execute(void)
{
	OSG::SharePtrGraphOpRefPtr TheGraphOp = OSG::SharePtrGraphOp::create();

	std::string includes(MainApplication::the()->getSettings().get<std::string>("player.debugger.share_ptr_graph_op.includes")), 
				excludes(MainApplication::the()->getSettings().get<std::string>("player.debugger.share_ptr_graph_op.excludes"));

	if((includes.length() > 0) && (excludes.length() > 0))
	{
		SLOG << "SharePtrGraphOpCommand::execute: Settings given for both includes and excludes. Excludes will be ignored!";
	}
	if(includes.length() > 0)
	{
		TheGraphOp->setIncludes(includes);
	}
	else if(excludes.length() > 0)
	{
		TheGraphOp->setExcludes(excludes);
	}

	TheGraphOp->traverse(_RootNode);
}

std::string SharePtrGraphOpCommand::getCommandDescription(void) const
{
	std::string Description("Tries to save memory by sharing fields between field containers.");
	
	return Description;
}

std::string SharePtrGraphOpCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &SharePtrGraphOpCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SharePtrGraphOpCommand::~SharePtrGraphOpCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SharePtrGraphOpCommand::operator =(const SharePtrGraphOpCommand& source)
{
}

