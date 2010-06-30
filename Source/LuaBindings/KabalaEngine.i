
%module KabalaEngine
%import  <OSGBase.i>
%import  <OSGSystem.i>
%import  <OSGToolbox.i>
%{
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGActivity.h>
#include <OpenSG/OSGLuaActivity.h>
//#include <OpenSG/OSGGenericEvent.h>
//#include <OpenSG/OSGEventProducerType.h>
#include <boost/bind.hpp>
#include "KELuaBindings.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"
#include "Project/SceneObject/KEBehaviorFactory.h"
#include "Project/SceneObject/KEBehavior.h"
#include "Project/SceneObject/KEBehaviorType.h"

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
    class GenericEventUnrecPtr;
    
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
    class Scene : public SceneBase
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
    
        void produceGenericEvent(UInt32 GenericEventId, GenericEventUnrecPtr e);
    
      protected:
        Scene(void);
        Scene(const Scene &source);
        virtual ~Scene(void); 
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
        Project(const Animation &source);
        virtual ~Project(void); 
    };
    
    /******************************************************/
    /*                   BehaviorType                     */
    /******************************************************/
    class BehaviorType : public AttachmentContainer
    {
		public:
		
			UInt32 findEventID(std::string eventName);
			
			BehaviorType(const std::string &szName,
                 const std::string &szParentName = "",
				 std::vector<std::string> bEvents = std::vector<std::string>(),
				 std::vector<std::string> bEventLinks = std::vector<std::string>(),
			     BoostPath& FilePath = BoostPath());

			BehaviorType(const BehaviorType &source);
			
			std::string getName();
			const Char8* getChar8Name();
			
		protected:
			void registerType();
    };
    
    /******************************************************/
    /*                 BehaviorFactory                    */
    /******************************************************/
    class BehaviorFactoryBase : public AttachmentContainer
    {
		public:
		
			UInt32 registerType(BehaviorType *pType);
			UInt32    findTypeId(const Char8 *szName);

			BehaviorType *findType  (      UInt32    uiTypeId       );
			BehaviorType *findType  (const Char8    *szName         );
			OSG::BehaviorTransitPtr createBehavior(std::string Name);
			
		protected:
    };
    
    /******************************************************/
    /*                   SceneObject                      */
    /******************************************************/
    class SceneObject : public AttachmentContainer
    {
		public:
			const Scene* getParentScene () const;
			Scene* getParentScene ();

			OSG::BehaviorUnrecPtr getBehaviors (UInt32 index);

    };
    
    /******************************************************/
    /*						Behavior                      */
    /******************************************************/
    class Behavior : public AttachmentContainer
    {
		public:
    		BehaviorType * getBehaviorType(void);

			bool isInitialized();
	};
}

