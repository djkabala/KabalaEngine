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

#include "KEAttachColGeomGraphOpCommand.h"
#include "Application/KEMainApplication.h"
#include <OpenSG/OSGAttachColGeomGraphOp.h>

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

CommandType AttachColGeomGraphOpCommand::_Type("AttachColGeomGraphOpCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

AttachColGeomGraphOpCommandPtr AttachColGeomGraphOpCommand::create(Node* const RootNode)
{
	return RefPtr(new AttachColGeomGraphOpCommand(RootNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AttachColGeomGraphOpCommand::execute(void)
{
	AttachColGeomGraphOpRefPtr TheGraphOp = OSG::AttachColGeomGraphOp::create();

    TheGraphOp->setMatchName(MainApplication::the()->getSettings().get<bool>("player.debugger.col_geom_graph_op.match_name"));
    TheGraphOp->setMatchWholeName(MainApplication::the()->getSettings().get<bool>("player.debugger.col_geom_graph_op.match_whole_name"));
    TheGraphOp->setMatchCurrentTravMask(MainApplication::the()->getSettings().get<bool>("player.debugger.col_geom_graph_op.match_trav_mask"));
    TheGraphOp->setCurrentTravMaskValue(MainApplication::the()->getSettings().get<UInt32>("player.debugger.col_geom_graph_op.match_trav_mask_value"));
    TheGraphOp->setMatchMaskCondition(MainApplication::the()->getSettings().get<UInt8>("player.debugger.col_geom_graph_op.match_mask_condition"));
    TheGraphOp->setCreateGeomType(MainApplication::the()->getSettings().get<UInt32>("player.debugger.col_geom_graph_op.create_geom_type"));

	TheGraphOp->traverse(_RootNode);
}

std::string AttachColGeomGraphOpCommand::getCommandDescription(void) const
{
	std::string Description("Attach Physics geom to nodes.");
	
	return Description;
}

std::string AttachColGeomGraphOpCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &AttachColGeomGraphOpCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AttachColGeomGraphOpCommand::~AttachColGeomGraphOpCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AttachColGeomGraphOpCommand::operator =(const AttachColGeomGraphOpCommand& source)
{
}

