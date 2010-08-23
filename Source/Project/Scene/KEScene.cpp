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
#include <OpenSG/OSGAnimation.h>
#include <OpenSG/OSGParticleSystem.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGUIDrawingSurface.h>
#include "Application/KEMainApplication.h"
#include <OpenSG/OSGLuaManager.h>
#include <OpenSG/OSGPhysicsWorld.h>
#include <OpenSG/OSGPhysicsHandler.h>
#include <OpenSG/OSGPhysicsUtils.h>
#include <OpenSG/OSGGenericEventDetails.h>
#include "Project/SceneObject/KESceneObject.h"

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
   _UpdateConnection = MainApplication::the()->getMainWindow()->connectUpdate(boost::bind(&Scene::handleUpdate, this, _1));
   _MouseClickedConnection = MainApplication::the()->getMainWindow()->connectMouseClicked(boost::bind(&Scene::handleMouseClicked, this, _1));
   _MouseEnteredConnection = MainApplication::the()->getMainWindow()->connectMouseEntered(boost::bind(&Scene::handleMouseEntered, this, _1));
   _MouseExitedConnection = MainApplication::the()->getMainWindow()->connectMouseExited(boost::bind(&Scene::handleMouseExited, this, _1));
   _MousePressedConnection = MainApplication::the()->getMainWindow()->connectMousePressed(boost::bind(&Scene::handleMousePressed, this, _1));
   _MouseReleasedConnection = MainApplication::the()->getMainWindow()->connectMouseReleased(boost::bind(&Scene::handleMouseReleased, this, _1));
   _MouseMovedConnection = MainApplication::the()->getMainWindow()->connectMouseMoved(boost::bind(&Scene::handleMouseMoved, this, _1));
   _MouseDraggedConnection = MainApplication::the()->getMainWindow()->connectMouseDragged(boost::bind(&Scene::handleMouseDragged, this, _1));
   _MouseWheelMovedConnection = MainApplication::the()->getMainWindow()->connectMouseWheelMoved(boost::bind(&Scene::handleMouseWheelMoved, this, _1));
   _KeyPressedConnection = MainApplication::the()->getMainWindow()->connectKeyPressed(boost::bind(&Scene::handleKeyPressed, this, _1));
   _KeyReleasedConnection = MainApplication::the()->getMainWindow()->connectKeyReleased(boost::bind(&Scene::handleKeyReleased, this, _1));
   _KeyTypedConnection = MainApplication::the()->getMainWindow()->connectKeyTyped(boost::bind(&Scene::handleKeyTyped, this, _1));
   _WindowOpenedConnection = MainApplication::the()->getMainWindow()->connectWindowOpened(boost::bind(&Scene::handleWindowOpened, this, _1));
   _WindowClosingConnection = MainApplication::the()->getMainWindow()->connectWindowClosing(boost::bind(&Scene::handleWindowClosing, this, _1));
   _WindowClosedConnection = MainApplication::the()->getMainWindow()->connectWindowClosed(boost::bind(&Scene::handleWindowClosed, this, _1));
   _WindowIconifiedConnection = MainApplication::the()->getMainWindow()->connectWindowIconified(boost::bind(&Scene::handleWindowIconified, this, _1));
   _WindowDeiconifiedConnection = MainApplication::the()->getMainWindow()->connectWindowDeiconified(boost::bind(&Scene::handleWindowDeiconified, this, _1));
   _WindowActivatedConnection = MainApplication::the()->getMainWindow()->connectWindowActivated(boost::bind(&Scene::handleWindowActivated, this, _1));
   _WindowDeactivatedConnection = MainApplication::the()->getMainWindow()->connectWindowDeactivated(boost::bind(&Scene::handleWindowDeactivated, this, _1));
   _WindowEnteredConnection = MainApplication::the()->getMainWindow()->connectWindowEntered(boost::bind(&Scene::handleWindowEntered, this, _1));
   _WindowExitedConnection = MainApplication::the()->getMainWindow()->connectWindowExited(boost::bind(&Scene::handleWindowExited, this, _1));

    //Set up Initial Model Nodes
    for(::OSG::UInt32 i(0) ; i<getMFInitialModelNodes()->size() ; ++i)
    {
        getRoot()->addChild(getInitialModelNodes(i));
    }

    //Root Node
    getParentProject()->setActiveNode(getRoot());

    //Attach the User Interface Drawing Surfaces to the Window Event Producer
    for(::OSG::UInt32 i(0) ; i<getMFUIDrawingSurfaces()->size() ; ++i)
    {
        getUIDrawingSurfaces(i)->setEventProducer(getParentProject()->getEventProducer());
    }

    //Attach the viewports
    for(::OSG::UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
    {
        getParentProject()->addViewport(getViewports(i));
    }

    //Attach the initial animations
    for(::OSG::UInt32 i(0) ; i<getMFInitialAnimations()->size() ; ++i)
    {
        getInitialAnimations(i)->attachUpdateProducer(this);
        getInitialAnimations(i)->start();
    }

    //Attach the initial particle systems
    for(::OSG::UInt32 i(0) ; i<getMFInitialParticleSystems()->size() ; ++i)
    {
        getInitialParticleSystems(i)->attachUpdateProducer(this);
    }

    produceSceneEntered();

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

            getPhysicsHandler()->attachUpdateProducer(this);

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

    produceSceneStarted();

    _IsStarted = true;
}

void Scene::end(void)
{
    _IsStarted = false;

    produceSceneEnded();

    SLOG << "Ending Scene: "
        << (getName(SceneRefPtr(this)) ? getName(SceneRefPtr(this)) : "UNNAMED SCENE")
        << "." << std::endl;
}

void Scene::reset(void)
{
    SLOG << "Reseting Scene: "
        << (getName(SceneRefPtr(this)) ? getName(SceneRefPtr(this)) : "UNNAMED SCENE")
        << "." << std::endl;

    produceSceneReset();
}


void Scene::exit(void)
{
    //Dettach the viewports
    for(::OSG::UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
    {
        getParentProject()->removeViewport(getViewports(i));
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
    _UpdateConnection.disconnect();
    _MouseClickedConnection.disconnect();
    _MouseEnteredConnection.disconnect();
    _MouseExitedConnection.disconnect();
    _MousePressedConnection.disconnect();
    _MouseReleasedConnection.disconnect();
    _MouseMovedConnection.disconnect();
    _MouseDraggedConnection.disconnect();
    _MouseWheelMovedConnection.disconnect();
    _KeyPressedConnection.disconnect();
    _KeyReleasedConnection.disconnect();
    _KeyTypedConnection.disconnect();
    _WindowOpenedConnection.disconnect();
    _WindowClosingConnection.disconnect();
    _WindowClosedConnection.disconnect();
    _WindowIconifiedConnection.disconnect();
    _WindowDeiconifiedConnection.disconnect();
    _WindowActivatedConnection.disconnect();
    _WindowDeactivatedConnection.disconnect();
    _WindowEnteredConnection.disconnect();
    _WindowExitedConnection.disconnect();

    //If There is a physics Handler then detach it
    if(getPhysicsHandler() != NULL)
    {
        //getPhysicsHandler()->detachUpdateProducer();

        //Detach all Physics spaces from the Physics handler
        //getPhysicsHandler()->getSpaces().clear();
        //getPhysicsHandler()->setUpdateNode(NULL);
        //getPhysicsHandler()->setWorld(NULL);
    }

    produceSceneExited();

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

UInt32 Scene::registerNewGenericEvent(const std::string& EventName,
                                       const std::string& EventDescriptionText)
{
    if(!isGenericEventDefined(EventName))
    {
        UInt32 Id = SceneBase::NextProducedEventId + _GenericEventIDCount;
        _GenericEventIDCount++;

        EventDescription newGenericDescription(EventName,
                                               EventDescriptionText,
                                               Id,
                                               FieldTraits<GenericEventDetails *>::getType(),
                                               true,
                                               NULL/*static_cast<EventGetMethod>(&Scene::getHandleGenericEventSignal)*/);

        _GenericEventSignalMap[Id] = boost::shared_ptr<GenericEventSignalType>(new GenericEventSignalType());
        const_cast<EventProducerType&>(getProducerType()).addDescription(newGenericDescription);

        return Id;
    }
    else
    {
        SWARNING << "Scene::registerNewGenericEvent(): Attempted to reregister Event with name : " << EventName << std::endl;
        return getGenericEventId(EventName);
    }
}

bool Scene::unregisterNewGenericEvent(UInt32 Id)
{
    if(SceneBase::NextProducedEventId > Id)
    {
        SWARNING << "Scene::unregisterNewGenericEvent(): Attempted to unregister Event Id : " << Id 
                 << ".  Can only unregister Events with Ids > " << SceneBase::NextProducedEventId << "." << std::endl;
        return false;
    }

    if(!isGenericEventDefined(Id))
    {
        SWARNING << "Scene::unregisterNewGenericEvent(): Attempted to unregister Event Id : " << Id 
                 << ". That Id has not been registered." << std::endl;
        return false;
    }

    _GenericEventSignalMap.erase(_GenericEventSignalMap.find(Id));
    return const_cast<EventProducerType&>(getProducerType()).subDescription(Id);
}

bool Scene::unregisterNewGenericEvent(const std::string& EventName)
{
    UInt32 Id = getGenericEventId(EventName);
    if(Id == 0)
    {
        SWARNING << "Scene::unregisterNewGenericEvent(): Attempted to unregister Event Id : " << Id 
                                                          << ". That Id has not been registered."<< std::endl;
        return false;
    }
    return unregisterNewGenericEvent(Id);
}

bool Scene::isGenericEventDefined(UInt32 Id) const
{
    return (Id >= Scene::NextProducedEventId && Id <= getProducerType().getNumEventDescs());
}

bool Scene::isGenericEventDefined(const std::string& EventName) const
{
    UInt32 Id = getGenericEventId(EventName);
    return Id != 0;
}

boost::signals2::connection Scene::connectGenericEvent(UInt32 genericEventId, 
                                                       const BaseEventType::slot_type &listener, 
                                                       boost::signals2::connect_position at)
{
    if(isGenericEventDefined(genericEventId))
    {
        return _GenericEventSignalMap[genericEventId]->connect(listener, at);
    }
    else
    {
        SWARNING << "Generic Event ID " << genericEventId << " Not Found.";
        return boost::signals2::connection();
    }
}

boost::signals2::connection Scene::connectGenericEvent(UInt32 genericEventId, 
                                                        const BaseEventType::group_type &group,
                                                        const BaseEventType::slot_type &listener,
                                                        boost::signals2::connect_position at)
{
    if(isGenericEventDefined(genericEventId))
    {
        return _GenericEventSignalMap[genericEventId]->connect(group, listener, at);
    }
    else
    {
        SWARNING << "Generic Event ID " << genericEventId << " Not Found.";
        return boost::signals2::connection();
    }
}

UInt32 Scene::getGenericEventId(const std::string& EventName) const
{
    const EventDescription* desc = getProducerType().findEventDescription(EventName.c_str());
    if(desc != NULL)
    {
        return desc->getEventId();
    }
    else
    {
        return 0;
    }
}

std::string Scene::getGenericEventName  (      UInt32       Id        ) const
{
    const EventDescription* desc = getProducerType().getEventDescription(Id);
    if(desc != NULL)
    {
        return desc->getName();
    }
    else
    {
        return NULL;
    }
}

void Scene::produceGenericEvent(UInt32 GenericEventId, GenericEventDetails* const e)
{
    if(isGenericEventDefined(GenericEventId))
    {
        _GenericEventSignalMap[GenericEventId]->set_combiner(ConsumableEventCombiner(e));

        (*_GenericEventSignalMap[GenericEventId])(e, GenericEventId);
    }
    else
    {
        SWARNING << "Generic Event ID " << GenericEventId << " Not Found.";
    }
}

void Scene::produceGenericEvent(std::string GenericEventName, GenericEventDetails* const e)
{
    produceGenericEvent(getGenericEventId(GenericEventName),e);
}

void Scene::checkBehaviorInitialization()
{
	for(UInt32 i = 0; i < _mfSceneObjects.size(); i++)
	{
		getSceneObjects(i)->checkBehaviorInitialization();
	}
}

boost::signals2::connection Scene::connectEvent(UInt32 eventId, 
                                                             const BaseEventType::slot_type &listener, 
                                                             boost::signals2::connect_position at)
{
    if(isGenericEventDefined(eventId))
    {
        return connectGenericEvent(eventId, listener, at);
    }
    else
    {
        return Inherited::connectEvent(eventId, listener, at);
    }
}
                                  
boost::signals2::connection Scene::connectEvent(UInt32 eventId, 
                                  const BaseEventType::group_type &group,
                                  const BaseEventType::slot_type &listener,
                                  boost::signals2::connect_position at)
{
    if(isGenericEventDefined(eventId))
    {
        return connectGenericEvent(eventId, group, listener, at);
    }
    else
    {
        return Inherited::connectEvent(eventId, group, listener, at);
    }
}

void   Scene::disconnectEvent        (UInt32 eventId, const BaseEventType::group_type &group)
{
    if(isGenericEventDefined(eventId))
    {
        _GenericEventSignalMap[eventId]->disconnect(group);
    }
    else
    {
        Inherited::disconnectEvent(eventId, group);
    }
}

void   Scene::disconnectAllSlotsEvent(UInt32 eventId)
{
    if(isGenericEventDefined(eventId))
    {
        _GenericEventSignalMap[eventId]->disconnect_all_slots();
    }
    else
    {
        Inherited::disconnectAllSlotsEvent(eventId);
    }
}

bool   Scene::isEmptyEvent           (UInt32 eventId) const
{
    if(isGenericEventDefined(eventId))
    {
        return (*_GenericEventSignalMap.find(eventId)).second->empty();
    }
    else
    {
        return Inherited::isEmptyEvent(eventId);
    }
}

UInt32 Scene::numSlotsEvent          (UInt32 eventId) const
{
    if(isGenericEventDefined(eventId))
    {
        return (*_GenericEventSignalMap.find(eventId)).second->num_slots();
    }
    else
    {
        return Inherited::numSlotsEvent(eventId);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Scene::produceSceneEntered(void)
{
    SceneEventDetailsUnrecPtr details = SceneEventDetails::create(this, getTimeStamp());
   
    Inherited::produceSceneEntered(details);
}

void Scene::produceSceneExited(void)
{
    SceneEventDetailsUnrecPtr details = SceneEventDetails::create(this, getTimeStamp());
   
    Inherited::produceSceneExited(details);
}

void Scene::produceSceneStarted(void)
{
    SceneEventDetailsUnrecPtr details = SceneEventDetails::create(this, getTimeStamp());
   
    Inherited::produceSceneStarted(details);
}

void Scene::produceSceneEnded(void)
{
    SceneEventDetailsUnrecPtr details = SceneEventDetails::create(this, getTimeStamp());
   
    Inherited::produceSceneEnded(details);
}

void Scene::produceSceneReset(void)
{
    SceneEventDetailsUnrecPtr details = SceneEventDetails::create(this, getTimeStamp());
   
    Inherited::produceSceneReset(details);
}

void Scene::resolveLinks(void)
{
    Inherited::resolveLinks();
        
    _UpdateConnection.disconnect();
    _MouseClickedConnection.disconnect();
    _MouseEnteredConnection.disconnect();
    _MouseExitedConnection.disconnect();
    _MousePressedConnection.disconnect();
    _MouseReleasedConnection.disconnect();
    _MouseMovedConnection.disconnect();
    _MouseDraggedConnection.disconnect();
    _MouseWheelMovedConnection.disconnect();
    _KeyPressedConnection.disconnect();
    _KeyReleasedConnection.disconnect();
    _KeyTypedConnection.disconnect();
    _WindowOpenedConnection.disconnect();
    _WindowClosingConnection.disconnect();
    _WindowClosedConnection.disconnect();
    _WindowIconifiedConnection.disconnect();
    _WindowDeiconifiedConnection.disconnect();
    _WindowActivatedConnection.disconnect();
    _WindowDeactivatedConnection.disconnect();
    _WindowEnteredConnection.disconnect();
    _WindowExitedConnection.disconnect();

}

/*----------------------- constructors & destructors ----------------------*/

Scene::Scene(void) :
    Inherited(),
    _IsStarted(false),
    _BlockInput(false),
    _GenericEventSignalMap(),
    _GenericEventIDCount(0)
{
}

Scene::Scene(const Scene &source) :
    Inherited(source),
    _IsStarted(false),
    _BlockInput(source._BlockInput),
    _GenericEventSignalMap(),
    _GenericEventIDCount(source._GenericEventIDCount)
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
       getParentProject() != NULL &&
       getParentProject()->getActiveScene() == this)
    {
        //getParentProject()->clearViewports();

        //Add The Viewports
        for(::OSG::UInt32 i(0) ; i<getMFViewports()->size() ; ++i)
        {
            getParentProject()->addViewport(getViewports(i));
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
