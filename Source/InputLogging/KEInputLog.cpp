/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "KEInputLog.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/convenience.hpp>
#include <OpenSG/OSGWindowEventProducer.h>

#include <fstream>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class InputLog
The Main Application. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

InputLogPtr InputLog::create(void)
{
    return InputLogPtr(new InputLog);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void InputLog::setLogFile(const BoostPath& LogFilePath)
{
    _LogFilePath = LogFilePath;
}

const BoostPath& InputLog::getLogFile(void) const
{
    return _LogFilePath;
}

void InputLog::start(void)
{
    ////Create the writting thread
    //_FileWritingThread = dynamic_pointer_cast<Thread>(ThreadManager::the()->getThread("__KABALA_ENGINE_INPUT_LOGGING_THREAD", true));
    //_ReadWriteLock = Lock::get(NULL, true);
    //
    //_Logging = true;

    ////Start the render thread on aspect 1
    //_FileWritingThread->runFunction(InputLog::mainWritingLoop, 1, this);
}

void InputLog::pause(void)
{
    //_Paused = true;
}

void InputLog::unpause(void)
{
    //_Paused = false;
}

void InputLog::stop(void)
{
    //Stop the Writing thread
    //_Logging = false;
}

bool InputLog::logging(void) const
{
    return _Logging;
}

bool InputLog::paused(void) const
{
    return _Paused;
}

void InputLog::setEventProducer(WindowEventProducer* const Producer)
{
    //_Producer = Producer;

    //for(UInt32 i(0) ; i<_InputConnections.size() ; ++i)
    //{
    //    _InputConnections[i].disconnect();
    //}
    //_InputConnections.clear();

    //if(_Producer != NULL)
    //{
    //    const EventDescription* MouseClickedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseClickedEventId);
    //    const EventDescription* MouseEnteredDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseEnteredEventId);
    //    const EventDescription* MouseExitedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseExitedEventId);
    //    const EventDescription* MousePressedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MousePressedEventId);
    //    const EventDescription* MouseReleasedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseReleasedEventId);
    //    const EventDescription* MouseMovedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseMovedEventId);
    //    const EventDescription* MouseDraggedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseDraggedEventId);
    //    const EventDescription* MouseWheelMovedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::MouseWheelMovedEventId);
    //    const EventDescription* KeyPressedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::KeyPressedEventId);
    //    const EventDescription* KeyReleasedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::KeyReleasedEventId);
    //    const EventDescription* KeyTypedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::KeyTypedEventId);
    //    const EventDescription* WindowOpenedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowOpenedEventId);
    //    const EventDescription* WindowClosingDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowClosingEventId);
    //    const EventDescription* WindowClosedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowClosedEventId);
    //    const EventDescription* WindowIconifiedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowIconifiedEventId);
    //    const EventDescription* WindowDeiconifiedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowDeiconifiedEventId);
    //    const EventDescription* WindowActivatedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowActivatedEventId);
    //    const EventDescription* WindowDeactivatedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowDeactivatedEventId);
    //    const EventDescription* WindowEnteredDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowEnteredEventId);
    //    const EventDescription* WindowExitedDesc = _Producer->getProducerType().getEventDescription(WindowEventProducer::WindowExitedEventId);

    //    //_InputConnections.push_back(_Producer->connectMouseClicked     (boost::bind(&InputLog::handleInputEvent, this, _1, MouseClickedDesc)));
    //    //_InputConnections.push_back(_Producer->connectMouseEntered     (boost::bind(&InputLog::handleInputEvent, this, _1, MouseEnteredDesc)));
    //    //_InputConnections.push_back(_Producer->connectMouseExited      (boost::bind(&InputLog::handleInputEvent, this, _1, MouseExitedDesc)));
    //    _InputConnections.push_back(_Producer->connectMousePressed     (boost::bind(&InputLog::handleInputEvent, this, _1, MousePressedDesc)));
    //    _InputConnections.push_back(_Producer->connectMouseReleased    (boost::bind(&InputLog::handleInputEvent, this, _1, MouseReleasedDesc)));
    //    _InputConnections.push_back(_Producer->connectMouseMoved       (boost::bind(&InputLog::handleInputEvent, this, _1, MouseMovedDesc)));
    //    _InputConnections.push_back(_Producer->connectMouseDragged     (boost::bind(&InputLog::handleInputEvent, this, _1, MouseDraggedDesc)));
    //    _InputConnections.push_back(_Producer->connectMouseWheelMoved  (boost::bind(&InputLog::handleInputEvent, this, _1, MouseWheelMovedDesc)));
    //    _InputConnections.push_back(_Producer->connectKeyPressed       (boost::bind(&InputLog::handleInputEvent, this, _1, KeyPressedDesc)));
    //    _InputConnections.push_back(_Producer->connectKeyReleased      (boost::bind(&InputLog::handleInputEvent, this, _1, KeyReleasedDesc)));
    //    _InputConnections.push_back(_Producer->connectKeyTyped         (boost::bind(&InputLog::handleInputEvent, this, _1, KeyTypedDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowOpened     (boost::bind(&InputLog::handleInputEvent, this, _1, WindowOpenedDesc)));
    //    //_InputConnections.push_back(_Producer->connectWindowClosing    (boost::bind(&InputLog::handleInputEvent, this, _1, WindowClosingDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowClosed     (boost::bind(&InputLog::handleInputEvent, this, _1, WindowClosedDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowIconified  (boost::bind(&InputLog::handleInputEvent, this, _1, WindowIconifiedDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowDeiconified(boost::bind(&InputLog::handleInputEvent, this, _1, WindowDeiconifiedDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowActivated  (boost::bind(&InputLog::handleInputEvent, this, _1, WindowActivatedDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowDeactivated(boost::bind(&InputLog::handleInputEvent, this, _1, WindowDeactivatedDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowEntered    (boost::bind(&InputLog::handleInputEvent, this, _1, WindowEnteredDesc)));
    //    _InputConnections.push_back(_Producer->connectWindowExited     (boost::bind(&InputLog::handleInputEvent, this, _1, WindowExitedDesc)));
    //}
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void InputLog::handleInputEvent(EventDetails* const details,
                                const EventDescription* desc)
{
    //if(!paused())
    //{
    //    _ReadWriteLock->acquire();

    //    pushToStream(_BufferedEventLog,details,desc);

    //    _ReadWriteLock->release();
    //}
}


void InputLog::pushToStream(std::ostream& stream,
                            EventDetails* const Details,
                            const EventDescription* EventDesc)
{
    //OutStream OSGOutputStream(stream);
    //GetFieldHandlePtr TheFieldHandle;

    ////Write all of the Fields
    //FieldContainerType& TheFCType(Details->getType());
    //UInt32 NumFields(TheFCType.getNumFieldDescs());

    //stream << "    <" << EventDesc->getName() << " ";
    //for(UInt32 i(1) ; i<NumFields+1 ; ++i)
    //{
    //    TheFieldHandle = Details->getField(i);

    //    if(TheFieldHandle != NULL &&
    //        TheFieldHandle->getClass() == FieldType::ValueField)
    //    {
    //        stream << Details->getFieldDescription(i)->getCName() << "=\"";
    //        TheFieldHandle->pushValueToStream(OSGOutputStream);
    //        stream << "\" ";
    //    }
    //}
    //stream << "/>" << std::endl;
}


void InputLog::openLogFile(void)
{
}

void InputLog::closeLogFile(void)
{
}

void InputLog::mainWritingLoop(void* args)
{
//    InputLog* Logger= reinterpret_cast<InputLog*>(args);
//
//    Logger->_ReadWriteLock->acquire();
//    Logger->_BufferedEventLog << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
//    Logger->_BufferedEventLog << "<InputCapture>" << std::endl;
//    Logger->_BufferedEventLog << "    <Desktop Size=\"" << Logger->_Producer->getDesktopSize().x() << " " << Logger->_Producer->getDesktopSize().y() << "\" />" << std::endl;
//    Logger->_BufferedEventLog << "    <Window Position=\"" << Logger->_Producer->getPosition().x() << " " << Logger->_Producer->getPosition().y() << "\""
//            << " Size=\"" << Logger->_Producer->getSize().x() << " " << Logger->_Producer->getSize().y()  << "\" />" << std::endl;
//    Logger->_ReadWriteLock->release();
//
//    while(Logger->logging())
//    {
//        Logger->_ReadWriteLock->acquire();
//        if(Logger->paused() || Logger->_BufferedEventLog.str().size() < Logger->_FlushBufferSize)
//        {
//            Logger->_ReadWriteLock->release();
//            //Release the processor
//#ifdef OSG_USE_WINTHREADS
//            SwitchToThread();
//#endif
//#ifdef OSG_USE_PTHREADS
//            sched_yield();
//#endif
//        }
//        else
//        {
//            Logger->_ReadWriteLock->release();
//
//            //Open the file for appending
//            std::ofstream LogFile(Logger->getLogFile().string().c_str(), std::ios_base::app);
//            
//            Logger->_ReadWriteLock->acquire();
//            
//            //Write buffer
//            LogFile << Logger->_BufferedEventLog.str();
//            Logger->_BufferedEventLog.str("");
//
//            Logger->_ReadWriteLock->release();
//
//            LogFile.close();
//        }
//    }
//    //Open the file for appending
//    std::ofstream LogFile(Logger->getLogFile().string().c_str(), std::ios_base::app);
//
//    Logger->_ReadWriteLock->acquire();
//    
//    //Write buffer
//    Logger->_BufferedEventLog << "</InputCapture>" << std::endl;
//
//    LogFile << Logger->_BufferedEventLog.str();
//    Logger->_BufferedEventLog.str("");
//
//    Logger->_ReadWriteLock->release();
//
//    LogFile.close();
}

/*----------------------- constructors & destructors ----------------------*/

InputLog::InputLog(void) :
    _Paused(false),
    _Logging(false),
    _FlushBufferSize(2000)
{
}

InputLog::~InputLog(void)
{
}

/*----------------------------- class specific ----------------------------*/

