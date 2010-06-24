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

#include "OSGMethodDescription.h"
#include "OSGLog.h"
#include "OSGTypeBase.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                              Register                                   */


void BehaviorType::registerType()
{
    BehaviorFactory::the()->registerType(this);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BehaviorType::BehaviorType(const std::string &szName,
                                   const std::string &szParentName,
								   std::vector<BehaviorType> bDependencies) :
     Inherited        (szName.c_str(), 
                       szParentName.c_str()     ),

    _bInitialized     (false            ),

    _pParent          (NULL             ),

    _szParentName     (szParentName     ),

	_bDependencies	  (bDependencies	),

	_bName			  (szName			)
{
}

BehaviorType::BehaviorType(const BehaviorType &obj) :

     Inherited        (obj                   ),

    _bInitialized     (false                 ),

    _pParent          (obj._pParent          ),

    _szParentName     (obj._szParentName     ),

	_bDependencies	  (obj._bDependencies	 ),

	_bName			  (obj._bName			 )
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
    UInt32 i;

    _bInitialized = false;
}

