/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "KEBehaviorType.h"
#include "KEBehaviorFactory.h"
#include "Project/Scene/KEScene.h"

#include "OSGMethodDescription.h"
#include "OSGLog.h"
#include "OSGTypeBase.h"

#include "OSGFilePathAttachment.h"
#include "OSGContainerUtils.h"
#include <fstream>
#include <sstream>


OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*-------------------------------------------------------------------------*/
/*                                Find                                     */

UInt32 BehaviorType::findEventID(std::string eventName)
{
	if(_bEvents.empty())
	{
		SWARNING << "BehaviorType: " << _bName << " has not been registered. Search for EventID's default returns ZERO!!" << std::endl;
		return 0;
	}
	for(UInt32 i = 0; _bEvents.size() > i; i++)
	{
		if(_bEvents[i] == eventName)
		{
			return _bActiveEventIDs[i];
		}
	}

	SWARNING << "BehaviorType: " << _bName << " has no event by the name of " << eventName << "Search for EventID's default returns ZERO!!" <<std::endl;
	return 0;
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
	scene = (Scene*)scene;
	if(scene != attachedScene)
	{
		for(UInt32 i = 0; _bEvents.size(); i++)
		{
			_bActiveEventIDs[i] = scene->registerNewGenericMethod(_bEvents[i]);
		}
		attachedScene = scene;
	}

	scene->checkBehaviorInitialization();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BehaviorType::BehaviorType(const std::string &szName,
						   const std::string &szParentName,
						   std::vector<std::string> bEvents,
						   std::vector<std::string> bEventLinks,
						   BoostPath& FilePath) :
    Inherited        (szName.c_str(), 
                       szParentName.c_str()     ),

    _bInitialized     (false            ),

    _pParent          (NULL             ),

    _szParentName     (szParentName     ),

	_bEvents		  (bEvents			),

	_bEventLinks	  (bEventLinks		),

	_bName			  (szName			),
	
	attachedScene	  (NULL             )
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

            setCode(Code.str());
        }
    }
    catch(std::fstream::failure &f)
    {
        SWARNING << "BehaviorType::Constructor(): Error reading file" << FilePath.string() << ": " << f.what() << std::endl;
    }
}

BehaviorType::BehaviorType(const BehaviorType &obj) :

     Inherited        (obj                   ),

    _bInitialized     (false                 ),

    _pParent          (obj._pParent          ),

    _szParentName     (obj._szParentName     ),

	_bDependencies	  (obj._bDependencies	 ),

	_bName			  (obj._bName			 ),
	
	attachedScene	  (NULL					 ),

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

const Char8* BehaviorType::getChar8Name(void)
{
	return static_cast<const Char8*>(_bName.c_str());
}