/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGEVENTPRODUCERFACTORYIMPL_INL_
#define _OSGEVENTPRODUCERFACTORYIMPL_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              Mapper                                     */

inline
void BehaviorFactory::setMapper(EventProducerMapper *pMapper)
{
    _pMapper = pMapper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
BehaviorPtr BehaviorFactoryBase::getContainer(
    UInt32 uiContainerId) const
{
    BehaviorPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pBehaviorStore->size())
    {
        returnValue = (*_pBehaviorStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

inline
BehaviorPtr BehaviorFactory::getMappedContainer(
    UInt32 uiContainerId) const
{
    if(_pMapper != NULL)
    {
        return getContainer(_pMapper->map(uiContainerId));
    }
    else
    {
        return getContainer(uiContainerId);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

inline
UInt32 BehaviorFactory::registerBehavior(
    const BehaviorPtr &pBehavior)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pBehaviorStore == NULL)
    {
        _pBehaviorStore = new BehaviorStore;

        _pBehaviorStore->push_back(NullFC);
    }

    _pBehaviorStore->push_back(pBehavior);

    returnValue = _pBehaviorStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

inline
bool BehaviorFactory::unregisterBehavior(
    const BehaviorPtr &pBehavior)
{
    if(pBehavior == NullFC)
        return false;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pBehaviorStore != NULL)
    {
#ifdef OSG_DEBUG
        if (pBehavior.getBehaviorId() >=
                    (*_pBehaviorStore).size())
        {
            FWARNING(("EventProducerFactory::unregisterEventProducer:"
                "id %d inconsistent with store size %d!\n", 
                _pBehavior.getBehaviorId(), 
                (*_pBehaviorStore).size() ));   
            return true;         
        }
        else
#endif

        (*_pBehaviorStore)[pBehavior.getBehaviorId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
    
    return false;
}

/*-------------------------------------------------------------------------*/
/*                            Invalid Pointer                              */

inline
void BehaviorFactory::setThrowInvalidPointerException(bool s)
{
#ifndef OSG_INVALID_PTR_CHECK
    FFATAL(("EventProducerFactory::setThrowInvalidPointerException: invalid pointer check is not enabled, use the 'invalid_pointer_check' option in the scons build system!\n"));
#else
    _throw_invalid_pointer_exception = s;
#endif
}

inline
bool BehaviorFactory::getThrowInvalidPointerException(void) const
{
    return _throw_invalid_pointer_exception;
}

inline
void BehaviorFactory::checkThrowInvalidPointerException(void) const
{
    if(!_throw_invalid_pointer_exception)
        return;

    throw InvalidPointerException();
}

OSG_END_NAMESPACE

#endif /* _OSGEVENTPRODUCERFACTORYIMPL_INL_ */
