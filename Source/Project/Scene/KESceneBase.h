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
 **     class Scene
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _KESCENEBASE_H_
#define _KESCENEBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include <OpenSG/OSGAttachmentContainer.h> // Parent

#include <Project/KEProjectFields.h> // InternalParentProject type
#include <OpenSG/OSGStringFields.h> // Name type
#include <OpenSG/OSGBackgroundFields.h> // Backgrounds type
#include <OpenSG/UserInterface/OSGUIDrawingSurfaceFields.h> // UIDrawingSurfaces type
#include <OpenSG/OSGBackgroundFields.h> // InitialBackground type
#include <OpenSG/OSGForegroundFields.h> // Foregrounds type
#include <OpenSG/OSGForegroundFields.h> // InitialForegrounds type
#include <OpenSG/OSGNodeFields.h> // ModelNodes type
#include <OpenSG/OSGNodeFields.h> // InitialModelNodes type
#include <OpenSG/OSGNodeFields.h> // Root type
#include <OpenSG/OSGTransformFields.h> // RootCore type
#include <OpenSG/OSGNodeFields.h> // DefaultCameraBeacon type
#include <OpenSG/OSGTransformFields.h> // DefaultCameraBeaconCore type
#include <OpenSG/OSGCameraFields.h> // Cameras type
#include <OpenSG/OSGCameraFields.h> // InitialCamera type
#include <OpenSG/Animation/OSGAnimation.h> // Animations type
#include <OpenSG/Animation/OSGAnimation.h> // InitialAnimations type
#include <OpenSG/OSGReal32Fields.h> // TimeInScene type
#include <OpenSG/ParticleSystem/OSGParticleSystem.h> // ParticleSystems type
#include <OpenSG/ParticleSystem/OSGParticleSystem.h> // InitialParticleSystems type

#include "KESceneFields.h"
#include <OpenSG/Toolbox/OSGEventProducer.h>
#include <OpenSG/Toolbox/OSGEventProducerType.h>
#include <OpenSG/Toolbox/OSGMethodDescription.h>
#include <OpenSG/Toolbox/OSGEventProducerPtrType.h>

OSG_BEGIN_NAMESPACE

class Scene;
class BinaryDataHandler;

//! \brief Scene Base Class.

class KE_KABALAENGINELIB_DLLMAPPING SceneBase : public AttachmentContainer
{
  private:

    typedef AttachmentContainer    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef ScenePtr  Ptr;

    enum
    {
        InternalParentProjectFieldId   = Inherited::NextFieldId,
        NameFieldId                    = InternalParentProjectFieldId   + 1,
        BackgroundsFieldId             = NameFieldId                    + 1,
        UIDrawingSurfacesFieldId       = BackgroundsFieldId             + 1,
        InitialBackgroundFieldId       = UIDrawingSurfacesFieldId       + 1,
        ForegroundsFieldId             = InitialBackgroundFieldId       + 1,
        InitialForegroundsFieldId      = ForegroundsFieldId             + 1,
        ModelNodesFieldId              = InitialForegroundsFieldId      + 1,
        InitialModelNodesFieldId       = ModelNodesFieldId              + 1,
        RootFieldId                    = InitialModelNodesFieldId       + 1,
        RootCoreFieldId                = RootFieldId                    + 1,
        DefaultCameraBeaconFieldId     = RootCoreFieldId                + 1,
        DefaultCameraBeaconCoreFieldId = DefaultCameraBeaconFieldId     + 1,
        CamerasFieldId                 = DefaultCameraBeaconCoreFieldId + 1,
        InitialCameraFieldId           = CamerasFieldId                 + 1,
        AnimationsFieldId              = InitialCameraFieldId           + 1,
        InitialAnimationsFieldId       = AnimationsFieldId              + 1,
        TimeInSceneFieldId             = InitialAnimationsFieldId       + 1,
        ParticleSystemsFieldId         = TimeInSceneFieldId             + 1,
        InitialParticleSystemsFieldId  = ParticleSystemsFieldId         + 1,
        EventProducerFieldId           = InitialParticleSystemsFieldId  + 1,
        NextFieldId                    = EventProducerFieldId           + 1
    };

    static const OSG::BitVector InternalParentProjectFieldMask;
    static const OSG::BitVector NameFieldMask;
    static const OSG::BitVector BackgroundsFieldMask;
    static const OSG::BitVector UIDrawingSurfacesFieldMask;
    static const OSG::BitVector InitialBackgroundFieldMask;
    static const OSG::BitVector ForegroundsFieldMask;
    static const OSG::BitVector InitialForegroundsFieldMask;
    static const OSG::BitVector ModelNodesFieldMask;
    static const OSG::BitVector InitialModelNodesFieldMask;
    static const OSG::BitVector RootFieldMask;
    static const OSG::BitVector RootCoreFieldMask;
    static const OSG::BitVector DefaultCameraBeaconFieldMask;
    static const OSG::BitVector DefaultCameraBeaconCoreFieldMask;
    static const OSG::BitVector CamerasFieldMask;
    static const OSG::BitVector InitialCameraFieldMask;
    static const OSG::BitVector AnimationsFieldMask;
    static const OSG::BitVector InitialAnimationsFieldMask;
    static const OSG::BitVector TimeInSceneFieldMask;
    static const OSG::BitVector ParticleSystemsFieldMask;
    static const OSG::BitVector InitialParticleSystemsFieldMask;
    static const OSG::BitVector EventProducerFieldMask;


    enum
    {
        SceneEnteredMethodId = 1,
        SceneExitedMethodId  = SceneEnteredMethodId + 1,
        SceneStartedMethodId = SceneExitedMethodId  + 1,
        SceneEndedMethodId   = SceneStartedMethodId + 1,
        SceneResetMethodId   = SceneEndedMethodId   + 1,
        NextMethodId         = SceneResetMethodId   + 1
    };



    static const OSG::BitVector MTInfluenceMask;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static        FieldContainerType &getClassType    (void); 
    static        UInt32              getClassTypeId  (void); 
    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType  (void); 
    virtual const FieldContainerType &getType  (void) const; 

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


           SFString            *editSFName           (void);
     const SFString            *getSFName           (void) const;

           MFBackgroundPtr     *editMFBackgrounds    (void);
     const MFBackgroundPtr     *getMFBackgrounds    (void) const;

           MFUIDrawingSurfacePtr *editMFUIDrawingSurfaces(void);
     const MFUIDrawingSurfacePtr *getMFUIDrawingSurfaces(void) const;

           SFBackgroundPtr     *editSFInitialBackground(void);
     const SFBackgroundPtr     *getSFInitialBackground(void) const;

           MFForegroundPtr     *editMFForegrounds    (void);
     const MFForegroundPtr     *getMFForegrounds    (void) const;

           MFForegroundPtr     *editMFInitialForegrounds(void);
     const MFForegroundPtr     *getMFInitialForegrounds(void) const;

           MFNodePtr           *editMFModelNodes     (void);
     const MFNodePtr           *getMFModelNodes     (void) const;

           MFNodePtr           *editMFInitialModelNodes(void);
     const MFNodePtr           *getMFInitialModelNodes(void) const;

           MFCameraPtr         *editMFCameras        (void);
     const MFCameraPtr         *getMFCameras        (void) const;

           SFCameraPtr         *editSFInitialCamera  (void);
     const SFCameraPtr         *getSFInitialCamera  (void) const;

           MFAnimationPtr      *editMFAnimations     (void);
     const MFAnimationPtr      *getMFAnimations     (void) const;

           MFAnimationPtr      *editMFInitialAnimations(void);
     const MFAnimationPtr      *getMFInitialAnimations(void) const;

           SFReal32            *editSFTimeInScene    (void);
     const SFReal32            *getSFTimeInScene    (void) const;

           MFParticleSystemPtr *editMFParticleSystems(void);
     const MFParticleSystemPtr *getMFParticleSystems(void) const;

           MFParticleSystemPtr *editMFInitialParticleSystems(void);
     const MFParticleSystemPtr *getMFInitialParticleSystems(void) const;



           std::string         &editName           (void);
     const std::string         &getName           (void) const;

           BackgroundPtr       &editInitialBackground(void);
     const BackgroundPtr       &getInitialBackground(void) const;





           CameraPtr           &editInitialCamera  (void);
     const CameraPtr           &getInitialCamera  (void) const;

           Real32              &editTimeInScene    (void);
     const Real32              &getTimeInScene    (void) const;

           BackgroundPtr       &editBackgrounds    (const UInt32 index);
     const BackgroundPtr       &getBackgrounds    (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFBackgroundPtr     &getBackgrounds    (void);
     const MFBackgroundPtr     &getBackgrounds    (void) const;
#endif

           UIDrawingSurfacePtr &editUIDrawingSurfaces(const UInt32 index);
     const UIDrawingSurfacePtr &getUIDrawingSurfaces(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFUIDrawingSurfacePtr &getUIDrawingSurfaces(void);
     const MFUIDrawingSurfacePtr &getUIDrawingSurfaces(void) const;
#endif

           ForegroundPtr       &editForegrounds    (const UInt32 index);
     const ForegroundPtr       &getForegrounds    (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFForegroundPtr     &getForegrounds    (void);
     const MFForegroundPtr     &getForegrounds    (void) const;
#endif

           ForegroundPtr       &editInitialForegrounds(const UInt32 index);
     const ForegroundPtr       &getInitialForegrounds(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFForegroundPtr     &getInitialForegrounds(void);
     const MFForegroundPtr     &getInitialForegrounds(void) const;
#endif

           NodePtr             &editModelNodes     (const UInt32 index);
     const NodePtr             &getModelNodes     (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFNodePtr           &getModelNodes     (void);
     const MFNodePtr           &getModelNodes     (void) const;
#endif

           NodePtr             &editInitialModelNodes(const UInt32 index);
     const NodePtr             &getInitialModelNodes(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFNodePtr           &getInitialModelNodes(void);
     const MFNodePtr           &getInitialModelNodes(void) const;
#endif

           CameraPtr           &editCameras        (const UInt32 index);
     const CameraPtr           &getCameras        (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFCameraPtr         &getCameras        (void);
     const MFCameraPtr         &getCameras        (void) const;
#endif

           AnimationPtr        &editAnimations     (const UInt32 index);
     const AnimationPtr        &getAnimations     (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFAnimationPtr      &getAnimations     (void);
     const MFAnimationPtr      &getAnimations     (void) const;
#endif

           AnimationPtr        &editInitialAnimations(const UInt32 index);
     const AnimationPtr        &getInitialAnimations(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFAnimationPtr      &getInitialAnimations(void);
     const MFAnimationPtr      &getInitialAnimations(void) const;
#endif

           ParticleSystemPtr   &editParticleSystems(const UInt32 index);
     const ParticleSystemPtr   &getParticleSystems(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFParticleSystemPtr &getParticleSystems(void);
     const MFParticleSystemPtr &getParticleSystems(void) const;
#endif

           ParticleSystemPtr   &editInitialParticleSystems(const UInt32 index);
     const ParticleSystemPtr   &getInitialParticleSystems(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFParticleSystemPtr &getInitialParticleSystems(void);
     const MFParticleSystemPtr &getInitialParticleSystems(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setName           ( const std::string &value );
     void setInitialBackground( const BackgroundPtr &value );
     void setInitialCamera  ( const CameraPtr &value );
     void setTimeInScene    ( const Real32 &value );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Method Produced Get                           */
    /*! \{                                                                 */

    virtual const EventProducerType &getProducerType(void) const; 
    EventConnection attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);
    bool isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const;
    UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const;
    ActivityPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const;
    void detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);
    UInt32 getNumProducedEvents(void) const;
    const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const;
    const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;
    UInt32 getProducedEventId(const Char8 *ProducedEventName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (const BitVector         &whichField);
    virtual void   copyToBin  (      BinaryDataHandler &pMem,
                               const BitVector         &whichField);
    virtual void   copyFromBin(      BinaryDataHandler &pMem,
                               const BitVector         &whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ScenePtr      create          (void); 
    static  ScenePtr      createEmpty     (void); 

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr     shallowCopy     (void) const; 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    EventProducer _Producer;

    SFEventProducerPtr *editSFEventProducer(void);
    EventProducerPtr &editEventProducer(void);

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFProjectPtr        _sfInternalParentProject;
    SFString            _sfName;
    MFBackgroundPtr     _mfBackgrounds;
    MFUIDrawingSurfacePtr   _mfUIDrawingSurfaces;
    SFBackgroundPtr     _sfInitialBackground;
    MFForegroundPtr     _mfForegrounds;
    MFForegroundPtr     _mfInitialForegrounds;
    MFNodePtr           _mfModelNodes;
    MFNodePtr           _mfInitialModelNodes;
    SFNodePtr           _sfRoot;
    SFTransformPtr      _sfRootCore;
    SFNodePtr           _sfDefaultCameraBeacon;
    SFTransformPtr      _sfDefaultCameraBeaconCore;
    MFCameraPtr         _mfCameras;
    SFCameraPtr         _sfInitialCamera;
    MFAnimationPtr      _mfAnimations;
    MFAnimationPtr      _mfInitialAnimations;
    SFReal32            _sfTimeInScene;
    MFParticleSystemPtr   _mfParticleSystems;
    MFParticleSystemPtr   _mfInitialParticleSystems;

    /*! \}                                                                 */
    SFEventProducerPtr _sfEventProducer;
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SceneBase(void);
    SceneBase(const SceneBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

           SFProjectPtr        *editSFInternalParentProject(void);
     const SFProjectPtr        *getSFInternalParentProject(void) const;
           SFNodePtr           *editSFRoot           (void);
     const SFNodePtr           *getSFRoot           (void) const;
           SFTransformPtr      *editSFRootCore       (void);
     const SFTransformPtr      *getSFRootCore       (void) const;
           SFNodePtr           *editSFDefaultCameraBeacon(void);
     const SFNodePtr           *getSFDefaultCameraBeacon(void) const;
           SFTransformPtr      *editSFDefaultCameraBeaconCore(void);
     const SFTransformPtr      *getSFDefaultCameraBeaconCore(void) const;

           ProjectPtr          &editInternalParentProject(void);
     const ProjectPtr          &getInternalParentProject(void) const;
           NodePtr             &editRoot           (void);
     const NodePtr             &getRoot           (void) const;
           TransformPtr        &editRootCore       (void);
     const TransformPtr        &getRootCore       (void) const;
           NodePtr             &editDefaultCameraBeacon(void);
     const NodePtr             &getDefaultCameraBeacon(void) const;
           TransformPtr        &editDefaultCameraBeaconCore(void);
     const TransformPtr        &getDefaultCameraBeaconCore(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setInternalParentProject(const ProjectPtr &value);
     void setRoot           (const NodePtr &value);
     void setRootCore       (const TransformPtr &value);
     void setDefaultCameraBeacon(const NodePtr &value);
     void setDefaultCameraBeaconCore(const TransformPtr &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      SceneBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      SceneBase *pOther,
                         const BitVector         &whichField,
                         const SyncInfo          &sInfo     );

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField,
                               const SyncInfo          &sInfo);

    virtual void execBeginEdit     (const BitVector &whichField,
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

            void execBeginEditImpl (const BitVector &whichField,
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

    virtual void onDestroyAspect(UInt32 uiId, UInt32 uiAspect);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;

    static MethodDescription   *_methodDesc[];
    static EventProducerType _producerType;

    static FieldDescription   *_desc[];
    static FieldContainerType  _type;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef SceneBase *SceneBaseP;

typedef osgIF<SceneBase::isNodeCore,
              CoredNodePtr<Scene>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet SceneNodePtr;

typedef RefPtr<ScenePtr> SceneRefPtr;

OSG_END_NAMESPACE

#endif /* _KESCENEBASE_H_ */
