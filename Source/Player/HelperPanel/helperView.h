
#include <OpenSG/OSGConfig.h>

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

OSG_BEGIN_NAMESPACE

public class HelperView
{
private:
	enum tabs{LUA=1,ERROR,CONSOLE,PROPERTIES};

	PanelPtr SplitPanelPanel;
	SpringLayoutPtr PanelFlowLayout;

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

	void setLabelValuesToNull();
	void setLabelValues(NodePtr SelectedNode);
	/////////////////// for the Information TabPanel - end ///////////////////

public:
	

	/////////////////// Constructors - begin///////////////////
    HelperView(void);
    HelperView(const HelperView &source);
	/////////////////// Constructors - end///////////////////


	/////////////////// Destructors - begin///////////////////
    ~HelperView(void); 
	/////////////////// Destructors - end///////////////////

     
	/////////////////// Lua Listener - begin///////////////////
	class LuaErrorListener : public LuaListener
    {

        public:
            LuaErrorListener(ApplicationPlayerPtr TheApplicationPlayer);

        protected :
            ApplicationPlayerPtr _ApplicationPlayer;

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
		BasicListener(HelperViewPtr TheHelperView);
		~BasicListener();

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		HelperViewPtr _HelperView;
	
	};

	friend class BasicListener;
	BasicListener _BasicListener;
	/////////////////// Basic Listener - end///////////////////



	/////////////////// Key Listener - begin///////////////////
	class PlayerKeyListener : public KeyAdapter
	{
	public:
		PlayerKeyListener(HelperViewPtr TheHelperView);

		virtual void keyTyped(const KeyEventPtr e);
	protected :
		HelperViewPtr _HelperView;
	};
	
    friend class PlayerKeyListener;
	PlayerKeyListener _PlayerKeyListener;
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

	void updateListBox(void);
	void setupHistoryList(void);
	void setupRest(void);

	void actionPerformed(const ActionEventPtr e);
	void keyTyped(const KeyEventPtr e);
	/////////////////// other function definitions - end///////////////////
}


typedef HelperView *HelperViewP;


OSG_END_NAMESPACE

#include "KEHelperViewBase.inl"
#include "KEHelperView.inl"

