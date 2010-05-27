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

#ifndef _KEPARTICLESYSTEMEFFECT_H_
#define _KEPARTICLESYSTEMEFFECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KEParticleSystemEffectBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemEffect class. See \ref
           PageKabalaEngineParticleSystemEffect for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ParticleSystemEffect : public ParticleSystemEffectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleSystemEffectBase Inherited;
    typedef ParticleSystemEffect     Self;

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

    // Variables should all be in ParticleSystemEffectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemEffect(void);
    ParticleSystemEffect(const ParticleSystemEffect &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemEffect(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemEffectBase;

    bool isPausedFlag;
    EventProducerPtr theUpdateProducer;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemEffect &source);
};

typedef ParticleSystemEffect *ParticleSystemEffectP;

OSG_END_NAMESPACE

#include "OSGParticleSystem.h"          // TheSystem Class
#include "KEParticleSystemEffectBase.inl"
#include "KEParticleSystemEffect.inl"

#endif /* _KEPARTICLESYSTEMEFFECT_H_ */
