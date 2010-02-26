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

	PanelPtr newTabLabelPanel = Panel::createEmpty();

	ButtonPtr CloseButtonPtr = ButtonPtr::dcast(InternalWindowPtr::dcast(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());
	/*ButtonPtr CloseButtonPtr = Button::create();
	
	beginEditCP(CloseButtonPtr,Button::TextFieldMask | Button::PreferredSizeFieldMask);
		CloseButtonPtr->setPreferredSize(Vec2f(100,20));
		CloseButtonPtr->setText("X");
	endEditCP(CloseButtonPtr,Button::TextFieldMask | Button::PreferredSizeFieldMask);*/

	CloseButtonPtr->addActionListener(&_CloseButtonListener);

	LabelPtr newTabLabel=Label::create();
	beginEditCP(newTabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        newTabLabel->setText(file.leaf());
        newTabLabel->setBorders(NullFC);
        newTabLabel->setBackgrounds(NullFC);

	endEditCP(newTabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	
	SpringLayoutPtr springLayout = osg::SpringLayout::create();
	
	springLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CloseButtonPtr, 2, SpringLayoutConstraints::NORTH_EDGE, newTabLabelPanel);  
    springLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CloseButtonPtr, -2, SpringLayoutConstraints::EAST_EDGE, newTabLabelPanel);
	springLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CloseButtonPtr, -20, SpringLayoutConstraints::EAST_EDGE, newTabLabelPanel);
	springLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CloseButtonPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, newTabLabelPanel);
    
	springLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, newTabLabel, 2, SpringLayoutConstraints::NORTH_EDGE, newTabLabelPanel);  
    springLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, newTabLabel, -5, SpringLayoutConstraints::WEST_EDGE, CloseButtonPtr);
	springLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, newTabLabel, 2, SpringLayoutConstraints::WEST_EDGE, newTabLabelPanel);
	springLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, newTabLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, newTabLabelPanel);


	beginEditCP(newTabLabelPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		newTabLabelPanel->setPreferredSize(Vec2f(120,20));
		newTabLabelPanel->getChildren().push_back(newTabLabel);
		newTabLabelPanel->getChildren().push_back(CloseButtonPtr);
		newTabLabelPanel->setLayout(springLayout);
	endEditCP(newTabLabelPanel,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
	
		

	std::string sent;
	std::string para="";
	std::ifstream inputFile((file.string()).c_str());
	while(std::getline(inputFile,sent))para+=sent+"\n";
	inputFile.close();
	//std::cout<<para<<std::endl;

	TextAreaPtr newTextArea = osg::TextArea::create();
    newTextArea->setText(para);
	newTextArea->setEditable(true);
        
    ScrollPanelPtr newTabContent = ScrollPanel::create();
    beginEditCP(newTabContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        newTabContent->setPreferredSize(Vec2f(200,1200));
        newTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(newTabContent, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	newTabContent->setViewComponent(newTextArea);

	
	PanelPtr newTabLabelPanel_r = Panel::createEmpty();

	ButtonPtr CloseButtonPtr_r = ButtonPtr::dcast(InternalWindowPtr::dcast(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());
	
	/*beginEditCP(CloseButtonPtr_r,Button::TextFieldMask | Button::PreferredSizeFieldMask);
	CloseButtonPtr_r->setPreferredSize(Vec2f(20,10));
	CloseButtonPtr_r->setText("X");
	endEditCP(CloseButtonPtr_r,Button::TextFieldMask | Button::PreferredSizeFieldMask);*/
	
	CloseButtonPtr_r->addActionListener(&_CloseButtonListener);

	LabelPtr newTabLabel_r=Label::create();
	beginEditCP(newTabLabel_r, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        newTabLabel_r->setText(file.leaf());
        newTabLabel_r->setBorders(NullFC);
        newTabLabel_r->setBackgrounds(NullFC);
	endEditCP(newTabLabel_r, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	
	SpringLayoutPtr springLayout_r = osg::SpringLayout::create();
	
	springLayout_r->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CloseButtonPtr_r, 2, SpringLayoutConstraints::NORTH_EDGE, newTabLabelPanel_r);  
    springLayout_r->putConstraint(SpringLayoutConstraints::EAST_EDGE, CloseButtonPtr_r, -2, SpringLayoutConstraints::EAST_EDGE, newTabLabelPanel_r);
	springLayout_r->putConstraint(SpringLayoutConstraints::WEST_EDGE, CloseButtonPtr_r, -20, SpringLayoutConstraints::EAST_EDGE, newTabLabelPanel_r);
	springLayout_r->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CloseButtonPtr_r, -2, SpringLayoutConstraints::SOUTH_EDGE, newTabLabelPanel_r);
    
	springLayout_r->putConstraint(SpringLayoutConstraints::NORTH_EDGE, newTabLabel_r, 2, SpringLayoutConstraints::NORTH_EDGE, newTabLabelPanel_r);  
    springLayout_r->putConstraint(SpringLayoutConstraints::EAST_EDGE, newTabLabel_r, -5, SpringLayoutConstraints::WEST_EDGE, CloseButtonPtr_r);
	springLayout_r->putConstraint(SpringLayoutConstraints::WEST_EDGE, newTabLabel_r, 2, SpringLayoutConstraints::WEST_EDGE, newTabLabelPanel_r);
	springLayout_r->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, newTabLabel_r, -2, SpringLayoutConstraints::SOUTH_EDGE, newTabLabelPanel_r);
	

	beginEditCP(newTabLabelPanel_r,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		newTabLabelPanel_r->setPreferredSize(Vec2f(120,20));
		newTabLabelPanel_r->getChildren().push_back(CloseButtonPtr_r);
		newTabLabelPanel_r->getChildren().push_back(newTabLabel_r);
		newTabLabelPanel_r->setLayout(springLayout_r);
	endEditCP(newTabLabelPanel_r,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
	

	
	TextAreaPtr newTextArea_r = osg::TextArea::create();
    newTextArea_r->setText(para);
	newTextArea_r->setEditable(true);
	        
    ScrollPanelPtr newTabContent_r = ScrollPanel::create();
    beginEditCP(newTabContent_r, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        newTabContent_r->setPreferredSize(Vec2f(200,1200));
        newTabContent_r->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(newTabContent_r, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	newTabContent_r->setViewComponent(newTextArea_r);


	beginEditCP(rightTabPanel,TabPanel::TabsFieldMask);
		rightTabPanel->addTab(newTabLabelPanel, newTabContent);
    endEditCP(rightTabPanel, TabPanel::TabsFieldMask);

    rightTabPanel->setSelectedIndex((rightTabPanel->getTabs().getSize())-1);

	beginEditCP(leftTabPanel,TabPanel::TabsFieldMask);
		leftTabPanel->addTab(newTabLabelPanel_r, newTabContent_r);
    endEditCP(leftTabPanel, TabPanel::TabsFieldMask);

	
    leftTabPanel->setSelectedIndex((leftTabPanel->getTabs().getSize())-1);
		
}

void ContentPanel::saveTextFile(Path file)
{
	std::ofstream outputFile((file.string()).c_str());

	ScrollPanelPtr toBeSavedScrollPanel = ScrollPanelPtr::dcast(leftTabPanel->getTabContents(leftTabPanel->getSelectedIndex()));
	TextAreaPtr toBeSavedTextArea = TextAreaPtr::dcast(toBeSavedScrollPanel->getViewComponent());
	
	std::string tobeSavedText = toBeSavedTextArea->getText();
	outputFile<<tobeSavedText;
	outputFile.close();
}

void ContentPanel::closeCurrentWindow()
{

	beginEditCP(leftTabPanel,TabPanel::TabsFieldMask);
		leftTabPanel->removeTab(leftTabPanel->getSelectedIndex());
    endEditCP(leftTabPanel, TabPanel::TabsFieldMask);

	beginEditCP(rightTabPanel,TabPanel::TabsFieldMask| TabPanel::TabContentsFieldMask | TabPanel::ChildrenFieldMask);
		rightTabPanel->removeTab(rightTabPanel->getSelectedIndex());
    endEditCP(rightTabPanel, TabPanel::TabsFieldMask|TabPanel::TabContentsFieldMask | TabPanel::ChildrenFieldMask);

}

void ContentPanel::createRightTabPanel()
{
	rightTabPanel= osg::TabPanel::create();
    beginEditCP(rightTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		rightTabPanel->setPreferredSize(Vec2f(1200,1200));
	    rightTabPanel->addTab(TabPanel1_r, TabContentA_r);
		rightTabPanel->setTabAlignment(0.5f);
        rightTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(rightTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    rightTabPanel->setSelectedIndex(0);
}

void ContentPanel::createLeftTabPanel()
{
	leftTabPanel= osg::TabPanel::create();
    beginEditCP(leftTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		leftTabPanel->setPreferredSize(Vec2f(1200,1200));
	    leftTabPanel->addTab(TabPanel1, TabContentA);
		leftTabPanel->setTabAlignment(0.5f);
        leftTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(leftTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    leftTabPanel->setSelectedIndex(0);
}

void ContentPanel::tempcreateDefaultTabs()
{
	TabPanel1 = osg::Label::create();

	// set the fields of the labels
	beginEditCP(TabPanel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::PreferredSizeFieldMask);
		TabPanel1->setPreferredSize(Vec2f(120,20));
        TabPanel1->setText("Welcome!");
        TabPanel1->setBorders(NullFC);
        TabPanel1->setBackgrounds(NullFC);
	endEditCP(TabPanel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::PreferredSizeFieldMask);
    
	// Create a StackTraceTextArea
	TextArea1 = osg::TextArea::create();
    TextArea1->setText("Hey Programmer!\n\n\n The following shortcuts also exists \n Ctrl+X\t-\t to execute Lua code \n Ctrl+1\t-\t To Focus on Lua Console TextArea \n Ctrl+S\t-\t for splitting the Content Panel \n\n You can now save/open files using the Debugging Interface\n Please DO NOT open files greater than 5KB.It is not efficiently coded and hence would take years to load.\n\n\n\t\tThank you!\n\n");
	TextArea1->setEditable(false);
        
    TabContentA = ScrollPanel::create();
    beginEditCP(TabContentA, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentA->setPreferredSize(Vec2f(200,1200));
        TabContentA->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TabContentA, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea1 to the ScrollPanel so it is displayed
	TabContentA->setViewComponent(TextArea1);


	TabPanel1_r = osg::Label::create();

	// set the fields of the labels
	beginEditCP(TabPanel1_r, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel1_r->setText("Screen2");
        TabPanel1_r->setBorders(NullFC);
        TabPanel1_r->setBackgrounds(NullFC);
	endEditCP(TabPanel1_r, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	// Create a StackTraceTextArea
	TextArea1_r = osg::TextArea::create();
    TextArea1_r->setText("This is the Second screen.\n\n Opening files now will open them in both screens.\n\n Pressing the \"Save file\" would only save the currently selected file in the left screen.\n\n\t\tThank you!\n\n");
	TextArea1_r->setEditable(false);
        
    TabContentA_r = ScrollPanel::create();
    beginEditCP(TabContentA_r, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentA_r->setPreferredSize(Vec2f(200,1200));
        TabContentA_r->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TabContentA_r, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea1_r to the ScrollPanel so it is displayed
	TabContentA_r->setViewComponent(TextArea1_r);

}


void ContentPanel::setIsSplit(bool value)
{
	isSplit = value;
	updatePanel();
}

bool ContentPanel::getIsSplit()
{
	return isSplit;
}
void ContentPanel::updatePanel()
{
	if(SplitPanelConstraints == NullFC)
	{
	SplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(SplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
		SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(SplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
	}

	beginEditCP(SplitPanelPtr(this), SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
	SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);

	this->setConstraints(SplitPanelConstraints);
	this->setMaxComponent(rightTabPanel);
	this->setDividerSize(5);
	this->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);

	if(isSplit)
	{
			this->setDividerPosition(.50); 
			this->setExpandable(true);
			this->setMaxDividerPosition(.85);
			this->setMinDividerPosition(.15);
			this->setMinComponent(leftTabPanel);
	}
	else
	{
			this->setDividerPosition(0); 
			this->setExpandable(true);
			this->setMaxDividerPosition(0);
			this->setMinDividerPosition(0);
			this->setMinComponent(leftTabPanel);
	}
	endEditCP(SplitPanelPtr(this), SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
	SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);

}
void ContentPanel::init()
{
	tempcreateDefaultTabs();
	createRightTabPanel();
	createLeftTabPanel();
	setIsSplit(false);
}

void ContentPanel::addTab()
{

}

void ContentPanel::removeTab(UInt32 tabno)
{

}
void ContentPanel::actionPerformed(const osg::ActionEventPtr e)
{
	//if(e->getSource()->getClassType() == osg::Button)
	//{
	ButtonPtr tempCloseButton = ButtonPtr::dcast(e->getSource());
	PanelPtr tempPanel = PanelPtr::dcast(tempCloseButton->getParentContainer());
	TabPanelPtr temptabpanel = TabPanelPtr::dcast(tempPanel->getParentContainer());
	UInt32 childindex = (temptabpanel->getChildIndex(tempPanel))/2;
	std::cout<<"chldindex:"<<childindex<<std::endl;
	
	beginEditCP(leftTabPanel,TabPanel::ChildrenFieldMask);
		leftTabPanel->removeTab(childindex);
	endEditCP(leftTabPanel,TabPanel::ChildrenFieldMask);

	beginEditCP(rightTabPanel,TabPanel::ChildrenFieldMask);
		rightTabPanel->removeTab(childindex);
	endEditCP(rightTabPanel,TabPanel::ChildrenFieldMask);

	//}
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

