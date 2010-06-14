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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEMainApplication.h"

// Input
#include <OpenSG/OSGWindowUtils.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGNameAttachment.h>

#include "KEApplicationSettings.h"
#include "KEApplicationMode.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

// UserInterface Headers
#include <OpenSG/OSGLookAndFeelManager.h>

//TODO: Uncomment
//#include "KEApplicationBuilder.h"
#include "Player/KEApplicationPlayer.h"
#include "StartScreen/KEApplicationStartScreen.h"
//#include "KEFieldContainerEditorFactory.h"

#include <boost/filesystem.hpp>

//#include <OpenSG/OSGInventory.h>
#include <OpenSG/OSGPhysicsHandler.h>

//Bindings for the OSGToolbox libraries
#include <OpenSG/OSGToolbox_wrap.h>

//Kabala Engine Lua Bindings
#include "LuaBindings/KELuaBindings.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MainApplication
The Main Application. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
boost::program_options::options_description MainApplication::_OptionsDescription("Allowed options");
boost::program_options::positional_options_description MainApplication::_PositionalOptions = boost::program_options::positional_options_description();


MainApplication *MainApplication::_Instance = NULL;

const BoostPath MainApplication::EngineAppDataDirectory = BoostPath("./KabalaEngine/Data");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


MainApplication *MainApplication::the(void)
{
    if(_Instance == NULL)
    {
        _Instance = new MainApplication;

        //Initialize static variables
        _OptionsDescription.add_options()
            ("help,h", "Produce help message.")
            ("settings-file,s", boost::program_options::value<std::string>()->default_value("./.KEDefaultSettings.xml"), "The settings file to use.")
            ("project-file,f", boost::program_options::value<std::string>(), "The Project file to use.")
            ("builder,b", "Start the world builder.")
            ("play,p", "Play the project file.")
            ("debug,d", "Only relevant if -p option is present.  Startup with the dubugger attached.")
		    ("log-level,l", boost::program_options::value<UInt32>(), "The logging level.  Higher values logs more information. 0=LOG_LOG,1=LOG_FATAL,2=LOG_WARNING,3=LOG_NOTICE,4=LOG_INFO,5=LOG_DEBUG.  This will override the value defined in the settings file.")
		    ("log-type,t", boost::program_options::value<UInt32>(), "The location to route the logging. 0=LOG_NONE,1=LOG_STDOUT,2=LOG_STDERR,3=LOG_FILE,4=LOG_BUFFER.  This will override the value defined in the settings file.")
		    ("log-file,g", boost::program_options::value<std::string>(), "The file to route the logging to.  This will override the value defined in the settings file.  This option is only relavent if log-route is 3(LOG_FILE).")
            ;

        _PositionalOptions.add("project-file", -1);
    }

    return _Instance;
}

ApplicationSettingsRefPtr MainApplication::createDefaultSettings(void)
{
    SLOG << "Creating default settings." << std::endl;
    ApplicationSettingsRefPtr DefaultSettings = ApplicationSettings::create();
    DefaultSettings->setDataDirectory(BoostPath("./share") / EngineAppDataDirectory);
    DefaultSettings->setDefaultWindowPosition(Pnt2f(-1.0f,-1.0f));
    DefaultSettings->setDefaultWindowSize(Vec2f(0.85f,0.85f));
    DefaultSettings->setFullscreen(false);
    return DefaultSettings;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


EventConnection MainApplication::addLogListener(LogListenerPtr Listener)
{
    _LogListeners.insert(Listener);

    return EventConnection(
                           boost::bind(&MainApplication::isLogListenerAttached, this, Listener),
                           boost::bind(&MainApplication::removeLogListener, this, Listener));
}

void MainApplication::removeLogListener(LogListenerPtr Listener)
{
    LogListenerSetItor EraseIter(_LogListeners.find(Listener));
    if(EraseIter != _LogListeners.end())
    {
        _LogListeners.erase(EraseIter);
    }
}

void MainApplication::printCommandLineHelp(void) const
{
    std::cout << _OptionsDescription << std::endl;
}

Int32 MainApplication::run(int argc, char **argv)
{
    //Get the path to the command
    BoostPath CommandPath(argv[0]);
    if(!CommandPath.is_complete() && !CommandPath.has_root_directory())
    {
        CommandPath = boost::filesystem::complete(CommandPath);
    }
    CommandPath.normalize();

    //Parse the Program arguments
    boost::program_options::variables_map OptionsVariableMap;
    try
    {
        boost::program_options::store(boost::program_options::command_line_parser(argc, argv).
                                      options(_OptionsDescription).positional(_PositionalOptions).run(), OptionsVariableMap);
        boost::program_options::notify(OptionsVariableMap);
    }
    catch(boost::program_options::error& e)
    {
        std::cout << "Error parsing command line: " << e.what() << std::endl;
        printCommandLineHelp();
    }

    //Check for the help argument
    if(OptionsVariableMap.count("help"))
    {
        printCommandLineHelp();
        return 1;
    }
    
    //Setup the Logging
    LogLevel KELogLevel(LOG_NOTICE);
    if(OptionsVariableMap.count("log-level"))
    {
        KELogLevel = OptionsVariableMap["log-level"].as<LogLevel>();
    }
    LogType KELogType(LOG_FILE);
    if(OptionsVariableMap.count("log-type"))
    {
        KELogType = OptionsVariableMap["log-type"].as<LogType>();
    }
    BoostPath KELogFilePath("./KabalaEngine.log");
    if(KELogType == LOG_FILE && OptionsVariableMap.count("log-file"))
    {
        KELogFilePath = BoostPath(OptionsVariableMap["log-file"].as<std::string>());
    }
    initializeLogging(KELogType, KELogFilePath);
    osgLogP->setLogLevel(KELogLevel, true);
	osgLogP->setHeaderElem((LOG_TYPE_HEADER | LOG_TIMESTAMP_HEADER), true);

    //Initialize OpenSG
    initOpenSG(argc,argv);

    // Set up Settings
    //Check for the settings file
    if(OptionsVariableMap.count("settings-file"))
    {
        setSettingsLoadFile(BoostPath(OptionsVariableMap["settings-file"].as<std::string>()));
    }
    loadSettings(getSettingsLoadFile());

    if(getSettings() == NULL)
    {
        setSettings(createDefaultSettings());
    }

    //If the settings aren't being overriden by the command-line options
    //then set the logging with the settings values
    if(!OptionsVariableMap.count("log-level"))
    {
	    osgLogP->setLogLevel(static_cast<LogLevel>(getSettings()->getLogLevel()), true);
    }
    if(osgLogP->getLogType() == LOG_FILE &&
       !OptionsVariableMap.count("log-file") &&
       !boost::filesystem::equivalent(getSettings()->getLogFile(),KELogFilePath))
    {
        initializeLogging(static_cast<LogType>(getSettings()->getLogType()), getSettings()->getLogFile());
    }
    if(!OptionsVariableMap.count("log-type"))
    {
	    osgLogP->setLogType(static_cast<LogType>(getSettings()->getLogType()), true);
    }
	osgLogP->setHeaderElem(getSettings()->getLogHeaderElements(), true);

    //Log information about the Engine
    SLOG << "Starting Kabala Engine:" << std::endl;
    OSG::indentLog(4,PLOG);
    PLOG << "Version: " << getKabalaEngineVersion() << std::endl;
    OSG::indentLog(4,PLOG);
    PLOG << "Revision: " << getKabalaEngineBuildRepositoryRevision() << std::endl;
    OSG::indentLog(4,PLOG);
    PLOG << "Build Type: " << getKabalaEngineBuildType() << std::endl;

    //Check if the Data Directory exists
    if(!boost::filesystem::exists(getSettings()->getDataDirectory()))
    {
        SWARNING << "Could not find Application Data directory: \""
                 << getSettings()->getDataDirectory().string()
                 << "\" specified in the Settings file because the directory doesn't exist." << std::endl;

        //Try to find the data directory in a few locations
        std::vector<BoostPath> PathsToTry;
        PathsToTry.push_back(BoostPath("/usr/local/share") / EngineAppDataDirectory);
        PathsToTry.push_back(BoostPath("/usr/share") / EngineAppDataDirectory);
        PathsToTry.push_back(CommandPath.parent_path() / EngineAppDataDirectory);
        PathsToTry.push_back(CommandPath.parent_path() / BoostPath("..") / EngineAppDataDirectory);
        PathsToTry.push_back(CommandPath.parent_path() / BoostPath("../share") / EngineAppDataDirectory);

        for(UInt32 i(0) ; i<PathsToTry.size() ; ++i)
        {
            SNOTICE << "Looking for Data directory in: "
                << PathsToTry[i].string() << std::endl;
            if(boost::filesystem::exists(PathsToTry[i]))
            {
                PNOTICE << "FOUND" << std::endl;
                PathsToTry[i].normalize();
                getSettings()->setDataDirectory(PathsToTry[i]);
                break;
            }
            else
            {
                PNOTICE << "NOT FOUND" << std::endl;
            }
        }
    }

    if(!boost::filesystem::exists(getSettings()->getDataDirectory()))
    {
        SWARNING << "Could not find Application Data directory: \""
                 << getSettings()->getDataDirectory().string()
                 << "\" because the directory doesn't exist." << std::endl;
    }
    else
    {
        SLOG << "Using Application Data directory: \""
                 << getSettings()->getDataDirectory().string()
                 << "\"" << std::endl;
    }

    // Set up Window
    setMainWindow(createNativeWindow());
    setName(getMainWindow(),"__KABALA_ENGINE_WINDOW_EVENT_PRODUCER");

    getMainWindow()->initWindow();

    getMainWindow()->setFullscreen(getSettings()->getFullscreen());

    getMainWindow()->addWindowListener(&_MainWindowListener);

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    //Initialize Kabala Engine Specific Types
    //FieldContainerEditorFactory::the()->init();


    //Open Window
    Vec2f WindowSize(getSettings()->getDefaultWindowSize());
    if(getSettings()->getDefaultWindowSize().x() <= 1.0f )
    {
        WindowSize[0] = getMainWindow()->getDesktopSize().x() * getSettings()->getDefaultWindowSize().x();
    }
    if(getSettings()->getDefaultWindowSize().y() <= 1.0f )
    {
        WindowSize[1] = getMainWindow()->getDesktopSize().y() * getSettings()->getDefaultWindowSize().y();
    }
    Pnt2f WindowPos(getSettings()->getDefaultWindowPosition());
    if(getSettings()->getDefaultWindowPosition().x() < 0.0f )
    {
        WindowPos[0] = (getMainWindow()->getDesktopSize().x() - WindowSize.x()) * 0.5f;
    }
    if(getSettings()->getDefaultWindowPosition().y() < 0.0f )
    {
        WindowPos[1] = (getMainWindow()->getDesktopSize().y() - WindowSize.y()) * 0.5f;
    }

    getMainWindow()->openWindow(WindowPos,
                                WindowSize,
                                "Kabala Engine");

    //Load the Project file, if given
    if(OptionsVariableMap.count("project-file"))
    {
        loadProject(BoostPath(OptionsVariableMap["project-file"].as<std::string>()));
    }
    else
    {
        loadProject(getSettings()->getLastOpenedProjectFile());
    }

    if(getProject() == NULL)
    {
        //Project Failed to load, or file didn't exist
        setProject(createDefaultProject());
    }

    if(OptionsVariableMap.count("builder"))
    {
        attachBuilder();
    }
    else if(OptionsVariableMap.count("play"))
    {
        attachPlayer();
        if(OptionsVariableMap.count("debug"))
        {
            dynamic_pointer_cast<ApplicationPlayer>(getPlayerMode())->enableDebug(true);
        }
    }
    else
    {
        attachStartScreen();
    }

    //Main Loop
    getMainWindow()->mainLoop();

    //Exited Main Loop
    //Save Settings
    saveSettings(getSettingsLoadFile());
    
    SLOG << "Stopping Kabala Engine" << std::endl;

	//OSG exit
    OSG::osgExit();

    return 0;
}

void MainApplication::initOpenSG(int argc, char **argv)
{
    OSG::preloadSharedObject("OSGCluster");
    OSG::preloadSharedObject("OSGContribBackgroundloader");
    OSG::preloadSharedObject("OSGContribComputeBase");
    OSG::preloadSharedObject("OSGContribGUI");
    OSG::preloadSharedObject("OSGContribLuaToolbox");
    OSG::preloadSharedObject("OSGContribParticleSystem");
    OSG::preloadSharedObject("OSGContribPhysics");
    OSG::preloadSharedObject("OSGContribPLY");
    OSG::preloadSharedObject("OSGContribSound");
    OSG::preloadSharedObject("OSGContribTrapezoidalShadowMaps");
    OSG::preloadSharedObject("OSGContribUserInterface");
    OSG::preloadSharedObject("OSGContribVideo");
    OSG::preloadSharedObject("OSGDynamics");
    OSG::preloadSharedObject("OSGEffectGroups");
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGGroup");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGTBAnimation");

    // OSG init
	OSG::osgInit(argc,argv);

    //Toolbox Bindings
    OSG::LuaManager::the()->openLuaBindingLib(getOSGToolboxLuaBindingsLibFunctor());
    
    //Kabala Engine Bindings
    OSG::LuaManager::the()->openLuaBindingLib(getKabalaEngineLuaBindingsLibFunctor());
}

void MainApplication::attachStartScreen(void)
{
    createDefaultStartScreenMode();

    if(getCurrentMode() != NULL && getCurrentMode() != getStartScreenMode())
    {
        getCurrentMode()->stop();
        getCurrentMode()->dettachApplication();
    }

    getStartScreenMode()->attachApplication();
    setCurrentMode(getStartScreenMode());

    getCurrentMode()->start();
}

void MainApplication::attachBuilder(void)
{
    createDefaultBuilderMode();

    if(getCurrentMode() != NULL && getCurrentMode() != getBuilderMode())
    {
        getCurrentMode()->stop();
        getCurrentMode()->dettachApplication();
    }

    getBuilderMode()->attachApplication();
    setCurrentMode(getBuilderMode());

    getCurrentMode()->start();
}

void MainApplication::attachPlayer(void)
{
    createDefaultPlayerMode();

    if(getCurrentMode() != NULL && getCurrentMode() != getPlayerMode())
    {
        getCurrentMode()->stop();
        getCurrentMode()->dettachApplication();
    }

    getPlayerMode()->attachApplication();
    setCurrentMode(getPlayerMode());

    getCurrentMode()->start();
}

void MainApplication::saveProject(const BoostPath& ProjectFile)
{
    if(getProject() != NULL)
    {
        getProject()->save(ProjectFile);
    }
}

void MainApplication::loadProject(const BoostPath& ProjectFile)
{
    ProjectRefPtr LoadedProject = Project::load(ProjectFile);

    if(LoadedProject != NULL)
    {
        setProject(LoadedProject);

        getSettings()->setLastOpenedProjectFile(ProjectFile);

        //Update Recent Projects
        MFBoostPath::iterator
            SearchItor(getSettings()->editMFRecentProjectFiles()->begin());
        for( ; SearchItor!=getSettings()->editMFRecentProjectFiles()->end() ; ++SearchItor)
        {
            if(boost::filesystem::equivalent(*SearchItor,ProjectFile))
            {
                break;
            }
        }
        if(SearchItor != getSettings()->editMFRecentProjectFiles()->end())
        {
            getSettings()->editMFRecentProjectFiles()->erase(SearchItor);
        }
        getSettings()->editMFRecentProjectFiles()->push_back(ProjectFile);

    }
}

void MainApplication::saveSettings(const BoostPath& SettingsFile)
{
    if(getSettings() != NULL)
    {
        getSettings()->save(SettingsFile);
    }
}

void MainApplication::loadSettings(const BoostPath& SettingsFile)
{

    ApplicationSettingsRefPtr LoadedSettings;
    if(!boost::filesystem::exists(SettingsFile))
    {
        SWARNING << "Could not load Settings from: \""
                 << SettingsFile.string() << "\" because that file does not exist." << std::endl;
    }
    else
    {
        BoostPath SettingsFullPath(SettingsFile);
        if(!SettingsFile.is_complete() && !SettingsFile.has_root_directory())
        {
            SettingsFullPath = boost::filesystem::complete(SettingsFile);
        }
        SettingsFullPath.normalize();

        SLOG << "Loading Settings from: " << SettingsFullPath.string() << std::endl;

        LoadedSettings = ApplicationSettings::load(SettingsFile);
    }

    if(LoadedSettings != NULL)
    {
        setSettings(LoadedSettings);
    }
}

void MainApplication::createDefaultBuilderMode(void)
{
    if(getBuilderMode() == NULL)
    {
    //TODO: Uncomment
        //setBuilderMode(ApplicationBuilder::create());
    }
}

void MainApplication::createDefaultPlayerMode(void)
{
    if(getPlayerMode() == NULL)
    {
        setPlayerMode(ApplicationPlayer::create());
    }
}

void MainApplication::createDefaultStartScreenMode(void)
{
    if(getStartScreenMode() == NULL)
    {
        setStartScreenMode(ApplicationStartScreen::create());
    }
}

void MainApplication::exit(void)
{
    getMainWindow()->closeWindow();
}

SceneRefPtr MainApplication::createDefaultScene(void)
{
    //The Default Scene
    //Camera Transformation Node
    Matrix CameraTransformMatrix;
    CameraTransformMatrix.setTranslate(0.0f,0.0f, 9.0f);
    TransformRefPtr CameraBeaconTransform = Transform::create();
    CameraBeaconTransform->setMatrix(CameraTransformMatrix);

    NodeRefPtr CameraBeaconNode = Node::create();
    setName(CameraBeaconNode, "Camera Beacon" );
    CameraBeaconNode->setCore(CameraBeaconTransform);

    //Camera
    PerspectiveCameraRefPtr DefaultSceneCamera = PerspectiveCamera::create();
    setName(DefaultSceneCamera, "Untitled Camera" );
    DefaultSceneCamera->setFov(60.f);
    DefaultSceneCamera->setNear(10.0f);
    DefaultSceneCamera->setFar(50000.0f);
    DefaultSceneCamera->setBeacon(CameraBeaconNode);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 64, 64);
    setName(TorusGeometryNode, "Torus" );

    NodeRefPtr TorusTransformNode = Node::create();
    setName(TorusTransformNode, "Torus Transform" );
    TorusTransformNode->setCore(Transform::create());
    TorusTransformNode->addChild(TorusGeometryNode);

    // Make Box Node (creates Box in background of scene)
    NodeRefPtr BoxGeometryNode = makeBox(3.0f, 3.0f, 3.0f, 8, 8, 8);
    setName(BoxGeometryNode, "Box" );

    Matrix BoxTransformMatrix;
    BoxTransformMatrix.setTranslate(5.0f,0.0f, 0.0f);

    TransformRefPtr BoxTransform = Transform::create();
    BoxTransform->setMatrix(BoxTransformMatrix);

    NodeRefPtr BoxTransformNode = Node::create();
    setName(BoxTransformNode, "Box Transform" );
    BoxTransformNode->setCore(BoxTransform);
    BoxTransformNode->addChild(BoxGeometryNode);

    // Make Cone Node (creates Cone in background of scene)
    NodeRefPtr ConeGeometryNode = makeCone(3.5, 1.5f, 96, true, true);
    setName(ConeGeometryNode, "Cone" );

    Matrix ConeTransformMatrix;
    ConeTransformMatrix.setTranslate(-5.0f,0.0f, 0.0f);

    TransformRefPtr ConeTransform = Transform::create();
    ConeTransform->setMatrix(ConeTransformMatrix);

    NodeRefPtr ConeTransformNode = Node::create();
    setName(ConeTransformNode, "Cone Transform" );
    ConeTransformNode->setCore(ConeTransform);
    ConeTransformNode->addChild(ConeGeometryNode);

    //Light Beacon
    Matrix LightTransformMatrix;
    LightTransformMatrix.setTranslate(0.0f,5.0f, 5.0f);
    TransformRefPtr LightBeaconTransform = Transform::create();
    LightBeaconTransform->setMatrix(LightTransformMatrix);

    NodeRefPtr LightBeaconNode = Node::create();
    setName(LightBeaconNode, "Light Beacon" );
    LightBeaconNode->setCore(LightBeaconTransform);

    //Make the Light
    PointLightRefPtr ThePointLight = PointLight::create();

    ThePointLight->setBeacon(LightBeaconNode);

    NodeRefPtr LightNode = Node::create();
    setName(LightNode, "Light " );
    LightNode->setCore(ThePointLight);
    LightNode->addChild(TorusTransformNode);
    LightNode->addChild(BoxTransformNode);
    LightNode->addChild(ConeTransformNode);

    //Scene Root Node
    NodeRefPtr DefaultSceneNode = Node::create();
    setName(DefaultSceneNode, "Scene Root" );
    DefaultSceneNode->setCore(OSG::Group::create());
    DefaultSceneNode->addChild(LightBeaconNode);
    DefaultSceneNode->addChild(CameraBeaconNode);
    DefaultSceneNode->addChild(LightNode);

    //Background
    SolidBackgroundRefPtr DefaultSceneBackground = SolidBackground::create();
    setName(DefaultSceneBackground, "Untitled Background" );
    DefaultSceneBackground->setColor(Color3f(0.3f,0.3f,0.3f));

    //Viewport
    ViewportRefPtr DefaultSceneViewport = Viewport::create();
    setName(DefaultSceneViewport, "Untitled Viewport" );
    DefaultSceneViewport->setSize(0.0,0.0,1.0,1.0);
    DefaultSceneViewport->setCamera(DefaultSceneCamera);
    DefaultSceneViewport->setBackground(DefaultSceneBackground);
    DefaultSceneViewport->setRoot(DefaultSceneNode);


    SceneRefPtr TheDefaultScene = Scene::create();
    TheDefaultScene->pushToBackgrounds(DefaultSceneBackground);
    TheDefaultScene->setInitialBackground(DefaultSceneBackground);

    TheDefaultScene->pushToCameras(DefaultSceneCamera);
    TheDefaultScene->setInitialCamera(DefaultSceneCamera);

    TheDefaultScene->pushToModelNodes(DefaultSceneNode);
    TheDefaultScene->pushToInitialModelNodes(DefaultSceneNode);

    TheDefaultScene->pushToViewports(DefaultSceneViewport);

    return TheDefaultScene;
}

ProjectRefPtr MainApplication::createDefaultProject(void)
{
    ProjectRefPtr TheDefaultProject = ProjectBase::create();


    SceneRefPtr TheDefaultScene(createDefaultScene());

    TheDefaultProject->pushToScenes(TheDefaultScene);
    TheDefaultProject->setInitialScene(TheDefaultScene);	
    setName(TheDefaultProject,"Untitled Project");

    return TheDefaultProject;
}


void MainApplication::setSettings( const ApplicationSettingsRefPtr &value )
{
    _Settings = value;
}

void MainApplication::setSettingsLoadFile( const BoostPath &value )
{
    _SettingsPath = value;
}

void MainApplication::setMainWindow( const WindowEventProducerRefPtr &value )
{
    _MainWindow = value;
}

void MainApplication::setProject ( const ProjectRefPtr &value )
{
    _Project = value;
    if(getCurrentMode() != NULL)
    {
        getCurrentMode()->reset();
    }
    if(_Project != NULL)
    {
        SLOG << "Set Project to " << ( getName(_Project) ? getName(_Project) : "UNNAMED_PROJECT" ) << std::endl;
    }
}

void MainApplication::setBuilderMode( const ApplicationModeRefPtr &value )
{
    _BuilderMode = value;
}

void MainApplication::setPlayerMode( const ApplicationModeRefPtr &value )
{
    _PlayerMode = value;
}

void MainApplication::setStartScreenMode( const ApplicationModeRefPtr &value )
{
    _StartScreenMode = value;
}

void MainApplication::setCurrentMode( const ApplicationModeRefPtr &value )
{
    _CurrentMode = value;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MainApplication::KELogBufferCallback(const Char8 *data, 
                         Int32  size,
                         void  *clientData)
{
	//Send to the Log Listeners
    std::string value(data,size);
    LogEventUnrecPtr e = LogEvent::create(NULL, getTimeStamp(),value);
    MainApplication::the()->produceLog(e);
}


void MainApplication::initializeLogging(LogType KELogType, BoostPath KELogFilePath)
{
	//Set the log type
	//LOG_NONE, 
	//LOG_STDOUT, 
	//LOG_STDERR, 
	//LOG_FILE,

    if(osgLogP->getLogType() != KELogType)
    {
	    osgLogP->setLogType(KELogType, true);

	    if(osgLogP->getLogType() == LOG_BUFFER)
	    {
		    //Configure the LogBuffer
		    osgLogP->getLogBuf().setEnabled(true);
		    osgLogP->getLogBuf().setCallback(KELogBufferCallback);
	    }
	    else
	    {
		    osgLogP->getLogBuf().setEnabled(false);
		    osgLogP->getLogBuf().removeCallback();
	    }
    }

	if(osgLogP->getLogType() == LOG_FILE)
	{
		//If the Log is to a file then set the file
		osgLogP->setLogFile(KELogFilePath.string().c_str(), true);
	}
}

void MainApplication::produceLog(const LogEventUnrecPtr e)
{
    LogListenerSet ListenerSet(_LogListeners);
    for(LogListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->log(e);
    }
}

/*----------------------- constructors & destructors ----------------------*/

MainApplication::MainApplication(void) :
		_MainWindowListener(this)
{
}

MainApplication::MainApplication(const MainApplication &source) :
		_MainWindowListener(this)
{
}

MainApplication::~MainApplication(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MainApplication::MainWindowListener::windowClosing(const WindowEventUnrecPtr e)
{
}

void MainApplication::MainWindowListener::windowClosed(const WindowEventUnrecPtr e)
{
}

