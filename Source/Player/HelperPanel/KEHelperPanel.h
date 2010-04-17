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

#ifndef _KEHELPERPANEL_H_
#define _KEHELPERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEHelperPanelBase.h"


//for lua
#include <OpenSG/Lua/OSGLuaManager.h>

// for tab panel contents
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <sstream>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGPanel.h>

// for the buttons
#include <OpenSG/UserInterface/OSGButton.h>

// spring layout
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>

// for labels
#include <OpenSG/UserInterface/OSGLabel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>

#include <OpenSG/UserInterface/OSGGridLayout.h>

#include "Application/KEMainApplication.h"

#include "Player/KEApplicationPlayerFields.h"
#include "Player/HierarchyPanel/KEHierarchyPanelFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief HelperPanel class. See \ref 
           PageKabalaEngineHelperPanel for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING HelperPanel : public HelperPanelBase
{
   typedef HelperPanelBase Inherited;

  private:

	SpringLayoutPtr _Layout;
	GridLayoutPtr _TabPanel4ContentLayout;

	enum tab{LUA=1,ERR,CONSOLE,PROPERTIES};

	LabelPtr					_HistoryLabel;
	ListSelectionModelPtr		_HistoryListSelectionModel;
	ListPtr						_HistoryList;
	DefaultListModelPtr			_HistoryListModel;
	ScrollPanelPtr				_HistoryScrollPanel;
	std::vector<std::string>	_ListOfCommands;

	ButtonPtr _ExecuteBtn;

	TabPanelPtr _InfoTabPanel;
	TextAreaPtr _CodeTextArea;
	TextAreaPtr _ErrorTextArea;
	TextAreaPtr _StackTraceTextArea;

	LabelPtr _TabPanel1Label;
	LabelPtr _TabPanel2Label;
	LabelPtr _TabPanel3Label;
	LabelPtr _TabPanel4Label;
	
	PanelPtr		_LuaConsoleContent;
	ScrollPanelPtr	_LuaConsoleScrollPanel;
	ScrollPanelPtr	_TabPanel2Content;
	ScrollPanelPtr	_TabPanel3Content;
	PanelPtr		_TabPanel4Content;

	LabelPtr _NodeNameLabel;
	LabelPtr _NodeCoreTypeLabel;
	LabelPtr _NodeMinLabel;
	LabelPtr _NodeMaxLabel;
	LabelPtr _NodeCenterLabel;
	LabelPtr _NodeTriCountLabel;
	LabelPtr _NodeTravMaskLabel;
	LabelPtr _NodeOcclusionMaskLabel;
	LabelPtr _NodeActiveLabel;

	LabelPtr _NodeNameValueLabel;
	LabelPtr _NodeCoreTypeValueLabel;
	LabelPtr _NodeMinValueLabel;
	LabelPtr _NodeMaxValueLabel;
	LabelPtr _NodeCenterValueLabel;
	LabelPtr _NodeTriCountValueLabel;
	LabelPtr _NodeTravMaskValueLabel;
	LabelPtr _NodeOcclusionMaskValueLabel;
	LabelPtr _NodeActiveValueLabel;

    //Logging Panel
	LabelPtr _LoggingContentLabel;
	PanelPtr		_LoggingContent;
	TextAreaPtr _LoggingArea;
	ScrollPanelPtr	_LoggingScrollPanel;


	void updateListBox(void);
	void setLabelValues(NodePtr _SelectedNode);
	void setLabelValuesToNull();

	friend class ApplicationPlayer;
	friend class HierarchyPanel;

	void setupLuaTab(void);
	void setupErrorTab(void);
	void setupTraceTab(void);
	void setupPropertiesTab(void);
	void setupInfoTabLabels(void);
	void setupInfoTabPanel(void);
    void createLoggingTab(void);


    /*==========================  PUBLIC  =================================*/
  public:

	  	   /////////////////// Lua Listener - begin///////////////////
	class LuaErrorListener : public LuaListener
    {

        public:
            LuaErrorListener(HelperPanelPtr TheHelperPanel);

        protected :
            HelperPanelPtr _HelperPanel;

        public:

            virtual void error(const LuaErrorEventPtr e);
    };
    friend class LuaErrorListener;
	LuaErrorListener  _LuaErrorListener;
	/////////////////// Lua listener - end///////////////////


	/////////////////// Basic Listener - begin///////////////////
	class BasicListener : public ActionListener
	{
	public:
		BasicListener(HelperPanelPtr TheHelperPanel);

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		HelperPanelPtr _HelperPanel;
	
	};

	friend class BasicListener;
	BasicListener _BasicListener;
	/////////////////// Basic Listener - end///////////////////



	/////////////////// Key Listener - begin///////////////////
	class PlayerKeyListener2 : public KeyAdapter
	{
	public:
		PlayerKeyListener2(HelperPanelPtr TheHelperPanel);

		virtual void keyTyped(const KeyEventPtr e);
	protected :
		HelperPanelPtr _HelperPanel;
	};
	
    friend class PlayerKeyListener2;
	PlayerKeyListener2 _PlayerKeyListener2;
	/////////////////// Key Listener - end///////////////////
	
	/////////////////// Key Listener - begin///////////////////
	class PlayerMouseListener : public MouseAdapter
	{
	public:
		PlayerMouseListener(HelperPanelPtr TheHelperPanel);

		virtual void mouseClicked(const MouseEventPtr e);
	protected :
		HelperPanelPtr _HelperPanel;
	};
	
    friend class PlayerMouseListener;
	PlayerMouseListener _PlayerMouseListener;
	/////////////////// Key Listener - end///////////////////
	

	/////////////////// other function definitions - begin///////////////////
	void viewTab(UInt32);
	void hideTab(UInt32);

	//void updateListBox(void);
	void setupHistoryList(void);
	void setupRest(void);

	void actionPerformed(const ActionEventPtr e);
	void keyTyped2(const KeyEventPtr e);
	/////////////////// other function definitions - end///////////////////



    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class HelperPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const HelperPanel &source);
};

typedef HelperPanel *HelperPanelP;

OSG_END_NAMESPACE

#include "KEHelperPanelBase.inl"
#include "KEHelperPanel.inl"

#endif /* _KEHELPERPANEL_H_ */
