
%module KabalaEngine
%import  <OSGBase.i>
%import  <OSGSystem.i>
%import  <OSGToolbox.i>
%{
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGActivity.h>
#include <OpenSG/OSGLuaActivity.h>
#include <OpenSG/OSGGenericEventDetails.h>
#include <boost/bind.hpp>
#include <OpenSG/OSGPathType.h>
#include "KELuaBindings.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

#include "Project/Effect/KEEffect.h"
#include "Player/KEApplicationPlayer.h"

#include "Project/SceneObject/KEBehaviorFactory.h"
#include "Project/SceneObject/KEBehavior.h"
#include "Project/SceneObject/KELuaBehavior.h"
#include "Project/SceneObject/KEBehaviorType.h"
#include "Project/SceneObject/KELuaBehaviorType.h"

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

std::string getKabalaEngineVersion(void);
std::string getKabalaEngineBuildType(void);
std::string getKabalaEngineBuildRepositoryRevision(void);

namespace OSG {
    class Scene;
    class Project;
    class Effect;
    class EffectRefPtr;
    class SceneObject;
    class ApplicationPlayer;
    class Behavior;
    class BehaviorFactory;
    class BehaviorType;
    class LuaBehaviorType;
    class Behavior;
    class BehaviorRefPtr;
    class LuaBehavior;
    
    
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
        
        UInt32 registerNewGenericEvent(const std::string& EventName,const std::string& EventDescriptionText = std::string(""));

        bool unregisterNewGenericEvent(UInt32 Id);
        bool unregisterNewGenericEvent(const std::string& EventName);

        bool isGenericEventDefined(UInt32 Id) const;
        bool isGenericEventDefined(const std::string& EventName) const;
        UInt32 getGenericEventId(const std::string& EventName) const;
    
      protected:
        Scene(void);
        Scene(const Scene &source);
        virtual ~Scene(void); 
    };
    %extend Scene
    {
        void produceGenericEvent(UInt32 GenericEventId, GenericEventDetailsRefPtr e)
        {
            self->produceGenericEvent(GenericEventId, e);
        }
    };
    

    /******************************************************/
    /*                  ProjectRefPtr                     */
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
    
        //void setActiveScene(SceneRefPtr TheScene);
        //SceneRefPtr getActiveScene(void) const;
    
        void pauseActiveUpdates(void);
        void unpauseActiveUpdates(void);
        void togglePauseActiveUpdates(void);
    
        SceneRefPtr getLastActiveScene(void) const;
      protected:
        Project(void);
        Project(const Project &source);
        virtual ~Project(void);
    };
    %extend Project
    {
        void setActiveScene(SceneRefPtr TheScene)
        {
            self->setActiveScene(TheScene);
        }
        
        SceneRefPtr getActiveScene(void) const
        {
            return self->getActiveScene();
        }
        void setActiveSceneOnEvent(SceneRefPtr TheScene,
                                   FieldContainerRefPtr EventProducer,
                                   UInt32 EventId)
        {
            self->setActiveSceneOnEvent(TheScene, EventProducer, EventId);
        }
        void setActiveSceneOnEvent(SceneRefPtr TheScene,
                                   FieldContainerRefPtr EventProducer,
                                   const std::string& EventName)
        {
            self->setActiveSceneOnEvent(TheScene, EventProducer, EventName);
        }
        
        WindowEventProducerRefPtr getEventProducer(void) const
        {
            return self->getEventProducer();
        }
    };
    
    /******************************************************/
    /*                    SceneObjectRefPtr               */
    /******************************************************/
    class SceneObjectRefPtr : public AttachmentContainerRefPtr
    {
      public:
         SceneObjectRefPtr(void);
         SceneObjectRefPtr(const SceneObjectRefPtr               &source);
         /*SceneObjectRefPtr(const NullFieldContainerRefPtr &source);*/
        
        ~SceneObjectRefPtr(void); 
        SceneObject *operator->(void);
        
    };
    %extend SceneObjectRefPtr
    {
        static SceneObjectRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::SceneObject>(oIn);
        }
    };
    
    /******************************************************/
    /*                     SceneObject                    */
    /******************************************************/
    class SceneObject : public AttachmentContainer
    {
      public:
    
        Effect* getEffect(std::string name);
        SceneRefPtr getParentScene () const;
    
      protected:
        SceneObject(void);
        SceneObject(const SceneObject &source);
        virtual ~SceneObject(void); 
    };
    %extend SceneObject
    {
        SceneRefPtr getParentScene () const
        {
            return self->getParentScene();
        }
        BehaviorRefPtr getBehaviors (UInt32 index)
        {
            return self->getBehaviors(index);
        }
    }

    
    /******************************************************/
    /*                   BehaviorType                     */
    /******************************************************/
    class BehaviorType : public TypeBase
    {
        public:

            UInt32 findEventID(std::string eventName);

        protected:
            BehaviorType(   const std::string &szName,
                    FieldContainerType * bBehaviorFieldContainerType,
                    std::vector<std::string> eventSourceNames = std::vector<std::string>(),
                    std::vector<std::string> bEvents = std::vector<std::string>(),
                    std::vector<std::string> bEventLinks = std::vector<std::string>());


            BehaviorType(const BehaviorType &source);
    };

    /******************************************************/
    /*				LuaBehaviorType                      */
    /******************************************************/
    class LuaBehaviorType : public BehaviorType
    {
        public:
            std::vector<std::string> getLuaFunctionNames();

            static LuaBehaviorType create(const std::string &szName,
                    const std::string &type,
                    const std::string &bEvents = "",
                    const std::string &bEventLinks = "",
                    const std::string &luaCallback = "",
                    const std::string &StrFilePath = "");

        protected:
            LuaBehaviorType(const std::string &szName,
                    FieldContainerType * bBehaviorFieldContainerType,
                    std::vector<std::string> eventSourceNames = std::vector<std::string>(),
                    std::vector<std::string> bEvents = std::vector<std::string>(),
                    std::vector<std::string> bEventLinks = std::vector<std::string>(),
                    std::vector<std::string> bLuaCallbacks = std::vector<std::string>(),
                    BoostPath& FilePath = BoostPath());
            LuaBehaviorType(const LuaBehaviorType &source);
            virtual ~LuaBehaviorType(void); 
    };
    
    /******************************************************/
    /*                 BehaviorFactory (Base?)            */
    /******************************************************/
    class BehaviorFactory
    {
        public :
            static BehaviorFactory *the(void);

        protected:
            BehaviorFactory(void);

            virtual ~BehaviorFactory(void);

    };
    %extend BehaviorFactory
    {
        UInt32    registerType      (      BehaviorType *pType          )
        {
            return OSG::BehaviorFactory::the()->registerType(pType);
        }

        UInt32    findTypeId        (const Char8    *szName)
        {
            return OSG::BehaviorFactory::the()->findTypeId(szName);
        }

        BehaviorType *findType      (      UInt32    uiTypeId       )
        {
            return OSG::BehaviorFactory::the()->findType(uiTypeId);
        }

        BehaviorType *findType      (const Char8    *szName)
        {
            return OSG::BehaviorFactory::the()->findType(szName);
        }

        OSG::BehaviorRefPtr     createBehavior(std::string Name)
        {
            return OSG::BehaviorFactory::the()->createBehavior(Name);
        }
    }
    
    /******************************************************/
    /*						Behavior                      */
    /******************************************************/
    class Behavior : public AttachmentContainer
    {
        public:
            BehaviorType * getBehaviorType(void);
        protected:
            Behavior(void);
            Behavior(const Behavior &source);
            virtual ~Behavior(void); 
    };
    %extend Behavior
    {
        SceneObjectRefPtr getParentSceneObject () const
        {
            return self->getParentSceneObject();
        }
        
         void produceEvent(std::string name, GenericEventDetailsRefPtr eventData = NULL)
        {
            self->produceEvent(name, eventData);
        }
        
        void produceEvent(UInt32 id, GenericEventDetailsRefPtr eventData = NULL)
        {
            self->produceEvent(id, eventData);
        } 
    };
    
    /******************************************************/
    /*                  BehaviorRefPtr                    */
    /******************************************************/
    class BehaviorRefPtr : public AttachmentContainerRefPtr
    {
      public:
         BehaviorRefPtr(void);
         BehaviorRefPtr(const BehaviorRefPtr               &source);

        ~BehaviorRefPtr(void); 
        Behavior *operator->(void);
        
    };
    %extend BehaviorRefPtr
    {
        static BehaviorRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Behavior>(oIn);
        }
    };
    
    /******************************************************/
    /*					 LuaBehavior                      */
    /******************************************************/
    class LuaBehavior : public Behavior
    {
        public:
            LuaBehaviorType * getLuaBehaviorType(void);

        protected:
            LuaBehavior(void);
            LuaBehavior(const LuaBehavior &source);
            virtual ~LuaBehavior(void); 
    };
    
    /******************************************************/
    /*                 LuaBehaviorRefPtr                  */
    /******************************************************/
    class LuaBehaviorRefPtr : public BehaviorRefPtr
    {
      public:
         LuaBehaviorRefPtr(void);
         LuaBehaviorRefPtr(const LuaBehaviorRefPtr               &source);

        ~LuaBehaviorRefPtr(void); 
        LuaBehavior *operator->(void);
        
    };
    %extend LuaBehaviorRefPtr
    {
        static LuaBehaviorRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::LuaBehavior>(oIn);
        }
    };
    
    /******************************************************/
    /*                   Effect                           */
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
        Effect(void);
        Effect(const Effect &source);
        virtual ~Effect(void); 
    };
    %extend Effect
    {
        SceneObjectRefPtr getParentSceneObject () const
        {
            return self->getParentSceneObject();
        }
    };
    
    /******************************************************/
    /*                    EffectRefPtr               */
    /******************************************************/
    class EffectRefPtr : public AttachmentContainerRefPtr
    {
      public:
         EffectRefPtr(void);
         EffectRefPtr(const EffectRefPtr               &source);
         /*EffectRefPtr(const NullFieldContainerRefPtr &source);*/
        
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
            dynamic_cast<OSG::ApplicationPlayer*>(OSG::MainApplication::the()->getPlayerMode())->openEditor(FCToEdit);
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
