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
#include "Player/KEApplicationPlayer.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include "Application/KEMainApplication.h"
#include <OpenSG/OSGNameAttachment.h>

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
    _CodeTextArea = OSG::TextArea::create();
    _CodeTextArea->setText("");

    _LuaConsoleScrollPanel = ScrollPanel::create();
    _LuaConsoleScrollPanel->setPreferredSize(Vec2f(300,1200));
    _LuaConsoleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _CodeTextArea to the ScrollPanel so it is displayed
    _LuaConsoleScrollPanel->setViewComponent(_CodeTextArea);


    _HistoryList = List::create();
    _HistoryList->setPreferredSize(Vec2f(100, 100));
    _HistoryList->setOrientation(List::VERTICAL_ORIENTATION);
    _HistoryList->setModel(_HistoryListModel);

    _HistoryList->setSelectionModel(_HistoryListSelectionModel);
    _HistoryList->addMouseListener(&_PlayerMouseListener);


    _HistoryScrollPanel = ScrollPanel::create();
    _HistoryScrollPanel->setPreferredSize(Vec2f(400,100));
    _HistoryScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    _HistoryScrollPanel->setViewComponent(_HistoryList);


    _HistoryLabel = OSG::Label::create();

    _HistoryLabel->setText("History");

    // the execute button
    _ExecuteBtn=OSG::Button::create();

    _ExecuteBtn->setText("EXECUTE");
    _ExecuteBtn->setPreferredSize(Vec2f(90,25));

    _ExecuteBtn->addActionListener(&_BasicListener);
    //Content Panel
    _LuaConsoleContent = OSG::Panel::createEmpty();

    SpringLayoutRefPtr LuaConsoleContentLayout = OSG::SpringLayout::create();

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

    _LuaConsoleContent->setLayout(LuaConsoleContentLayout);
    _LuaConsoleContent->pushToChildren(_LuaConsoleScrollPanel);
    _LuaConsoleContent->pushToChildren(_HistoryLabel);
    _LuaConsoleContent->pushToChildren(_HistoryScrollPanel);
    _LuaConsoleContent->pushToChildren(_ExecuteBtn);

}
void HelperPanel::setupErrorTab()
{
    // Create an _ErrorTextArea	
    _ErrorTextArea = OSG::TextArea::create();
    _ErrorTextArea->setText("Error List");
    _ErrorTextArea->setEditable(false);

    _TabPanel2Content = ScrollPanel::create();
    _TabPanel2Content->setPreferredSize(Vec2f(200,1200));
    _TabPanel2Content->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _ErrorTextArea to the ScrollPanel so it is displayed
    _TabPanel2Content->setViewComponent(_ErrorTextArea);

}

void HelperPanel::setupTraceTab()
{
    // Create a _StackTraceTextArea
    _StackTraceTextArea = OSG::TextArea::create();
    _StackTraceTextArea->setText("Stack Trace");
    _StackTraceTextArea->setEditable(false);

    _TabPanel3Content = ScrollPanel::create();
    _TabPanel3Content->setPreferredSize(Vec2f(200,1200));
    _TabPanel3Content->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _StackTraceTextArea to the ScrollPanel so it is displayed
    _TabPanel3Content->setViewComponent(_StackTraceTextArea);
}

void HelperPanel::createLoggingTab()
{
    //Text Area
    _LoggingArea = OSG::TextArea::create();
    _LoggingArea->setEditable(false);

    //Scroll Panel
    _LoggingScrollPanel = OSG::ScrollPanel::create();
    _LoggingScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    _LoggingScrollPanel->setViewComponent(_LoggingArea);

    //Content Panel
    _LoggingContent = OSG::Panel::createEmpty();

    SpringLayoutRefPtr LoggingContentLayout = OSG::SpringLayout::create();

    LoggingContentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _LoggingScrollPanel, 5, SpringLayoutConstraints::NORTH_EDGE, _LoggingContent);  
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _LoggingScrollPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, _LoggingContent); 
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _LoggingScrollPanel, -5, SpringLayoutConstraints::WEST_EDGE, _LoggingContent);
    LoggingContentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _LoggingScrollPanel, 5, SpringLayoutConstraints::WEST_EDGE, _LoggingContent);  

    _LoggingContent->setLayout(LoggingContentLayout);
    _LoggingContent->pushToChildren(_LoggingScrollPanel);
}

void HelperPanel::setupPropertiesTab()
{
    _TabPanel4Content = OSG::Panel::create();

    _TabPanel4ContentLayout = OSG::GridLayout::create();

    _TabPanel4ContentLayout->setRows(9);
    _TabPanel4ContentLayout->setColumns(2);
    _TabPanel4ContentLayout->setHorizontalGap(2);
    _TabPanel4ContentLayout->setVerticalGap(2);


    _NodeNameLabel = Label::create();
    _NodeNameLabel->setText("Name");
    _NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeNameValueLabel = Label::create();
    _NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeCoreTypeLabel = Label::create();
    _NodeCoreTypeLabel->setText("Core Type");
    _NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeCoreTypeValueLabel = Label::create();
    _NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeMinLabel = Label::create();
    _NodeMinLabel->setText("Min");
    _NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeMinValueLabel = Label::create();
    _NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeMaxLabel = Label::create();
    _NodeMaxLabel->setText("Max");
    _NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeMaxValueLabel = Label::create();
    _NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeCenterLabel = Label::create();
    _NodeCenterLabel->setText("Center");
    _NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeCenterValueLabel = Label::create();
    _NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeTriCountLabel = Label::create();
    _NodeTriCountLabel->setText("TriCount");
    _NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeTriCountValueLabel = Label::create();
    _NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeTravMaskLabel = Label::create();
    _NodeTravMaskLabel->setText("Traversal Mask");
    _NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeTravMaskValueLabel = Label::create();
    _NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeOcclusionMaskLabel = Label::create();
    _NodeOcclusionMaskLabel->setText("Occlusion Mask");
    _NodeOcclusionMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeOcclusionMaskValueLabel = Label::create();
    _NodeOcclusionMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _NodeActiveLabel = Label::create();
    _NodeActiveLabel->setText("Active");
    _NodeActiveLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    _NodeActiveValueLabel = Label::create();
    _NodeActiveValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    _TabPanel4Content->setPreferredSize(Vec2f(100.0f, 200.0f));
    _TabPanel4Content->setLayout(_TabPanel4ContentLayout);
    _TabPanel4Content->pushToChildren(_NodeNameLabel);
    _TabPanel4Content->pushToChildren(_NodeNameValueLabel);
    _TabPanel4Content->pushToChildren(_NodeCoreTypeLabel);
    _TabPanel4Content->pushToChildren(_NodeCoreTypeValueLabel);
    _TabPanel4Content->pushToChildren(_NodeMinLabel);
    _TabPanel4Content->pushToChildren(_NodeMinValueLabel);
    _TabPanel4Content->pushToChildren(_NodeMaxLabel);
    _TabPanel4Content->pushToChildren(_NodeMaxValueLabel);
    _TabPanel4Content->pushToChildren(_NodeCenterLabel);
    _TabPanel4Content->pushToChildren(_NodeCenterValueLabel);
    _TabPanel4Content->pushToChildren(_NodeTriCountLabel);
    _TabPanel4Content->pushToChildren(_NodeTriCountValueLabel);
    _TabPanel4Content->pushToChildren(_NodeTravMaskLabel);
    _TabPanel4Content->pushToChildren(_NodeTravMaskValueLabel);
    _TabPanel4Content->pushToChildren(_NodeOcclusionMaskLabel);
    _TabPanel4Content->pushToChildren(_NodeOcclusionMaskValueLabel);
    _TabPanel4Content->pushToChildren(_NodeActiveLabel);
    _TabPanel4Content->pushToChildren(_NodeActiveValueLabel);

}

void HelperPanel::setupInfoTabLabels()
{
    _TabPanel1Label = OSG::Label::create();
    _TabPanel2Label = OSG::Label::create();
    _TabPanel3Label = OSG::Label::create();
    _TabPanel4Label = OSG::Label::create();
    _LoggingContentLabel = OSG::Label::create();

    // set the fields of the labels
    _TabPanel1Label->setText("Lua Console");
    _TabPanel1Label->setBorders(NULL);
    _TabPanel1Label->setBackgrounds(NULL);

    _TabPanel2Label->setText("Error");
    _TabPanel2Label->setBorders(NULL);
    _TabPanel2Label->setBackgrounds(NULL);

    LuaManager::the()->addLuaListener(&_LuaErrorListener);

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
    setupLuaTab();			//_LuaConsoleScrollPanel
    setupErrorTab();		//_TabPanel2Content
    setupTraceTab();		//_TabPanel3Content
    setupPropertiesTab();	//_TabPanel4Content
    createLoggingTab();     //LoggingTab

    _InfoTabPanel= OSG::TabPanel::create();
    _InfoTabPanel->setPreferredSize(Vec2f(1200,200));
    _InfoTabPanel->addTab(_TabPanel1Label, _LuaConsoleContent);
    _InfoTabPanel->addTab(_TabPanel2Label, _TabPanel2Content);
    _InfoTabPanel->addTab(_TabPanel3Label, _TabPanel3Content);
    _InfoTabPanel->addTab(_TabPanel4Label, _TabPanel4Content);
    _InfoTabPanel->addTab(_LoggingContentLabel, _LoggingContent);
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
    ListSelectionModelPtr _HistoryListSelectionModel(new DefaultListSelectionModel);


    _HistoryListModel = DefaultListModel::create();

    updateListBox();

}

void HelperPanel::setupRest()
{
    _Layout = OSG::SpringLayout::create();

    _Layout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _InfoTabPanel, 5, SpringLayoutConstraints::NORTH_EDGE, HelperPanelRefPtr(this));  
    _Layout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _InfoTabPanel, -5, SpringLayoutConstraints::SOUTH_EDGE, HelperPanelRefPtr(this)); 
    _Layout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _InfoTabPanel, -5, SpringLayoutConstraints::EAST_EDGE, HelperPanelRefPtr(this));
    _Layout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _InfoTabPanel, 5, SpringLayoutConstraints::WEST_EDGE, HelperPanelRefPtr(this));  

    this->pushToChildren(_InfoTabPanel);
    this->setLayout(_Layout);
    this->setBorders(NULL);

    MainApplication::the()->getMainWindow()->addKeyListener(&_PlayerKeyListener2);
}

void HelperPanel::viewTab(UInt32)
{

}
void HelperPanel::hideTab(UInt32)
{

}


void HelperPanel::setLabelValuesToNull()
{
    _NodeNameValueLabel->setText("");

    _NodeCoreTypeValueLabel->setText("");

    _NodeMinValueLabel->setText("");

    _NodeMaxValueLabel->setText("");

    _NodeCenterValueLabel->setText("");

    _NodeTriCountValueLabel->setText("");

    _NodeTravMaskValueLabel->setText("");

    _NodeOcclusionMaskValueLabel->setText("");

    _NodeActiveValueLabel->setText("");
}


void HelperPanel::setLabelValues(NodeRefPtr _SelectedNode)
{
    const Char8 *_NodeName = getName(_SelectedNode);

    if(_NodeName == NULL)
    {
        _NodeNameValueLabel->setText("Unnamed Node");
    }
    else
    {
        _NodeNameValueLabel->setText(_NodeName);
    }

    _NodeCoreTypeValueLabel->setText(_SelectedNode->getCore()->getType().getCName());


    BoxVolume _DyVol;
    _SelectedNode->getWorldVolume(_DyVol);
    Pnt3f Min,Max,Center;
    _DyVol.getBounds(Min,Max);
    _DyVol.getCenter(Center);

    std::string _TempText("");

    _TempText = boost::lexical_cast<std::string>(Min.x()) + ", " +boost::lexical_cast<std::string>(Min.x()) + ", " + boost::lexical_cast<std::string>(Min.x());
    _NodeMinValueLabel->setText(_TempText);

    _TempText = boost::lexical_cast<std::string>(Max.x()) + ", " +boost::lexical_cast<std::string>(Max.x()) + ", " + boost::lexical_cast<std::string>(Max.x());
    _NodeMaxValueLabel->setText(_TempText);

    _TempText = boost::lexical_cast<std::string>(Center.x()) + ", " +boost::lexical_cast<std::string>(Center.x()) + ", " + boost::lexical_cast<std::string>(Center.x());
    _NodeCenterValueLabel->setText(_TempText);

    //GeometryPrimitivesCounter PrimCounter;
    //PrimCounter(_SelectedNode);
    //_NodeTriCountValueLabel->setText(boost::lexical_cast<std::string>(PrimCounter.getTriCount()));

    _NodeTravMaskValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getTravMask()));

    //_NodeOcclusionMaskValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getOcclusionMask()));

    //_NodeActiveValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getActive()));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HelperPanel::HelperPanel(void) :
    Inherited(),
    _BasicListener(HelperPanelRefPtr(this)),
    _PlayerKeyListener2(HelperPanelRefPtr(this)),
    _PlayerMouseListener(HelperPanelRefPtr(this)),
    _LuaErrorListener(HelperPanelRefPtr(this))

{
}

HelperPanel::HelperPanel(const HelperPanel &source) :
    Inherited(source),
    _BasicListener(HelperPanelRefPtr(this)),
    _PlayerKeyListener2(HelperPanelRefPtr(this)),
    _PlayerMouseListener(HelperPanelRefPtr(this)),
    _LuaErrorListener(HelperPanelRefPtr(this))

{
}

HelperPanel::~HelperPanel(void)
{
    MainApplication::the()->getMainWindow()->removeKeyListener(&_PlayerKeyListener2);
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

void HelperPanel::BasicListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _HelperPanel->actionPerformed(e);
}

void HelperPanel::actionPerformed(const ActionEventUnrecPtr e)
{
    if(e->getSource() == _ExecuteBtn)
    {
        LuaManager::the()->runScript(std::string(_CodeTextArea->getText()));
        _ListOfCommands.push_back(std::string(_CodeTextArea->getText()));
        updateListBox();
    }
}

void HelperPanel::PlayerKeyListener2::keyTyped(const KeyEventUnrecPtr e)
{
    _HelperPanel->keyTyped2(e);
}

void HelperPanel::PlayerMouseListener::mouseClicked(const MouseEventUnrecPtr e)
{
    if(e->getClickCount() == 2)
    {
        if(_HelperPanel->_HistoryListModel->getSize()>0 && !_HelperPanel->_HistoryList->getSelectionModel()->isSelectionEmpty())
        {

            UInt32 _SelectedItemIndex(_HelperPanel->_HistoryList->getSelectionModel()->getMinSelectionIndex());
            std::string _Temp = std::string(_HelperPanel->_CodeTextArea->getText());
            _Temp+="\n"+boost::any_cast<std::string>(_HelperPanel->_HistoryListModel->getElementAt(_SelectedItemIndex));
            _HelperPanel->_CodeTextArea->setText(_Temp);

        }
    }
}

void HelperPanel::keyTyped2(const KeyEventUnrecPtr e)
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


HelperPanel::LuaErrorListener::LuaErrorListener(HelperPanelRefPtr TheHelperPanel)
{
    _HelperPanel=TheHelperPanel;
}

HelperPanel::BasicListener::BasicListener(HelperPanelRefPtr TheHelperPanel)
{
    _HelperPanel=TheHelperPanel;
}

HelperPanel::PlayerKeyListener2::PlayerKeyListener2(HelperPanelRefPtr TheHelperPanel)
{
    _HelperPanel=TheHelperPanel;
}

HelperPanel::PlayerMouseListener::PlayerMouseListener(HelperPanelRefPtr TheHelperPanel)
{
    _HelperPanel=TheHelperPanel;
}


void HelperPanel::LuaErrorListener::error(const LuaErrorEventUnrecPtr e)
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

OSG_END_NAMESPACE
