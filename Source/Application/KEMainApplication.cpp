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

#include "KEConfig.h"

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

#include "KEApplicationSettings.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

// UserInterface Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

#include "Builder/KEApplicationBuilder.h"
#include "Player/KEApplicationPlayer.h"
#include "StartScreen/KEApplicationStartScreen.h"
#include "Builder/UserInterface/Editors/KEFieldContainerEditorFactory.h"

KE_USING_NAMESPACE

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

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MainApplication::initMethod (void)
{
	_OptionsDescription.add_options()
		("help,h", "Produce help message.")
		("settings-file,s", boost::program_options::value<std::string>()->default_value("./.KEDefaultSettings.xml"), "The settings file to use.")
		("project-file,f", boost::program_options::value<std::string>(), "The Project file to use.")
		("builder,b", "Start the world builder.")
		("play,p", "Play the project file.")
		;

	_PositionalOptions.add("project-file", -1);
}

ApplicationSettingsPtr MainApplication::createDefaultSettings(void)
{
    ApplicationSettingsPtr DefaultSettings = ApplicationSettings::create();
    beginEditCP(DefaultSettings);
        DefaultSettings->setDataDirectory(Path("./Data"));
        DefaultSettings->setDefaultWindowPosition(Pnt2f(0.0f,0.0f));
        DefaultSettings->setDefaultWindowSize(Vec2f(1280.0f,1024.0f));
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
		loadSettings(Path(OptionsVariableMap["settings-file"].as<std::string>()));
	}
	else
	{
		loadSettings(getSettingsLoadFile());
	}

    if(getSettings() == NullFC)
    {
        beginEditCP(MainApplicationPtr(this), SettingsFieldMask);
            setSettings(createDefaultSettings());
        endEditCP(MainApplicationPtr(this), SettingsFieldMask);
    }

    // Set up Window
	beginEditCP(MainApplicationPtr(this), MainApplication::MainWindowEventProducerFieldMask);
		setMainWindowEventProducer(createDefaultWindowEventProducer());
	endEditCP(MainApplicationPtr(this), MainApplication::MainWindowEventProducerFieldMask);

    ::osg::WindowPtr MainWindow = getMainWindowEventProducer()->initWindow();

	getMainWindowEventProducer()->addWindowListener(&_MainWindowListener);

	getMainWindowEventProducer()->openWindow(getSettings()->getDefaultWindowPosition(),
                                        getSettings()->getDefaultWindowSize(),
                                        "Kabala Engine");
										
    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    //Initialize Kabala Engine Specific Types
    FieldContainerEditorFactory::the()->init();
	

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
		beginEditCP(MainApplicationPtr(this), ProjectFieldMask);
			setProject(createDefaultProject());
		endEditCP(MainApplicationPtr(this), ProjectFieldMask);
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

	_ExitMainLoop = false;
    while(!_ExitMainLoop)
    {
        if(getMainWindowEventProducer()->getVisible() && !getMainWindowEventProducer()->getIconify())
        {
            getMainWindowEventProducer()->update();
            getMainWindowEventProducer()->draw();
        }
        else
        {
            osgsleep(10);
        }
    }

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
	
	getStartScreenMode()->attachApplication(MainApplicationPtr(this));
	beginEditCP(MainApplicationPtr(this), CurrentModeFieldMask);
		setCurrentMode(getStartScreenMode());
	endEditCP(MainApplicationPtr(this), CurrentModeFieldMask);
	
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
	
	getBuilderMode()->attachApplication(MainApplicationPtr(this));
	beginEditCP(MainApplicationPtr(this), CurrentModeFieldMask);
		setCurrentMode(getBuilderMode());
	endEditCP(MainApplicationPtr(this), CurrentModeFieldMask);
	
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
	
	getPlayerMode()->attachApplication(MainApplicationPtr(this));
	beginEditCP(MainApplicationPtr(this), CurrentModeFieldMask);
		setCurrentMode(getPlayerMode());
	endEditCP(MainApplicationPtr(this), CurrentModeFieldMask);
	
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
		beginEditCP(MainApplicationPtr(this), ProjectFieldMask);
			setProject(LoadedProject);
		endEditCP(MainApplicationPtr(this), ProjectFieldMask);
		
		beginEditCP(getSettings(), ApplicationSettings::LastOpenedProjectFileFieldMask);
			getSettings()->setLastOpenedProjectFile(ProjectFile);
		endEditCP(getSettings(), ApplicationSettings::LastOpenedProjectFileFieldMask);
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
		beginEditCP(MainApplicationPtr(this), MainApplication::SettingsFieldMask);
			setSettings(LoadedSettings);
		endEditCP(MainApplicationPtr(this), MainApplication::SettingsFieldMask);
	}
}

void MainApplication::createDefaultBuilderMode(void)
{
	if(getBuilderMode() == NullFC)
	{
		beginEditCP(MainApplicationPtr(this), BuilderModeFieldMask);
			setBuilderMode(ApplicationBuilder::create());
		endEditCP(MainApplicationPtr(this), BuilderModeFieldMask);
	}
}

void MainApplication::createDefaultPlayerMode(void)
{
	if(getPlayerMode() == NullFC)
	{
		beginEditCP(MainApplicationPtr(this), PlayerModeFieldMask);
			setPlayerMode(ApplicationPlayer::create());
		endEditCP(MainApplicationPtr(this), PlayerModeFieldMask);
	}
}

void MainApplication::createDefaultStartScreenMode(void)
{
	if(getStartScreenMode() == NullFC)
	{
		beginEditCP(MainApplicationPtr(this), StartScreenModeFieldMask);
			setStartScreenMode(ApplicationStartScreen::create());
		endEditCP(MainApplicationPtr(this), StartScreenModeFieldMask);
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
	beginEditCP(CameraBeaconNode, Node::CoreFieldMask);
		CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(CameraBeaconNode, Node::CoreFieldMask);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 64, 64);
    
	NodePtr SceneTransformNode = Node::create();
    beginEditCP(SceneTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		SceneTransformNode->setCore(Transform::create());
        SceneTransformNode->addChild(TorusGeometryNode);
	endEditCP(SceneTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	NodePtr DefaultSceneNode = Node::create();
    beginEditCP(DefaultSceneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultSceneNode->setCore(osg::Group::create());
        DefaultSceneNode->addChild(CameraBeaconNode);
        DefaultSceneNode->addChild(SceneTransformNode);
    endEditCP(DefaultSceneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Camera
    PerspectiveCameraPtr DefaultSceneCamera = PerspectiveCamera::create();
    beginEditCP(DefaultSceneCamera, PerspectiveCamera::FovFieldMask | PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask | PerspectiveCamera::BeaconFieldMask);
        DefaultSceneCamera->setFov(60.f);
        DefaultSceneCamera->setNear(0.1f);
        DefaultSceneCamera->setFar(100.0f);
        DefaultSceneCamera->setBeacon(CameraBeaconNode);
    endEditCP(DefaultSceneCamera, PerspectiveCamera::FovFieldMask | PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask | PerspectiveCamera::BeaconFieldMask);

    //Background
    SolidBackgroundPtr DefaultSceneBackground = SolidBackground::create();
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
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MainApplication::MainApplication(void) :
    Inherited(),
		_MainWindowListener(MainApplicationPtr(this))
{
}

MainApplication::MainApplication(const MainApplication &source) :
    Inherited(source),
		_MainWindowListener(MainApplicationPtr(this))
{
}

MainApplication::~MainApplication(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MainApplication::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & ProjectFieldMask) &&
        getCurrentMode() != NullFC)
    {
        getCurrentMode()->reset();
    }
}

void MainApplication::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MainApplication NI" << std::endl;
}

void MainApplication::MainWindowListener::windowClosing(const WindowEvent& e)
{
	_MainApplication->exitMainLoop();
}

void MainApplication::MainWindowListener::windowClosed(const WindowEvent& e)
{
	_MainApplication->exitMainLoop();
}
