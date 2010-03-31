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

#include <OpenSG/UserInterface/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGMenuButton.h>

OSG_BEGIN_NAMESPACE

/*! \brief HierarchyPanel class. See \ref 
           PageKabalaEngineHierarchyPanel for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING HierarchyPanel : public HierarchyPanelBase
{
  private:

	typedef HierarchyPanelBase Inherited;

	enum tabs{LUA=1,SCENEGRAPH};

	ApplicationPlayerPtr _ApplicationPlayer;
	
	std::set<UInt32> TabsAdded;
	std::set<UInt32>::iterator TabsAddedItr;
	SceneGraphTreeModelPtr TheTreeModel;
	LuaGraphTreeModelPtr TheTreeModel2;
	//SceneGraphTreeModelPtr TempTreeModel;
	TreePtr TheTree;
	TreePtr TheTree2;
	NodePtr SelectedNode;

	ScrollPanelPtr TreeScrollPanel;
	ScrollPanelPtr TreeScrollPanel2;
	NodePtr highlightNode;
	CardLayoutPtr TopLeftCardLayout;
	BorderLayoutConstraintsPtr	PanelTopLeftConstraints1;


	
	

    /*==========================  PUBLIC  =================================*/
  public:

	friend class ApplicationPlayer;

	void createSceneGraphTree(void);
	void createLuaGraphTree(void);
	void createPanel(void);
	void addTab(UInt32 tabno);
	void removeTab(UInt32 tabno);
	void createDefaultHierarchyPanel();
	void setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer);

	friend class DeleteCommand;
	friend class CutCommand;
	friend class CopyCommand;
	friend class PasteCommand;

	class TheTreeSelectionListener2 : public TreeSelectionListener
	{
	public:

		TheTreeSelectionListener2(HierarchyPanelPtr TheHierarchyPanel);
		//Called whenever elements are added to the selection
		virtual void selectionAdded(const TreeSelectionEventPtr e)
		{
			//Get the selected Node
			try
			{
				_SelectedPath = boost::any_cast<Path>(_TheTree->getLastSelectedPathComponent());
			}
			catch (boost::bad_any_cast &)
			{
	//			_SelectedPath = boost::any_cast<Path>(boost::any(std::string(".")));
			}
		}

		//Called whenever elements are removed to the selection
		virtual void selectionRemoved(const TreeSelectionEventPtr e)
		{
	//		_SelectedPath = boost::any_cast<Path>(boost::any(std::string(".")));
		}

		void setParams(TreePtr,ApplicationPlayerPtr);

	protected:
		HierarchyPanelPtr _HierarchyPanel;
		TreePtr _TheTree;
		ApplicationPlayerPtr _ApplicationPlayer;
		Path _SelectedPath;
	};

	friend class TheTreeSelectionListener2;
	TheTreeSelectionListener2 _TheTreeSelectionListener2;

	class TheTreeSelectionListener : public TreeSelectionListener
	{
	public:
		TheTreeSelectionListener(HierarchyPanelPtr TheHierarchyPanel);
		//Called whenever elements are added to the selection
		virtual void selectionAdded(const TreeSelectionEventPtr e)
		{
			//Get the selected Node
			try
			{
				_SelectedNode = boost::any_cast<NodePtr>(_TheTree->getLastSelectedPathComponent());
				std::cout<<std::endl<<"selection changed"<<std::endl;
				changeShowHideMenuItem();
			}
			catch (boost::bad_any_cast &)
			{
				_SelectedNode = NullFC;
			}
			selectedNodeChanged();
		}

		//Called whenever elements are removed to the selection
		virtual void selectionRemoved(const TreeSelectionEventPtr e)
		{
			_SelectedNode = NullFC;
			selectedNodeChanged();
		}
		void changeShowHideMenuItem(void);
		void selectedNodeChanged();
		void setParams(TreePtr,ApplicationPlayerPtr);
		void updateHighlight(void);
		void highlightChanged(void);
		NodePtr getHighlight(void);
		void setHighlight(NodePtr selectednode);

		friend class ShowHideCommand;
		

	protected:
		HierarchyPanelPtr _HierarchyPanel;
		TreePtr _TheTree;
		NodePtr _SelectedNode;
		NodePtr  _highlight;
		GeoPositions3fPtr _highlightPoints;
		ApplicationPlayerPtr _ApplicationPlayer;
	};

	friend class TheTreeSelectionListener;
	TheTreeSelectionListener _TheTreeSelectionListener;

	

	class PlayerMouseListener2 : public MouseAdapter
	{
	public:
		PlayerMouseListener2(HierarchyPanelPtr TheHierarchyPanel);

		virtual void mouseClicked(const MouseEventPtr e);

	//	void setParams(ApplicationPlayerPtr);
	protected :
		HierarchyPanelPtr _HierarchyPanel;
	//	ApplicationPlayerPtr _ApplicationPlayer;
	};
	
    friend class PlayerMouseListener2;
	PlayerMouseListener2 _PlayerMouseListener2;

	class MenuButtonActionListener : public ActionListener
	{
	public:
		MenuButtonActionListener(HierarchyPanelPtr TheHierearchyPanel);
		virtual void actionPerformed(const ActionEventPtr e)
		{
			std::cout<<e->getSource()<<std::endl;
			MenuButtonPtr TheMenuButton(MenuButtonPtr::dcast(e->getSource()));
			if(TheMenuButton != NullFC)
			{
				try
				{
					
					//NodeCorePtr SelectedNodeCore = NodeCorePtr::dcast(boost::any_cast<osg::FieldContainerType>(TheMenuButton->getSelectionValue()));
					//std::cout << "Selected: " << boost::any_cast<>(TheMenuButton->getSelectionValue());
					//std::string StrValue = boost::any_cast<std::string>(TheMenuButton->getSelectionValue());
					//std::cout << "Selected: " << SelectedNodeCore->getClassType().getCName() << std::endl;
				}
				catch(boost::bad_any_cast &)
				{
					std::cout << "badcast: " << std::endl;
				}
			}
			else
			{
				std::cout << "TheMenuButton is null " << std::endl;
			}
		}
	protected:
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

	DerivedFieldContainerComboBoxModelPtr NewNodeMenuModel;
	MenuButtonPtr CreateNewNodeMenuButton;
	PanelPtr SceneGraphPanel;
	BorderLayoutConstraintsPtr CreateNewButtonConstraints;


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
