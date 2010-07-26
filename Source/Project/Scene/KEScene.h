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
#include <OpenSG/OSGViewport.h>         // Viewports Class
#include <OpenSG/OSGBackground.h>       // Backgrounds Class
#include <OpenSG/OSGUIDrawingSurface.h> // UIDrawingSurfaces Class
#include <OpenSG/OSGForeground.h>       // Foregrounds Class
#include <OpenSG/OSGNode.h>             // ModelNodes Class
#include <OpenSG/OSGTransform.h>        // RootCore Class
#include <OpenSG/OSGCamera.h>           // Cameras Class
#include <OpenSG/OSGAnimation.h>        // Animations Class
#include <OpenSG/OSGParticleSystem.h>   // ParticleSystems Class
#include <OpenSG/OSGPhysicsHandler.h>   // PhysicsHandler Class
#include <OpenSG/OSGPhysicsWorld.h>     // PhysicsWorld Class

#include "KESceneEvent.h"
#include <OpenSG/OSGUpdateListener.h>
#include <OpenSG/OSGMouseListener.h>
#include <OpenSG/OSGMouseMotionListener.h>
#include <OpenSG/OSGMouseWheelListener.h>
#include <OpenSG/OSGKeyListener.h>
#include <OpenSG/OSGWindowListener.h>
#include <OpenSG/OSGGenericEvent.h>
#include "Project/SceneObject/KESceneObject.h"

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
	
	UInt32      registerNewGenericMethod(const std::string& MethodName,
                                    const std::string& MethodDescriptionText = std::string(""));

	bool        unregisterNewGenericMethod(UInt32 Id);
	bool        unregisterNewGenericMethod(const std::string& MethodName);

	bool        isGenericMethodDefined(      UInt32       Id        ) const;
	bool        isGenericMethodDefined(const std::string& MethodName) const;
	UInt32      getGenericMethodId    (const std::string& MethodName) const;
    std::string getGenericMethodName  (      UInt32       Id        ) const;
	void        addSceneObject        (	   	SceneObject* so		    );
	void        removeSceneObject     (		SceneObject* so		    );

	void        produceGenericEvent(UInt32 GenericEventId, GenericEventUnrecPtr e);
    void        produceGenericEvent(std::string GenericEventName, GenericEventUnrecPtr e);

	void        checkBehaviorInitialization();

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

    void enter(void);
    void exit(void);
    void start(void);
    void end(void);
    void reset(void);

    void createDefaults(void);
    void initDefaults(void);

    friend class Project;

    void attachNames(void);


    void producerSceneEntered(const SceneEventUnrecPtr e);
    void producerSceneExited(const SceneEventUnrecPtr e);
    void producerSceneStarted(const SceneEventUnrecPtr e);
    void producerSceneEnded(const SceneEventUnrecPtr e);
    void producerSceneReset(const SceneEventUnrecPtr e);

    class SceneUpdateListener : public UpdateListener,
                                public MouseListener,
                                public MouseMotionListener,
                                public MouseWheelListener,
                                public KeyListener,
                                public WindowListener
    {
      public:
        SceneUpdateListener(SceneRefPtr TheScene);

        virtual void update(const UpdateEventUnrecPtr e);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);

        virtual void mouseMoved(const MouseEventUnrecPtr e);
        virtual void mouseDragged(const MouseEventUnrecPtr e);

        virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);

        virtual void keyPressed(const KeyEventUnrecPtr e);
        virtual void keyReleased(const KeyEventUnrecPtr e);
        virtual void keyTyped(const KeyEventUnrecPtr e);

        virtual void windowOpened(const WindowEventUnrecPtr e);
        virtual void windowClosing(const WindowEventUnrecPtr e);
        virtual void windowClosed(const WindowEventUnrecPtr e);
        virtual void windowIconified(const WindowEventUnrecPtr e);
        virtual void windowDeiconified(const WindowEventUnrecPtr e);
        virtual void windowActivated(const WindowEventUnrecPtr e);
        virtual void windowDeactivated(const WindowEventUnrecPtr e);
        virtual void windowEntered(const WindowEventUnrecPtr e);
        virtual void windowExited(const WindowEventUnrecPtr e);
      protected :
        SceneRefPtr _Scene;
    };

    friend class SceneUpdateListener;

    SceneUpdateListener _SceneUpdateListener;

    bool _IsStarted;
    bool _BlockInput;

    UInt32 _GenericMethodIDCount;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Scene &source);
};

typedef Scene *SceneP;

OSG_END_NAMESPACE

#include "Project/KEProject.h"    // InternalParentProject Class
#include "KESceneBase.inl"
#include "KEScene.inl"

#endif /* _KESCENE_H_ */
