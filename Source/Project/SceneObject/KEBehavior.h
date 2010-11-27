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
#include <Project/SceneObject/KESceneObjectFields.h>
#include <OpenSG/OSGGenericEventDetails.h>
#include <OpenSG/OSGEventDetails.h>
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

    SceneObject* getParentSceneObject(void) const;

    virtual void initEvents(SceneObject* const rootSceneObject) = 0;
	virtual void initLinks(SceneObject* const rootSceneObject) = 0;

	BehaviorType * getBehaviorType(void) const;

	virtual bool isLinked(void) const;
    virtual bool eventsAreInitted(void) const;

	void checkListenerAttachment(void);

    void produceEvent(std::string name, GenericEventDetails* const eventData = NULL);
    void produceEvent(UInt32 id, GenericEventDetails* const eventData = NULL);

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

	
    virtual ~Behavior(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
	
	virtual void depBehaviorProducedEvent(EventDetails* const e, UInt32 ID) = 0;
    virtual void depFieldContainerProducedEvent(EventDetails* const e, UInt32 ID) = 0;

	void attachHandlers (Scene* const eventProducer);

	BehaviorType* _BehaviorType;
    UInt32 _LinksMade;
    bool _EventsInitted;

    // Variables should all be in BehaviorBase.

	void handleDepBehaviorEvent(EventDetails* const details, UInt32 ProducedEventId);
    boost::signals2::connection _DepBehaviorEventConnection;

	void handleDepFieldContainerEvent(EventDetails* const details, UInt32 ProducedEventId);
    boost::signals2::connection _DepFieldContainerEventConnection;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Behavior(void);
    Behavior(const Behavior &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \} 
    */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BehaviorBase;
	friend class BehaviorFactoryBase;
	friend class BehaviorType;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Behavior &source);
};

typedef Behavior *BehaviorP;

OSG_END_NAMESPACE

#include "Project/SceneObject/KESceneObject.h"

#include "KEBehaviorBase.inl"
#include "KEBehavior.inl"

#endif /* _KEBEHAVIOR_H_ */
