
#include <stdlib.h>
#include <stdio.h>

#include "helperView.h"

OSG_USING_NAMESPACE



void HelperView::setupLuaTab()
{
	// Create a CodeTextArea
    CodeTextArea = osg::TextArea::create();
    CodeTextArea->setText("");
	
    TabContentA = ScrollPanel::create();
    beginEditCP(TabContentA, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentA->setPreferredSize(Vec2f(300,1200));
        TabContentA->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		endEditCP(TabContentA, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the CodeTextArea to the ScrollPanel so it is displayed
	TabContentA->setViewComponent(CodeTextArea);

}
void HelperView::setupErrorTab()
{
	// Create an ErrorTextArea	
	ErrorTextArea = osg::TextArea::create();
    ErrorTextArea->setText("Error List");
	ErrorTextArea->setEditable(false);
        
    TabContentB = ScrollPanel::create();
    beginEditCP(TabContentB, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentB->setPreferredSize(Vec2f(200,1200));
        TabContentB->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TabContentB, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the ErrorTextArea to the ScrollPanel so it is displayed
	TabContentB->setViewComponent(ErrorTextArea);

}
void HelperView::setupTraceTab()
{
	// Create a StackTraceTextArea
	StackTraceTextArea = osg::TextArea::create();
    StackTraceTextArea->setText("Stack Trace");
	StackTraceTextArea->setEditable(false);
        
    TabContentC = ScrollPanel::create();
    beginEditCP(TabContentC, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TabContentC->setPreferredSize(Vec2f(200,1200));
        TabContentC->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TabContentC, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the StackTraceTextArea to the ScrollPanel so it is displayed
	TabContentC->setViewComponent(StackTraceTextArea);
}
void HelperView::setupPropertiesTab()
{
	TabContentD = osg::Panel::create();

	GridLayoutPtr TabContentDLayout = osg::GridLayout::create();

    beginEditCP(TabContentDLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
	    TabContentDLayout->setRows(9);
        TabContentDLayout->setColumns(2);
        TabContentDLayout->setHorizontalGap(2);
        TabContentDLayout->setVerticalGap(2);
    endEditCP(TabContentDLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
	GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);


	NodeNameLabel = Label::create();
    beginEditCP(NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeNameLabel->setText("Name");
        NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeNameValueLabel = Label::create();
    beginEditCP(NodeNameValueLabel, Label::PreferredSizeFieldMask);
        NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeNameValueLabel, Label::PreferredSizeFieldMask);

    NodeCoreTypeLabel = Label::create();
    beginEditCP(NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeCoreTypeLabel->setText("Core Type");
        NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeCoreTypeValueLabel = Label::create();
    beginEditCP(NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);
        NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);

    NodeMinLabel = Label::create();
    beginEditCP(NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeMinLabel->setText("Min");
        NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeMinValueLabel = Label::create();
    beginEditCP(NodeMinValueLabel, Label::PreferredSizeFieldMask);
        NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeMinValueLabel, Label::PreferredSizeFieldMask);

    NodeMaxLabel = Label::create();
    beginEditCP(NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeMaxLabel->setText("Max");
        NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeMaxValueLabel = Label::create();
    beginEditCP(NodeMaxValueLabel, Label::PreferredSizeFieldMask);
        NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeMaxValueLabel, Label::PreferredSizeFieldMask);

    NodeCenterLabel = Label::create();
    beginEditCP(NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeCenterLabel->setText("Center");
        NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeCenterValueLabel = Label::create();
    beginEditCP(NodeCenterValueLabel, Label::PreferredSizeFieldMask);
        NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeCenterValueLabel, Label::PreferredSizeFieldMask);

    NodeTriCountLabel = Label::create();
    beginEditCP(NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeTriCountLabel->setText("TriCount");
        NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeTriCountValueLabel = Label::create();
    beginEditCP(NodeTriCountValueLabel, Label::PreferredSizeFieldMask);
        NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeTriCountValueLabel, Label::PreferredSizeFieldMask);

    NodeTravMaskLabel = Label::create();
    beginEditCP(NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeTravMaskLabel->setText("Traversal Mask");
        NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeTravMaskValueLabel = Label::create();
    beginEditCP(NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);
        NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);

    NodeOcclusionMaskLabel = Label::create();
    beginEditCP(NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeOcclusionMaskLabel->setText("Occlusion Mask");
        NodeOcclusionMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeOcclusionMaskValueLabel = Label::create();
    beginEditCP(NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);
        NodeOcclusionMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);

    NodeActiveLabel = Label::create();
    beginEditCP(NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeActiveLabel->setText("Active");
        NodeActiveLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeActiveValueLabel = Label::create();
    beginEditCP(NodeActiveValueLabel, Label::PreferredSizeFieldMask);
        NodeActiveValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeActiveValueLabel, Label::PreferredSizeFieldMask);
	
	beginEditCP(TabContentD,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
        TabContentD->setPreferredSize(Vec2f(100.0f, 200.0f));
        TabContentD->setLayout(TabContentDLayout);
        TabContentD->getChildren().push_back(NodeNameLabel);
        TabContentD->getChildren().push_back(NodeNameValueLabel);
        TabContentD->getChildren().push_back(NodeCoreTypeLabel);
        TabContentD->getChildren().push_back(NodeCoreTypeValueLabel);
        TabContentD->getChildren().push_back(NodeMinLabel);
        TabContentD->getChildren().push_back(NodeMinValueLabel);
        TabContentD->getChildren().push_back(NodeMaxLabel);
        TabContentD->getChildren().push_back(NodeMaxValueLabel);
        TabContentD->getChildren().push_back(NodeCenterLabel);
        TabContentD->getChildren().push_back(NodeCenterValueLabel);
        TabContentD->getChildren().push_back(NodeTriCountLabel);
        TabContentD->getChildren().push_back(NodeTriCountValueLabel);
        TabContentD->getChildren().push_back(NodeTravMaskLabel);
        TabContentD->getChildren().push_back(NodeTravMaskValueLabel);
        TabContentD->getChildren().push_back(NodeOcclusionMaskLabel);
        TabContentD->getChildren().push_back(NodeOcclusionMaskValueLabel);
        TabContentD->getChildren().push_back(NodeActiveLabel);
        TabContentD->getChildren().push_back(NodeActiveValueLabel);
	endEditCP(TabContentD,Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);

}

void HelperView::setupInfoTabLabels()
{
	TabPanel1 = osg::Label::create();
    TabPanel2 = osg::Label::create();
    TabPanel3 = osg::Label::create();
	TabPanel4 = osg::Label::create();

	// set the fields of the labels
	beginEditCP(TabPanel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel1->setText("Lua Console");
        TabPanel1->setBorders(NullFC);
        TabPanel1->setBackgrounds(NullFC);
	endEditCP(TabPanel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	beginEditCP(TabPanel2, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel2->setText("Error");
        TabPanel2->setBorders(NullFC);
        TabPanel2->setBackgrounds(NullFC);
    endEditCP(TabPanel2, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
	LuaManager::the()->addLuaListener(&_LuaErrorListener);
        
    beginEditCP(TabPanel3, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel3->setText("Stack");
        TabPanel3->setBorders(NullFC);
        TabPanel3->setBackgrounds(NullFC);
    endEditCP(TabPanel3, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
	beginEditCP(TabPanel4, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        TabPanel4->setText("Properties");
        TabPanel4->setBorders(NullFC);
        TabPanel4->setBackgrounds(NullFC);
    endEditCP(TabPanel4, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);

}
void HelperView::setupInfoTabPanel()
{
	setupInfoTabLabels();	//TabPanel(1,2,3,4)
	setupLuaTab();			//TabContentA
	setupErrorTab();		//TabContentB
	setupTraceTab();		//TabContentC
	setupPropertiesTab();	//TabContentD

	InfoTabPanel= osg::TabPanel::create();
    beginEditCP(InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		InfoTabPanel->setPreferredSize(Vec2f(1200,200));
	    InfoTabPanel->addTab(TabPanel1, TabContentA);
        InfoTabPanel->addTab(TabPanel2, TabContentB);
        InfoTabPanel->addTab(TabPanel3, TabContentC);
		InfoTabPanel->addTab(TabPanel4, TabContentD);
		InfoTabPanel->setTabAlignment(0.5f);
        InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
	endEditCP(InfoTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    InfoTabPanel->setSelectedIndex(0);
}

void HelperView::updateListBox(void)
{
	HistoryListModel->clear();
	
	for(int i=list_of_commands.size()-1;i>=0;i--)
	{
		HistoryListModel->pushBack(boost::any(list_of_commands[i]));
	}
	std::cout<<std::endl;
}

void HelperView::setupHistoryList()
{
	ListSelectionModelPtr HistoryListSelectionModel(new DefaultListSelectionModel);

	HistoryListModel = DefaultListModel::create();

	updateListBox();
	
	HistoryList = List::create();
	beginEditCP(HistoryList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
	    HistoryList->setPreferredSize(Vec2f(100, 100));
	    HistoryList->setOrientation(List::VERTICAL_ORIENTATION);
		HistoryList->setModel(HistoryListModel);
	endEditCP(HistoryList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);

	HistoryList->setSelectionModel(HistoryListSelectionModel);

	HistoryScrollPanel = ScrollPanel::create();
	beginEditCP(HistoryScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
		HistoryScrollPanel->setPreferredSize(Vec2f(100,100));
		HistoryScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
	endEditCP(HistoryScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	HistoryScrollPanel->setViewComponent(HistoryList);
	
	historyLabel = osg::Label::create();

	beginEditCP(historyLabel, Label::TextFieldMask);
        historyLabel->setText("History");
   	endEditCP(historyLabel, Label::TextFieldMask);

}

void HelperView::setupRest()
{
	// the execute button
	executeBtn=osg::Button::create();

	beginEditCP(executeBtn,Button::TextFieldMask);
		executeBtn->setText("EXECUTE");
		executeBtn->setPreferredSize(Vec2f(100,30));
	endEditCP(executeBtn,Button::TextFieldMask);

	executeBtn->addActionListener(&_BasicListener);

	UInt32 SPACE_FOR_BUTTON = 200;

    // OverlayLayout has no options to edit!
    beginEditCP(PanelFlowLayout);
        // NOTHING : )
    endEditCP(PanelFlowLayout); 

	// SplitPanelPanel is the panel which holds everything that the helper view contains
	SplitPanelPanel = osg::Panel::create();
	PanelFlowLayout = osg::SpringLayout::create();

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InfoTabPanel, 5, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InfoTabPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, SplitPanelPanel); 
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InfoTabPanel, -1*SPACE_FOR_BUTTON, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InfoTabPanel, 5, SpringLayoutConstraints::WEST_EDGE, SplitPanelPanel);  

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, historyLabel, 5, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, historyLabel, 25, SpringLayoutConstraints::NORTH_EDGE, SplitPanelPanel); 
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, historyLabel, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, historyLabel, 5, SpringLayoutConstraints::EAST_EDGE, InfoTabPanel);  

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, HistoryScrollPanel, 5, SpringLayoutConstraints::SOUTH_EDGE, historyLabel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, HistoryScrollPanel, -5, SpringLayoutConstraints::NORTH_EDGE, executeBtn); 
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, HistoryScrollPanel, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, HistoryScrollPanel, 5, SpringLayoutConstraints::EAST_EDGE, InfoTabPanel);  

	PanelFlowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, executeBtn, 15, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, executeBtn, -15, SpringLayoutConstraints::SOUTH_EDGE, SplitPanelPanel);
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, executeBtn, -5, SpringLayoutConstraints::EAST_EDGE, SplitPanelPanel);  
    PanelFlowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, executeBtn, 5, SpringLayoutConstraints::EAST_EDGE, InfoTabPanel);  
    
	
	beginEditCP(SplitPanelPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		SplitPanelPanel->getChildren().push_back(InfoTabPanel);
		SplitPanelPanel->getChildren().push_back(historyLabel);
		SplitPanelPanel->getChildren().push_back(HistoryScrollPanel);		
		SplitPanelPanel->getChildren().push_back(executeBtn);
        SplitPanelPanel->setLayout(PanelFlowLayout);
    endEditCP(SplitPanelPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

}

void HelperView::viewTab(UInt32)
{

}
void HelperView::hideTab(UInt32)
{

}

HelperView::HelperView(): 
_BasicListener(HelperViewPtr(this)),
_PlayerKeyListener(HelperViewPtr(this))
{
	setupInfoTabPanel();
	setupHistoryList();
	setupRest();
	MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&_PlayerKeyListener);
}

HelperView::HelperView(const HelperView &source): 
_BasicListener(HelperViewPtr(this)),
_PlayerKeyListener(HelperViewPtr(this))
{
}


HelperView::~HelperView()
{
	MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_PlayerKeyListener);
}

void HelperView::BasicListener::actionPerformed(const ActionEventPtr e)
{
    _HelperView->actionPerformed(e);
}

void HelperView::actionPerformed(const ActionEventPtr e)
{
	if(e->getSource() == executeBtn)
	{
		LuaManager::the()->runScript(std::string(CodeTextArea->getText()));
		list_of_commands.push_back(std::string(CodeTextArea->getText()));
		updateListBox();
	}
}

void HelperView::PlayerKeyListener::keyTyped(const KeyEventPtr e)
{
    _HelperView->keyTyped(e);
}

void HelperView::keyTyped(const KeyEventPtr e)
{
	if(e->getKey() == KeyEvent::KEY_X && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
	{
		LuaManager::the()->runScript(std::string(CodeTextArea->getText()));
		list_of_commands.push_back(std::string(CodeTextArea->getText()));
		updateListBox();
	}
	if(e->getKey() == KeyEvent::KEY_C && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
	{
		//MainInternalWindow->setFocusedComponent(CodeTextArea); // need to get the access to the maininternal window.. 
		InfoTabPanel->setSelectedIndex(0);
	}
}


HelperView::LuaErrorListener::LuaErrorListener(HelperViewPtr TheHelperView)
{
	_HelperView=TheHelperView;
}

void HelperView::LuaErrorListener::error(const LuaErrorEventPtr e)
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
    _HelperView->ErrorTextArea->clear();
    if(_HelperView->ErrorTextArea->getText().size() != 0)
    {
        _HelperView->ErrorTextArea->write("\n");
    }
    _HelperView->ErrorTextArea->write(ErrorType + ":\n    " + e->getErrorString());

    //Select the Error Tab
    _HelperView->InfoTabPanel->setSelectedIndex(1);

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
        _HelperView->StackTraceTextArea->clear();
        _HelperView->StackTraceTextArea->write(ss.str());
    }
}

