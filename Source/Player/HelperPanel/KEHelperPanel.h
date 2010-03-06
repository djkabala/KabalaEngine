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

	public:
	SpringLayoutPtr PanelFlowLayout;
	GridLayoutPtr TabContentDLayout;
  private:


	enum tab{LUA=1,ERR,CONSOLE,PROPERTIES};

    typedef HelperPanelBase Inherited;

	//enum tabs{LUA=1,SCENEGRAPH};

	friend class ApplicationPlayer;
	friend class HierarchyPanel;



	void setLabelValues(NodePtr SelectedNode);
	void setLabelValuesToNull();


	/////////////////// for the history Label- begin ///////////////////
	LabelPtr historyLabel;
	LabelPtr historyLabel2;
	/////////////////// for the history Label- end ///////////////////


	/////////////////// for the History list - begin ///////////////////
	ListSelectionModelPtr HistoryListSelectionModel;
	ListPtr HistoryList;
	DefaultListModelPtr HistoryListModel;
	ScrollPanelPtr HistoryScrollPanel;
	std::vector<std::string> list_of_commands;
	void updateListBox(void);
	/////////////////// for the History list - end ///////////////////


	/////////////////// for the execute Button- begin ///////////////////
	ButtonPtr executeBtn;
	/////////////////// for the execute Button- end ///////////////////


	/////////////////// for the Information TabPanel - begin///////////////////
	TabPanelPtr InfoTabPanel;
	TextAreaPtr CodeTextArea;
	TextAreaPtr ErrorTextArea;
	TextAreaPtr StackTraceTextArea;

	LabelPtr TabPanel1;
	LabelPtr TabPanel2;
	LabelPtr TabPanel3;
	LabelPtr TabPanel4;
	
	ScrollPanelPtr TabContentA;
	ScrollPanelPtr TabContentB;
	ScrollPanelPtr TabContentC;
	PanelPtr TabContentD;

	// for the properties tab
	LabelPtr NodeNameLabel;
	LabelPtr NodeCoreTypeLabel;
	LabelPtr NodeMinLabel;
	LabelPtr NodeMaxLabel;
	LabelPtr NodeCenterLabel;
	LabelPtr NodeTriCountLabel;
	LabelPtr NodeTravMaskLabel;
	LabelPtr NodeOcclusionMaskLabel;
	LabelPtr NodeActiveLabel;

	LabelPtr NodeNameValueLabel;
	LabelPtr NodeCoreTypeValueLabel;
	LabelPtr NodeMinValueLabel;
	LabelPtr NodeMaxValueLabel;
	LabelPtr NodeCenterValueLabel;
	LabelPtr NodeTriCountValueLabel;
	LabelPtr NodeTravMaskValueLabel;
	LabelPtr NodeOcclusionMaskValueLabel;
	LabelPtr NodeActiveValueLabel;


	/////////////////// for the Information TabPanel - end ///////////////////



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

	void setupLuaTab(void);
	void setupErrorTab(void);
	void setupTraceTab(void);
	void setupPropertiesTab(void);
	void setupInfoTabLabels(void);
	void setupInfoTabPanel(void);

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
