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

#ifndef _KEEFFECTGROUP_H_
#define _KEEFFECTGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "KEEffectGroupBase.h"
#include "KEEffectListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief EffectGroup class. See \ref
           PageKabalaEngineEffectGroup for a description.
*/

class KE_KABALAENGINE_DLLMAPPING EffectGroup : public EffectGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef EffectGroupBase Inherited;
    typedef EffectGroup     Self;

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

    virtual void handleEffectFinished() = 0;

    virtual void inheritedBegin    (void) = 0;
    virtual bool inheritedIsPlaying(void) = 0;
    virtual bool inheritedIsPaused (void) = 0;
    virtual void inheritedPause    (void) = 0;
    virtual void inheritedUnpause  (void) = 0;
    virtual void inheritedStop     (void) = 0;
    virtual void initEffect        (void) = 0;
    virtual void finished                  (void);

    // Variables should all be in EffectGroupBase.

    class InternalEffectListener : public EffectListener
    {
      public:

        InternalEffectListener(EffectGroup* parent);
        InternalEffectListener(){};
        ~InternalEffectListener(){};

        void effectBegan(const EffectEventUnrecPtr e);
        void effectStopped(const EffectEventUnrecPtr e);
        void effectPaused(const EffectEventUnrecPtr e);
        void effectUnpaused(const EffectEventUnrecPtr e);
        void effectFinished(const EffectEventUnrecPtr e);

      protected:
        
        EffectGroup* fx;
    };

    InternalEffectListener theInternalEffectListener;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EffectGroup(void);
    EffectGroup(const EffectGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EffectGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class EffectGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const EffectGroup &source);
};

typedef EffectGroup *EffectGroupP;

OSG_END_NAMESPACE

#include "KEEffectGroupBase.inl"
#include "KEEffectGroup.inl"

#endif /* _KEEFFECTGROUP_H_ */
