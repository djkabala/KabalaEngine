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
#include <OpenSG/OSGBackground.h>       // Backgrounds Class
#include <OpenSG/OSGForeground.h>       // Foregrounds Class
#include <OpenSG/OSGNode.h>             // ModelNodes Class
#include <OpenSG/OSGCamera.h>           // Cameras Class
#include <OpenSG/OSGAnimation.h>        // ActiveAnimations Class
#include <OpenSG/OSGParticleSystem.h>   // ActiveParticleSystems Class

#include <OpenSG/OSGPathType.h>
#include <OpenSG/OSGWindowEventProducerFields.h>
#include <OpenSG/OSGUpdateListener.h>
#include <OpenSG/OSGMouseListener.h>
#include <OpenSG/OSGMouseMotionListener.h>
#include <OpenSG/OSGMouseWheelListener.h>
#include <OpenSG/OSGKeyListener.h>
#include <OpenSG/OSGWindowListener.h>
#include <OpenSG/OSGNavigator.h>

#include "KEProjectEvent.h"

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

    void setActiveScene(SceneRefPtr TheScene);
    SceneRefPtr getActiveScene(void) const;

    void setActiveNode(NodeRefPtr TheNode);
    NodeRefPtr getActiveNode(void);

    void addActiveAnimation(AnimationRefPtr TheAnimation);
    void removeActiveAnimation(AnimationRefPtr TheAnimation);
    void addActiveParticleSystem(ParticleSystemRefPtr TheParticleSystem);
    void removeActiveParticleSystem(ParticleSystemRefPtr TheParticleSystem);

    void save(const BoostPath& ProjectFile);

    static ProjectRefPtr load(const BoostPath& ProjectFile);

    static ProjectRefPtr create(const BoostPath& ProjectFile);

    void save(void);

    void attachNames(void);

    WindowEventProducerRefPtr getEventProducer(void) const;

    void pauseActiveUpdates(void);
    void unpauseActiveUpdates(void);
    void togglePauseActiveUpdates(void);
    bool getPauseActiveUpdates(void) const;

    SceneRefPtr getLastActiveScene(void) const;
    SceneRefPtr getSceneByName(const std::string& FindSceneName) const;

    void blockInput(bool block);
    bool isInputBlocked(void) const;

    void addViewport(const ViewportRefPtr& port);
    void insertViewport(const ViewportRefPtr& port, UInt32 index);
    void removeViewport(const ViewportRefPtr& port);
    void clearViewports(void);
    UInt32 numViewports(void) const;
    ViewportRefPtr getViewport(UInt32 index) const;

    BoostPath getProjectFilePath(void) const;
    BoostPath getLuaModulePath(void) const;
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
    
	class ProjectUpdateListener : public UpdateListener,
                                  public MouseListener,
                                  public MouseMotionListener,
                                  public MouseWheelListener,
                                  public KeyListener,
                                  public WindowListener
    {
      public:
        ProjectUpdateListener(ProjectRefPtr TheProject);

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
        ProjectRefPtr _Project;
    };

    friend class ProjectUpdateListener;

    ProjectUpdateListener _ProjectUpdateListener;

    bool _PauseActiveUpdates;

    SceneRefPtr _LastActiveScene;

    void produceSceneChanged(const ProjectEventUnrecPtr e);
    void produceProjectStarted(const ProjectEventUnrecPtr e);
    void produceProjectStopping(const ProjectEventUnrecPtr e);
    void produceProjectStopped(const ProjectEventUnrecPtr e);
    void produceProjectReset(const ProjectEventUnrecPtr e);

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
