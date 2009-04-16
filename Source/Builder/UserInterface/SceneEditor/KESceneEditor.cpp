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

#include "KESceneEditor.h"

#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/OSGFieldContainerFactory.h>

#include "Builder/UserInterface/SceneEditor/Editors/KESceneComponentEditor.h" // Editors type
#include "Builder/KEApplicationBuilder.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneEditor
The SceneEditor.         
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SceneEditor::_PresentationName("Scene");
const std::string SceneEditor::_PresentationIconName("Scene");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::vector< ::osg::UInt32 > SceneEditor::getEditorTypeIds(void) const
{
	std::vector< ::osg::UInt32 > Result;

	for(FieldContainerFactory::TypeMapIterator Itor(FieldContainerFactory::the()->beginTypes()) ; Itor != FieldContainerFactory::the()->endTypes() ; ++Itor)
	{
		if(Itor->second->isDerivedFrom(SceneComponentEditor::getClassType()))
		{
			Result.push_back(Itor->second->getId());
		}
	}

	return Result;
}

const std::string& SceneEditor::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& SceneEditor::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void SceneEditor::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//Component Editors
	std::vector< ::osg::UInt32 > EditorTypeIdVector(getEditorTypeIds());
	FieldContainerPtr Editor(NullFC);
	beginEditCP(SceneEditorPtr(this), EditorsFieldMask);
	for(std::vector< ::osg::UInt32 >::const_iterator Itor(EditorTypeIdVector.begin()) ; Itor != EditorTypeIdVector.end(); ++Itor)
	{
		Editor = FieldContainerFactory::the()->findType(*Itor)->createFieldContainer();
		if(Editor != NullFC)
		{
			getEditors().push_back(SceneComponentEditor::Ptr::dcast(Editor));
			getEditors().back()->createInterface(TheApplicationBuilder);
		}
	}
	endEditCP(SceneEditorPtr(this), EditorsFieldMask);

	//Scene Label
    UIFontPtr SceneLabelFont = UIFont::create();
	beginEditCP(SceneLabelFont, UIFont::SizeFieldMask);
        SceneLabelFont->setSize(24);
    endEditCP(SceneLabelFont, UIFont::SizeFieldMask);

	//Scene Name Label
    _SceneLabel = osg::Label::create();
	beginEditCP(_SceneLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::FontFieldMask);
		_SceneLabel->setText("Scene:");
        _SceneLabel->setFont(SceneLabelFont);
        _SceneLabel->setPreferredSize(Vec2f(75,30));
	endEditCP(_SceneLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::FontFieldMask);

    _SceneNameLabel = osg::Label::create();
	beginEditCP(_SceneNameLabel, Label::PreferredSizeFieldMask | Label::FontFieldMask);
        _SceneNameLabel->setFont(SceneLabelFont);
        _SceneNameLabel->setPreferredSize(Vec2f(100,30));
	endEditCP(_SceneNameLabel, Label::PreferredSizeFieldMask | Label::FontFieldMask);


	//TabPanel
    _SceneEditorsTabPanel = osg::TabPanel::create();
    beginEditCP(_SceneEditorsTabPanel, TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask);
        _SceneEditorsTabPanel->setTabAlignment(0.0f);
        _SceneEditorsTabPanel->setTabPlacement(TabPanel::PLACEMENT_WEST);
		for(::osg::UInt32 i(0) ; i<getEditors().size() ; ++i)
		{
			_SceneEditorsTabPanel->addTab(createEditorTab(getEditors()[i], TheApplicationBuilder->getIconManager()), getEditors()[i]);
		}
    endEditCP(_SceneEditorsTabPanel,TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask);
        _SceneEditorsTabPanel->setSelectedIndex(0);


	//Layout
	SpringLayoutPtr SceneEditorInterfaceLayout = SpringLayout::create();

	//Scene Label
    SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SceneLabel, 0, SpringLayoutConstraints::WEST_EDGE, SceneEditorPtr(this));
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _SceneLabel, 0, SpringLayoutConstraints::NORTH_EDGE, SceneEditorPtr(this));
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SceneLabel, LayoutSpring::height(_SceneLabel));
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _SceneLabel, LayoutSpring::width(_SceneLabel));

	//Scene Name Label
    SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SceneNameLabel, 1, SpringLayoutConstraints::EAST_EDGE, _SceneLabel);
    SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SceneNameLabel, 0, SpringLayoutConstraints::EAST_EDGE, SceneEditorPtr(this));
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _SceneNameLabel, 0, SpringLayoutConstraints::NORTH_EDGE, SceneEditorPtr(this));
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _SceneNameLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _SceneLabel);

	//Scene Editors Tab Panel
    SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SceneEditorsTabPanel, 0, SpringLayoutConstraints::WEST_EDGE, SceneEditorPtr(this));
    SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SceneEditorsTabPanel, 0, SpringLayoutConstraints::EAST_EDGE, SceneEditorPtr(this));
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _SceneEditorsTabPanel, 1, SpringLayoutConstraints::SOUTH_EDGE, _SceneLabel);
	SceneEditorInterfaceLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _SceneEditorsTabPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, SceneEditorPtr(this));

	beginEditCP(SceneEditorPtr(this), SceneEditor::ChildrenFieldMask | SceneEditor::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(_SceneLabel);
		getChildren().push_back(_SceneNameLabel);
		getChildren().push_back(_SceneEditorsTabPanel);
		setLayout(SceneEditorInterfaceLayout);
	endEditCP(SceneEditorPtr(this), SceneEditor::ChildrenFieldMask | SceneEditor::LayoutFieldMask);
	
}

PanelPtr SceneEditor::createEditorTab(SceneComponentEditorPtr Editor, IconManagerPtr TheIconManager) const
{
	//Editor Icon
	ImageComponentPtr EditorIcon = TheIconManager->createIconImageComponent(Editor->getPresentationIconName());
    if(EditorIcon == NullFC)
    {
        EditorIcon = ImageComponent::create();
    }

	beginEditCP(EditorIcon, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		EditorIcon->setAlignment(Vec2f(0.5f,0.5f));
		EditorIcon->setScale(ImageComponent::SCALE_MIN_AXIS);
	endEditCP(EditorIcon, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	
	//Editor Label
	LabelPtr TabLabel = Label::create();
	beginEditCP(TabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::AlignmentFieldMask);
		TabLabel->setBorders(NullFC);
		TabLabel->setBackgrounds(NullFC);
		TabLabel->setText(Editor->getPresentationName());
		TabLabel->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(TabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::AlignmentFieldMask);

	//Tab
	PanelPtr Tab = Panel::createEmpty();

	//Layout
	SpringLayoutPtr TabLayout = SpringLayout::create();

	//Editor Icon
    TabLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, EditorIcon, 0, SpringLayoutConstraints::WEST_EDGE, Tab);
    TabLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, EditorIcon, 0, SpringLayoutConstraints::EAST_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, EditorIcon, 0, SpringLayoutConstraints::NORTH_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, EditorIcon, -1, SpringLayoutConstraints::NORTH_EDGE, TabLabel);
	
	//Editor Label
    TabLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TabLabel, 0, SpringLayoutConstraints::WEST_EDGE, Tab);
    TabLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TabLabel, 0, SpringLayoutConstraints::EAST_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TabLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TabLabel, LayoutSpring::height(TabLabel));
    
    //Tab Layout
    //TabLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, Tab, LayoutSpring::max(TabLayout->getConstraint(SpringLayoutConstraints::WIDTH_EDGE,TabLabel),TabLayout->getConstraint(SpringLayoutConstraints::WIDTH_EDGE,EditorIcon)));
    //TabLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, Tab, LayoutSpring::sum(TabLayout->getConstraint(SpringLayoutConstraints::HEIGHT_EDGE,TabLabel),TabLayout->getConstraint(SpringLayoutConstraints::HEIGHT_EDGE,EditorIcon)));
    TabLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, Tab, LayoutSpring::width(Tab));
    TabLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, Tab, LayoutSpring::height(Tab));

	beginEditCP(Tab, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		Tab->getChildren().push_back(EditorIcon);
		Tab->getChildren().push_back(TabLabel);
		Tab->setLayout(TabLayout);
		Tab->setPreferredSize(Vec2f(70.0f,50.0f));
	endEditCP(Tab, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);

	return Tab;
}

void SceneEditor::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	beginEditCP(SceneEditorPtr(this), EditingSceneFieldMask);
		setEditingScene(TheApplicationBuilder->getParentApplication()->getProject()->getInitialScene());
	endEditCP(SceneEditorPtr(this), EditingSceneFieldMask);

    //_SceneEditorsTabPanel->addChangeListener(&_EditorsTabPanelListener);

    getEditors()[_SceneEditorsTabPanel->getSelectedIndex()]->connectInterface(TheApplicationBuilder);
}

void SceneEditor::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	getEditors()[_SceneEditorsTabPanel->getSelectedIndex()]->disconnectInterface(TheApplicationBuilder);

    //_SceneEditorsTabPanel->removeChangeListener(&_EditorsTabPanelListener);
}

void SceneEditor::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	for(::osg::UInt32 i(0) ; i<getEditors().size() ; ++i)
	{
		getEditors()[i]->updateInterface(TheApplicationBuilder);
	}
}

void SceneEditor::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	for(::osg::UInt32 i(0) ; i<getEditors().size() ; ++i)
	{
		getEditors()[i]->destroyInterface(TheApplicationBuilder);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneEditor::SceneEditor(void) :
    Inherited(),
		_SceneNameLabel(NullFC),
        _EditorsTabPanelListener(SceneEditorPtr(this))
{
}

SceneEditor::SceneEditor(const SceneEditor &source) :
    Inherited(source),
		_SceneNameLabel(NullFC),
        _EditorsTabPanelListener(SceneEditorPtr(this))
{
}

SceneEditor::~SceneEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneEditor::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & EditingSceneFieldMask)
	{
		for(::osg::UInt32 i(0) ; i<getEditors().size() ; ++i)
		{
			beginEditCP(getEditors(i), SceneComponentEditor::EditingSceneFieldMask);
				getEditors(i)->setEditingScene(getEditingScene());
			endEditCP(getEditors(i), SceneComponentEditor::EditingSceneFieldMask);
		}
		
		if(_SceneNameLabel != NullFC)
		{
			beginEditCP(_SceneNameLabel, Label::TextFieldMask);
			if(getEditingScene() != NullFC)
			{
				_SceneNameLabel->setText(getEditingScene()->getName());
			}
			else
			{
				_SceneNameLabel->setText("");
			}
			endEditCP(_SceneNameLabel, Label::TextFieldMask);
		}
	}
}

void SceneEditor::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneEditor NI" << std::endl;
}

void SceneEditor::EditorsTabPanelListener::stateChanged(const ChangeEvent& e)
{
	//getEditors()[_SceneEditorsTabPanel->getActiveTab()]->disconnectInterface(TheApplicationBuilder);
    _SceneEditor->getEditors()[_SceneEditor->_SceneEditorsTabPanel->getSelectedIndex()]->connectInterface(NullFC);
}
