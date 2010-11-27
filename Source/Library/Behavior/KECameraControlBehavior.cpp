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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KECameraControlBehavior.h"
#include <OpenSG/OSGPhysicsBody.h>
#include <OpenSG/OSGPhysicsLMotorJoint.h>
#include <OpenSG/OSGPhysicsLMotorJoint.h>
#include <OpenSG/OSGPhysicsAMotorJoint.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCameraControlBehaviorBase.cpp file.
// To modify it, please change the .fcd file (OSGCameraControlBehavior.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CameraControlBehavior::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void CameraControlBehavior::initEvents(SceneObject* const rootSceneObject)
{
}

void CameraControlBehavior::initLinks(SceneObject* const rootSceneObject)
{
    NodeRecPtr CameraBeaconNode  = rootSceneObject->getNode();
    _PhysBody = dynamic_cast<PhysicsBody*>(CameraBeaconNode->findAttachment(PhysicsBody::getClassType()));
    _PhysBody->setGravityMode(false);
    //_PhysBody->setMaxAngularSpeed(0.0f);
    //_PhysBody->setLinearDamping(0.001);

    //Add the Linear Motor
    _LinearMotor = PhysicsLMotorJoint::create(rootSceneObject->getParentScene()->getPhysicsWorld());
    _LinearMotor->setFirstBody(_PhysBody);
    _LinearMotor->setSecondBody(NULL);
    _LinearMotor->setNumAxes(3);
    _LinearMotor->setAxis1Properties(Vec3f(1.0,0.0,0.0),1);
    _LinearMotor->setAxis2Properties(Vec3f(0.0,1.0,0.0),1);
    _LinearMotor->setAxis3Properties(Vec3f(0.0,0.0,1.0),1);

    CameraBeaconNode->addAttachment(_LinearMotor);

    //Add the Angular Motor
    _AngularMotor = PhysicsAMotorJoint::create(rootSceneObject->getParentScene()->getPhysicsWorld());
    _AngularMotor->setFirstBody(_PhysBody);
    _AngularMotor->setSecondBody(NULL);
    _AngularMotor->setNumAxes(3);
    _AngularMotor->setAxis1Properties(Vec3f(1.0,0.0,0.0),1);
    _AngularMotor->setAxis2Properties(Vec3f(0.0,1.0,0.0),1);
    _AngularMotor->setAxis3Properties(Vec3f(0.0,0.0,1.0),1);

    CameraBeaconNode->addAttachment(_AngularMotor);

    _KeyPressedConnection = rootSceneObject->getParentScene()->connectKeyPressed(boost::bind(&CameraControlBehavior::handleKeyPressed, this, _1));
    _KeyReleasedConnection = rootSceneObject->getParentScene()->connectKeyReleased(boost::bind(&CameraControlBehavior::handleKeyReleased, this, _1));
    _UpdateConnection = rootSceneObject->getParentScene()->connectUpdate(boost::bind(&CameraControlBehavior::handleUpdate, this, _1));
    _MousePressedConnection = rootSceneObject->getParentScene()->connectMousePressed(boost::bind(&CameraControlBehavior::handleMousePressed, this, _1));
}

bool CameraControlBehavior::eventsAreInitted(void) const
{
	return true;
}

bool CameraControlBehavior::isLinked(void) const
{
    return _KeyPressedConnection.connected();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void CameraControlBehavior::depBehaviorProducedEvent(EventDetails* const e, UInt32 ID)
{
}

void CameraControlBehavior::depFieldContainerProducedEvent(EventDetails* const e, UInt32 ID)
{
}

void CameraControlBehavior::handleKeyPressed(KeyEventDetails* const details)
{
    switch(details->getKey())
    {
    case KeyEventDetails::KEY_A:
    case KeyEventDetails::KEY_LEFT:
        _MoveStateLeft = true;
        break;
    case KeyEventDetails::KEY_S:
    case KeyEventDetails::KEY_DOWN:
        _MoveStateBackward = true;
        break;
    case KeyEventDetails::KEY_D:
    case KeyEventDetails::KEY_RIGHT:
        _MoveStateRight = true;
        break;
    case KeyEventDetails::KEY_W:
    case KeyEventDetails::KEY_UP:
        _MoveStateForward = true;
        break;
    }
}

void CameraControlBehavior::handleKeyReleased(KeyEventDetails* const details)
{
    switch(details->getKey())
    {
    case KeyEventDetails::KEY_A:
    case KeyEventDetails::KEY_LEFT:
        _MoveStateLeft = false;
        break;
    case KeyEventDetails::KEY_S:
    case KeyEventDetails::KEY_DOWN:
        _MoveStateBackward = false;
        break;
    case KeyEventDetails::KEY_D:
    case KeyEventDetails::KEY_RIGHT:
        _MoveStateRight = false;
        break;
    case KeyEventDetails::KEY_W:
    case KeyEventDetails::KEY_UP:
        _MoveStateForward = false;
        break;
    }
}

void CameraControlBehavior::handleUpdate(UpdateEventDetails* const details)
{
    Vec3f Velocity;

    if(_MoveStateForward)
    {
        Velocity = Velocity - Vec3f(0.0,0.0,1.0);
    }
    if(_MoveStateBackward)
    {
        Velocity = Velocity + Vec3f(0.0,0.0,1.0);
    }
    if(_MoveStateLeft)
    {
        Velocity = Velocity - Vec3f(1.0,0.0,0.0);
    }
    if(_MoveStateRight)
    {
        Velocity = Velocity + Vec3f(1.0,0.0,0.0);
    }

    Velocity.normalize();
    Velocity = Velocity * _LinearSpeed;

    _PhysBody->setEnable(true);

    _LinearMotor->setVel(Velocity.x());
    if(Velocity.x() != 0.0)
    {
        _LinearMotor->setFMax(_MaxLinearForce);
    }
    else
    {
        _LinearMotor->setFMax(_MaxLinearForce);
    }
    _LinearMotor->setVel2(Velocity.y());
    if(Velocity.y() != 0.0)
    {
        _LinearMotor->setFMax2(_MaxLinearForce);
    }
    else
    {
        _LinearMotor->setFMax2(_MaxLinearForce);
    }
    _LinearMotor->setVel3(Velocity.z());
    if(Velocity.z() != 0.0)
    {
        _LinearMotor->setFMax3(_MaxLinearForce);
    }
    else
    {
        _LinearMotor->setFMax3(_MaxLinearForce);
    }
    
    //Determine the amount of rotation around the local Z-axis
    Vec3f ZAxisRot;
    _PhysBody->getQuaternion().getEulerAngleRad(ZAxisRot);
    
    //Apply an angular velocity to correct for any z-axis drift
    Vec3f AngularVelocity = Vec3f(0.0,0.0,-ZAxisRot.z() * _AngularSpeed.z());

    _AngularMotor->setVel(AngularVelocity.x());
    if(AngularVelocity.x() != 0.0)
    {
        _AngularMotor->setFMax(_MaxAngularForce.x());
    }
    else
    {
        _AngularMotor->setFMax(_MaxAngularForce.x());
    }
    _AngularMotor->setVel2(AngularVelocity.y());
    if(AngularVelocity.y() != 0.0)
    {
        _AngularMotor->setFMax2(_MaxAngularForce.y());
    }
    else
    {
        _AngularMotor->setFMax2(_MaxAngularForce.y());
    }
    _AngularMotor->setVel3(AngularVelocity.z());
    if(AngularVelocity.z() != 0.0)
    {
        _AngularMotor->setFMax3(_MaxAngularForce.z());
    }
    else
    {
        _AngularMotor->setFMax3(_MaxAngularForce.z());
    }
}

void CameraControlBehavior::handleMousePressed(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        _MouseDraggedConnection = MainApplication::the()->getMainWindow()->connectMouseDragged(boost::bind(&CameraControlBehavior::handleMouseDragged, this, _1));
        _MouseReleasedConnection = MainApplication::the()->getMainWindow()->connectMouseReleased(boost::bind(&CameraControlBehavior::handleMouseReleased, this, _1));
    }
}

void CameraControlBehavior::handleMouseDragged(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        _DeltaRotation -= Vec2f(details->getDelta().x() * _MouseSensitivity.x(),
                                details->getDelta().y() * _MouseSensitivity.y());

        Quaternion YRot(Vec3f(0.0,1.0,0.0), _DeltaRotation.x());
        Quaternion XRot(Vec3f(1.0,0.0,0.0), _DeltaRotation.y());
        Quaternion TotalRot = YRot;
        TotalRot.mult(XRot);
        /*Vec2f Delta(details->getDelta());

        Real32 x = osgSgn(Delta.x()) * Delta.x() * Delta.x() * _CameraXRotSensitivity[1] + Delta.x() * _CameraXRotSensitivity[0];
        Real32 y = -osgSgn(Delta.y()) * Delta.y() * Delta.y() * _CameraYRotSensitivity[1]  + Delta.y() * _CameraYRotSensitivity[0];

        Quaternion OldRot = _PhysBody->getQuaternion();

        OldRot.mult(Quaternion(Vec3f(1,0,0),_MouseSensitivity.y() * y));

        OldRot.mult(Quaternion(Vec3f(0,1,0),-_MouseSensitivity.x() * x));*/

        _PhysBody->setQuaternion(TotalRot);
    }
}

void CameraControlBehavior:: handleMouseReleased(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        _MouseDraggedConnection.disconnect();
        _MouseReleasedConnection.disconnect();
    }
}


/*----------------------- constructors & destructors ----------------------*/

CameraControlBehavior::CameraControlBehavior(void) :
    Inherited(),
    _MoveStateForward(false),
    _MoveStateBackward(false),
    _MoveStateLeft(false),
    _MoveStateRight(false),
    _LinearSpeed(4.0f),
    _MaxLinearForce(300.0f),
    _AngularSpeed(0.5f,0.5f,3.0f),
    _MaxAngularForce(2000.0f,2000.0f,6000.0f),
    _CameraXRotSensitivity(3.0f, 0.0001f),
    _CameraYRotSensitivity(-6.0f, 0.0004f),
    _MouseSensitivity(0.002f, 0.002f),
    _DeltaRotation(0.0f,0.0f)
{
}

CameraControlBehavior::CameraControlBehavior(const CameraControlBehavior &source) :
    Inherited(source),
    _MoveStateForward(false),
    _MoveStateBackward(false),
    _MoveStateLeft(false),
    _MoveStateRight(false),
    _LinearSpeed(source._LinearSpeed),
    _MaxLinearForce(source._MaxLinearForce),
    _AngularSpeed(source._AngularSpeed),
    _MaxAngularForce(source._MaxAngularForce),
    _CameraXRotSensitivity(source._CameraXRotSensitivity),
    _CameraYRotSensitivity(source._CameraYRotSensitivity),
    _MouseSensitivity(source._MouseSensitivity),
    _DeltaRotation(0.0f,0.0f)
{
}

CameraControlBehavior::~CameraControlBehavior(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CameraControlBehavior::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CameraControlBehavior::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CameraControlBehavior NI" << std::endl;
}

OSG_END_NAMESPACE
