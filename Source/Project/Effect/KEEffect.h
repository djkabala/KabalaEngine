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

#ifndef _KEEFFECT_H_
#define _KEEFFECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KEEffectBase.h"
#include "KEEffectEvent.h"
#include "Project/SceneObject/KESceneObject.h"

OSG_BEGIN_NAMESPACE

/*! \brief Effect class. See \ref
           PageKabalaEngineEffect for a description.
*/

class KE_KABALAENGINE_DLLMAPPING Effect : public EffectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef EffectBase Inherited;
    typedef Effect     Self;

    void begin(void);
    bool isPlaying(void);
    bool isPaused(void);
    void pause(void);
    void unpause(void);
    void end(void);

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    const SceneObject* getParentSceneObject(void) const;


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
    
    virtual void inheritedBegin    (void) = 0;
    virtual bool inheritedIsPlaying(void) = 0;
    virtual bool inheritedIsPaused (void) = 0;
    virtual void inheritedPause    (void) = 0;
    virtual void inheritedUnpause  (void) = 0;
    virtual void inheritedEnd      (void) = 0;

    void producerEffectPlayed  (const EffectEventUnrecPtr e);
    void producerEffectPaused  (const EffectEventUnrecPtr e);
    void producerEffectUnpaused(const EffectEventUnrecPtr e);
    void producerEffectFinished(const EffectEventUnrecPtr e);
    void producerEffectStopped (const EffectEventUnrecPtr e);

    // Variables should all be in EffectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Effect(void);
    Effect(const Effect &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Effect(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class EffectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Effect &source);
};

typedef Effect *EffectP;

OSG_END_NAMESPACE

#include <OpenSG/OSGFieldContainer.h>   // ParentSceneObject Class
#include "KEEffectBase.inl"
#include "KEEffect.inl"

#endif /* _KEEFFECT_H_ */
