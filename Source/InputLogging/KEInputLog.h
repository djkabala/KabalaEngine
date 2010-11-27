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

#ifndef _KEINPUTLOG_H_
#define _KEINPUTLOG_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEConfig.h"

#include <OpenSG/OSGPathFields.h>
#include <OpenSG/OSGEventDetailsFields.h>
#include <OpenSG/OSGWindowEventProducerFields.h>
#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGLock.h>


#include <boost/shared_ptr.hpp>
#include <sstream>

OSG_BEGIN_NAMESPACE

/*! \brief InputLog class. See \ref 
           PageKabalaEngineInputLog for a description.
*/

class InputLog;
typedef boost::shared_ptr<InputLog> InputLogPtr;

class KE_KABALAENGINE_DLLMAPPING InputLog
{
  private:
    /*==========================  PUBLIC  =================================*/
  public:
      static InputLogPtr create(void);

      void setLogFile(const BoostPath& LogFilePath);
      const BoostPath& getLogFile(void) const;

      void start(void);
      void pause(void);
      void unpause(void);
      void stop(void);
      bool logging(void) const;
      bool paused(void) const;

      void setEventProducer(WindowEventProducer* const Producer);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~InputLog(void); 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */


    /*! \}                                                                 */

    void handleInputEvent(EventDetails* const details,
                          const EventDescription* desc);

    std::vector<boost::signals2::connection> _InputConnections;

    void pushToStream(std::ostream& stream,
                    EventDetails* const Details,
                    const EventDescription* EventDesc);

    static void mainWritingLoop(void* args);

    void openLogFile(void);
    void closeLogFile(void);

    BoostPath _LogFilePath;
    WindowEventProducerRecPtr _Producer;
    std::ostringstream _BufferedEventLog;
    UInt32 _FlushBufferSize;

    ThreadRefPtr _FileWritingThread;

    bool _Paused;
    bool _Logging;
    LockRefPtr _ReadWriteLock;
    /*==========================  PRIVATE  ================================*/
  private:

    void operator =(const InputLog &source);
    InputLog(void);
    InputLog(const InputLog &source);
};

OSG_END_NAMESPACE

#include "KEInputLog.inl"

#endif /* _KEINPUTLOG_H_ */
