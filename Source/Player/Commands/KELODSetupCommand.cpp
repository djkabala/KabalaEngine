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

#include "KELODSetupCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGLODSetupGraphOp.h>

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

CommandType LODSetupCommand::_Type("LODSetupCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

LODSetupCommandPtr LODSetupCommand::create(NodeUnrecPtr RootNode)
{
	return RefPtr(new LODSetupCommand(RootNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LODSetupCommand::execute(void)
{
	OSG::LODSetupGraphOpRefPtr LODSetupGrOp = OSG::LODSetupGraphOp::create();
	LODSetupGrOp->addLODInfo(0,100.0f,"_High");
	LODSetupGrOp->addLODInfo(1,200.0f,"_Mid");
	LODSetupGrOp->addLODInfo(2,200.0f,"_Med");
	LODSetupGrOp->addLODInfo(3,290.0f,"_Low");

	if(LODSetupGrOp->traverse(_RootNode))
	{
		std::cout << "Number of LOD nodes set up: " << LODSetupGrOp->getNumLODSMade() << std::endl;
	}
}

std::string LODSetupCommand::getCommandDescription(void) const
{
	std::string Description("Sets up level of detail nodes in the scene");
	
	return Description;
}

std::string LODSetupCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &LODSetupCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LODSetupCommand::~LODSetupCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LODSetupCommand::operator =(const LODSetupCommand& source)
{
}

