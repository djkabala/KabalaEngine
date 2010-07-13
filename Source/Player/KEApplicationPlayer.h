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

#ifndef _KEAPPLICATIONPLAYER_H_
#define _KEAPPLICATIONPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include "KEApplicationPlayerBase.h"
#include "Project/KEProject.h"

#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGNavigator.h>
#include <OpenSG/OSGEventListener.h>

#include <OpenSG/OSGKeyAdapter.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>
#include <OpenSG/OSGMenu.h>
#include <OpenSG/OSGMenuItem.h>
#include <OpenSG/OSGMenuBar.h>
#include <OpenSG/OSGTextArea.h>
#include <OpenSG/OSGLuaManager.h>
#include <OpenSG/OSGTabPanel.h>
#include <OpenSG/OSGButton.h>
#include <OpenSG/OSGColorLayer.h>
#include <OpenSG/OSGBorderLayout.h>
#include <OpenSG/OSGBorderLayoutConstraints.h>
//text area
#include <OpenSG/OSGScrollPanel.h>

//split panel 
#include <OpenSG/OSGSplitPanel.h>

//spring layout
#include <OpenSG/OSGSpringLayout.h>
#include <OpenSG/OSGSpringLayoutConstraints.h>
#include <OpenSG/OSGLabel.h>
#include <OpenSG/OSGBoxLayout.h>
#include <OpenSG/OSGComponentContainer.h>
#include <OpenSG/OSGPanel.h>
#include <OpenSG/OSGColorLayer.h>

// UserInterface Headers
#include <OpenSG/OSGUIForeground.h>
#include <OpenSG/OSGInternalWindow.h>
#include <OpenSG/OSGUIDrawingSurface.h>
#include <OpenSG/OSGGraphics2D.h>
#include <OpenSG/OSGLookAndFeelManager.h>


#include <OpenSG/OSGPhysicsCharacteristicsDrawable.h>
#include <OpenSG/OSGNode.h>

// tree headers

#include <OpenSG/OSGTree.h>
#include <OpenSG/OSGSceneGraphTreeModel.h>
#include <OpenSG/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/OSGGridLayout.h>
#include <OpenSG/OSGTreeSelectionListener.h>


// List header files
#include <OpenSG/OSGList.h>
#include <OpenSG/OSGDefaultListModel.h>
#include <OpenSG/OSGDefaultListSelectionModel.h>
#include <OpenSG/OSGFlowLayout.h>

//Combobox
#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGDefaultMutableComboBoxModel.h>

//cardlayout
#include <OpenSG/OSGCardLayout.h>

#include <OpenSG/OSGCommand.h>
#include <OpenSG/OSGUndoManager.h>
#include <OpenSG/OSGCommandManager.h>
 
#include "Player/HierarchyPanel/KEHierarchyPanelFields.h"
#include "Player/HelperPanel/KEHelperPanelFields.h"
#include "Player/ContentPanel/KEContentPanelFields.h"

#include "Player/Commands/KECommandActionListenerForPlayer.h"

//Animation
#include <OpenSG/OSGKeyframeSequences.h>
#include <OpenSG/OSGKeyframeAnimator.h>
#include <OpenSG/OSGFieldAnimation.h>
#include <OpenSG/OSGAnimationGroup.h>

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationPlayer class. See \ref
           PageKabalaEngineApplicationPlayer for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ApplicationPlayer : public ApplicationPlayerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ApplicationPlayerBase Inherited;
    typedef ApplicationPlayer     Self;

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
	virtual void attachApplication(void);
	virtual void dettachApplication(void);
	virtual void attachInterface(void);
	virtual void attachListeners(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);
    virtual void gotoScene(SceneRefPtr TheScene);
    void enableDebug(bool EnableDebug);

	CommandManagerPtr getCommandManager(void);
	void setCurrentAction(UInt32 action);
	UInt32 getCurrentAction(void);
	void setClonedNodeInCopyClipboard(NodeRefPtr node);
	NodeRefPtr getClonedNodeInCopyClipboard(void);
	UndoManagerPtr getUndoManager(void);
	NodeRefPtr getHighlightNode(void);
	void setHighlightNode(NodeRefPtr);
	ViewportRefPtr getDebugViewport(void);
	void setDebugViewport(ViewportRefPtr);
	HelperPanelRefPtr getHelperPanel(void);
	void setHelperPanel(HelperPanelRefPtr);
	NodeRefPtr getSelectedNode(void);
	void setSelectedNode(NodeRefPtr);
	void selectNode(const Pnt2f& ViewportPoint);
	ContentPanelRefPtr getContentPanel(void);
	void setContentPanel(ContentPanelRefPtr);

    Navigator& getDebugSceneNavigator(void);

    void moveDebugCamera(const Matrix& Transform);
    void resetDebugCamera(void);

    void setDebugView(UInt32 Index);
    void updateHighlightNode(void);
    void updateWireframeNode(void);
    
    void openEditor(FieldContainer* FCToEdit);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ApplicationPlayerBase.

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    class CommandManagerListener: public ChangeListener
    {
      public:
        CommandManagerListener(ApplicationPlayerRefPtr ApplicationPlayer);

        virtual void stateChanged(const ChangeEventUnrecPtr e);

        void setApplicationPlayer(ApplicationPlayerRefPtr TheApplicationPlayer);

      protected :
        ApplicationPlayerRefPtr _ApplicationPlayer;
    };
    friend class CommandManagerListener;
    CommandManagerListener _CommandManagerListener;


    class PlayerKeyListener : public KeyAdapter
    {
      public:
        PlayerKeyListener(ApplicationPlayerRefPtr TheApplicationPlayer);

        virtual void keyTyped(const KeyEventUnrecPtr e);
      protected :
        ApplicationPlayerRefPtr _ApplicationPlayer;
    };
    friend class PlayerKeyListener;
    PlayerKeyListener _PlayerKeyListener;


    class BasicListener : public ActionListener
    {
      public:
        BasicListener(ApplicationPlayerRefPtr TheApplicationPlayer);
        ~BasicListener();

        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        ApplicationPlayerRefPtr _ApplicationPlayer;

    };
    friend class BasicListener;
    BasicListener _BasicListener;



    class ComboBoxListener: public ComboBoxSelectionListener
    {
      public:
        void selectionChanged(const ComboBoxSelectionEventUnrecPtr e);

        ComboBoxListener(ApplicationPlayerRefPtr TheApplicationPlayer);
      protected:
        ApplicationPlayerRefPtr _ApplicationPlayer;
    };
    friend class ComboBoxListener;
    ComboBoxListener _ComboBoxListener;



    class GotoSceneItemListener : public ActionListener
    {
      public:
        GotoSceneItemListener(ApplicationPlayerRefPtr TheApplicationPlayer);
        ~GotoSceneItemListener();

        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        ApplicationPlayerRefPtr _ApplicationPlayer;

    };
    friend class GotoSceneItemListener;
    GotoSceneItemListener _GotoSceneItemListener;



    class ProjectListener : public EventListener
    {
      public:
        ProjectListener(ApplicationPlayerRefPtr TheApplicationPlayer);
        ~ProjectListener();

        virtual void eventProduced(const EventUnrecPtr e, UInt32 EventProducedId);
      protected :
        ApplicationPlayerRefPtr _ApplicationPlayer;

    };
    friend class ProjectListener;
    ProjectListener _ProjectListener;



    class highlightNodeListener : public UpdateListener
    {
      public:
        highlightNodeListener(ApplicationPlayerRefPtr TheApplicationPlayer);
        ~highlightNodeListener();

        virtual void update(const UpdateEventUnrecPtr e);
      protected :
        ApplicationPlayerRefPtr _ApplicationPlayer;

    };
    friend class highlightNodeListener;
    highlightNodeListener _highlightNodeListener;


    NodeRefPtr _HighlightNode;
    NodeRefPtr _HighlightVolumeBoxNode;
    GeometryRefPtr _HighlightVolumeBoxGeo;
    LineChunkRefPtr _HighlightBoundBoxMatLineChunk;
    NodeRefPtr _HighlightAxisNode;
    GeometryRefPtr _HighlightAxisGeo;
    LineChunkRefPtr _HighlightAxisLineChunk;
    NodeRefPtr _WireframeMatGroupNode;
    NodeRefPtr _WireframeNode;
    TransformRefPtr _WireframeTransform;
    MaterialChunkRefPtr _WireframeMatMaterialChunk;
    LineChunkRefPtr _WireframeMatLineChunk;
    NodeRefPtr _SelectedNode;
    NodeRefPtr _WorkspaceGrid;
    LineChunkRefPtr _WorkspaceGridLineChunk;

    HierarchyPanelRefPtr	_HierarchyPanel;
    HelperPanelRefPtr		_HelperPanel;
    ContentPanelRefPtr		_ContentPanel;

    ViewportRefPtr _DebugViewport;

    enum cActions{NONE,CUT,COPY};

    NodeRefPtr _ClonedNodeInCopyClipboard;

    CommandManagerPtr				_TheCommandManager;
    UndoManagerPtr					_TheUndoManager;
    CommandActionListenerForPlayer	_UndoActionListener;
    CommandActionListenerForPlayer	_RedoActionListener;


    PanelRefPtr					_ToolbarAndContentPanel;

    PanelRefPtr			_Toolbar;

    ButtonRefPtr	_OpenFileButton;
    ButtonRefPtr	_SaveFileButton;
    ButtonRefPtr	_CloseFileButton;


    MenuItemRefPtr _ResetItem ;				
    MenuItemRefPtr _ForceQuitItem ;			

    MenuItemRefPtr _UndoItem ;				
    MenuItemRefPtr _RedoItem ;				


    MenuItemRefPtr _NextItem ;				
    MenuItemRefPtr _PrevItem ;				
    MenuItemRefPtr _FirstItem;				
    MenuItemRefPtr _LastItem ;				
    MenuRefPtr		_SceneSubItem ;				

    MenuItemRefPtr _FlyNavigatorItem ;		
    MenuItemRefPtr _TrackballNavigatorItem ;
    MenuItemRefPtr _BasicItem ;				
    MenuItemRefPtr _RenderItem ;			
    MenuItemRefPtr _PhysicsItem ;			
    MenuItemRefPtr _ParticleSystemItem ;	
    MenuItemRefPtr _AnimationItem ;			
    MenuItemRefPtr _PauseActiveUpdatesItem;			
    MenuItemRefPtr _DrawBoundingVolumesItem ;		
    MenuItemRefPtr _FrustrumCullingItem  ;
    MenuItemRefPtr _DrawPhysicsCharacteristicsItem  ;


    MenuRefPtr		_EditMenu;
    MenuRefPtr		_ProjectMenu;
    MenuRefPtr		_SceneMenu;
    MenuRefPtr		_NavigatorMenu;
    MenuRefPtr		_StatisticsMenu;
    MenuRefPtr		_ToggleMenu;
    MenuBarRefPtr	_MainMenuBar;

    BorderLayoutConstraintsRefPtr	_DebugWindowSplitPanelConstraints;
    SplitPanelRefPtr				_DebugWindowSplitPanel;

    BorderLayoutConstraintsRefPtr	_TopHalfSplitPanelConstraints;
    SplitPanelRefPtr				_TopHalfSplitPanel;

    DefaultMutableComboBoxModelRefPtr	_ModeComboBoxModel;
    ComboBoxRefPtr						_ModeComboBox;

    NodeRefPtr _DebugBeacon;

    bool _IsDebugActive;

    SimpleStatisticsForegroundRefPtr _DebugBasicStatForeground;
    SimpleStatisticsForegroundRefPtr _DebugRenderStatForeground;
    SimpleStatisticsForegroundRefPtr _DebugPhysicsStatForeground;
    SimpleStatisticsForegroundRefPtr _DebugParticleSystemStatForeground;
    SimpleStatisticsForegroundRefPtr _DebugAnimationStatForeground;

    //Debug Camera
    CameraRefPtr    _SceneViewportCamera;
    CameraRefPtr    _DebugCamera;
    NodeRefPtr      _DebugCameraBeacon;
    TransformRefPtr _DebugBeaconTransform;

    //Camera Navigator
    Navigator    _DebugSceneNavigator;

    //Debug Camera Animation
    KeyframeTransformationSequenceRefPtr _DebugCameraTransformationKeyframes;
    //KeyframeNumbersSequenceRefPtr _DebugCameraFovKeyframes;
    FieldAnimationRefPtr _DebugCameraTransAnimation;
    //FieldAnimationRefPtr _DebugCameraFovAnimation;
    AnimationGroupRefPtr _DebugCameraAnimationGroup;

    void updateListBox(void);
    void setupPopupMenu();
    void invertShowHideCaption();

    void keyTyped(const KeyEventUnrecPtr e);
    void actionPerformed(const ActionEventUnrecPtr e);

    ViewportRefPtr createDebugViewport(void);
    void attachDebugViewport(void);
    void detachDebugViewport(void);
    void updateDebugViewport(void);

    void createDebugCameraAnim(void);

    virtual void attachDebugInterface(void);
    virtual void detachDebugInterface(void);
    virtual void createDebugInterface(void);

    void updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager);
    void createGotoSceneMenuItems(ProjectRefPtr TheProject);
    void updateGotoSceneMenuItems(ProjectRefPtr TheProject);
    void updateDebugUI(void);

    void initDebugStatForegrounds(void);
    void hideAllStatForegrounds(void);
    void toggleStatForeground(StatisticsForegroundRefPtr TheForeground);
    void toggleDrawBoundingVolumes(void);
    void toggleFrustumCulling(void);
    void toggleDrawPhysicsCharacteristics(void);
    void toggleSceneInputBlocking(void);
    void setSceneInputBlocking(bool block);

    NodeRefPtr getPhysicsDrawableNode(void);
    void updateDebugSceneChange(void);

    void createHighlightNode(void);
    void createHighlightBoundBoxNode(void);
    void createHighlightAxisNode(void);
    void createHighlightTriMeshNode(void);

    InternalWindowRefPtr MainInternalWindow;		
    GraphicsRefPtr DebuggerGraphics;				
    UIForegroundRefPtr DebuggerUIForeground;		
    UIDrawingSurfaceRefPtr DebuggerDrawingSurface;	

    void updateWindowTitle(void);

    PhysicsCharacteristicsDrawableRefPtr _PhysDrawable;
    NodeRefPtr                           _PhysDrawableNode;
    bool _WasMouseHidden;
    bool _WasMouseAttached;

    void updateFromSettings(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ApplicationPlayerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ApplicationPlayer &source);
};

typedef ApplicationPlayer *ApplicationPlayerP;

OSG_END_NAMESPACE

#include "Player/HierarchyPanel/KEHierarchyPanel.h"
#include "Player/HelperPanel/KEHelperPanel.h"
#include "Player/ContentPanel/KEContentPanel.h"
#include "KEApplicationPlayerBase.inl"
#include "KEApplicationPlayer.inl"

#endif /* _KEAPPLICATIONPLAYER_H_ */
