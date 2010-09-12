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

#ifndef _KEHELPERPANEL_H_
#define _KEHELPERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KEHelperPanelBase.h"

//for lua
#include <OpenSG/OSGLuaManager.h>

// for tab panel contents
#include <OpenSG/OSGTabPanelFields.h>
#include <OpenSG/OSGTextAreaFields.h>
#include <sstream>
#include <OpenSG/OSGScrollPanelFields.h>
#include <OpenSG/OSGPanelFields.h>

// for the buttons
#include <OpenSG/OSGButtonFields.h>

// spring layout
#include <OpenSG/OSGSpringLayoutFields.h>
#include <OpenSG/OSGSpringLayoutConstraintsFields.h>

// for labels
#include <OpenSG/OSGLabel.h>

// List header files
#include <OpenSG/OSGListFields.h>
#include <OpenSG/OSGDefaultListModelFields.h>
#include <OpenSG/OSGFlowLayoutFields.h>

#include <OpenSG/OSGGridLayoutFields.h>
#include <OpenSG/OSGFieldContainerEditorFactory.h>
#include <OpenSG/OSGActionEventDetailsFields.h>

#include "Application/KEMainApplication.h"

#include "Player/KEApplicationPlayerFields.h"
#include "Player/HierarchyPanel/KEHierarchyPanelFields.h"
#include "Player/KEApplicationPlayerFields.h"

#ifdef OSG_WITH_LUA_DEBUGGER
#include <OpenSG/OSGTreeFields.h>
#include <OpenSG/OSGLuaIntrospectionTreeModelFields.h>
#endif

OSG_BEGIN_NAMESPACE

/*! \brief HelperPanel class. See \ref
           PageKabalaEngineHelperPanel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING HelperPanel : public HelperPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HelperPanelBase Inherited;
    typedef HelperPanel     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
	void viewTab(UInt32);
	void hideTab(UInt32);

	//void updateListBox(void);
	void setupHistoryList(void);
	void setupRest(void);

    void setApplicationPlayer(ApplicationPlayer* const TheApplicationPlayer);

    void updateSelectedNode(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in HelperPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HelperPanel(void);
    HelperPanel(const HelperPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HelperPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    void handleLuaError(LuaErrorEventDetails* const details);
    void handleExecuteScriptAction(ActionEventDetails* const details);
	void handleHistoryListMouseClicked(MouseEventDetails* const details);

    boost::signals2::connection _LuaErrorConnection,
                                _ExecuteScriptActionConnection,
                                _HistoryListMouseClickedConnection;

	SpringLayoutRefPtr _Layout;

    ApplicationPlayerRefPtr _ApplicationPlayer;

	LabelRefPtr					_HistoryLabel;
	ListRefPtr					_HistoryList;
	DefaultListModelRefPtr		_HistoryListModel;
	ScrollPanelRefPtr			_HistoryScrollPanel;
	std::vector<std::string>	_ListOfCommands;

	ButtonRefPtr _ExecuteBtn;

	TabPanelRefPtr _InfoTabPanel;
	TextAreaRefPtr _CodeTextArea;
	TextAreaRefPtr _ErrorTextArea;
	TextAreaRefPtr _StackTraceTextArea;

	LabelRefPtr _TabPanel1Label;
	LabelRefPtr _TabPanel2Label;
	LabelRefPtr _TabPanel3Label;
	LabelRefPtr _TabPanel4Label;
	
	PanelRefPtr		_LuaConsoleContent;
	ScrollPanelRefPtr	_LuaConsoleScrollPanel;
	ScrollPanelRefPtr	_TabPanel2Content;
	ScrollPanelRefPtr	_TabPanel3Content;
	PanelRefPtr		_TabPanel4Content;

    //Editor Panel
    FieldContainerEditorComponentRefPtr _NodeEditor;
    FieldContainerEditorComponentRefPtr _CoreEditor;

    //Logging Panel
	LabelRefPtr _LoggingContentLabel;
	PanelRefPtr		_LoggingContent;
	TextAreaRefPtr _LoggingArea;
	ScrollPanelRefPtr	_LoggingScrollPanel;


	void updateListBox(void);

	friend class ApplicationPlayer;
	friend class HierarchyPanel;

	void setupLuaTab(void);
	void setupErrorTab(void);
	void setupTraceTab(void);
	void setupPropertiesTab(void);
	void setupInfoTabLabels(void);
	void setupInfoTabPanel(void);
    void createLoggingTab(void);
    
#ifdef OSG_WITH_LUA_DEBUGGER
    void createIntrospectionTreeTab(TabPanel* const tabPanel);
    void updateGlobalLuaIntroTree(void);
    void updateLocalLuaIntroTree(void);

    LuaIntrospectionTreeModelRecPtr _GlobalLuaIntroTreeModel;
#endif
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HelperPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HelperPanel &source);
};

typedef HelperPanel *HelperPanelP;

OSG_END_NAMESPACE

#include "KEHelperPanelBase.inl"
#include "KEHelperPanel.inl"

#endif /* _KEHELPERPANEL_H_ */
