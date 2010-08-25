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

#ifndef _KESEQUENTIALEFFECTGROUP_H_
#define _KESEQUENTIALEFFECTGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "KESequentialEffectGroupBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SequentialEffectGroup class. See \ref
           PageKabalaEngineSequentialEffectGroup for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SequentialEffectGroup : public SequentialEffectGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SequentialEffectGroupBase Inherited;
    typedef SequentialEffectGroup     Self;
    
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
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

     // Variables should all be in SequentialEffectGroupBase.

    void handleEffectFinished(EffectEventDetails* const details);
    boost::signals2::connection _EffectFinishedConnection;
    
    void initEffect        (void);
    void inheritedBegin    (void);
    bool inheritedIsPlaying(void);
    bool inheritedIsPaused (void);
    void inheritedPause    (void);
    void inheritedUnpause  (void);
    void inheritedStop     (void);
    void finished          (void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SequentialEffectGroup(void);
    SequentialEffectGroup(const SequentialEffectGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SequentialEffectGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SequentialEffectGroupBase;

    UInt8 activeEffectIndex;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SequentialEffectGroup &source);
};

typedef SequentialEffectGroup *SequentialEffectGroupP;

OSG_END_NAMESPACE

#include "KESequentialEffectGroupBase.inl"
#include "KESequentialEffectGroup.inl"

#endif /* _KESEQUENTIALEFFECTGROUP_H_ */
