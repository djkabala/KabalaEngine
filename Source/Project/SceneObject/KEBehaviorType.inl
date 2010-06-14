/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *            Copyright (C) 2000-2002,2002 by the OpenSG Forum               *
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

#ifndef _KEBEHAVIORTYPE_INL_
#define _KEBEHAVIORTYPE_INL_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGMethodDescription.h"
#include "KEBehaviorType.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt16 BehaviorType::getGroupId (void) const
{
    return _uiGroupId;
}

inline
BehaviorType *BehaviorType::getParent(void) const
{
    return _pParent;
}

inline
MethodDescription *BehaviorType::getMethodDescription(UInt32 uiMethodId)
{
    MethodDescription *foundDesc = NULL;
    MethodDescription *testDesc;
    DescVecIt it;
    for ( it=_vDescVec.begin() ; it < _vDescVec.end(); it++ )
    {
        testDesc = *it;
        if(testDesc != NULL)
        {
            if(testDesc->getMethodId() == uiMethodId)
            {
                foundDesc = testDesc;
            }
        }
    }
    return foundDesc;
}

inline
const MethodDescription *BehaviorType::getMethodDescription(
    UInt32 uiMethodId) const
{
    MethodDescription *foundDesc = NULL;
    MethodDescription *testDesc;
    DescVecConstIt it;
    for ( it=_vDescVec.begin() ; it < _vDescVec.end(); it++ )
    {
        testDesc = *it;
        if(testDesc != NULL)
        {
            if(testDesc->getMethodId() == uiMethodId)
            {
                foundDesc = testDesc;
            }
        }
    }
    return foundDesc;
}

inline
MethodDescription *BehaviorType::findMethodDescription(
    const std::string &szMethodName)
{
    DescMapIt descIt = _mDescMap.find(szMethodName);

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
const MethodDescription *BehaviorType::findMethodDescription(
    const std::string &szMethodName) const
{
    DescMapConstIt descIt = _mDescMap.find(szMethodName);

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
UInt32 BehaviorType::getNumMethodDescs(void) const
{
    return _vDescVec.size();
}


/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool BehaviorType::isInitialized(void) const
{
    return _bInitialized;
}

inline
bool MethodDescriptionPLT::operator()(const MethodDescription *pElemDesc1, 
                const MethodDescription *pElemDesc2) const
{
    return pElemDesc1->getMethodId() < pElemDesc2->getMethodId();
}

OSG_END_NAMESPACE


#endif /* _KEBEHAVIORTYPE_INL_ */
