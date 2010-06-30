
%module KabalaEngine
%import  <OSGBase.i>
%import  <OSGSystem.i>
%import  <OSGToolbox.i>
%{
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGActivity.h>
#include <OpenSG/OSGLuaActivity.h>
#include <OpenSG/OSGGenericEvent.h>
#include <OpenSG/OSGEventProducerType.h>
#include <boost/bind.hpp>
#include "KELuaBindings.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"
#include "Project/Effect/KEEffect.h"
#include "Player/KEApplicationPlayer.h"

//#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGSound.h>
#include <OpenSG/OSGSoundGroup.h>
#include <OpenSG/OSGSoundManager.h>
#include <OpenSG/OSGAnimation.h>
#include <OpenSG/OSGComponent.h>
#include <OpenSG/OSGParticleSystem.h>
#include <OpenSG/OSGDistribution1D.h>
#include <OpenSG/OSGDistribution1D.h>
#include <OpenSG/OSGDistribution2D.h>
#include <OpenSG/OSGDistribution3D.h>

#include <OpenSG/OSGPhysicsHandler.h>
#include <OpenSG/OSGPhysicsBody.h>
#include <OpenSG/OSGPhysicsSpace.h>
#include <OpenSG/OSGPhysicsWorld.h>

#include <OpenSG/OSGVideoWrapper.h>
#include <OpenSG/OSGVideoManager.h>
%}

namespace OSG {
    class Scene;
    class Project;
    class Effect;
    class ApplicationPlayer;
    
    /******************************************************/
    /*                    SceneRefPtr                        */
    /******************************************************/
    class SceneRefPtr : public AttachmentContainerRefPtr
    {
      public:
         SceneRefPtr(void);
         SceneRefPtr(const SceneRefPtr               &source);
         /*SceneRefPtr(const NullFieldContainerRefPtr &source);*/


        ~SceneRefPtr(void); 
        Scene *operator->(void);
        
    };
    %extend SceneRefPtr
    {
        static SceneRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Scene>(oIn);
        }
    };
    
    /******************************************************/
    /*                     Scene                          */
    /******************************************************/
    class Scene
    {
      public:
    
        bool isStarted(void) const;
        void blockInput(bool block);
        bool isInputBlocked(void) const;
        
        UInt32 registerNewGenericMethod(const std::string& MethodName,const std::string& MethodDescriptionText = std::string(""));

        bool unregisterNewGenericMethod(UInt32 Id);
        bool unregisterNewGenericMethod(const std::string& MethodName);

        bool isGenericMethodDefined(UInt32 Id) const;
        bool isGenericMethodDefined(const std::string& MethodName) const;
        UInt32 getGenericMethodId(const std::string& MethodName) const;
    
      protected:
        Scene(void);
        Scene(const Scene &source);
        virtual ~Scene(void); 
    };
    %extend Scene
    {
        void produceGenericEvent(UInt32 GenericEventId, GenericEventRefPtr e)
        {
            self->produceGenericEvent(GenericEventId, e);
        }
    };
    

    /******************************************************/
    /*                  ProjectRefPtr                        */
    /******************************************************/
    class ProjectRefPtr : public AttachmentContainerRefPtr
    {
      public:
         ProjectRefPtr(void);
         ProjectRefPtr(const ProjectRefPtr               &source);
         /*ProjectRefPtr(const NullFieldContainerRefPtr &source);*/


        ~ProjectRefPtr(void); 
        Project *operator->(void);
        
    };
    %extend ProjectRefPtr
    {
        static ProjectRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Project>(oIn);
        }
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
    
        void setActiveScene(SceneRefPtr TheScene);
        SceneRefPtr getActiveScene(void) const;
    
        void setActiveNode(NodeRefPtr TheNode);
        
        void addActiveAnimation(AnimationRefPtr TheAnimation);
        void removeActiveAnimation(AnimationRefPtr TheAnimation);
        void addActiveParticleSystem(ParticleSystemRefPtr TheParticleSystem);
        void removeActiveParticleSystem(ParticleSystemRefPtr TheParticleSystem);
    
        //void save(const BoostPath& ProjectFile);
    
        //static ProjectRefPtr load(const BoostPath& ProjectFile);
    
        //static ProjectRefPtr create(const BoostPath& ProjectFile);
    
        //void save(void);
    
        //void attachNames(void);
    
        WindowEventProducerRefPtr getEventProducer(void) const;
    
        void pauseActiveUpdates(void);
        void unpauseActiveUpdates(void);
        void togglePauseActiveUpdates(void);
    
        SceneRefPtr getLastActiveScene(void) const;
      protected:
        Project(void);
        Project(const Project &source);
        virtual ~Project(void); 
    };
    
    /******************************************************/
    /*                  EffectRefPtr                        */
    /******************************************************/
    class EffectRefPtr : public AttachmentContainerRefPtr
    {
      public:
         EffectRefPtr(void);
         EffectRefPtr(const EffectRefPtr               &source);
         /*ProjectRefPtr(const NullFieldContainerRefPtr &source);*/


        ~EffectRefPtr(void); 
        Effect *operator->(void);
        
    };
    %extend EffectRefPtr
    {
        static EffectRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Effect>(oIn);
        }
    };
    
    /******************************************************/
    /*                    Effect                         */
    /******************************************************/
    class Effect : public AttachmentContainer
    {
      public:
        void begin(void);
        bool isPlaying(void);
        bool isPaused(void);
        void pause(void);
        void unpause(void);
        void stop(void);
      protected:
        Project(void);
        Project(const Animation &source);
        virtual ~Project(void); 
    };
    
    /******************************************************/
    /*                     ApplicationPlayer                          */
    /******************************************************/
    class ApplicationPlayer
    {
      public:
    
      protected:
        ApplicationPlayer(void);
        ApplicationPlayer(const ApplicationPlayer &source);
        virtual ~ApplicationPlayer(void); 
    };
    %extend ApplicationPlayer
    {
        //void openEditor(FieldContainerRefPtr FCToEdit)
        //{
        //    self->openEditor(FCToEdit);
        //}
        static void openEditor(FieldContainerRefPtr FCToEdit)
        {
            OSG::dynamic_pointer_cast<OSG::ApplicationPlayer>(OSG::MainApplication::the()->getPlayerMode())->openEditor(FCToEdit);
        }
    };
    
    /******************************************************/
    /*                    ApplicationPlayerRefPtr                        */
    /******************************************************/
    // class ApplicationPlayerRefPtr : public AttachmentContainerRefPtr
    //{
    //  public:
    //     ApplicationPlayerRefPtr(void);
    //     ApplicationPlayerRefPtr(const ApplicationPlayerRefPtr               &source);
    //     /*ApplicationPlayerRefPtr(const NullFieldContainerRefPtr &source);*/


     //   ~ApplicationPlayerRefPtr(void); 
    //    ApplicationPlayer *operator->(void);
    //    
    //};
    //%extend ApplicationPlayerRefPtr
    //{
    //    static ApplicationPlayerRefPtr dcast(const FieldContainerRefPtr oIn)
    //    {
    //        return OSG::dynamic_pointer_cast<OSG::ApplicationPlayer>(oIn);
    //    }
    //};
}

