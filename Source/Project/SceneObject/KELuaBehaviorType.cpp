/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *            Authors: David Kabala,Eric Langkamp,Robert Goetz               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#include <stdlib.h>
#include <stdio.h>

#include "KELuaBehaviorType.h"

#include <iostream>

#include <algorithm>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem/operations.hpp>

#include "KEBehaviorFactory.h"
#include "Project/Scene/KEScene.h"

#include <OpenSG/OSGMethodDescription.h>
#include <OpenSG/OSGLog.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <fstream>
#include <sstream>

#include <OpenSG/OSGLuaManager.h>


OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*-------------------------------------------------------------------------*/
/*                                Find                                     */



/*-------------------------------------------------------------------------*/
/*                                Has                                      */


/*-------------------------------------------------------------------------*/
/*                              Register                                   */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

LuaBehaviorType::LuaBehaviorType( const std::string &szName,
							FieldContainerType * bBehaviorFieldContainerType,
                            std::vector<std::string> eventSourceNames,
		                    std::vector<std::string> bEvents,
		                    std::vector<std::string> bEventLinks,
                            std::vector<std::string> bLuaCallbacks,
	                        BoostPath FilePath) :
    Inherited        (szName,
					  bBehaviorFieldContainerType,
                      eventSourceNames,
		              bEvents,
		              bEventLinks),

    luaFunctionNames  (bLuaCallbacks    )
{
    if(!FilePath.string().empty())
    {
        if(!boost::filesystem::exists(FilePath))
        {
            SWARNING << "Cannot load script for LuaBehaviorType, because file: "
                << FilePath.string() << " does not exist." << std::endl;
        }
        else if(!boost::filesystem::is_regular_file(FilePath))
        {
            SWARNING << "Cannot load script for LuaBehaviorType, because file: "
                << FilePath.string() << " is not a regular file." << std::endl;
        }
        else
        {
            LuaManager::the()->runScript(FilePath);
        }
    }
}

LuaBehaviorType LuaBehaviorType::create(const std::string &szName,
                                        const std::string &type,
                                        const std::string &bEvents,
                                        const std::string &bEventLinks,
                                        const std::string &luaCallback,
                                        const std::string &StrFilePath)
{
    std::vector< std::string > evtSplitVec;
    std::vector< std::string > fcsrcSplitVec;
    std::vector< std::string > evtlkSplitVec;
    std::vector< std::string > luacSplitVec;
    
    if(!bEvents.empty())
    {
        boost::algorithm::split( evtSplitVec, bEvents, boost::algorithm::is_any_of(std::string(";")) );
    }
    
    if(luaCallback.empty())
    {
        if(!bEventLinks.empty())
        {
            std::vector< std::string > eventArgs;
            std::vector< std::string > eventDefs;
            
            std::string toParse;

            boost::algorithm::split( eventArgs, bEventLinks, boost::algorithm::is_any_of("|") );

            for(std::vector< std::string >::const_iterator StrVecItor(eventArgs.begin()) ;
                StrVecItor != eventArgs.end() ;
                ++StrVecItor)
            {
                boost::algorithm::split( eventDefs, (*StrVecItor), boost::algorithm::is_any_of(":"));
                
                toParse = eventDefs[0];

                boost::algorithm::trim(toParse);

                if(toParse.length() > 1 && (toParse[0] == '\"' || toParse[0] == '\'') && (toParse[toParse.length()-1] == '\"' || toParse[toParse.length()-1] == '\''))
                {
                    toParse = toParse.substr(1,toParse.length()-2);
                }
                else if((toParse[0] != '*'))
                {
                    SWARNING << "Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "The name must be encased in quotes." << endLog;
                    return LuaBehaviorType(szName,NULL);
                }

                //boost::algorithm::replace_all_regex(toParse, boost::regex("\\([^])"), std::string("$1"));

                if(eventDefs.size() == 3)
                {
                    fcsrcSplitVec.push_back(toParse);
                    toParse = eventDefs[1];
                    boost::algorithm::trim(toParse);
                    evtlkSplitVec.push_back(toParse);
                    toParse = eventDefs[2];
                    boost::algorithm::trim(toParse);
                    luacSplitVec.push_back(toParse);
                }
                else
                {
                    SWARNING << "Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "Use wilcards (*) in place of FieldContainerName to specify that this behavior is to listen to any behaviors that can provide that event." << endLog;
                    return LuaBehaviorType(szName,NULL);
                }
            }
        }
    }
    else
    {
        if(!bEventLinks.empty())
        {
            std::vector< std::string > eventArgs;
            std::vector< std::string > eventDefs;
            
            std::string toParse;

            boost::algorithm::split( eventArgs, bEventLinks, boost::algorithm::is_any_of("|") );

            for(std::vector< std::string >::const_iterator StrVecItor(eventArgs.begin()) ;
                StrVecItor != eventArgs.end() ;
                ++StrVecItor)
            {
                boost::algorithm::split( eventDefs, (*StrVecItor), boost::algorithm::is_any_of(":"));
                
                toParse = eventDefs[0];

                boost::algorithm::trim(toParse);
                
                if(toParse.length() > 1 && (toParse[0] == '\"' || toParse[0] == '\'') && (toParse[toParse.length()-1] == '\"' || toParse[toParse.length()-1] == '\''))
                {
                    toParse = toParse.substr(1,toParse.length()-2);
                }
                else if((toParse[0] != '*'))
                {
                    SWARNING << "Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "The name must be encased in quotes." << endLog;
                    return LuaBehaviorType(szName,NULL);
                }

                //boost::algorithm::replace_all_regex(toParse, boost::regex("\\([^])"), std::string("$1"));

                if(eventDefs.size() == 2)
                {
                    fcsrcSplitVec.push_back(toParse);
                    toParse = eventDefs[1];
                    boost::algorithm::trim(toParse);
                    evtlkSplitVec.push_back(toParse);
                    luacSplitVec.push_back(luaCallback);
                }
                else
                {
                    SWARNING << "Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "Use wilcards (*) in place of FieldContainerName to specify that this behavior is to listen to any behaviors that can provide that event." << endLog;
                    return LuaBehaviorType(szName,NULL);
                }
            }
        }
    }
    
    FieldContainerType* theType = FieldContainerFactory::the()->findType(type.c_str());

    if(theType == NULL)
    {
        SWARNING << "LUA: KabalaEngine.BehaviorType_create(): The type "<< type <<" could not be found." << endLog;
        return LuaBehaviorType(szName,NULL);
    }

    return LuaBehaviorType(szName,theType,fcsrcSplitVec,evtSplitVec,evtlkSplitVec,luacSplitVec,BoostPath(StrFilePath));
}

LuaBehaviorType::LuaBehaviorType(const LuaBehaviorType &obj) :
    Inherited        (obj),
    luaFunctionNames  (obj.luaFunctionNames    )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

LuaBehaviorType::~LuaBehaviorType(void)
{
    if(GlobalSystemState != Shutdown)
    {
        terminate();
    }
}

/*-------------------------------------------------------------------------*/
/*                            Add / Sub                                    */


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void LuaBehaviorType::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "LuaBehaviorType: "
         << getCName()
         << ", Id: "       
         << getId()
         << ", parentP: " 
         << (_pParent ? _pParent->getCName() : "NONE")
         << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                                Init                                     */

