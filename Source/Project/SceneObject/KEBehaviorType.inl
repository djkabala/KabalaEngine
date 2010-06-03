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

#ifndef _OSGEVENTPRODUCERTYPE_INL_
#define _OSGEVENTPRODUCERTYPE_INL_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGMethodDescription.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt16 EventProducerType::getGroupId (void) const
{
    return _uiGroupId;
}

inline
EventProducerType *EventProducerType::getParent(void) const
{
    return _pParent;
}

inline
MethodDescription *EventProducerType::getMethodDescription(UInt32 uiMethodId)
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
const MethodDescription *EventProducerType::getMethodDescription(
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
MethodDescription *EventProducerType::findMethodDescription(
    const std::string &szMethodName)
{
    DescMapIt descIt = _mDescMap.find(szMethodName);

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
const MethodDescription *EventProducerType::findMethodDescription(
    const std::string &szMethodName) const
{
    DescMapConstIt descIt = _mDescMap.find(szMethodName);

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
UInt32 EventProducerType::getNumMethodDescs(void) const
{
    return _vDescVec.size();
}


/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool EventProducerType::isInitialized(void) const
{
    return _bInitialized;
}

inline
bool EventProducerType::isDerivedFrom(const TypeBase &other) const
{
    return Inherited::isDerivedFrom(other);
}

inline
bool EventProducerType::isDerivedFrom(const EventProducerType &other) const
{
    if(_uiTypeId == other._uiTypeId)
    {
        return true;
    }
    else
    {
        EventProducerType *pCurrType   = _pParent;
        while(pCurrType != NULL)
        {
            if(other._uiTypeId == pCurrType->_uiTypeId)
            {
                return true;
            }
            pCurrType = pCurrType->_pParent;
        }
    }
    return false;
}

inline
bool MethodDescriptionPLT::operator()(const MethodDescription *pElemDesc1, 
                const MethodDescription *pElemDesc2) const
{
    return pElemDesc1->getMethodId() < pElemDesc2->getMethodId();
}

OSG_END_NAMESPACE


#endif /* _OSGEVENTPRODUCERTYPE_INL_ */
