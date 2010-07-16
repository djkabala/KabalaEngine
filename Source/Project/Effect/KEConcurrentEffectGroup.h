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

#ifndef _KECONCURRENTEFFECTGROUP_H_
#define _KECONCURRENTEFFECTGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConcurrentEffectGroupBase.h"
#include "KEEffectListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief ConcurrentEffectGroup class. See \ref
           PageKabalaEngineConcurrentEffectGroup for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ConcurrentEffectGroup : public ConcurrentEffectGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ConcurrentEffectGroupBase Inherited;
    typedef ConcurrentEffectGroup     Self;

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
    
    void handleEffectFinished(void);
    
    void initEffect        (void);
    void inheritedBegin    (void);
    bool inheritedIsPlaying(void);
    bool inheritedIsPaused (void);
    void inheritedPause    (void);
    void inheritedUnpause  (void);
    void inheritedStop     (void);
    void finished          (void);

    // Variables should all be in ConcurrentEffectGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ConcurrentEffectGroup(void);
    ConcurrentEffectGroup(const ConcurrentEffectGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ConcurrentEffectGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ConcurrentEffectGroupBase;

    UInt8 activeEffects;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ConcurrentEffectGroup &source);
};

typedef ConcurrentEffectGroup *ConcurrentEffectGroupP;

OSG_END_NAMESPACE

#include "KEConcurrentEffectGroupBase.inl"
#include "KEConcurrentEffectGroup.inl"

#endif /* _KECONCURRENTEFFECTGROUP_H_ */
