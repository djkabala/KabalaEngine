/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESceneDynamicsEditor.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneDynamicsEditor
The Scene Dynamics Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SceneDynamicsEditor::_PresentationName("Dynamics");
const std::string SceneDynamicsEditor::_PresentationIconName("Dynamics");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneDynamicsEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::string& SceneDynamicsEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& SceneDynamicsEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void SceneDynamicsEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneDynamicsEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneDynamicsEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneDynamicsEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneDynamicsEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneDynamicsEditor::SceneDynamicsEditor(void) :
    Inherited()
{
}

SceneDynamicsEditor::SceneDynamicsEditor(const SceneDynamicsEditor &source) :
    Inherited(source)
{
}

SceneDynamicsEditor::~SceneDynamicsEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneDynamicsEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SceneDynamicsEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneDynamicsEditor NI" << std::endl;
}

