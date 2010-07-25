/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *  authors: David Kabala (djkabala@gmail.com), Eric Langkamp, Robert Goetz  *
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

#include "KELuaBehavior.h"
#include "KELuaBehaviorType.h"

#include <OpenSG/OSGLuaManager.h>
#include <OpenSG/OSG_wrap.h>
#include <OpenSG/OSGFilePathAttachment.h>
#include <OpenSG/OSGContainerUtils.h>
#include <fstream>
#include <sstream>

#include "LuaBindings/KELuaBindings.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaBehaviorBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaBehavior.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaBehavior::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

LuaBehaviorType* const LuaBehavior::getLuaBehaviorType(void) const
{
    return dynamic_cast<LuaBehaviorType* const>(theBehaviorType);
}

void LuaBehavior::initialize(SceneObjectUnrecPtr rootSceneObject)
{
    LuaBehaviorType* const theLuaType = getLuaBehaviorType();
	theLuaType->registerWithScene(rootSceneObject->getParentScene());

    for(UInt32 i(0); i < theLuaType->getSourceContainers().size(); ++i)
    {
        if(theLuaType->getSourceContainers()[i].compare("*")==0)
        {
            UInt64 uId(0);//rootSceneObject->getParentScene()->getId();
            //uId <<= 32;
            const MethodDescription* desc = getEventProducer(rootSceneObject->getParentScene())->getProducerType().findMethodDescription(theLuaType->getEventLinks()[i]);
            if(desc != NULL)
            {
                uId |=  desc->getMethodId();
                luaFunctionsMap[uId] = theLuaType->getLuaFunctionNames()[i];
            }
            else
            {
                SWARNING << "LuaBehavior could not find event " << theLuaType->getEventLinks()[i] << endLog;
            }

            attachListeners(rootSceneObject->getParentScene()->editEventProducer());
        }
        else
        {
            FieldContainerRefPtr fc = getFieldContainer(theLuaType->getSourceContainers()[i]);
            EventProducerPtr eventProducer = getEventProducer(fc);

            UInt64 uId = fc->getId();

            uId <<= 32;
            const MethodDescription* desc = getEventProducer(fc)->getProducerType().findMethodDescription(theLuaType->getEventLinks()[i]);
            if(desc != NULL)
            {
                uId |=  desc->getMethodId();
                luaFunctionsMap[uId] = theLuaType->getLuaFunctionNames()[i];
            }
            else
            {
                SWARNING << "LuaBehavior could not find event " << theLuaType->getEventLinks()[i] << endLog;
            }
            
            eventProducer->attachEventListener(&_DepFieldContainerListener,eventProducer->getProducedEventId(theLuaType->getEventLinks()[i]));
        }
    }
}

void LuaBehavior::depBehaviorProducedMethod(EventUnrecPtr e, UInt32 producedEventID)
{
    LuaBehaviorType* const theLuaType = getLuaBehaviorType();
    if(!theLuaType->getLuaFunctionNames().empty())
    {
		//Get the Lua state
		lua_State *LuaState(LuaManager::the()->getLuaState());
        
        //std::map<UInt64, std::string> LuaFuncMap;
        //dont forget the << add!
        //LuaFuncMap[e->getSource()->getId()][producedEventID];

        UInt64 uId(producedEventID);
        
        std::string funcName = luaFunctionsMap[uId];

	    //Get the Lua function to be called
        lua_getglobal(LuaState, funcName.c_str());

	    //Push on the arguments
	    push_FieldContainer_on_lua(LuaState, e);   //Argument 1: the EventUnrecPtr

		push_Behavior_on_lua(LuaState, this);   //Argument 2: the The Behavior it came from

	    lua_pushnumber(LuaState,producedEventID);             //Argument 3: the ProducedEvent ID

	    //Execute the Function
	    //
	    //                  |------3 arguments to function
	    //                  |
	    //                  |  |---0 arguments returned
	    //                  |  |
	    //                  V  V
	    LuaManager::the()->checkError(lua_pcall(LuaState, 3, 0, 0));
        
	}
}

void LuaBehavior::depFieldContainerProducedMethod(EventUnrecPtr e, UInt32 producedEventID)
{
    LuaBehaviorType* const theLuaType = getLuaBehaviorType();
    if(!theLuaType->getLuaFunctionNames().empty())
    {
		//Get the Lua state
		lua_State *LuaState(LuaManager::the()->getLuaState());
        
        //std::map<UInt64, std::string> LuaFuncMap;
        //dont forget the << add!
        //LuaFuncMap[e->getSource()->getId()][producedEventID];

        UInt64 uId(e->getSource()->getId());
        uId <<= 32;
        uId |= producedEventID;

        std::string funcName = luaFunctionsMap[uId];

	    //Get the Lua function to be called
        lua_getglobal(LuaState, funcName.c_str());

	    //Push on the arguments
	    push_FieldContainer_on_lua(LuaState, e);   //Argument 1: the EventUnrecPtr

		push_Behavior_on_lua(LuaState, this);   //Argument 2: the The Behavior it came from

	    lua_pushnumber(LuaState,producedEventID);             //Argument 3: the ProducedEvent ID

	    //Execute the Function
	    //
	    //                  |------3 arguments to function
	    //                  |
	    //                  |  |---0 arguments returned
	    //                  |  |
	    //                  V  V
	    LuaManager::the()->checkError(lua_pcall(LuaState, 3, 0, 0));
        
	}
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaBehavior::LuaBehavior(void) :
    Inherited()
{
}

LuaBehavior::LuaBehavior(const LuaBehavior &source) :
    Inherited(source)
{
}

LuaBehavior::~LuaBehavior(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaBehavior::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LuaBehavior::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaBehavior NI" << std::endl;
}

OSG_END_NAMESPACE
