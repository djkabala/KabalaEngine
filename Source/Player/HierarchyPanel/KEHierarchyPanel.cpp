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
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include "Application/KEMainApplication.h"





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

}

void HierarchyPanel::createLuaGraphTree()
{
	ExampleButton2 = osg::Button::create();

	beginEditCP(ExampleButton2, Button::TextFieldMask);
        ExampleButton2->setText("Lua Graph");
    endEditCP(ExampleButton2, Button::TextFieldMask);

}

void HierarchyPanel::createPanel()
{
	PanelTopLeftConstraints1 = osg::BorderLayoutConstraints::create();
	
	beginEditCP(PanelTopLeftConstraints1, BorderLayoutConstraints::RegionFieldMask);
        PanelTopLeftConstraints1->setRegion(BorderLayoutConstraints::BORDER_CENTER);
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
			if (ExampleButton2 == NullFC)
			{
				std::cout<<"the luafile tree hasnt been created yet.. so creating tree";
				createLuaGraphTree();
			}
			beginEditCP(HierarchyPanelPtr(this),  Panel::ChildrenFieldMask);
				this->getChildren().push_back(ExampleButton2);
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
				this->getChildren().erase(this->getChildren().find(ComponentPtr::dcast(ExampleButton2)));
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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HierarchyPanel::HierarchyPanel() :
    Inherited(),
	_TheTreeSelectionListener(HierarchyPanelPtr(this))
{
	_ApplicationPlayer = NullFC;
	
}

HierarchyPanel::HierarchyPanel(const HierarchyPanel &source) :
    Inherited(source),
	_TheTreeSelectionListener(HierarchyPanelPtr(this))
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

