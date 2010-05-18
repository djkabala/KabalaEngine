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

#ifndef _KECHANGESCENEACTIVITY_H_
#define _KECHANGESCENEACTIVITY_H_
#ifdef __sgi
#pragma once
#endif

#include "KEChangeSceneActivityBase.h"
#include "KEChangeSceneActivityBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ChangeSceneActivity class. See \ref
           PageKabalaEngineChangeSceneActivity for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ChangeSceneActivity : public ChangeSceneActivityBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ChangeSceneActivityBase Inherited;
    typedef ChangeSceneActivity     Self;

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

    virtual void eventProduced(const EventUnrecPtr EventDetails, UInt32 ProducedEventId);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ChangeSceneActivityBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ChangeSceneActivity(void);
    ChangeSceneActivity(const ChangeSceneActivity &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ChangeSceneActivity(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ChangeSceneActivityBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ChangeSceneActivity &source);
};

typedef ChangeSceneActivity *ChangeSceneActivityP;

OSG_END_NAMESPACE

#include "KEChangeSceneActivityBase.inl"
#include "KEChangeSceneActivity.inl"

#endif /* _KECHANGESCENEACTIVITY_H_ */
