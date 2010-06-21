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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _KEBEHAVIOR_H_
#define _KEBEHAVIOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEBehaviorBase.h"

#include <Project/Scene/KESceneFields.h>
#include <Project/SceneObject/KESceneObject.h>
#include <OpenSG/OSGGenericEvent.h>
#include <OpenSG/OSGEvent.h>
#include <OpenSG/OSGEventListener.h>
#include "KEBehaviorType.h"

OSG_BEGIN_NAMESPACE

/*! \brief Behavior class. See \ref
           PageKabalaEngineBehavior for a description.
*/

class KE_KABALAENGINE_DLLMAPPING Behavior : public BehaviorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:


    typedef BehaviorBase Inherited;
    typedef Behavior     Self;


	void addedToSceneObject(SceneObjectUnrecPtr rootSceneObject);


	bool initialized;
	bool isInitialized();

	BehaviorType getBehaviorType(void);

	BehaviorType *TheBehaviorType;


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
    /*=========================  PROTECTED  ===============================*/

  protected:
	
	virtual void depBehaviorProducedMethod(EventUnrecPtr e, UInt32 ID);

	void initialize(SceneObjectUnrecPtr rootSceneObject);
	void setupDependency(BehaviorUnrecPtr behavior);
	void setupDependant(BehaviorUnrecPtr behavior);

    // Variables should all be in BehaviorBase.

    class DepBehaviorListener : public EventListener
	{
		public:
			
			DepBehaviorListener(BehaviorUnrecPtr TheBehavior);

			virtual void eventProduced(const EventUnrecPtr e);

		protected :
			BehaviorRecPtr _Behavior;
	};

	DepBehaviorListener		_DepBehaviorListener;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Behavior(void);
    Behavior(const Behavior &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Behavior(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BehaviorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Behavior &source);
};

typedef Behavior *BehaviorP;

OSG_END_NAMESPACE

#include "Project/SceneObject/KESceneObject.h"

#include "KEBehaviorBase.inl"
#include "KEBehavior.inl"

#endif /* _KEBEHAVIOR_H_ */
