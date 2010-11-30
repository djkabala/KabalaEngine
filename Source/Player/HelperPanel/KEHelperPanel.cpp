/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEHelperPanel.h"
#include "KELogListModel.h"
#include "KELogListComponentGenerator.h"
#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include "Application/KEMainApplication.h"
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGTextArea.h>
#include <OpenSG/OSGList.h>
#include <OpenSG/OSGSpringLayout.h>
#include <OpenSG/OSGSpringLayoutConstraints.h>
#include <OpenSG/OSGDefaultListModel.h>
#include <OpenSG/OSGTabPanel.h>
#include <OpenSG/OSGScrollPanel.h>
#include <OpenSG/OSGTextEditor.h>
#include <OpenSG/OSGTextDomArea.h>
#include <OpenSG/OSGAdvancedTextDomArea.h>
#include <OpenSG/OSGTextDomLayoutManager.h>
#include <OpenSG/OSGGlyphView.h>
#include <OpenSG/OSGDocument.h>

#ifdef OSG_WITH_LUA_DEBUGGER
#include <OpenSG/OSGLuaIntrospectionTreeModel.h>
#include <OpenSG/OSGLuaIntrospectionComponentGenerator.h>
#include <OpenSG/OSGTree.h>
#include <OpenSG/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/OSGBorderLayout.h>
#include <OpenSG/OSGBorderLayoutConstraints.h>
#include <OpenSG/OSGSplitPanel.h>
#endif

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHelperPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGHelperPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HelperPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void HelperPanel::setupLuaTab()
{
    // Create a _CodeTextArea
    _CodeTextArea = AdvancedTextDomArea::create();
	_CodeTextArea->setText("print(\"hello world\");");
    //_CodeTextArea->setIsSplit(false);
	//_CodeTextArea->setClipboardVisible(false);
	_CodeTextArea->setPreferredSize(Vec2f(200,1200));
    setName(_CodeTextArea,"__KABALA_ENGINE_PLAYER_CODE_TEXT_AREA");

    /*_LuaConsoleScrollPanel = ScrollPanel::create();
    _LuaConsoleScrollPanel->setPreferredSize(Vec2f(300,1200));
    _LuaConsoleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _CodeTextArea to the ScrollPanel so it is displayed
    _LuaConsoleScrollPanel->setViewComponent(_CodeTextArea);*/


    _HistoryList = List::create();
    _HistoryList->setPreferredSize(Vec2f(100, 100));
    _HistoryList->setOrientation(List::VERTICAL_ORIENTATION);
    _HistoryList->setModel(_HistoryListModel);

    _HistoryListMouseClickedConnection = _HistoryList->connectMouseClicked(boost::bind(&HelperPanel::handleHistoryListMouseClicked, this, _1));


    _HistoryScrollPanel = ScrollPanel::create();
    _HistoryScrollPanel->setPreferredSize(Vec2f(400,100));
    _HistoryScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    _HistoryScrollPanel->setViewComponent(_HistoryList);


    _HistoryLabel = Label::create();

    _HistoryLabel->setText("History");

    // the execute button
    _ExecuteBtn=Button::create();

    _ExecuteBtn->setText("Execute");
    _ExecuteBtn->setPreferredSize(Vec2f(90,25));

    _ExecuteScriptActionConnection = _ExecuteBtn->connectActionPerformed(boost::bind(&HelperPanel::handleExecuteScriptAction, this, _1));
    //Content Panel
    _LuaConsoleContent = Panel::createEmpty();

    SpringLayoutRefPtr LuaConsoleContentLayout = SpringLayout::create();

    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _CodeTextArea, 0, SpringLayoutConstraints::NORTH_EDGE, _LuaConsoleContent);  
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _CodeTextArea, 0, SpringLayoutConstraints::SOUTH_EDGE, _LuaConsoleContent); 
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _CodeTextArea, -5, SpringLayoutConstraints::WEST_EDGE, _HistoryScrollPanel);
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _CodeTextArea, 0, SpringLayoutConstraints::WEST_EDGE, _LuaConsoleContent);  

    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _HistoryLabel, 5, SpringLayoutConstraints::NORTH_EDGE, _LuaConsoleContent);  
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HistoryLabel, -5, SpringLayoutConstraints::EAST_EDGE, _LuaConsoleContent);
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HistoryLabel, 0, SpringLayoutConstraints::WEST_EDGE, _HistoryScrollPanel);  

    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _HistoryScrollPanel, 5, SpringLayoutConstraints::SOUTH_EDGE, _HistoryLabel);  
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _HistoryScrollPanel, -5, SpringLayoutConstraints::NORTH_EDGE, _ExecuteBtn); 
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HistoryScrollPanel, 0, SpringLayoutConstraints::EAST_EDGE, _LuaConsoleContent);

    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _ExecuteBtn, -5, SpringLayoutConstraints::SOUTH_EDGE, _LuaConsoleContent);
    LuaConsoleContentLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _ExecuteBtn, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _HistoryScrollPanel);  

    _LuaConsoleContent->setLayout(LuaConsoleContentLayout);
    _LuaConsoleContent->pushToChildren(_CodeTextArea);
    _LuaConsoleContent->pushToChildren(_HistoryLabel);
    _LuaConsoleContent->pushToChildren(_HistoryScrollPanel);
    _LuaConsoleContent->pushToChildren(_ExecuteBtn);

}
void HelperPanel::setupErrorTab()
{
    // Create an _ErrorTextArea	
    _ErrorTextArea = AdvancedTextDomArea::create();
    _ErrorTextArea->setText("Error List");
    _ErrorTextArea->setEditable(false);
	//_ErrorTextArea->setIsSplit(false);
	//_ErrorTextArea->setClipboardVisible(false);
	_ErrorTextArea->setPreferredSize(Vec2f(200,1200));
    setName(_ErrorTextArea,"__KABALA_ENGINE_PLAYER_ERROR_TEXT_AREA");

    //_TabPanel2Content = ScrollPanel::create();
    //_TabPanel2Content->setPreferredSize(Vec2f(200,1200));
    //_TabPanel2Content->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //// Add the _ErrorTextArea to the ScrollPanel so it is displayed
    //_TabPanel2Content->setViewComponent(_ErrorTextArea);

}

void HelperPanel::setupTraceTab()
{
    // Create a _StackTraceTextArea
    _StackTraceTextArea = AdvancedTextDomArea::create();
    _StackTraceTextArea->setText("Stack Trace");
    _StackTraceTextArea->setEditable(false);
	//_StackTraceTextArea->setIsSplit(false);
	//_StackTraceTextArea->setClipboardVisible(false);

    //_TabPanel3Content = ScrollPanel::create();
    //_TabPanel3Content->setPreferredSize(Vec2f(200,1200));
    //_TabPanel3Content->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //// Add the _StackTraceTextArea to the ScrollPanel so it is displayed
    //_TabPanel3Content->setViewComponent(_StackTraceTextArea);
}

void HelperPanel::createLoggingTab()
{   
    //Logging List Component Generator
	LogListComponentGeneratorRecPtr LoggingCompGenerator = LogListComponentGenerator::create();

    //Logging Model
	LogListModelRecPtr LoggingModel = LogListModel::create();
    LoggingModel->connectLogging();

    ListRecPtr _LoggingList = List::create();
    _LoggingList->setPreferredSize(Vec2f(200, 300));
    _LoggingList->setOrientation(List::VERTICAL_ORIENTATION);
	_LoggingList->setModel(LoggingModel);
	_LoggingList->setCellGenerator(LoggingCompGenerator);
	_LoggingList->setSelectable(false);

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    _LoggingScrollPanel = ScrollPanel::create();
    _LoggingScrollPanel->setPreferredSize(Vec2f(200,300));
    _LoggingScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    _LoggingScrollPanel->setViewComponent(_LoggingList);

    //Content Panel
    _LoggingContent = Panel::createEmpty();

    SpringLayoutRefPtr LoggingContentLayout = SpringLayout::create();

    LoggingContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _LoggingScrollPanel, 5, SpringLayoutConstraints::NORTH_EDGE, _LoggingContent);  
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _LoggingScrollPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, _LoggingContent); 
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _LoggingScrollPanel, -5, SpringLayoutConstraints::EAST_EDGE, _LoggingContent);
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _LoggingScrollPanel, 5, SpringLayoutConstraints::WEST_EDGE, _LoggingContent);  

    _LoggingContent->setLayout(LoggingContentLayout);
    _LoggingContent->pushToChildren(_LoggingScrollPanel);
}

void HelperPanel::setupPropertiesTab()
{
    _TabPanel4Content = Panel::create();

    SpringLayoutRefPtr TabPanel4ContentLayout = SpringLayout::create();

    _NodeEditor = FieldContainerEditorFactory::the()->createDefaultEditor(_TabPanel4Content, _ApplicationPlayer->getCommandManager());
    ScrollPanelRefPtr NodeEditorScrollPanel = ScrollPanel::create();
    NodeEditorScrollPanel->setPreferredSize(Vec2f(450,400));
    NodeEditorScrollPanel->setViewComponent(_NodeEditor);

    _CoreEditor = FieldContainerEditorFactory::the()->createDefaultEditor(_TabPanel4Content, _ApplicationPlayer->getCommandManager());
    ScrollPanelRefPtr CoreEditorScrollPanel = ScrollPanel::create();
    CoreEditorScrollPanel->setPreferredSize(Vec2f(450,400));
    CoreEditorScrollPanel->setViewComponent(_CoreEditor);


    TabPanel4ContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, NodeEditorScrollPanel, 5, SpringLayoutConstraints::NORTH_EDGE, _TabPanel4Content);  
    TabPanel4ContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, NodeEditorScrollPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, _TabPanel4Content); 
    TabPanel4ContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, NodeEditorScrollPanel, -15, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _TabPanel4Content);
    
    TabPanel4ContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CoreEditorScrollPanel, 5, SpringLayoutConstraints::NORTH_EDGE, _TabPanel4Content);  
    TabPanel4ContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CoreEditorScrollPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, _TabPanel4Content); 
    TabPanel4ContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CoreEditorScrollPanel, 15, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _TabPanel4Content);  

    _TabPanel4Content->setPreferredSize(Vec2f(100.0f, 200.0f));
    _TabPanel4Content->setLayout(TabPanel4ContentLayout);
    _TabPanel4Content->pushToChildren(NodeEditorScrollPanel);
    _TabPanel4Content->pushToChildren(CoreEditorScrollPanel);

}

void HelperPanel::setupInfoTabLabels()
{
    _TabPanel1Label = Label::create();
    _TabPanel2Label = Label::create();
    _TabPanel3Label = Label::create();
    _TabPanel4Label = Label::create();
    _LoggingContentLabel = Label::create();

    // set the fields of the labels
    _TabPanel1Label->setText("Lua Console");
    _TabPanel1Label->setBorders(NULL);
    _TabPanel1Label->setBackgrounds(NULL);

    _TabPanel2Label->setText("Error");
    _TabPanel2Label->setBorders(NULL);
    _TabPanel2Label->setBackgrounds(NULL);

    _LuaErrorConnection = LuaManager::the()->connectLuaError(boost::bind(&HelperPanel::handleLuaError, this, _1));

    _TabPanel3Label->setText("Stack");
    _TabPanel3Label->setBorders(NULL);
    _TabPanel3Label->setBackgrounds(NULL);

    _TabPanel4Label->setText("Properties");
    _TabPanel4Label->setBorders(NULL);
    _TabPanel4Label->setBackgrounds(NULL);

    _LoggingContentLabel->setText("Logging");
    _LoggingContentLabel->setBorders(NULL);
    _LoggingContentLabel->setBackgrounds(NULL);

}
void HelperPanel::setupInfoTabPanel()
{
    setupInfoTabLabels();	//TabPanel(1,2,3,4)
    setupLuaTab();			//_CodeTextArea
    setupErrorTab();		//_TabPanel2Content
    setupTraceTab();		//_TabPanel3Content
    setupPropertiesTab();	//_TabPanel4Content
    createLoggingTab();     //LoggingTab

    _InfoTabPanel= TabPanel::create();
    _InfoTabPanel->setPreferredSize(Vec2f(1200,200));
    _InfoTabPanel->addTab(_TabPanel1Label, _LuaConsoleContent);
    _InfoTabPanel->addTab(_TabPanel2Label, _ErrorTextArea);
    _InfoTabPanel->addTab(_TabPanel3Label, _StackTraceTextArea);
    _InfoTabPanel->addTab(_TabPanel4Label, _TabPanel4Content);
    _InfoTabPanel->addTab(_LoggingContentLabel, _LoggingContent);
#ifdef OSG_WITH_LUA_DEBUGGER
    createIntrospectionTreeTab(_InfoTabPanel);
#endif
    _InfoTabPanel->setTabAlignment(0.5f);
    _InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    _InfoTabPanel->setSelectedIndex(0);
}

void HelperPanel::updateListBox(void)
{
    _HistoryListModel->clear();

    for(int i=_ListOfCommands.size()-1;i>=0;i--)
    {
        _HistoryListModel->pushBack(boost::any(_ListOfCommands[i]));
    }

}

void HelperPanel::setupHistoryList()
{
    _HistoryListModel = DefaultListModel::create();

    updateListBox();

}

void HelperPanel::setupRest()
{
    _Layout = SpringLayout::create();

    _Layout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _InfoTabPanel, 5, SpringLayoutConstraints::NORTH_EDGE, this);  
    _Layout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _InfoTabPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, this); 
    _Layout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _InfoTabPanel, -5, SpringLayoutConstraints::EAST_EDGE, this);
    _Layout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _InfoTabPanel, 5, SpringLayoutConstraints::WEST_EDGE, this);  

    pushToChildren(_InfoTabPanel);
    setLayout(_Layout);
    setBorders(NULL);
}

void HelperPanel::viewTab(UInt32)
{

}
void HelperPanel::hideTab(UInt32)
{

}

#ifdef OSG_WITH_LUA_DEBUGGER

void HelperPanel::createIntrospectionTreeTab(TabPanel* const tabPanel)
{
    BorderLayoutConstraintsRefPtr CenterConstraints = OSG::BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    BorderLayoutConstraintsRefPtr NorthConstraints = OSG::BorderLayoutConstraints::create();
    NorthConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);


    _GlobalLuaIntroTreeModel = LuaIntrospectionTreeModel::create();
    _GlobalLuaIntroTreeModel->setRoot("");

    LuaIntrospectionComponentGeneratorRecPtr LuaIntroTreeComponentGenerator = LuaIntrospectionComponentGenerator::create();

    //Create the Tree
    TreeRecPtr TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(200, 500));
    TheTree->setModel(_GlobalLuaIntroTreeModel);
    TheTree->setCellGenerator(LuaIntroTreeComponentGenerator);

    //Layout Expansion
    TheTree->expandPath(_GlobalLuaIntroTreeModel->getRootPath());

    //Create a scroll panel for the tree
    ScrollPanelRefPtr TreeScrollPanel = ScrollPanel::create();
    TreeScrollPanel->setPreferredSize(Vec2f(200,300));
    TreeScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    TreeScrollPanel->setViewComponent(TheTree);
    TreeScrollPanel->setConstraints(CenterConstraints);

    //Global Label
    LabelRecPtr GlobalTreeLabel = Label::create();
    GlobalTreeLabel->setText("Global");
    GlobalTreeLabel->setConstraints(NorthConstraints);

    BorderLayoutRecPtr BorderPanelLayout = BorderLayout::create();

    //Global Panel
    PanelRecPtr GlobalLuaTreePanel = Panel::createEmpty();
    GlobalLuaTreePanel->pushToChildren(GlobalTreeLabel);
    GlobalLuaTreePanel->pushToChildren(TreeScrollPanel);
    GlobalLuaTreePanel->setLayout(BorderPanelLayout);

    //Local Label
    LabelRecPtr LocalTreeLabel = Label::create();
    LocalTreeLabel->setText("Local");
    LocalTreeLabel->setConstraints(NorthConstraints);

    //Local Panel
    PanelRecPtr LocalLuaTreePanel = Panel::createEmpty();
    LocalLuaTreePanel->pushToChildren(LocalTreeLabel);
    LocalLuaTreePanel->setLayout(BorderPanelLayout);

    //Global/Local Split Panel
    SplitPanelRecPtr GlocalLocalSplitPanel = SplitPanel::create();
    GlocalLocalSplitPanel->setMinComponent(GlobalLuaTreePanel);
    GlocalLocalSplitPanel->setMaxComponent(LocalLuaTreePanel);
    GlocalLocalSplitPanel->setDividerPosition(0.5f);
    GlocalLocalSplitPanel->setDividerSize(5);
    GlocalLocalSplitPanel->setMinDividerPosition(.1);
    GlocalLocalSplitPanel->setMaxDividerPosition(.9);
    

    //Add the Panel to the TabPanel
    LabelRefPtr IntrospectionTreeTabLabel = Label::create();
    IntrospectionTreeTabLabel->setText("Lua Introspection");
    IntrospectionTreeTabLabel->setBorders(NULL);
    IntrospectionTreeTabLabel->setBackgrounds(NULL);

    tabPanel->addTab(IntrospectionTreeTabLabel, GlocalLocalSplitPanel);
}

#endif

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void HelperPanel::resolveLinks(void)
{
    Inherited::resolveLinks();
	SpringLayoutRefPtr _Layout;

    _ApplicationPlayer = NULL;
	_HistoryLabel = NULL;
	_HistoryList = NULL;
	_HistoryListModel = NULL;
	_HistoryScrollPanel = NULL;
	_ExecuteBtn = NULL;
	_InfoTabPanel = NULL;
	_CodeTextArea = NULL;
	_ErrorTextArea = NULL;
	_StackTraceTextArea = NULL;
	_TabPanel1Label = NULL;
	_TabPanel2Label = NULL;
	_TabPanel3Label = NULL;
	_TabPanel4Label = NULL;
	_LuaConsoleContent = NULL;
	_LuaConsoleScrollPanel = NULL;
	_TabPanel2Content = NULL;
	_TabPanel3Content = NULL;
	_TabPanel4Content = NULL;
    _NodeEditor = NULL;
    _CoreEditor = NULL;
	_LoggingContentLabel = NULL;
	_LoggingContent = NULL;
	_LoggingArea = NULL;
	_LoggingScrollPanel = NULL;

    _LuaErrorConnection.disconnect();
    _ExecuteScriptActionConnection.disconnect();
    _HistoryListMouseClickedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

HelperPanel::HelperPanel(void) :
    Inherited()
{
}

HelperPanel::HelperPanel(const HelperPanel &source) :
    Inherited(source)
{
}

HelperPanel::~HelperPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HelperPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HelperPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump HelperPanel NI" << std::endl;
}

void HelperPanel::handleExecuteScriptAction(ActionEventDetails* const details)
{
    if(details->getSource() == _ExecuteBtn)
    {
        LuaManager::the()->runScript(std::string(_CodeTextArea->getText()));
        _ListOfCommands.push_back(std::string(_CodeTextArea->getText()));
        updateListBox();
    }
}

void HelperPanel::handleHistoryListMouseClicked(MouseEventDetails* const details)
{
    if(details->getClickCount() == 2)
    {
        if(_HistoryListModel->getSize()>0 && !_HistoryList->getSelectionModel()->isSelectionEmpty())
        {

            UInt32 _SelectedItemIndex(_HistoryList->getSelectionModel()->getMinSelectionIndex());
            std::string _Temp = std::string(_CodeTextArea->getText());
            _Temp+="\n"+boost::any_cast<std::string>(_HistoryListModel->getElementAt(_SelectedItemIndex));
            _CodeTextArea->setText(_Temp);

        }
    }
}

void HelperPanel::handleLuaError(LuaErrorEventDetails* const details)
{
    std::string ErrorType("");
    switch(details->getStatus())
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
    _ErrorTextArea->clear();
    _ErrorTextArea->write(ErrorType + ":\n    " + details->getErrorString() + "\r\n");

    //Select the Error Tab
    _InfoTabPanel->setSelectedIndex(1);

    //Fill Stack Trace
    if(details->getStackTraceEnabled() && 
       (details->getStatus() == LUA_ERRMEM ||
        details->getStatus() == LUA_ERRERR ||
        details->getStatus() == LUA_ERRRUN))
    {
        std::stringstream ss;
        ss << "Lua Stack Trace: " << std::endl;

        MFString::StorageType::const_iterator ListItor(details->getMFStackTrace()->begin());
        for(; ListItor != details->getMFStackTrace()->end() ; ++ListItor)
        {
            ss << "     " << (*ListItor) << std::endl;
        }
        _StackTraceTextArea->clear();
        _StackTraceTextArea->write(ss.str() + "\r\n");
    }
}

void HelperPanel::setApplicationPlayer(ApplicationPlayer* const TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void HelperPanel::updateSelectedNode(void)
{
    NodeRecPtr SelNode(_ApplicationPlayer->getSelectedNode());
    if(SelNode == NULL)
    {
        _NodeEditor->dettachFieldContainer();
        _CoreEditor->dettachFieldContainer();
    }
    else
    {
        _NodeEditor->attachFieldContainer(SelNode);
        _CoreEditor->attachFieldContainer(SelNode->getCore());
    }
}

OSG_END_NAMESPACE
