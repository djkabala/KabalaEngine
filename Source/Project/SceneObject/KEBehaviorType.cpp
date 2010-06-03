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

#include "OSGEventProducerType.h"
#include "OSGEventProducerFactory.h"

#include "OSGMethodDescription.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

inline
void EventProducerType::registerType(const std::string &szGroupName)
{
    EventProducerFactory::the()->registerType (this);

    //_uiGroupId = EventProducerFactory::the()->registerGroup(
        //!szGroupName.empty() ? szGroupName : _szName);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

EventProducerType::EventProducerType(const std::string &szName,
                                   const std::string &szParentName,
                                   const std::string &szGroupName,
                                   //PrototypeCreateF    fPrototypeCreate,
                                   InitEventProducerFunctor      fInitMethod,
                                   MethodDescription  **pDesc,
                                   UInt32              uiDescByteCounter) :
     Inherited        (szName.c_str(), 
                       szParentName.c_str()     ),
    _uiGroupId        (0                ),
    _szGroupName      (szGroupName      ),

    _bInitialized     (false            ),
    
    _pParent          (NULL             ),

    _szParentName     (szParentName     ),

    //_pPrototype       (NullFC           ),
    //_fPrototypeCreate (fPrototypeCreate ),

    _pDesc            (pDesc            ),
    _uiDescByteCounter(uiDescByteCounter),

    _mDescMap         (                 ),
    _vDescVec         (0                )
{
    registerType(szGroupName);

    if(!fInitMethod.empty())
        fInitMethod();
}

EventProducerType::EventProducerType(const EventProducerType &obj) :

     Inherited        (obj                   ),
    _uiGroupId        (obj._uiGroupId        ),
    _szGroupName      (obj._szGroupName      ),

    _bInitialized     (false                 ),
    
    _pParent          (obj._pParent          ),

    _szParentName     (obj._szParentName     ),

    //_pPrototype       (obj._pPrototype       ),
    //_fPrototypeCreate (obj._fPrototypeCreate ),

    _pDesc            (obj._pDesc            ),
    _uiDescByteCounter(obj._uiDescByteCounter),

    _mDescMap         (                      ),
    _vDescVec         (0                     )
{
    //if(_pPrototype != NullFC)
    //    addRefCP(_pPrototype);

    initMethods();
    initParentMethods();

    _bInitialized = true;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

EventProducerType::~EventProducerType(void)
{
    if(GlobalSystemState != Shutdown)
    {
        terminate();
    }
}

/*-------------------------------------------------------------------------*/
/*                            Add / Sub                                    */

UInt32 EventProducerType::addDescription(const MethodDescription &desc)
{
    UInt32            returnValue = 0;
    DescMapConstIt    descIt;
    DescVecIt         descVIt;

    MethodDescription  *pDesc;
    MethodDescription  *pNullDesc = NULL;

    //if(_bDescsAddable == false)
    //    return returnValue;

    descIt = _mDescMap.find(desc.getName());

    if(desc.isValid())
    {
        if(descIt == _mDescMap.end())
        {
            pDesc = new MethodDescription(desc);

            _mDescMap[pDesc->getName()] = pDesc;

            descVIt = std::find(_vDescVec.begin(),
                                _vDescVec.end(),
                                 pNullDesc);

            if(descVIt == _vDescVec.end())
            {
                _vDescVec.push_back(pDesc);

                returnValue = _vDescVec.size();
            }
            else
            {
                (*descVIt) = pDesc;

                returnValue  = descVIt - _vDescVec.begin();
                returnValue += 1;
            }
        }
        else
        {
            SWARNING << "ERROR: Double method description "
                        << "in " << _szName << " from "
                        << desc.getCName() << " (id:"
                        << desc.getMethodId() << ")" << std::endl;
        }
    }
    else
    {
        SWARNING << "ERROR: Invalid method description "
                    << "in " << _szName << " from "
                    << desc.getMethodId() << std::endl;
    }

    return returnValue;
}

bool EventProducerType::subDescription(UInt32 uiMethodId)
{
    MethodDescription  *pDesc = getMethodDescription(uiMethodId);
    DescMapIt          descMIt;
    DescVecIt          descVIt;
    bool               returnValue = true;

    //if(pDesc == NULL || _bDescsAddable == false)
    //    return false;

    descMIt = _mDescMap.find(pDesc->getName());

    if(descMIt != _mDescMap.end())
    {
        _mDescMap.erase(descMIt);
    }
    else
    {
        returnValue = false;
    }

    descVIt = std::find(_vDescVec.begin(), _vDescVec.end(), pDesc);

    if(descVIt != _vDescVec.end())
    {
        (*descVIt) = NULL;

        returnValue &= true;
    }
    else
    {
        returnValue = false;
    }

    delete pDesc;

    return returnValue;
}

bool EventProducerType::isAbstract   (void) const
{
    return false;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void EventProducerType::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "EventProducerType: "
         << getCName()
         << ", Id: "       
         << getId()
         << ", parentP: " 
         << (_pParent ? _pParent->getCName() : "NONE")
         << ", groupId: "  
         << _uiGroupId
         //<< ", abstract: "
         //<< ((_pPrototype != NullFC) ? "false" : "true")
         << " "
         << _vDescVec.size()
         << std::endl;

    for(UInt32 i = 0; i < _vDescVec.size(); i++)
    {
        SLOG << "Desc : " << _vDescVec[i]->getCName() << std::endl;
    }
}


/*-------------------------------------------------------------------------*/
/*                                Init                                     */

/*bool EventProducerType::initPrototype(void)
{
    _bInitialized = true;

    if(_fPrototypeCreate != NULL)
    {
        _pPrototype = _fPrototypeCreate();

        addRefCP(_pPrototype);
    }

    return _bInitialized;
}*/

bool EventProducerType::initMethods(void)
{
    UInt32    i;
    DescMapIt descIt;

    _bInitialized = true;

	if(_pDesc == NULL)
		return true;

    for(i = 0; i < _uiDescByteCounter / sizeof(MethodDescription *); i++)
    {
        if(_pDesc[i]->isValid())
        {
            descIt = _mDescMap.find(_pDesc[i]->getName());

            if(descIt == _mDescMap.end())
            {
                _mDescMap[_pDesc[i]->getName()] = _pDesc[i];

                _vDescVec.push_back(_pDesc[i]);
            }
            else
            {
                SWARNING << "ERROR: Double method description "
                            << "in " << _szName << " from "
                            << _pDesc[i]->getName() << " (id:"
                            << _pDesc[i]->getMethodId() << ")" << std::endl;

                _bInitialized = false;
            }
        }
        else
        {
            SWARNING << "ERROR: Invalid method description "
                        << "in " << _szName << "from "
                        << (_pDesc[i]?_pDesc[i]->getMethodId():0) << std::endl;

            _bInitialized = false;
        }

    }

    std::sort(_vDescVec.begin(), _vDescVec.end(), MethodDescriptionPLT());

    return _bInitialized;
}

bool EventProducerType::initParentMethods(void)
{
    DescMapIt dPIt;

    _bInitialized = true;

    if(!_szParentName.empty())
    {
        _pParent =
            dynamic_cast<EventProducerType*>(EventProducerFactory::the()->findType(_szParentName.c_str()));

        if(_pParent != NULL)
        {
            _bInitialized = _pParent->initialize();

            if(_bInitialized == false)
            {
                return _bInitialized;
            }

            for(  dPIt  = _pParent->_mDescMap.begin();
                  dPIt != _pParent->_mDescMap.end();
                ++dPIt)
            {
                if(_mDescMap.find((*dPIt).first) == _mDescMap.end())
                {
                    _mDescMap[(*dPIt).first] = (*dPIt).second;
                }
                else
                {
                    SWARNING << "ERROR: Can't add method "
                                << "description a second time: "
                                << (*dPIt).first
                                << " to producer of type " << getCName() << std::endl;
                }
            }

            _vDescVec.insert(_vDescVec.end(),
                             _pParent->_vDescVec.begin(),
                             _pParent->_vDescVec.end());

        }
        else
        {
            SWARNING << "ERROR: Can't find producer with "
                        << "name " << _szParentName
                        << " to set as parent of producer type " << getCName()
                        <<  std::endl;

            _bInitialized = false;
        }
    }

    return _bInitialized;
}

bool EventProducerType::initialize(void)
{
    if(_bInitialized == true)
        return _bInitialized;

    _bInitialized = initParentMethods();

    if(_bInitialized == false)
        return _bInitialized;

    _bInitialized = initMethods      ();

    if(_bInitialized == false)
        return _bInitialized;

    //_bInitialized = initPrototype   ();

    //if(_bInitialized == false)
    //    return _bInitialized;

    //FDEBUG ( ( "init EventProducerType %s (%d)\n",
               //_szName, int(_bInitialized) ));
    
    return _bInitialized;
}

void EventProducerType::terminate(void)
{
    UInt32 i;

    //subRefCP(_pPrototype);

    _bInitialized = false;

    for(i = 0; i < _uiDescByteCounter / sizeof(MethodDescription *); i++)
    {
        delete _pDesc[i];
    }
}

