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
#include <OpenSG/OSGWindowAdapter.h>
#include <boost/program_options.hpp>
#include "Application/KEApplicationSettings.h" // Settings type
#include <OpenSG/OSGBoostPathFields.h> // SettingsLoadFile type
#include <OpenSG/OSGWindowEventProducerFields.h> // MainWindowEventProducer type
#include "Project/KEProjectFields.h" // Project type
#include "Project/Scene/KESceneFields.h" // Scene type
#include "Application/KEApplicationModeFields.h"
#include <set> 
#include "Application/Logging/KELogListener.h"
#include <OpenSG/OSGEventConnection.h>

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
           WindowEventProducerRefPtr &getMainWindow(void);
     const WindowEventProducerRefPtr &getMainWindow(void) const;
           ProjectRefPtr          &getProject        (void);
     const ProjectRefPtr          &getProject        (void) const;
           ApplicationModeRefPtr  &getBuilderMode    (void);
     const ApplicationModeRefPtr  &getBuilderMode    (void) const;
           ApplicationModeRefPtr  &getPlayerMode     (void);
     const ApplicationModeRefPtr  &getPlayerMode     (void) const;
           ApplicationModeRefPtr  &getStartScreenMode(void);
     const ApplicationModeRefPtr  &getStartScreenMode(void) const;
           ApplicationModeRefPtr  &getCurrentMode    (void);
     const ApplicationModeRefPtr  &getCurrentMode    (void) const;
     
     void setSettings       ( const ApplicationSettings &value );
     void setSettingsLoadFile( const BoostPath &value );
     void setMainWindow( const WindowEventProducerRefPtr &value );
     void setProject        ( const ProjectRefPtr &value );
     void setBuilderMode    ( const ApplicationModeRefPtr &value );
     void setPlayerMode     ( const ApplicationModeRefPtr &value );
     void setStartScreenMode( const ApplicationModeRefPtr &value );
     void setCurrentMode    ( const ApplicationModeRefPtr &value );

     static const BoostPath EngineAppDataDirectory;
    
     EventConnection addLogListener(LogListenerPtr Listener);
     bool isLogListenerAttached(LogListenerPtr Listener) const;
     void removeLogListener(LogListenerPtr Listener);
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

     static ApplicationSettings createDefaultSettings(void);
     static void applyDefaultSettings(ApplicationSettings& TheSettings, bool overwriteIfDefined = true);

     void createDefaultBuilderMode(void);

     void createDefaultPlayerMode(void);

     void createDefaultStartScreenMode(void);

     ProjectRefPtr createDefaultProject(void);
     SceneRefPtr createDefaultScene(void);
    // Variables should all be in MainApplicationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MainApplication(void); 

    class MainWindowListener : public WindowAdapter
    {
      public :
        MainWindowListener(MainApplication* TheMainApplication);
        virtual void windowClosing(const WindowEventUnrecPtr e);

        virtual void windowClosed(const WindowEventUnrecPtr e);
      protected :
        MainApplication* _MainApplication;
    };

    MainWindowListener _MainWindowListener;

    static boost::program_options::options_description _OptionsDescription;
    static boost::program_options::positional_options_description _PositionalOptions;

	typedef std::set<LogListenerPtr> LogListenerSet;
    typedef LogListenerSet::iterator LogListenerSetItor;
    typedef LogListenerSet::const_iterator LogListenerSetConstItor;

    LogListenerSet       _LogListeners;

    void produceLog(const LogEventUnrecPtr e);

    void initializeLogging(LogType TheLogType = LOG_FILE,
                           BoostPath LogFilePath = BoostPath("./KabalaEngine.log"));

    static void KELogBufferCallback(const Char8 *data, 
                                    Int32  size,
                                    void  *clientData);

    void initOpenSG(int argc, char **argv);
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
