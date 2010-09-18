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

#ifndef _KEPROJECT_H_
#define _KEPROJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KEProjectBase.h"
#include <OpenSG/OSGBackgroundFields.h>       // Backgrounds Class
#include <OpenSG/OSGForegroundFields.h>       // Foregrounds Class
#include <OpenSG/OSGNodeFields.h>             // ModelNodes Class
#include <OpenSG/OSGCameraFields.h>           // Cameras Class
#include <OpenSG/OSGAnimationFields.h>        // ActiveAnimations Class
#include <OpenSG/OSGParticleSystemFields.h>   // ActiveParticleSystems Class

#include <OpenSG/OSGPathType.h>
#include <OpenSG/OSGWindowEventProducerFields.h>
#include <OpenSG/OSGNavigator.h>

#include "KEProjectEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Project class. See \ref
           PageKabalaEngineProject for a description.
*/

class KE_KABALAENGINE_DLLMAPPING Project : public ProjectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ProjectBase Inherited;
    typedef Project     Self;

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

    void start(void);

    void reset(void);

    void stop(void);

    void setActiveScene(Scene* const TheScene);
    void setActiveSceneOnEvent(Scene* const TheScene,
                               ReflexiveContainer* EventProducer,
                               UInt32 EventId);
    void setActiveSceneOnEvent(Scene* const TheScene,
                               ReflexiveContainer* EventProducer,
                               const std::string& EventName);

    Scene* getActiveScene(void) const;

    void save(const BoostPath& ProjectFile);

    static ProjectRefPtr load(const BoostPath& ProjectFile);

    static ProjectRefPtr create(const BoostPath& ProjectFile);

    void save(void);

    WindowEventProducer* getEventProducer(void) const;

    void pauseActiveUpdates(void);
    void unpauseActiveUpdates(void);
    void togglePauseActiveUpdates(void);
    bool getPauseActiveUpdates(void) const;

    Scene* getLastActiveScene(void) const;
    Scene* getSceneByName(const std::string& FindSceneName) const;

    void blockInput(bool block);
    bool isInputBlocked(void) const;

    void addViewport(const ViewportRefPtr& port);
    void insertViewport(const ViewportRefPtr& port, UInt32 index);
    void removeViewport(const ViewportRefPtr& port);
    void clearViewports(void);
    UInt32 numViewports(void) const;
    Viewport* getViewport(UInt32 index) const;

    BoostPath getProjectFilePath(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ProjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Project(void);
    Project(const Project &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Project(void);

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

    
    void handleTriggeringSceneChangeEvent(EventDetails* const details,
                                          Scene* const scene);
    boost::signals2::connection _TriggeringSceneChangeEventConnection;

    bool _PauseActiveUpdates;

    SceneRefPtr _LastActiveScene;

    void produceSceneChanged(void);
    void produceProjectStarted(void);
    void produceProjectStopping(void);
    void produceProjectStopped(void);
    void produceProjectReset(void);

    void loadScripts(void);
    bool _BlockInput;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ProjectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Project &source);
};

typedef Project *ProjectP;

OSG_END_NAMESPACE

#include "Project/Scene/KEScene.h"      // Scenes Class
#include "KEProjectBase.inl"
#include "KEProject.inl"

#endif /* _KEPROJECT_H_ */
