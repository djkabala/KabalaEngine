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

#include "KEConfig.h"

#include "KEScene3DNodesEditor.h"

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Scene3DNodesEditor
The Scene 3DNodes Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string Scene3DNodesEditor::_PresentationName("3D World");
const std::string Scene3DNodesEditor::_PresentationIconName("Model");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Scene3DNodesEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


const std::string& Scene3DNodesEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& Scene3DNodesEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void Scene3DNodesEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Scene3DNodesEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Scene3DNodesEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Scene3DNodesEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Scene3DNodesEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Scene3DNodesEditor::Scene3DNodesEditor(void) :
    Inherited()
{
}

Scene3DNodesEditor::Scene3DNodesEditor(const Scene3DNodesEditor &source) :
    Inherited(source)
{
}

Scene3DNodesEditor::~Scene3DNodesEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Scene3DNodesEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Scene3DNodesEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Scene3DNodesEditor NI" << std::endl;
}

