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

#include "KEScene.h"
#include "KEUtils.h"
#include "Project/KEProject.h"
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include "Application/KEMainApplication.h"
#include <OpenSG/Lua/OSGLuaManager.h>
#include <OpenSG/Physics/OSGPhysicsWorld.h>
#include <OpenSG/Physics/OSGPhysicsHandler.h>
#include <OpenSG/Physics/OSGPhysicsUtils.h>
#include <OpenSG/Toolbox/OSGGenericEvent.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Scene
The Scene.     
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Scene::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Scene::enter(void)
{
    SLOG << "Entering Scene: "
         << (getName(ScenePtr(this)) ? getName(ScenePtr(this)) : "UNNAMED SCENE")
         << "." << std::endl;
    dump(1);

    if(getRoot() == NullFC)
    {
        createDefaults();
        initDefaults();
    }

    //Attach the listeners
    MainApplication::the()->getMainWindowEventProducer()->addUpdateListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->addMouseListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->addMouseMotionListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->addMouseWheelListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->addWindowListener(&_SceneUpdateListener);

    //Set up Initial Model Nodes
    beginEditCP(getRoot(), Node::ChildrenFieldMask);
        for(::osg::UInt32 i(0) ; i<getInitialModelNodes().size() ; ++i)
        {
            getRoot()->addChild(getInitialModelNodes()[i]);
        }
    endEditCP(getRoot(), Node::ChildrenFieldMask);

    //Root Node
    getInternalParentProject()->setActiveNode(getRoot());

    //Attach the User Interface Drawing Surfaces to the Window Event Producer
    for(::osg::UInt32 i(0) ; i<getUIDrawingSurfaces().size() ; ++i)
    {
        beginEditCP(getUIDrawingSurfaces(i), UIDrawingSurface::EventProducerFieldMask);
            getUIDrawingSurfaces(i)->setEventProducer(getInternalParentProject()->getEventProducer());
        endEditCP(getUIDrawingSurfaces(i), UIDrawingSurface::EventProducerFieldMask);
    }

    //Attach the viewports
    for(::osg::UInt32 i(0) ; i<getViewports().size() ; ++i)
    {
        getInternalParentProject()->addViewport(getViewports(i));
    }

    //Attach the initial animations
    for(::osg::UInt32 i(0) ; i<getInitialAnimations().size() ; ++i)
    {
        getInitialAnimations(i)->attachUpdateProducer(editEventProducer());
        getInitialAnimations(i)->start();
    }

    //Attach the initial particle systems
    for(::osg::UInt32 i(0) ; i<getInitialParticleSystems().size() ; ++i)
    {
        getInitialParticleSystems(i)->attachUpdateProducer(editEventProducer());
    }
    
    producerSceneEntered(SceneEvent::create(ScenePtr(this), getTimeStamp()));

    //If There is a physics World then update it's contents
    if(getPhysicsWorld() != NullFC && getPhysicsHandler()->getUpdateNode() == NullFC)
    {
        PhysicsAttachmentsFinder PhysicsFinder;
        PhysicsFinder.traverse(getRoot());

        //For each Body set it's world to this scenes world
        const std::vector<PhysicsBodyPtr>& FoundBodies(PhysicsFinder.getFoundBodies());
        for(UInt32 i(0) ; i<FoundBodies.size() ; ++i)
        {
            beginEditCP(FoundBodies[i],PhysicsBody::WorldFieldMask);
                FoundBodies[i]->setWorld(getPhysicsWorld());
            endEditCP(FoundBodies[i],PhysicsBody::WorldFieldMask);
        }

        //For each Joint set it's world to this scenes world
        const std::vector<PhysicsJointPtr>& FoundJoints(PhysicsFinder.getFoundJoints());
        for(UInt32 i(0) ; i<FoundJoints.size() ; ++i)
        {
            beginEditCP(FoundJoints[i],PhysicsJoint::WorldFieldMask);
                FoundJoints[i]->setWorld(getPhysicsWorld());
            endEditCP(FoundJoints[i],PhysicsJoint::WorldFieldMask);
        }

        //If There is a physics Handler then attach it to the update
        if(getPhysicsHandler() != NullFC)
        {
            
            getPhysicsHandler()->attachUpdateProducer(editEventProducer());

            //Attach all Physics spaces without a parent space to the Physics handler
            beginEditCP(getPhysicsHandler(), PhysicsHandler::SpacesFieldMask | PhysicsHandler::UpdateNodeFieldMask | PhysicsHandler::WorldFieldMask);
                getPhysicsHandler()->setUpdateNode(getRoot());
                getPhysicsHandler()->setWorld(getPhysicsWorld());
            endEditCP(getPhysicsHandler(), PhysicsHandler::SpacesFieldMask | PhysicsHandler::UpdateNodeFieldMask | PhysicsHandler::WorldFieldMask);
            if(getPhysicsHandler()->getSpaces().size() > 0)
            {
                const std::vector<PhysicsGeomPtr>& FoundGeoms(PhysicsFinder.getFoundGeoms());
                for(UInt32 i(0) ; i<FoundGeoms.size() ; ++i)
                {
                    if(FoundGeoms[i]->getSpace() == NullFC)
                    {
                        //If the Goem has no parent space then add it to this scenes space
                        beginEditCP(FoundGeoms[i], PhysicsGeom::SpaceFieldMask);
                            FoundGeoms[i]->setSpace(getPhysicsHandler()->getSpaces()[0]);
                        endEditCP(FoundGeoms[i], PhysicsGeom::SpaceFieldMask);
                    }
                    //Tell the Geom to update it's body
                    endEditCP(FoundGeoms[i], PhysicsGeom::BodyFieldMask);
                }
            }
        }
    }

}

void Scene::start(void)
{
    SLOG << "Starting Scene: "
         << (getName(ScenePtr(this)) ? getName(ScenePtr(this)) : "UNNAMED SCENE")
         << "." << std::endl;

    //If there is  a Lua Module for this scene then load it
    if(!getLuaModule().string().empty())
    {
        LuaManager::the()->runScript(getLuaModule());
    }

    producerSceneStarted(SceneEvent::create(ScenePtr(this), getTimeStamp()));

    _IsStarted = true;
}

void Scene::end(void)
{
    _IsStarted = false;

    producerSceneEnded(SceneEvent::create(ScenePtr(this), getTimeStamp()));

    SLOG << "Ending Scene: "
         << (getName(ScenePtr(this)) ? getName(ScenePtr(this)) : "UNNAMED SCENE")
         << "." << std::endl;
}

void Scene::reset(void)
{
    SLOG << "Reseting Scene: "
         << (getName(ScenePtr(this)) ? getName(ScenePtr(this)) : "UNNAMED SCENE")
         << "." << std::endl;

    producerSceneReset(SceneEvent::create(ScenePtr(this), getTimeStamp()));
}


void Scene::exit(void)
{
    //Dettach the viewports
    for(::osg::UInt32 i(0) ; i<getViewports().size() ; ++i)
    {
        getInternalParentProject()->removeViewport(getViewports(i));
    }

    //Dettach the initial animations
    for(::osg::UInt32 i(0) ; i<getInitialAnimations().size() ; ++i)
    {
        //getInitialAnimations(i)->stop();
        getInitialAnimations(i)->detachUpdateProducer();
    }

    //Dettach the initial particle systems
    for(::osg::UInt32 i(0) ; i<getInitialParticleSystems().size() ; ++i)
    {
        getInitialParticleSystems(i)->detachUpdateProducer();
    }
    
    //Detach the User Interface Drawing Surfaces from the Window Event Producer
    for(::osg::UInt32 i(0) ; i<getUIDrawingSurfaces().size() ; ++i)
    {
        getUIDrawingSurfaces(i)->detachFromEventProducer();
    }
    
    //Detach the listeners
    MainApplication::the()->getMainWindowEventProducer()->removeUpdateListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->removeMouseListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->removeMouseMotionListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->removeMouseWheelListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindowEventProducer()->removeWindowListener(&_SceneUpdateListener);

    //If There is a physics Handler then detach it
    if(getPhysicsHandler() != NullFC)
    {
        //getPhysicsHandler()->detachUpdateProducer();

        //Detach all Physics spaces from the Physics handler
        //beginEditCP(getPhysicsHandler(), PhysicsHandler::SpacesFieldMask | PhysicsHandler::UpdateNodeFieldMask | PhysicsHandler::WorldFieldMask);
            //getPhysicsHandler()->getSpaces().clear();
            //getPhysicsHandler()->setUpdateNode(NullFC);
            //getPhysicsHandler()->setWorld(NullFC);
        //endEditCP(getPhysicsHandler(), PhysicsHandler::SpacesFieldMask | PhysicsHandler::UpdateNodeFieldMask | PhysicsHandler::WorldFieldMask);
    }

    producerSceneExited(SceneEvent::create(ScenePtr(this), getTimeStamp()));

    SLOG << "Exited Scene: "
         << (getName(ScenePtr(this)) ? getName(ScenePtr(this)) : "UNNAMED SCENE")
         << "." << std::endl;
}

void Scene::createDefaults(void)
{
    if(getDefaultCameraBeaconCore() == NullFC)
    {
        TransformPtr TheDefaultCameraBeaconCore = Transform::create();

        beginEditCP(ScenePtr(this), Scene::DefaultCameraBeaconCoreFieldMask);
            setDefaultCameraBeaconCore(TheDefaultCameraBeaconCore);
        endEditCP(ScenePtr(this), Scene::DefaultCameraBeaconCoreFieldMask);
    }

    if(getDefaultCameraBeacon() == NULL)
    {
        NodePtr TheDefaultCameraBeacon = Node::create();

        beginEditCP(ScenePtr(this), Scene::DefaultCameraBeaconFieldMask);
            setDefaultCameraBeacon(TheDefaultCameraBeacon);
        endEditCP(ScenePtr(this), Scene::DefaultCameraBeaconFieldMask);
    }

    if(getRootCore() == NullFC)
    {
        TransformPtr TheRootCore = Transform::create();

        beginEditCP(ScenePtr(this), Scene::RootCoreFieldMask);
            setRootCore(TheRootCore);
        endEditCP(ScenePtr(this), Scene::RootCoreFieldMask);
    }

    if(getRoot() == NULL)
    {
        NodePtr TheRoot = Node::create();

        beginEditCP(ScenePtr(this), Scene::RootFieldMask);
            setRoot(TheRoot);
        endEditCP(ScenePtr(this), Scene::RootFieldMask);
    }

    if(getViewports().size() == 0)
    {
        std::cout << "getViewports().size(): " << getViewports().size()<< std::endl;
        ViewportPtr TheViewport = Viewport::create();

        beginEditCP(ScenePtr(this), Scene::ViewportsFieldMask);
            getViewports().push_back(TheViewport);
        endEditCP(ScenePtr(this), Scene::ViewportsFieldMask);
    }
}

void Scene::initDefaults(void)
{
    Matrix Mat;
    Mat.setIdentity();

    beginEditCP(getDefaultCameraBeaconCore() , Transform::MatrixFieldMask);
        getDefaultCameraBeaconCore()->setMatrix(Mat);
    endEditCP(getDefaultCameraBeaconCore() , Transform::MatrixFieldMask);

    beginEditCP(getDefaultCameraBeacon(), Node::CoreFieldMask);
        getDefaultCameraBeacon()->setCore(getDefaultCameraBeaconCore());
    endEditCP(getDefaultCameraBeacon(), Node::CoreFieldMask);

    beginEditCP(getRootCore() , Transform::MatrixFieldMask);
        getRootCore()->setMatrix(Mat);
    endEditCP(getRootCore() , Transform::MatrixFieldMask);

    beginEditCP(getRoot(), Node::CoreFieldMask | Node::ChildrenFieldMask);
        getRoot()->setCore(getRootCore());
        while(getRoot()->getNChildren() > 0)
        {
            getRoot()->subChild(getRoot()->getNChildren()-1);
        }
        getRoot()->addChild(getDefaultCameraBeacon());
    endEditCP(getRoot(), Node::ChildrenFieldMask | Node::ChildrenFieldMask);

}

void Scene::attachNames(void)
{
    //Backgrounds
    for(::osg::UInt32 i(0); i<getBackgrounds().size() ; ++i)
    {
        attachName(getBackgrounds(i));
    }

    //Foregrounds
    for(::osg::UInt32 i(0); i<getForegrounds().size() ; ++i)
    {
        attachName(getForegrounds(i));
    }

    //Cameras
    for(::osg::UInt32 i(0); i<getCameras().size() ; ++i)
    {
        attachName(getCameras(i));
    }

    //ModelNodes
    for(::osg::UInt32 i(0); i<getModelNodes().size() ; ++i)
    {
        if(getModelNodes(i) != NullFC)
        {
            attachName(getModelNodes(i));
        }
    }
}

/*****************************************************************
* COMPILES, BUT IS UNTESTED.
******************************************************************/
UInt32 Scene::registerNewGenericMethod(const std::string& MethodName)
{
    if(!isGenericMethodDefined(MethodName))
    {
        UInt32 Id = SceneBase::NextMethodId + _GenericMethodIDCount;
        _GenericMethodIDCount++;
        
        MethodDescription newGenericDescription(MethodName.c_str(),
                                                Id,
                                                SFEventPtr::getClassType(),
                                                FunctorAccessMethod());
        
        const_cast<EventProducerType&>(_Producer.getProducerType()).addDescription(newGenericDescription);

        return Id;
    }
    else
    {
        SWARNING << "Scene::registerNewGenericMethod(): Attempted to reregister Method with name : " << MethodName << std::endl;
        return getGenericMethodId(MethodName);
    }
}

bool Scene::unregisterNewGenericMethod(UInt32 Id)
{
    if(SceneBase::NextMethodId > Id)
    {
        SWARNING << "Scene::unregisterNewGenericMethod(): Attempted to unregister Method Id : " << Id 
                 << ".  Can only unregister Methods with Ids > " << SceneBase::NextMethodId << "." << std::endl;
        return false;
    }

    if(!isGenericMethodDefined(Id))
    {
        SWARNING << "Scene::unregisterNewGenericMethod(): Attempted to unregister Method Id : " << Id 
                 << ". That Id has not been registered."<< std::endl;
        return false;
    }
    return const_cast<EventProducerType&>(_Producer.getProducerType()).subDescription(Id);
}

bool Scene::unregisterNewGenericMethod(const std::string& MethodName)
{
    UInt32 Id = getGenericMethodId(MethodName);
    if(Id == 0)
    {
        SWARNING << "Scene::unregisterNewGenericMethod(): Attempted to unregister Method Id : " << Id 
                 << ". That Id has not been registered."<< std::endl;
        return false;
    }
    return unregisterNewGenericMethod(Id);
}

bool Scene::isGenericMethodDefined(UInt32 Id) const
{
    return(_Producer.getProducerType().getMethodDescription(Id) != NULL);
}

bool Scene::isGenericMethodDefined(const std::string& MethodName) const
{
    UInt32 Id = getGenericMethodId(MethodName);
    return Id != 0;
}

//const mismatch?
UInt32 Scene::getGenericMethodId(const std::string& MethodName) const
{
    const MethodDescription* desc = _Producer.getProducerType().findMethodDescription(MethodName.c_str());
    if(desc != NULL)
    {
        return desc->getMethodId();
    }
    else
    {
        return 0;
    }
}

void Scene::produceGenericEvent(UInt32 GenericEventId, GenericEventPtr e)
{
    if(isGenericMethodDefined(GenericEventId))
    {
        _Producer.produceEvent(GenericEventId, e);
    }
    else
    {
        SWARNING << "Generic Event ID " << GenericEventId << " Not Found.";
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void Scene::producerSceneEntered(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneEnteredMethodId, e);
}

void Scene::producerSceneExited(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneExitedMethodId, e);
}

void Scene::producerSceneStarted(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneStartedMethodId, e);
}

void Scene::producerSceneEnded(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneEndedMethodId, e);
}

void Scene::producerSceneReset(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneResetMethodId, e);
}

/*----------------------- constructors & destructors ----------------------*/

Scene::Scene(void) :
    Inherited(),
    _SceneUpdateListener(ScenePtr(this)),
    _IsStarted(false),
    _BlockInput(false),
    _GenericMethodIDCount(0)
{
}

Scene::Scene(const Scene &source) :
    Inherited(source),
        _SceneUpdateListener(ScenePtr(this)),
    _IsStarted(false),
    _BlockInput(source._BlockInput),
    _GenericMethodIDCount(source._GenericMethodIDCount)
{
}

Scene::~Scene(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Scene::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & ViewportsFieldMask) &&
       getInternalParentProject() != NullFC &&
       getInternalParentProject()->getActiveScene() == ScenePtr(this))
    {
        //getInternalParentProject()->clearViewports();

        //Add The Viewports
        for(::osg::UInt32 i(0) ; i<getViewports().size() ; ++i)
        {
            getInternalParentProject()->addViewport(getViewports(i));
        }
    }
}

void Scene::dump(      UInt32 uiIndent   , 
                         const BitVector ) const
{
    for(UInt32 i(0) ; i<getViewports().size() ; ++i)
    {
        //Viewport
        OSG::indentLog(uiIndent*4,PLOG);
        PLOG << i << " Viewport: " 
             << (getName(getViewports(i)) ? getName(getViewports(i)) : "UNNAMED VIEWPORT")
             << ", Bounds ( L " << getViewports(i)->getLeft() 
             << ", R " << getViewports(i)->getRight()
             << ", T " << getViewports(i)->getTop()
             << ", B " << getViewports(i)->getBottom() << ")"
             << std::endl;

        //Camera
        OSG::indentLog((uiIndent+1)*4,PLOG);
        PLOG << "Camera: ";
        if(getViewports(i)->getCamera() == NullFC)
        {
            PLOG << "NULL";
        }
        else
        {
            PLOG << (getName(getViewports(i)->getCamera()) ?
                     getName(getViewports(i)->getCamera()) : "UNNAMED CAMERA")
                 << ", Type: "
                 << getViewports(i)->getCamera()->getType().getCName();
        }
        PLOG << std::endl;

        //Root
        OSG::indentLog((uiIndent+1)*4,PLOG);
        PLOG << "Root Node: " 
             << (getViewports(i)->getRoot() == NullFC ? "NULL" :
                 (getName(getViewports(i)->getRoot()) ?
                  getName(getViewports(i)->getRoot()) : "UNNAMED Node"))
             << std::endl;

        //Background
        OSG::indentLog((uiIndent+1)*4,PLOG);
        PLOG << "Background: ";
        if(getViewports(i)->getBackground() == NullFC)
        {
            PLOG << "NULL";
        }
        else
        {
            PLOG << (getName(getViewports(i)->getBackground()) ? getName(getViewports(i)->getBackground()) : "UNNAMED BACKGROUND")
                 << ", Type: "
                 << getViewports(i)->getBackground()->getType().getCName();
        }
        PLOG << std::endl;

        //Foreground
        for(UInt32 j(0) ; j<getViewports(i)->getForegrounds().size() ; ++j)
        {
            OSG::indentLog((uiIndent+1)*4,PLOG);
            PLOG << j << " Foreground: " 
                 << (getName(getViewports(i)->getForegrounds(j)) ?
                      getName(getViewports(i)->getForegrounds(j)) : "UNNAMED FOREGROUND")
                 << ", Type: "
                 << getViewports(i)->getForegrounds(j)->getType().getCName()
                 << std::endl;
        }
    }
}


OSG_END_NAMESPACE

