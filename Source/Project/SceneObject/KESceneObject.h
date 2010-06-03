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

#ifndef _KESCENEOBJECT_H_
#define _KESCENEOBJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneObjectBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneObject class. See \ref
           PageKabalaEngineSceneObject for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneObject : public SceneObjectBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneObjectBase Inherited;
    typedef SceneObject     Self;

	BehaviorUnrecPtr getBehaviors (UInt32 index);


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

	  void InitializeAll();
	  void InitializeBehaviors();

    // Variables should all be in SceneObjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneObject(void);
    SceneObject(const SceneObject &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneObject(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneObjectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneObject &source);
};

typedef SceneObject *SceneObjectP;

OSG_END_NAMESPACE

#include "Project/SceneObject/KEBehavior.h" // Behaviors Class
#include <OpenSG/OSGNode.h>             // Node Class
#include "Project/Effect/KEEffect.h"    // AttachedEffects Class
#include "KESceneObjectBase.inl"
#include "KESceneObject.inl"

#endif /* _KESCENEOBJECT_H_ */
