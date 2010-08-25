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

#ifndef _KEEFFECTEVENTDETAILS_H_
#define _KEEFFECTEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "KEEffectEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief EffectEventDetails class. See \ref
           PageKabalaEngineEffectEventDetails for a description.
*/

class KE_KABALAENGINE_DLLMAPPING EffectEventDetails : public EffectEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef EffectEventDetailsBase Inherited;
    typedef EffectEventDetails     Self;

    static EffectEventDetailsTransitPtr create(FieldContainer* const Source,
                                                     Time TimeStamp);

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

    // Variables should all be in EffectEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EffectEventDetails(void);
    EffectEventDetails(const EffectEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EffectEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class EffectEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const EffectEventDetails &source);
};

typedef EffectEventDetails *EffectEventDetailsP;

OSG_END_NAMESPACE

#include "KEEffectEventDetailsBase.inl"
#include "KEEffectEventDetails.inl"

#endif /* _KEEFFECTEVENTDETAILS_H_ */
