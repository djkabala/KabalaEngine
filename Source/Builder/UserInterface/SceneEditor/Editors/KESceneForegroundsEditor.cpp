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

#include "KESceneForegroundsEditor.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneForegroundsEditor
The Scene Foregrounds Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SceneForegroundsEditor::_PresentationName("Foregrounds");
const std::string SceneForegroundsEditor::_PresentationIconName("Foreground");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneForegroundsEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::string& SceneForegroundsEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& SceneForegroundsEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void SceneForegroundsEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneForegroundsEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneForegroundsEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneForegroundsEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneForegroundsEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneForegroundsEditor::SceneForegroundsEditor(void) :
    Inherited()
{
}

SceneForegroundsEditor::SceneForegroundsEditor(const SceneForegroundsEditor &source) :
    Inherited(source)
{
}

SceneForegroundsEditor::~SceneForegroundsEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneForegroundsEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SceneForegroundsEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneForegroundsEditor NI" << std::endl;
}

