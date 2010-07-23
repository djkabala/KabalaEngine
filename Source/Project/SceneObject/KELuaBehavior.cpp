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

void LuaBehavior::depBehaviorProducedMethod(EventUnrecPtr e, UInt32 ID)
{
    if(!dynamic_cast<LuaBehaviorType*>(getBehaviorType())->getLuaFunctionNames().empty())
    {
		//Get the Lua state
		lua_State *LuaState(LuaManager::the()->getLuaState());
        
        FieldContainerRefPtr src = e->getSource();
        EventProducerPtr     evt = getEventProducer(src);
        EventProducerType    typ = evt->getProducerType();
        MethodDescription*   des = typ.getMethodDescription(ID);
        std::string eventName = des->getName();
        
        UInt32 i(0);
        while(i < getBehaviorType()->getEventLinks().size())
        {
            if(getBehaviorType()->getEventLinks()[i].compare(eventName))
            {
                break;
            }
            ++i;
        }

	    //Get the Lua function to be called
        lua_getglobal(LuaState, dynamic_cast<LuaBehaviorType*>(getBehaviorType())->getLuaFunctionNames()[i].c_str());

	    //Push on the arguments
	    push_FieldContainer_on_lua(LuaState, e);   //Argument 1: the EventUnrecPtr

	    push_FieldContainer_on_lua(LuaState, this);   //Argument 2: the The Behavior it came from

	    lua_pushnumber(LuaState,ID);             //Argument 3: the ProducedEvent ID

	    //Execute the Function
	    //
	    //                  |------3 arguments to function
	    //                  |
	    //                  |  |---0 arguments returned
	    //                  |  |
	    //                  V  V
	    lua_pcall(LuaState, 3, 0, 0);
        
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
