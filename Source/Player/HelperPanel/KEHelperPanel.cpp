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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEHelperPanel.h"

#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include "Application/KEMainApplication.h"
#include <OpenSG/OSGSimpleAttachments.h>


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::HelperPanel
The HelperView.  
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HelperPanel::initMethod (void)
{
}


void HelperPanel::setupLuaTab()
{
	// Create a _CodeTextArea
    _CodeTextArea = osg::TextArea::create();
    _CodeTextArea->setText("");
	
    _LuaConsoleScrollPanel = ScrollPanel::create();
    beginEditCP(_LuaConsoleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _LuaConsoleScrollPanel->setPreferredSize(Vec2f(300,1200));
        _LuaConsoleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		endEditCP(_LuaConsoleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the _CodeTextArea to the ScrollPanel so it is displayed
	_LuaConsoleScrollPanel->setViewComponent(_CodeTextArea);

	
	_HistoryList = List::create();
	beginEditCP(_HistoryList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
	    _HistoryList->setPreferredSize(Vec2f(100, 100));
	    _HistoryList->setOrientation(List::VERTICAL_ORIENTATION);
		_HistoryList->setModel(_HistoryListModel);
	endEditCP(_HistoryList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);

	_HistoryList->setSelectionModel(_HistoryListSelectionModel);
	_HistoryList->addMouseListener(&_PlayerMouseListener);

	
	_HistoryScrollPanel = ScrollPanel::create();
	beginEditCP(_HistoryScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
		_HistoryScrollPanel->setPreferredSize(Vec2f(400,100));
		_HistoryScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
	endEditCP(_HistoryScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	_HistoryScrollPanel->setViewComponent(_HistoryList);
	
	
	_HistoryLabel = osg::Label::create();

	beginEditCP(_HistoryLabel, Label::TextFieldMask);
        _HistoryLabel->setText("History");
   	endEditCP(_HistoryLabel, Label::TextFieldMask);

	// the execute button
	_ExecuteBtn=osg::Button::create();

	beginEditCP(_ExecuteBtn,Button::TextFieldMask);
		_ExecuteBtn->setText("EXECUTE");
		_ExecuteBtn->setPreferredSize(Vec2f(90,25));
	endEditCP(_ExecuteBtn,Button::TextFieldMask);

	_ExecuteBtn->addActionListener(&_BasicListener);
    //Content Panel
	_LuaConsoleContent = osg::Panel::createEmpty();

	SpringLayoutPtr LuaConsoleContentLayout = osg::SpringLayout::create();

	LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _LuaConsoleScrollPanel, 0, SpringLayoutConstraints::NORTH_EDGE, _LuaConsoleContent);  
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _LuaConsoleScrollPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, _LuaConsoleContent); 
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _LuaConsoleScrollPanel, -5, SpringLayoutConstraints::WEST_EDGE, _HistoryScrollPanel);
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _LuaConsoleScrollPanel, 0, SpringLayoutConstraints::WEST_EDGE, _LuaConsoleContent);  

	LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _HistoryLabel, 5, SpringLayoutConstraints::NORTH_EDGE, _LuaConsoleContent);  
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HistoryLabel, -5, SpringLayoutConstraints::EAST_EDGE, _LuaConsoleContent);
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HistoryLabel, 0, SpringLayoutConstraints::WEST_EDGE, _HistoryScrollPanel);  

	LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _HistoryScrollPanel, 5, SpringLayoutConstraints::SOUTH_EDGE, _HistoryLabel);  
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _HistoryScrollPanel, -5, SpringLayoutConstraints::NORTH_EDGE, _ExecuteBtn); 
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HistoryScrollPanel, 0, SpringLayoutConstraints::EAST_EDGE, _LuaConsoleContent);

    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _ExecuteBtn, -5, SpringLayoutConstraints::SOUTH_EDGE, _LuaConsoleContent);
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _ExecuteBtn, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _HistoryScrollPanel);  

	beginEditCP(_LuaConsoleContent,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        _LuaConsoleContent->setLayout(LuaConsoleContentLayout);
        _LuaConsoleContent->getChildren().push_back(_LuaConsoleScrollPanel);
        _LuaConsoleContent->getChildren().push_back(_HistoryLabel);
        _LuaConsoleContent->getChildren().push_back(_HistoryScrollPanel);
        _LuaConsoleContent->getChildren().push_back(_ExecuteBtn);
	endEditCP(_LuaConsoleContent,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

}
void HelperPanel::setupErrorTab()
{
	// Create an _ErrorTextArea	
	_ErrorTextArea = osg::TextArea::create();
    _ErrorTextArea->setText("Error List");
	_ErrorTextArea->setEditable(false);
        
    _TabPanel2Content = ScrollPanel::create();
    beginEditCP(_TabPanel2Content, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _TabPanel2Content->setPreferredSize(Vec2f(200,1200));
        _TabPanel2Content->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_TabPanel2Content, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the _ErrorTextArea to the ScrollPanel so it is displayed
	_TabPanel2Content->setViewComponent(_ErrorTextArea);

}

void HelperPanel::setupTraceTab()
{
	// Create a _StackTraceTextArea
	_StackTraceTextArea = osg::TextArea::create();
    _StackTraceTextArea->setText("Stack Trace");
	_StackTraceTextArea->setEditable(false);
        
    _TabPanel3Content = ScrollPanel::create();
    beginEditCP(_TabPanel3Content, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        _TabPanel3Content->setPreferredSize(Vec2f(200,1200));
        _TabPanel3Content->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(_TabPanel3Content, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the _StackTraceTextArea to the ScrollPanel so it is displayed
	_TabPanel3Content->setViewComponent(_StackTraceTextArea);
}

void HelperPanel::createLoggingTab()
{
	//Text Area
    _LoggingArea = osg::TextArea::create();
	beginEditCP(_LoggingArea, TextArea::EditableFieldMask);
        _LoggingArea->setEditable(false);
	endEditCP(_LoggingArea, TextArea::EditableFieldMask);
	
    //Scroll Panel
    _LoggingScrollPanel = osg::ScrollPanel::create();
	beginEditCP(_LoggingScrollPanel, ScrollPanel::HorizontalResizePolicyFieldMask);
		_LoggingScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
	endEditCP(_LoggingScrollPanel, ScrollPanel::HorizontalResizePolicyFieldMask);
	_LoggingScrollPanel->setViewComponent(_LoggingArea);

    //Content Panel
	_LoggingContent = osg::Panel::createEmpty();

	SpringLayoutPtr LoggingContentLayout = osg::SpringLayout::create();

	LoggingContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _LoggingScrollPanel, 5, SpringLayoutConstraints::NORTH_EDGE, _LoggingContent);  
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _LoggingScrollPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, _LoggingContent); 
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _LoggingScrollPanel, -5, SpringLayoutConstraints::WEST_EDGE, _LoggingContent);
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _LoggingScrollPanel, 5, SpringLayoutConstraints::WEST_EDGE, _LoggingContent);  

	beginEditCP(_LoggingContent,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        _LoggingContent->setLayout(LoggingContentLayout);
        _LoggingContent->getChildren().push_back(_LoggingScrollPanel);
	endEditCP(_LoggingContent,Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
}

void HelperPanel::setupPropertiesTab()
{
	_TabPanel4Content = osg::Panel::create();

	_TabPanel4ContentLayout = osg::GridLayout::create();

    beginEditCP(_TabPanel4ContentLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
	    _TabPanel4ContentLayout->setRows(9);
        _TabPanel4ContentLayout->setColumns(2);
        _TabPanel4ContentLayout->setHorizontalGap(2);
        _TabPanel4ContentLayout->setVerticalGap(2);
    endEditCP(_TabPanel4ContentLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
	GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);


	_NodeNameLabel = Label::create();
    beginEditCP(_NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeNameLabel->setText("Name");
        _NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeNameValueLabel = Label::create();
    beginEditCP(_NodeNameValueLabel, Label::PreferredSizeFieldMask);
        _NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeNameValueLabel, Label::PreferredSizeFieldMask);

    _NodeCoreTypeLabel = Label::create();
    beginEditCP(_NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeCoreTypeLabel->setText("Core Type");
        _NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeCoreTypeValueLabel = Label::create();
    beginEditCP(_NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);
        _NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);

    _NodeMinLabel = Label::create();
    beginEditCP(_NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeMinLabel->setText("Min");
        _NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeMinValueLabel = Label::create();
    beginEditCP(_NodeMinValueLabel, Label::PreferredSizeFieldMask);
        _NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeMinValueLabel, Label::PreferredSizeFieldMask);

    _NodeMaxLabel = Label::create();
    beginEditCP(_NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeMaxLabel->setText("Max");
        _NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeMaxValueLabel = Label::create();
    beginEditCP(_NodeMaxValueLabel, Label::PreferredSizeFieldMask);
        _NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeMaxValueLabel, Label::PreferredSizeFieldMask);

    _NodeCenterLabel = Label::create();
    beginEditCP(_NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeCenterLabel->setText("Center");
        _NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeCenterValueLabel = Label::create();
    beginEditCP(_NodeCenterValueLabel, Label::PreferredSizeFieldMask);
        _NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeCenterValueLabel, Label::PreferredSizeFieldMask);

    _NodeTriCountLabel = Label::create();
    beginEditCP(_NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeTriCountLabel->setText("TriCount");
        _NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeTriCountValueLabel = Label::create();
    beginEditCP(_NodeTriCountValueLabel, Label::PreferredSizeFieldMask);
        _NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeTriCountValueLabel, Label::PreferredSizeFieldMask);

    _NodeTravMaskLabel = Label::create();
    beginEditCP(_NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeTravMaskLabel->setText("Traversal Mask");
        _NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeTravMaskValueLabel = Label::create();
    beginEditCP(_NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);
        _NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);

    _NodeOcclusionMaskLabel = Label::create();
    beginEditCP(_NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeOcclusionMaskLabel->setText("Occlusion Mask");
        _NodeOcclusionMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeOcclusionMaskValueLabel = Label::create();
    beginEditCP(_NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);
        _NodeOcclusionMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);

    _NodeActiveLabel = Label::create();
    beginEditCP(_NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        _NodeActiveLabel->setText("Active");
        _NodeActiveLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(_NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    _NodeActiveValueLabel = Label::create();
    beginEditCP(_NodeActiveValueLabel, Label::PreferredSizeFieldMask);
        _NodeActiveValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(_NodeActiveValueLabel, Label::PreferredSizeFieldMask);
	
	beginEditCP(_TabPanel4Content,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
        _TabPanel4Content->setPreferredSize(Vec2f(100.0f, 200.0f));
        _TabPanel4Content->setLayout(_TabPanel4ContentLayout);
        _TabPanel4Content->getChildren().push_back(_NodeNameLabel);
        _TabPanel4Content->getChildren().push_back(_NodeNameValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeCoreTypeLabel);
        _TabPanel4Content->getChildren().push_back(_NodeCoreTypeValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeMinLabel);
        _TabPanel4Content->getChildren().push_back(_NodeMinValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeMaxLabel);
        _TabPanel4Content->getChildren().push_back(_NodeMaxValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeCenterLabel);
        _TabPanel4Content->getChildren().push_back(_NodeCenterValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeTriCountLabel);
        _TabPanel4Content->getChildren().push_back(_NodeTriCountValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeTravMaskLabel);
        _TabPanel4Content->getChildren().push_back(_NodeTravMaskValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeOcclusionMaskLabel);
        _TabPanel4Content->getChildren().push_back(_NodeOcclusionMaskValueLabel);
        _TabPanel4Content->getChildren().push_back(_NodeActiveLabel);
        _TabPanel4Content->getChildren().push_back(_NodeActiveValueLabel);
	endEditCP(_TabPanel4Content,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);

}

void HelperPanel::setupInfoTabLabels()
{
	_TabPanel1Label = osg::Label::create();
    _TabPanel2Label = osg::Label::create();
    _TabPanel3Label = osg::Label::create();
	_TabPanel4Label = osg::Label::create();
	_LoggingContentLabel = osg::Label::create();

	// set the fields of the labels
	beginEditCP(_TabPanel1Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _TabPanel1Label->setText("Lua Console");
        _TabPanel1Label->setBorders(NullFC);
        _TabPanel1Label->setBackgrounds(NullFC);
	endEditCP(_TabPanel1Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	beginEditCP(_TabPanel2Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _TabPanel2Label->setText("Error");
        _TabPanel2Label->setBorders(NullFC);
        _TabPanel2Label->setBackgrounds(NullFC);
    endEditCP(_TabPanel2Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	
	LuaManager::the()->addLuaListener(&_LuaErrorListener);
        
    beginEditCP(_TabPanel3Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _TabPanel3Label->setText("Stack");
        _TabPanel3Label->setBorders(NullFC);
        _TabPanel3Label->setBackgrounds(NullFC);
    endEditCP(_TabPanel3Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	beginEditCP(_TabPanel4Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _TabPanel4Label->setText("Properties");
        _TabPanel4Label->setBorders(NullFC);
        _TabPanel4Label->setBackgrounds(NullFC);
    endEditCP(_TabPanel4Label, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	beginEditCP(_LoggingContentLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        _LoggingContentLabel->setText("Logging");
        _LoggingContentLabel->setBorders(NullFC);
        _LoggingContentLabel->setBackgrounds(NullFC);
    endEditCP(_LoggingContentLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);

}
void HelperPanel::setupInfoTabPanel()
{
	setupInfoTabLabels();	//TabPanel(1,2,3,4)
	setupLuaTab();			//_LuaConsoleScrollPanel
	setupErrorTab();		//_TabPanel2Content
	setupTraceTab();		//_TabPanel3Content
	setupPropertiesTab();	//_TabPanel4Content
    createLoggingTab();     //LoggingTab

	_InfoTabPanel= osg::TabPanel::create();
    beginEditCP(_InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		_InfoTabPanel->setPreferredSize(Vec2f(1200,200));
	    _InfoTabPanel->addTab(_TabPanel1Label, _LuaConsoleContent);
        _InfoTabPanel->addTab(_TabPanel2Label, _TabPanel2Content);
        _InfoTabPanel->addTab(_TabPanel3Label, _TabPanel3Content);
		_InfoTabPanel->addTab(_TabPanel4Label, _TabPanel4Content);
		_InfoTabPanel->addTab(_LoggingContentLabel, _LoggingContent);
		_InfoTabPanel->setTabAlignment(0.5f);
        _InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(_InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    _InfoTabPanel->setSelectedIndex(0);
}

void HelperPanel::updateListBox(void)
{
	_HistoryListModel->clear();
	
	for(int i=_ListOfCommands.size()-1;i>=0;i--)
	{
		_HistoryListModel->pushBack(boost::any(_ListOfCommands[i]));
	}

	
	std::cout<<std::endl;
}

void HelperPanel::setupHistoryList()
{
	ListSelectionModelPtr _HistoryListSelectionModel(new DefaultListSelectionModel);

	
	_HistoryListModel = DefaultListModel::create();

	updateListBox();

}

void HelperPanel::setupRest()
{
	_Layout = osg::SpringLayout::create();

	_Layout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _InfoTabPanel, 5, SpringLayoutConstraints::NORTH_EDGE, HelperPanelPtr(this));  
    _Layout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _InfoTabPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, HelperPanelPtr(this)); 
    _Layout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _InfoTabPanel, -5, SpringLayoutConstraints::EAST_EDGE, HelperPanelPtr(this));
    _Layout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _InfoTabPanel, 5, SpringLayoutConstraints::WEST_EDGE, HelperPanelPtr(this));  
	
	beginEditCP(HelperPanelPtr(this), Panel::ChildrenFieldMask | Panel::BordersFieldMask | Panel::LayoutFieldMask);
		this->getChildren().push_back(_InfoTabPanel);
        this->setLayout(_Layout);
        this->setBorders(NullFC);
    endEditCP(HelperPanelPtr(this), Panel::ChildrenFieldMask | Panel::BordersFieldMask | Panel::LayoutFieldMask);

	MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&_PlayerKeyListener2);
}

void HelperPanel::viewTab(UInt32)
{

}
void HelperPanel::hideTab(UInt32)
{

}


void HelperPanel::setLabelValuesToNull()
{
	    beginEditCP(_NodeNameValueLabel, Label::TextFieldMask);
           _NodeNameValueLabel->setText("");
        endEditCP(_NodeNameValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeCoreTypeValueLabel, Label::TextFieldMask);
            _NodeCoreTypeValueLabel->setText("");
        endEditCP(_NodeCoreTypeValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeMinValueLabel, Label::TextFieldMask);
            _NodeMinValueLabel->setText("");
        endEditCP(_NodeMinValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeMaxValueLabel, Label::TextFieldMask);
            _NodeMaxValueLabel->setText("");
        endEditCP(_NodeMaxValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeCenterValueLabel, Label::TextFieldMask);
            _NodeCenterValueLabel->setText("");
        endEditCP(_NodeCenterValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeTriCountValueLabel, Label::TextFieldMask);
            _NodeTriCountValueLabel->setText("");
        endEditCP(_NodeTriCountValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeTravMaskValueLabel, Label::TextFieldMask);
            _NodeTravMaskValueLabel->setText("");
        endEditCP(_NodeTravMaskValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeOcclusionMaskValueLabel, Label::TextFieldMask);
            _NodeOcclusionMaskValueLabel->setText("");
        endEditCP(_NodeOcclusionMaskValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeActiveValueLabel, Label::TextFieldMask);
            _NodeActiveValueLabel->setText("");
        endEditCP(_NodeActiveValueLabel, Label::TextFieldMask);
}


void HelperPanel::setLabelValues(NodePtr _SelectedNode)
{
		const Char8 *_NodeName = getName(_SelectedNode);

		beginEditCP(_NodeNameValueLabel, Label::TextFieldMask);
            if(_NodeName == NULL)
            {
                _NodeNameValueLabel->setText("Unnamed Node");
            }
            else
            {
                _NodeNameValueLabel->setText(_NodeName);
            }
        endEditCP(_NodeNameValueLabel, Label::TextFieldMask);
	
        beginEditCP(_NodeCoreTypeValueLabel, Label::TextFieldMask);
            _NodeCoreTypeValueLabel->setText(_SelectedNode->getCore()->getType().getCName());
        endEditCP(_NodeCoreTypeValueLabel, Label::TextFieldMask);
		

        DynamicVolume _DyVol;
        _SelectedNode->getWorldVolume(_DyVol);
        Pnt3f Min,Max,Center;
        _DyVol.getBounds(Min,Max);
        _DyVol.getCenter(Center);

        std::string _TempText("");

        _TempText = boost::lexical_cast<std::string>(Min.x()) + ", " +boost::lexical_cast<std::string>(Min.x()) + ", " + boost::lexical_cast<std::string>(Min.x());
        beginEditCP(_NodeMinValueLabel, Label::TextFieldMask);
            _NodeMinValueLabel->setText(_TempText);
        endEditCP(_NodeMinValueLabel, Label::TextFieldMask);

        _TempText = boost::lexical_cast<std::string>(Max.x()) + ", " +boost::lexical_cast<std::string>(Max.x()) + ", " + boost::lexical_cast<std::string>(Max.x());
        beginEditCP(_NodeMaxValueLabel, Label::TextFieldMask);
            _NodeMaxValueLabel->setText(_TempText);
        endEditCP(_NodeMaxValueLabel, Label::TextFieldMask);

        _TempText = boost::lexical_cast<std::string>(Center.x()) + ", " +boost::lexical_cast<std::string>(Center.x()) + ", " + boost::lexical_cast<std::string>(Center.x());
        beginEditCP(_NodeCenterValueLabel, Label::TextFieldMask);
            _NodeCenterValueLabel->setText(_TempText);
        endEditCP(_NodeCenterValueLabel, Label::TextFieldMask);

        GeometryPrimitivesCounter PrimCounter;
        PrimCounter(_SelectedNode);
        beginEditCP(_NodeTriCountValueLabel, Label::TextFieldMask);
            _NodeTriCountValueLabel->setText(boost::lexical_cast<std::string>(PrimCounter.getTriCount()));
        endEditCP(_NodeTriCountValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeTravMaskValueLabel, Label::TextFieldMask);
            _NodeTravMaskValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getTravMask()));
        endEditCP(_NodeTravMaskValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeOcclusionMaskValueLabel, Label::TextFieldMask);
            _NodeOcclusionMaskValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getOcclusionMask()));
        endEditCP(_NodeOcclusionMaskValueLabel, Label::TextFieldMask);

        beginEditCP(_NodeActiveValueLabel, Label::TextFieldMask);
            _NodeActiveValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getActive()));
        endEditCP(_NodeActiveValueLabel, Label::TextFieldMask);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/


HelperPanel::HelperPanel(void) :
    Inherited(),
	_BasicListener(HelperPanelPtr(this)),
	_PlayerKeyListener2(HelperPanelPtr(this)),
	_PlayerMouseListener(HelperPanelPtr(this)),
	_LuaErrorListener(HelperPanelPtr(this))
{
	
}

HelperPanel::HelperPanel(const HelperPanel &source) :
    Inherited(source),
	_BasicListener(HelperPanelPtr(this)),
	_PlayerKeyListener2(HelperPanelPtr(this)),
	_PlayerMouseListener(HelperPanelPtr(this)),
	_LuaErrorListener(HelperPanelPtr(this))
{
}


HelperPanel::~HelperPanel(void)
{
		MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_PlayerKeyListener2);
		//MainApplication::the()->getMainWindowEventProducer()->removeMouseListener(&_PlayerMouseListener);
}


void HelperPanel::BasicListener::actionPerformed(const ActionEventPtr e)
{
    _HelperPanel->actionPerformed(e);
}

void HelperPanel::actionPerformed(const ActionEventPtr e)
{
	if(e->getSource() == _ExecuteBtn)
	{
		LuaManager::the()->runScript(std::string(_CodeTextArea->getText()));
		_ListOfCommands.push_back(std::string(_CodeTextArea->getText()));
		updateListBox();
	}
}

void HelperPanel::PlayerKeyListener2::keyTyped(const KeyEventPtr e)
{
    _HelperPanel->keyTyped2(e);
}

void HelperPanel::PlayerMouseListener::mouseClicked(const MouseEventPtr e)
{
   if(e->getClickCount() == 2)
   {
	   if(_HelperPanel->_HistoryListModel->getSize()>0 && !_HelperPanel->_HistoryList->getSelectionModel()->isSelectionEmpty())
	   {
		   
		UInt32 _SelectedItemIndex(_HelperPanel->_HistoryList->getSelectionModel()->getMinSelectionIndex());
		std::string _Temp = std::string(_HelperPanel->_CodeTextArea->getText());
		_Temp+="\n"+boost::any_cast<std::string>(_HelperPanel->_HistoryListModel->getElementAt(_SelectedItemIndex));
		beginEditCP(_HelperPanel->_CodeTextArea,TextArea::TextFieldMask);		
		_HelperPanel->_CodeTextArea->setText(_Temp);
		endEditCP(_HelperPanel->_CodeTextArea,TextArea::TextFieldMask);		
		
	   }
	   else
	   {
		   std::cout<<"no item in list"<<std::endl;
	   }
		//std::cout<<"mouse was double clicked on:"<<e->getSource();
   }
}

void HelperPanel::keyTyped2(const KeyEventPtr e)
{
	if(e->getKey() == KeyEvent::KEY_X && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
	{
		LuaManager::the()->runScript(std::string(_CodeTextArea->getText()));
		_ListOfCommands.push_back(std::string(_CodeTextArea->getText()));
		updateListBox();
	}
	//if(e->getKey() == KeyEvent::KEY_C && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
	//{
	//	//MainInternalWindow->setFocusedComponent(_CodeTextArea); // need to get the access to the maininternal window.. 
	//	_InfoTabPanel->setSelectedIndex(0);
	//}
}


HelperPanel::LuaErrorListener::LuaErrorListener(HelperPanelPtr TheHelperPanel)
{
	_HelperPanel=TheHelperPanel;
}

HelperPanel::BasicListener::BasicListener(HelperPanelPtr TheHelperPanel)
{
	_HelperPanel=TheHelperPanel;
}

HelperPanel::PlayerKeyListener2::PlayerKeyListener2(HelperPanelPtr TheHelperPanel)
{
	_HelperPanel=TheHelperPanel;
}

HelperPanel::PlayerMouseListener::PlayerMouseListener(HelperPanelPtr TheHelperPanel)
{
	_HelperPanel=TheHelperPanel;
}


void HelperPanel::LuaErrorListener::error(const LuaErrorEventPtr e)
{
    std::string ErrorType("");
    switch(e->getStatus())
    {
        case LUA_ERRSYNTAX:
            //Syntax Error
            ErrorType = "Lua Syntax Error";
            break;
        case LUA_ERRMEM:
            //Memory Allocation Error
            ErrorType = "Lua Memory Allocation Error";
            break;
        case LUA_ERRRUN:
            //Memory Allocation Error
            ErrorType = "Lua Runtime Error";
            break;
        case LUA_ERRERR:
            //Memory Allocation Error
            ErrorType = "Lua Error in Error Handler";
            break;
        default:
            //Unknown
            ErrorType = "Lua Unknown Error";
            break;
    }
    _HelperPanel->_ErrorTextArea->clear();
    if(_HelperPanel->_ErrorTextArea->getText().size() != 0)
    {
        _HelperPanel->_ErrorTextArea->write("\n");
    }
    _HelperPanel->_ErrorTextArea->write(ErrorType + ":\n    " + e->getErrorString());

    //Select the Error Tab
    _HelperPanel->_InfoTabPanel->setSelectedIndex(1);

    //Fill Stack Trace
    if(e->getStackTraceEnabled() && 
            (e->getStatus() == LUA_ERRMEM ||
             e->getStatus() == LUA_ERRERR ||
             e->getStatus() == LUA_ERRRUN))
    {
        std::stringstream ss;
        ss << "Lua Stack Trace: " << std::endl;

        MFString::StorageType::const_iterator ListItor(e->getMFStackTrace()->begin());
        for(; ListItor != e->getMFStackTrace()->end() ; ++ListItor)
        {
            ss << "     " << (*ListItor) << std::endl;
        }
        _HelperPanel->_StackTraceTextArea->clear();
        _HelperPanel->_StackTraceTextArea->write(ss.str());
    }
}

/*----------------------------- class specific ----------------------------*/

void HelperPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void HelperPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump HelperPanel NI" << std::endl;
}


OSG_END_NAMESPACE

