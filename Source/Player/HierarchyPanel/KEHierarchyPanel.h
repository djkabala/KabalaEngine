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

#ifndef _KEHIERARCHYPANEL_H_
#define _KEHIERARCHYPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEHierarchyPanelBase.h"


#include <OpenSG/UserInterface/OSGTree.h>
#include <OpenSG/UserInterface/OSGSceneGraphTreeModel.h>
#include "Player/LuaGraphTreeModel/KELuaGraphTreeModel.h"
#include <OpenSG/UserInterface/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/UserInterface/OSGTreeSelectionListener.h>
#include <OpenSG/Toolbox/OSGGeometryUtils.h>

#include <OpenSG/UserInterface/OSGPanel.h>

#include <OpenSG/UserInterface/OSGCardLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>

#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGSimpleAttachments.h> // FOR ATTACHING NAMES TO NODES ETC.

#include <set>
#include <vector>

#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>

#include "Player/KEApplicationPlayerFields.h"
#include "Project/KEProjectFields.h"
#include "Project/Scene/KESceneFields.h"

#include "Application/KEMainApplication.h"

#include "Player/HelperPanel/KEHelperPanelFields.h"

#include "Player/Commands/KEShowHideCommand.h"
#include "Player/Commands/KEDeleteCommand.h"
#include "Player/Commands/KECutCommand.h"
#include "Player/Commands/KECopyCommand.h"
#include "Player/Commands/KEPasteCommand.h"
#include "Player/Commands/KENewCommand.h"

#include <OpenSG/UserInterface/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGMenuButton.h>


#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGMatrixUtility.h>

#include "Player/KEApplicationPlayer.h"

OSG_BEGIN_NAMESPACE

/*! \brief HierarchyPanel class. See \ref 
           PageKabalaEngineHierarchyPanel for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING HierarchyPanel : public HierarchyPanelBase
{
  private:

	typedef HierarchyPanelBase Inherited;

	enum tabs{LUA=1,SCENEGRAPH};

	std::set<UInt32>			_TabsAdded;
	std::set<UInt32>::iterator	_TabsAddedItr;
	SceneGraphTreeModelPtr		_TheSceneGraphTreeModel;
	LuaGraphTreeModelPtr		_TheLuaGraphTreeModel;
	TreePtr						_TheSceneGraphTree;
	TreePtr						_TheLuaGraphTree;
	NodePtr						_SelectedNode;

	ScrollPanelPtr				_TheSceneGraphTreeScrollPanel;
	ScrollPanelPtr				_TheLuaGraphTreeScrollPanel;
	NodePtr						_HighlightNode;

	CardLayoutPtr				_CardLayout;
	BorderLayoutConstraintsPtr	_LayoutConstraints;


    /*==========================  PUBLIC  =================================*/
  public:

	//inline functions
	
	SceneGraphTreeModelPtr getSceneGraphTreeModel(void);
	TreePtr getSceneGraphTree(void);
	ApplicationPlayerPtr getApplicationPlayer(void);

	void createSceneGraphTree(void);
	void createLuaGraphTree(void);
	void createPanel(void);
	void addTab(UInt32 tabno);
	void removeTab(UInt32 tabno);
	void createDefaultHierarchyPanel();
	void setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer);

    void setView(UInt32 Index);

	class LuaGraphTreeSelectionListener : public TreeSelectionListener
	{
	public:

		LuaGraphTreeSelectionListener(HierarchyPanelPtr TheHierarchyPanel);

		void selectionAdded(const TreeSelectionEventPtr e);
		void selectionRemoved(const TreeSelectionEventPtr e){};
		void setParams(TreePtr,ApplicationPlayerPtr);

	protected:
		HierarchyPanelPtr _HierarchyPanel;
		TreePtr _TheTree;
		ApplicationPlayerPtr _ApplicationPlayer;
		Path _SelectedPath;
	};

	friend class LuaGraphTreeSelectionListener;
	LuaGraphTreeSelectionListener _LuaGraphTreeSelectionListener;

	class SceneGraphTreeSelectionListener : public TreeSelectionListener
	{
	public:
		SceneGraphTreeSelectionListener(HierarchyPanelPtr TheHierarchyPanel);

		void selectionAdded(const TreeSelectionEventPtr e);
		void selectionRemoved(const TreeSelectionEventPtr e);
		void selectedNodeChanged(void);
		void setParams(TreePtr,ApplicationPlayerPtr);

		friend class ShowHideCommand;

		NodePtr _SelectedNode;
	protected:
		HierarchyPanelPtr _HierarchyPanel;
		TreePtr _TheTree;
		ApplicationPlayerPtr _ApplicationPlayer;
	};

	friend class SceneGraphTreeSelectionListener;
	SceneGraphTreeSelectionListener _SceneGraphTreeSelectionListener;

	

	class PlayerMouseListener2 : public MouseAdapter
	{
	public:
		PlayerMouseListener2(HierarchyPanelPtr TheHierarchyPanel);

		virtual void mouseClicked(const MouseEventPtr e);
	protected :
		HierarchyPanelPtr _HierarchyPanel;
	};
	
    friend class PlayerMouseListener2;
	PlayerMouseListener2 _PlayerMouseListener2;


	class MenuButtonActionListener : public ActionListener
	{
	public:
		MenuButtonActionListener(HierarchyPanelPtr TheHierearchyPanel);

		void actionPerformed(const ActionEventPtr e);
	protected:
		void createNewNode(const ActionEventPtr e);
		HierarchyPanelPtr _HierarchyPanel;
	};

	friend class MenuButtonActionListener;
	MenuButtonActionListener _TheMenuButtonActionListener;
	
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

  	ApplicationPlayerPtr _ApplicationPlayer;
	DerivedFieldContainerComboBoxModelPtr _NewNodeMenuModel;
	MenuButtonPtr _CreateNewNodeMenuButton;
	PanelPtr _SceneGraphPanel;
	BorderLayoutConstraintsPtr _CreateNewButtonConstraints;

	PopupMenuPtr _HierarchyPanelPopupMenu;
	
	MenuItemPtr _ShowHideItem ;
	MenuItemPtr _CutItem ;
	MenuItemPtr _CopyItem ;
	MenuItemPtr _PasteItem ;
	MenuItemPtr _DeleteItem ;
	MenuItemPtr _FocusCamera ;

	void createPopUpMenu(void);
	void updatePopupMenu(void);
	void changeShowHideMenuItem(void);
	void actionPerformed(const ActionEventPtr e);

	class BasicListener : public ActionListener
	{
	public:
		BasicListener(HierarchyPanelPtr TheHierarchyPanel);
		~BasicListener();

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		HierarchyPanelPtr _HierarchyPanel;
	
	};
	friend class BasicListener;
	BasicListener _BasicListener;

    void changeDebugCameraPosition(void);
    void showAll(CameraPtr TheCameraOrig,
                 NodePtr Scene,
                 ViewportPtr LocalViewport);
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

    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class HierarchyPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const HierarchyPanel &source);
};

typedef HierarchyPanel *HierarchyPanelP;

OSG_END_NAMESPACE

#include "KEHierarchyPanelBase.inl"
#include "KEHierarchyPanel.inl"

#endif /* _KEHIERARCHYPANEL_H_ */
