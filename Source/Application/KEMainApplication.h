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
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <boost/program_options.hpp>
#include <Application/KEApplicationSettingsFields.h> // Settings type
#include <OpenSG/Toolbox/OSGPathType.h> // SettingsLoadFile type
#include <OpenSG/Input/OSGWindowEventProducerFields.h> // MainWindowEventProducer type
#include <Project/KEProjectFields.h> // Project type
#include <Application/KEApplicationModeFields.h> 


OSG_BEGIN_NAMESPACE

/*! \brief MainApplication class. See \ref 
           PageKabalaEngineMainApplication for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING MainApplication
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

	void saveSettings(const Path& SettingsFile);
	void loadSettings(const Path& SettingsFile);

	void saveProject(const Path& ProjectFile);
	void loadProject(const Path& ProjectFile);

	void attachBuilder(void);

	void attachPlayer(void);

	void attachStartScreen(void);

           ApplicationSettingsPtr &getSettings       (void);
     const ApplicationSettingsPtr &getSettings       (void) const;
           Path                &getSettingsLoadFile(void);
     const Path                &getSettingsLoadFile(void) const;
           WindowEventProducerPtr &getMainWindowEventProducer(void);
     const WindowEventProducerPtr &getMainWindowEventProducer(void) const;
           ProjectPtr          &getProject        (void);
     const ProjectPtr          &getProject        (void) const;
           ApplicationModePtr  &getBuilderMode    (void);
     const ApplicationModePtr  &getBuilderMode    (void) const;
           ApplicationModePtr  &getPlayerMode     (void);
     const ApplicationModePtr  &getPlayerMode     (void) const;
           ApplicationModePtr  &getStartScreenMode(void);
     const ApplicationModePtr  &getStartScreenMode(void) const;
           ApplicationModePtr  &getCurrentMode    (void);
     const ApplicationModePtr  &getCurrentMode    (void) const;
     
     void setSettings       ( const ApplicationSettingsPtr &value );
     void setSettingsLoadFile( const Path &value );
     void setMainWindowEventProducer( const WindowEventProducerPtr &value );
     void setProject        ( const ProjectPtr &value );
     void setBuilderMode    ( const ApplicationModePtr &value );
     void setPlayerMode     ( const ApplicationModePtr &value );
     void setStartScreenMode( const ApplicationModePtr &value );
     void setCurrentMode    ( const ApplicationModePtr &value );
    /*=========================  PROTECTED  ===============================*/
  protected:

    ApplicationSettingsPtr _Settings;
    Path                   _SettingsPath;
    WindowEventProducerPtr _MainWindowEventProducer;
    ProjectPtr             _Project;
    ApplicationModePtr     _BuilderMode;
    ApplicationModePtr     _StartScreenMode;
    ApplicationModePtr     _PlayerMode;
    ApplicationModePtr     _CurrentMode;

    static ApplicationSettingsPtr createDefaultSettings(void);

	void createDefaultBuilderMode(void);

	void createDefaultPlayerMode(void);

	void createDefaultStartScreenMode(void);

	ProjectPtr createDefaultProject(void);
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
		virtual void windowClosing(const WindowEventPtr e);

		virtual void windowClosed(const WindowEventPtr e);
	protected :
		MainApplication* _MainApplication;
	};

	MainWindowListener _MainWindowListener;

	static boost::program_options::options_description _OptionsDescription;
	static boost::program_options::positional_options_description _PositionalOptions;
    /*! \}                                                                 */
;
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
