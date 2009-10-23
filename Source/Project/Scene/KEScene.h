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

#ifndef _KESCENE_H_
#define _KESCENE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KESceneBase.h"
#include "KESceneEvent.h"
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>
#include <OpenSG/Input/OSGMouseWheelListener.h>
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief Scene class. See \ref 
           PageKabalaEngineScene for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING Scene : public SceneBase
{
  private:

    typedef SceneBase Inherited;

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

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    bool isStarted(void) const;
    void blockInput(bool block);
    bool isInputBlocked(void) const;

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

	void enter(void);
	void exit(void);
	void start(void);
	void end(void);
	void reset(void);

	void createDefaults(void);
	void initDefaults(void);

	friend class Project;

	void attachNames(void);
    
    void producerSceneEntered(const SceneEventPtr e);
    void producerSceneExited(const SceneEventPtr e);
    void producerSceneStarted(const SceneEventPtr e);
    void producerSceneEnded(const SceneEventPtr e);
    void producerSceneReset(const SceneEventPtr e);
    
	class SceneUpdateListener : public UpdateListener,
                                  public MouseListener,
                                  public MouseMotionListener,
                                  public MouseWheelListener,
                                  public KeyListener,
                                  public WindowListener
	{
	public:
		SceneUpdateListener(ScenePtr TheScene);

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
		ScenePtr _Scene;
	};

    friend class SceneUpdateListener;

	SceneUpdateListener _SceneUpdateListener;
    
    bool _IsStarted;
    bool _BlockInput;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Scene &source);
};

typedef Scene *SceneP;

OSG_END_NAMESPACE

#include "KESceneBase.inl"
#include "KEScene.inl"

#endif /* _KESCENE_H_ */
