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

#include "KESceneCamerasEditor.h"

#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>

#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGSplitPanel.h>

#include <OpenSG/UserInterface/OSGComboBox.h>
#include <OpenSG/UserInterface/OSGDefaultMutableComboBoxModel.h>

#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>



KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneCamerasEditor
The Scene Cameras Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SceneCamerasEditor::_PresentationName("Cameras");
const std::string SceneCamerasEditor::_PresentationIconName("Camera");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneCamerasEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::string& SceneCamerasEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& SceneCamerasEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void SceneCamerasEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{	
	//components in panel 1
	DefaultMutableComboBoxModelPtr comboBoxModel1 = DefaultMutableComboBoxModel::create();
	comboBoxModel1->addElement(boost::any(std::string("Matrix")));
	comboBoxModel1->addElement(boost::any(std::string("Perspective")));

	ComboBoxPtr comboBox1 = ComboBox::create();

	beginEditCP(comboBox1, ComboBox::ModelFieldMask);
		// Set the Model created above to the ComboBox
		comboBox1->setModel(comboBoxModel1);
	endEditCP(comboBox1, ComboBox::ModelFieldMask);

	// Determine where the ComboBox starts
	comboBox1->setSelectedIndex(0);



	ButtonPtr button1 = osg::Button::create();
    ButtonPtr button2 = osg::Button::create();

	beginEditCP(button1, Button::PreferredSizeFieldMask);
        button1->setPreferredSize(Vec2f(200, 50));
    endEditCP(button1, Button::PreferredSizeFieldMask);

    beginEditCP(button2, Button::PreferredSizeFieldMask);
        button2->setPreferredSize(Vec2f(50, 50));
    endEditCP(button2, Button::PreferredSizeFieldMask);

	FlowLayoutPtr PanelFlowLayout = osg::FlowLayout::create();
	//
	PanelPtr panel1 = osg::Panel::create();
    PanelPtr panel2 = osg::Panel::create();
	
	TextFieldPtr* 
		textField = (TextFieldPtr*)malloc(sizeof(TextFieldPtr) * 16);// = osg::TextField::create();
	for (int i = 0; i < 16; i++){
		textField[i] = osg::TextField::create();
		beginEditCP(textField[i], TextComponent::TextFieldMask);
			textField[i]->setText("0");
		endEditCP(textField[i], TextComponent::TextFieldMask);
	}
	/*
	beginEditCP(textField0, TextComponent::TextFieldMask);
        textField0->setText("0");
    endEditCP(textField0, TextComponent::TextFieldMask);
	*/
	GridLayoutPtr gridLayout = osg::GridLayout::create();

    beginEditCP(gridLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
        gridLayout->setRows(4);
        gridLayout->setColumns(4);
        gridLayout->setHorizontalGap(4);
        gridLayout->setVerticalGap(4);
    endEditCP(gridLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);


	beginEditCP(panel1, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		panel1->getChildren().push_back(comboBox1);
        panel1->getChildren().push_back(button1);
        panel1->setLayout(PanelFlowLayout);
    endEditCP(panel1, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
    beginEditCP(panel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        //panel2->getChildren().push_back(textField0);
		for (int i = 0; i < 16; i++)
			panel2->getChildren().push_back(textField[i]);
        panel2->setLayout(gridLayout);
    endEditCP(panel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	SplitPanelPtr splitPanel = osg::SplitPanel::create();

	beginEditCP(splitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        //splitPanel->setConstraints(splitPanelConstraints);
        splitPanel->setMinComponent(panel1);
        splitPanel->setMaxComponent(panel2);
        //splitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        splitPanel->setDividerPosition(.25); // this is a percentage
        splitPanel->setDividerPosition(300); // this is an absolute (300 > 1.0) 
        // location from the left/top
        splitPanel->setDividerSize(5);
        // splitPanel->setExpandable(false);
        splitPanel->setMaxDividerPosition(.9);
        splitPanel->setMinDividerPosition(220);
        
        // also, if you want to change the way the divider looks, you can always set a
        // DrawObjectCanvas in place of the default divider
        // splitPanel->setDividerDrawObject(drawObjectName);
    endEditCP(splitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
    

	SpringLayoutPtr SceneCamerasEditorLayout = SpringLayout::create();

	SceneCamerasEditorLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, splitPanel, 0, SpringLayoutConstraints::WEST_EDGE, SceneCamerasEditorPtr(this));
	SceneCamerasEditorLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, splitPanel, 0, SpringLayoutConstraints::NORTH_EDGE, SceneCamerasEditorPtr(this));
	SceneCamerasEditorLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, splitPanel, 0, SpringLayoutConstraints::EAST_EDGE, SceneCamerasEditorPtr(this));
	SceneCamerasEditorLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, splitPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, SceneCamerasEditorPtr(this));

	//Basic Scene Editor
	beginEditCP(SceneCamerasEditorPtr(this), SceneCamerasEditor::ChildrenFieldMask | SceneCamerasEditor::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(splitPanel); 
		setLayout(SceneCamerasEditorLayout);
	endEditCP(SceneCamerasEditorPtr(this), SceneCamerasEditor::ChildrenFieldMask | SceneCamerasEditor::LayoutFieldMask);

}

void SceneCamerasEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneCamerasEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneCamerasEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneCamerasEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneCamerasEditor::SceneCamerasEditor(void) :
    Inherited()
{
}

SceneCamerasEditor::SceneCamerasEditor(const SceneCamerasEditor &source) :
    Inherited(source)
{
}

SceneCamerasEditor::~SceneCamerasEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneCamerasEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SceneCamerasEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneCamerasEditor NI" << std::endl;
}

