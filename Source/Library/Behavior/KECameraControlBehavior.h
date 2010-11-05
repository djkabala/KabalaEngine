/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com),                            *
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

#ifndef _KECAMERACONTROLBEHAVIOR_H_
#define _KECAMERACONTROLBEHAVIOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KECameraControlBehaviorBase.h"
#include <OpenSG/OSGPhysicsBodyFields.h>
#include <OpenSG/OSGPhysicsLMotorJointFields.h>
#include <OpenSG/OSGPhysicsAMotorJointFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief CameraControlBehavior class. See \ref
           PageKabalaEngineCameraControlBehavior for a description.
*/

class KE_KABALAENGINE_DLLMAPPING CameraControlBehavior : public CameraControlBehaviorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CameraControlBehaviorBase Inherited;
    typedef CameraControlBehavior     Self;

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
    virtual void initEvents(SceneObject* const rootSceneObject);
	virtual void initLinks(SceneObject* const rootSceneObject);

	virtual bool isLinked(void) const;
    virtual bool eventsAreInitted(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CameraControlBehaviorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CameraControlBehavior(void);
    CameraControlBehavior(const CameraControlBehavior &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CameraControlBehavior(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void handleKeyPressed(KeyEventDetails* const details);
    void handleKeyReleased(KeyEventDetails* const details);
    void handleUpdate(UpdateEventDetails* const details);
    void handleMousePressed(MouseEventDetails* const details);
    void handleMouseDragged(MouseEventDetails* const details);
    void handleMouseReleased(MouseEventDetails* const details);

    boost::signals2::connection _KeyPressedConnection,
                                _KeyReleasedConnection,
                                _UpdateConnection,
                                _MousePressedConnection,
                                _MouseDraggedConnection,
                                _MouseReleasedConnection;

	virtual void depBehaviorProducedEvent(EventDetails* const e, UInt32 ID);
    virtual void depFieldContainerProducedEvent(EventDetails* const e, UInt32 ID);

    bool _MoveStateForward,
         _MoveStateBackward,
         _MoveStateLeft,
         _MoveStateRight;

    Real32 _LinearSpeed,
           _MaxLinearForce;

    Vec3f  _AngularSpeed,
           _MaxAngularForce;

    Vec2f  _CameraXRotSensitivity,
           _CameraYRotSensitivity;

    Vec3f  _MouseSensitivity;

    PhysicsBodyRecPtr _PhysBody;
    PhysicsLMotorJointRecPtr _LinearMotor;
    PhysicsAMotorJointRecPtr _AngularMotor;

    Vec2f _DeltaRotation;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CameraControlBehaviorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CameraControlBehavior &source);
};

typedef CameraControlBehavior *CameraControlBehaviorP;

OSG_END_NAMESPACE

#include "KECameraControlBehaviorBase.inl"
#include "KECameraControlBehavior.inl"

#endif /* _KECAMERACONTROLBEHAVIOR_H_ */
