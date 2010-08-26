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

#include "KEPruneGraphOpCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGPruneGraphOp.h>

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

CommandType PruneGraphOpCommand::_Type("PruneGraphOpCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

PruneGraphOpCommandPtr PruneGraphOpCommand::create(NodeUnrecPtr RootNode)
{
	return RefPtr(new PruneGraphOpCommand(RootNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PruneGraphOpCommand::execute(void)
{
	std::string sMethod(MainApplication::the()->getSettings().get<std::string>("player.debugger.prune_graph_op.method")),
				sSize(MainApplication::the()->getSettings().get<std::string>("player.debugger.prune_graph_op.size"));

	OSG::PruneGraphOpRefPtr TheGraphOp = OSG::PruneGraphOp::create();

	std::string params = std::string("size=") + sSize + std::string(" method=")  + sMethod;
	TheGraphOp->setParams(params);

	TheGraphOp->traverse(_RootNode);

}

std::string PruneGraphOpCommand::getCommandDescription(void) const
{
	std::string Description("Removes nodes smaller than a given size.");
	
	return Description;
}

std::string PruneGraphOpCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &PruneGraphOpCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PruneGraphOpCommand::~PruneGraphOpCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PruneGraphOpCommand::operator =(const PruneGraphOpCommand& source)
{
}

