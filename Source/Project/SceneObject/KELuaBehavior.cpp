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
#include <boost/algorithm/string.hpp>


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

void LuaBehavior::initEvents(SceneObjectUnrecPtr rootSceneObject)
{
    LuaBehaviorType* const theLuaType = getLuaBehaviorType();
	theLuaType->registerWithScene(rootSceneObject->getParentScene());
    eventsInitted = true;
}

void LuaBehavior::initLinks(SceneObjectUnrecPtr rootSceneObject)
{
    LuaBehaviorType* const theLuaType = getLuaBehaviorType();

    for(UInt32 i(0); i < theLuaType->getSourceContainers().size(); ++i)
    {
        if(theLuaType->getSourceContainers()[i].compare("*")==0)
        {
            UInt64 uId(0);//rootSceneObject->getParentScene()->getId();
            //uId <<= 32;
            const EventDescription* desc = rootSceneObject->getParentScene()->getProducerType().findEventDescription(theLuaType->getEventLinks()[i]);
            if(desc != NULL)
            {
                uId |=  desc->getEventId();
                _FunctionsMap[uId] = std::vector<std::string>();

                std::string NestedTableFunction(theLuaType->getLuaFunctionNames()[i]);
                if(NestedTableFunction.empty())
                {
                    SWARNING << "The lua function bound to the " << desc->getName() << " produced event of " << theLuaType->getName() << " is empty." << theLuaType->getEventLinks()[i] << endLog;
                }
                else
                {
                    std::string::size_type subStrStart(0),
                                           subStrEnd(0);
                    //Loop through all nested tables
                    while(subStrEnd != std::string::npos)
                    {
                        subStrEnd   = NestedTableFunction.find_first_of('.',subStrStart);
                        _FunctionsMap[uId].push_back(NestedTableFunction.substr(subStrStart,subStrEnd-subStrStart));

                        if(subStrEnd != std::string::npos) ++subStrEnd; 
                        subStrStart = subStrEnd;
                    }
                    //BUG: For some reason using the split algorithm is causing a
                    //misaligned stack error on OS X builds of the engine.  This
                    //does not occur for the use of split in dependent libraries.
                    //So for now the split is done by hand.
                    //boost::algorithm::split( , NestedTableFunction, boost::algorithm::is_any_of(std::string(".")) );
                }


                attachHandlers(rootSceneObject->getParentScene());
            }
            else
            {
                SWARNING << "LuaBehavior could not find event " << theLuaType->getEventLinks()[i] << endLog;
            }
        }
        else
        {
            FieldContainerRefPtr fc = getFieldContainer(theLuaType->getSourceContainers()[i]);

            UInt64 uId = fc->getId();

            uId <<= 32;
            const EventDescription* desc = fc->getProducerType().findEventDescription(theLuaType->getEventLinks()[i]);
            if(desc != NULL)
            {
                std::string NestedTableFunction(theLuaType->getLuaFunctionNames()[i]);
                if(NestedTableFunction.empty())
                {
                    SWARNING << "The lua function bound to the " << desc->getName() << " produced event of " << fc->getProducerType().getName() << " is empty." << theLuaType->getEventLinks()[i] << endLog;
                }
                else
                {
                    uId |=  desc->getEventId();
                    _FunctionsMap[uId] = std::vector<std::string>();

                    std::string::size_type subStrStart(0),
                                           subStrEnd(0);
                    //Loop through all nested tables
                    while(subStrEnd != std::string::npos)
                    {
                        subStrEnd   = NestedTableFunction.find_first_of('.',subStrStart);
                        _FunctionsMap[uId].push_back(NestedTableFunction.substr(subStrStart,subStrEnd-subStrStart));

                        if(subStrEnd != std::string::npos) ++subStrEnd; 
                        subStrStart = subStrEnd;
                    }
                    //BUG: For some reason using the split algorithm is causing a
                    //misaligned stack error on OS X builds of the engine.  This
                    //does not occur for the use of split in dependent libraries.
                    //So for now the split is done by hand.
                    //boost::algorithm::split( _FunctionsMap[uId], NestedTableFunction, boost::algorithm::is_any_of(std::string(".")) );
                }

                UInt32 EventID(fc->getProducerType().getProducedEventId(theLuaType->getEventLinks()[i]));
                fc->connectEvent(EventID, boost::bind(&LuaBehavior::handleDepFieldContainerEvent, this, _1, EventID));
                linksMade++;
            }
            else
            {
                SWARNING << "LuaBehavior could not find event " << theLuaType->getEventLinks()[i] << endLog;
            }
            
        }
    }
}

void LuaBehavior::depBehaviorProducedEvent(EventDetails* const e, UInt32 producedEventID)
{
    UInt64 uId(producedEventID);

    callLuaFunctionForEvent(uId,e,producedEventID);
}

void LuaBehavior::depFieldContainerProducedEvent(EventDetails* const details, UInt32 producedEventID)
{
    UInt64 uId(details->getSource()->getId());
    uId <<= 32;
    uId |= producedEventID;

    callLuaFunctionForEvent(uId,details,producedEventID);
}

void LuaBehavior::callLuaFunctionForEvent(UInt64 MapId,
                                          EventDetails* const details,
                                          UInt32 ProducedEventID)
{
    //Get the Lua state
    lua_State *LuaState(LuaManager::the()->getLuaState());
        
    const std::vector<std::string>& funcPath = _FunctionsMap[MapId];

    //Get the Lua function to be called
    for(UInt32 i(0) ; i<funcPath.size() ; ++i)
    {
        if(i == 0)
        {
            lua_pushstring(LuaState,funcPath[i].c_str());             //push the name of the table on the stack
            lua_gettable(LuaState, LUA_GLOBALSINDEX);  //Push The table onto the stack
        }
        else
        {
            //Check if the the value given is a table
            if(!lua_istable(LuaState, -1))
            {
                lua_pop(LuaState, 1); //Pop the value off the stack
                std::string TablePath("");
                for(UInt32 j(0) ; j<i ; ++j)
                {
                    if(j!=0) TablePath += ".";
                    TablePath += funcPath[j];
                }
                SWARNING << TablePath << " cannot be referenced in lua because it is not a table" << std::endl;
                return;
            }
        
            lua_pushstring(LuaState,funcPath[i].c_str());             //push the name of the table on the stack
            lua_gettable(LuaState, -2);  //Push The table onto the stack

            //Remove the original table from the stack
            lua_remove(LuaState, -2);
        }
    }

    //Check if the the value given is a function
    if(!lua_isfunction(LuaState, -1))
    {
        lua_pop(LuaState, 1); //Pop the value off the stack

        std::string TablePath("");
        for(UInt32 i(0) ; i<funcPath.size() ; ++i)
        {
            if(i!=0) TablePath += ".";
            TablePath += funcPath[i];
        }
        SWARNING << TablePath << " cannot be referenced in lua because it is not a function" << std::endl;
        return;
    }

    //Push on the arguments
    push_FieldContainer_on_lua(LuaState, details);   //Argument 1: the Event

    push_Behavior_on_lua(LuaState, this);   //Argument 2: the The Behavior it came from

    lua_pushnumber(LuaState,ProducedEventID);             //Argument 3: the ProducedEvent ID

    //Execute the Function
    //
    //                                                |------3 arguments to function
    //                                                |
    //                                                |  |---0 arguments returned
    //                                                |  |
    //                                                V  V
    LuaManager::the()->checkError(lua_pcall(LuaState, 3, 0, 0));
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
