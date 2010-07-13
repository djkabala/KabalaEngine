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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESceneObject.h"
#include "KEBehavior.h"
#include "Project/Scene/KEScene.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneObjectBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneObject.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               * 
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneObject::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}
BehaviorUnrecPtr SceneObject::getBehaviors (UInt32 index)
{
	if(index >= getMFBehaviors()->size())
	{
		SWARNING << "Scene Object attempted to access a index of MFBehaviors that doesn't exist. Returning last index of MFBehaviors!" << std::endl;
		index = getMFBehaviors()->size() - 1;
	}

	return _mfBehaviors[index];
}

const Scene* SceneObject::getParentScene () const
{
	return dynamic_cast<const Scene*>(_sfParentScene.getValue());
}

Scene* SceneObject::getParentScene ()
{
	return dynamic_cast<Scene*>(_sfParentScene.getValue());
}

void SceneObject::checkBehaviorInitialization()
{
	for(UInt32 i = 0;_mfBehaviors.size() > i; i++)
	{
		if(!getBehaviors(i)->isInitialized())
		{
			getBehaviors(i)->checkListenerAttachment();
		}
	}
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EffectRefPtr SceneObject::getEffect(std::string name)
{
    MFUnrecChildEffectPtr::const_iterator elemIt  =
        _mfAttachedEffects.begin();
    MFUnrecChildEffectPtr::const_iterator elemEnd =
        _mfAttachedEffects.end  ();

    while(elemIt != elemEnd)
    {
        if(name.compare(OSG::getName(*elemIt)) == 0)
        {
            return *elemIt;
        }

        ++elemIt;
    }
}

void SceneObject::InitializeAll()
{
	SLOG << "Initializing All Behaviors"  << std::endl;

	for(UInt32 i = 0; i < getMFBehaviors()->size(); i++)
	{
		getBehaviors(i)->addedToSceneObject(SceneObjectUnrecPtr(this));
	}
}

void SceneObject::InitializeBehaviors()
{
	SLOG << "Initializing all uninitialized behaviors"  << std::endl;

	for(UInt32 i = 0; i < getMFBehaviors()->size(); i++)
	{
		if(!getBehaviors(i)->isInitialized())
		{
			getBehaviors(i)->addedToSceneObject(SceneObjectUnrecPtr(this));
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneObject::SceneObject(void) :
    Inherited()
{
}

SceneObject::SceneObject(const SceneObject &source) :
    Inherited(source)
{
}

SceneObject::~SceneObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneObject::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & ParentSceneFieldMask)
	{
		InitializeAll();
	}
	if(whichField & BehaviorsFieldMask)
	{
		InitializeBehaviors();
	}
}

void SceneObject::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneObject NI" << std::endl;
}

OSG_END_NAMESPACE
