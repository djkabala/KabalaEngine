/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  Robert Goetz (rdgoetz@iastate.edu)                            *
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

#ifndef _KEPHYSICSIMPULSEEFFECT_H_
#define _KEPHYSICSIMPULSEEFFECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KEPhysicsImpulseEffectBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsImpulseEffect class. See \ref
           PageKabalaEnginePhysicsImpulseEffect for a description.
*/

class KE_KABALAENGINE_DLLMAPPING PhysicsImpulseEffect : public PhysicsImpulseEffectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsImpulseEffectBase Inherited;
    typedef PhysicsImpulseEffect     Self;

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

    // Variables should all be in PhysicsImpulseEffectBase.

    void inheritedBegin    (void);
    bool inheritedIsPlaying(void);
    bool inheritedIsPaused (void);
    void inheritedPause    (void);
    void inheritedUnpause  (void);
    void inheritedStop     (void);
    void initEffect        (void);
    void finished          (void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsImpulseEffect(void);
    PhysicsImpulseEffect(const PhysicsImpulseEffect &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsImpulseEffect(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsImpulseEffectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsImpulseEffect &source);
};

typedef PhysicsImpulseEffect *PhysicsImpulseEffectP;

OSG_END_NAMESPACE

#include <OpenSG/OSGPhysicsBody.h>      // PhysicsBodies Class
#include <OpenSG/OSGPhysicsWorld.h>     // PhysicsWorld Class
#include <OpenSG/OSGPhysicsSpace.h>     // PhysicsSpace Class
#include <OpenSG/OSGPhysicsWorld.h>     // PhysicsWorld Class
#include "KEPhysicsImpulseEffectBase.inl"
#include "KEPhysicsImpulseEffect.inl"

#endif /* _KEPHYSICSIMPULSEEFFECT_H_ */
