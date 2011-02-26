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

#include "Application/Logging/KELogEventDetails.h"
#include "KEVersion.h"
#include <OpenSG/OSGPlatformUtils.h>
#include <OpenSG/OSGWindowEventProducer.h> // MainWindowEventProducer type

OSG_BEGIN_NAMESPACE

inline
ApplicationSettings &MainApplication::getSettings(void)
{
    return _Settings;
}

inline
const ApplicationSettings &MainApplication::getSettings(void) const
{
    return _Settings;
}

inline
BoostPath  &MainApplication::getSettingsLoadFile(void)
{
    return _SettingsPath;
}

inline
const BoostPath  &MainApplication::getSettingsLoadFile(void) const
{
    return _SettingsPath;
}

inline
WindowEventProducer* MainApplication::getMainWindow(void)
{
    return _MainWindow;
}

inline
const WindowEventProducer* MainApplication::getMainWindow(void) const
{
    return _MainWindow;
}

inline
Project* MainApplication::getProject(void)
{
    return _Project;
}

inline
const Project* MainApplication::getProject(void) const
{
    return _Project;
}

#ifdef BUILD_WITH_WORLD_BUILDER
inline
ApplicationMode* MainApplication::getBuilderMode(void)
{
    return _BuilderMode;
}

inline
const ApplicationMode*  MainApplication::getBuilderMode(void) const
{
    return _BuilderMode;
}
#endif

inline
ApplicationMode* MainApplication::getPlayerMode(void)
{
    return _PlayerMode;
}

inline
const ApplicationMode* MainApplication::getPlayerMode(void) const
{
    return _PlayerMode;
}

inline
ApplicationMode* MainApplication::getStartScreenMode(void)
{
    return _StartScreenMode;
}

inline
const ApplicationMode* MainApplication::getStartScreenMode(void) const
{
    return _StartScreenMode;
}

inline
ApplicationMode* MainApplication::getCurrentMode(void)
{
    return _CurrentMode;
}

inline
const ApplicationMode* MainApplication::getCurrentMode(void) const
{
    return _CurrentMode;
}

//! access the producer type of the class
inline
const EventProducerType &MainApplication::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 MainApplication::getProducerClassTypeId(void)
{
    return _producerType.getId();
}
inline
boost::signals2::connection MainApplication::attachActivity(UInt32 eventId,
                                           Activity* TheActivity)
{
    return connectLog(eventId, boost::bind(&Activity::eventProduced, TheActivity, _1, _2) );
}

inline
UInt32 MainApplication::getNumProducedEvents(void) const
{
    return getProducerType().getNumEventDescs();
}

inline
const EventDescription *MainApplication::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return getProducerType().findEventDescription(ProducedEventName);
}

inline
const EventDescription *MainApplication::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getEventDescription(ProducedEventId);
}

inline
UInt32 MainApplication::getProducedEventId(const Char8 *ProducedEventName) const
{
    return getProducerType().getProducedEventId(ProducedEventName);
}

inline
boost::signals2::connection  MainApplication::connectLog(const LogEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _LogEvent.connect(listener, at);
}

inline
boost::signals2::connection  MainApplication::connectLog(const LogEventType::group_type &group,
                                                    const LogEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _LogEvent.connect(group, listener, at);
}

inline
void  MainApplication::disconnectLog(const LogEventType::group_type &group)
{
    _LogEvent.disconnect(group);
}

inline
void  MainApplication::disconnectAllSlotsLog(void)
{
    _LogEvent.disconnect_all_slots();
}

inline
bool  MainApplication::isEmptyLog(void) const
{
    return _LogEvent.empty();
}

inline
UInt32  MainApplication::numSlotsLog(void) const
{
    return _LogEvent.num_slots();
}

inline
BoostPath MainApplication::getUserAppDataDir(void) const
{
    return BoostPath(getPlatformUserAppDataDir()
                   / BoostPath("KabalaEngine")
                   / BoostPath(getKabalaEngineVersion()));
}

inline
BoostPath MainApplication::getLoggingDir(void) const
{
    return BoostPath(getUserAppDataDir()
                   / BoostPath("Logs"));
}

inline
BoostPath MainApplication::getLoggingFilePath(void) const
{
    return _LogFilePath;
}

inline
bool MainApplication::getLoggingEnabled(void) const
{
    return _EnableLogging;
}

inline
bool MainApplication::getLoggingToFile(void) const
{
    return _LogToFile;
}


inline
Thread*  MainApplication::getApplicationThread(void)
{
    return _ApplicationThread;
}

inline
const Thread*  MainApplication::getApplicationThread(void) const
{
    return _ApplicationThread;
}

inline
Thread*  MainApplication::getRenderThread(void)
{
    return _RenderThread;
}

inline
const Thread*  MainApplication::getRenderThread(void) const
{
    return _RenderThread;
}

inline
Thread*  MainApplication::getLoadingThread(void)
{
    return _LoadingThread;
}

inline
const Thread*  MainApplication::getLoadingThread(void) const
{
    return _LoadingThread;
}

OSG_END_NAMESPACE

