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

#ifndef _KEAPPLICATIONSTARTSCREEN_H_
#define _KEAPPLICATIONSTARTSCREEN_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEApplicationStartScreenBase.h"
#include <OpenSG/OSGForegroundFields.h>
#include <OpenSG/Input/OSGKeyAdapter.h>
#include <OpenSG/UserInterface/OSGActionListener.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurfaceFields.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Input/OSGUpdateListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationStartScreen class. See \ref 
           PageKabalaEngineApplicationStartScreen for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING ApplicationStartScreen : public ApplicationStartScreenBase
{
  private:

    typedef ApplicationStartScreenBase Inherited;

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
	virtual void attachApplication(void);
	virtual void dettachApplication(void);
	ForegroundPtr createInterface(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ApplicationStartScreenBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationStartScreen(void);
    ApplicationStartScreen(const ApplicationStartScreen &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationStartScreen(void); 

    /*! \}                                                                 */
    
	class StartScreenKeyListener : public KeyAdapter
	{
	public:
		StartScreenKeyListener(ApplicationStartScreenPtr TheApplicationStartScreen);

		virtual void keyTyped(const KeyEventPtr e);
	protected :
		ApplicationStartScreenPtr _ApplicationStartScreen;
	};

    friend class StartScreenKeyListener;

	StartScreenKeyListener _StartScreenKeyListener;

	//Builder ::osg::Button Action Listener
	class BuilderButtonActionListener : public ActionListener
	{
	public:
		BuilderButtonActionListener(ApplicationStartScreenPtr TheApplicationStartScreen);

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		ApplicationStartScreenPtr _ApplicationStartScreen;
	};

    friend class BuilderButtonActionListener;

	BuilderButtonActionListener _BuilderButtonActionListener;
	
	//Player ::osg::Button Action Listener
	class PlayerButtonActionListener : public ActionListener
	{
	public:
		PlayerButtonActionListener(ApplicationStartScreenPtr TheApplicationStartScreen);

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		ApplicationStartScreenPtr _ApplicationStartScreen;
	};

    friend class PlayerButtonActionListener;

	PlayerButtonActionListener _PlayerButtonActionListener;
	
	//Exit ::osg::Button Action Listener
	class ExitButtonActionListener : public ActionListener
	{
	public:
		ExitButtonActionListener(ApplicationStartScreenPtr TheApplicationStartScreen);

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		ApplicationStartScreenPtr _ApplicationStartScreen;
	};

    friend class ExitButtonActionListener;

	ExitButtonActionListener _ExitButtonActionListener;
    
	class ScreenUpdateListener : public UpdateListener
	{
	public:
		ScreenUpdateListener(ApplicationStartScreenPtr TheApplicationStartScreen);
        virtual void update(const UpdateEventPtr e);
	private:
		ApplicationStartScreenPtr _ApplicationStartScreen;
	};

	friend class ScreenUpdateListener;

	ScreenUpdateListener _ScreenUpdateListener;

    UIDrawingSurfacePtr _TheUIDrawingSurface;

    ElapsedTimeAnimationAdvancerPtr _AnimationAdvancer;
    FieldAnimationPtr _TorusAnimation;

    void updateAnimation(const Time& Elps);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ApplicationStartScreenBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ApplicationStartScreen &source);
};

typedef ApplicationStartScreen *ApplicationStartScreenP;

OSG_END_NAMESPACE

#include "KEApplicationStartScreenBase.inl"
#include "KEApplicationStartScreen.inl"

#endif /* _KEAPPLICATIONSTARTSCREEN_H_ */
