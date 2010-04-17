/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEContentPanel.h"
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGTitlebar.h>

#include <boost/program_options.hpp>

//#include "Application/KEMainApplication.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ContentPanel
The ContentPanel. Shows the content of files   
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ContentPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ContentPanel::addTabWithText(Path file)
{

	PanelPtr _NewLeftTabLabelPanel = Panel::createEmpty();

	ButtonPtr _NewLeftTabLabelCloseButtonPtr = ButtonPtr::dcast(InternalWindowPtr::dcast(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());

	/*ButtonPtr _NewLeftTabLabelCloseButtonPtr = Button::create();
	
	beginEditCP(_NewLeftTabLabelCloseButtonPtr,Button::TextFieldMask | Button::PreferredSizeFieldMask);
		_NewLeftTabLabelCloseButtonPtr->setPreferredSize(Vec2f(100,20));
		_NewLeftTabLabelCloseButtonPtr->setText("X");
	endEditCP(_NewLeftTabLabelCloseButtonPtr,Button::TextFieldMask | Button::PreferredSizeFieldMask);*/

	_NewLeftTabLabelCloseButtonPtr->addActionListener(&_CloseButtonListener);

	LabelPtr _NewLeftTabLabelLabel=Label::create();
	beginEditCP(_NewLeftTabLabelLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _NewLeftTabLabelLabel->setText(file.leaf());
        _NewLeftTabLabelLabel->setBorders(NullFC);
        _NewLeftTabLabelLabel->setBackgrounds(NullFC);
	endEditCP(_NewLeftTabLabelLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	
	SpringLayoutPtr _NewLeftTabLabelPanelSpringLayout = osg::SpringLayout::create();
	
	_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelCloseButtonPtr, 2, SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelPanel);  
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelCloseButtonPtr, -2, SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelPanel);
	_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelCloseButtonPtr, -20, SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelPanel);
	_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelCloseButtonPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelPanel);
    
	_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelLabel, 2, SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelPanel);  
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelLabel, -5, SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelCloseButtonPtr);
	_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelLabel, 2, SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelPanel);
	_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelPanel);


	beginEditCP(_NewLeftTabLabelPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		_NewLeftTabLabelPanel->setPreferredSize(Vec2f(120,20));
		_NewLeftTabLabelPanel->getChildren().push_back(_NewLeftTabLabelLabel);
		_NewLeftTabLabelPanel->getChildren().push_back(_NewLeftTabLabelCloseButtonPtr);
		_NewLeftTabLabelPanel->setLayout(_NewLeftTabLabelPanelSpringLayout);
	endEditCP(_NewLeftTabLabelPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
	
		

	std::string sent;
	std::string para="";
	std::ifstream inputFile((file.string()).c_str());
	while(std::getline(inputFile,sent))para+=sent+"\n";
	inputFile.close();
	//std::cout<<para<<std::endl;

	TextAreaPtr _NewLeftTabTextArea = osg::TextArea::create();
    _NewLeftTabTextArea->setText(para);
	_NewLeftTabTextArea->setEditable(true);
        
    ScrollPanelPtr _NewLeftTabContent = ScrollPanel::create();
    beginEditCP(_NewLeftTabContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _NewLeftTabContent->setPreferredSize(Vec2f(200,1200));
        _NewLeftTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_NewLeftTabContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	_NewLeftTabContent->setViewComponent(_NewLeftTabTextArea);

	
	PanelPtr _NewRightTabLabelPanel = Panel::createEmpty();

	ButtonPtr _RightTabLabelCloseButtonPtr = ButtonPtr::dcast(InternalWindowPtr::dcast(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());
	
	/*beginEditCP(_RightTabLabelCloseButtonPtr,Button::TextFieldMask | Button::PreferredSizeFieldMask);
	_RightTabLabelCloseButtonPtr->setPreferredSize(Vec2f(20,10));
	_RightTabLabelCloseButtonPtr->setText("X");
	endEditCP(_RightTabLabelCloseButtonPtr,Button::TextFieldMask | Button::PreferredSizeFieldMask);*/
	
	_RightTabLabelCloseButtonPtr->addActionListener(&_CloseButtonListener);

	LabelPtr _NewRightTabLabel=Label::create();
	beginEditCP(_NewRightTabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _NewRightTabLabel->setText(file.leaf());
        _NewRightTabLabel->setBorders(NullFC);
        _NewRightTabLabel->setBackgrounds(NullFC);
	endEditCP(_NewRightTabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	
	SpringLayoutPtr _NewRightTabLabelPanelSpringLayout = osg::SpringLayout::create();
	
	_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _RightTabLabelCloseButtonPtr, 2, SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabelPanel);  
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RightTabLabelCloseButtonPtr, -2, SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabelPanel);
	_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _RightTabLabelCloseButtonPtr, -20, SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabelPanel);
	_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _RightTabLabelCloseButtonPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabelPanel);
    
	_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabel, 2, SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabelPanel);  
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabel, -5, SpringLayoutConstraints::WEST_EDGE, _RightTabLabelCloseButtonPtr);
	_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewRightTabLabel, 2, SpringLayoutConstraints::WEST_EDGE, _NewRightTabLabelPanel);
	_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabelPanel);
	

	beginEditCP(_NewRightTabLabelPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		_NewRightTabLabelPanel->setPreferredSize(Vec2f(120,20));
		_NewRightTabLabelPanel->getChildren().push_back(_RightTabLabelCloseButtonPtr);
		_NewRightTabLabelPanel->getChildren().push_back(_NewRightTabLabel);
		_NewRightTabLabelPanel->setLayout(_NewRightTabLabelPanelSpringLayout);
	endEditCP(_NewRightTabLabelPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
	

	
	TextAreaPtr _NewRightTabTextArea = osg::TextArea::create();
    _NewRightTabTextArea->setText(para);
	_NewRightTabTextArea->setEditable(true);
	        
    ScrollPanelPtr _NewRightTabContent = ScrollPanel::create();
    beginEditCP(_NewRightTabContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _NewRightTabContent->setPreferredSize(Vec2f(200,1200));
        _NewRightTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_NewRightTabContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	_NewRightTabContent->setViewComponent(_NewRightTabTextArea);


	beginEditCP(_RightTabPanel,TabPanel::TabsFieldMask);
		_RightTabPanel->addTab(_NewLeftTabLabelPanel, _NewLeftTabContent);
    endEditCP(_RightTabPanel, TabPanel::TabsFieldMask);

    _RightTabPanel->setSelectedIndex((_RightTabPanel->getTabs().getSize())-1);

	beginEditCP(_LeftTabPanel,TabPanel::TabsFieldMask);
		_LeftTabPanel->addTab(_NewRightTabLabelPanel, _NewRightTabContent);
    endEditCP(_LeftTabPanel, TabPanel::TabsFieldMask);

	_LeftTabPanel->setSelectedIndex((_LeftTabPanel->getTabs().getSize())-1);
		
}

void ContentPanel::saveTextFile(Path file)
{
	std::ofstream _OutputFile((file.string()).c_str());

	ScrollPanelPtr _ToBeSavedScrollPanel = ScrollPanelPtr::dcast(_LeftTabPanel->getTabContents(_LeftTabPanel->getSelectedIndex()));
	TextAreaPtr _ToBeSavedTextArea = TextAreaPtr::dcast(_ToBeSavedScrollPanel->getViewComponent());
	
	std::string _TobeSavedText = _ToBeSavedTextArea->getText();
	_OutputFile<<_TobeSavedText;
	_OutputFile.close();

	std::cout<<"File Saved"<<std::endl;
}

void ContentPanel::closeCurrentWindow()
{

	beginEditCP(_LeftTabPanel,TabPanel::TabsFieldMask);
		_LeftTabPanel->removeTab(_LeftTabPanel->getSelectedIndex());
    endEditCP(_LeftTabPanel, TabPanel::TabsFieldMask);

	beginEditCP(_RightTabPanel,TabPanel::TabsFieldMask| TabPanel::TabContentsFieldMask | TabPanel::ChildrenFieldMask);
		_RightTabPanel->removeTab(_RightTabPanel->getSelectedIndex());
    endEditCP(_RightTabPanel, TabPanel::TabsFieldMask|TabPanel::TabContentsFieldMask | TabPanel::ChildrenFieldMask);

}

void ContentPanel::createRightTabPanel()
{
	_RightTabPanel= osg::TabPanel::create();
    beginEditCP(_RightTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		_RightTabPanel->setPreferredSize(Vec2f(1200,1200));
	    _RightTabPanel->addTab(_RightTabPanelLabel, _RightTabPanelContent);
		_RightTabPanel->setTabAlignment(0.5f);
        _RightTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(_RightTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    _RightTabPanel->setSelectedIndex(0);
}

void ContentPanel::createLeftTabPanel()
{
	_LeftTabPanel= osg::TabPanel::create();
    beginEditCP(_LeftTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		_LeftTabPanel->setPreferredSize(Vec2f(1200,1200));
	    _LeftTabPanel->addTab(_LeftTabPanelLabel, _LeftTabPanelContent);
		_LeftTabPanel->setTabAlignment(0.5f);
        _LeftTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(_LeftTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    _LeftTabPanel->setSelectedIndex(0);
}

void ContentPanel::createDefaultTabs()
{
	_LeftTabPanelLabel = osg::Label::create();

	// set the fields of the labels
	beginEditCP(_LeftTabPanelLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::PreferredSizeFieldMask);
		_LeftTabPanelLabel->setPreferredSize(Vec2f(120,20));
        _LeftTabPanelLabel->setText("Welcome!");
        _LeftTabPanelLabel->setBorders(NullFC);
        _LeftTabPanelLabel->setBackgrounds(NullFC);
	endEditCP(_LeftTabPanelLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::PreferredSizeFieldMask);
    
	// Create a _StackTraceTextArea
	_LeftTabPanelTextArea = osg::TextArea::create();
    _LeftTabPanelTextArea->setText("Hey Programmer!\n\n\n The following shortcuts also exists \n Ctrl+X\t-\t to execute Lua code \n Ctrl+1\t-\t To Focus on Lua Console TextArea \n Ctrl+T\t-\t for splitting the Content Panel \n\n You can now save/open files using the Debugging Interface\n Please DO NOT open files greater than 5KB.It is not efficiently coded and hence would take years to load.\n\n\n\t\tThank you!\n\n");
	_LeftTabPanelTextArea->setEditable(false);
        
    _LeftTabPanelContent = ScrollPanel::create();
    beginEditCP(_LeftTabPanelContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _LeftTabPanelContent->setPreferredSize(Vec2f(200,1200));
        _LeftTabPanelContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_LeftTabPanelContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the _LeftTabPanelTextArea to the ScrollPanel so it is displayed
	_LeftTabPanelContent->setViewComponent(_LeftTabPanelTextArea);


	_RightTabPanelLabel = osg::Label::create();

	// set the fields of the labels
	beginEditCP(_RightTabPanelLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _RightTabPanelLabel->setText("Screen2");
        _RightTabPanelLabel->setBorders(NullFC);
        _RightTabPanelLabel->setBackgrounds(NullFC);
	endEditCP(_RightTabPanelLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	// Create a _StackTraceTextArea
	_RightTabPanelTextArea = osg::TextArea::create();
    _RightTabPanelTextArea->setText("This is the Second screen.\n\n Opening files now will open them in both screens.\n\n Pressing the \"Save file\" would only save the currently selected file in the left screen.\n\n\t\tThank you!\n\n");
	_RightTabPanelTextArea->setEditable(false);
        
    _RightTabPanelContent = ScrollPanel::create();
    beginEditCP(_RightTabPanelContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _RightTabPanelContent->setPreferredSize(Vec2f(200,1200));
        _RightTabPanelContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_RightTabPanelContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the _RightTabPanelTextArea to the ScrollPanel so it is displayed
	_RightTabPanelContent->setViewComponent(_RightTabPanelTextArea);

}


void ContentPanel::setIsSplit(bool value)
{
	_IsSplit = value;
	updatePanel();
}

bool ContentPanel::getIsSplit()
{
	return _IsSplit;
}

void ContentPanel::createLuaEditorSplitPanel()
{
	createDefaultTabs();
	createRightTabPanel();
	createLeftTabPanel();

    //Lua Editing Panel
    _LuaEditorSplitPanel = SplitPanel::create();

    beginEditCP(_LuaEditorSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
                SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);

        _LuaEditorSplitPanel->setMaxComponent(_RightTabPanel);
        _LuaEditorSplitPanel->setDividerSize(5);
        _LuaEditorSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);

    endEditCP(_LuaEditorSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
              SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
}

void ContentPanel::updatePanel()
{
    beginEditCP(_LuaEditorSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
                SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
    
	if(_IsSplit)
	{
			_LuaEditorSplitPanel->setDividerPosition(.50); 
			_LuaEditorSplitPanel->setExpandable(true);
			_LuaEditorSplitPanel->setMaxDividerPosition(.85);
			_LuaEditorSplitPanel->setMinDividerPosition(.15);
			_LuaEditorSplitPanel->setMinComponent(_LeftTabPanel);
	}
	else
	{
			_LuaEditorSplitPanel->setDividerPosition(0); 
			_LuaEditorSplitPanel->setExpandable(true);
			_LuaEditorSplitPanel->setMaxDividerPosition(0);
			_LuaEditorSplitPanel->setMinDividerPosition(0);
			_LuaEditorSplitPanel->setMinComponent(_LeftTabPanel);
	}

    endEditCP(_LuaEditorSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
              SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);

}

void ContentPanel::createSceneEditorPanel()
{
    //Scene Editing Panel
    _SceneEditorPanel = Panel::createEmpty();
}

void ContentPanel::init()
{
    //Create the Lua Code Editing Panel
    createLuaEditorSplitPanel();
	setIsSplit(false);

    //Create the Scene Graph Editing Panel
    createSceneEditorPanel();

    //Add the Editing Panels in a card layout to this panel
	_MainCardLayout = CardLayout::create();
    
    beginEditCP(ContentPanelPtr(this), Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        getChildren().push_back(_SceneEditorPanel);
        getChildren().push_back(_LuaEditorSplitPanel);
        setLayout(_MainCardLayout);
        setBackgrounds(NullFC);
        setBorders(NullFC);
    endEditCP(ContentPanelPtr(this), Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
}

void ContentPanel::setView(UInt32 Index)
{
    beginEditCP(_MainCardLayout, CardLayout::CardFieldMask);
        _MainCardLayout->setCard(Index);
    endEditCP(_MainCardLayout, CardLayout::CardFieldMask);
}

void ContentPanel::addTab()
{

}

void ContentPanel::removeTab(UInt32 tabno)
{

}
void ContentPanel::actionPerformed(const osg::ActionEventPtr e)
{

	ButtonPtr _TempCloseButton = ButtonPtr::dcast(e->getSource());
	PanelPtr _TempPanel = PanelPtr::dcast(_TempCloseButton->getParentContainer());
	TabPanelPtr _TempTabPanel = TabPanelPtr::dcast(_TempPanel->getParentContainer());
	UInt32 _ChildIndex = (_TempTabPanel->getChildIndex(_TempPanel))/2;
	std::cout<<"chldindex:"<<_ChildIndex<<std::endl;
	
	beginEditCP(_LeftTabPanel,TabPanel::ChildrenFieldMask);
		_LeftTabPanel->removeTab(_ChildIndex);
	endEditCP(_LeftTabPanel,TabPanel::ChildrenFieldMask);

	beginEditCP(_RightTabPanel,TabPanel::ChildrenFieldMask);
		_RightTabPanel->removeTab(_ChildIndex);
	endEditCP(_RightTabPanel,TabPanel::ChildrenFieldMask);

}
ContentPanel::CloseButtonListener::CloseButtonListener(ContentPanelPtr TheContentPanel)
{
	_ContentPanelPtr = TheContentPanel;
}

ContentPanel::CloseButtonListener::~CloseButtonListener()
{
}

void ContentPanel::CloseButtonListener::actionPerformed(const osg::ActionEventPtr e)
{
	_ContentPanelPtr->actionPerformed(e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ContentPanel::ContentPanel(void) :
    Inherited(),
	_CloseButtonListener(ContentPanelPtr(this))
{
}

ContentPanel::ContentPanel(const ContentPanel &source) :
    Inherited(source),
	_CloseButtonListener(ContentPanelPtr(this))
{
}

ContentPanel::~ContentPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ContentPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ContentPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ContentPanel NI" << std::endl;
}


OSG_END_NAMESPACE

