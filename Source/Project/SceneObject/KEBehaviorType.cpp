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

#include "OSGConfig.h"

#include <iostream>

#include <algorithm>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "KEBehaviorType.h"
#include "KEBehaviorFactory.h"
#include "Project/Scene/KEScene.h"

#include "OSGMethodDescription.h"
#include "OSGLog.h"
#include "OSGTypeBase.h"

#include <OpenSG/OSGLuaManager.h>
#include <OpenSG/OSG_wrap.h>

#include "OSGFilePathAttachment.h"
#include "OSGContainerUtils.h"
#include "OSGFieldContainerFactory.h"
#include <fstream>
#include <sstream>


OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

const std::vector<std::string> BehaviorType::getSourceContainers()
{
    return _bSourceContainers;
}


const std::vector<BehaviorType*> BehaviorType::getDependencies()
{
    return _bDependencies;
}

/*-------------------------------------------------------------------------*/
/*                                Find                                     */

UInt32 BehaviorType::findEventID(std::string eventName)
{
	if(_bEvents.empty())
	{
		SWARNING << "BehaviorType: " << getName() << " has not been registered. Search for EventID's default returns ZERO!!" << std::endl;
		return 0;
	}
	for(UInt32 i = 0; _bEvents.size() > i; i++)
	{
		if(_bEvents[i] == eventName)
		{
			return _bActiveEventIDs[i];
		}
	}

	SWARNING << "BehaviorType: " << getName() << " has no event by the name of " << eventName << "Search for EventID's default returns ZERO!!" <<std::endl;
	return 0;
}

std::string BehaviorType::findEventName(UInt32 id)
{
	if(id > 0 && id < _bActiveEventIDs.size())
    {
		return _bEvents[id];
	}
    else
    {
    	SWARNING << "BehaviorType: " << getName() << " has no event by the id of " << id << "Search for EventID's default returns ZERO!!" <<std::endl;
	    return NULL;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Has                                      */

bool BehaviorType::hasEvent(std::string e)
{
	for(UInt32 i = 0; i < _bEvents.size(); i++)
	{
		if(_bEvents[i].compare(e) == 0)
		{
			return true;
		}
	}
	return false;
}

bool BehaviorType::hasEventLink(std::string e)
{
	for(UInt32 i = 0; i < _bEventLinks.size(); i++)
	{
		if(_bEventLinks[i].compare(e) == 0)
		{
			return true;
		}
	}
	return false;
}

bool BehaviorType::hasDependent(BehaviorType* d)
{
	for(UInt32 i = 0; i < _bDependencies.size(); i++)
	{
		if(_bDependencies[i] == d)
		{
			return true;
		}
	}
	return false;
}

bool BehaviorType::hasDependency(BehaviorType* d)
{
	for(UInt32 i = 0; i < _bDependents.size(); i++)
	{
		if(_bDependents[i] == d)
		{
			return true;
		}
	}
	return false;
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

void BehaviorType::registerType()
{
    BehaviorFactory::the()->registerType(this);
}

void BehaviorType::registerWithScene(Scene* scene)
{
//	scene = (Scene*)scene;
	if(scene != attachedScene)
	{
        _bActiveEventIDs.clear();
		for(UInt32 i = 0; i < _bEvents.size(); i++)
		{
            _bActiveEventIDs.push_back(scene->registerNewGenericMethod(_bEvents[i]));
		}
		attachedScene = scene;
	}

	scene->checkBehaviorInitialization();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BehaviorType::BehaviorType( const std::string &szName,
							FieldContainerType * bBehaviorFieldContainerType,
                            std::vector<std::string> eventSourceNames,
		                    std::vector<std::string> bEvents,
		                    std::vector<std::string> bEventLinks,
                            std::vector<std::string> bLuaCallbacks,
	                        BoostPath& FilePath) :
    Inherited        (szName.c_str(), 
                      "TypeBase"),

    _bInitialized     (false            ),

	behaviorFieldContainerType	(bBehaviorFieldContainerType),

    _pParent          (NULL             ),

	_bEvents		  (bEvents			),

	_bEventLinks	  (bEventLinks		),

    luaFunctionNames  (bLuaCallbacks    ),

    _bSourceContainers(eventSourceNames ),
	
	attachedScene	  (NULL             )
{
    if(!FilePath.string().empty())
    {
	    std::ifstream TheFile;
        TheFile.exceptions(std::fstream::failbit | std::fstream::badbit);

        try
        {
            TheFile.open(FilePath.string().c_str());
            if(TheFile)
            {
                std::ostringstream Code;
                Code << TheFile.rdbuf();
                TheFile.close();
                LuaManager::the()->runScript(Code.str());
            }
        }
        catch(std::fstream::failure &f)
        {
            SWARNING << "BehaviorType::Constructor(): Error reading file" << FilePath.string() << ": " << f.what() << std::endl;
        }
    }

    if(!(eventSourceNames.size() == bEventLinks.size() && bEventLinks.size() == bLuaCallbacks.size()))
    {
        SWARNING << "BehaviorType::Constructor(): There is not a one to one correspondance between the events, thier sources, and callbacks." << std::endl;
    }
}

BehaviorType BehaviorType::create(const std::string &szName,
                                  const std::string &type,
                                  const std::string &bEvents,
                                  const std::string &bEventLinks,
                                  const std::string &luaCallback,
                                  const std::string &StrFilePath)
{
    std::vector< std::string > evtSplitVec = std::vector<std::string>();
    std::vector< std::string > fcsrcSplitVec = std::vector<std::string>();
    std::vector< std::string > evtlkSplitVec = std::vector<std::string>();
    std::vector< std::string > luacSplitVec = std::vector<std::string>();
    
    OSG::BoostPath FilePath = OSG::BoostPath();
    
    if(!bEvents.empty())
    {
        boost::algorithm::split( evtSplitVec, bEvents, boost::algorithm::is_any_of(std::string(";")) );
    }
    
    if(luaCallback.empty())
    {
        if(!bEventLinks.empty())
        {
            std::vector< std::string > eventArgs = std::vector<std::string>();
            std::vector< std::string > eventDefs = std::vector<std::string>();
            
            std::string toParse;

            boost::algorithm::split( eventArgs, bEventLinks, boost::algorithm::is_any_of(std::string("|")) );

            for(OSG::UInt32 i(0); i < eventArgs.size(); ++i)
            {
                boost::algorithm::split( eventDefs, eventArgs[i], boost::algorithm::is_any_of(std::string(":")));
                
                toParse = eventDefs[0];

                boost::algorithm::trim(toParse);

                if(toParse.length() > 1 && (toParse[0] == '\"' || toParse[0] == '\'') && (toParse[toParse.length()-1] == '\"' || toParse[toParse.length()-1] == '\''))
                {
                    toParse = toParse.substr(1,toParse.length()-2);
                }
                else if((toParse[0] != '*'))
                {
                    SWARNING << "LUA: KabalaEngine.BehaviorType_create(): Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "The name must be encased in quotes." << OSG::endLog;
                    return OSG::BehaviorType(szName,NULL);
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
                    SWARNING << "LUA: KabalaEngine.BehaviorType_create(): Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "Use wilcards (*) in place of FieldContainerName to specify that this behavior is to listen to any behaviors that can provide that event." << OSG::endLog;
                    return OSG::BehaviorType(szName,NULL);
                }
            }
        }
    }
    else
    {
        if(!bEventLinks.empty())
        {
            std::vector< std::string > eventArgs = std::vector<std::string>();
            std::vector< std::string > eventDefs = std::vector<std::string>();
            
            std::string toParse;

            boost::algorithm::split( eventArgs, bEventLinks, boost::algorithm::is_any_of(std::string("|")) );

            for(OSG::UInt32 i(0); i < eventArgs.size(); ++i)
            {
                boost::algorithm::split( eventDefs, eventArgs[i], boost::algorithm::is_any_of(std::string(":")));
                
                toParse = eventDefs[0];

                boost::algorithm::trim(toParse);
                
                if(toParse.length() > 1 && (toParse[0] == '\"' || toParse[0] == '\'') && (toParse[toParse.length()-1] == '\"' || toParse[toParse.length()-1] == '\''))
                {
                    toParse = toParse.substr(1,toParse.length()-2);
                }
                else if((toParse[0] != '*'))
                {
                    SWARNING << "LUA: KabalaEngine.BehaviorType_create(): Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "The name must be encased in quotes." << OSG::endLog;
                    return OSG::BehaviorType(szName,NULL);
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
                    SWARNING << "LUA: KabalaEngine.BehaviorType_create(): Malformed linking string. Should be \'FieldContainerName:EventName:Callback|FieldContainerName:EventName:Callback|...\'" <<
                                "Use wilcards (*) in place of FieldContainerName to specify that this behavior is to listen to any behaviors that can provide that event." << OSG::endLog;
                    return OSG::BehaviorType(szName,NULL);
                }
            }
        }
    }
    
    if(!StrFilePath.empty())
    {
        FilePath = OSG::BoostPath(StrFilePath);
    }
    
    FieldContainerType* theType = FieldContainerFactory::the()->findType(type.c_str());

    if(theType == NULL)
    {
        SWARNING << "LUA: KabalaEngine.BehaviorType_create(): The type "<< type <<" could not be found." << OSG::endLog;
        return OSG::BehaviorType(szName,NULL);
    }

    return OSG::BehaviorType(szName,theType,fcsrcSplitVec,evtSplitVec,evtlkSplitVec,luacSplitVec,FilePath);
}

BehaviorType::BehaviorType(const BehaviorType &obj) :

     Inherited        (obj                   ),

    _bInitialized     (false                 ),

    _pParent          (obj._pParent          ),

    behaviorFieldContainerType	(obj.behaviorFieldContainerType),

	_bDependencies	  (obj._bDependencies	 ),

    _bEvents		  (obj._bEvents			 ),

	_bEventLinks	  (obj._bEventLinks		 ),
	
	attachedScene	  (NULL					 ),

    luaFunctionNames  (obj.luaFunctionNames  ),

    _bSourceContainers (obj._bSourceContainers),

	TheCode			  (obj.TheCode           )
{
    _bInitialized = true;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BehaviorType::~BehaviorType(void)
{
    if(GlobalSystemState != Shutdown)
    {
        terminate();
    }
}

/*-------------------------------------------------------------------------*/
/*                            Add / Sub                                    */

bool BehaviorType::isAbstract   (void) const
{
    return false;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void BehaviorType::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "BehaviorType: "
         << getCName()
         << ", Id: "       
         << getId()
         << ", parentP: " 
         << (_pParent ? _pParent->getCName() : "NONE")
         << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool BehaviorType::initialize(void)
{
    if(_bInitialized == true)
        return _bInitialized;

    _bInitialized = true;

    if(_bInitialized == false)
        return _bInitialized;

    if(_bInitialized == false)
        return _bInitialized;
    
    return _bInitialized;
}

void BehaviorType::terminate(void)
{
    _bInitialized = false;
}
