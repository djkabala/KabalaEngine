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

#ifndef _KEMAINAPPLICATION_H_
#define _KEMAINAPPLICATION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGWindowFields.h>
#include <boost/program_options.hpp>
#include "Application/KEApplicationSettings.h" // Settings type
#include <OpenSG/OSGBoostPathFields.h> // SettingsLoadFile type
#include <OpenSG/OSGWindowEventProducerFields.h> // MainWindowEventProducer type
#include <OpenSG/OSGWindowEventDetailsFields.h> // MainWindowEventProducer type
#include "Project/KEProjectFields.h" // Project type
#include "Project/Scene/KESceneFields.h" // Scene type
#include "Application/KEApplicationModeFields.h"
#include "Application/Logging/KELogEventDetailsFields.h"

#include <boost/function.hpp>
#include "OSGEventDescription.h"
#include "OSGConsumableEventCombiner.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGEventProducerType.h"
#include "OSGActivity.h"

#include <boost/date_time/posix_time/posix_time.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief MainApplication class. See \ref 
           PageKabalaEngineMainApplication for a description.
*/

class KE_KABALAENGINE_DLLMAPPING MainApplication
{
  private:
    /*==========================  PUBLIC  =================================*/
      static MainApplication* _Instance;
  public:

      static MainApplication* the(void);

    /*! \}                                                                 */

	Int32 run(int argc, char **argv);
	void exit(void);

	void printCommandLineHelp(void) const;

	void saveSettings(const BoostPath& SettingsFile);
	void loadSettings(const BoostPath& SettingsFile);

	void saveProject(const BoostPath& ProjectFile);
	void loadProject(const BoostPath& ProjectFile);

	void attachBuilder(void);

	void attachPlayer(void);

	void attachStartScreen(void);

           ApplicationSettings      &getSettings       (void);
     const ApplicationSettings      &getSettings       (void) const;
           BoostPath                &getSettingsLoadFile(void);
     const BoostPath                &getSettingsLoadFile(void) const;
           WindowEventProducer* getMainWindow(void);
     const WindowEventProducer* getMainWindow(void) const;
           Project*          getProject        (void);
     const Project*          getProject        (void) const;
           ApplicationMode*  getBuilderMode    (void);
     const ApplicationMode*  getBuilderMode    (void) const;
           ApplicationMode*  getPlayerMode     (void);
     const ApplicationMode*  getPlayerMode     (void) const;
           ApplicationMode*  getStartScreenMode(void);
     const ApplicationMode*  getStartScreenMode(void) const;
           ApplicationMode*  getCurrentMode    (void);
     const ApplicationMode*  getCurrentMode    (void) const;
     
     void setSettings       ( const ApplicationSettings &value );
     void setSettingsLoadFile( const BoostPath &value );
     void setMainWindow( WindowEventProducer* const value );
     void setProject        ( Project* const value );
     void setBuilderMode    ( ApplicationMode* const value );
     void setPlayerMode     ( ApplicationMode* const value );
     void setStartScreenMode( ApplicationMode* const value );
     void setCurrentMode    ( ApplicationMode* const value );

     static const BoostPath EngineAppDataDirectory;
    typedef LogEventDetails LogEventDetailsType;
    typedef boost::signals2::signal<void (LogEventDetailsType* const, UInt32), ConsumableEventCombiner> LogEventType;

    enum
    {
        LogEventId = 1,
        NextEventId     = LogEventId            + 1
    };
    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 
    virtual const EventProducerType &getProducerType(void) const; 

    boost::signals2::connection          attachActivity(UInt32 eventId,
                                                       Activity* TheActivity);
    UInt32                   getNumProducedEvents(void)          const;
    const EventDescription *getProducedEventDescription(const   Char8 *ProducedEventName) const;
    const EventDescription *getProducedEventDescription(UInt32  ProducedEventId) const;
    UInt32                   getProducedEventId(const            Char8 *ProducedEventName) const;

    boost::signals2::connection connectLog(const LogEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    boost::signals2::connection connectLog(const LogEventType::group_type &group,
                                                       const LogEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    void   disconnectLog       (const LogEventType::group_type &group);
    void   disconnectAllSlotsLog(void);
    bool   isEmptyLog          (void) const;
    UInt32 numSlotsLog         (void) const;

    BoostPath getUserAppDataDir(void) const;
    BoostPath getLoggingDir(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

     ApplicationSettings        _Settings;
     BoostPath                  _SettingsPath;
     WindowEventProducerRefPtr  _MainWindow;
     ProjectRefPtr              _Project;
     ApplicationModeRefPtr      _BuilderMode;
     ApplicationModeRefPtr      _StartScreenMode;
     ApplicationModeRefPtr      _PlayerMode;
     ApplicationModeRefPtr      _CurrentMode;
     boost::posix_time::ptime   _DateTimeRun;

     bool          _EnableLogging;
     bool          _LogToFile;
     std::ofstream _LogFile;
     BoostPath     _LogFilePath;

     static ApplicationSettings createDefaultSettings(void);
     static void applyDefaultSettings(ApplicationSettings& TheSettings, bool overwriteIfDefined = true);

     void createDefaultBuilderMode(void);

     void createDefaultPlayerMode(void);

     void createDefaultStartScreenMode(void);

     ProjectRefPtr createDefaultProject(void);
     SceneRefPtr createDefaultScene(void);

     BoostPath getCrashIndicationFilePath(void) const;
     void createCrashIndicationFile(void);
     void removeCrashIndicationFile(void);
     bool didCrashLastExecution(void) const;
     void handleCrashLastExecution(void);
    // Variables should all be in MainApplicationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MainApplication(void); 

    void handleWindowClosing(WindowEventDetails* const details);
    void handleWindowClosed(WindowEventDetails* const details);
    boost::signals2::connection _WindowClosingConnection,
                                _WindowClosedConnection;

    static boost::program_options::options_description _OptionsDescription;
    static boost::program_options::positional_options_description _PositionalOptions;

    void initializeLogging(BoostPath LogFilePath);
    void uninitializeLogging(void);
    
    void cleanupLoggingDir(void);

    static void KELogBufferCallback(const Char8 *data, 
                                    Int32  size,
                                    void  *clientData);

    void initOpenSG(int argc, char **argv);
    void updateRecentProject(const BoostPath& ProjectFile);

    static EventDescription   *_eventDesc[];
    static EventProducerType _producerType;
    LogEventType _LogEvent;
    
    void produceLog(LogEventDetailsType* const e);

    struct CompLogFileDates
    {
        bool operator()(const BoostPath& Left, const BoostPath Right);
    };
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    void operator =(const MainApplication &source);
    MainApplication(void);
    MainApplication(const MainApplication &source);
};

typedef MainApplication *MainApplicationP;

OSG_END_NAMESPACE

#include "KEMainApplication.inl"

#endif /* _KEMAINAPPLICATION_H_ */
