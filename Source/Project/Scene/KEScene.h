/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com), Robert Goetz               *
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

#ifndef _KESCENE_H_
#define _KESCENE_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneBase.h"
#include <OpenSG/OSGViewportFields.h>         // Viewports Class
#include <OpenSG/OSGBackgroundFields.h>       // Backgrounds Class
#include <OpenSG/OSGUIDrawingSurfaceFields.h> // UIDrawingSurfaces Class
#include <OpenSG/OSGForegroundFields.h>       // Foregrounds Class
#include <OpenSG/OSGNodeFields.h>             // ModelNodes Class
#include <OpenSG/OSGTransformFields.h>        // RootCore Class
#include <OpenSG/OSGCameraFields.h>           // Cameras Class
#include <OpenSG/OSGAnimationFields.h>        // Animations Class
#include <OpenSG/OSGParticleSystemFields.h>   // ParticleSystems Class
#include <OpenSG/OSGPhysicsHandlerFields.h>   // PhysicsHandler Class
#include <OpenSG/OSGPhysicsWorldFields.h>     // PhysicsWorld Class

#include "KESceneEventDetailsFields.h"
#include <OpenSG/OSGGenericEventDetailsFields.h>
#include "Project/SceneObject/KESceneObjectFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Scene class. See \ref
           PageKabalaEngineScene for a description.
*/

class KE_KABALAENGINE_DLLMAPPING Scene : public SceneBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneBase Inherited;
    typedef Scene     Self;
    typedef GenericEventDetails GenericEventDetailsType;
    typedef boost::signals2::signal<void (GenericEventDetails* const, UInt32), ConsumableEventCombiner> GenericEventSignalType;
    typedef std::map<UInt32, boost::shared_ptr<GenericEventSignalType> > GenericEventSignalMap;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    bool        isStarted(void) const;
    void        blockInput(bool block);
    bool        isInputBlocked(void) const;
	
	UInt32      registerNewGenericEvent(const std::string& EventName,
                                         const std::string& EventDescriptionText = std::string(""));

	bool        unregisterNewGenericEvent(UInt32 Id);
	bool        unregisterNewGenericEvent(const std::string& EventName);

	bool        isGenericEventDefined(      UInt32       Id        ) const;
	bool        isGenericEventDefined(const std::string& EventName) const;
	UInt32      getGenericEventId    (const std::string& EventName) const;
    std::string getGenericEventName  (      UInt32       Id        ) const;
	void        addSceneObject        (	   	SceneObject* so		    );
	void        removeSceneObject     (		SceneObject* so		    );

	void        produceGenericEvent(UInt32 GenericEventId, GenericEventDetails* const e);
    void        produceGenericEvent(std::string GenericEventName, GenericEventDetails* const e);

    boost::signals2::connection connectGenericEvent(UInt32 genericEventId, 
                                                    const BaseEventType::slot_type &listener,
                                                    boost::signals2::connect_position at= boost::signals2::at_back);

    boost::signals2::connection connectGenericEvent(UInt32 genericEventId, 
                                                    const BaseEventType::group_type &group,
                                                    const BaseEventType::slot_type &listener,
                                                    boost::signals2::connect_position at= boost::signals2::at_back);
    
    virtual boost::signals2::connection connectEvent(UInt32 eventId, 
                                              const BaseEventType::slot_type &listener,
                                              boost::signals2::connect_position at= boost::signals2::at_back);
                                              
    virtual boost::signals2::connection connectEvent(UInt32 eventId, 
                                              const BaseEventType::group_type &group,
                                              const BaseEventType::slot_type &listener,
                                              boost::signals2::connect_position at= boost::signals2::at_back);
    
    virtual void   disconnectEvent        (UInt32 eventId, const BaseEventType::group_type &group);
    virtual void   disconnectAllSlotsEvent(UInt32 eventId);
    virtual bool   isEmptyEvent           (UInt32 eventId) const;
    virtual UInt32 numSlotsEvent          (UInt32 eventId) const;

	void        checkBehaviorInitialization();

    Project* getParentProject(void) const;

    Viewport* getPrimaryViewport(void) const;

    SceneObject* findParentSceneObject(Node* const SceneNode) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Scene(void);
    Scene(const Scene &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Scene(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    void enter(void);
    void exit(void);
    void start(void);
    void end(void);
    void reset(void);

    void createDefaults(void);

    friend class Project;

    void produceSceneEntered(void);
    void produceSceneExited(void);
    void produceSceneStarted(void);
    void produceSceneEnded(void);
    void produceSceneReset(void);


    void handleUpdate(UpdateEventDetails* const details);

    void handleMouseClicked(MouseEventDetails* const details);
    void handleMouseEntered(MouseEventDetails* const details);
    void handleMouseExited(MouseEventDetails* const details);
    void handleMousePressed(MouseEventDetails* const details);
    void handleMouseReleased(MouseEventDetails* const details);

    void handleMouseMoved(MouseEventDetails* const details);
    void handleMouseDragged(MouseEventDetails* const details);

    void handleMouseWheelMoved(MouseWheelEventDetails* const details);

    void handleKeyPressed(KeyEventDetails* const details);
    void handleKeyReleased(KeyEventDetails* const details);
    void handleKeyTyped(KeyEventDetails* const details);

    void handleWindowOpened(WindowEventDetails* const details);
    void handleWindowClosing(WindowEventDetails* const details);
    void handleWindowClosed(WindowEventDetails* const details);
    void handleWindowIconified(WindowEventDetails* const details);
    void handleWindowDeiconified(WindowEventDetails* const details);
    void handleWindowActivated(WindowEventDetails* const details);
    void handleWindowDeactivated(WindowEventDetails* const details);
    void handleWindowEntered(WindowEventDetails* const details);
    void handleWindowExited(WindowEventDetails* const details);
    boost::signals2::connection _UpdateConnection,
                                _MouseClickedConnection,
                                _MouseEnteredConnection,
                                _MouseExitedConnection,
                                _MousePressedConnection,
                                _MouseReleasedConnection,
                                _MouseMovedConnection,
                                _MouseDraggedConnection,
                                _MouseWheelMovedConnection,
                                _KeyPressedConnection,
                                _KeyReleasedConnection,
                                _KeyTypedConnection,
                                _WindowOpenedConnection,
                                _WindowClosingConnection,
                                _WindowClosedConnection,
                                _WindowIconifiedConnection,
                                _WindowDeiconifiedConnection,
                                _WindowActivatedConnection,
                                _WindowDeactivatedConnection,
                                _WindowEnteredConnection,
                                _WindowExitedConnection;

    bool _IsStarted;
    bool _BlockInput;

    GenericEventSignalMap _GenericEventSignalMap;
    UInt32 _GenericEventIDCount;

    void loadLuaModule(void);

    void attachViewports(void);
    void attachUIDrawingSurfaces(void);
    void attachPhysics(void);
    void attachInitialAnimations(void);
    void attachInitialParticleSystems(void);

    void detachViewports(void);
    void detachUIDrawingSurfaces(void);
    void detachPhysics(void);
    void detachInitialAnimations(void);
    void detachInitialParticleSystems(void);

    void disconnectAllEvents(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Scene &source);
};

typedef Scene *SceneP;

OSG_END_NAMESPACE

#include <OpenSG/OSGUIDrawingSurface.h>
#include <OpenSG/OSGAnimation.h>
#include <OpenSG/OSGParticleSystem.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPhysicsWorld.h>
#include <OpenSG/OSGPhysicsHandler.h>
#include "Project/KEProject.h"
#include "Project/SceneObject/KESceneObject.h"
#include "Project/KEAssetStore.h"

#include "KESceneBase.inl"
#include "KEScene.inl"

#endif /* _KESCENE_H_ */
