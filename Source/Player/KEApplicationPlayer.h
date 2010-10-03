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

#include <OpenSG/OSGViewportFields.h>
#include <OpenSG/OSGTransformFields.h>
#include <OpenSG/OSGLineChunkFields.h>
#include <OpenSG/OSGMaterialChunkFields.h>
#include <OpenSG/OSGNavigator.h>

#include <OpenSG/OSGSimpleStatisticsForegroundFields.h>
#include <OpenSG/OSGMenuFields.h>
#include <OpenSG/OSGMenuItemFields.h>
#include <OpenSG/OSGMenuBarFields.h>
#include <OpenSG/OSGTextAreaFields.h>
#include <OpenSG/OSGLuaManager.h>
#include <OpenSG/OSGTabPanelFields.h>
#include <OpenSG/OSGButtonFields.h>
#include <OpenSG/OSGColorLayerFields.h>
#include <OpenSG/OSGBorderLayoutFields.h>
#include <OpenSG/OSGBorderLayoutConstraintsFields.h>
//text area
#include <OpenSG/OSGScrollPanelFields.h>

//split panel 
#include <OpenSG/OSGSplitPanelFields.h>

//spring layout
#include <OpenSG/OSGSpringLayoutFields.h>
#include <OpenSG/OSGSpringLayoutConstraintsFields.h>
#include <OpenSG/OSGLabelFields.h>
#include <OpenSG/OSGBoxLayoutFields.h>
#include <OpenSG/OSGComponentContainerFields.h>
#include <OpenSG/OSGPanelFields.h>

// UserInterface Headers
#include <OpenSG/OSGUIForegroundFields.h>
#include <OpenSG/OSGInternalWindowFields.h>
#include <OpenSG/OSGUIDrawingSurfaceFields.h>
#include <OpenSG/OSGGraphics2DFields.h>
#include <OpenSG/OSGLookAndFeelManager.h>


#include <OpenSG/OSGPhysicsCharacteristicsDrawable.h>
#include <OpenSG/OSGNodeFields.h>

// tree headers

#include <OpenSG/OSGTreeFields.h>
#include <OpenSG/OSGSceneGraphTreeModelFields.h>
#include <OpenSG/OSGFixedHeightTreeModelLayoutFields.h>
#include <OpenSG/OSGGridLayoutFields.h>


// List header files
#include <OpenSG/OSGListFields.h>
#include <OpenSG/OSGDefaultListModelFields.h>
#include <OpenSG/OSGDefaultListSelectionModelFields.h>
#include <OpenSG/OSGFlowLayoutFields.h>

//Combobox
#include <OpenSG/OSGComboBoxFields.h>
#include <OpenSG/OSGDefaultMutableComboBoxModelFields.h>

//cardlayout
#include <OpenSG/OSGCardLayoutFields.h>

#include <OpenSG/OSGCommand.h>
#include <OpenSG/OSGUndoManager.h>
#include <OpenSG/OSGCommandManager.h>
 
#include "Player/HierarchyPanel/KEHierarchyPanelFields.h"
#include "Player/HelperPanel/KEHelperPanelFields.h"
#include "Player/ContentPanel/KEContentPanelFields.h"
#include <OpenSG/OSGDialogWindowFields.h>

#include <OpenSG/OSGComboBoxSelectionEventDetailsFields.h>
#include <OpenSG/OSGStatisticsForegroundFields.h>

//Animation
#include <OpenSG/OSGKeyframeSequences.h>
#include <OpenSG/OSGKeyframeAnimatorFields.h>
#include <OpenSG/OSGFieldAnimationFields.h>
#include <OpenSG/OSGAnimationGroupFields.h>


//XForm Manipulator
#include <OpenSG/OSGManipulatorManager.h>
#include <OpenSG/OSGReplicateTransformFields.h>

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

    enum DebugGraphMasks
    {
        DEBUG_GRAPH_NONE          = 0x0,
        DEBUG_GRAPH_DRAWN         = 0x1,
        DEBUG_GRAPH_INTERSECTABLE = 0x2
    };

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
	virtual void attachHandlers(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);
    virtual void gotoScene(SceneRefPtr TheScene);
    void enableDebug(bool EnableDebug);
    bool isDebugging(void) const;

	CommandManagerPtr getCommandManager(void);
	void setCurrentAction(UInt32 action);
	UInt32 getCurrentAction(void);
	void setClonedNodeInCopyClipboard(NodeRefPtr node);
	Node* getClonedNodeInCopyClipboard(void);
	UndoManagerPtr getUndoManager(void);
	Node* getHighlightNode(void);
	void setHighlightNode(NodeRefPtr);
	Viewport* getDebugViewport(void);
	void setDebugViewport(ViewportRefPtr);
	HelperPanel* getHelperPanel(void);
	void setHelperPanel(HelperPanelRefPtr);
	Node* getSelectedNode(void);
	void setSelectedNode(NodeRefPtr);
	void selectNode(const Pnt2f& ViewportPoint);
	ContentPanel* getContentPanel(void);
	void setContentPanel(ContentPanelRefPtr);

    Navigator& getDebugSceneNavigator(void);

    void moveDebugCamera(const Matrix& Transform);
    void resetDebugCamera(void);

    void setDebugView(UInt32 Index);
    void updateHighlightNode(void);
    void updateWireframeNode(void);
    void updateXFormManipulator(void);
    
    const ManipulatorManager& getXFormManipMgr(void) const;
    ManipulatorManager& editXFormManipMgr(void);
    
    void openEditor(void);

    void openEditor(FieldContainer* FCToEdit);

    void focusSelectedNode(void);
    void showAll(CameraRefPtr TheCameraOrig,
                 NodeRefPtr Scene,
                 ViewportRefPtr LocalViewport);

    UIDrawingSurface* const getDebuggerDrawingSurface(void) const;
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

    void handleCommandManagerStateChanged(ChangeEventDetails* const details);

    void handlePlayerKeyTyped(KeyEventDetails* const details);
    boost::signals2::connection _PlayerKeyTypedConnection;

    void handleBasicAction(ActionEventDetails* const details);

    void handleComboBoxSelectionChanged(ComboBoxSelectionEventDetails* const details);

    void handleGotoSceneItemAction(ActionEventDetails* const details);

    void handleProjectSceneChanged(ProjectEventDetails* const details);
    boost::signals2::connection _ProjectSceneChangedConnection;
    
    void handleUndoButtonAction(ActionEventDetails* const details);
    void handleRedoButtonAction(ActionEventDetails* const details);
    void handleEditProjectAction(ActionEventDetails* const details);
    void handleOpenEditorAction(ActionEventDetails* const details);

    void handleHighlightNodeUpdate(UpdateEventDetails* const details);
    boost::signals2::connection _HighlightNodeUpdateConnection;

    void handleStatisticsReset(UpdateEventDetails* const details);
    boost::signals2::connection _StatisticsResetConnection;

    //Selected Node
    NodeRefPtr _SelectedNode;

    void createGenericEditor(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Visual Annotations                          */
    /*! \{                                                                 */

    //Main Highlight Node
    NodeRefPtr _HighlightNode;

    //Volume Box
    NodeRefPtr _HighlightVolumeBoxNode;
    GeometryRefPtr _HighlightVolumeBoxGeo;
    LineChunkRefPtr _HighlightBoundBoxMatLineChunk;

    //Local Coordinate Axis
    NodeRefPtr _HighlightAxisNode;
    GeometryRefPtr _HighlightAxisGeo;
    LineChunkRefPtr _HighlightAxisLineChunk;

    //Mesh Wireframe
    NodeRefPtr _WireframeMatGroupNode;
    NodeRefPtr _WireframeNode;
    ReplicateTransformRefPtr _WireframeTransform;
    MaterialChunkRefPtr _WireframeMatMaterialChunk;
    LineChunkRefPtr _WireframeMatLineChunk;

    //Workspace grid
    NodeRefPtr _WorkspaceGrid;
    LineChunkRefPtr _WorkspaceGridLineChunk;

    //Transformation Manipulators
    ManipulatorManager _XFormManipMgr;
    NodeRefPtr         _XFormManipNode;
    ReplicateTransformRefPtr _XFormManipNodeCore;

    /*! \}                                                                 */

    HierarchyPanelRefPtr	_HierarchyPanel;
    HelperPanelRefPtr		_HelperPanel;
    ContentPanelRefPtr		_ContentPanel;

    ViewportRefPtr _DebugViewport;

    DialogWindowRecPtr _GenericEditorDialog;

    enum cActions{NONE,CUT,COPY};

    NodeRefPtr _ClonedNodeInCopyClipboard;

    CommandManagerPtr				_TheCommandManager;
    UndoManagerPtr					_TheUndoManager;


    PanelRefPtr					_ToolbarAndContentPanel;

    MenuItemRefPtr _LoadProjectItem;				
    MenuItemRefPtr _SaveProjectItem;				
    MenuItemRefPtr _SaveProjectAsItem;
    MenuItemRefPtr _ResetProjectItem;
    MenuItemRefPtr _ForceQuitItem;			

    MenuItemRefPtr _UndoItem;
    MenuItemRefPtr _RedoItem;
    MenuItemRefPtr _EditProjectItem;
    MenuItemRefPtr _OpenEditorItem;


    MenuItemRefPtr _NextSceneItem;				
    MenuItemRefPtr _PrevSceneItem;				
    MenuItemRefPtr _FirstSceneItem;				
    MenuItemRefPtr _LastSceneItem;
    MenuItemRefPtr _ResetSceneItem;
    MenuRefPtr		_SceneSubItem;				

    MenuItemRefPtr _FlyNavigatorItem;		
    MenuItemRefPtr _TrackballNavigatorItem;
    MenuItemRefPtr _BasicStatsItem;				
    MenuItemRefPtr _RenderStatsItem;			
    MenuItemRefPtr _PhysicsStatsItem;			
    MenuItemRefPtr _ParticleSystemStatsItem;	
    MenuItemRefPtr _AnimationStatsItem;	
    MenuItemRefPtr _ConfigurableStatsItem;
    MenuItemRefPtr _PauseActiveUpdatesItem;			
    MenuItemRefPtr _DrawBoundingVolumesItem;		
    MenuItemRefPtr _FrustrumCullingItem;
    MenuItemRefPtr _DrawPhysicsCharacteristicsItem;


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
    SimpleStatisticsForegroundRefPtr _ConfigurableStatForeground;

    //Debug Camera
    CameraRefPtr    _SceneViewportCamera;
    CameraRefPtr    _DebugCamera;
    NodeRefPtr      _DebugCameraBeacon;
    TransformRefPtr _DebugBeaconTransform;
    ViewportRefPtr  _SceneViewport;

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

    ViewportRefPtr createDebugViewport(void);
    void attachDebugViewport(void);
    void detachDebugViewport(void);
    void updateDebugViewport(void);

    void attachDebugViewportCamera(void);
    void detachDebugViewportCamera(void);

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
    void toggleStatForeground(StatisticsForeground* const TheForeground);
    void toggleDrawBoundingVolumes(void);
    void toggleFrustumCulling(void);
    void toggleDrawPhysicsCharacteristics(void);
    void toggleSceneInputBlocking(void);
    void setSceneInputBlocking(bool block);

    Node* getPhysicsDrawableNode(void);
    void updateDebugSceneChange(void);

    void createHighlightNode(void);
    void createHighlightBoundBoxNode(void);
    void createHighlightAxisNode(void);
    void createHighlightTriMeshNode(void);
    void createXFormManipulator(void);

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
