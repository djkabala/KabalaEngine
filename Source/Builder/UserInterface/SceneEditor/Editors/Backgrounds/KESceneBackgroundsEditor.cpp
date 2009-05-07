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

#include "KESceneBackgroundsEditor.h"
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include "KEBackgroundsListComponentGenerator.h"
#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/KEBuilderInterface.h"

#include "Builder/UserInterface/Common/KEFieldContainerTypeComponentGenerator.h"

#include "Builder/UserInterface/Editors/KEFieldContainerEditorFactory.h"

#include "KECreateSceneBackgroundCommand.h"
#include "KEDeleteSceneBackgroundCommand.h"
#include "KERenameSceneBackgroundCommand.h"

#include "Project/Scene/KEScene.h"

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneBackgroundsEditor
The Scene Backgrounds Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SceneBackgroundsEditor::_PresentationName("Backgrounds");
const std::string SceneBackgroundsEditor::_PresentationIconName("Background");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneBackgroundsEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::string& SceneBackgroundsEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& SceneBackgroundsEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void SceneBackgroundsEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
    
    _IconManager = TheApplicationBuilder->getIconManager();
    //Create the Generic Field Container Editor if needed
    FieldContainerEditorType* GenericFCEditorType = FieldContainerEditorFactory::the()->getDefaultGenericEditor();
    if(GenericFCEditorType != NULL)
    {
        _GenericEditor = GenericFCEditorType->create();
    }

    //For all Background Types
    UInt32 NumFieldContainersFound(0);
    FieldContainerType* FoundType = NULL;
    FieldContainerEditorPtr DefaultEditor;
    for(UInt32 j(0) ; NumFieldContainersFound<FieldContainerFactory::the()->getNumTypes(); ++j)
    {
        FoundType = FieldContainerFactory::the()->findType(j);
        if(FoundType != NULL)
        {
            if(FoundType->isDerivedFrom(Background::getClassType())  && !FoundType->isAbstract())
            {
                //Add Editor
                DefaultEditor = FieldContainerEditorFactory::the()->createDefaultEditor(FoundType);
                if(DefaultEditor != FieldContainerEditorPtr())
                {
                    _Editors[FoundType->getId()] = DefaultEditor;
                }
            }
            ++NumFieldContainersFound;
        }
    }

    //Background create Menu button
    //Create the Background Type List Model
    _BackgroundTypesModel = DerivedFieldContainerComboBoxModel::create();
    beginEditCP(_BackgroundTypesModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);
        _BackgroundTypesModel->getDerivedFieldContainerTypes().push_back(std::string(Background::getClassname()));
    endEditCP(_BackgroundTypesModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);

    //Create the Component Generator
    FieldContainerTypeComponentGeneratorPtr BackgroundTypeComponentGenerator = FieldContainerTypeComponentGenerator::create();
    BackgroundTypeComponentGenerator->setIconManager(TheApplicationBuilder->getIconManager());

    _BackgroundCreateMenuButton = MenuButton::create();
    beginEditCP(_BackgroundCreateMenuButton, MenuButton::CellGeneratorFieldMask | MenuButton::ModelFieldMask | MenuButton::PreferredSizeFieldMask);
        _BackgroundCreateMenuButton->setCellGenerator(BackgroundTypeComponentGenerator);
        _BackgroundCreateMenuButton->setModel(_BackgroundTypesModel);
        _BackgroundCreateMenuButton->setPreferredSize(Vec2f(38,38));
    endEditCP(_BackgroundCreateMenuButton, MenuButton::CellGeneratorFieldMask | MenuButton::ModelFieldMask | MenuButton::PreferredSizeFieldMask);
    TheApplicationBuilder->getIconManager()->applyIconSet(_BackgroundCreateMenuButton, "NewBackground", Vec2f(32,32));
    _BackgroundCreateMenuButton->addMenuActionListener(&_BackgroundCreateMenuButtonListener);
    _BackgroundCreateMenuButtonListener.setApplicationBuilder(TheApplicationBuilder);

	_ListModel = SceneBackgroundsComboBoxModel::create();

	_ListComponentGenerator = BackgroundsListComponentGenerator::create();
	_ListComponentGenerator->setIconManager(TheApplicationBuilder->getIconManager());

	//Backgrounds List PopupMenu
	MenuItemPtr BackgroundDeleteMenuItem = MenuItem::create();
    beginEditCP(BackgroundDeleteMenuItem, MenuItem::TextFieldMask);
        BackgroundDeleteMenuItem->setText("Delete");
    endEditCP(BackgroundDeleteMenuItem, MenuItem::TextFieldMask);
	BackgroundDeleteMenuItem->addActionListener(&_BackgroundDeleteActionListener);
    _BackgroundDeleteActionListener.setApplicationBuilder(TheApplicationBuilder);

    PopupMenuPtr BackgroundListPopupMenu = PopupMenu::create();
    BackgroundListPopupMenu->addItem(BackgroundDeleteMenuItem);

	//Backgrounds List
    _BackgroundsList = List::create();
	beginEditCP(_BackgroundsList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::CellGeneratorFieldMask | List::ModelFieldMask);
        _BackgroundsList->setPreferredSize(Vec2f(200, 300));
        _BackgroundsList->setOrientation(List::VERTICAL_ORIENTATION);
		_BackgroundsList->setCellGenerator(_ListComponentGenerator);
		_BackgroundsList->setModel(_ListModel);
        _BackgroundsList->setPopupMenu(BackgroundListPopupMenu);
    endEditCP(_BackgroundsList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::CellGeneratorFieldMask | List::ModelFieldMask);
    _BackgroundsList->setSelectionModel(_ListSelectionModel);
    _BackgroundsList->getSelectionModel()->addListSelectionListener(&_BackgroundsListListener);

	//Backgrounds List Scroll Panel
    _BackgroundListScrollPanel = ScrollPanel::create();
    beginEditCP(_BackgroundListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _BackgroundListScrollPanel->setPreferredSize(Vec2f(200,300));
        _BackgroundListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_BackgroundListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    _BackgroundListScrollPanel->setViewComponent(_BackgroundsList);

	//Initial Background Label
	_InitialBackgroundLabel = Label::create();
	beginEditCP(_InitialBackgroundLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
		_InitialBackgroundLabel->setText("Initial");
		_InitialBackgroundLabel->setPreferredSize(Vec2f(35.0f, 20.0f));
	endEditCP(_InitialBackgroundLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

	//Initial Background ComboBox
	_InitialBackgroundComboBox = ComboBox::create();
	beginEditCP(_InitialBackgroundComboBox, ComboBox::EditableFieldMask | ComboBox::ModelFieldMask | ComboBox::CellGeneratorFieldMask);
		_InitialBackgroundComboBox->setEditable(false);
		_InitialBackgroundComboBox->setModel(_ListModel);
		_InitialBackgroundComboBox->setCellGenerator(_ListComponentGenerator);
	endEditCP(_InitialBackgroundComboBox, ComboBox::EditableFieldMask | ComboBox::ModelFieldMask | ComboBox::CellGeneratorFieldMask);

	//Background Navigation Panel
    _BackgroundNavigationPanel = osg::Panel::create();
	SpringLayoutPtr BackgroundNavigationPanelLayout = SpringLayout::create();

	//Label
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _InitialBackgroundLabel, 0, SpringLayoutConstraints::WEST_EDGE, _BackgroundNavigationPanel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _InitialBackgroundLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _BackgroundNavigationPanel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _InitialBackgroundLabel, LayoutSpring::width(_InitialBackgroundLabel));
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _InitialBackgroundLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _InitialBackgroundComboBox);

	//ComboBox
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _InitialBackgroundComboBox, 1, SpringLayoutConstraints::EAST_EDGE, _InitialBackgroundLabel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _InitialBackgroundComboBox, 0, SpringLayoutConstraints::NORTH_EDGE,_BackgroundNavigationPanel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _InitialBackgroundComboBox, 0, SpringLayoutConstraints::EAST_EDGE, _BackgroundNavigationPanel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _InitialBackgroundComboBox, LayoutSpring::height(_InitialBackgroundComboBox));

	//List Scroll Panel
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BackgroundListScrollPanel, 0, SpringLayoutConstraints::WEST_EDGE, _BackgroundNavigationPanel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundListScrollPanel, 1, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundCreateMenuButton);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundListScrollPanel, 0, SpringLayoutConstraints::EAST_EDGE, _BackgroundNavigationPanel);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundListScrollPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundNavigationPanel);

    //Create Menu Button
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundCreateMenuButton, 1, SpringLayoutConstraints::SOUTH_EDGE, _InitialBackgroundComboBox);
	BackgroundNavigationPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundCreateMenuButton, 0, SpringLayoutConstraints::EAST_EDGE, _BackgroundNavigationPanel);

	beginEditCP(_BackgroundNavigationPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		_BackgroundNavigationPanel->getChildren().push_back(_InitialBackgroundLabel);
		_BackgroundNavigationPanel->getChildren().push_back(_InitialBackgroundComboBox);
		_BackgroundNavigationPanel->getChildren().push_back(_BackgroundCreateMenuButton);
		_BackgroundNavigationPanel->getChildren().push_back(_BackgroundListScrollPanel);
		_BackgroundNavigationPanel->setLayout(BackgroundNavigationPanelLayout);
	endEditCP(_BackgroundNavigationPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	

    UIFontPtr BackgroundLabelFont = UIFont::create();
	beginEditCP(BackgroundLabelFont, UIFont::SizeFieldMask);
        BackgroundLabelFont->setSize(22);
    endEditCP(BackgroundLabelFont, UIFont::SizeFieldMask);

    //Name Label
    LabelPtr BackgroundNameLabel = Label::create();
    beginEditCP(BackgroundNameLabel, Label::TextFieldMask | Label::FontFieldMask);
        BackgroundNameLabel->setText("Name:");
        BackgroundNameLabel->setFont(BackgroundLabelFont);
    endEditCP(BackgroundNameLabel, Label::TextFieldMask | Label::FontFieldMask);

    //Name
    _BackgroundNameTextField = TextField::create();
    beginEditCP(_BackgroundNameTextField, TextField::FontFieldMask);
        _BackgroundNameTextField->setFont(BackgroundLabelFont);
    endEditCP(_BackgroundNameTextField, TextField::FontFieldMask);
    _BackgroundNameTextListener.setApplicationBuilder(TheApplicationBuilder);


    //Type Icon
    _BackgroundTypeIcon = ImageComponent::create();
	beginEditCP(_BackgroundTypeIcon, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask | ImageComponent::PreferredSizeFieldMask);
		_BackgroundTypeIcon->setAlignment(Vec2f(0.5f, 0.5f));
		_BackgroundTypeIcon->setScale(ImageComponent::SCALE_MIN_AXIS);
		_BackgroundTypeIcon->setPreferredSize(Vec2f(32.0f,32.0f));
	endEditCP(_BackgroundTypeIcon, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask | ImageComponent::PreferredSizeFieldMask);

    //Type Label
    _BackgroundTypeLabel = Label::create();
    beginEditCP(_BackgroundTypeLabel, Label::PreferredSizeFieldMask | Label::FontFieldMask);
		_BackgroundTypeLabel->setPreferredSize(Vec2f(170.0f, 20.0f));
        _BackgroundTypeLabel->setFont(BackgroundLabelFont);
    endEditCP(_BackgroundTypeLabel, Label::PreferredSizeFieldMask | Label::FontFieldMask);

    //Editor Panel
    _BackgroundEditorPanel = Panel::createEmpty();
    beginEditCP(_BackgroundEditorPanel, Panel::LayoutFieldMask);
        _BackgroundEditorPanel->setLayout(BorderLayout::create());
    endEditCP(_BackgroundEditorPanel, Panel::LayoutFieldMask);

	//Background Desc Editor
	_BackgroundDescEditorPanel = Panel::createEmpty();
	SpringLayoutPtr BackgroundDescEditorPanelLayout = SpringLayout::create();

	//Name Label
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, BackgroundNameLabel, 0, SpringLayoutConstraints::WEST_EDGE, _BackgroundDescEditorPanel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, BackgroundNameLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _BackgroundDescEditorPanel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, BackgroundNameLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundTypeIcon);

    //Name TextField
    BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BackgroundNameTextField, 1, SpringLayoutConstraints::EAST_EDGE, BackgroundNameLabel);
    BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundNameTextField, 1, SpringLayoutConstraints::WEST_EDGE, _BackgroundTypeIcon);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundNameTextField, 0, SpringLayoutConstraints::NORTH_EDGE, _BackgroundDescEditorPanel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundNameTextField, 0, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundTypeIcon);
    
    //Type Icon
    BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundTypeIcon, 1, SpringLayoutConstraints::WEST_EDGE, _BackgroundTypeLabel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundTypeIcon, 0, SpringLayoutConstraints::NORTH_EDGE, _BackgroundDescEditorPanel);
    
    //Type Label
    BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundTypeLabel, 0, SpringLayoutConstraints::EAST_EDGE, _BackgroundDescEditorPanel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundTypeLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _BackgroundDescEditorPanel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundTypeLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundTypeIcon);
    
    //Details Editor
    BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BackgroundEditorPanel, 0, SpringLayoutConstraints::WEST_EDGE, _BackgroundDescEditorPanel);
    BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundEditorPanel, -2, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _BackgroundDescEditorPanel);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundEditorPanel, 1, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundTypeIcon);
	BackgroundDescEditorPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundEditorPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundDescEditorPanel);

    beginEditCP(_BackgroundDescEditorPanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
        _BackgroundDescEditorPanel->setLayout(BackgroundDescEditorPanelLayout);
        _BackgroundDescEditorPanel->getChildren().push_back(BackgroundNameLabel);
        _BackgroundDescEditorPanel->getChildren().push_back(_BackgroundNameTextField);
        _BackgroundDescEditorPanel->getChildren().push_back(_BackgroundTypeIcon);
        _BackgroundDescEditorPanel->getChildren().push_back(_BackgroundTypeLabel);
        _BackgroundDescEditorPanel->getChildren().push_back(_BackgroundEditorPanel);
    endEditCP(_BackgroundDescEditorPanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);

	//Background Preview Viewport
	Matrix TransformMatrix;
	TransformMatrix.setTranslate(0.0f,0.0f, 0.0f);
	TransformPtr CameraBeaconTransform = Transform::create();
	beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
		CameraBeaconTransform->setMatrix(TransformMatrix);
	endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	_CameraBeaconNode = Node::create();
	beginEditCP(_CameraBeaconNode, Node::CoreFieldMask);
		_CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(_CameraBeaconNode, Node::CoreFieldMask);

    // Make Main Scene Node
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(_CameraBeaconNode);
    endEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Camera
	PerspectiveCameraPtr DefaultCamera = PerspectiveCamera::create();
     beginEditCP(DefaultCamera);
		 DefaultCamera->setBeacon(_CameraBeaconNode);
		 DefaultCamera->setFov   (deg2rad(60.f));
		 DefaultCamera->setNear  (0.1f);
		 DefaultCamera->setFar   (100.f);
     endEditCP(DefaultCamera);
	
	//Viewport
	_BackgroundPreviewViewport = Viewport::create();
	beginEditCP(_BackgroundPreviewViewport);
		_BackgroundPreviewViewport->setCamera                  (DefaultCamera);
		_BackgroundPreviewViewport->setRoot                    (DefaultRootNode);
		_BackgroundPreviewViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
		_BackgroundPreviewViewport->setBackground              (getEditingBackground());
	endEditCP(_BackgroundPreviewViewport);
	
	//GL Viewport Component
	_BackgroundPreviewComponent = GLViewport::create();
	beginEditCP(_BackgroundPreviewComponent, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask);
		_BackgroundPreviewComponent->setPort(_BackgroundPreviewViewport);
		_BackgroundPreviewComponent->setPreferredSize(Vec2f(800.0f,600.0f));
	endEditCP(_BackgroundPreviewComponent, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask);

	//Background Editor Panel
    _BackgroundViewEditorPanel = osg::Panel::createEmpty();
	SpringLayoutPtr BackgroundViewEditorPanelLayout = SpringLayout::create();

    BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundDescEditorPanel, 0, SpringLayoutConstraints::EAST_EDGE, _BackgroundViewEditorPanel);
	BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundDescEditorPanel, -2, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _BackgroundViewEditorPanel);
    BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundDescEditorPanel,0, SpringLayoutConstraints::NORTH_EDGE, _BackgroundViewEditorPanel);
	BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BackgroundDescEditorPanel,0, SpringLayoutConstraints::WEST_EDGE, _BackgroundViewEditorPanel);

    BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _BackgroundPreviewComponent, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _BackgroundViewEditorPanel);
	BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundPreviewComponent, 0, SpringLayoutConstraints::SOUTH_EDGE, _BackgroundViewEditorPanel);
    BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundPreviewComponent,2, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _BackgroundViewEditorPanel);
    BackgroundViewEditorPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _BackgroundPreviewComponent, LayoutSpring::scale(BackgroundViewEditorPanelLayout->getConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _BackgroundPreviewComponent),1.77778));


	beginEditCP(_BackgroundViewEditorPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		_BackgroundViewEditorPanel->getChildren().push_back(_BackgroundDescEditorPanel);
		_BackgroundViewEditorPanel->getChildren().push_back(_BackgroundPreviewComponent);
		_BackgroundViewEditorPanel->setLayout(BackgroundViewEditorPanelLayout);
	endEditCP(_BackgroundViewEditorPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	//SplitPanel
    _BackgroundSplitPanel = osg::SplitPanel::create();

	beginEditCP(_BackgroundSplitPanel, SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        _BackgroundSplitPanel->setMinComponent(_BackgroundNavigationPanel);
        _BackgroundSplitPanel->setMaxComponent(_BackgroundViewEditorPanel);
        _BackgroundSplitPanel->setDividerPosition(200); // this is an absolute (300 > 1.0) 
        // location from the left/top
        _BackgroundSplitPanel->setDividerSize(5);
        _BackgroundSplitPanel->setMaxDividerPosition(0.9f);
        _BackgroundSplitPanel->setMinDividerPosition(50);
        
        // also, if you want to change the way the divider looks, you can always set a
        // DrawObjectCanvas in place of the default divider
        // _BackgroundSplitPanel->setDividerDrawObject(drawObjectName);
    endEditCP(_BackgroundSplitPanel, SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
    
	//Layout
	SpringLayoutPtr SceneBackgroundsEditorLayout = SpringLayout::create();

	/*SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BackgroundListScrollPanel, 0, SpringLayoutConstraints::WEST_EDGE, SceneBackgroundsEditorPtr(this));
	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundListScrollPanel, 0, SpringLayoutConstraints::NORTH_EDGE, SceneBackgroundsEditorPtr(this));
	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _BackgroundListScrollPanel, LayoutSpring::height(_BackgroundListScrollPanel));
	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _BackgroundListScrollPanel, LayoutSpring::width(_BackgroundListScrollPanel));*/


	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BackgroundSplitPanel, 0, SpringLayoutConstraints::WEST_EDGE, SceneBackgroundsEditorPtr(this));
	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _BackgroundSplitPanel, 0, SpringLayoutConstraints::NORTH_EDGE, SceneBackgroundsEditorPtr(this));
	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BackgroundSplitPanel, 0, SpringLayoutConstraints::EAST_EDGE, SceneBackgroundsEditorPtr(this));
	SceneBackgroundsEditorLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _BackgroundSplitPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, SceneBackgroundsEditorPtr(this));

	//Basic Scene Editor
	beginEditCP(SceneBackgroundsEditorPtr(this), SceneBackgroundsEditor::ChildrenFieldMask | SceneBackgroundsEditor::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(_BackgroundSplitPanel);
		setLayout(SceneBackgroundsEditorLayout);
	endEditCP(SceneBackgroundsEditorPtr(this), SceneBackgroundsEditor::ChildrenFieldMask | SceneBackgroundsEditor::LayoutFieldMask);


    //Toolbar Tools
    _Tools.push_back(::osg::Button::create());
}

void SceneBackgroundsEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
    TheApplicationBuilder->getInterface()->addToolbarTools(_Tools);
}

void SceneBackgroundsEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
    TheApplicationBuilder->getInterface()->removeToolbarTools(_Tools);
}

void SceneBackgroundsEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void SceneBackgroundsEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneBackgroundsEditor::SceneBackgroundsEditor(void) :
    Inherited(),
		_ListSelectionModel(new DefaultListSelectionModel()),
		_BackgroundsListListener(SceneBackgroundsEditorPtr(this)),
		_BackgroundCreateMenuButtonListener(SceneBackgroundsEditorPtr(this)),
		_BackgroundDeleteActionListener(SceneBackgroundsEditorPtr(this)),
		_BackgroundNameTextListener(SceneBackgroundsEditorPtr(this))
{
}

SceneBackgroundsEditor::SceneBackgroundsEditor(const SceneBackgroundsEditor &source) :
    Inherited(source),
		_ListSelectionModel(new DefaultListSelectionModel()),
		_BackgroundsListListener(SceneBackgroundsEditorPtr(this)),
		_BackgroundCreateMenuButtonListener(SceneBackgroundsEditorPtr(this)),
		_BackgroundDeleteActionListener(SceneBackgroundsEditorPtr(this)),
		_BackgroundNameTextListener(SceneBackgroundsEditorPtr(this))
{
}

SceneBackgroundsEditor::~SceneBackgroundsEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneBackgroundsEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & EditingSceneFieldMask)
	{
		beginEditCP(_ListModel, SceneBackgroundsComboBoxModel::EditingSceneFieldMask);
			_ListModel->setEditingScene(getEditingScene());
		endEditCP(_ListModel, SceneBackgroundsComboBoxModel::EditingSceneFieldMask);
	}

	if(whichField & EditingBackgroundFieldMask)
	{
		CameraPtr TheCamera = Camera::Ptr::dcast(getEditingScene()->getInitialCamera()->shallowCopy());
		beginEditCP(TheCamera, Camera::BeaconFieldMask);
			TheCamera->setBeacon(_CameraBeaconNode);
		endEditCP(TheCamera, Camera::BeaconFieldMask);

		NodePtr RootNode = Node::create();
		beginEditCP(RootNode, Node::ChildrenFieldMask);
		
			RootNode->setCore(Group::create());
			for(::osg::UInt32 i(0) ; i<getEditingScene()->getInitialModelNodes().size() ; ++i)
			{
				RootNode->addChild(getEditingScene()->getInitialModelNodes()[i]);
			}
			RootNode->addChild(_CameraBeaconNode);
		endEditCP(RootNode, Node::ChildrenFieldMask);

		//Update Background Viewport
		beginEditCP(_BackgroundPreviewViewport, Viewport::CameraFieldMask | Viewport::RootFieldMask | Viewport::BackgroundFieldMask | Viewport::ForegroundsFieldMask);
			_BackgroundPreviewViewport->setCamera                  (TheCamera);
			_BackgroundPreviewViewport->setRoot                    (RootNode);
			_BackgroundPreviewViewport->setBackground              (getEditingBackground());
			_BackgroundPreviewViewport->getForegrounds().clear();
			for(UInt32 i(0) ; i<getEditingScene()->getInitialForegrounds().size(); ++i)
			{
				_BackgroundPreviewViewport->getForegrounds().push_back(getEditingScene()->getInitialForegrounds(i));
			}
		endEditCP(_BackgroundPreviewViewport, Viewport::CameraFieldMask | Viewport::RootFieldMask | Viewport::BackgroundFieldMask | Viewport::ForegroundsFieldMask);
		

		_BackgroundPreviewComponent->set(getEditingScene()->getInitialCamera()->getBeacon()->getToWorld());

        //Editor
        if(getEditingBackground() != NullFC)
        {

            //Update Name Text Field
            _BackgroundNameTextField->removeTextListener(&_BackgroundNameTextListener);
            beginEditCP(_BackgroundNameTextField, TextField::TextFieldMask);
			    const Char8* Name(getName(getEditingBackground()));
			    if(Name != NULL)
			    {
				    _BackgroundNameTextField->setText(Name);
			    }
            endEditCP(_BackgroundNameTextField, TextField::TextFieldMask);
            _BackgroundNameTextField->addTextListener(&_BackgroundNameTextListener);

            //Update The Type Icon
            _BackgroundTypeIcon->setTexture(_IconManager->getIconTexture(getEditingBackground()->getTypeName()));
            
            //Update Type Label
            beginEditCP(_BackgroundTypeLabel, Label::TextFieldMask);
                _BackgroundTypeLabel->setText(getEditingBackground()->getTypeName());
            endEditCP(_BackgroundTypeLabel, Label::TextFieldMask);

            if(_ActiveEditor != FieldContainerEditorPtr())
            {
                _ActiveEditor->detachTarget();
            }

            std::map<UInt32, FieldContainerEditorPtr>::iterator SearchEditors = _Editors.find(getEditingBackground()->getTypeId());
                
            if(SearchEditors != _Editors.end())
            {
                _ActiveEditor = SearchEditors->second;
            }
            else
            {
                _ActiveEditor = _GenericEditor;
            }

            _ActiveEditor->setTarget(getEditingBackground());

            beginEditCP(_BackgroundEditorPanel, Panel::ChildrenFieldMask);
                _BackgroundEditorPanel->getChildren().clear();
                if(getEditingBackground() != NullFC)
                {
                    BorderLayoutConstraintsPtr ActiveEditorConstraints = osg::BorderLayoutConstraints::create();
                    beginEditCP(ActiveEditorConstraints, BorderLayoutConstraints::RegionFieldMask);
                        ActiveEditorConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
                    endEditCP(ActiveEditorConstraints, BorderLayoutConstraints::RegionFieldMask);

                    ComponentPtr TheComponent(_ActiveEditor->createInterface());
                    beginEditCP(TheComponent, Component::ConstraintsFieldMask);
                        TheComponent->setConstraints(ActiveEditorConstraints);
                    endEditCP(TheComponent, Component::ConstraintsFieldMask);
                    _BackgroundEditorPanel->getChildren().push_back(TheComponent);
                }
            endEditCP(_BackgroundEditorPanel, Panel::ChildrenFieldMask);

            
            _ActiveEditor->attachTarget();
        }
	}
}

void SceneBackgroundsEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneBackgroundsEditor NI" << std::endl;
}


void SceneBackgroundsEditor::BackgroundsListListener::selectionChanged(const ListSelectionEvent& e)
{
	beginEditCP(_SceneBackgroundsEditor, EditingBackgroundFieldMask);

	if(!_SceneBackgroundsEditor->_BackgroundsList->getSelectionModel()->isSelectionEmpty())
	{
        try
        {
            BackgroundPtr TheSelectedBackground = boost::any_cast<BackgroundPtr>(_SceneBackgroundsEditor->_BackgroundsList->getValueAtIndex(_SceneBackgroundsEditor->_BackgroundsList->getSelectionModel()->getAnchorSelectionIndex()));
            _SceneBackgroundsEditor->setEditingBackground(TheSelectedBackground);
        }
        catch(boost::bad_any_cast &)
        {
		    _SceneBackgroundsEditor->setEditingBackground(NullFC);
        }

	}
	else
	{
		_SceneBackgroundsEditor->setEditingBackground(NullFC);
	}

	endEditCP(_SceneBackgroundsEditor, EditingBackgroundFieldMask);
}

void SceneBackgroundsEditor::BackgroundCreateMenuButtonListener::actionPerformed(const ActionEvent& e)
{
    try
    {
        FieldContainerType* FCType;
        FCType = boost::any_cast<FieldContainerType*>(_SceneBackgroundsEditor->_BackgroundCreateMenuButton->getSelectionValue());
        CommandPtr CreateBackground = CreateSceneBackgroundCommand::create(_SceneBackgroundsEditor->_ListModel, FCType);
        _ApplicationBuilder->getCommandManager()->executeCommand(CreateBackground);
    }
    catch(boost::bad_any_cast&)
    {
    }
}

void SceneBackgroundsEditor::BackgroundDeleteActionListener::actionPerformed(const ActionEvent& e)
{
    Int32 SelectedIndex = _SceneBackgroundsEditor->_ListSelectionModel->getMinSelectionIndex();
    if(SelectedIndex >= 0)
    {
        CommandPtr DeleteBackground = DeleteSceneBackgroundCommand::create(_SceneBackgroundsEditor->_ListModel, SelectedIndex);
        _ApplicationBuilder->getCommandManager()->executeCommand(DeleteBackground);
    }
}


void SceneBackgroundsEditor::BackgroundNameTextListener::textValueChanged(const TextEvent& e)
{

    Int32 SelectedIndex = _SceneBackgroundsEditor->_ListSelectionModel->getMinSelectionIndex();
    if(SelectedIndex >= 0)
    {
        CommandPtr RenameBackground = RenameSceneBackgroundCommand::create(_SceneBackgroundsEditor->_ListModel, SelectedIndex, _SceneBackgroundsEditor->_BackgroundNameTextField->getText());
        _ApplicationBuilder->getCommandManager()->executeCommand(RenameBackground);
        Component::Ptr::dcast(e.getSource())->takeFocus();
    }
}
