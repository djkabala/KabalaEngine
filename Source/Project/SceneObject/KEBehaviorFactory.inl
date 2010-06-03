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
void EventProducerFactory::setMapper(EventProducerMapper *pMapper)
{
    _pMapper = pMapper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
EventProducerPtr EventProducerFactory::getContainer(
    UInt32 uiContainerId) const
{
    EventProducerPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pEventProducerStore->size())
    {
        returnValue = (*_pEventProducerStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

inline
EventProducerPtr EventProducerFactory::getMappedContainer(
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
UInt32 EventProducerFactory::registerEventProducer(
    const EventProducerPtr &pEventProducer)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pEventProducerStore == NULL)
    {
        _pEventProducerStore = new EventProducerStore;

        _pEventProducerStore->push_back(NullFC);
    }

    _pEventProducerStore->push_back(pEventProducer);

    returnValue = _pEventProducerStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

inline
bool EventProducerFactory::unregisterEventProducer(
    const EventProducerPtr &pEventProducer)
{
    if(pEventProducer == NullFC)
        return false;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pEventProducerStore != NULL)
    {
#ifdef OSG_DEBUG
        if (pEventProducer.getEventProducerId() >=
                    (*_pEventProducerStore).size())
        {
            FWARNING(("EventProducerFactory::unregisterEventProducer:"
                "id %d inconsistent with store size %d!\n", 
                pEventProducer.getEventProducerId(), 
                (*_pEventProducerStore).size() ));   
            return true;         
        }
        else
#endif

        (*_pEventProducerStore)[pEventProducer.getEventProducerId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
    
    return false;
}

/*-------------------------------------------------------------------------*/
/*                            Invalid Pointer                              */

inline
void EventProducerFactory::setThrowInvalidPointerException(bool s)
{
#ifndef OSG_INVALID_PTR_CHECK
    FFATAL(("EventProducerFactory::setThrowInvalidPointerException: invalid pointer check is not enabled, use the 'invalid_pointer_check' option in the scons build system!\n"));
#else
    _throw_invalid_pointer_exception = s;
#endif
}

inline
bool EventProducerFactory::getThrowInvalidPointerException(void) const
{
    return _throw_invalid_pointer_exception;
}

inline
void EventProducerFactory::checkThrowInvalidPointerException(void) const
{
    if(!_throw_invalid_pointer_exception)
        return;

    throw InvalidPointerException();
}

OSG_END_NAMESPACE

#endif /* _OSGEVENTPRODUCERFACTORYIMPL_INL_ */
