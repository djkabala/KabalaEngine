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

#include <OpenSG/UserInterface/OSGMenuButton.h>
#include <OpenSG/UserInterface/OSGDefaultListModel.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLabel.h>

#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>

#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/UserInterface/OSGGLViewport.h>
#include <OpenSG/OSGPerspectiveCamera.h>

#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGSolidBackground.h>

OSG_USING_NAMESPACE

std::map<std::string, CameraPtr> cameraMap;
TextFieldPtr nameTextField;
PanelPtr panel2, matrixPanel, perspectivePanel;
DefaultListModelPtr cameraListModel;
MenuButtonPtr cameraMenuButton;
ListPtr cameraTypeList, cameraList;
SpinnerPtr nearSpinner; 
SpinnerPtr farSpinner;
SpinnerPtr sfFarSpinner; 
SpinnerPtr sfNearSpinner; 

ComboBoxPtr beaconCombo;
ComboBoxPtr sfBeaconCombo;

ViewportPtr cameraViewport;
GLViewportPtr viewPort;



class CameraAddButtonListener: public ActionListener
	{
	  public:

		  CameraAddButtonListener(){}
		  void actionPerformed(const ActionEventPtr e){	
			  int i = cameraMenuButton->getSelectionIndex();
			  if (!i){ //matrix
					static int i = 0;
					char name[32];
					sprintf(name, "MatrixCamera%d", i++);
					cameraListModel->pushBack(boost::any(std::string(name)));
					cameraMap[std::string(name)] = MatrixCamera::create();
				  return;
			  } 
			  if (i == 1){
				static int i = 0;
				char name[32];
				sprintf(name, "PerspectiveCamera%d", i++);
				cameraListModel->pushBack(boost::any(std::string(name)));
				cameraMap[std::string(name)] = PerspectiveCamera::create();
			  }
		}	
	};

class CameraDeleteButtonListener: public ActionListener
	{
	  public:

		  CameraDeleteButtonListener(){}
		  void actionPerformed(const ActionEventPtr e){	
			int i = cameraList->getSelectionModel()->getMinSelectionIndex();
			if (i < 0) return;
			std::string name = boost::any_cast<std::string>(cameraListModel->getElementAt(i));
			cameraListModel->erase(i);
			cameraMap.erase(name);
			
		}	
	};

class CameraListListener: public ListSelectionListener
	{
	  public:
		  CameraListListener(){
			  
		  }

		  virtual void selectionChanged(const ListSelectionEventPtr e){
			  int i = cameraList->getSelectionModel()->getMinSelectionIndex();
			  if (i < 0) return;
			  std::string name = boost::any_cast<std::string>(cameraListModel->getElementAt(i));
			  beginEditCP(nameTextField, TextComponent::TextFieldMask);
			  nameTextField->setText(name.c_str());
			  endEditCP(nameTextField, TextComponent::TextFieldMask);
			  MatrixCameraPtr matrixC = MatrixCameraPtr::dcast(cameraMap[name]);
			  if (matrixC != NullFC){
				  beginEditCP(panel2, Panel::ChildrenFieldMask);
				  panel2->getChildren().erase(panel2->getChildren().end()-1);
				  panel2->getChildren().push_back(matrixPanel);
				  endEditCP(panel2, Panel::ChildrenFieldMask); 
				  
			  }
			  PerspectiveCameraPtr PerspectiveC = PerspectiveCameraPtr::dcast(cameraMap[name]);
			  if (PerspectiveC != NullFC){
				  beginEditCP(panel2, Panel::ChildrenFieldMask);
				  panel2->getChildren().erase(panel2->getChildren().end()-1);
				  panel2->getChildren().push_back(perspectivePanel);
				  endEditCP(panel2, Panel::ChildrenFieldMask); 
				  printf("Perspective\n");
			  }
		  }
	};

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
	//create left pane and its children
	PanelPtr panel1 = osg::Panel::create();
	
	DefaultListModelPtr cameraTypeListModel = DefaultListModel::create();
    cameraTypeListModel->pushBack(boost::any(std::string("Matrix")));
	cameraTypeListModel->pushBack(boost::any(std::string("Perspective")));

	cameraMenuButton = MenuButton::create();
    beginEditCP(cameraMenuButton, MenuButton::TextFieldMask | MenuButton::PreferredSizeFieldMask | MenuButton::ModelFieldMask);
        cameraMenuButton->setText("Add camera");
        cameraMenuButton->setPreferredSize(Vec2f(120, 20));
        cameraMenuButton->setModel(cameraTypeListModel);
    endEditCP(cameraMenuButton, MenuButton::TextFieldMask | MenuButton::PreferredSizeFieldMask | MenuButton::ModelFieldMask);
	
    cameraMenuButton->addMenuActionListener(new CameraAddButtonListener());
	
	//delete button
	ButtonPtr deleteButton = Button::create();
	beginEditCP(deleteButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        deleteButton->setText("delete camera");
        deleteButton->setPreferredSize(Vec2f(130, 20));
    endEditCP(deleteButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
	deleteButton->addActionListener(new CameraDeleteButtonListener());

	//camera lists model
	cameraListModel = DefaultListModel::create();
	cameraList = List::create();
	ListSelectionModelPtr cameraListSelectionModel(new DefaultListSelectionModel());
	cameraList->setSelectionModel(cameraListSelectionModel);
	cameraList->getSelectionModel()->addListSelectionListener(new CameraListListener());

	beginEditCP(cameraList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
        cameraList->setPreferredSize(Vec2f(200, 300));
        cameraList->setOrientation(List::VERTICAL_ORIENTATION);
        //cameraList->setOrientation(List::HORIZONTAL_ORIENTATION);
		cameraList->setModel(cameraListModel);
    endEditCP(cameraList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
	
	//flow layout
	FlowLayoutPtr flowLayout = osg::FlowLayout::create();
    beginEditCP(flowLayout, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask | FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        flowLayout->setHorizontalGap(3.0f);
        flowLayout->setVerticalGap(3.0f);
        flowLayout->setMajorAxisAlignment(0.0f);
        flowLayout->setMinorAxisAlignment(0.0f);
    endEditCP(flowLayout, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask | FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);

	beginEditCP(panel1, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		//panel1->getChildren().push_back(cameraTypeList);
		panel1->getChildren().push_back(cameraMenuButton);
		panel1->getChildren().push_back(deleteButton);
		panel1->getChildren().push_back(cameraList);
		panel1->setLayout(flowLayout);
    endEditCP(panel1, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	//create right pane and its children
	panel2 = osg::Panel::create();
	
	//Name Label
    LabelPtr nameLabel = Label::create();
    beginEditCP(nameLabel, Label::TextFieldMask | Label::FontFieldMask);
        nameLabel->setText("Name:");
        //nameLabel->setFont(BackgroundLabelFont);
    endEditCP(nameLabel, Label::TextFieldMask | Label::FontFieldMask);


    //Name
    nameTextField = TextField::create();
	beginEditCP(nameTextField, Component::PreferredSizeFieldMask);
        nameTextField->setPreferredSize(Vec2f(200, 20));
	endEditCP(nameTextField, Component::PreferredSizeFieldMask );

	//matrix panel
	matrixPanel = Panel::create();
	GridLayoutPtr matrixGridLayout = GridLayout::create();
	beginEditCP(matrixGridLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
        matrixGridLayout->setRows(4);
        matrixGridLayout->setColumns(4);
        matrixGridLayout->setHorizontalGap(4);
        matrixGridLayout->setVerticalGap(4);
    endEditCP(matrixGridLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);

	TextFieldPtr textField[16];
	for (int i = 0; i < 16; i++)
		textField[i] = TextField::create();

    beginEditCP(matrixPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask| Panel::MinSizeFieldMask );
        //panel2->getChildren().push_back(textField0);
		for (int i = 0; i < 16; i++){
			textField[i]->setText(std::string("0"));
			matrixPanel->getChildren().push_back(textField[i]);
		}
        matrixPanel->setLayout(matrixGridLayout);
		matrixPanel->setPreferredSize(Vec2f(900, 300));
    endEditCP(matrixPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask| Panel::MinSizeFieldMask );

	//perspective panel
	perspectivePanel = Panel::create();
	perspectivePanel->setPreferredSize(Vec2f(900, 300));
	
	{
		Real32SpinnerModelPtr model = new Real32SpinnerModel();
		model->setStepSize(.5);
		// model->setValue(boost::any(Real32(0)));
		model->setMaximum(1000);
		model->setMinimum(-1000);
		nearSpinner = Spinner::create();
		nearSpinner->setModel(model);

		LabelPtr label = Label::create();
	    beginEditCP(label, Label::TextFieldMask | Label::FontFieldMask);
        label->setText("Near:");
		endEditCP(label, Label::TextFieldMask | Label::FontFieldMask);

		beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(label);
		perspectivePanel->getChildren().push_back(nearSpinner);
		endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	}

	{
		Real32SpinnerModelPtr model = new Real32SpinnerModel();
		model->setStepSize(.5);
		// model->setValue(boost::any(Real32(0)));
		model->setMaximum(1000);
		model->setMinimum(-1000);
		farSpinner = Spinner::create();
		farSpinner->setModel(model);

		LabelPtr label = Label::create();
	    beginEditCP(label, Label::TextFieldMask | Label::FontFieldMask);
        label->setText("Far:");
		endEditCP(label, Label::TextFieldMask | Label::FontFieldMask);

		beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(label);
		perspectivePanel->getChildren().push_back(farSpinner);
		endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	}

	{
		Real32SpinnerModelPtr model = new Real32SpinnerModel();
		model->setStepSize(.5);
		// model->setValue(boost::any(Real32(0)));
		model->setMaximum(1000);
		model->setMinimum(-1000);
		sfNearSpinner = Spinner::create();
		sfNearSpinner->setModel(model);

		LabelPtr label = Label::create();
	    beginEditCP(label, Label::TextFieldMask | Label::FontFieldMask);
        label->setText("SF Near:");
		endEditCP(label, Label::TextFieldMask | Label::FontFieldMask);

		beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(label);
		perspectivePanel->getChildren().push_back(sfNearSpinner);
		endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	}

	{
		Real32SpinnerModelPtr model = new Real32SpinnerModel();
		model->setStepSize(.5);
		// model->setValue(boost::any(Real32(0)));
		model->setMaximum(1000);
		model->setMinimum(-1000);
		sfFarSpinner = Spinner::create();
		sfFarSpinner->setModel(model);

		LabelPtr label = Label::create();
	    beginEditCP(label, Label::TextFieldMask | Label::FontFieldMask);
        label->setText("SF Far:");
		endEditCP(label, Label::TextFieldMask | Label::FontFieldMask);

		beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(label);
		perspectivePanel->getChildren().push_back(sfFarSpinner);
		endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	}

	{
		DefaultMutableComboBoxModelPtr comboModel = DefaultMutableComboBoxModel::create();
		comboModel->addElement(boost::any(std::string("Light")));
		comboModel->addElement(boost::any(std::string("Torus")));

		beaconCombo = ComboBox::create();

		beginEditCP(beaconCombo, ComboBox::ModelFieldMask);
		// Set the Model created above to the ComboBox
			beaconCombo->setModel(comboModel);
		endEditCP(beaconCombo, ComboBox::ModelFieldMask);

		// Determine where the ComboBox starts
		beaconCombo->setSelectedIndex(0);

		LabelPtr label = Label::create();
	    beginEditCP(label, Label::TextFieldMask | Label::FontFieldMask);
        label->setText("Beacon:");
		endEditCP(label, Label::TextFieldMask | Label::FontFieldMask);

		beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(label);
		perspectivePanel->getChildren().push_back(beaconCombo);
		endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	}

	{
		DefaultMutableComboBoxModelPtr comboModel = DefaultMutableComboBoxModel::create();
		comboModel->addElement(boost::any(std::string("Light")));
		comboModel->addElement(boost::any(std::string("Torus")));

		sfBeaconCombo = ComboBox::create();

		beginEditCP(sfBeaconCombo, ComboBox::ModelFieldMask);
		// Set the Model created above to the ComboBox
			sfBeaconCombo->setModel(comboModel);
		endEditCP(sfBeaconCombo, ComboBox::ModelFieldMask);

		// Determine where the ComboBox starts
		sfBeaconCombo->setSelectedIndex(0);

		LabelPtr label = Label::create();
	    beginEditCP(label, Label::TextFieldMask | Label::FontFieldMask);
        label->setText("SF Beacon:");
		endEditCP(label, Label::TextFieldMask | Label::FontFieldMask);

		beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(label);
		perspectivePanel->getChildren().push_back(sfBeaconCombo);
		endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	}

	{
	//view port
	//Viewport
	cameraViewport = Viewport::create();
	beginEditCP(cameraViewport);
	cameraViewport->setCamera                  (MatrixCamera::create());
		//cameraViewport->setRoot                    (DefaultRootNode);
		//cameraViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
	cameraViewport->setBackground              (SolidBackground::create());//getEditingScene()->getInitialBackground());
	endEditCP(cameraViewport);
	
	//GL Viewport Component
	viewPort = GLViewport::create();
	beginEditCP(viewPort, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask);
		viewPort->setPort(cameraViewport);
		viewPort->setPreferredSize(Vec2f(800.0f,600.0f));
	endEditCP(viewPort, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask);

	/*
	beginEditCP(perspectivePanel, Panel::ChildrenFieldMask );
		perspectivePanel->getChildren().push_back(viewPort);
	endEditCP(perspectivePanel, Panel::ChildrenFieldMask );
	*/
	}
	beginEditCP(perspectivePanel, Panel::LayoutFieldMask | Panel::MinSizeFieldMask );
		perspectivePanel->setLayout(flowLayout);
    endEditCP(perspectivePanel,  Panel::LayoutFieldMask | Panel::MinSizeFieldMask );

	//right panel
	beginEditCP(panel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::MinSizeFieldMask );
		panel2->getChildren().push_back(nameLabel);
		panel2->getChildren().push_back(nameTextField);
		panel2->getChildren().push_back(matrixPanel);
		//panel2->setMinSize(Vec2f(400, 400));
		panel2->getChildren().push_back(viewPort);
		panel2->setLayout(flowLayout);
    endEditCP(panel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::MinSizeFieldMask );

	//create top level split pane
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
    endEditCP(splitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
    
	//top level spring layout
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

	
#if 0 
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
#endif
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

