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

#ifndef _KESOUNDEFFECT_H_
#define _KESOUNDEFFECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KESoundEffectBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundEffect class. See \ref
           PageKabalaEngineSoundEffect for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SoundEffect : public SoundEffectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SoundEffectBase Inherited;
    typedef SoundEffect     Self;

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

    // Variables should all be in SoundEffectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SoundEffect(void);
    SoundEffect(const SoundEffect &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundEffect(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SoundEffectBase;
    
    bool isPausedFlag;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SoundEffect &source);
};

typedef SoundEffect *SoundEffectP;

OSG_END_NAMESPACE

#include <OpenSG/OSGSound.h>            // TheSound Class
#include "KESoundEffectBase.inl"
#include "KESoundEffect.inl"

#endif /* _KESOUNDEFFECT_H_ */
