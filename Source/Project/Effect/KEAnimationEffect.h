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

#ifndef _KEANIMATIONEFFECT_H_
#define _KEANIMATIONEFFECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KEAnimationEffectBase.h"
#include <OpenSG/OSGEventProducer.h>

OSG_BEGIN_NAMESPACE

/*! \brief AnimationEffect class. See \ref
           PageKabalaEngineAnimationEffect for a description.
*/

class KE_KABALAENGINE_DLLMAPPING AnimationEffect : public AnimationEffectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimationEffectBase Inherited;
    typedef AnimationEffect     Self;
    
    void begin();
    bool isPlaying();
    bool isPaused();
    void pause();
    void unpause();
    void end();

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

    // Variables should all be in AnimationEffectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimationEffect(void);
    AnimationEffect(const AnimationEffect &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimationEffect(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimationEffectBase;

    EventProducerPtr theUpdateProducer;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimationEffect &source);
};

typedef AnimationEffect *AnimationEffectP;

OSG_END_NAMESPACE

#include <OpenSG/OSGAnimation.h>        // TheAnimation Class
#include "KEAnimationEffectBase.inl"
#include "KEAnimationEffect.inl"

#endif /* _KEANIMATIONEFFECT_H_ */
