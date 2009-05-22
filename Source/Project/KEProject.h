/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#include "KEConfig.h"

#include "KEProjectBase.h"

#include <OpenSG/Toolbox/OSGPathType.h>
#include <OpenSG/Input/OSGWindowEventProducerFields.h>
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGMouseMotionAdapter.h>
#include <OpenSG/Input/OSGKeyAdapter.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGNavigator.h>


OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

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
                         ::osg::UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      ::osg::UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	void start(void);

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
	
    /*=========================  PROTECTED  ===============================*/
  protected:
	  ViewportPtr createDefaultViewport(void) const;

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
                                  public MouseAdapter,
                                  public MouseMotionAdapter,
                                  public KeyAdapter
	{
	public:
		ProjectUpdateListener(ProjectPtr TheProject);

        virtual void update(const UpdateEvent& e);
        virtual void mousePressed(const MouseEvent& e);
        virtual void mouseReleased(const MouseEvent& e);
        virtual void mouseMoved(const MouseEvent& e);
        virtual void mouseDragged(const MouseEvent& e);
        virtual void keyPressed(const KeyEvent& e);
	protected :
		ProjectPtr _Project;
	};

    friend class ProjectUpdateListener;

	ProjectUpdateListener _ProjectUpdateListener;

    void update(const UpdateEvent& e);
    void mousePressed(const MouseEvent& e);
    void mouseReleased(const MouseEvent& e);
    void mouseMoved(const MouseEvent& e);
    void mouseDragged(const MouseEvent& e);
    void keyPressed(const KeyEvent& e);

    ElapsedTimeAnimationAdvancerPtr _AnimationAdvancer;
    Real32 _TimeInScene;
    bool _PauseActiveUpdates;
    bool _NavigatorAttached;
    Navigator _navigator;
    Pnt2f _MouseStartPos;
    Vec3f _RotationYAxis, _RotationXAxis;
    Real32 _MotionFactor;
    Matrix _RotationStartMat;

    void updateNavigatorSceneAttachment(void);
    void setCameraBeaconMatrix(const Matrix& m);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ProjectBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Project &source);
};

typedef Project *ProjectP;

KE_END_NAMESPACE

#include "KEProjectBase.inl"
#include "KEProject.inl"

#endif /* _KEPROJECT_H_ */
