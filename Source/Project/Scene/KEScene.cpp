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

#include "KEScene.h"
#include "KEUtils.h"
#include "Project/KEProject.h"
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGUIDrawingSurface.h>
#include "Application/KEMainApplication.h"
#include <OpenSG/OSGLuaManager.h>
#include <OpenSG/OSGPhysicsWorld.h>
#include <OpenSG/OSGPhysicsHandler.h>
#include <OpenSG/OSGPhysicsUtils.h>
#include <OpenSG/OSGGenericEvent.h>

#include <boost/filesystem/operations.hpp>
OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneBase.cpp file.
// To modify it, please change the .fcd file (OSGScene.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Scene::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Scene::enter(void)
{
    SLOG << "Entering Scene: "
        << (getName(SceneRefPtr(this)) ? getName(SceneRefPtr(this)) : "UNNAMED SCENE")
        << "." << std::endl;
    dump(1);

    if(getRoot() == NULL)
    {
        createDefaults();
        initDefaults();
    }

    //Attach the listeners
    MainApplication::the()->getMainWindow()->addUpdateListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->addMouseListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->addMouseMotionListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->addMouseWheelListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->addKeyListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->addWindowListener(&_SceneUpdateListener);

    //Set up Initial Model Nodes
    for(::OSG::UInt32 i(0) ; i<getMFInitialModelNodes()->size() ; ++i)
    {
        getRoot()->addChild(getInitialModelNodes(i));
    }

    //Root Node
    getInternalParentProject()->setActiveNode(getRoot());

    //Attach the User Interface Drawing Surfaces to the Window Event Producer
    for(::OSG::UInt32 i(0) ; i<getMFUIDrawingSurfaces()->size() ; ++i)
    {
        getUIDrawingSurfaces(i)->setEventProducer(getInternalParentProject()->getEventProducer());
    }

    //Attach the viewports
    for(::OSG::UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
    {
        getInternalParentProject()->addViewport(getViewports(i));
    }

    //Attach the initial animations
    for(::OSG::UInt32 i(0) ; i<getMFInitialAnimations()->size() ; ++i)
    {
        getInitialAnimations(i)->attachUpdateProducer(editEventProducer());
        getInitialAnimations(i)->start();
    }

    //Attach the initial particle systems
    for(::OSG::UInt32 i(0) ; i<getMFInitialParticleSystems()->size() ; ++i)
    {
        getInitialParticleSystems(i)->attachUpdateProducer(editEventProducer());
    }

    producerSceneEntered(SceneEvent::create(SceneRefPtr(this), getTimeStamp()));

    //If There is a physics World then update it's contents
    if(getPhysicsWorld() != NULL && getPhysicsHandler()->getUpdateNode() == NULL)
    {
        PhysicsAttachmentsFinder PhysicsFinder;
        PhysicsFinder.traverse(getRoot());

        //For each Body set it's world to this scenes world
        const std::vector<PhysicsBody*>& FoundBodies(PhysicsFinder.getFoundBodies());
        for(UInt32 i(0) ; i<FoundBodies.size() ; ++i)
        {
            FoundBodies[i]->setWorld(getPhysicsWorld());
        }

        //For each Joint set it's world to this scenes world
        const std::vector<PhysicsJoint*>& FoundJoints(PhysicsFinder.getFoundJoints());
        for(UInt32 i(0) ; i<FoundJoints.size() ; ++i)
        {
            FoundJoints[i]->setWorld(getPhysicsWorld());
        }

        //If There is a physics Handler then attach it to the update
        if(getPhysicsHandler() != NULL)
        {

            getPhysicsHandler()->attachUpdateProducer(editEventProducer());

            //Attach all Physics spaces without a parent space to the Physics handler
            getPhysicsHandler()->setUpdateNode(getRoot());
            getPhysicsHandler()->setWorld(getPhysicsWorld());
            if(getPhysicsHandler()->getMFSpaces()->size() > 0)
            {
                const std::vector<PhysicsGeom*>& FoundGeoms(PhysicsFinder.getFoundGeoms());
                for(UInt32 i(0) ; i<FoundGeoms.size() ; ++i)
                {
                    if(FoundGeoms[i]->getSpace() == NULL)
                    {
                        //If the Goem has no parent space then add it to this scenes space
                        FoundGeoms[i]->setSpace(getPhysicsHandler()->getSpaces(0));
                    }
                    //Tell the Geom to update it's body
                }
            }
        }
    }

}

void Scene::start(void)
{
    SLOG << "Starting Scene: "
        << (getName(this) ? getName(this) : "UNNAMED SCENE")
        << "." << std::endl;

    //If there is  a Lua Module for this scene then load it
    if(!getLuaModule().string().empty())
    {
        if(!boost::filesystem::exists(getLuaModule()))
        {
            SWARNING << "Cannot load script for scene " << (getName(this) ? getName(this) : "UNNAMED SCENE") << " because file: "
                << getLuaModule().string() << " does not exist." << std::endl;
        }
        else if(!boost::filesystem::is_regular_file(getLuaModule()))
        {
            SWARNING << "Cannot load script for scene " << (getName(this) ? getName(this) : "UNNAMED SCENE") << " because file: "
                << getLuaModule().string() << " is not a regular file." << std::endl;
        }
        else
        {
            LuaManager::the()->runScript(getLuaModule());
        }
    }

    producerSceneStarted(SceneEvent::create(SceneRefPtr(this), getTimeStamp()));

    _IsStarted = true;
}

void Scene::end(void)
{
    _IsStarted = false;

    producerSceneEnded(SceneEvent::create(SceneRefPtr(this), getTimeStamp()));

    SLOG << "Ending Scene: "
        << (getName(SceneRefPtr(this)) ? getName(SceneRefPtr(this)) : "UNNAMED SCENE")
        << "." << std::endl;
}

void Scene::reset(void)
{
    SLOG << "Reseting Scene: "
        << (getName(SceneRefPtr(this)) ? getName(SceneRefPtr(this)) : "UNNAMED SCENE")
        << "." << std::endl;

    producerSceneReset(SceneEvent::create(SceneRefPtr(this), getTimeStamp()));
}


void Scene::exit(void)
{
    //Dettach the viewports
    for(::OSG::UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
    {
        getInternalParentProject()->removeViewport(getViewports(i));
    }

    //Dettach the initial animations
    for(::OSG::UInt32 i(0) ; i<getMFInitialAnimations()->size() ; ++i)
    {
        //getInitialAnimations(i)->stop();
        getInitialAnimations(i)->detachUpdateProducer();
    }

    //Dettach the initial particle systems
    for(::OSG::UInt32 i(0) ; i<getMFInitialParticleSystems()->size() ; ++i)
    {
        getInitialParticleSystems(i)->detachUpdateProducer();
    }

    //Detach the User Interface Drawing Surfaces from the Window Event Producer
    for(::OSG::UInt32 i(0) ; i<getMFUIDrawingSurfaces()->size() ; ++i)
    {
        getUIDrawingSurfaces(i)->detachFromEventProducer();
    }

    //Detach the listeners
    MainApplication::the()->getMainWindow()->removeUpdateListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->removeMouseListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->removeMouseMotionListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->removeMouseWheelListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->removeKeyListener(&_SceneUpdateListener);
    MainApplication::the()->getMainWindow()->removeWindowListener(&_SceneUpdateListener);

    //If There is a physics Handler then detach it
    if(getPhysicsHandler() != NULL)
    {
        //getPhysicsHandler()->detachUpdateProducer();

        //Detach all Physics spaces from the Physics handler
        //getPhysicsHandler()->getSpaces().clear();
        //getPhysicsHandler()->setUpdateNode(NULL);
        //getPhysicsHandler()->setWorld(NULL);
    }

    producerSceneExited(SceneEvent::create(SceneRefPtr(this), getTimeStamp()));

    SLOG << "Exited Scene: "
        << (getName(SceneRefPtr(this)) ? getName(SceneRefPtr(this)) : "UNNAMED SCENE")
        << "." << std::endl;
}

void Scene::createDefaults(void)
{
    if(getDefaultCameraBeaconCore() == NULL)
    {
        TransformRefPtr TheDefaultCameraBeaconCore = Transform::create();

        setDefaultCameraBeaconCore(TheDefaultCameraBeaconCore);
    }

    if(getDefaultCameraBeacon() == NULL)
    {
        NodeRefPtr TheDefaultCameraBeacon = Node::create();

        setDefaultCameraBeacon(TheDefaultCameraBeacon);
    }

    if(getRootCore() == NULL)
    {
        TransformRefPtr TheRootCore = Transform::create();

        setRootCore(TheRootCore);
    }

    if(getRoot() == NULL)
    {
        NodeRefPtr TheRoot = Node::create();

        setRoot(TheRoot);
    }

    if(getMFViewports()->size() == 0)
    {
        ViewportRefPtr TheViewport = Viewport::create();

        pushToViewports(TheViewport);
    }
}

void Scene::initDefaults(void)
{
    Matrix Mat;
    Mat.setIdentity();

    getDefaultCameraBeaconCore()->setMatrix(Mat);

    getDefaultCameraBeacon()->setCore(getDefaultCameraBeaconCore());

    getRootCore()->setMatrix(Mat);

    getRoot()->setCore(getRootCore());
    while(getRoot()->getNChildren() > 0)
    {
        getRoot()->subChild(getRoot()->getNChildren()-1);
    }
    getRoot()->addChild(getDefaultCameraBeacon());

}

void Scene::attachNames(void)
{
    //Backgrounds
    for(::OSG::UInt32 i(0); i<getMFBackgrounds()->size() ; ++i)
    {
        attachName(getBackgrounds(i));
    }

    //Foregrounds
    for(::OSG::UInt32 i(0); i<getMFForegrounds()->size() ; ++i)
    {
        attachName(getForegrounds(i));
    }

    //Cameras
    for(::OSG::UInt32 i(0); i<getMFCameras()->size() ; ++i)
    {
        attachName(getCameras(i));
    }

    //ModelNodes
    for(::OSG::UInt32 i(0); i<getMFModelNodes()->size() ; ++i)
    {
        if(getModelNodes(i) != NULL)
        {
            attachName(getModelNodes(i));
        }
    }
}

UInt32 Scene::registerNewGenericMethod(const std::string& MethodName,
                                       const std::string& MethodDescriptionText)
{
    if(!isGenericMethodDefined(MethodName))
    {
        UInt32 Id = SceneBase::NextProducedMethodId + _GenericMethodIDCount;
        _GenericMethodIDCount++;

        MethodDescription newGenericDescription(MethodName,
                                                MethodDescriptionText,
                                                Id,
                                                SFRecEventPtr::getClassType(),
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
    if(SceneBase::NextProducedMethodId > Id)
    {
        SWARNING << "Scene::unregisterNewGenericMethod(): Attempted to unregister Method Id : " << Id 
                                                          << ".  Can only unregister Methods with Ids > " << SceneBase::NextProducedMethodId << "." << std::endl;
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

void Scene::produceGenericEvent(UInt32 GenericEventId, GenericEventUnrecPtr e)
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

void Scene::producerSceneEntered(const SceneEventUnrecPtr e)
{
    _Producer.produceEvent(SceneEnteredMethodId, e);
}

void Scene::producerSceneExited(const SceneEventUnrecPtr e)
{
    _Producer.produceEvent(SceneExitedMethodId, e);
}

void Scene::producerSceneStarted(const SceneEventUnrecPtr e)
{
    _Producer.produceEvent(SceneStartedMethodId, e);
}

void Scene::producerSceneEnded(const SceneEventUnrecPtr e)
{
    _Producer.produceEvent(SceneEndedMethodId, e);
}

void Scene::producerSceneReset(const SceneEventUnrecPtr e)
{
    _Producer.produceEvent(SceneResetMethodId, e);
}

/*----------------------- constructors & destructors ----------------------*/

Scene::Scene(void) :
    Inherited(),
    _SceneUpdateListener(SceneRefPtr(this)),
    _IsStarted(false),
    _BlockInput(false),
    _GenericMethodIDCount(0)
{
}

Scene::Scene(const Scene &source) :
    Inherited(source),
    _SceneUpdateListener(SceneRefPtr(this)),
    _IsStarted(false),
    _BlockInput(source._BlockInput),
    _GenericMethodIDCount(source._GenericMethodIDCount)
{
}

Scene::~Scene(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Scene::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & ViewportsFieldMask) &&
       getInternalParentProject() != NULL &&
       getInternalParentProject()->getActiveScene() == this)
    {
        //getInternalParentProject()->clearViewports();

        //Add The Viewports
        for(::OSG::UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
        {
            getInternalParentProject()->addViewport(getViewports(i));
        }
    }
}

void Scene::dump(      UInt32 uiIndent   ,
                         const BitVector ) const
{
    for(UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
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
        if(getViewports(i)->getCamera() == NULL)
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
             << (getViewports(i)->getRoot() == NULL ? "NULL" :
                 (getName(getViewports(i)->getRoot()) ?
                  getName(getViewports(i)->getRoot()) : "UNNAMED Node"))
             << std::endl;

        //Background
        OSG::indentLog((uiIndent+1)*4,PLOG);
        PLOG << "Background: ";
        if(getViewports(i)->getBackground() == NULL)
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
        for(UInt32 j(0) ; j<getViewports(i)->getMFForegrounds()->size() ; ++j)
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
