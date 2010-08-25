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

#include "KEContentPanel.h"
#include <OpenSG/OSGInternalWindow.h>
#include <OpenSG/OSGTitlebar.h>
#include "Player/KEApplicationPlayer.h"
#include <OpenSG/OSGSetFieldValueCommand.h>
#include <OpenSG/OSGMathFieldTraits.h>
#include <OpenSG/OSGSplitPanel.h>
#include <OpenSG/OSGSpringLayout.h>
#include <OpenSG/OSGSpringLayoutConstraints.h>
#include <OpenSG/OSGScrollPanel.h>
#include <OpenSG/OSGTextArea.h>
#include <OpenSG/OSGCardLayout.h>
#include <OpenSG/OSGTabPanel.h>
#include <sstream>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGContentPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGContentPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ContentPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ContentPanel::addTabWithText(BoostPath file)
{

    PanelRefPtr _NewLeftTabLabelPanel = Panel::createEmpty();

    ButtonRefPtr _NewLeftTabLabelCloseButtonRefPtr =
        dynamic_pointer_cast<Button>(dynamic_cast<InternalWindow*>(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());

    //ButtonRefPtr _NewLeftTabLabelCloseButtonRefPtr = Button::create();

    _NewLeftTabLabelCloseButtonRefPtr->setPreferredSize(Vec2f(100,20));
    _NewLeftTabLabelCloseButtonRefPtr->setText("X");

    _CloseLeftButtonActionConnection = _NewLeftTabLabelCloseButtonRefPtr->connectActionPerformed(boost::bind(&ContentPanel::handleCloseButtonAction, this, _1));

    LabelRefPtr _NewLeftTabLabelLabel=Label::create();
    _NewLeftTabLabelLabel->setText(file.leaf());
    _NewLeftTabLabelLabel->setBorders(NULL);
    _NewLeftTabLabelLabel->setBackgrounds(NULL);

    SpringLayoutRefPtr _NewLeftTabLabelPanelSpringLayout = SpringLayout::create();

    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelCloseButtonRefPtr, 2, SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelPanel);  
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelPanel);
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelCloseButtonRefPtr, -20, SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelPanel);
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelPanel);

    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelLabel, 2, SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelPanel);  
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelLabel, -5, SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelCloseButtonRefPtr);
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelLabel, 2, SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelPanel);
    _NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelPanel);


    _NewLeftTabLabelPanel->setPreferredSize(Vec2f(120,20));
    _NewLeftTabLabelPanel->pushToChildren(_NewLeftTabLabelLabel);
    _NewLeftTabLabelPanel->pushToChildren(_NewLeftTabLabelCloseButtonRefPtr);
    _NewLeftTabLabelPanel->setLayout(_NewLeftTabLabelPanelSpringLayout);



    std::string sent;
    std::string para="";
    std::ifstream inputFile((file.string()).c_str());
    while(std::getline(inputFile,sent))para+=sent+"\n";
    inputFile.close();

    TextAreaRefPtr _NewLeftTabTextArea = TextArea::create();
    _NewLeftTabTextArea->setText(para);
    _NewLeftTabTextArea->setEditable(true);

    ScrollPanelRefPtr _NewLeftTabContent = ScrollPanel::create();
    _NewLeftTabContent->setPreferredSize(Vec2f(200,1200));
    _NewLeftTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    _NewLeftTabContent->setViewComponent(_NewLeftTabTextArea);


    PanelRefPtr _NewRightTabLabelPanel = Panel::createEmpty();

    ButtonRefPtr _RightTabLabelCloseButtonRefPtr = dynamic_pointer_cast<Button>(dynamic_cast<InternalWindow*>(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());

    _RightTabLabelCloseButtonRefPtr->setPreferredSize(Vec2f(20,10));
    _RightTabLabelCloseButtonRefPtr->setText("X");

    _CloseRightButtonActionConnection = _RightTabLabelCloseButtonRefPtr->connectActionPerformed(boost::bind(&ContentPanel::handleCloseButtonAction, this, _1));

    LabelRefPtr _NewRightTabLabel=Label::create();
    _NewRightTabLabel->setText(file.leaf());
    _NewRightTabLabel->setBorders(NULL);
    _NewRightTabLabel->setBackgrounds(NULL);

    SpringLayoutRefPtr _NewRightTabLabelPanelSpringLayout = SpringLayout::create();

    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _RightTabLabelCloseButtonRefPtr, 2, SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabelPanel);  
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RightTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabelPanel);
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _RightTabLabelCloseButtonRefPtr, -20, SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabelPanel);
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _RightTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabelPanel);

    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabel, 2, SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabelPanel);  
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabel, -5, SpringLayoutConstraints::WEST_EDGE, _RightTabLabelCloseButtonRefPtr);
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewRightTabLabel, 2, SpringLayoutConstraints::WEST_EDGE, _NewRightTabLabelPanel);
    _NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabelPanel);


    _NewRightTabLabelPanel->setPreferredSize(Vec2f(120,20));
    _NewRightTabLabelPanel->pushToChildren(_RightTabLabelCloseButtonRefPtr);
    _NewRightTabLabelPanel->pushToChildren(_NewRightTabLabel);
    _NewRightTabLabelPanel->setLayout(_NewRightTabLabelPanelSpringLayout);



    TextAreaRefPtr _NewRightTabTextArea = TextArea::create();
    _NewRightTabTextArea->setText(para);
    _NewRightTabTextArea->setEditable(true);

    ScrollPanelRefPtr _NewRightTabContent = ScrollPanel::create();
    _NewRightTabContent->setPreferredSize(Vec2f(200,1200));
    _NewRightTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    _NewRightTabContent->setViewComponent(_NewRightTabTextArea);


    _RightTabPanel->addTab(_NewLeftTabLabelPanel, _NewLeftTabContent);

    _RightTabPanel->setSelectedIndex((_RightTabPanel->getMFTabs()->size())-1);

    _LeftTabPanel->addTab(_NewRightTabLabelPanel, _NewRightTabContent);

    _LeftTabPanel->setSelectedIndex((_LeftTabPanel->getMFTabs()->size())-1);

}

void ContentPanel::saveTextFile(BoostPath file)
{
    std::ofstream _OutputFile((file.string()).c_str());

    ScrollPanelRefPtr _ToBeSavedScrollPanel = dynamic_cast<ScrollPanel*>(_LeftTabPanel->getTabContents(_LeftTabPanel->getSelectedIndex()));
    TextAreaRefPtr _ToBeSavedTextArea = dynamic_cast<TextArea*>(_ToBeSavedScrollPanel->getViewComponent());

    std::string _TobeSavedText = _ToBeSavedTextArea->getText();
    _OutputFile<<_TobeSavedText;
    _OutputFile.close();
}

void ContentPanel::closeCurrentWindow()
{

    _LeftTabPanel->removeTab(_LeftTabPanel->getSelectedIndex());

    _RightTabPanel->removeTab(_RightTabPanel->getSelectedIndex());

}

void ContentPanel::createRightTabPanel()
{
    _RightTabPanel= TabPanel::create();
    _RightTabPanel->setPreferredSize(Vec2f(1200,1200));
    _RightTabPanel->addTab(_RightTabPanelLabel, _RightTabPanelContent);
    _RightTabPanel->setTabAlignment(0.5f);
    _RightTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    _RightTabPanel->setSelectedIndex(0);
}

void ContentPanel::createLeftTabPanel()
{
    _LeftTabPanel= TabPanel::create();
    _LeftTabPanel->setPreferredSize(Vec2f(1200,1200));
    _LeftTabPanel->addTab(_LeftTabPanelLabel, _LeftTabPanelContent);
    _LeftTabPanel->setTabAlignment(0.5f);
    _LeftTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    _LeftTabPanel->setSelectedIndex(0);
}

void ContentPanel::createDefaultTabs()
{
    _LeftTabPanelLabel = Label::create();

    // set the fields of the labels
    _LeftTabPanelLabel->setPreferredSize(Vec2f(120,20));
    _LeftTabPanelLabel->setText("Welcome!");
    _LeftTabPanelLabel->setBorders(NULL);
    _LeftTabPanelLabel->setBackgrounds(NULL);

    // Create a _StackTraceTextArea
    _LeftTabPanelTextArea = TextArea::create();
    _LeftTabPanelTextArea->setText("Hey Programmer!\n\n\n The following shortcuts also exists \n Ctrl+X\t-\t to execute Lua code \n Ctrl+1\t-\t To Focus on Lua Console TextArea \n Ctrl+T\t-\t for splitting the Content Panel \n\n You can now save/open files using the Debugging Interface\n Please DO NOT open files greater than 5KB.It is not efficiently coded and hence would take years to load.\n\n\n\t\tThank you!\n\n");
    _LeftTabPanelTextArea->setEditable(false);

    _LeftTabPanelContent = ScrollPanel::create();
    _LeftTabPanelContent->setPreferredSize(Vec2f(200,1200));
    _LeftTabPanelContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _LeftTabPanelTextArea to the ScrollPanel so it is displayed
    _LeftTabPanelContent->setViewComponent(_LeftTabPanelTextArea);


    _RightTabPanelLabel = Label::create();

    // set the fields of the labels
    _RightTabPanelLabel->setText("Screen2");
    _RightTabPanelLabel->setBorders(NULL);
    _RightTabPanelLabel->setBackgrounds(NULL);

    // Create a _StackTraceTextArea
    _RightTabPanelTextArea = TextArea::create();
    _RightTabPanelTextArea->setText("This is the Second screen.\n\n Opening files now will open them in both screens.\n\n Pressing the \"Save file\" would only save the currently selected file in the left screen.\n\n\t\tThank you!\n\n");
    _RightTabPanelTextArea->setEditable(false);

    _RightTabPanelContent = ScrollPanel::create();
    _RightTabPanelContent->setPreferredSize(Vec2f(200,1200));
    _RightTabPanelContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
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

    _LuaEditorSplitPanel->setMaxComponent(_RightTabPanel);
    _LuaEditorSplitPanel->setDividerSize(5);
    _LuaEditorSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);

}

void ContentPanel::updatePanel()
{
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


}

void ContentPanel::createSceneEditorPanel()
{
    //Scene Editing Panel
    _SceneEditorPanel = Panel::createEmpty();
    _SceneEditorPanelMouseClickedConnection = _SceneEditorPanel->connectMouseClicked(boost::bind(&ContentPanel::handleSceneEditorPanelMouseClicked, this, _1));
    _SceneEditorPanelMousePressedConnection = _SceneEditorPanel->connectMousePressed(boost::bind(&ContentPanel::handleSceneEditorPanelMousePressed, this, _1));
    _SceneEditorPanelMouseWheelMovedConnection = _SceneEditorPanel->connectMouseWheelMoved(boost::bind(&ContentPanel::handleSceneEditorPanelMouseWheelMoved, this, _1));
    _SceneEditorPanelKeyTypedConnection = _SceneEditorPanel->connectKeyTyped(boost::bind(&ContentPanel::handleSceneEditorPanelKeyTyped, this, _1));
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

    pushToChildren(_SceneEditorPanel);
    pushToChildren(_LuaEditorSplitPanel);
    setLayout(_MainCardLayout);
    setBackgrounds(NULL);
    setBorders(NULL);
}

void ContentPanel::setView(UInt32 Index)
{
    _MainCardLayout->setCard(Index);
}

void ContentPanel::addTab()
{

}

void ContentPanel::removeTab(UInt32 tabno)
{

}
void ContentPanel::handleCloseButtonAction(ActionEventDetails* const details)
{

    ButtonRefPtr _TempCloseButton = dynamic_cast<Button*>(details->getSource());
    PanelRefPtr _TempPanel = dynamic_cast<Panel*>(_TempCloseButton->getParentContainer());
    TabPanelRefPtr _TempTabPanel = dynamic_cast<TabPanel*>(_TempPanel->getParentContainer());
    UInt32 _ChildIndex = (_TempTabPanel->getChildIndex(_TempPanel))/2;

    _LeftTabPanel->removeTab(_ChildIndex);

    _RightTabPanel->removeTab(_ChildIndex);

}

void ContentPanel::handleSceneEditorPanelMouseDragged(MouseEventDetails* const details)
{
    _ApplicationPlayer->getDebugSceneNavigator().moveTo(details->getX(),details->getY());

    if( _ApplicationPlayer->editXFormManipMgr().isManipulating() )
    {
        _ApplicationPlayer->editXFormManipMgr().mouseMove(details->getX(),
                                                                         details->getViewport()->getPixelHeight() - details->getY());
    }
}


void ContentPanel::handleSceneEditorPanelMouseClicked(MouseEventDetails* const details)
{
    switch (details->getButton())
    {
        case MouseEventDetails::BUTTON1: 
            //Cast a ray into the scene and select the closest node
            _ApplicationPlayer->selectNode(details->getLocation());
            break;
    }
}

void ContentPanel::handleSceneEditorPanelKeyTyped(KeyEventDetails* const details)
{
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_F:
            _ApplicationPlayer->focusSelectedNode();
            break;
        case KeyEventDetails::KEY_T:
            _ApplicationPlayer->editXFormManipMgr().changeManipulator(ManipulatorManager::TRANSLATE);
            break;
        case KeyEventDetails::KEY_S:
            _ApplicationPlayer->editXFormManipMgr().changeManipulator(ManipulatorManager::SCALE);
            break;
        case KeyEventDetails::KEY_R:
            _ApplicationPlayer->editXFormManipMgr().changeManipulator(ManipulatorManager::ROTATE);
            break;
        case KeyEventDetails::KEY_ESCAPE:
            if( _ApplicationPlayer->editXFormManipMgr().isManipulating() )
            {
                _ApplicationPlayer->editXFormManipMgr().cancelManip();
            }
            else
            {
            }
            break;
    }

}

void ContentPanel::handleSceneEditorPanelMousePressed(MouseEventDetails* const details)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_ALT)
    {
        switch (details->getButton())
        {
            case MouseEventDetails::BUTTON1: 
                _ApplicationPlayer->getDebugSceneNavigator().buttonPress(Navigator::LEFT_MOUSE,details->getX(),details->getY());
                break;
            case MouseEventDetails::BUTTON2:
                _ApplicationPlayer->getDebugSceneNavigator().buttonPress(Navigator::RIGHT_MOUSE,details->getX(),details->getY());
                break;
            case MouseEventDetails::BUTTON3:
                _ApplicationPlayer->getDebugSceneNavigator().buttonPress(Navigator::MIDDLE_MOUSE,details->getX(),details->getY());
                break;

        }
        _SceneEditorPanelMouseDraggedConnection = dynamic_cast<WindowEventProducer*>(details->getSource())->connectMouseDragged(boost::bind(&ContentPanel::handleSceneEditorPanelMouseDragged, this, _1));
        _SceneEditorPanelMouseReleasedConnection = dynamic_cast<WindowEventProducer*>(details->getSource())->connectMouseReleased(boost::bind(&ContentPanel::handleSceneEditorPanelMouseReleased, this, _1));
    }
    else if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        Line ViewRay;
        ViewportRefPtr
            TheViewport(_ApplicationPlayer->getDebugViewport());
        TheViewport->getCamera()->calcViewRay( ViewRay, details->getX(),details->getY(), *TheViewport);

        IntersectAction *CastRayAction = IntersectAction::create();

        CastRayAction->setLine( ViewRay );
        CastRayAction->setTravMask(ApplicationPlayer::DEBUG_GRAPH_INTERSECTABLE);
        CastRayAction->apply( TheViewport->getRoot() );             

        if ( (CastRayAction->didHit()) &&
             (_ApplicationPlayer->editXFormManipMgr().startManip( CastRayAction->getHitObject()) ) )
        {
            _ApplicationPlayer->editXFormManipMgr().mouseButtonPress(details->getButton(), details->getX(),details->getViewport()->getPixelHeight() - details->getY());
        }
        _SceneEditorPanelMouseDraggedConnection = dynamic_cast<WindowEventProducer*>(details->getSource())->connectMouseDragged(boost::bind(&ContentPanel::handleSceneEditorPanelMouseDragged, this, _1));
        _SceneEditorPanelMouseReleasedConnection = dynamic_cast<WindowEventProducer*>(details->getSource())->connectMouseReleased(boost::bind(&ContentPanel::handleSceneEditorPanelMouseReleased, this, _1));
    }
}

void ContentPanel::handleSceneEditorPanelMouseReleased(MouseEventDetails* const details)
{
    switch (details->getButton())
    {
        case MouseEventDetails::BUTTON1: 
            _ApplicationPlayer->getDebugSceneNavigator().buttonRelease(Navigator::LEFT_MOUSE,details->getX(),details->getY());
            break;
        case MouseEventDetails::BUTTON2:
            _ApplicationPlayer->getDebugSceneNavigator().buttonRelease(Navigator::RIGHT_MOUSE,details->getX(),details->getY());
            break;
        case MouseEventDetails::BUTTON3:
            _ApplicationPlayer->getDebugSceneNavigator().buttonRelease(Navigator::MIDDLE_MOUSE,details->getX(),details->getY());
            break;
    }
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        if(_ApplicationPlayer->editXFormManipMgr().isManipulating() )
        {
            _ApplicationPlayer->editXFormManipMgr().mouseButtonRelease(details->getButton(), details->getX(),details->getViewport()->getPixelHeight() - details->getY());
            _ApplicationPlayer->editXFormManipMgr().endManip();

            Node* target(_ApplicationPlayer->editXFormManipMgr().getTarget());
            if(target &&
               target->getCore() &&
               target->getCore()->getType().isDerivedFrom(Transform::getClassType()))
            {
                std::ostringstream initMatStrStream;
                OutStream theinitMatOutStream(initMatStrStream);
                FieldTraits<Matrix>::putToStream(_ApplicationPlayer->editXFormManipMgr().getManipulator()->getInitialXForm(),theinitMatOutStream);


                std::ostringstream matStrStream;
                OutStream theOutStream(matStrStream);
                dynamic_cast<Transform*>(target->getCore())->getField(Transform::MatrixFieldId)->pushValueToStream(theOutStream);

                SetFieldValueCommandPtr SetCommand =
                    SetFieldValueCommand::create(target->getCore(),
                                                 Transform::MatrixFieldId,
                                                 matStrStream.str(),
                                                 initMatStrStream.str());

                _ApplicationPlayer->getCommandManager()->executeCommand(SetCommand);
            }
        }
    }
    _SceneEditorPanelMouseDraggedConnection.disconnect();
    _SceneEditorPanelMouseReleasedConnection.disconnect();
}

void ContentPanel::handleSceneEditorPanelMouseWheelMoved(MouseWheelEventDetails* const details)
{
    Navigator& TheNav(_ApplicationPlayer->getDebugSceneNavigator());
    TheNav.setDistance(TheNav.getDistance() + details->getUnitsToScroll() * TheNav.getMotionFactor());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void ContentPanel::resolveLinks(void)
{
    Inherited::resolveLinks();

    _CloseRightButtonActionConnection.disconnect();
    _CloseLeftButtonActionConnection.disconnect();
    _SceneEditorPanelMouseDraggedConnection.disconnect();
    _SceneEditorPanelMouseClickedConnection.disconnect();
    _SceneEditorPanelMousePressedConnection.disconnect();
    _SceneEditorPanelMouseReleasedConnection.disconnect();
    _SceneEditorPanelMouseWheelMovedConnection.disconnect();
    _SceneEditorPanelKeyTypedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

ContentPanel::ContentPanel(void) :
    Inherited()
{
}

ContentPanel::ContentPanel(const ContentPanel &source) :
    Inherited(source)
{
}

ContentPanel::~ContentPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ContentPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ContentPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ContentPanel NI" << std::endl;
}

OSG_END_NAMESPACE
