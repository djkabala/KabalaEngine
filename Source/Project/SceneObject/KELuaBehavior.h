/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com), Eric Langkamp              *
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

#ifndef _KELUABEHAVIOR_H_
#define _KELUABEHAVIOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KELuaBehaviorBase.h"
#include "KELuaBehaviorType.h"

OSG_BEGIN_NAMESPACE

/*! \brief LuaBehavior class. See \ref
           PageKabalaEngineLuaBehavior for a description.
*/

class KE_KABALAENGINE_DLLMAPPING LuaBehavior : public LuaBehaviorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LuaBehaviorBase Inherited;
    typedef LuaBehavior     Self;

    LuaBehaviorType* const getLuaBehaviorType(void) const;

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

    // Variables should all be in LuaBehaviorBase.

	void depBehaviorProducedMethod(EventUnrecPtr e, UInt32 ID);
    void depFieldContainerProducedMethod(EventUnrecPtr e, UInt32 ID);

    void initialize(SceneObjectUnrecPtr rootSceneObject);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaBehavior(void);
    LuaBehavior(const LuaBehavior &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaBehavior(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LuaBehaviorBase;

    std::map<UInt64,std::string> luaFunctionsMap;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LuaBehavior &source);
};

typedef LuaBehavior *LuaBehaviorP;

OSG_END_NAMESPACE

#include "KELuaBehaviorBase.inl"
#include "KELuaBehavior.inl"

#endif /* _KELUABEHAVIOR_H_ */
