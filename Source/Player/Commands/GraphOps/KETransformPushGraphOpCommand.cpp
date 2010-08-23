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

#include "KETransformPushGraphOpCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGTransformPushGraphOp.h>

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

CommandType TransformPushGraphOpCommand::_Type("TransformPushGraphOpCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

TransformPushGraphOpCommandPtr TransformPushGraphOpCommand::create(NodeUnrecPtr RootNode)
{
	return RefPtr(new TransformPushGraphOpCommand(RootNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TransformPushGraphOpCommand::execute(void)
{
	OSG::TransformPushGraphOpRefPtr TheGraphOp = OSG::TransformPushGraphOp::create();

	// no settings for this graph op...

	TheGraphOp->traverse(_RootNode);
}

std::string TransformPushGraphOpCommand::getCommandDescription(void) const
{
	std::string Description("Attempts to push transforms towards leaf nodes.");
	
	return Description;
}

std::string TransformPushGraphOpCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &TransformPushGraphOpCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TransformPushGraphOpCommand::~TransformPushGraphOpCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TransformPushGraphOpCommand::operator =(const TransformPushGraphOpCommand& source)
{
}

