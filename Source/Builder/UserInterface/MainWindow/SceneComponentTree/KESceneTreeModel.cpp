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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESceneTreeModel.h"
#include "Project/Scene/KEScene.h"
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGLight.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
boost::any SceneTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    if(parent.type() == typeid(Scene* const))
    {
        switch(index)
        {
        case BasicComponent:              //Basic
            return boost::any(UInt32(BasicComponent));
            break;
        case ForegroundsComponent:              //Foregrounds
            return boost::any(UInt32(ForegroundsComponent));
            break;
        case BackgroundComponent:              //Background
            return boost::any(UInt32(BackgroundComponent));
            break;
        case CameraComponent:              //Camera
            return boost::any(UInt32(CameraComponent));
            break;
        case SceneObjectsComponent:              //Models
            return boost::any(UInt32(SceneObjectsComponent));
            break;
        case LightsComponent:              //Models
            return boost::any(UInt32(LightsComponent));
            break;
        case DynamicsComponent:              //Dynamics
            return boost::any(UInt32(DynamicsComponent));
            break;
        }
    }
    else if(parent.type() == typeid(UInt32))
    {
        UInt32 Value(boost::any_cast<UInt32>(parent));
        switch(Value)
        {
        case BasicComponent:              //Basic
        case BackgroundComponent:              //Background
        case CameraComponent:              //Camera
            return boost::any();
            break;
        case ForegroundsComponent:              //Foregrounds
            if(index < getInternalRoot()->getPrimaryViewport()->getMFForegrounds()->size())
            {
                return boost::any(getInternalRoot()->getPrimaryViewport()->getForegrounds(index));
            }
            break;
        case SceneObjectsComponent:              //Models
            if(index < getInternalRoot()->getMFSceneObjects()->size())
            {
                return boost::any(getInternalRoot()->getSceneObjects(index));
            }
            break;
        case LightsComponent:              //Lights
            {
                NodeRecPtr LightNode(getInternalRoot()->getPrimaryViewport()->getRoot());

                for(UInt32 i(0) ; i<=index ; ++i)
                {
                    if(LightNode->getNChildren() > 0 &&
                        LightNode->getChild(0)->getCore()->getType().isDerivedFrom(Light::getClassType()))
                    {
                        LightNode = LightNode->getChild(0);
                    }
                }

                if(LightNode != NULL)
                {
                    return boost::any(dynamic_cast<Light*>(LightNode->getCore()));
                }
                else
                {
                    return boost::any();
                }
            }
            break;
        case DynamicsComponent:              //Dynamics
            switch(index+DynamicsComponentsFirst)
            {
            case ScriptsComponent:              //Scripts
                return boost::any(UInt32(ScriptsComponent));
                break;
            case BehavioursComponent:              //Behaviours
                return boost::any(UInt32(BehavioursComponent));
                break;
            case AnimationsComponent:              //Animations
                return boost::any(UInt32(AnimationsComponent));
                break;
            }
            break;
        }
    }
    return boost::any();
}

UInt32 SceneTreeModel::getChildCount(const boost::any& parent) const
{
    if(parent.type() == typeid(Scene* const))
    {
        return SceneComponentsLast;
    }
    else if(parent.type() == typeid(UInt32))
    {
        UInt32 Value(boost::any_cast<UInt32>(parent));
        switch(Value)
        {
        case BasicComponent:              //Basic
        case BackgroundComponent:              //Background
        case CameraComponent:              //Camera
            return 0;
            break;
        case ForegroundsComponent:              //Foregrounds
            return getInternalRoot()->getPrimaryViewport()->getMFForegrounds()->size();
            break;
        case SceneObjectsComponent:              //Models
            return getInternalRoot()->getMFSceneObjects()->size();
            break;
        case LightsComponent:              //Lights
            {
                NodeRecPtr LightNode(getInternalRoot()->getPrimaryViewport()->getRoot());
                UInt32 NumLights(0);

                while(LightNode->getNChildren() > 0 &&
                      LightNode->getChild(0)->getCore()->getType().isDerivedFrom(Light::getClassType()))
                {
                    LightNode = LightNode->getChild(0);

                    ++NumLights;
                }
                return NumLights;
            }
            break;
        case DynamicsComponent:              //Dynamics
            return DynamicsComponentsLast - DynamicsComponentsFirst;
            break;
        case ScriptsComponent:              //Scripts
            return 0;
            break;
        case BehavioursComponent:              //Behaviours
            return 0;
            break;
        case AnimationsComponent:              //Animations
            return 0;
            break;
        }
    }
    else
    {
        return 0;
    }
}

UInt32 SceneTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
    if(parent.type() == typeid(Scene* const))
    {
        UInt32 Value(boost::any_cast<UInt32>(child));
        switch(Value)
        {
        case BasicComponent:              //Basic
            return BasicComponent;
            break;
        case ForegroundsComponent:              //Foregrounds
            return ForegroundsComponent;
            break;
        case BackgroundComponent:              //Background
            return BackgroundComponent;
            break;
        case CameraComponent:              //Camera
            return CameraComponent;
            break;
        case SceneObjectsComponent:              //Models
            return SceneObjectsComponent;
            break;
        case DynamicsComponent:              //Dynamics
            return DynamicsComponent;
            break;
        }
    }
    else if(parent.type() == typeid(UInt32))
    {
        UInt32 Value(boost::any_cast<UInt32>(parent));
        switch(Value)
        {
        case BasicComponent:              //Basic
        case BackgroundComponent:              //Background
        case CameraComponent:              //Camera
            return 0;
            break;
        case ForegroundsComponent:              //Foregrounds
            for(UInt32 i(0) ; i<getInternalRoot()->getPrimaryViewport()->getMFForegrounds()->size() ; ++i)
            {
                if(getInternalRoot()->getPrimaryViewport()->getForegrounds(i) == boost::any_cast<Foreground* const>(child))
                {
                    return i;
                }
            }
            return 0;
            break;
        case SceneObjectsComponent:              //Models
            for(UInt32 i(0) ; i<getInternalRoot()->getMFSceneObjects()->size() ; ++i)
            {
                if(getInternalRoot()->getSceneObjects(i) == boost::any_cast<SceneObject* const>(child))
                {
                    return i;
                }
            }
            break;
        case LightsComponent:              //Lights
            {
                UInt32 NumLights(getChildCount(parent));
                UInt32 FoundLights(0);

                NodeRecPtr LightNode(getInternalRoot()->getPrimaryViewport()->getRoot());
                while(FoundLights < NumLights &&
                      LightNode->getNChildren() > 0 &&
                      LightNode->getChild(0)->getCore()->getType().isDerivedFrom(Light::getClassType()))
                {
                    LightNode = LightNode->getChild(0);

                    if(LightNode ==boost::any_cast<Light* const>(child)->getParents().front() )
                    {
                        return FoundLights;
                    }

                    ++FoundLights;
                }
            }
            break;
        case DynamicsComponent:              //Dynamics
            UInt32 Value(boost::any_cast<UInt32>(child));
            switch(Value)
            {
                case ScriptsComponent:              //Scripts
                    return ScriptsComponent - DynamicsComponentsFirst;
                    break;
                case BehavioursComponent:              //Behaviours
                    return BehavioursComponent - DynamicsComponentsFirst;
                    break;
                case AnimationsComponent:              //Animations
                    return AnimationsComponent - DynamicsComponentsFirst;
                    break;
            }
        }
    }
    else
    {
        return 0;
    }
}

boost::any SceneTreeModel::getRoot(void) const
{
    return boost::any(getRootScene());
}

bool SceneTreeModel::isLeaf(const boost::any& node) const
{
    return getChildCount(node) == 0;
}

void SceneTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
}

TreePath SceneTreeModel::getSceneObjectPath(SceneObject* const ObjToSelect) const
{
    TreePath Path(getRootPath());
    Path = Path.getChildPath(boost::any(UInt32(SceneObjectsComponent)));
    Path = Path.getChildPath(boost::any(ObjToSelect));
    return Path;
}

TreePath SceneTreeModel::getCameraPath(void) const
{
    TreePath Path(getRootPath());
    Path = Path.getChildPath(boost::any(UInt32(CameraComponent)));
    return Path;
}

TreePath SceneTreeModel::getLightPath(Light* const LightToSelect) const
{
    TreePath Path(getRootPath());
    Path = Path.getChildPath(boost::any(UInt32(LightsComponent)));
    Path = Path.getChildPath(boost::any(LightToSelect));
    return Path;
}


void SceneTreeModel::setRoot(Scene* const root)
{
    dettachChangedFunctors();
    _ViewportFieldsChangedContainer = root->getPrimaryViewport();
    _SceneFieldsChangedContainer = root;
    attachChangedFunctors();

    setInternalRoot(root);
    std::vector<UInt32> ChildIndices;
    std::vector<boost::any> Children;
    produceTreeStructureChanged(getRootPath(), ChildIndices, Children);
}

Scene* SceneTreeModel::getRootScene(void) const
{
    return getInternalRoot();
}

void SceneTreeModel::foregroundAdded(Foreground* const TheForeground)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(ForegroundsComponent)));

    produceTreeNodeInserted(Parent, boost::any(TheForeground));
}

void SceneTreeModel::foregroundRemoved(Foreground* const TheForeground)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(ForegroundsComponent)));

    produceTreeNodeRemoved(Parent, boost::any(TheForeground));
}

void SceneTreeModel::foregroundWillBeRemoved(Foreground* const TheForeground)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(ForegroundsComponent)));

    produceTreeNodeWillBeRemoved(Parent, boost::any(TheForeground));
}

void SceneTreeModel::lightAdded(Light* const TheLightNode)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(LightsComponent)));

    produceTreeNodeInserted(Parent, boost::any(TheLightNode));
}

void SceneTreeModel::lightWillBeRemoved(Light* const TheLightNode)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(LightsComponent)));

    produceTreeNodeWillBeRemoved(Parent, boost::any(TheLightNode));
}

void SceneTreeModel::lightRemoved(Light* const TheLightNode)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(LightsComponent)));

    produceTreeNodeRemoved(Parent, boost::any(TheLightNode));
}


void SceneTreeModel::sceneObjectAdded(SceneObject* const TheSceneObject)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(SceneObjectsComponent)));

    produceTreeNodeInserted(Parent, boost::any(TheSceneObject));
}

void SceneTreeModel::sceneObjectWillBeRemoved(SceneObject* const TheSceneObject)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(SceneObjectsComponent)));

    produceTreeNodeWillBeRemoved(Parent, boost::any(TheSceneObject));
}

void SceneTreeModel::sceneObjectRemoved(SceneObject* const TheSceneObject)
{
    TreePath Parent(getRootPath(), boost::any(UInt32(SceneObjectsComponent)));

    produceTreeNodeRemoved(Parent, boost::any(TheSceneObject));
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void SceneTreeModel::setAsVisible(const TreePath& path)
{
    boost::any value = path.getLastPathComponent();

    if(value.type() == typeid(Scene* const))
    {
        attachChangeHandler(boost::any_cast<Scene* const>(value), 
                            path.getParentPath(),
                             path);
    }
    else if(value.type() == typeid(Light* const))
    {
        attachChangeHandler(boost::any_cast<Light* const>(value), 
                             path.getParentPath(),
                             path);
    }
    else if(value.type() == typeid(Foreground* const))
    {
        attachChangeHandler(boost::any_cast<Foreground* const>(value), 
                             path.getParentPath(),
                             path);
    }
    else if(value.type() == typeid(SceneObject* const))
    {
        attachChangeHandler(boost::any_cast<SceneObject* const>(value), 
                             path.getParentPath(),
                             path);
    }
}

void SceneTreeModel::setAsNotVisible(const TreePath& path)
{
    boost::any value = path.getLastPathComponent();

    if(value.type() == typeid(Scene* const))
    {
        dettachChangeHandler(boost::any_cast<Scene* const>(value), 
                             path.getParentPath(),
                             path);
    }
    else if(value.type() == typeid(Light* const))
    {
        dettachChangeHandler(boost::any_cast<Light* const>(value), 
                             path.getParentPath(),
                             path);
    }
    else if(value.type() == typeid(Foreground* const))
    {
        dettachChangeHandler(boost::any_cast<Foreground* const>(value), 
                             path.getParentPath(),
                             path);
    }
    else if(value.type() == typeid(SceneObject* const))
    {
        dettachChangeHandler(boost::any_cast<SceneObject* const>(value), 
                             path.getParentPath(),
                             path);
    }
}

void SceneTreeModel::attachChangeHandler(FieldContainer * const TheContainer,
                                               const TreePath& Parent, 
                                               const TreePath& ChildPath)
{
    //if(!TheContainer->hasChangedFunctor(boost::bind(&SceneTreeModel::handleFieldChanged, this,_1,_2,Parent, ChildPath)))
    //{
    //    TheContainer->addChangedFunctor(boost::bind(&SceneTreeModel::handleFieldChanged, this,_1,_2,Parent, ChildPath),"");
    //}
}

void SceneTreeModel::dettachChangeHandler(FieldContainer * const TheContainer,
                                               const TreePath& Parent, 
                                               const TreePath& ChildPath)
{
    //TheContainer->subChangedFunctor(boost::bind(&SceneTreeModel::handleFieldChanged, this,_1,_2,Parent, ChildPath));
}

void SceneTreeModel::attachChangedFunctors(void)
{
    if(_ViewportFieldsChangedContainer != NULL)
    {
        _ViewportFieldsChangedContainer->addChangedFunctor(boost::bind(&SceneTreeModel::handleViewportFieldsChanged, this, _1, _2),"");
    }
    if(_SceneFieldsChangedContainer != NULL)
    {
        _SceneFieldsChangedContainer->addChangedFunctor(boost::bind(&SceneTreeModel::handleSceneFieldsChanged, this, _1, _2),"");
    }
}

void SceneTreeModel::dettachChangedFunctors(void)
{
    if(_ViewportFieldsChangedContainer != NULL)
    {
        _ViewportFieldsChangedContainer->subChangedFunctor(boost::bind(&SceneTreeModel::handleViewportFieldsChanged, this, _1, _2));
    }
    if(_SceneFieldsChangedContainer != NULL)
    {
        _SceneFieldsChangedContainer->subChangedFunctor(boost::bind(&SceneTreeModel::handleSceneFieldsChanged, this, _1, _2));
    }
}

void SceneTreeModel::handleViewportFieldsChanged(FieldContainer *fc, ConstFieldMaskArg whichField)
{
    if(whichField & Viewport::ForegroundsFieldMask)
    {
        //Send the Foregrounds nodes changed
        //produceTreeNodesChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
    }
    else if(whichField & Viewport::BackgroundFieldMask)
    {
        //Send the Background node changed
        TreePath Root(getRootPath());

        std::vector<UInt32> ChildIndices;
        ChildIndices.push_back(getIndexOfChild(getRoot(), boost::any(BackgroundComponent)));
        
        std::vector<boost::any> Children;
        Children.push_back(getChild(getRoot(), ChildIndices.front()));
        
        produceTreeNodesChanged(Root, ChildIndices, Children);
    }
    else if(whichField & Viewport::CameraFieldMask)
    {
        //Send the Camera node changed
    }
    else if(whichField & Viewport::RootFieldMask)
    {
    }
}

void SceneTreeModel::handleSceneFieldsChanged(FieldContainer *fc, ConstFieldMaskArg whichField)
{
    if(whichField & Scene::SceneObjectsFieldMask)
    {
    }
}

void SceneTreeModel::handleFieldChanged(FieldContainer *fc, 
                                        ConstFieldMaskArg whichField,
                                        const TreePath& Parent, 
                                        const TreePath& ChildPath)
{
    if(whichField)
    {
        produceTreeNodeChanged(Parent, ChildPath);
    }
}

/*----------------------- constructors & destructors ----------------------*/

SceneTreeModel::SceneTreeModel(void) :
    Inherited(),
        _ViewportFieldsChangedContainer(NULL),
        _SceneFieldsChangedContainer(NULL)
{
}

SceneTreeModel::SceneTreeModel(const SceneTreeModel &source) :
    Inherited(source),
        _ViewportFieldsChangedContainer(NULL),
        _SceneFieldsChangedContainer(NULL)
{
}

SceneTreeModel::~SceneTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
