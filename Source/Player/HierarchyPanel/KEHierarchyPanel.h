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
#include <OpenSG/OSGTree.h>
#include <OpenSG/OSGSceneGraphTreeModel.h>
#include "Player/LuaGraphTreeModel/KELuaGraphTreeModel.h"
#include <OpenSG/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/OSGTreeSelectionListener.h>

#include <OpenSG/OSGPanel.h>

#include <OpenSG/OSGCardLayout.h>
#include <OpenSG/OSGGridLayout.h>

#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGNameAttachment.h> // FOR ATTACHING NAMES TO NODES ETC.

#include <set>

#include <OpenSG/OSGScrollPanel.h>
#include <OpenSG/OSGBorderLayout.h>
#include <OpenSG/OSGBorderLayoutConstraints.h>

#include "Project/KEProject.h"

#include "Application/KEMainApplication.h"

#include <OpenSG/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/OSGFlowLayout.h>
#include <OpenSG/OSGMenuButton.h>


#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGMatrixUtility.h>

#include "Player/KEApplicationPlayer.h"

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
	
	SceneGraphTreeModelRefPtr getSceneGraphTreeModel(void);
	TreeRefPtr getSceneGraphTree(void);
	ApplicationPlayerRefPtr getApplicationPlayer(void);

	void createSceneGraphTree(void);
	void createLuaGraphTree(void);
	void createPanel(void);
	void addTab(UInt32 tabno);
	void removeTab(UInt32 tabno);
	void createDefaultHierarchyPanel();
	void setApplicationPlayer(ApplicationPlayerRefPtr TheApplicationPlayer);

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

    enum tabs{LUA=1,SCENEGRAPH};

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

    ApplicationPlayerRefPtr _ApplicationPlayer;
    DerivedFieldContainerComboBoxModelRefPtr _NewNodeMenuModel;
    MenuButtonRefPtr _CreateNewNodeMenuButton;
    PanelRefPtr _SceneGraphPanel;
    BorderLayoutConstraintsRefPtr _CreateNewButtonConstraints;

    PopupMenuRefPtr _HierarchyPanelPopupMenu;

    MenuItemRefPtr _ShowHideItem ;
    MenuItemRefPtr _ShowRecursiveItem ;
    MenuItemRefPtr _CutItem ;
    MenuItemRefPtr _CopyItem ;
    MenuItemRefPtr _PasteItem ;
    MenuItemRefPtr _PasteInstanceItem ;
    MenuItemRefPtr _DeleteItem ;
    MenuItemRefPtr _FocusCamera ;

    void createPopUpMenu(void);
    void updatePopupMenu(void);
    void changeShowHideMenuItem(void);
    void actionPerformed(const ActionEventUnrecPtr e);

    class BasicListener : public ActionListener
    {
      public:
        BasicListener(HierarchyPanelRefPtr TheHierarchyPanel);
        ~BasicListener();

        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        HierarchyPanelRefPtr _HierarchyPanel;

    };
    friend class BasicListener;
    BasicListener _BasicListener;

    class LuaGraphTreeSelectionListener : public TreeSelectionListener
    {
      public:

        LuaGraphTreeSelectionListener(HierarchyPanelRefPtr TheHierarchyPanel);

        void selectionAdded(const TreeSelectionEventUnrecPtr e);
        void selectionRemoved(const TreeSelectionEventUnrecPtr e){};
        void setParams(TreeRefPtr,ApplicationPlayerRefPtr);

      protected:
        HierarchyPanelRefPtr _HierarchyPanel;
        TreeRefPtr _TheTree;
        ApplicationPlayerRefPtr _ApplicationPlayer;
        BoostPath _SelectedPath;
    };

    friend class LuaGraphTreeSelectionListener;
    LuaGraphTreeSelectionListener _LuaGraphTreeSelectionListener;

    class SceneGraphTreeSelectionListener : public TreeSelectionListener
    {
      public:
        SceneGraphTreeSelectionListener(HierarchyPanelRefPtr TheHierarchyPanel);

        void selectionAdded(const TreeSelectionEventUnrecPtr e);
        void selectionRemoved(const TreeSelectionEventUnrecPtr e);
        void selectedNodeChanged(void);
        void setParams(TreeRefPtr,ApplicationPlayerRefPtr);

        friend class ShowHideCommand;

        NodeRefPtr _SelectedNode;
      protected:
        HierarchyPanelRefPtr _HierarchyPanel;
        TreeRefPtr _TheTree;
        ApplicationPlayerRefPtr _ApplicationPlayer;
    };

    friend class SceneGraphTreeSelectionListener;
    SceneGraphTreeSelectionListener _SceneGraphTreeSelectionListener;



    class PlayerMouseListener2 : public MouseAdapter
    {
      public:
        PlayerMouseListener2(HierarchyPanelRefPtr TheHierarchyPanel);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
      protected :
        HierarchyPanelRefPtr _HierarchyPanel;
    };

    friend class PlayerMouseListener2;
    PlayerMouseListener2 _PlayerMouseListener2;


    class MenuButtonActionListener : public ActionListener
    {
      public:
        MenuButtonActionListener(HierarchyPanelRefPtr TheHierearchyPanel);

        void actionPerformed(const ActionEventUnrecPtr e);
      protected:
        void createNewNode(const ActionEventUnrecPtr e);
        HierarchyPanelRefPtr _HierarchyPanel;
    };

    friend class MenuButtonActionListener;
    MenuButtonActionListener _TheMenuButtonActionListener;

    class SceneGraphPopupListener : public PopupMenuListener
    {
      public:
        SceneGraphPopupListener(HierarchyPanelRefPtr TheHierearchyPanel);

        void popupMenuCanceled            (const  PopupMenuEventUnrecPtr e);
        void popupMenuWillBecomeInvisible (const  PopupMenuEventUnrecPtr e);
        void popupMenuWillBecomeVisible   (const  PopupMenuEventUnrecPtr e);
        void popupMenuContentsChanged     (const  PopupMenuEventUnrecPtr e);

      protected:
        HierarchyPanelRefPtr _HierarchyPanel;
    };

    friend class SceneGraphPopupListener;
    SceneGraphPopupListener _TheSceneGraphPopupListener;

    void changeDebugCameraPosition(void);
    void showAll(CameraRefPtr TheCameraOrig,
                 NodeRefPtr Scene,
                 ViewportRefPtr LocalViewport);
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
