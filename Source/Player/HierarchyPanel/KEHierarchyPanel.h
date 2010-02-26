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
#include <OpenSG/UserInterface/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/UserInterface/OSGTreeSelectionListener.h>
#include <OpenSG/Toolbox/OSGGeometryUtils.h>

#include <OpenSG/UserInterface/OSGPanel.h>

#include <OpenSG/UserInterface/OSGCardLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>

#include <OpenSG/OSGSimpleMaterial.h>

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
	SceneGraphTreeModelPtr TempTreeModel;
	TreePtr TheTree;
	NodePtr SelectedNode;

	ScrollPanelPtr TreeScrollPanel;
	NodePtr highlightNode;
	CardLayoutPtr TopLeftCardLayout;
	BorderLayoutConstraintsPtr	PanelTopLeftConstraints1;
	ButtonPtr ExampleButton2;

	
	

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

		void selectedNodeChanged();
		void setParams(TreePtr,ApplicationPlayerPtr);
		void updateHighlight(void);
		void highlightChanged(void);
		NodePtr getHighlight(void);
		void setHighlight(NodePtr selectednode);


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
