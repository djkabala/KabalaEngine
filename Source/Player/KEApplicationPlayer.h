/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#ifndef _KEAPPLICATIONPLAYER_H_
#define _KEAPPLICATIONPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEApplicationPlayerBase.h"

#include "Project/KEProjectFields.h"
#include "Project/Scene/KESceneFields.h"


#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGNavigator.h>
#include <OpenSG/Toolbox/OSGEventListener.h>

#include <OpenSG/Input/OSGKeyAdapter.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGMenuItem.h>
#include <OpenSG/UserInterface/OSGMenuBar.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/Lua/OSGLuaManager.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <sstream>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
//text area
#include <OpenSG/UserInterface/OSGScrollPanel.h>

//split panel 
#include <OpenSG/UserInterface/OSGSplitPanel.h>

//spring layout
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>


#include <OpenSG/Physics/OSGPhysicsCharacteristicsDrawable.h>
#include <OpenSG/OSGNode.h>

// tree headers

#include <OpenSG/UserInterface/OSGTree.h>
#include <OpenSG/UserInterface/OSGSceneGraphTreeModel.h>
#include <OpenSG/UserInterface/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>
#include <OpenSG/UserInterface/OSGTreeSelectionListener.h>
#include <OpenSG/Toolbox/OSGGeometryUtils.h>


// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>

//Combobox
#include <OpenSG/UserInterface/OSGComboBox.h>
#include <OpenSG/UserInterface/OSGDefaultMutableComboBoxModel.h>

//cardlayout
#include <OpenSG/UserInterface/OSGCardLayout.h>

#include <OpenSG/UserInterface/OSGCommand.h>
#include <OpenSG/UserInterface/OSGUndoManager.h>
#include <OpenSG/UserInterface/OSGCommandManager.h>
 
#include "Player/HierarchyPanel/KEHierarchyPanelFields.h"
#include "Player/HelperPanel/KEHelperPanelFields.h"
#include "Player/ContentPanel/KEContentPanelFields.h"


#include "Player/Commands/KECommandActionListenerForPlayer.h"

#include "Player/Commands/KECutCommand.h"
#include "Player/Commands/KECopyCommand.h"
#include "Player/Commands/KEPasteCommand.h"
#include "Player/Commands/KEDeleteCommand.h"
#include "Player/Commands/KEShowHideCommand.h"
#include "Player/Commands/KENewCommand.h"
#include "Player/Commands/KEUndoCommandOfPlayer.h"
#include "Player/Commands/KERedoCommandOfPlayer.h"


//Animation
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGAnimationGroup.h>

#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationPlayer class. See \ref 
           PageKabalaEngineApplicationPlayer for a description.
*/


class KE_KABALAENGINELIB_DLLMAPPING ApplicationPlayer : public ApplicationPlayerBase 
{
  private:


    typedef ApplicationPlayerBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ::osg::UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      ::osg::UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
	virtual void attachApplication(void);
	virtual void dettachApplication(void);
	virtual void attachInterface(void);
	virtual void attachListeners(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);
    virtual void gotoScene(ScenePtr TheScene);
    void enableDebug(bool EnableDebug);

	// inline functions 

	CommandManagerPtr getCommandManager(void);
	void setCurrentAction(UInt32 action);
	UInt32 getCurrentAction(void);
	void setClonedNodeInCopyClipboard(NodePtr node);
	NodePtr getClonedNodeInCopyClipboard(void);
	void setNodeInCutClipboard(NodePtr node);
	NodePtr getNodeInCutClipboard(void);
	UndoManagerPtr getUndoManager(void);
	NodePtr getHighlightNode(void);
	void setHighlightNode(NodePtr);
	ViewportPtr getDebugViewport(void);
	void setDebugViewport(ViewportPtr);
	HelperPanelPtr getHelperPanel(void);
	void setHelperPanel(HelperPanelPtr);
	NodePtr getSelectedNode(void);
	void setSelectedNode(NodePtr);
	ContentPanelPtr getContentPanel(void);
	void setContentPanel(ContentPanelPtr);

    Navigator& getDebugSceneNavigator(void);

    void moveDebugCamera(const Matrix& Transform);
    void resetDebugCamera(void);

    void setDebugView(UInt32 Index);
    void updateHighlightNode(void);
   /*=========================  PROTECTED  ===============================*/
  protected:




    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationPlayer(void);
    ApplicationPlayer(const ApplicationPlayer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationPlayer(void); 

    /*! \}                                                                 */
		


	class CommandManagerListener: public ChangeListener
	{
	  public:
		CommandManagerListener(ApplicationPlayerPtr ApplicationPlayer);

		virtual void stateChanged(const ChangeEventPtr e);

		void setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer);

	  protected :
        ApplicationPlayerPtr _ApplicationPlayer;
	};
	friend class CommandManagerListener;
	CommandManagerListener _CommandManagerListener;


	class PlayerKeyListener : public KeyAdapter
	{
	public:
		PlayerKeyListener(ApplicationPlayerPtr TheApplicationPlayer);

		virtual void keyTyped(const KeyEventPtr e);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	};
    friend class PlayerKeyListener;
	PlayerKeyListener _PlayerKeyListener;

	
	class BasicListener : public ActionListener
	{
	public:
		BasicListener(ApplicationPlayerPtr TheApplicationPlayer);
		~BasicListener();

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	
	};
	friend class BasicListener;
	BasicListener _BasicListener;



	class ComboBoxListener: public ComboBoxSelectionListener
    {
    public:
        void selectionChanged(const ComboBoxSelectionEventPtr e);
		
        ComboBoxListener(ApplicationPlayerPtr TheApplicationPlayer);
	protected:
			 ApplicationPlayerPtr _ApplicationPlayer;
	};
	friend class ComboBoxListener;
	ComboBoxListener _ComboBoxListener;



	class GotoSceneItemListener : public ActionListener
	{
	public:
		GotoSceneItemListener(ApplicationPlayerPtr TheApplicationPlayer);
		~GotoSceneItemListener();

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	
	};
	friend class GotoSceneItemListener;
	GotoSceneItemListener _GotoSceneItemListener;



	class ProjectListener : public EventListener
	{
	public:
		ProjectListener(ApplicationPlayerPtr TheApplicationPlayer);
		~ProjectListener();

		virtual void eventProduced(const EventPtr e, UInt32 EventProducedId);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	
	};
	friend class ProjectListener;
	ProjectListener _ProjectListener;



	class highlightNodeListener : public UpdateListener
	{
	public:
		highlightNodeListener(ApplicationPlayerPtr TheApplicationPlayer);
		~highlightNodeListener();

		virtual void update(const UpdateEventPtr e);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	
	};
	friend class highlightNodeListener;
	highlightNodeListener _highlightNodeListener;


	NodePtr _HighlightNode;
	NodePtr _SelectedNode;

	HierarchyPanelPtr	_HierarchyPanel;
	HelperPanelPtr		_HelperPanel;
	ContentPanelPtr		_ContentPanel;
	
    ViewportPtr _DebugViewport;

	enum cActions{NONE,CUT,COPY};

	UInt32 currentAction;

	NodePtr _NodeInCutClipboard;
	NodePtr _ClonedNodeInCopyClipboard;

	CommandManagerPtr				_TheCommandManager;
	UndoManagerPtr					_TheUndoManager;
	CommandActionListenerForPlayer	_UndoActionListener;
	CommandActionListenerForPlayer	_RedoActionListener;


	PanelPtr					_ToolbarAndContentPanel;

	PanelPtr			_Toolbar;
	
	ButtonPtr	_OpenFileButton;
	ButtonPtr	_SaveFileButton;
	ButtonPtr	_CloseFileButton;


	MenuItemPtr _ResetItem ;				
    MenuItemPtr _ForceQuitItem ;			

	MenuItemPtr _UndoItem ;				
    MenuItemPtr _RedoItem ;				
    

    MenuItemPtr _NextItem ;				
    MenuItemPtr _PrevItem ;				
    MenuItemPtr _FirstItem;				
    MenuItemPtr _LastItem ;				
    MenuPtr		_SceneSubItem ;				

	MenuItemPtr _FlyNavigatorItem ;		
    MenuItemPtr _TrackballNavigatorItem ;
    MenuItemPtr _BasicItem ;				
    MenuItemPtr _RenderItem ;			
    MenuItemPtr _PhysicsItem ;			
    MenuItemPtr _ParticleSystemItem ;	
	MenuItemPtr _AnimationItem ;			
	MenuItemPtr _PauseActiveUpdatesItem;			
	MenuItemPtr _DrawBoundingVolumesItem ;		
	MenuItemPtr _FrustrumCullingItem  ;
	MenuItemPtr _DrawPhysicsCharacteristicsItem  ;


	MenuPtr		_EditMenu;
	MenuPtr		_ProjectMenu;
	MenuPtr		_SceneMenu;
	MenuPtr		_NavigatorMenu;
	MenuPtr		_StatisticsMenu;
	MenuPtr		_ToggleMenu;
	MenuBarPtr	_MainMenuBar;

	BorderLayoutConstraintsPtr	_DebugWindowSplitPanelConstraints;
	SplitPanelPtr				_DebugWindowSplitPanel;

	BorderLayoutConstraintsPtr	_TopHalfSplitPanelConstraints;
	SplitPanelPtr				_TopHalfSplitPanel;

	DefaultMutableComboBoxModelPtr	_ModeComboBoxModel;
	ComboBoxPtr						_ModeComboBox;

	NodePtr _DebugBeacon;

	bool _IsDebugActive;

    SimpleStatisticsForegroundPtr _DebugBasicStatForeground;
    SimpleStatisticsForegroundPtr _DebugRenderStatForeground;
    SimpleStatisticsForegroundPtr _DebugPhysicsStatForeground;
    SimpleStatisticsForegroundPtr _DebugParticleSystemStatForeground;
    SimpleStatisticsForegroundPtr _DebugAnimationStatForeground;
	
    //Debug Camera
    CameraPtr    _SceneViewportCamera;
    CameraPtr    _DebugCamera;
    NodePtr      _DebugCameraBeacon;
    TransformPtr _DebugBeaconTransform;

    //Camera Navigator
    Navigator    _DebugSceneNavigator;

    //Debug Camera Animation
    KeyframeTransformationsSequencePtr _DebugCameraTransformationKeyframes;
    //KeyframeNumbersSequencePtr _DebugCameraFovKeyframes;
    FieldAnimationPtr _DebugCameraTransAnimation;
    //FieldAnimationPtr _DebugCameraFovAnimation;
    AnimationGroupPtr _DebugCameraAnimationGroup;

	void updateListBox(void);
	void setupPopupMenu();
	void invertShowHideCaption();

    void keyTyped(const KeyEventPtr e);
	void actionPerformed(const ActionEventPtr e);

	ViewportPtr createDebugViewport(void);
    void attachDebugViewport(void);
    void detachDebugViewport(void);
    void updateDebugViewport(void);

    void createDebugCameraAnim(void);

	virtual void attachDebugInterface(void);
	virtual void detachDebugInterface(void);
	virtual void createDebugInterface(void);

	void updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager);
	void createGotoSceneMenuItems(ProjectPtr TheProject);
    void updateGotoSceneMenuItems(ProjectPtr TheProject);
	void updateDebugUI(void);

    void initDebugStatForegrounds(void);
    void hideAllStatForegrounds(void);
    void toggleStatForeground(StatisticsForegroundPtr TheForeground);
    void toggleDrawBoundingVolumes(void);
    void toggleFrustumCulling(void);
    void toggleDrawPhysicsCharacteristics(void);
    void toggleSceneInputBlocking(void);
    void setSceneInputBlocking(bool block);

    NodePtr getPhysicsDrawableNode(void);
    void updateDebugSceneChange(void);

    void createHighlightNode(void);


    /*==========================  PRIVATE  ================================*/
  private:


	InternalWindowPtr MainInternalWindow;		
	GraphicsPtr DebuggerGraphics;				
	UIForegroundPtr DebuggerUIForeground;		
	UIDrawingSurfacePtr DebuggerDrawingSurface;	

    friend class FieldContainer;
    friend class ApplicationPlayerBase;
	

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ApplicationPlayer &source);
    void updateWindowTitle(void);

    PhysicsCharacteristicsDrawablePtr _PhysDrawable;
    NodePtr                           _PhysDrawableNode;
    bool _WasMouseHidden;
    bool _WasMouseAttached;
};

typedef ApplicationPlayer *ApplicationPlayerP;


OSG_END_NAMESPACE

#include "KEApplicationPlayerBase.inl"
#include "KEApplicationPlayer.inl"

#endif /* _KEAPPLICATIONPLAYER_H_ */
