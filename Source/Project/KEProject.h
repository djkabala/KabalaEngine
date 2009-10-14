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

#ifndef _KEPROJECT_H_
#define _KEPROJECT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEProjectBase.h"
#include "KEProjectEvent.h"

#include <OpenSG/Toolbox/OSGPathType.h>
#include <OpenSG/Input/OSGWindowEventProducerFields.h>
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>
#include <OpenSG/Input/OSGMouseWheelListener.h>
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowListener.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGNavigator.h>

OSG_BEGIN_NAMESPACE

/*! \brief Project class. See \ref 
           PageKabalaEngineProject for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING Project : public ProjectBase
{
  private:

    typedef ProjectBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent, 
                      const BitVector  bvFlags ) const;

    /*! \}                                                                 */

	void start(void);

	void reset(void);

	void stop(void);

	void setActiveScene(ScenePtr TheScene);
	ScenePtr getActiveScene(void) const;

	void setActiveBackground(BackgroundPtr TheBackground);

	void setActiveCamera(CameraPtr TheCamera);

	MFForegroundPtr &getActiveForegrounds(void);

	void setActiveNode(NodePtr TheNode);
    
	void addActiveAnimation(AnimationPtr TheAnimation);
	void removeActiveAnimation(AnimationPtr TheAnimation);
	void addActiveParticleSystem(ParticleSystemPtr TheParticleSystem);
	void removeActiveParticleSystem(ParticleSystemPtr TheParticleSystem);

	void save(const Path& ProjectFile);

	static ProjectPtr load(const Path& ProjectFile);

	static ProjectPtr create(const Path& ProjectFile);

	void save(void);

	void attachNames(void);

	WindowEventProducerPtr getEventProducer(void) const;

    void pauseActiveUpdates(void);
    void unpauseActiveUpdates(void);
    void togglePauseActiveUpdates(void);

    void attachFlyNavigation(void);
    void dettachFlyNavigation(void);
    void toggleFlyNavigation(void);

    ScenePtr getLastActiveScene(void) const;
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
    
    
	class ProjectUpdateListener : public UpdateListener,
                                  public MouseListener,
                                  public MouseMotionListener,
                                  public MouseWheelListener,
                                  public KeyListener,
                                  public WindowListener
	{
	public:
		ProjectUpdateListener(ProjectPtr TheProject);

        virtual void update(const UpdateEventPtr e);
        
        virtual void mouseClicked(const MouseEventPtr e);
        virtual void mouseEntered(const MouseEventPtr e);
        virtual void mouseExited(const MouseEventPtr e);
        virtual void mousePressed(const MouseEventPtr e);
        virtual void mouseReleased(const MouseEventPtr e);

        virtual void mouseMoved(const MouseEventPtr e);
        virtual void mouseDragged(const MouseEventPtr e);
        
        virtual void mouseWheelMoved(const MouseWheelEventPtr e);
        
        virtual void keyPressed(const KeyEventPtr e);
        virtual void keyReleased(const KeyEventPtr e);
        virtual void keyTyped(const KeyEventPtr e);
        
        virtual void windowOpened(const WindowEventPtr e);
        virtual void windowClosing(const WindowEventPtr e);
        virtual void windowClosed(const WindowEventPtr e);
        virtual void windowIconified(const WindowEventPtr e);
        virtual void windowDeiconified(const WindowEventPtr e);
        virtual void windowActivated(const WindowEventPtr e);
        virtual void windowDeactivated(const WindowEventPtr e);
        virtual void windowEntered(const WindowEventPtr e);
        virtual void windowExited(const WindowEventPtr e);
	protected :
		ProjectPtr _Project;
	};

    friend class ProjectUpdateListener;

	ProjectUpdateListener _ProjectUpdateListener;

    void update(const UpdateEventPtr e);
    void mousePressed(const MouseEventPtr e);
    void mouseReleased(const MouseEventPtr e);
    void mouseMoved(const MouseEventPtr e);
    void mouseDragged(const MouseEventPtr e);
    void keyPressed(const KeyEventPtr e);
    void keyReleased(const KeyEventPtr e);

    ElapsedTimeAnimationAdvancerPtr _AnimationAdvancer;
    bool _PauseActiveUpdates;
    bool _NavigatorAttached;
    Navigator _navigator;
    Real32 _ScaledMotionFactor;
    Real32 _MotionFactor;
    Real32 _FastMotionFactor;
    Real32 _FastRotMotionFactor;
    Real32 _YRotMotionFactor;
    Real32 _XRotMotionFactor;
    
    bool _IsAKeyDown;
    bool _IsSKeyDown;
    bool _IsDKeyDown;
    bool _IsWKeyDown;
    bool _IsShiftKeyDown;

    ScenePtr _LastActiveScene;

    void updateNavigatorSceneAttachment(void);
    void setCameraBeaconMatrix(const Matrix& m);
    ViewportPtr createDefaultViewport(void) const;

    void produceSceneChanged(const ProjectEventPtr e);
    void produceProjectStarted(const ProjectEventPtr e);
    void produceProjectStopping(const ProjectEventPtr e);
    void produceProjectStopped(const ProjectEventPtr e);
    void produceProjectReset(const ProjectEventPtr e);
    
    void loadScripts(void);

    /*==========================  PRIVATE  ================================*/
  private:
    void setDefaults(void);

    friend class FieldContainer;
    friend class ProjectBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Project &source);
};

typedef Project *ProjectP;

OSG_END_NAMESPACE

#include "KEProjectBase.inl"
#include "KEProject.inl"

#endif /* _KEPROJECT_H_ */
