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
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGNameAttachment.h>

#include "KEApplicationSettings.h"
#include "KEApplicationMode.h"
#include "KEPlatformUtils.h"
#include "KEDefaults.h"
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"

// UserInterface Headers
#include "Application/KELookAndFeel.h"

#ifdef BUILD_WITH_WORLD_BUILDER
#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"
#endif

#include "Player/KEApplicationPlayer.h"
#include "StartScreen/KEApplicationStartScreen.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/convenience.hpp>

//#include <OpenSG/OSGInventory.h>
#include <OpenSG/OSGPhysicsHandler.h>

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

EventDescription *MainApplication::_eventDesc[] =
{
    new EventDescription("Log", 
                          "Log",
                          LogEventId, 
                          FieldTraits<LogEventDetailsType *>::getType(),
                          true,
                          NULL),
};

EventProducerType MainApplication::_producerType(
                                            "MainApplicationProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

const EventProducerType &MainApplication::getProducerType(void) const
{
    return _producerType;
}

#ifdef __APPLE__
std::pair<std::string, std::string> procSerialNumParser(const std::string& s)
{
    if (s.find("-psn_") == 0)
    {
        return std::make_pair("process-serial-number", s.substr(5));
    }
    else
    {
        return std::make_pair(std::string(), std::string());
    }
}
#endif

MainApplication *MainApplication::the(void)
{
    if(_Instance == NULL)
    {
        _Instance = new MainApplication;

        //Initialize static variables
        _OptionsDescription.add_options()
            ("help,h",            "Produce help message.")
            ("settings-file,s",    boost::program_options::value<std::string>(),
                                  "The settings file to use.")
            ("project-file,f",     boost::program_options::value<std::string>(),
                                  "The Project file to use.")
            ("builder,b",         "Start the world builder.")
            ("play,p",            "Play the project file.")
            ("fullscreen,u",      "Run in fullscreen mode. This will override the value defined in the settings file.")
            ("no-fullscreen,o",   "Run in windowed mode. This will override the value defined in the settings file.")
            ("debug,d",           "Only relevant if -p option is present.  Startup with the dubugger attached.")
		    ("log-level,l",        boost::program_options::value<UInt32>(),
                                  "The logging level.  Higher values logs more information. 0=LOG_LOG,1=LOG_FATAL,2=LOG_WARNING,3=LOG_NOTICE,4=LOG_INFO,5=LOG_DEBUG.  This will override the value defined in the settings file.")
		    ("disable-log,y",      boost::program_options::value<bool>(),
                                  "Disables all logging.")
		    ("disable-file-log,z", boost::program_options::value<bool>(),
                                  "Disables logging to a file.")
		    ("log-file,g",         boost::program_options::value<std::string>(),
                                  "The file to route the logging to.  This will override the value defined in the settings file.  This option is only relavent if log-route is 3(LOG_FILE).")

#ifdef __APPLE__
		    ("process-serial-number", boost::program_options::value<std::string>(), "The process serial number when run as a Bundle in OS X.")
#endif
            ;

        _PositionalOptions.add("project-file", -1);
    }

    return _Instance;
}

void MainApplication::applyDefaultSettings(ApplicationSettings& TheSettings, bool overwriteIfDefined)
{
    TheSettings.put<BoostPath>("basic.data.directory", BoostPath("./share") / EngineAppDataDirectory, overwriteIfDefined);
    TheSettings.put<BoostPath>("basic.data.look_and_feel.path", BoostPath("./UI/LookAndFeel.xml") , overwriteIfDefined);
    
    TheSettings.put("basic.window.position",   Pnt2f(-1.0f,-1.0f), overwriteIfDefined);
    TheSettings.put("basic.window.size",       Vec2f(0.85f,0.85f), overwriteIfDefined);
    TheSettings.put("basic.window.fullscreen", false, overwriteIfDefined);

    TheSettings.put<UInt32>("basic.recent_projects.max", 8, overwriteIfDefined);

    TheSettings.put<bool>("basic.load_most_recent_project", true, overwriteIfDefined);
    TheSettings.put<std::string>("basic.initial_mode", "play", overwriteIfDefined);

    TheSettings.put<Real32>("basic.loading_viewport.camera.near_plane", 1.0f, overwriteIfDefined);
    TheSettings.put<Real32>("basic.loading_viewport.camera.far_plane", 100.0f, overwriteIfDefined);
    TheSettings.put<Real32>("basic.loading_viewport.camera.fov", 60.0f, overwriteIfDefined);
    TheSettings.put<Pnt3f> ("basic.loading_viewport.camera.position", Pnt3f(0.0f,0.0f, 0.0f), overwriteIfDefined);
    TheSettings.put<Color3f>("basic.loading_viewport.background.color", Color3f(0.0f,0.0f, 0.0f), overwriteIfDefined);
    TheSettings.put<BoostPath>("basic.loading_viewport.background.image_path",BoostPath("./UI/Loading.jpg"), overwriteIfDefined);

    TheSettings.put<Real32>("basic.default_scene.camera.near_plane", 0.1f, overwriteIfDefined);
    TheSettings.put<Real32>("basic.default_scene.camera.far_plane", 5000.0f, overwriteIfDefined);
    TheSettings.put<Real32>("basic.default_scene.camera.fov", 60.0f, overwriteIfDefined);
    TheSettings.put<Pnt3f>("basic.default_scene.camera.position", Pnt3f(0.0f,8.0f, 9.0f), overwriteIfDefined);
    
    TheSettings.put<bool>("basic.default_scene.torus.draw", true, overwriteIfDefined);
    TheSettings.put<Pnt3f>("basic.default_scene.torus.position", Pnt3f(0.0f,8.0f, 0.0f), overwriteIfDefined);
    
    TheSettings.put<bool>("basic.default_scene.box.draw", true, overwriteIfDefined);
    TheSettings.put<Pnt3f>("basic.default_scene.box.position", Pnt3f(5.0f,8.0f, 0.0f), overwriteIfDefined);
    
    TheSettings.put<bool>("basic.default_scene.cone.draw", true, overwriteIfDefined);
    TheSettings.put<Pnt3f>("basic.default_scene.cone.position", Pnt3f(-5.0f,8.0f, 0.0f), overwriteIfDefined);
    
    //TheSettings.put<bool>("basic.default_scene.point_light.draw", true, overwriteIfDefined);
    TheSettings.put<Pnt3f>("basic.default_scene.point_light.position", Pnt3f(0.0f,5.0f, 5.0f), overwriteIfDefined);
    
    TheSettings.put<Color3f>("basic.default_scene.background.color", Color3f(0.3f,0.3f,0.3f), overwriteIfDefined);

    //Logging
    TheSettings.put<UInt8>    ("logging.type",            LOG_FILE, overwriteIfDefined);
    TheSettings.put<UInt8>    ("logging.level",           LOG_NOTICE, overwriteIfDefined);
    TheSettings.put<BoostPath>("logging.file",            BoostPath("KabalaEngine.log"), overwriteIfDefined);
    TheSettings.put<UInt32>   ("logging.header_elements", (LOG_TYPE_HEADER | LOG_FUNCNAME_HEADER), overwriteIfDefined);
    TheSettings.put<bool>     ("logging.remove_old_logs", true, overwriteIfDefined);
    TheSettings.put<UInt32>   ("logging.max_old_logs",    3, overwriteIfDefined);

    //UI settings
    TheSettings.put<BoostPath>   ("ui.look_and_feel.xml_file",    BoostPath("LookAndFeel.xml"), overwriteIfDefined);

    //Player
    //Debugger
    TheSettings.put<std::string>("player.key_bindings", "", overwriteIfDefined);

    TheSettings.put<bool>   ("player.debugger.block_scene_input",           true, overwriteIfDefined);
    TheSettings.put<bool>   ("player.debugger.initially_active",           false, overwriteIfDefined);

    TheSettings.put<UInt32>("player.debugger.lua.console.max_history", 50, overwriteIfDefined);

    TheSettings.put<Color4f>("player.debugger.physics.collision_geom_color",          Color4f(0.5f,0.5f,1.0f,0.5f), overwriteIfDefined);

    TheSettings.put<Real32>("player.debugger.camera.near_plane", 0.1f, overwriteIfDefined);
    TheSettings.put<Real32>("player.debugger.camera.far_plane", 5000.0f, overwriteIfDefined);
    TheSettings.put<Real32>("player.debugger.camera.fov", 60.0f, overwriteIfDefined);

    TheSettings.put<bool>   ("player.debugger.grid.draw",           true, overwriteIfDefined);
    TheSettings.put<Vec2f>  ("player.debugger.grid.dimensions",     Vec2f(100.0f,100.0f), overwriteIfDefined);
    TheSettings.put<Real32> ("player.debugger.grid.segment_length", 1.0f, overwriteIfDefined);
    TheSettings.put<Color3f>("player.debugger.grid.color",          Color3f(0.7f,0.7f,0.7f), overwriteIfDefined);
    TheSettings.put<Real32> ("player.debugger.grid.line_thickness", 1.0f, overwriteIfDefined);

    
    TheSettings.put<bool>   ("player.debugger.undo_history.enable", true, overwriteIfDefined);
    TheSettings.put<Int32> ("player.debugger.undo_history.max_length", 200, overwriteIfDefined);

    TheSettings.put<bool>   ("player.debugger.selected_node.volume_box.draw", true, overwriteIfDefined);
    TheSettings.put<Color4f>("player.debugger.selected_node.volume_box.color", Color4f(0.0f,1.0f,1.0f,1.0f), overwriteIfDefined);
    TheSettings.put<Real32> ("player.debugger.selected_node.volume_box.line_thickness", 2.0f, overwriteIfDefined);

    TheSettings.put<bool>   ("player.debugger.selected_node.axis.draw", true, overwriteIfDefined);
    TheSettings.put<Color4f>("player.debugger.selected_node.axis.x_axis_color", Color4f(1.0f,0.0f,0.0f,1.0f), overwriteIfDefined);
    TheSettings.put<Color4f>("player.debugger.selected_node.axis.y_axis_color", Color4f(0.0f,1.0f,0.0f,1.0f), overwriteIfDefined);
    TheSettings.put<Color4f>("player.debugger.selected_node.axis.z_axis_color", Color4f(0.0f,0.0f,1.0f,1.0f), overwriteIfDefined);
    TheSettings.put<Real32> ("player.debugger.selected_node.axis.line_thickness", 2.0f, overwriteIfDefined);
    TheSettings.put<Real32> ("player.debugger.selected_node.axis.relative_length", 0.55f, overwriteIfDefined);

    TheSettings.put<Real32> ("player.debugger.transform_manip.axis.relative_length", 0.55f, overwriteIfDefined);

    TheSettings.put<bool>   ("player.debugger.selected_node.mesh.draw", true, overwriteIfDefined);
    TheSettings.put<Color4f>("player.debugger.selected_node.mesh.color", Color4f(1.0f,0.0f,1.0f,1.0f), overwriteIfDefined);
    TheSettings.put<Real32> ("player.debugger.selected_node.mesh.line_thickness", 1.0f, overwriteIfDefined);

    
    TheSettings.put<bool>      ("player.debugger.auto_save_project.enabled",       true, overwriteIfDefined);
    TheSettings.put<Real32>    ("player.debugger.auto_save_project.time_between",  120.0f, overwriteIfDefined);
    TheSettings.put<BoostPath> ("player.debugger.auto_save_project.recovery_file", BoostPath("./KabalaEngineProject.xml.recovery"), overwriteIfDefined);

	TheSettings.put<bool>      ("player.debugger.model_import.trav_mask_graph_op.enabled", true, overwriteIfDefined);

	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.match_name",                true, overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.trav_mask_graph_op.search_regex",              ".*_Col$", overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.match_whole_name",          true, overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.match_node_core_type",      false, overwriteIfDefined);
    TheSettings.put<std::string>("player.debugger.trav_mask_graph_op.node_core_typename",        "Drawable", overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.match_derived_core_types",  true, overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.match_trav_mask",           false, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.trav_mask_graph_op.match_trav_mask_value",     1, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.trav_mask_graph_op.match_mask_condition",      0, overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.apply_mask_to_decendents",  false, overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.trav_mask_graph_op.apply_to_non_matching",     false, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.trav_mask_graph_op.applied_trav_mask",         0, overwriteIfDefined);
	TheSettings.put<UInt8>      ("player.debugger.trav_mask_graph_op.apply_trav_mask_operation", 0, overwriteIfDefined);
	
	TheSettings.put<Vec3f>      ("player.debugger.lod_graph_op.lod_ranges", Vec3f(50.0f,100.0f,300.0f), overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.lod_graph_op.lod_high_tag", "_High", overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.lod_graph_op.lod_mid_tag", "_Mid", overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.lod_graph_op.lod_low_tag", "_Low", overwriteIfDefined);

	TheSettings.put<UInt16>("player.debugger.split_graph_op.max_polygons",1500,overwriteIfDefined);

	TheSettings.put<std::string>("player.debugger.share_ptr_graph_op.includes", "", overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.share_ptr_graph_op.excludes", "", overwriteIfDefined);

	TheSettings.put<std::string>("player.debugger.prune_graph_op.method", "sum_of_dimensions", overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.prune_graph_op.size", "1.0", overwriteIfDefined);

	TheSettings.put<std::string>("player.debugger.geo_merge_graph_op.max_geos_to_merge","200",overwriteIfDefined);

    //Attach Collision Geom Graph Op
	TheSettings.put<bool>       ("player.debugger.col_geom_graph_op.match_name",                true, overwriteIfDefined);
	TheSettings.put<std::string>("player.debugger.col_geom_graph_op.search_regex",              ".*_Col$", overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.col_geom_graph_op.match_whole_name",          true, overwriteIfDefined);
	TheSettings.put<bool>       ("player.debugger.col_geom_graph_op.match_trav_mask",           false, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.col_geom_graph_op.match_trav_mask_value",     1, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.col_geom_graph_op.match_mask_condition",      0, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.col_geom_graph_op.create_geom_type",          0, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.col_geom_graph_op.collide_mask",          4294967295, overwriteIfDefined);
	TheSettings.put<UInt32>     ("player.debugger.col_geom_graph_op.category_mask",          4294967295, overwriteIfDefined);


#ifdef BUILD_WITH_WORLD_BUILDER
    //Builder Settings
    TheSettings.put<BoostPath>("builder.ui.main_window.path", BoostPath("./UI/Builder/MainWindow.xml") , overwriteIfDefined);
    TheSettings.put<BoostPath>("builder.ui.about_window.path", BoostPath("./UI/Builder/AboutWindow.xml") , overwriteIfDefined);
    TheSettings.put<BoostPath>("builder.ui.credits_window.path", BoostPath("./UI/Builder/CreditsWindow.xml") , overwriteIfDefined);
    TheSettings.put<BoostPath>("builder.ui.visual_annotations.camera.path", BoostPath("./UI/Models/Camera.osb") , overwriteIfDefined);
    
#endif
}

ApplicationSettings MainApplication::createDefaultSettings(void)
{
    SLOG << "Creating default settings." << std::endl;
    ApplicationSettings DefaultSettings;
    applyDefaultSettings(DefaultSettings, true);

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
    //Get the date/time run
    _DateTimeRun = boost::posix_time::second_clock::local_time();

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
                                      options(_OptionsDescription).
#ifdef __APPLE__
                                      extra_parser(procSerialNumParser).
#endif
                                      positional(_PositionalOptions).run(), OptionsVariableMap);

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

    _LogFilePath = getLoggingDir()
                 / BoostPath(boost::posix_time::to_iso_string(_DateTimeRun) + ".log");  //ISO date/time format
    if(OptionsVariableMap.count("log-file"))
    {
        _LogFilePath = BoostPath(OptionsVariableMap["log-file"].as<std::string>());
    }
    if(OptionsVariableMap.count("disable-log"))
    {
        _EnableLogging = false;
    }
    if(OptionsVariableMap.count("disable-file-log"))
    {
        _LogToFile = false;
    }

    initializeLogging(_LogFilePath);
    osgLogP->setLogLevel(KELogLevel, true);
	osgLogP->setHeaderElem((LOG_TYPE_HEADER | LOG_FUNCNAME_HEADER), true);

    //Check if the last run crashed
    if(didCrashLastExecution())
    {
        handleCrashLastExecution();
    }

    //Create a file to indicate if a crash occurs
    createCrashIndicationFile();

    // Set up Settings
    //Check for the settings file
    if(OptionsVariableMap.count("settings-file"))
    {
        setSettingsLoadFile(BoostPath(OptionsVariableMap["settings-file"].as<std::string>()));
    }
    else
    {
        //Use default location
        setSettingsLoadFile(getUserAppDataDir()
                          / BoostPath("KEDefaultSettings.xml"));
    }
    loadSettings(getSettingsLoadFile());

    //Cleanup the Logging Directory
    cleanupLoggingDir();

    //If the settings aren't being overriden by the command-line options
    //then set the logging with the settings values
    if(!OptionsVariableMap.count("log-level"))
    {
        osgLogP->setLogLevel(static_cast<LogLevel>(getSettings().get<UInt8>("logging.level")), true);
    }
	osgLogP->setHeaderElem(getSettings().get<UInt32>("logging.header_elements"), true);

    //Initialize OpenSG
    initOpenSG(argc,argv);

    //Log information about the Engine
    {
        PLOG << "Starting Kabala Engine:" << std::endl;
        OSG::indentLog(4,PLOG);
        PLOG << "Arguments: ";
        for(UInt32 i(0) ; i<argc ; ++i)
        {
            PLOG << argv[i] << " ";
        }
        PLOG << std::endl;

        OSG::indentLog(4,PLOG);
        PLOG << "System:" << std::endl;
        OSG::indentLog(8,PLOG);
        PLOG << "Operating System: " << getPlatformName() << std::endl;
        OSG::indentLog(8,PLOG);
        PLOG << "Processor: " << getPlatformProcessors() << std::endl;
        OSG::indentLog(8,PLOG);
        PLOG << "RAM: " << getPlatformRAM() << std::endl;
        OSG::indentLog(4,PLOG);
        PLOG << "Time: " << to_simple_string(_DateTimeRun) << std::endl;
        OSG::indentLog(4,PLOG);
        PLOG << "Version: " << getKabalaEngineVersion() << std::endl;
        OSG::indentLog(8,PLOG);
        PLOG << "Revision: " << getKabalaEngineBuildRepositoryRevision() << std::endl;
        OSG::indentLog(8,PLOG);
        PLOG << "Build Type: " << getKabalaEngineBuildType() << std::endl;
        OSG::indentLog(4,PLOG);
        PLOG << "Working Directory: " << boost::filesystem::current_path().string() << std::endl;
        OSG::indentLog(4,PLOG);
        PLOG << "Executable Directory: " << CommandPath.parent_path().string() << std::endl;
        OSG::indentLog(4,PLOG);
        PLOG << "Settings File: " << getSettingsLoadFile().string() << std::endl;

        OSG::indentLog(4,PLOG);
        PLOG << "Logging: " << (_EnableLogging ? "Enabled" : "Disabled" ) << std::endl;
        if(_EnableLogging)
        {
            OSG::indentLog(8,PLOG);
            PLOG << "Log File: " << (_LogToFile ? _LogFilePath.string() : "Disabled" ) << std::endl;
        }
    }

    //Check if the Data Directory exists
    if(!boost::filesystem::exists(getSettings().get<BoostPath>("basic.data.directory")))
    {
        BoostPath DataDirPath(getSettings().get<BoostPath>("basic.data.directory"));
        DataDirPath = boost::filesystem::complete(DataDirPath);
        DataDirPath.normalize();
        SWARNING << "Could not find Application Data directory: \""
                 << DataDirPath.string()
                 << "\" specified in the Settings file because the directory doesn't exist." << std::endl;

        //Try to find the data directory in a few locations
        std::vector<BoostPath> PathsToTry;

#ifdef __APPLE__
        PathsToTry.push_back(CommandPath.parent_path() /
                             BoostPath("../Resources") /
                             EngineAppDataDirectory);       //Path to try for OS X Bundles
        PathsToTry.push_back(CommandPath.parent_path() /
                             BoostPath("../Resources/share") /
                             EngineAppDataDirectory);       //Path to try for OS X Bundles
#endif

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
                getSettings().put("basic.data.directory",PathsToTry[i]);
                break;
            }
            else
            {
                PNOTICE << "NOT FOUND" << std::endl;
            }
        }
    }

    if(!boost::filesystem::exists(getSettings().get<BoostPath>("basic.data.directory")))
    {
        SWARNING << "Could not find Application Data directory: \""
                 << getSettings().get<BoostPath>("basic.data.directory").string()
                 << "\" because the directory doesn't exist." << std::endl;
    }
    else
    {
        SLOG << "Using Application Data directory: \""
                 << getSettings().get<BoostPath>("basic.data.directory").string()
                 << "\"" << std::endl;
    }

    // Set up Window
    WindowEventProducerUnrecPtr MainWindow(createNativeWindow());
    setMainWindow(MainWindow);
    setName(getMainWindow(),"__KABALA_ENGINE_WINDOW_EVENT_PRODUCER");

    //If Fullscreen option -> Fullscreen
    if(OptionsVariableMap.count("fullscreen"))
    {
        getMainWindow()->setFullscreen(true);
    }
    //If no-fullscreen     -> not Fullscreen
    else if(OptionsVariableMap.count("no-fullscreen"))
    {
        getMainWindow()->setFullscreen(false);
    }
    //else                 -> use the value in the settings
    else
    {
        getMainWindow()->setFullscreen(getSettings().get<bool>("basic.window.fullscreen"));
    }

    getMainWindow()->initWindow();

    _WindowClosingConnection = getMainWindow()->connectWindowClosing(boost::bind(&MainApplication::handleWindowClosing, this, _1));
    _WindowClosedConnection = getMainWindow()->connectWindowClosed(boost::bind(&MainApplication::handleWindowClosed, this, _1));

    // Initialize the LookAndFeelManager to enable default settings
    KELookAndFeel::the()->init();


    //Open Window
    Vec2f WindowSize(getSettings().get<Vec2f>("basic.window.size"));
    if(getSettings().get<Vec2f>("basic.window.size").x() <= 1.0f )
    {
        WindowSize[0] = getMainWindow()->getDesktopSize().x() * getSettings().get<Vec2f>("basic.window.size").x();
    }
    if(getSettings().get<Vec2f>("basic.window.size").y() <= 1.0f )
    {
        WindowSize[1] = getMainWindow()->getDesktopSize().y() * getSettings().get<Vec2f>("basic.window.size").y();
    }
    Pnt2f WindowPos(getSettings().get<Pnt2f>("basic.window.position"));
    if(getSettings().get<Pnt2f>("basic.window.position").x() < 0.0f )
    {
        WindowPos[0] = (getMainWindow()->getDesktopSize().x() - WindowSize.x()) * 0.5f;
    }
    if(getSettings().get<Pnt2f>("basic.window.position").y() < 0.0f )
    {
        WindowPos[1] = (getMainWindow()->getDesktopSize().y() - WindowSize.y()) * 0.5f;
    }

    getMainWindow()->openWindow(WindowPos,
                                WindowSize,
                                "Kabala Engine");

        
    //Store a pointer to the application thread
    //_ApplicationThread = dynamic_cast<OSG::Thread *>(OSG::ThreadManager::getAppThread());
    
    //Create the rendering thread
    //_RenderThread = OSG::dynamic_pointer_cast<OSG::Thread>(OSG::ThreadManager::the()->getThread("__KABALA_ENGINE_RENDER_THREAD", true));
    
    //Create the loading thread
    //_LoadingThread = OSG::dynamic_pointer_cast<OSG::Thread>(OSG::ThreadManager::the()->getThread("__KABALA_ENGINE_LOADING_THREAD", true));

    //Draw the loading thread
    activateLoadingScreen();

    //Load the Project file, if given
    if(OptionsVariableMap.count("project-file"))
    {
        loadProject(BoostPath(OptionsVariableMap["project-file"].as<std::string>()));
    }
    else if(getSettings().get<bool>("basic.load_most_recent_project"))
    {
        boost::optional<BoostPath> LastOpenedProjectFile = getSettings().get_optional<BoostPath>("basic.last_opened_project");
        if(LastOpenedProjectFile)
        {
            loadProject(LastOpenedProjectFile.get());
            commitChanges();
        }
    }

    if(getProject() == NULL)
    {
        //Project Failed to load, or file didn't exist
        ProjectRecPtr NewProject = createDefaultProject();
        setProject(NewProject);
    }

    //Detach the loading screen
    detachLoadingScreen();

#ifdef BUILD_WITH_WORLD_BUILDER
    if(OptionsVariableMap.count("builder"))
    {
        attachBuilder();
    }
    else 
#endif
        if(OptionsVariableMap.count("play"))
    {
        attachPlayer();
        if(OptionsVariableMap.count("debug"))
        {
            dynamic_cast<ApplicationPlayer*>(getPlayerMode())->enableDebug(true);
        }
    }
    else
    {
#ifdef BUILD_WITH_WORLD_BUILDER
        if(getSettings().get<std::string>("basic.initial_mode").compare(std::string("builder")) == 0)
        {
            attachBuilder();
        }
        else
#endif
            if(getSettings().get<std::string>("basic.initial_mode").compare(std::string("play")) == 0)
        {
            attachPlayer();
            if(OptionsVariableMap.count("debug") || getSettings().get<bool>("player.debugger.initially_active"))
            {
                dynamic_cast<ApplicationPlayer*>(getPlayerMode())->enableDebug(true);
            }
        }
        else
        {
            attachStartScreen();
        }
    }
    
    //Start the render thread on aspect 1
    //_RenderThread->runFunction(MainApplication::mainRenderLoop, 1, NULL);
    
    //Start the loading thread on aspect 2
    //_LoadingThread->runFunction(MainApplication::mainLoadingLoop, 2, NULL);

    //Main Loop
    getMainWindow()->mainLoop();

    //Exited Main Loop
    //Save Settings
    saveSettings(getSettingsLoadFile());
    
    SLOG << "Stopping Kabala Engine" << std::endl;
    OSG::indentLog(4,PLOG);
    PLOG << "Time: " << to_simple_string(boost::posix_time::second_clock::local_time()) << std::endl;

	//OSG exit
    OSG::osgExit();

    //Uninitialize logging
    uninitializeLogging();

    //Create a file to indicate if a crash occurs
    removeCrashIndicationFile();

    return 0;
}

void MainApplication::initOpenSG(int argc, char **argv)
{
    //Ensure that libraries are loaded
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

    //Set the number of aspects
    //ThreadManager::setNumAspects(2);

    //Set the read/write default to true
    //ChangeList::setReadWriteDefault(true);

    // OSG init
	OSG::osgInit(argc,argv);
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

#ifdef BUILD_WITH_WORLD_BUILDER
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

void MainApplication::createDefaultBuilderMode(void)
{
    if(getBuilderMode() == NULL)
    {
        ApplicationModeRecPtr BuilderMode = ApplicationBuilder::create();
        setBuilderMode(BuilderMode);
    }
}

void MainApplication::setBuilderMode( ApplicationMode* const value )
{
    _BuilderMode = value;
}
#endif

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

        updateRecentProject(ProjectFile);
    }
}

void MainApplication::updateRecentProject(const BoostPath& ProjectFile)
{
    getSettings().put<BoostPath>("basic.last_opened_project",ProjectFile);

    //Update Recent Projects
    std::vector<BoostPath> RecentProjects;
    
    try
    {
        RecentProjects = getSettings().get_vec<BoostPath>("basic.recent_projects.files");
    }
    catch(boost::property_tree::ptree_bad_path&)
    {
    }

    std::vector<BoostPath>::iterator SearchItor(RecentProjects.begin());
    for( ; SearchItor!=RecentProjects.end() ; ++SearchItor)
    {
        if(boost::filesystem::equivalent((*SearchItor),ProjectFile))
        {
            break;
        }
    }
    if(SearchItor != RecentProjects.end())
    {
        RecentProjects.erase(SearchItor);
    }
    RecentProjects.insert(RecentProjects.begin(), ProjectFile);

    //Resize
    UInt32 MaxRecProj(getSettings().get<UInt32>("basic.recent_projects.max"));
    if(RecentProjects.size() > MaxRecProj)
    {
        //Pop off the front
        RecentProjects.resize(MaxRecProj);
    }


    getSettings().put_vec("basic.recent_projects.files.file", RecentProjects);

}

void MainApplication::loadProject(const BoostPath& ProjectFile)
{
    ProjectRefPtr LoadedProject = Project::load(ProjectFile);

    if(LoadedProject != NULL)
    {
        setProject(LoadedProject);
        updateRecentProject(ProjectFile);
    }
}

void MainApplication::saveSettings(const BoostPath& SettingsFile)
{
    getSettings().writeXML(SettingsFile);
}

void MainApplication::loadSettings(const BoostPath& SettingsFile)
{

    ApplicationSettings LoadedSettings;
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

        LoadedSettings.readXML(SettingsFile);
    }
    //Apply default settings to any settings that are not defined in loaded settings files
    applyDefaultSettings(LoadedSettings, false);
    setSettings(LoadedSettings);
}

void MainApplication::createDefaultPlayerMode(void)
{
    if(getPlayerMode() == NULL)
    {
        ApplicationPlayerUnrecPtr player = ApplicationPlayer::create();
        setPlayerMode(player);
    }
}

void MainApplication::createDefaultStartScreenMode(void)
{
    if(getStartScreenMode() == NULL)
    {
        ApplicationStartScreenUnrecPtr startScreen = ApplicationStartScreen::create();
        setStartScreenMode(startScreen);
    }
}

void MainApplication::exit(void)
{
    getMainWindow()->closeWindow();
}



void MainApplication::setSettings( const ApplicationSettings &value )
{
    _Settings = value;
}

void MainApplication::setSettingsLoadFile( const BoostPath &value )
{
    _SettingsPath = value;
}

void MainApplication::setMainWindow( WindowEventProducer* const value )
{
    _MainWindow = value;
}

void MainApplication::setProject ( Project* const value )
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

void MainApplication::setPlayerMode( ApplicationMode* const value )
{
    _PlayerMode = value;
}

void MainApplication::setStartScreenMode( ApplicationMode* const value )
{
    _StartScreenMode = value;
}

void MainApplication::setCurrentMode( ApplicationMode* const value )
{
    _CurrentMode = value;
}

void MainApplication::produceLog(LogEventDetailsType* const e)
{
    ConsumableEventCombiner comb(static_cast<EventDetails* const>(e));
    _LogEvent.set_combiner(comb);
    _LogEvent(e, LogEventId);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MainApplication::KELogBufferCallback(const Char8 *data, 
                         Int32  size,
                         void  *clientData)
{
    std::string value(data,size);

    //Log to the logfile
    if(MainApplication::the()->_LogToFile)
    {
        MainApplication::the()->_LogFile << value;
    }

    if(GlobalSystemState == Running)
    {
	    //Send to the Log Listeners
        LogEventDetailsUnrecPtr details = LogEventDetails::create(NULL, getTimeStamp(),value);
        MainApplication::the()->produceLog(details);
    }
}

bool MainApplication::CompLogFileDates::operator()(const BoostPath& Left, const BoostPath Right)
{
    //Get the filenames
    std::string LeftName(Left.stem());
    std::string RightName(Right.stem());

    //Convert the ISO formatted strings into time objects
    boost::posix_time::ptime LeftTime(boost::posix_time::from_iso_string(LeftName));
    boost::posix_time::ptime RightTime(boost::posix_time::from_iso_string(RightName));

    //Return time comparison
    //Oldest to Newest
    return LeftTime < RightTime;
}

void MainApplication::cleanupLoggingDir(void)
{
    //Determine if old log files need to be removed
    if(getSettings().get<bool>("logging.remove_old_logs") &&
       boost::filesystem::exists(getLoggingDir()))
    {
        std::vector<BoostPath> LogFiles;
        boost::filesystem::directory_iterator EndItor; // default construction yields past-the-end
        for ( boost::filesystem::directory_iterator DirItor( getLoggingDir() );
              DirItor != EndItor;
              ++DirItor )
        {
            //Remove all non-logging files
            if ( boost::filesystem::extension(DirItor->path()).compare(".log") !=0 )
            {
                boost::filesystem::remove(DirItor->path());
            }
            else
            {
                //Get all of the log files
                LogFiles.push_back(DirItor->path());
            }
        }

        UInt32 NumLogFiles(LogFiles.size());

        //Determine the number of log files to remove
        //   = Num of Log files - Max old logs
        UInt32 NumToRemove(osgMax<Int32>(0,NumLogFiles - static_cast<Int32>(getSettings().get<UInt32>("logging.max_old_logs"))));

        //Sort the LogFiles by date
        std::sort(LogFiles.begin(), LogFiles.end(), CompLogFileDates());

        //Remove the NumToRemove oldest logs
        for(UInt32 i(0) ; i<NumToRemove ; ++i)
        {
            try
            {
                boost::filesystem::remove(LogFiles[i]);
                SLOG << "Removed old log: " << LogFiles[i].string() << std::endl;
            }
            catch(std::exception& ex)
            {
                SWARNING << "Unable to remove log file: " << LogFiles[i].string() << ". Because " << ex.what() << std::endl;
            }
        }
    }

}

void MainApplication::initializeLogging(BoostPath KELogFilePath)
{
    if(_EnableLogging)
    {
        //Configure the LogBuffer
        osgLogP->setLogType(LOG_BUFFER, true);

        //Configure the LogBuffer
        osgLogP->getLogBuf().setEnabled(true);
        osgLogP->getLogBuf().setCallback(KELogBufferCallback);

	    if(_LogToFile)
	    {
            //Make sure the directory is created
            try
            {
                boost::filesystem::create_directories(KELogFilePath.parent_path());
            }
            catch(std::exception& ex)
            {
                SWARNING << "Failed to create directory: " << KELogFilePath.parent_path() 
                         << ", error: " << ex.what() << std::endl;
	            return;
            }

		    //If the Log is to a file then set the filev
            _LogFile.open(KELogFilePath.string().c_str());
        }
    }
    else
    {
        //Disable all logging
        osgLogP->setLogType(LOG_NONE, true);
    }
}

void MainApplication::uninitializeLogging(void)
{
    if(_EnableLogging && _LogToFile)
    {
        _LogFile.close();
    }
}

void MainApplication::createCrashIndicationFile(void)
{
    BoostPath TheFilePath(getCrashIndicationFilePath());
    if(!boost::filesystem::exists(TheFilePath))
    {
        std::ofstream IndicatorFile(TheFilePath.string().c_str());
        IndicatorFile << to_iso_string(_DateTimeRun);
        IndicatorFile.close();
    }
}

void MainApplication::removeCrashIndicationFile(void)
{
    BoostPath TheFilePath(getCrashIndicationFilePath());
    if(boost::filesystem::exists(TheFilePath))
    {
        try
        {
            boost::filesystem::remove(TheFilePath);
            SLOG << "Destroying crash indicator file " << std::endl;
        }
        catch(std::exception& ex)
        {
            SWARNING << "Unable to crash indicator file: " << TheFilePath.string() << ". Because " << ex.what() << std::endl;
        }
    }
}

bool MainApplication::didCrashLastExecution(void) const
{
    return boost::filesystem::exists(getCrashIndicationFilePath());
}

BoostPath MainApplication::getCrashIndicationFilePath(void) const
{
    return getUserAppDataDir() / "CrashIndicator";
}

void MainApplication::handleCrashLastExecution(void)
{
    //Get the details of the crash
    std::ifstream IndicatorFile(getCrashIndicationFilePath().string().c_str());
    std::ostringstream Contents;
    Contents << IndicatorFile.rdbuf();
    IndicatorFile.close();

    boost::posix_time::ptime DateTimeCrashRun = boost::posix_time::from_iso_string(Contents.str());
    SLOG << "KabalaEngine crashed the last time it was run at " << boost::posix_time::to_simple_string(DateTimeCrashRun) << std::endl;

    removeCrashIndicationFile();
}

 void MainApplication::attachLoadingScreen(void)
 {
     if(_LoadingViewport == NULL)
     {
         _LoadingViewport = createDefaultLoadingViewport();
     }
     getMainWindow()->addPort(_LoadingViewport);
 }

 void MainApplication::activateLoadingScreen(void)
 {
     attachLoadingScreen();
     getMainWindow()->draw();
 }
 
 void MainApplication::detachLoadingScreen(void)
 {
     getMainWindow()->subPortByObj(_LoadingViewport);
 }

 void MainApplication::dectivateLoadingScreen(void)
 {
     detachLoadingScreen();
 }

void MainApplication::mainRenderLoop(void* args)
{
    OSG::osgSleep(5000);
    //Render
    while(true)
    {
        //Sync data
        the()->getApplicationThread()->getChangeList()->applyAndClear();

        //Draw
        the()->getMainWindow()->draw();
    }
}

void MainApplication::mainLoadingLoop(void* args)
{
    //Load
    while(true)
    {
    }
}

/*----------------------- constructors & destructors ----------------------*/

MainApplication::MainApplication(void) :
    _EnableLogging(true),
    _LogToFile(true)
{
}

MainApplication::MainApplication(const MainApplication &source)
{
    assert(false && "MainApplication is a singleton, copy constructor should never be reached");
}

MainApplication::~MainApplication(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MainApplication::handleWindowClosing(WindowEventDetails* const details)
{
}

void MainApplication::handleWindowClosed(WindowEventDetails* const details)
{
    _WindowClosingConnection.disconnect();
    _WindowClosedConnection.disconnect();
}

