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
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include "KEApplicationSettings.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

// UserInterface Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

#include "Builder/KEApplicationBuilder.h"
#include "Player/KEApplicationPlayer.h"
#include "StartScreen/KEApplicationStartScreen.h"
#include "Builder/UserInterface/Editors/KEFieldContainerEditorFactory.h"

#include <boost/filesystem.hpp>

#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Game/OSGInventory.h>
#include <OpenSG/Lua/OSGLuaManager.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MainApplication
The Main Application. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
boost::program_options::options_description MainApplication::_OptionsDescription("Allowed options");
boost::program_options::positional_options_description MainApplication::_PositionalOptions = boost::program_options::positional_options_description();


MainApplication *MainApplication::_Instance = NULL;
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
		    ;

	    _PositionalOptions.add("project-file", -1);
    }

    return _Instance;
}

ApplicationSettingsPtr MainApplication::createDefaultSettings(void)
{
    ApplicationSettingsPtr DefaultSettings = ApplicationSettings::create();
    beginEditCP(DefaultSettings);
        DefaultSettings->setDataDirectory(Path("./share/KabalaEngine/Data"));
        DefaultSettings->setDefaultWindowPosition(Pnt2f(-1.0f,-1.0f));
        DefaultSettings->setDefaultWindowSize(Vec2f(0.85f,0.85f));
        DefaultSettings->setFullscreen(false);
    endEditCP(DefaultSettings);
    return DefaultSettings;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MainApplication::printCommandLineHelp(void) const
{
	std::cout << _OptionsDescription << std::endl;
}

Int32 MainApplication::run(int argc, char **argv)
{
    //Make Dummy Values to link in external libs
    //Sound
    if(Sound::getClassType().getId() == 0)
    {
        return -1;
    }
    
    //Game
    if(Inventory::getClassType().getId() == 0)
    {
        return -1;
    }

    //Lua
    if(LuaManager::the() == NULL)
    {
        return -1;
    }

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
		SWARNING << "Error parsing command line: " << e.what() << std::endl;
		printCommandLineHelp();
	}
	
	//Check for the help argument
	if(OptionsVariableMap.count("help"))
	{
		printCommandLineHelp();
		return 1;
	}

    // Set up Settings
	//Check for the settings file
	if(OptionsVariableMap.count("settings-file"))
	{
		setSettingsLoadFile(Path(OptionsVariableMap["settings-file"].as<std::string>()));
	}
	loadSettings(getSettingsLoadFile());

    if(getSettings() == NullFC)
    {
        setSettings(createDefaultSettings());
    }

    // Set up Window
    setMainWindowEventProducer(createDefaultWindowEventProducer());
   
    ::osg::WindowPtr MainWindow = getMainWindowEventProducer()->initWindow();

    getMainWindowEventProducer()->setFullscreen(getSettings()->getFullscreen());

	getMainWindowEventProducer()->addWindowListener(&_MainWindowListener);

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    //Initialize Kabala Engine Specific Types
    FieldContainerEditorFactory::the()->init();
	

    //Open Window
    Vec2f WindowSize(getSettings()->getDefaultWindowSize());
    if(getSettings()->getDefaultWindowSize().x() <= 1.0f )
    {
        WindowSize[0] = getMainWindowEventProducer()->getDesktopSize().x() * getSettings()->getDefaultWindowSize().x();
    }
    if(getSettings()->getDefaultWindowSize().y() <= 1.0f )
    {
        WindowSize[1] = getMainWindowEventProducer()->getDesktopSize().y() * getSettings()->getDefaultWindowSize().y();
    }
    Pnt2f WindowPos(getSettings()->getDefaultWindowPosition());
    if(getSettings()->getDefaultWindowPosition().x() < 0.0f )
    {
        WindowPos[0] = (getMainWindowEventProducer()->getDesktopSize().x() - WindowSize.x()) * 0.5f;
    }
    if(getSettings()->getDefaultWindowPosition().y() < 0.0f )
    {
        WindowPos[1] = (getMainWindowEventProducer()->getDesktopSize().y() - WindowSize.y()) * 0.5f;
    }
    
	getMainWindowEventProducer()->openWindow(WindowPos,
                                        WindowSize,
                                        "Kabala Engine");

	//Load the Project file, if given
	if(OptionsVariableMap.count("project-file"))
	{
		loadProject(Path(OptionsVariableMap["project-file"].as<std::string>()));
	}
	else
	{
		loadProject(getSettings()->getLastOpenedProjectFile());
	}

	if(getProject() == NullFC)
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
	}
	else
	{
		attachStartScreen();
	}
										
    //Main Loop
    getMainWindowEventProducer()->mainLoop();

	//Exited Main Loop
    //Save Settings
    saveSettings(getSettingsLoadFile());

	return 0;
}

void MainApplication::attachStartScreen(void)
{
	createDefaultStartScreenMode();
	
	if(getCurrentMode() != NullFC && getCurrentMode() != getStartScreenMode())
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
	
	if(getCurrentMode() != NullFC && getCurrentMode() != getBuilderMode())
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
	
	if(getCurrentMode() != NullFC && getCurrentMode() != getPlayerMode())
	{
		getCurrentMode()->stop();
		getCurrentMode()->dettachApplication();
	}
	
	getPlayerMode()->attachApplication();
    setCurrentMode(getPlayerMode());
	
	getCurrentMode()->start();
}

void MainApplication::saveProject(const Path& ProjectFile)
{
	if(getProject() != NullFC)
	{
		getProject()->save(ProjectFile);
	}
}

void MainApplication::loadProject(const Path& ProjectFile)
{
	ProjectPtr LoadedProject = Project::load(ProjectFile);

	if(LoadedProject != NullFC)
	{
        setProject(LoadedProject);
		
		beginEditCP(getSettings(), ApplicationSettings::LastOpenedProjectFileFieldMask | ApplicationSettings::RecentProjectFilesFieldMask);
			getSettings()->setLastOpenedProjectFile(ProjectFile);
            
            //Update Recent Projects
			MFPath::iterator SearchItor(getSettings()->getRecentProjectFiles().begin());
			for( ; SearchItor!=getSettings()->getRecentProjectFiles().end() ; ++SearchItor)
			{
				if(boost::filesystem::equivalent(*SearchItor,ProjectFile))
				{
					break;
				}
			}
            if(SearchItor != getSettings()->getRecentProjectFiles().end())
            {
                getSettings()->getRecentProjectFiles().erase(SearchItor);
            }
            getSettings()->getRecentProjectFiles().push_back(ProjectFile);
		endEditCP(getSettings(), ApplicationSettings::LastOpenedProjectFileFieldMask | ApplicationSettings::RecentProjectFilesFieldMask);

	}
}

void MainApplication::saveSettings(const Path& SettingsFile)
{
	if(getSettings() != NullFC)
	{
		getSettings()->save(SettingsFile);
	}
}

void MainApplication::loadSettings(const Path& SettingsFile)
{
	ApplicationSettingsPtr LoadedSettings = ApplicationSettings::load(SettingsFile);

	if(LoadedSettings != NullFC)
	{
        setSettings(LoadedSettings);
	}
}

void MainApplication::createDefaultBuilderMode(void)
{
	if(getBuilderMode() == NullFC)
	{
        setBuilderMode(ApplicationBuilder::create());
	}
}

void MainApplication::createDefaultPlayerMode(void)
{
	if(getPlayerMode() == NullFC)
	{
        setPlayerMode(ApplicationPlayer::create());
	}
}

void MainApplication::createDefaultStartScreenMode(void)
{
	if(getStartScreenMode() == NullFC)
	{
        setStartScreenMode(ApplicationStartScreen::create());
	}
}

void MainApplication::exit(void)
{
	getMainWindowEventProducer()->closeWindow();
}

ProjectPtr MainApplication::createDefaultProject(void)
{
	ProjectPtr TheDefaultProject = ProjectBase::create();

    //The Default Scene
    //Root Node
    //Camera Transformation Node
	Matrix CameraTransformMatrix;
	CameraTransformMatrix.setTranslate(0.0f,0.0f, 5.0f);
	TransformPtr CameraBeaconTransform = Transform::create();
	beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
		CameraBeaconTransform->setMatrix(CameraTransformMatrix);
	endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
    setName(CameraBeaconNode, "Camera Beacon" );
	beginEditCP(CameraBeaconNode, Node::CoreFieldMask);
		CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(CameraBeaconNode, Node::CoreFieldMask);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 64, 64);
    setName(TorusGeometryNode, "Torus" );
    
	NodePtr SceneTransformNode = Node::create();
    setName(SceneTransformNode, "Torus Transform" );
    beginEditCP(SceneTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		SceneTransformNode->setCore(Transform::create());
        SceneTransformNode->addChild(TorusGeometryNode);
	endEditCP(SceneTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	NodePtr DefaultSceneNode = Node::create();
    setName(DefaultSceneNode, "Scene Root" );
    beginEditCP(DefaultSceneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultSceneNode->setCore(osg::Group::create());
        DefaultSceneNode->addChild(CameraBeaconNode);
        DefaultSceneNode->addChild(SceneTransformNode);
    endEditCP(DefaultSceneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Camera
    PerspectiveCameraPtr DefaultSceneCamera = PerspectiveCamera::create();
    setName(DefaultSceneCamera, "Camera" );
    beginEditCP(DefaultSceneCamera, PerspectiveCamera::FovFieldMask | PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask | PerspectiveCamera::BeaconFieldMask);
        DefaultSceneCamera->setFov(60.f);
        DefaultSceneCamera->setNear(0.1f);
        DefaultSceneCamera->setFar(100.0f);
        DefaultSceneCamera->setBeacon(CameraBeaconNode);
    endEditCP(DefaultSceneCamera, PerspectiveCamera::FovFieldMask | PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask | PerspectiveCamera::BeaconFieldMask);

    //Background
    SolidBackgroundPtr DefaultSceneBackground = SolidBackground::create();
    setName(DefaultSceneBackground, "Background" );
    beginEditCP(DefaultSceneBackground, SolidBackground::ColorFieldMask);
        DefaultSceneBackground->setColor(Color3f(0.0f,1.0f,0.0f));
    endEditCP(DefaultSceneBackground, SolidBackground::ColorFieldMask);


	ScenePtr TheDefaultScene = Scene::create();
    beginEditCP(TheDefaultScene);
        TheDefaultScene->getBackgrounds().push_back(DefaultSceneBackground);
        TheDefaultScene->setInitialBackground(DefaultSceneBackground);

        TheDefaultScene->getCameras().push_back(DefaultSceneCamera);
        TheDefaultScene->setInitialCamera(DefaultSceneCamera);

        TheDefaultScene->getModelNodes().push_back(DefaultSceneNode);
        TheDefaultScene->getInitialModelNodes().push_back(DefaultSceneNode);
    endEditCP(TheDefaultScene);

	beginEditCP(TheDefaultProject, Project::ScenesFieldMask | Project::InitialSceneFieldMask);
		TheDefaultProject->getScenes().push_back(TheDefaultScene);
		TheDefaultProject->setInitialScene(TheDefaultScene);	
	endEditCP(TheDefaultProject, Project::ScenesFieldMask | Project::InitialSceneFieldMask);

	return TheDefaultProject;
}


void MainApplication::setSettings( const ApplicationSettingsPtr &value )
{
    if(_Settings != NullFC)
    {
        subRefCP(_Settings);
    }
    _Settings = value;
    if(_Settings != NullFC)
    {
        addRefCP(_Settings);
    }
}

void MainApplication::setSettingsLoadFile( const Path &value )
{
    _SettingsPath = value;
}

void MainApplication::setMainWindowEventProducer( const WindowEventProducerPtr &value )
{
    if(_MainWindowEventProducer != NullFC)
    {
        subRefCP(_MainWindowEventProducer);
    }
    _MainWindowEventProducer = value;
    if(_MainWindowEventProducer != NullFC)
    {
        addRefCP(_MainWindowEventProducer);
    }
}

void MainApplication::setProject ( const ProjectPtr &value )
{
    if(_Project != NullFC)
    {
        subRefCP(_Project);
    }
    _Project = value;
    if(_Project != NullFC)
    {
        addRefCP(_Project);
    }
    if(getCurrentMode() != NullFC)
    {
        getCurrentMode()->reset();
    }
}

void MainApplication::setBuilderMode( const ApplicationModePtr &value )
{
    if(_BuilderMode != NullFC)
    {
        subRefCP(_BuilderMode);
    }
    _BuilderMode = value;
    if(_BuilderMode != NullFC)
    {
        addRefCP(_BuilderMode);
    }
}

void MainApplication::setPlayerMode( const ApplicationModePtr &value )
{
    if(_PlayerMode != NullFC)
    {
        subRefCP(_PlayerMode);
    }
    _PlayerMode = value;
    if(_PlayerMode != NullFC)
    {
        addRefCP(_PlayerMode);
    }
}

void MainApplication::setStartScreenMode( const ApplicationModePtr &value )
{
    if(_StartScreenMode != NullFC)
    {
        subRefCP(_StartScreenMode);
    }
    _StartScreenMode = value;
    if(_StartScreenMode != NullFC)
    {
        addRefCP(_StartScreenMode);
    }
}

void MainApplication::setCurrentMode( const ApplicationModePtr &value )
{
    if(_CurrentMode != NullFC)
    {
        subRefCP(_CurrentMode);
    }
    _CurrentMode = value;
    if(_CurrentMode != NullFC)
    {
        addRefCP(_CurrentMode);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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
    if(_Settings != NullFC)
    {
        subRefCP(_Settings);
    }
    if(_MainWindowEventProducer != NullFC)
    {
        subRefCP(_MainWindowEventProducer);
    }
    if(_Project != NullFC)
    {
        subRefCP(_Project);
    }
    if(_BuilderMode != NullFC)
    {
        subRefCP(_BuilderMode);
    }
    if(_StartScreenMode != NullFC)
    {
        subRefCP(_StartScreenMode);
    }
    if(_PlayerMode != NullFC)
    {
        subRefCP(_PlayerMode);
    }
    if(_CurrentMode != NullFC)
    {
        subRefCP(_CurrentMode);
    }
}

/*----------------------------- class specific ----------------------------*/

void MainApplication::MainWindowListener::windowClosing(const WindowEventPtr e)
{
}

void MainApplication::MainWindowListener::windowClosed(const WindowEventPtr e)
{
}

