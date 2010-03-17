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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEHierarchyPanel.h"


#include "Player/KEApplicationPlayer.h"
#include "Player/HelperPanel/KEHelperPanel.h"
#include "Player/ContentPanel/KEContentPanel.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include "Application/KEMainApplication.h"

#include <boost/filesystem/operations.hpp>
#include <OpenSG/UserInterface/OSGTreePath.h>
#include "boost/filesystem.hpp"


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::HierarchyPanel
The HierarchyPanel. Stores the tree structure for the lua files and the scenegraph.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HierarchyPanel::initMethod (void)
{
}

void HierarchyPanel::createSceneGraphTree(void)
{
	TheTree = Tree::create();
	TheTreeModel = SceneGraphTreeModel::create();

	beginEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setModel(TheTreeModel);
    endEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);

	
    TheTree->getSelectionModel()->addTreeSelectionListener(&_TheTreeSelectionListener);
	
	
    BorderLayoutConstraintsPtr SceneTreeConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);
        SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);

    TreeScrollPanel = ScrollPanel::create();
    beginEditCP(TreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
        TreeScrollPanel->setPreferredSize(Vec2s(350,300));
        TreeScrollPanel->setConstraints(SceneTreeConstraints);
    endEditCP(TreeScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
    TreeScrollPanel->setViewComponent(TheTree);

	
	_TheTreeSelectionListener.setParams(TheTree,_ApplicationPlayer);
	_TheTreeSelectionListener.updateHighlight();

//	TheTree->addMouseListener(&_PlayerMouseListener2);

}

void HierarchyPanel::createLuaGraphTree()
{

	TheTree2 = Tree::create();
	TheTreeModel2 = LuaGraphTreeModel::create();
	
	TheTreeModel2->setRoot(MainApplication::the()->getProject()->getLuaModulePath());

	beginEditCP(TheTree2, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
        TheTree2->setPreferredSize(Vec2f(100, 500));
        TheTree2->setModel(TheTreeModel2);
    endEditCP(TheTree2, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);

	TheTree2->getSelectionModel()->addTreeSelectionListener(&_TheTreeSelectionListener2);

	BorderLayoutConstraintsPtr SceneTreeConstraints2 = osg::BorderLayoutConstraints::create();
    beginEditCP(SceneTreeConstraints2, BorderLayoutConstraints::RegionFieldMask);
        SceneTreeConstraints2->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(SceneTreeConstraints2, BorderLayoutConstraints::RegionFieldMask);

    TreeScrollPanel2 = ScrollPanel::create();
    beginEditCP(TreeScrollPanel2, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
        TreeScrollPanel2->setPreferredSize(Vec2s(350,300));
        TreeScrollPanel2->setConstraints(SceneTreeConstraints2);
    endEditCP(TreeScrollPanel2, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
    TreeScrollPanel2->setViewComponent(TheTree2);

	
	_TheTreeSelectionListener2.setParams(TheTree2,_ApplicationPlayer);

	//_PlayerMouseListener2.setParams(_ApplicationPlayer);

	TheTree2->addMouseListener(&_PlayerMouseListener2);

	

}

void HierarchyPanel::createPanel()
{
	PanelTopLeftConstraints1 = osg::BorderLayoutConstraints::create();
	
	beginEditCP(PanelTopLeftConstraints1, BorderLayoutConstraints::RegionFieldMask);
        PanelTopLeftConstraints1->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(PanelTopLeftConstraints1, BorderLayoutConstraints::RegionFieldMask);


	TopLeftCardLayout = osg::CardLayout::create(); 

   
	beginEditCP(HierarchyPanelPtr(this), Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
        this->setLayout(TopLeftCardLayout);
        this->setConstraints(PanelTopLeftConstraints1);
    endEditCP(HierarchyPanelPtr(this), Panel::LayoutFieldMask | Panel::ChildrenFieldMask);

}


void HierarchyPanel::addTab(UInt32 tabno) // tabno defined by the enum variable
{
	TabsAddedItr = TabsAdded.find(tabno);
	if(TabsAddedItr == TabsAdded.end())
	{
		if(tabno == SCENEGRAPH)
		{
			if (TreeScrollPanel == NullFC)
			{
				std::cout<<"the scenegraph tree hasnt been created yet.. so creating tree";
				createSceneGraphTree();
			}
			beginEditCP(HierarchyPanelPtr(this),Panel::ChildrenFieldMask);
				this->getChildren().push_back(TreeScrollPanel);
			endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

			TabsAdded.insert(SCENEGRAPH);

		}
		else if(tabno == LUA)
		{
			if (TreeScrollPanel2 == NullFC)
			{
				std::cout<<"the luafile tree hasnt been created yet.. so creating tree";
				createLuaGraphTree();
			}
			beginEditCP(HierarchyPanelPtr(this),  Panel::ChildrenFieldMask);
				this->getChildren().push_back(TreeScrollPanel2);
			endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

			TabsAdded.insert(LUA);
		}
		else
		{
			std::cout<<"undefined number in addtab of HierarchyPanel";
		}
	}
	else
	{
		std::cout<<"tab already exists\n";
	}
}

void HierarchyPanel::removeTab(UInt32 tabno)
{

	beginEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);
	TabsAddedItr = TabsAdded.find(tabno);

	if(TabsAddedItr!= TabsAdded.end())
	{
		switch(*TabsAddedItr)
		{

			case SCENEGRAPH:	
				this->getChildren().erase(this->getChildren().find(ComponentPtr::dcast(TreeScrollPanel)));
				break;
			case LUA:
				this->getChildren().erase(this->getChildren().find(ComponentPtr::dcast(TreeScrollPanel2)));
				break;
		}

	}
	else
	{
		std::cout<<"no such tab exists\n";
	}
	endEditCP(HierarchyPanelPtr(this), Panel::ChildrenFieldMask);

}

void HierarchyPanel::createDefaultHierarchyPanel() // creates the panel with the LUA and SCENEGRAPH trees
{
	createPanel();
	addTab(SCENEGRAPH);
	addTab(LUA);
}


void HierarchyPanel::TheTreeSelectionListener::changeShowHideMenuItem(void)
{

	if(_ApplicationPlayer!=NullFC && _SelectedNode!=NullFC && _ApplicationPlayer->ShowHideItem!=NullFC)
	{
		UInt32 maskval = _SelectedNode->getTravMask();
		//std::cout<<"maskval:"<<maskval<<std::endl;	
		if(!maskval)
		{
			if(_ApplicationPlayer->ShowHideItem->getText()== "Hide")
			{
				//std::cout<<"changing from hide to show"<<std::endl;
				beginEditCP(_ApplicationPlayer->ShowHideItem,MenuItem::TextFieldMask);
				_ApplicationPlayer->ShowHideItem->setText("Show");
				endEditCP(_ApplicationPlayer->ShowHideItem,MenuItem::TextFieldMask);
			}
			else
			{
				//std::cout<<"its already 'show'";
			}
		}
		else 
		{
			if(_ApplicationPlayer->ShowHideItem->getText()== "Show")
			{
				//std::cout<<"changing from show to hide"<<std::endl;
				beginEditCP(_ApplicationPlayer->ShowHideItem,MenuItem::TextFieldMask);
				_ApplicationPlayer->ShowHideItem->setText("Hide");
				endEditCP(_ApplicationPlayer->ShowHideItem,MenuItem::TextFieldMask);
			}
			else
			{
				//std::cout<<"its already 'hide'";
			}
		}
	}
}

HierarchyPanel::TheTreeSelectionListener2::TheTreeSelectionListener2(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
	_ApplicationPlayer = NullFC;
	_TheTree=NullFC;
}

HierarchyPanel::TheTreeSelectionListener::TheTreeSelectionListener(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel = TheHierarchyPanel;
	_ApplicationPlayer = NullFC;
	_TheTree=NullFC;
	_highlight = NullFC;
	_highlightPoints = NullFC;
}

void HierarchyPanel::TheTreeSelectionListener::setParams(TreePtr TheTree,ApplicationPlayerPtr TheApplicationPlayer)//,NodePtr  SelectedNode)
{
	_TheTree=TheTree;
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::TheTreeSelectionListener2::setParams(TreePtr TheTree,ApplicationPlayerPtr TheApplicationPlayer)//,NodePtr  SelectedNode)
{
	_TheTree=TheTree;
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::TheTreeSelectionListener::setHighlight(NodePtr selectednode)
{
	
	_highlight = selectednode;
	highlightChanged();
}
NodePtr HierarchyPanel::TheTreeSelectionListener::getHighlight()
{
	return _highlight;
}
void HierarchyPanel::TheTreeSelectionListener::highlightChanged(void)
{
 
	// change the ShowHideMenuItem's text 
	
	SimpleMaterialPtr _highlightMaterial;
	
	
// SWARNING << "SimpleSceneManager::updateHightlight() called\n";

	// init as needed
	if(_highlightMaterial == NullFC)
	{
		_highlightMaterial = SimpleMaterial::create();
		
		beginEditCP(_highlightMaterial);
		_highlightMaterial->setDiffuse (Color3f(0,1,0));
		_highlightMaterial->setLit     (false);
		endEditCP(_highlightMaterial);
	}
	if(_ApplicationPlayer->highlightNode == NullFC)
	{
		GeoPTypesPtr type = GeoPTypesUI8::create();
		beginEditCP(type);
		type->push_back(GL_LINE_STRIP);
		type->push_back(GL_LINES);
		endEditCP(type);

		GeoPLengthsPtr lens = GeoPLengthsUI32::create();
		beginEditCP(lens);
		lens->push_back(10);
		lens->push_back(6);
		endEditCP(lens);

		GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
		beginEditCP(index);
		index->getFieldPtr()->push_back(0);
		index->getFieldPtr()->push_back(1);
		index->getFieldPtr()->push_back(3);
		index->getFieldPtr()->push_back(2);
		index->getFieldPtr()->push_back(0);
		index->getFieldPtr()->push_back(4);
		index->getFieldPtr()->push_back(5);
		index->getFieldPtr()->push_back(7);
		index->getFieldPtr()->push_back(6);
		index->getFieldPtr()->push_back(4);

		index->getFieldPtr()->push_back(1);
		index->getFieldPtr()->push_back(5);
		index->getFieldPtr()->push_back(2);
		index->getFieldPtr()->push_back(6);
		index->getFieldPtr()->push_back(3);
		index->getFieldPtr()->push_back(7);
		endEditCP(index);

		_highlightPoints = GeoPositions3f::create();
		beginEditCP(_highlightPoints);
		_highlightPoints->push_back(Pnt3f(-1, -1, -1));
		_highlightPoints->push_back(Pnt3f( 1, -1, -1));
		_highlightPoints->push_back(Pnt3f(-1,  1, -1));
		_highlightPoints->push_back(Pnt3f( 1,  1, -1));
		_highlightPoints->push_back(Pnt3f(-1, -1,  1));
		_highlightPoints->push_back(Pnt3f( 1, -1,  1));
		_highlightPoints->push_back(Pnt3f(-1,  1,  1));
		_highlightPoints->push_back(Pnt3f( 1,  1,  1));
		endEditCP(_highlightPoints);
		addRefCP(_highlightPoints);

		GeometryPtr geo=Geometry::create();
		beginEditCP(geo);
		geo->setTypes     (type);
		geo->setLengths   (lens);
		geo->setIndices   (index);
		geo->setPositions (_highlightPoints);
		geo->setMaterial  (_highlightMaterial);  /// billa
		endEditCP(geo);
		addRefCP(geo);

		_ApplicationPlayer->highlightNode = Node::create();
		setName(_ApplicationPlayer->highlightNode,"DEBUG_MODE_BOUNDING_BOX");
		
		beginEditCP(_ApplicationPlayer->highlightNode);
		_ApplicationPlayer->highlightNode->setCore(geo);
		endEditCP(_ApplicationPlayer->highlightNode);
		addRefCP(_ApplicationPlayer->highlightNode);
	}

	
	// attach the hightlight node to the root if the highlight is active
	if(getHighlight() != NullFC)
	{
		if(_ApplicationPlayer->highlightNode->getParent() == NullFC)
		{
		beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->addChild(_ApplicationPlayer->highlightNode);

		endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		}
		
	}
	else
	{
		if(_ApplicationPlayer->highlightNode->getParent() != NullFC)
		{
		beginEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot()->subChild(_ApplicationPlayer->highlightNode);
		endEditCP(MainApplication::the()->getProject()->getActiveScene()->getViewports(0)->getRoot());
		}
	}
	// update the highlight geometry
	updateHighlight();
}


void HierarchyPanel::TheTreeSelectionListener::updateHighlight(void)
{
	if(_highlight==NullFC)
	return;

	// calc the world bbox of the highlight object
	#ifndef OSG_2_PREP
	DynamicVolume vol;
	#else
	BoxVolume      vol;
	#endif
	_highlight->getWorldVolume(vol);

	Pnt3f min,max;
	vol.getBounds(min, max);

	beginEditCP(_highlightPoints);
	_highlightPoints->setValue(Pnt3f(min[0], min[1], min[2]), 0);
	_highlightPoints->setValue(Pnt3f(max[0], min[1], min[2]), 1);
	_highlightPoints->setValue(Pnt3f(min[0], max[1], min[2]), 2);
	_highlightPoints->setValue(Pnt3f(max[0], max[1], min[2]), 3);
	_highlightPoints->setValue(Pnt3f(min[0], min[1], max[2]), 4);
	_highlightPoints->setValue(Pnt3f(max[0], min[1], max[2]), 5);
	_highlightPoints->setValue(Pnt3f(min[0], max[1], max[2]), 6);
	_highlightPoints->setValue(Pnt3f(max[0], max[1], max[2]), 7);
	endEditCP(_highlightPoints);


}

void HierarchyPanel::setApplicationPlayer(ApplicationPlayerPtr TheApplicationPlayer)
{
	_ApplicationPlayer = TheApplicationPlayer;
}

void HierarchyPanel::TheTreeSelectionListener::selectedNodeChanged(void)
{
	
	setHighlight(_SelectedNode);
	
    //Update Details Panel
    if(_SelectedNode == NullFC)
    {
		
		_ApplicationPlayer->_HelperPanel->setLabelValuesToNull();
    }
    else
    {
		_ApplicationPlayer->SelectedNode=_SelectedNode;
		_ApplicationPlayer->_HelperPanel->setLabelValues(_SelectedNode);
    }
}

HierarchyPanel::PlayerMouseListener2::PlayerMouseListener2(HierarchyPanelPtr TheHierarchyPanel)
{
	_HierarchyPanel=TheHierarchyPanel;
}


void HierarchyPanel::PlayerMouseListener2::mouseClicked(const MouseEventPtr e)
{
   if(e->getButton() == e->BUTTON3)
   {
	   std::cout<<"right clicked!!!"<<std::endl;
   }
   if(e->getClickCount() == 2)
   {
		Path path = boost::any_cast<Path>(_HierarchyPanel->TheTree2->getLastSelectedPathComponent());
		
		if(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path))
		{
			std::string filename(path.string());
			std::cout<<"\nfile to open:"<<filename<<std::endl;
			_HierarchyPanel->_ApplicationPlayer->_ContentPanel->addTabWithText(path);
			//_ApplicationPlayer->_ContentPanel->addTabWithText(path);
		}
   }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HierarchyPanel::HierarchyPanel() :
    Inherited(),
	_TheTreeSelectionListener(HierarchyPanelPtr(this)),
	_TheTreeSelectionListener2(HierarchyPanelPtr(this)),
	_PlayerMouseListener2(HierarchyPanelPtr(this))
{
	_ApplicationPlayer = NullFC;
	
}

HierarchyPanel::HierarchyPanel(const HierarchyPanel &source) :
    Inherited(source),
	_TheTreeSelectionListener(HierarchyPanelPtr(this)),
	_TheTreeSelectionListener2(HierarchyPanelPtr(this)),
	_PlayerMouseListener2(HierarchyPanelPtr(this))
{
}

HierarchyPanel::~HierarchyPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HierarchyPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void HierarchyPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump HierarchyPanel NI" << std::endl;
}


OSG_END_NAMESPACE

