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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class Scene!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SceneBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 SceneBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! access the producer type of the class
inline
const EventProducerType &SceneBase::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 SceneBase::getProducerClassTypeId(void)
{
    return _producerType.getId();
}

//! create a new instance of the class
inline
ScenePtr SceneBase::create(void) 
{
    ScenePtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = ScenePtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
ScenePtr SceneBase::createEmpty(void) 
{ 
    ScenePtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the Scene::_sfInternalParentProject field.
inline
const SFProjectPtr *SceneBase::getSFInternalParentProject(void) const
{
    return &_sfInternalParentProject;
}

//! Get the Scene::_sfInternalParentProject field.
inline
SFProjectPtr *SceneBase::editSFInternalParentProject(void)
{
    return &_sfInternalParentProject;
}

//! Get the Scene::_mfViewports field.
inline
const MFViewportPtr *SceneBase::getMFViewports(void) const
{
    return &_mfViewports;
}

//! Get the Scene::_mfViewports field.
inline
MFViewportPtr *SceneBase::editMFViewports(void)
{
    return &_mfViewports;
}

//! Get the Scene::_mfBackgrounds field.
inline
const MFBackgroundPtr *SceneBase::getMFBackgrounds(void) const
{
    return &_mfBackgrounds;
}

//! Get the Scene::_mfBackgrounds field.
inline
MFBackgroundPtr *SceneBase::editMFBackgrounds(void)
{
    return &_mfBackgrounds;
}

//! Get the Scene::_mfUIDrawingSurfaces field.
inline
const MFUIDrawingSurfacePtr *SceneBase::getMFUIDrawingSurfaces(void) const
{
    return &_mfUIDrawingSurfaces;
}

//! Get the Scene::_mfUIDrawingSurfaces field.
inline
MFUIDrawingSurfacePtr *SceneBase::editMFUIDrawingSurfaces(void)
{
    return &_mfUIDrawingSurfaces;
}

//! Get the Scene::_sfInitialBackground field.
inline
const SFBackgroundPtr *SceneBase::getSFInitialBackground(void) const
{
    return &_sfInitialBackground;
}

//! Get the Scene::_sfInitialBackground field.
inline
SFBackgroundPtr *SceneBase::editSFInitialBackground(void)
{
    return &_sfInitialBackground;
}

//! Get the Scene::_mfForegrounds field.
inline
const MFForegroundPtr *SceneBase::getMFForegrounds(void) const
{
    return &_mfForegrounds;
}

//! Get the Scene::_mfForegrounds field.
inline
MFForegroundPtr *SceneBase::editMFForegrounds(void)
{
    return &_mfForegrounds;
}

//! Get the Scene::_mfInitialForegrounds field.
inline
const MFForegroundPtr *SceneBase::getMFInitialForegrounds(void) const
{
    return &_mfInitialForegrounds;
}

//! Get the Scene::_mfInitialForegrounds field.
inline
MFForegroundPtr *SceneBase::editMFInitialForegrounds(void)
{
    return &_mfInitialForegrounds;
}

//! Get the Scene::_mfModelNodes field.
inline
const MFNodePtr *SceneBase::getMFModelNodes(void) const
{
    return &_mfModelNodes;
}

//! Get the Scene::_mfModelNodes field.
inline
MFNodePtr *SceneBase::editMFModelNodes(void)
{
    return &_mfModelNodes;
}

//! Get the Scene::_mfInitialModelNodes field.
inline
const MFNodePtr *SceneBase::getMFInitialModelNodes(void) const
{
    return &_mfInitialModelNodes;
}

//! Get the Scene::_mfInitialModelNodes field.
inline
MFNodePtr *SceneBase::editMFInitialModelNodes(void)
{
    return &_mfInitialModelNodes;
}

//! Get the Scene::_sfRoot field.
inline
const SFNodePtr *SceneBase::getSFRoot(void) const
{
    return &_sfRoot;
}

//! Get the Scene::_sfRoot field.
inline
SFNodePtr *SceneBase::editSFRoot(void)
{
    return &_sfRoot;
}

//! Get the Scene::_sfRootCore field.
inline
const SFTransformPtr *SceneBase::getSFRootCore(void) const
{
    return &_sfRootCore;
}

//! Get the Scene::_sfRootCore field.
inline
SFTransformPtr *SceneBase::editSFRootCore(void)
{
    return &_sfRootCore;
}

//! Get the Scene::_sfDefaultCameraBeacon field.
inline
const SFNodePtr *SceneBase::getSFDefaultCameraBeacon(void) const
{
    return &_sfDefaultCameraBeacon;
}

//! Get the Scene::_sfDefaultCameraBeacon field.
inline
SFNodePtr *SceneBase::editSFDefaultCameraBeacon(void)
{
    return &_sfDefaultCameraBeacon;
}

//! Get the Scene::_sfDefaultCameraBeaconCore field.
inline
const SFTransformPtr *SceneBase::getSFDefaultCameraBeaconCore(void) const
{
    return &_sfDefaultCameraBeaconCore;
}

//! Get the Scene::_sfDefaultCameraBeaconCore field.
inline
SFTransformPtr *SceneBase::editSFDefaultCameraBeaconCore(void)
{
    return &_sfDefaultCameraBeaconCore;
}

//! Get the Scene::_mfCameras field.
inline
const MFCameraPtr *SceneBase::getMFCameras(void) const
{
    return &_mfCameras;
}

//! Get the Scene::_mfCameras field.
inline
MFCameraPtr *SceneBase::editMFCameras(void)
{
    return &_mfCameras;
}

//! Get the Scene::_sfInitialCamera field.
inline
const SFCameraPtr *SceneBase::getSFInitialCamera(void) const
{
    return &_sfInitialCamera;
}

//! Get the Scene::_sfInitialCamera field.
inline
SFCameraPtr *SceneBase::editSFInitialCamera(void)
{
    return &_sfInitialCamera;
}

//! Get the Scene::_mfAnimations field.
inline
const MFAnimationPtr *SceneBase::getMFAnimations(void) const
{
    return &_mfAnimations;
}

//! Get the Scene::_mfAnimations field.
inline
MFAnimationPtr *SceneBase::editMFAnimations(void)
{
    return &_mfAnimations;
}

//! Get the Scene::_mfInitialAnimations field.
inline
const MFAnimationPtr *SceneBase::getMFInitialAnimations(void) const
{
    return &_mfInitialAnimations;
}

//! Get the Scene::_mfInitialAnimations field.
inline
MFAnimationPtr *SceneBase::editMFInitialAnimations(void)
{
    return &_mfInitialAnimations;
}

//! Get the Scene::_mfParticleSystems field.
inline
const MFParticleSystemPtr *SceneBase::getMFParticleSystems(void) const
{
    return &_mfParticleSystems;
}

//! Get the Scene::_mfParticleSystems field.
inline
MFParticleSystemPtr *SceneBase::editMFParticleSystems(void)
{
    return &_mfParticleSystems;
}

//! Get the Scene::_mfInitialParticleSystems field.
inline
const MFParticleSystemPtr *SceneBase::getMFInitialParticleSystems(void) const
{
    return &_mfInitialParticleSystems;
}

//! Get the Scene::_mfInitialParticleSystems field.
inline
MFParticleSystemPtr *SceneBase::editMFInitialParticleSystems(void)
{
    return &_mfInitialParticleSystems;
}

//! Get the Scene::_sfLuaModule field.
inline
const SFPath *SceneBase::getSFLuaModule(void) const
{
    return &_sfLuaModule;
}

//! Get the Scene::_sfLuaModule field.
inline
SFPath *SceneBase::editSFLuaModule(void)
{
    return &_sfLuaModule;
}

//! Get the Scene::_sfPhysicsHandler field.
inline
const SFPhysicsHandlerPtr *SceneBase::getSFPhysicsHandler(void) const
{
    return &_sfPhysicsHandler;
}

//! Get the Scene::_sfPhysicsHandler field.
inline
SFPhysicsHandlerPtr *SceneBase::editSFPhysicsHandler(void)
{
    return &_sfPhysicsHandler;
}

//! Get the Scene::_sfPhysicsWorld field.
inline
const SFPhysicsWorldPtr *SceneBase::getSFPhysicsWorld(void) const
{
    return &_sfPhysicsWorld;
}

//! Get the Scene::_sfPhysicsWorld field.
inline
SFPhysicsWorldPtr *SceneBase::editSFPhysicsWorld(void)
{
    return &_sfPhysicsWorld;
}

//! Get the Scene::_sfGenericMethodIDs field.
inline
const SFUInt32 *SceneBase::getSFGenericMethodIDs(void) const
{
    return &_sfGenericMethodIDs;
}

//! Get the Scene::_sfGenericMethodIDs field.
inline
SFUInt32 *SceneBase::editSFGenericMethodIDs(void)
{
    return &_sfGenericMethodIDs;
}


//! Get the value of the Scene::_sfInternalParentProject field.
inline
ProjectPtr &SceneBase::editInternalParentProject(void)
{
    return _sfInternalParentProject.getValue();
}

//! Get the value of the Scene::_sfInternalParentProject field.
inline
const ProjectPtr &SceneBase::getInternalParentProject(void) const
{
    return _sfInternalParentProject.getValue();
}

//! Set the value of the Scene::_sfInternalParentProject field.
inline
void SceneBase::setInternalParentProject(const ProjectPtr &value)
{
    _sfInternalParentProject.setValue(value);
}

//! Get the value of the Scene::_sfInitialBackground field.
inline
BackgroundPtr &SceneBase::editInitialBackground(void)
{
    return _sfInitialBackground.getValue();
}

//! Get the value of the Scene::_sfInitialBackground field.
inline
const BackgroundPtr &SceneBase::getInitialBackground(void) const
{
    return _sfInitialBackground.getValue();
}

//! Set the value of the Scene::_sfInitialBackground field.
inline
void SceneBase::setInitialBackground(const BackgroundPtr &value)
{
    _sfInitialBackground.setValue(value);
}

//! Get the value of the Scene::_sfRoot field.
inline
NodePtr &SceneBase::editRoot(void)
{
    return _sfRoot.getValue();
}

//! Get the value of the Scene::_sfRoot field.
inline
const NodePtr &SceneBase::getRoot(void) const
{
    return _sfRoot.getValue();
}

//! Set the value of the Scene::_sfRoot field.
inline
void SceneBase::setRoot(const NodePtr &value)
{
    _sfRoot.setValue(value);
}

//! Get the value of the Scene::_sfRootCore field.
inline
TransformPtr &SceneBase::editRootCore(void)
{
    return _sfRootCore.getValue();
}

//! Get the value of the Scene::_sfRootCore field.
inline
const TransformPtr &SceneBase::getRootCore(void) const
{
    return _sfRootCore.getValue();
}

//! Set the value of the Scene::_sfRootCore field.
inline
void SceneBase::setRootCore(const TransformPtr &value)
{
    _sfRootCore.setValue(value);
}

//! Get the value of the Scene::_sfDefaultCameraBeacon field.
inline
NodePtr &SceneBase::editDefaultCameraBeacon(void)
{
    return _sfDefaultCameraBeacon.getValue();
}

//! Get the value of the Scene::_sfDefaultCameraBeacon field.
inline
const NodePtr &SceneBase::getDefaultCameraBeacon(void) const
{
    return _sfDefaultCameraBeacon.getValue();
}

//! Set the value of the Scene::_sfDefaultCameraBeacon field.
inline
void SceneBase::setDefaultCameraBeacon(const NodePtr &value)
{
    _sfDefaultCameraBeacon.setValue(value);
}

//! Get the value of the Scene::_sfDefaultCameraBeaconCore field.
inline
TransformPtr &SceneBase::editDefaultCameraBeaconCore(void)
{
    return _sfDefaultCameraBeaconCore.getValue();
}

//! Get the value of the Scene::_sfDefaultCameraBeaconCore field.
inline
const TransformPtr &SceneBase::getDefaultCameraBeaconCore(void) const
{
    return _sfDefaultCameraBeaconCore.getValue();
}

//! Set the value of the Scene::_sfDefaultCameraBeaconCore field.
inline
void SceneBase::setDefaultCameraBeaconCore(const TransformPtr &value)
{
    _sfDefaultCameraBeaconCore.setValue(value);
}

//! Get the value of the Scene::_sfInitialCamera field.
inline
CameraPtr &SceneBase::editInitialCamera(void)
{
    return _sfInitialCamera.getValue();
}

//! Get the value of the Scene::_sfInitialCamera field.
inline
const CameraPtr &SceneBase::getInitialCamera(void) const
{
    return _sfInitialCamera.getValue();
}

//! Set the value of the Scene::_sfInitialCamera field.
inline
void SceneBase::setInitialCamera(const CameraPtr &value)
{
    _sfInitialCamera.setValue(value);
}

//! Get the value of the Scene::_sfLuaModule field.
inline
Path &SceneBase::editLuaModule(void)
{
    return _sfLuaModule.getValue();
}

//! Get the value of the Scene::_sfLuaModule field.
inline
const Path &SceneBase::getLuaModule(void) const
{
    return _sfLuaModule.getValue();
}

//! Set the value of the Scene::_sfLuaModule field.
inline
void SceneBase::setLuaModule(const Path &value)
{
    _sfLuaModule.setValue(value);
}

//! Get the value of the Scene::_sfPhysicsHandler field.
inline
PhysicsHandlerPtr &SceneBase::editPhysicsHandler(void)
{
    return _sfPhysicsHandler.getValue();
}

//! Get the value of the Scene::_sfPhysicsHandler field.
inline
const PhysicsHandlerPtr &SceneBase::getPhysicsHandler(void) const
{
    return _sfPhysicsHandler.getValue();
}

//! Set the value of the Scene::_sfPhysicsHandler field.
inline
void SceneBase::setPhysicsHandler(const PhysicsHandlerPtr &value)
{
    _sfPhysicsHandler.setValue(value);
}

//! Get the value of the Scene::_sfPhysicsWorld field.
inline
PhysicsWorldPtr &SceneBase::editPhysicsWorld(void)
{
    return _sfPhysicsWorld.getValue();
}

//! Get the value of the Scene::_sfPhysicsWorld field.
inline
const PhysicsWorldPtr &SceneBase::getPhysicsWorld(void) const
{
    return _sfPhysicsWorld.getValue();
}

//! Set the value of the Scene::_sfPhysicsWorld field.
inline
void SceneBase::setPhysicsWorld(const PhysicsWorldPtr &value)
{
    _sfPhysicsWorld.setValue(value);
}

//! Get the value of the Scene::_sfGenericMethodIDs field.
inline
UInt32 &SceneBase::editGenericMethodIDs(void)
{
    return _sfGenericMethodIDs.getValue();
}

//! Get the value of the Scene::_sfGenericMethodIDs field.
inline
const UInt32 &SceneBase::getGenericMethodIDs(void) const
{
    return _sfGenericMethodIDs.getValue();
}

//! Set the value of the Scene::_sfGenericMethodIDs field.
inline
void SceneBase::setGenericMethodIDs(const UInt32 &value)
{
    _sfGenericMethodIDs.setValue(value);
}


//! Get the value of the \a index element the Scene::_mfViewports field.
inline
ViewportPtr &SceneBase::editViewports(const UInt32 index)
{
    return _mfViewports[index];
}

//! Get the value of the \a index element the Scene::_mfViewports field.
inline
const ViewportPtr &SceneBase::getViewports(const UInt32 index) const
{
    return _mfViewports[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfViewports field.
inline
MFViewportPtr &SceneBase::getViewports(void)
{
    return _mfViewports;
}

//! Get the Scene::_mfViewports field.
inline
const MFViewportPtr &SceneBase::getViewports(void) const
{
    return _mfViewports;
}

#endif
//! Get the value of the \a index element the Scene::_mfBackgrounds field.
inline
BackgroundPtr &SceneBase::editBackgrounds(const UInt32 index)
{
    return _mfBackgrounds[index];
}

//! Get the value of the \a index element the Scene::_mfBackgrounds field.
inline
const BackgroundPtr &SceneBase::getBackgrounds(const UInt32 index) const
{
    return _mfBackgrounds[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfBackgrounds field.
inline
MFBackgroundPtr &SceneBase::getBackgrounds(void)
{
    return _mfBackgrounds;
}

//! Get the Scene::_mfBackgrounds field.
inline
const MFBackgroundPtr &SceneBase::getBackgrounds(void) const
{
    return _mfBackgrounds;
}

#endif
//! Get the value of the \a index element the Scene::_mfUIDrawingSurfaces field.
inline
UIDrawingSurfacePtr &SceneBase::editUIDrawingSurfaces(const UInt32 index)
{
    return _mfUIDrawingSurfaces[index];
}

//! Get the value of the \a index element the Scene::_mfUIDrawingSurfaces field.
inline
const UIDrawingSurfacePtr &SceneBase::getUIDrawingSurfaces(const UInt32 index) const
{
    return _mfUIDrawingSurfaces[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfUIDrawingSurfaces field.
inline
MFUIDrawingSurfacePtr &SceneBase::getUIDrawingSurfaces(void)
{
    return _mfUIDrawingSurfaces;
}

//! Get the Scene::_mfUIDrawingSurfaces field.
inline
const MFUIDrawingSurfacePtr &SceneBase::getUIDrawingSurfaces(void) const
{
    return _mfUIDrawingSurfaces;
}

#endif
//! Get the value of the \a index element the Scene::_mfForegrounds field.
inline
ForegroundPtr &SceneBase::editForegrounds(const UInt32 index)
{
    return _mfForegrounds[index];
}

//! Get the value of the \a index element the Scene::_mfForegrounds field.
inline
const ForegroundPtr &SceneBase::getForegrounds(const UInt32 index) const
{
    return _mfForegrounds[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfForegrounds field.
inline
MFForegroundPtr &SceneBase::getForegrounds(void)
{
    return _mfForegrounds;
}

//! Get the Scene::_mfForegrounds field.
inline
const MFForegroundPtr &SceneBase::getForegrounds(void) const
{
    return _mfForegrounds;
}

#endif
//! Get the value of the \a index element the Scene::_mfInitialForegrounds field.
inline
ForegroundPtr &SceneBase::editInitialForegrounds(const UInt32 index)
{
    return _mfInitialForegrounds[index];
}

//! Get the value of the \a index element the Scene::_mfInitialForegrounds field.
inline
const ForegroundPtr &SceneBase::getInitialForegrounds(const UInt32 index) const
{
    return _mfInitialForegrounds[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfInitialForegrounds field.
inline
MFForegroundPtr &SceneBase::getInitialForegrounds(void)
{
    return _mfInitialForegrounds;
}

//! Get the Scene::_mfInitialForegrounds field.
inline
const MFForegroundPtr &SceneBase::getInitialForegrounds(void) const
{
    return _mfInitialForegrounds;
}

#endif
//! Get the value of the \a index element the Scene::_mfModelNodes field.
inline
NodePtr &SceneBase::editModelNodes(const UInt32 index)
{
    return _mfModelNodes[index];
}

//! Get the value of the \a index element the Scene::_mfModelNodes field.
inline
const NodePtr &SceneBase::getModelNodes(const UInt32 index) const
{
    return _mfModelNodes[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfModelNodes field.
inline
MFNodePtr &SceneBase::getModelNodes(void)
{
    return _mfModelNodes;
}

//! Get the Scene::_mfModelNodes field.
inline
const MFNodePtr &SceneBase::getModelNodes(void) const
{
    return _mfModelNodes;
}

#endif
//! Get the value of the \a index element the Scene::_mfInitialModelNodes field.
inline
NodePtr &SceneBase::editInitialModelNodes(const UInt32 index)
{
    return _mfInitialModelNodes[index];
}

//! Get the value of the \a index element the Scene::_mfInitialModelNodes field.
inline
const NodePtr &SceneBase::getInitialModelNodes(const UInt32 index) const
{
    return _mfInitialModelNodes[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfInitialModelNodes field.
inline
MFNodePtr &SceneBase::getInitialModelNodes(void)
{
    return _mfInitialModelNodes;
}

//! Get the Scene::_mfInitialModelNodes field.
inline
const MFNodePtr &SceneBase::getInitialModelNodes(void) const
{
    return _mfInitialModelNodes;
}

#endif
//! Get the value of the \a index element the Scene::_mfCameras field.
inline
CameraPtr &SceneBase::editCameras(const UInt32 index)
{
    return _mfCameras[index];
}

//! Get the value of the \a index element the Scene::_mfCameras field.
inline
const CameraPtr &SceneBase::getCameras(const UInt32 index) const
{
    return _mfCameras[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfCameras field.
inline
MFCameraPtr &SceneBase::getCameras(void)
{
    return _mfCameras;
}

//! Get the Scene::_mfCameras field.
inline
const MFCameraPtr &SceneBase::getCameras(void) const
{
    return _mfCameras;
}

#endif
//! Get the value of the \a index element the Scene::_mfAnimations field.
inline
AnimationPtr &SceneBase::editAnimations(const UInt32 index)
{
    return _mfAnimations[index];
}

//! Get the value of the \a index element the Scene::_mfAnimations field.
inline
const AnimationPtr &SceneBase::getAnimations(const UInt32 index) const
{
    return _mfAnimations[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfAnimations field.
inline
MFAnimationPtr &SceneBase::getAnimations(void)
{
    return _mfAnimations;
}

//! Get the Scene::_mfAnimations field.
inline
const MFAnimationPtr &SceneBase::getAnimations(void) const
{
    return _mfAnimations;
}

#endif
//! Get the value of the \a index element the Scene::_mfInitialAnimations field.
inline
AnimationPtr &SceneBase::editInitialAnimations(const UInt32 index)
{
    return _mfInitialAnimations[index];
}

//! Get the value of the \a index element the Scene::_mfInitialAnimations field.
inline
const AnimationPtr &SceneBase::getInitialAnimations(const UInt32 index) const
{
    return _mfInitialAnimations[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfInitialAnimations field.
inline
MFAnimationPtr &SceneBase::getInitialAnimations(void)
{
    return _mfInitialAnimations;
}

//! Get the Scene::_mfInitialAnimations field.
inline
const MFAnimationPtr &SceneBase::getInitialAnimations(void) const
{
    return _mfInitialAnimations;
}

#endif
//! Get the value of the \a index element the Scene::_mfParticleSystems field.
inline
ParticleSystemPtr &SceneBase::editParticleSystems(const UInt32 index)
{
    return _mfParticleSystems[index];
}

//! Get the value of the \a index element the Scene::_mfParticleSystems field.
inline
const ParticleSystemPtr &SceneBase::getParticleSystems(const UInt32 index) const
{
    return _mfParticleSystems[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfParticleSystems field.
inline
MFParticleSystemPtr &SceneBase::getParticleSystems(void)
{
    return _mfParticleSystems;
}

//! Get the Scene::_mfParticleSystems field.
inline
const MFParticleSystemPtr &SceneBase::getParticleSystems(void) const
{
    return _mfParticleSystems;
}

#endif
//! Get the value of the \a index element the Scene::_mfInitialParticleSystems field.
inline
ParticleSystemPtr &SceneBase::editInitialParticleSystems(const UInt32 index)
{
    return _mfInitialParticleSystems[index];
}

//! Get the value of the \a index element the Scene::_mfInitialParticleSystems field.
inline
const ParticleSystemPtr &SceneBase::getInitialParticleSystems(const UInt32 index) const
{
    return _mfInitialParticleSystems[index];
}

#ifndef OSG_2_PREP
//! Get the Scene::_mfInitialParticleSystems field.
inline
MFParticleSystemPtr &SceneBase::getInitialParticleSystems(void)
{
    return _mfInitialParticleSystems;
}

//! Get the Scene::_mfInitialParticleSystems field.
inline
const MFParticleSystemPtr &SceneBase::getInitialParticleSystems(void) const
{
    return _mfInitialParticleSystems;
}

#endif

inline
EventConnection SceneBase::attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId)
{
    return _Producer.attachActivity(TheActivity, ProducedEventId);
}

inline
bool SceneBase::isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const
{
    return _Producer.isActivityAttached(TheActivity, ProducedEventId);
}

inline
UInt32 SceneBase::getNumActivitiesAttached(UInt32 ProducedEventId) const
{
    return _Producer.getNumActivitiesAttached(ProducedEventId);
}

inline
ActivityPtr SceneBase::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    return _Producer.getAttachedActivity(ProducedEventId,ActivityIndex);
}

inline
void SceneBase::detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId)
{
    _Producer.detachActivity(TheActivity, ProducedEventId);
}

inline
UInt32 SceneBase::getNumProducedEvents(void) const
{
    return _Producer.getNumProducedEvents();
}

inline
const MethodDescription *SceneBase::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return _Producer.getProducedEventDescription(ProducedEventName);
}

inline
const MethodDescription *SceneBase::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return _Producer.getProducedEventDescription(ProducedEventId);
}

inline
UInt32 SceneBase::getProducedEventId(const Char8 *ProducedEventName) const
{
    return _Producer.getProducedEventId(ProducedEventName);
}

inline
SFEventProducerPtr *SceneBase::editSFEventProducer(void)
{
    return &_sfEventProducer;
}

//! Get the value of the Scene::_sfEventProducer field.
inline
EventProducerPtr &SceneBase::editEventProducer(void)
{
    return _sfEventProducer.getValue();
}

OSG_END_NAMESPACE
