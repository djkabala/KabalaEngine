
%module KabalaEngine
%import  <OSGBase.i>
%import  <OSGSystem.i>
%import  <OSGToolbox.i>
%{
#include "KELuaBindings.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Animation/OSGAnimation.h>
#include <OpenSG/UserInterface/OSGComponent.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>


#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldDescription.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGAttachmentContainerPtr.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGImage.h>S
#include <OpenSG/OSGSysFieldDataType.h>
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGMathFieldDataType.h>
#include <OpenSG/OSGSFVecTypes.h>
#include <OpenSG/OSGSFMathTypes.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGMFMathTypes.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>
#include <OpenSG/Toolbox/OSGActivity.h>
#include <OpenSG/Toolbox/OSGEventProducerType.h>
#include <boost/bind.hpp>
%}

namespace osg {
    class Scene;
    class Project;
    
    /******************************************************/
    /*                    ScenePtr                        */
    /******************************************************/
    class ScenePtr : public AttachmentContainerPtr
    {
      public:
         ScenePtr(void);
         ScenePtr(const ScenePtr               &source);
         /*ScenePtr(const NullFieldContainerPtr &source);*/


        ~ScenePtr(void); 
        Scene *operator->(void);
        
        static ScenePtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                     Scene                          */
    /******************************************************/
    class Scene : public SceneBase
    {
      public:
    
        bool isStarted(void) const;
        void blockInput(bool block);
        bool isInputBlocked(void) const;
      protected:
        Scene(void);
        Scene(const Animation &source);
        virtual ~Scene(void); 
    };

    /******************************************************/
    /*                  ProjectPtr                        */
    /******************************************************/
    class ProjectPtr : public AttachmentContainerPtr
    {
      public:
         ProjectPtr(void);
         ProjectPtr(const ProjectPtr               &source);
         /*ProjectPtr(const NullFieldContainerPtr &source);*/


        ~ProjectPtr(void); 
        Project *operator->(void);
        
        static ProjectPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                    Project                         */
    /******************************************************/
    class Project : public AttachmentContainer
    {
      public:
    
        void start(void);
    
        void reset(void);
    
        void stop(void);
    
        void setActiveScene(ScenePtr TheScene);
        ScenePtr getActiveScene(void) const;
    
        //void setActiveBackground(BackgroundPtr TheBackground);
    
        void setActiveCamera(CameraPtr TheCamera);
    
        //MFForegroundPtr &getActiveForegrounds(void);
    
        void setActiveNode(NodePtr TheNode);
        
        void addActiveAnimation(AnimationPtr TheAnimation);
        void removeActiveAnimation(AnimationPtr TheAnimation);
        void addActiveParticleSystem(ParticleSystemPtr TheParticleSystem);
        void removeActiveParticleSystem(ParticleSystemPtr TheParticleSystem);
    
        //void save(const Path& ProjectFile);
    
        //static ProjectPtr load(const Path& ProjectFile);
    
        //static ProjectPtr create(const Path& ProjectFile);
    
        //void save(void);
    
        //void attachNames(void);
    
        WindowEventProducerPtr getEventProducer(void) const;
    
        void pauseActiveUpdates(void);
        void unpauseActiveUpdates(void);
        void togglePauseActiveUpdates(void);
    
        void attachFlyNavigation(void);
        void dettachFlyNavigation(void);
        void toggleFlyNavigation(void);
    
        ScenePtr getLastActiveScene(void) const;
      protected:
        Project(void);
        Project(const Animation &source);
        virtual ~Project(void); 
    };
    
}

