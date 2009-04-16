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

#include "KESceneBasicEditor.h"
#include <OpenSG/UserInterface/OSGFlowLayout.h>

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneBasicEditor
The Scene Basic Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SceneBasicEditor::_PresentationName("Basic");
const std::string SceneBasicEditor::_PresentationIconName("Scene");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneBasicEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::string& SceneBasicEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& SceneBasicEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void SceneBasicEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//Scene Name Label
    _SceneNameLabel = osg::Label::create();
	beginEditCP(_SceneNameLabel, Label::TextFieldMask);
		_SceneNameLabel->setText("Scene Name:");
	endEditCP(_SceneNameLabel, Label::TextFieldMask);

	//Scene Name Text Field
    _SceneNameTextField = osg::TextField::create();
	beginEditCP(_SceneNameTextField, TextField::TextFieldMask);
		_SceneNameTextField->setText("NOT NAMED");
	endEditCP(_SceneNameTextField, TextField::TextFieldMask);

	//Layout
	FlowLayoutPtr SceneBasicEditorLayout = FlowLayout::create();
	

	//Basic Scene Editor
	beginEditCP(SceneBasicEditorPtr(this), SceneBasicEditor::ChildrenFieldMask | SceneBasicEditor::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(_SceneNameLabel);
		getChildren().push_back(_SceneNameTextField);
		setLayout(SceneBasicEditorLayout);
	endEditCP(SceneBasicEditorPtr(this), SceneBasicEditor::ChildrenFieldMask | SceneBasicEditor::LayoutFieldMask);
}

void SceneBasicEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneBasicEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneBasicEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneBasicEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneBasicEditor::SceneBasicEditor(void) :
    Inherited()
{
}

SceneBasicEditor::SceneBasicEditor(const SceneBasicEditor &source) :
    Inherited(source)
{
}

SceneBasicEditor::~SceneBasicEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneBasicEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SceneBasicEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneBasicEditor NI" << std::endl;
}

