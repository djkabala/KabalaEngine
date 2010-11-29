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

#ifndef _KEHIERARCHYPANEL_H_
#define _KEHIERARCHYPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KEHierarchyPanelBase.h"
#include <OpenSG/OSGTreeFields.h>
#include <OpenSG/OSGSceneGraphTreeModelFields.h>
#include "Player/LuaGraphTreeModel/KELuaGraphTreeModelFields.h"
#include <OpenSG/OSGFixedHeightTreeModelLayoutFields.h>

#include <OpenSG/OSGPanelFields.h>

#include <OpenSG/OSGCardLayoutFields.h>
#include <OpenSG/OSGGridBagLayoutFields.h>
#include <OpenSG/OSGGridBagLayoutConstraintsFields.h>

#include <OpenSG/OSGSimpleMaterialFields.h>

#include <set>

#include <OpenSG/OSGScrollPanelFields.h>
#include <OpenSG/OSGBorderLayoutFields.h>
#include <OpenSG/OSGBorderLayoutConstraintsFields.h>

#include "Project/KEProjectFields.h"

#include "Application/KEMainApplication.h"

#include <OpenSG/OSGDerivedFieldContainerComboBoxModelFields.h>
#include <OpenSG/OSGFlowLayoutFields.h>
#include <OpenSG/OSGMenuButtonFields.h>
#include <OpenSG/OSGMenuItemFields.h>
#include <OpenSG/OSGMenuFields.h>
#include <OpenSG/OSGButtonFields.h>

#include <OpenSG/OSGTextEditorFields.h>


#include <OpenSG/OSGCameraFields.h>
#include <OpenSG/OSGPerspectiveCameraFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>
#include <OpenSG/OSGPopupMenuEventDetailsFields.h>
#include <OpenSG/OSGTreeSelectionEventDetailsFields.h>

#include "Player/KEApplicationPlayerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief HierarchyPanel class. See \ref
           PageKabalaEngineHierarchyPanel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING HierarchyPanel : public HierarchyPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HierarchyPanelBase Inherited;
    typedef HierarchyPanel     Self;

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
	
	SceneGraphTreeModel* getSceneGraphTreeModel(void);
	Tree* getSceneGraphTree(void);
	ApplicationPlayer* getApplicationPlayer(void);

	void createSceneGraphTree(void);
	void createLuaGraphTree(void);
	void createPanel(void);
	void addTab(UInt32 tabno);
	void removeTab(UInt32 tabno);
	void createDefaultHierarchyPanel();
	void setApplicationPlayer(ApplicationPlayer* const TheApplicationPlayer);

    void setView(UInt32 Index);
    /*=========================  PROTECTED  ===============================*/

  protected:

	// Variables should all be in HierarchyPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HierarchyPanel(void);
    HierarchyPanel(const HierarchyPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HierarchyPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    enum Tabs
    {
        SCENEGRAPH_TAB = 0,
        LUA_TAB = 1
    };

    std::set<UInt32>			_TabsAdded;
    std::set<UInt32>::iterator	_TabsAddedItr;
    SceneGraphTreeModelRefPtr		_TheSceneGraphTreeModel;
    LuaGraphTreeModelRefPtr		_TheLuaGraphTreeModel;
    TreeRefPtr						_TheSceneGraphTree;
    TreeRefPtr						_TheLuaGraphTree;
    NodeRefPtr						_SelectedNode;

    ScrollPanelRefPtr				_TheSceneGraphTreeScrollPanel;
    ScrollPanelRefPtr				_TheLuaGraphTreeScrollPanel;
    NodeRefPtr						_HighlightNode;

    CardLayoutRefPtr				_CardLayout;
    BorderLayoutConstraintsRefPtr	_LayoutConstraints;

	PanelRefPtr						_ButtonPanel;
	GridBagLayoutRefPtr				_ButtonPanelLayout;
	GridBagLayoutConstraintsRefPtr _CreateNewNodeButtonConstraints;
	GridBagLayoutConstraintsRefPtr _SaveFileButtonConstraints;
	GridBagLayoutConstraintsRefPtr _LoadFileButtonConstraints;


    ApplicationPlayerRefPtr _ApplicationPlayer;
    DerivedFieldContainerComboBoxModelRefPtr _NewNodeMenuModel;
    MenuButtonRefPtr _CreateNewNodeMenuButton;
	ButtonRefPtr _LoadFileButton;
	ButtonRefPtr _SaveFileButton;
    PanelRefPtr _SceneGraphPanel;

    PopupMenuRefPtr _HierarchyPanelPopupMenu;

    MenuItemRefPtr _ShowHideItem ;
    MenuItemRefPtr _ShowRecursiveItem ;
    MenuItemRefPtr _CutItem ;
    MenuItemRefPtr _CopyItem ;
    MenuItemRefPtr _PasteItem ;
    MenuItemRefPtr _PasteInstanceItem ;
    MenuItemRefPtr _DeleteItem ;
    MenuItemRefPtr _ImportItem ;
    MenuItemRefPtr _ExportItem ;
    MenuItemRefPtr _FocusCamera ;
    MenuItemRefPtr _OpenEditor;

    //Graph Operation Menus
	MenuRefPtr     _GraphOpMenu;
	MenuItemRefPtr _MaskGraphOpItem;
	MenuItemRefPtr _LodGraphOpItem;
	MenuItemRefPtr _GeoMergeGraphOpItem;
	MenuItemRefPtr _SplitGraphOpItem;
	MenuItemRefPtr _PruneGraphOpItem;
	MenuItemRefPtr _XformPushGraphOpItem;
	MenuItemRefPtr _MaterialGroupGraphOpItem;
	MenuItemRefPtr _SharePtrGraphOpItem;
	MenuItemRefPtr _AttachColGeomOpItem;

    
    //Physics Menus
    MenuRefPtr     _PhysicsMenu;
	MenuItemRefPtr _PhysicsBodyItem;

    //Geoms
    MenuRefPtr     _PhysicsGeomMenu;
	MenuItemRefPtr _PhysicsSphereGeomItem;
	MenuItemRefPtr _PhysicsBoxGeomItem;
	MenuItemRefPtr _PhysicsCapsuleGeomItem;
	MenuItemRefPtr _PhysicsPlaneGeomItem;
	MenuItemRefPtr _PhysicsRayGeomItem;
	MenuItemRefPtr _PhysicsTriMeshGeomItem;

    //Spaces
	MenuItemRefPtr _PhysicsSpaceItem;

    //Joints
    MenuRefPtr     _PhysicsJointMenu;
	MenuItemRefPtr _PhysicsAMotorJointItem;
	MenuItemRefPtr _PhysicsBallJointItem;
	MenuItemRefPtr _PhysicsHinge2JointItem;
	MenuItemRefPtr _PhysicsHingeJointItem;
	MenuItemRefPtr _PhysicsLMotorJointItem;
	MenuItemRefPtr _PhysicsPistonJointItem;
	MenuItemRefPtr _PhysicsPlane2DJointItem;
	MenuItemRefPtr _PhysicsPRJointItem;
	MenuItemRefPtr _PhysicsPUJointItem;
	MenuItemRefPtr _PhysicsSliderJointItem;
	MenuItemRefPtr _PhysicsUniversalJointItem;

    void createPopUpMenu(void);
    void updatePopupMenu(void);
    void changeShowHideMenuItem(void);
    void updatePhysicsMenuItems(void);

    void handleLuaGraphTreeSelectionAdded(TreeSelectionEventDetails* const details);
    boost::signals2::connection _LuaGraphTreeSelectionAddedConnection;

    void handleSceneGraphTreeSelectionAdded(TreeSelectionEventDetails* const details);
    void handleSceneGraphTreeSelectionRemoved(TreeSelectionEventDetails* const details);
    void selectedNodeChanged(void);
    boost::signals2::connection _SceneGraphTreeSelectionAddedConnection,
                                _SceneGraphTreeSelectionRemovedConnection;

    void handleSceneGraphTreeKeyTyped(KeyEventDetails* const details);
    boost::signals2::connection _SceneGraphTreeKeyTypedConnection;

    void handleLuaGraphTreeMouseClicked(MouseEventDetails* const details);
    void handleNewNodeMenuButtonAction(ActionEventDetails* const details);
	void handleLoadButtonAction(ActionEventDetails* const details);
	void handleSaveButtonAction(ActionEventDetails* const details);
    void handleSceneGraphPopupMenuWillBecomeVisible   (PopupMenuEventDetails* const details);
    boost::signals2::connection _LuaGraphTreeMouseClickedConnection,
                                _NewNodeMenuButtonActionConnection,
                                _SceneGraphPopupMenuWillBecomeVisibleConnection;

    void changeDebugCameraPosition(void);

    
    /*---------------------------------------------------------------------*/
    /*! \name               Scene Graph Commands                           */
    /*! \{                                                                 */

    void handleShowHideToggleSelectedNode(EventDetails* const details);
    void handleImportIntoSelectedNode(EventDetails* const details);
    void handleExportSelectedNode(EventDetails* const details);
    void handleFocusCameraOnSelectedNode(EventDetails* const details);
    void handleCopySelectedNode(EventDetails* const details);
    void handleCutSelectedNode(EventDetails* const details);
    void handlePasteOntoSelectedNode(EventDetails* const details);
    void handlePasteInstOntoSelectedNode(EventDetails* const details);
    void handleShowHideSelectedNodeRecursize(EventDetails* const details);
    void handleDeleteSelectedNode(EventDetails* const details);
    void handleRunTravMaskGraphOp(EventDetails* const details);
	void handleRunLODGraphOp(EventDetails* const details);
	void handleRunGeoMergeGraphOp(EventDetails* const details);
	void handleRunSplitGraphOp(EventDetails* const details);
	void handleRunPruneGraphOp(EventDetails* const details);
	void handleRunXformPushGraphOp(EventDetails* const details);
	void handleRunMaterialGroupGraphOp(EventDetails* const details);
	void handleRunSharePtrGraphOp(EventDetails* const details);
	void handleRunAttachColGeomGraphOp(EventDetails* const details);

	void handleOpenEditorMenuItem(EventDetails* const details);
    
	void handlePhysicsBodyMenuItem(EventDetails* const details);

	void handlePhysicsSphereGeomMenuItem(EventDetails* const details);
	void handlePhysicsBoxGeomMenuItem(EventDetails* const details);
	void handlePhysicsCapsuleGeomMenuItem(EventDetails* const details);
	void handlePhysicsPlaneGeomMenuItem(EventDetails* const details);
	void handlePhysicsRayGeomMenuItem(EventDetails* const details);
	void handlePhysicsTriMeshGeomMenuItem(EventDetails* const details);
	void handlePhysicsSpaceMenuItem(EventDetails* const details);

	void handlePhysicsAMotorJointMenuItem(EventDetails* const details);
	void handlePhysicsBallJointMenuItem(EventDetails* const details);
	void handlePhysicsHinge2JointMenuItem(EventDetails* const details);
	void handlePhysicsHingeJointMenuItem(EventDetails* const details);
	void handlePhysicsLMotorJointMenuItem(EventDetails* const details);
	void handlePhysicsPistonJointMenuItem(EventDetails* const details);
	void handlePhysicsPlane2DJointMenuItem(EventDetails* const details);
	void handlePhysicsPRJointMenuItem(EventDetails* const details);
	void handlePhysicsPUJointMenuItem(EventDetails* const details);
	void handlePhysicsSliderJointMenuItem(EventDetails* const details);
	void handlePhysicsUniversalJointMenuItem(EventDetails* const details);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HierarchyPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HierarchyPanel &source);
};

typedef HierarchyPanel *HierarchyPanelP;

OSG_END_NAMESPACE

#include "KEHierarchyPanelBase.inl"
#include "KEHierarchyPanel.inl"

#endif /* _KEHIERARCHYPANEL_H_ */
