
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
PROJECT("KabalaEngine")

#SET (CMAKE_VERBOSE_MAKEFILE TRUE)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Builds/cmake")

####### Declaration of functions
FUNCTION(RECURSIVE_DIRECTORY_FIND DIR IGNORE_DIRS_MATCHING STRIP_PATH)
    #Get the source files
    FILE(GLOB HEADERS ${DIR}/[^~]*.h)
    FILE(GLOB SOURCES ${DIR}/[^~]*.cpp)
    FILE(GLOB INLINES ${DIR}/[^~]*.inl)
    
    #Strip the path down to a relative one
    FILE(RELATIVE_PATH THE_SOURCE_GROUP ${STRIP_PATH} ${DIR})
    IF(THE_SOURCE_GROUP)
        STRING(REPLACE "/" "\\" THE_SOURCE_GROUP ${THE_SOURCE_GROUP})
    ELSE(THE_SOURCE_GROUP)
        SET(THE_SOURCE_GROUP "\\")
    ENDIF(THE_SOURCE_GROUP)
    
    
    SOURCE_GROUP(${THE_SOURCE_GROUP} FILES ${HEADERS} ${SOURCES} ${INLINES})
    
    FILE(GLOB THE_DIRS_AND_FILES ${DIR}/*)
    
    FOREACH(THE_PATH ${THE_DIRS_AND_FILES})
        IF(IS_DIRECTORY ${THE_PATH})
            IF(${THE_PATH} MATCHES "${IGNORE_DIRS_MATCHING}")
            ELSE(${THE_PATH} MATCHES "${IGNORE_DIRS_MATCHING}")
                #Call this function on all directories within this one
                RECURSIVE_DIRECTORY_FIND(${THE_PATH} ${IGNORE_DIRS_MATCHING} ${STRIP_PATH})
    
            ENDIF(${THE_PATH} MATCHES "${IGNORE_DIRS_MATCHING}")
        ENDIF(IS_DIRECTORY ${THE_PATH})
    ENDFOREACH(THE_PATH in ${THE_DIRS_AND_FILES})
ENDFUNCTION(RECURSIVE_DIRECTORY_FIND DIR IGNOR_DIRS_MATCHING)

######### Repository Information
FIND_PACKAGE(Git)
IF(GIT_FOUND)
    GIT_REPOSITORY_INFO(${CMAKE_SOURCE_DIR} KABALA_ENGINE)
ELSE()
    MESSAGE("Git not found")
ENDIF(GIT_FOUND)

######### Version
FILE(STRINGS ${CMAKE_SOURCE_DIR}/VERSION VersionFile)
STRING(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+).*" VersionMatch ${VersionFile})

SET(KABALA_ENGINE_MAJOR_VERSION ${CMAKE_MATCH_1})
SET(KABALA_ENGINE_MINOR_VERSION ${CMAKE_MATCH_2})
SET(KABALA_ENGINE_PATCH_VERSION ${CMAKE_MATCH_3})
SET(KABALA_ENGINE_VERSION ${CMAKE_MATCH_0})
MESSAGE("Current Version is ${KABALA_ENGINE_VERSION}")

######## Authors
FILE(STRINGS ${CMAKE_SOURCE_DIR}/AUTHORS.txt KABALA_ENGINE_AUTHORS)

######## Website
FILE(STRINGS ${CMAKE_SOURCE_DIR}/WEBSITE.txt KABALA_ENGINE_WEBSITE)

######## IS 64 bit
IF( NOT APPLE )
    # check 64 bit
    IF( ${CMAKE_SIZEOF_VOID_P} EQUAL 4 )
        SET( HAVE_64_BIT 0 )
        MESSAGE("32 bit")
    ELSE( ${CMAKE_SIZEOF_VOID_P} EQUAL 4 )
        SET( HAVE_64_BIT 1 )
        MESSAGE("64 bit")
    ENDIF( ${CMAKE_SIZEOF_VOID_P} EQUAL 4 )
ELSE( NOT APPLE )
    SET( HAVE_64_BIT 0)
ENDIF( NOT APPLE )

######### OS X Specifics
IF(APPLE)
    SET(PLATFORM_COMPILE_FLAGS  "-arch i386 -mmacosx-version-min=10.5")
    SET(PLATFORM_LINKER_FLAGS "-arch i386 -mmacosx-version-min=10.5")
    SET(ENV{MACOSX_DEPLOYMENT_TARGET} 10.5)
ENDIF(APPLE)

######## Default Build Type
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug")
ENDIF(NOT CMAKE_BUILD_TYPE)

#############
######### OpenSG
SET(OSG_COMPONENTS OSGBase 
    OSGDrawable 
    OSGFileIO 
    OSGImageFileIO 
    OSGDynamics 
    OSGGroup 
    OSGState 
    OSGSystem 
    OSGUtil 
    OSGWindow 
    OSGText 
    OSGEffectGroups 
    OSGTBFileIO 
    OSGTBAnimation 
    OSGContribUserInterface 
    OSGContribGUI 
    OSGContribSound 
    OSGContribLua 
    OSGContribLuaToolbox 
    OSGContribVideo 
    OSGContribPhysics 
    OSGContribParticleSystem
    OSGContribFieldContainerEditor
    )

IF(UNIX)
    IF(APPLE)
        LIST(APPEND OSG_COMPONENTS OSGWindowCarbon)
    ELSE(APPLE)
        LIST(APPEND OSG_COMPONENTS OSGWindowX)
    ENDIF(APPLE)
ENDIF(UNIX)

IF(WIN32)
    LIST(APPEND OSG_COMPONENTS OSGWindowWIN32)
ENDIF(WIN32)

FIND_PACKAGE(OpenSG REQUIRED COMPONENTS ${OSG_COMPONENTS})
SET(OpenSG_BINARIES_DIR "${OpenSG_DIR}/bin/rel")

#############
######## BOOST
FIND_PACKAGE(Boost COMPONENTS system filesystem program_options date_time)
SET(Boost_USE_MULTITHREAD ON)
SET(Boost_STATIC_LIBS OFF)

IF(Boost_FOUND AND Boost_MINOR_VERSION GREATER "38")
    SET(Boost_COMPONENTS system ${Boost_COMPONENTS})

    FIND_PACKAGE(Boost COMPONENTS ${Boost_COMPONENTS} REQUIRED)
ENDIF(Boost_FOUND AND Boost_MINOR_VERSION GREATER "38")

IF(Boost_FOUND)
    LIST(APPEND DEP_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    LIST(APPEND DEP_LIBRARY_DIRS ${Boost_LIBRARY_DIRS})
    IF(NOT WIN32)
        LIST(APPEND DEP_LIBRARIES ${Boost_SYSTEM_LIBRARY})
        LIST(APPEND DEP_LIBRARIES ${Boost_FILESYSTEM_LIBRARY})
        LIST(APPEND DEP_LIBRARIES ${Boost_PROGRAM_OPTIONS_LIBRARY})
        LIST(APPEND DEP_LIBRARIES ${Boost_DATE_TIME_LIBRARY})
    ENDIF(NOT WIN32)
    
    SET(BOOST_BIN_DIR ${Boost_LIBRARY_DIRS})
    STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} Boost_SYSTEM_LIBRARY_BIN ${Boost_SYSTEM_LIBRARY_RELEASE})
    STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} Boost_FILESYSTEM_LIBRARY_BIN ${Boost_FILESYSTEM_LIBRARY_RELEASE})
    STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} Boost_PROGRAM_OPTIONS_LIBRARY_BIN ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE})
    #STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} Boost_DATE_TIME_LIBRARY_BIN ${Boost_DATE_TIME_LIBRARY_RELEASE})
ENDIF(Boost_FOUND)

#############
#### OpenGL
#############

FIND_PACKAGE(OpenGL REQUIRED)
LIST(APPEND DEP_LIBRARIES ${OPENGL_LIBRARIES})

#############
#### Cuda (optional, depending on how OpenSG was built)

FIND_PACKAGE(CUDA)

IF(CUDA_FOUND)
    SET(CUDA_LIBRARY_DIRS "${CUDA_TOOLKIT_ROOT_DIR}/lib")
ENDIF()

#############
#### Collada (optional, depending on how OpenSG was built)

FIND_PACKAGE(Collada)

IF(COLLADA_FOUND)
    SET(COLLADA_BIN_DIR ${COLLADA_LIBRARY_DIRS})
    STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} COLLADA_BINARY ${COLLADA_LIBRARY_RELEASE})
ENDIF(COLLADA_FOUND)

#############
#### CgFX (optional, depending on how OpenSG was built)

FIND_PACKAGE(Cg)

#IF(CG_FOUND)
    #SET(CG_BIN_DIR ${CG_INCLUDE_DIR}/../lib)
    #STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} CG_BINARY ${CG_LIBRARY})
    #STRING(REPLACE "/lib/" "/bin/" CG_BINARY ${CG_BINARY})
    #STRING(REPLACE ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX} CG_GL_BINARY ${CG_GL_LIBRARY})
    #STRING(REPLACE "/lib/" "/bin/" CG_GL_BINARY ${CG_GL_BINARY})
#ENDIF()

#############
######### FMod
OPTION(ENABLE_FMOD "Enable Fmod support in sound library." ON)
IF(ENABLE_FMOD)
    MESSAGE("Fmod Enabled")
    FIND_PATH(FMOD_BASE_DIR NAMES api/inc/fmod.h PATHS "/Developer/FMOD Programmers API")
    IF(NOT EXISTS ${FMOD_BASE_DIR})
        MESSAGE(SEND_ERROR "The supplied Fmod Base dir: ${FMOD_BASE_DIR} does not exist")
    ENDIF(NOT EXISTS ${FMOD_BASE_DIR})
    IF(NOT EXISTS ${FMOD_BASE_DIR}/api/inc)
        MESSAGE(SEND_ERROR "The Fmod Include dir: ${FMOD_BASE_DIR}/api/inc does not exist")
    ENDIF(NOT EXISTS ${FMOD_BASE_DIR}/api/inc)
    IF(NOT EXISTS ${FMOD_BASE_DIR}/api/lib)
        MESSAGE(SEND_ERROR "The Fmod Include dir: ${FMOD_BASE_DIR}/api/lib does not exist")
    ENDIF(NOT EXISTS ${FMOD_BASE_DIR}/api/lib)

    SET(FMOD_INC_DIR ${FMOD_BASE_DIR}/api/inc)
    SET(FMOD_LIB_DIR ${FMOD_BASE_DIR}/api/lib)
    SET(FMOD_BIN_DIR ${FMOD_BASE_DIR}/api)
    IF(HAVE_64_BIT)
        SET(FMOD_LIBRARIES fmodex64)
    ELSE(HAVE_64_BIT)
        SET(FMOD_LIBRARIES fmodex)
    ENDIF(HAVE_64_BIT)

    IF(WIN32)
        SET(FMOD_LIBRARIES "${FMOD_LIBRARIES}_vc")
        SET(FMOD_BINARY "${FMOD_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${FMOD_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    ELSE()
        SET(FMOD_BINARY "${FMOD_LIB_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${FMOD_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    ENDIF()

    LIST(APPEND DEP_INCLUDE_DIRS ${FMOD_INC_DIR})
    #LIST(APPEND DEP_LIBRARY_DIRS ${FMOD_LIB_DIR})
    #LIST(APPEND DEP_LIBRARIES ${FMOD_LIBRARIES})
ENDIF(ENABLE_FMOD)

#############
######### ODE
FIND_PATH(ODE_BASE_DIR include/ode/ode.h)
IF(NOT EXISTS ${ODE_BASE_DIR})
    MESSAGE(SEND_ERROR "The supplied ODE Base dir: ${ODE_BASE_DIR} does not exists")
ENDIF(NOT EXISTS ${ODE_BASE_DIR})
IF(NOT EXISTS ${ODE_BASE_DIR}/include)
    MESSAGE(SEND_ERROR "The ODE Include dir: ${ODE_BASE_DIR}/include does not exists")
ENDIF(NOT EXISTS ${ODE_BASE_DIR}/include)
IF(NOT EXISTS ${ODE_BASE_DIR}/lib)
    MESSAGE(SEND_ERROR "The ODE Include dir: ${ODE_BASE_DIR}/lib does not exists")
ENDIF(NOT EXISTS ${ODE_BASE_DIR}/lib)

SET(ODE_INC_DIR ${ODE_BASE_DIR}/include)
SET(ODE_LIB_DIR ${ODE_BASE_DIR}/lib)
SET(ODE_BIN_DIR ${ODE_BASE_DIR}/lib)
IF(WIN32)
    SET(ODE_LIBRARIES ode_single)
ELSE(WIN32)
    SET(ODE_LIBRARIES ode)
ENDIF(WIN32)
SET(ODE_BINARY "${ODE_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${ODE_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX}")

LIST(APPEND DEP_INCLUDE_DIRS ${ODE_INC_DIR})
#LIST(APPEND DEP_LIBRARY_DIRS ${ODE_LIB_DIR})
#LIST(APPEND DEP_LIBRARIES ${ODE_LIBRARIES})

#############
######### Lua
IF(WIN32)
    FIND_PATH(LUA_BASE_DIR include/lua.hpp)
    IF(NOT EXISTS ${LUA_BASE_DIR})
        MESSAGE(SEND_ERROR "The supplied LUA Base dir: ${LUA_BASE_DIR} does not exists")
    ENDIF(NOT EXISTS ${LUA_BASE_DIR})
    IF(NOT EXISTS ${LUA_BASE_DIR}/include)
        MESSAGE(SEND_ERROR "The LUA Include dir: ${LUA_BASE_DIR}/include does not exists")
    ENDIF(NOT EXISTS ${LUA_BASE_DIR}/include)
    IF(NOT EXISTS ${LUA_BASE_DIR}/lib)
        MESSAGE(SEND_ERROR "The LUA Include dir: ${LUA_BASE_DIR}/lib does not exists")
    ENDIF(NOT EXISTS ${LUA_BASE_DIR}/lib)

    SET(LUA_INC_DIR ${LUA_BASE_DIR}/include)
    SET(LUA_LIB_DIR ${LUA_BASE_DIR}/lib)
    SET(LUA_BIN_DIR ${LUA_BASE_DIR}/lib)
    SET(LUA_LIBRARIES lua5.1)
    SET(LUA_BINARY "${LUA_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${LUA_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    LIST(APPEND DEP_INCLUDE_DIRS ${LUA_INC_DIR})
    #LIST(APPEND DEP_LIBRARY_DIRS ${LUA_LIB_DIR})
    #LIST(APPEND DEP_LIBRARIES ${LUA_LIBRARIES})
ENDIF(WIN32)

######## Apple
IF(APPLE)
    FIND_LIBRARY(OSG_APPLICATIONSERVICES_FRAMEWORK NAMES ApplicationServices)
    LIST(APPEND DEP_LIBRARIES ${OSG_APPLICATIONSERVICES_FRAMEWORK})
    #FIND_LIBRARY(OSG_CARBON_FRAMEWORK NAMES Carbon)
    #FIND_LIBRARY(OSG_COCOA_FRAMEWORK NAMES Cocoa)
ENDIF(APPLE)

######## DEBUGGER Options
OPTION(BUILD_WITH_RUNTIME_DEBUGGER "Enable the run-time debugger." ON)

######## World Builder Options
OPTION(BUILD_WITH_WORLD_BUILDER "Enable the world builder." OFF)
OPTION(BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING "Enable input logging in the world builder." OFF)

######## Player Options
OPTION(BUILD_WITH_PLAYER "Enable the player." ON)

######## Start screen Options
OPTION(BUILD_WITH_START_SCREEN "Enable the start screen." ON)

#Configure the version and config headers
SET(KABALA_ENGINE_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Source/KEVersion.h.in
              "${CMAKE_BINARY_DIR}/Source/KEVersion.h")
              
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Source/KEConfig.h.in
              "${CMAKE_BINARY_DIR}/Source/KEConfig.h")

#Includes
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Source)
INCLUDE_DIRECTORIES(${OpenSG_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${DEP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/Source") #Location of version information

#Link dirs
MESSAGE("${OpenSG_LIBRARY_DIRS}")
LINK_DIRECTORIES(${OpenSG_LIBRARY_DIRS})
LINK_DIRECTORIES(${DEP_LIBRARY_DIRS})

######## Kabala Engine Executable

#Make the Source groups for these files
RECURSIVE_DIRECTORY_FIND(${CMAKE_SOURCE_DIR}/Source "/.svn" ${CMAKE_SOURCE_DIR}/Source)

#Get a listing of the Header, source, and inline files

#Version information file
LIST(APPEND HEADERS "${CMAKE_BINARY_DIR}/Source/KEVersion.h")

#Configuration file
LIST(APPEND HEADERS "${CMAKE_BINARY_DIR}/Source/KEConfig.h")

##### Start screen code
IF(BUILD_WITH_START_SCREEN)
    FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/StartScreen/[^~]*.h)
    FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/StartScreen/[^~]*.cpp)
    FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/StartScreen/[^~]*.inl)
    
    LIST(APPEND HEADERS ${TEMP_HEADERS})
    LIST(APPEND INLINES ${TEMP_INLINES})
    LIST(APPEND SOURCES ${TEMP_SOURCES})
ENDIF()

##### Player code
IF(BUILD_WITH_PLAYER)
        IF(BUILD_WITH_RUNTIME_DEBUGGER)
            FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/Player/[^~]*.h)
            FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/Player/[^~]*.cpp)
            FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/Player/[^~]*.inl)
            
            LIST(APPEND HEADERS ${TEMP_HEADERS})
            LIST(APPEND INLINES ${TEMP_INLINES})
            LIST(APPEND SOURCES ${TEMP_SOURCES})
        ELSE()
            FILE(GLOB TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/Player/[^~]*.h)
            FILE(GLOB TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/Player/[^~]*.cpp)
            FILE(GLOB TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/Player/[^~]*.inl)
            
            LIST(APPEND HEADERS ${TEMP_HEADERS})
            LIST(APPEND INLINES ${TEMP_INLINES})
            LIST(APPEND SOURCES ${TEMP_SOURCES})
        ENDIF()
ENDIF()

##### Library
FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/Library/[^~]*.h)
FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/Library/[^~]*.cpp)
FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/Library/[^~]*.inl)

LIST(APPEND HEADERS ${TEMP_HEADERS})
LIST(APPEND INLINES ${TEMP_INLINES})
LIST(APPEND SOURCES ${TEMP_SOURCES})

##### World builder code
IF(BUILD_WITH_WORLD_BUILDER)
    FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/Builder/[^~]*.h)
    FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/Builder/[^~]*.cpp)
    FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/Builder/[^~]*.inl)
    
    LIST(APPEND HEADERS ${TEMP_HEADERS})
    LIST(APPEND INLINES ${TEMP_INLINES})
    LIST(APPEND SOURCES ${TEMP_SOURCES})
    
    IF(BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING)
        FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/InputLogging/[^~]*.h)
        FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/InputLogging/[^~]*.cpp)
        FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/InputLogging/[^~]*.inl)
        
        LIST(APPEND HEADERS ${TEMP_HEADERS})
        LIST(APPEND INLINES ${TEMP_INLINES})
        LIST(APPEND SOURCES ${TEMP_SOURCES})
    ENDIF()
ENDIF()

#### Base
FILE(GLOB TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/[^~]*.h)
FILE(GLOB TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/[^~]*.cpp)
FILE(GLOB TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/[^~]*.inl)

LIST(APPEND HEADERS ${TEMP_HEADERS})
LIST(APPEND INLINES ${TEMP_INLINES})
LIST(APPEND SOURCES ${TEMP_SOURCES})

#### Application
FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/Application/[^~]*.h)
FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/Application/[^~]*.cpp)
FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/Application/[^~]*.inl)

LIST(APPEND HEADERS ${TEMP_HEADERS})
LIST(APPEND INLINES ${TEMP_INLINES})
LIST(APPEND SOURCES ${TEMP_SOURCES})

#### Projects
FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/Project/[^~]*.h)
FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/Project/[^~]*.cpp)
FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/Project/[^~]*.inl)

LIST(APPEND HEADERS ${TEMP_HEADERS})
LIST(APPEND INLINES ${TEMP_INLINES})
LIST(APPEND SOURCES ${TEMP_SOURCES})

#### Lua
FILE(GLOB_RECURSE TEMP_HEADERS ${CMAKE_SOURCE_DIR}/Source/LuaBindings/[^~]*.h)
FILE(GLOB_RECURSE TEMP_SOURCES ${CMAKE_SOURCE_DIR}/Source/LuaBindings/[^~]*.cpp)
FILE(GLOB_RECURSE TEMP_INLINES ${CMAKE_SOURCE_DIR}/Source/LuaBindings/[^~]*.inl)

LIST(APPEND HEADERS ${TEMP_HEADERS})
LIST(APPEND INLINES ${TEMP_INLINES})
LIST(APPEND SOURCES ${TEMP_SOURCES})


SET(EXECUTABLE_NAME "KabalaEngine")

# For Apple set the icns file containing icons
IF(APPLE)
    # set how it shows up in the Info.plist file
    SET(BUNDLE_ICON_NAME "kabalaenginelogo-noname.icns") 
    SET(BUNDLE_ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/OS X/${BUNDLE_ICON_NAME}") 

    # set where in the bundle to put the icns file
    SET_SOURCE_FILES_PROPERTIES(${BUNDLE_ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    # include the icns file in the target
    LIST(APPEND SOURCES ${BUNDLE_ICON_PATH})
ENDIF(APPLE)

ADD_EXECUTABLE(${EXECUTABLE_NAME} WIN32 MACOSX_BUNDLE ${HEADERS} ${SOURCES} ${INLINES} ${HEADERS_1} ${SOURCES_1} ${INLINES_1})

SET_TARGET_PROPERTIES(${EXECUTABLE_NAME} PROPERTIES
    #DEFINE_SYMBOL ${PROJ_DEFINE}
    VERSION ${KABALA_ENGINE_VERSION}
    SOVERSION ${KABALA_ENGINE_VERSION}
    DEBUG_POSTFIX "D"
    DEBUGOPT_POSTFIX "DO"
    RELWITHDEBINFO_POSTFIX "RD"
    RELEASENOOPT_POSTFIX "RN"
    #INSTALL_RPATH ""
    #SKIP_BUILD_RPATH OFF
    #BUILD_WITH_INSTALL_RPATH OFF
    #INSTALL_NAME_DIR ""
    )

IF(APPLE)
    SET_TARGET_PROPERTIES(${EXECUTABLE_NAME}
                               PROPERTIES
                                   MACOSX_BUNDLE TRUE
                                   #MACOSX_BUNDLE_GUI_IDENTIFIER ${CPACK_BUNDLE_IDENTIFIER}
                                   MACOSX_BUNDLE_ICON_FILE "${BUNDLE_ICON_NAME}"
                                   #MACOSX_BUNDLE_BUNDLE_NAME ${CPACK_BUNDLE_NAME}
                                   MACOSX_BUNDLE_BUNDLE_VERSION ${KABALA_ENGINE_VERSION}
                                   MACOSX_BUNDLE_LONG_VERSION_STRING ${KABALA_ENGINE_VERSION}
                                   MACOSX_BUNDLE_SHORT_VERSION_STRING ${KABALA_ENGINE_VERSION})
ENDIF(APPLE)

#Attach all of the libraries
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${OpenSG_LIBRARIES} ${DEP_LIBRARIES})

################### INSTALL ####################

#Install the libraries
INSTALL(TARGETS ${EXECUTABLE_NAME}
    EXPORT  KabalaEngineExport
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    BUNDLE  DESTINATION .
    COMPONENT Application)

SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${EXECUTABLE_NAME}")  # paths to executables

SET(PLUGIN_DIR "bin")
SET(CONFIG_DIR "bin")
SET(EXTERNAL_LIBS_DIR "bin")
SET(DATA_DIR "bin")

IF(APPLE)
  SET(PLUGIN_DIR ${EXECUTABLE_NAME}.app/Contents/MacOS/Plugins)
  SET(EXTERNAL_LIBS_DIR ${EXECUTABLE_NAME}.app/Contents)
  SET(CONFIG_DIR ${EXECUTABLE_NAME}.app/Contents/Resources)
  SET(DATA_DIR ${EXECUTABLE_NAME}.app/Contents/Resources)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/${EXECUTABLE_NAME}.app")
  SET(BUNDLE_APPS "\${CMAKE_INSTALL_PREFIX}/${EXECUTABLE_NAME}.app")
ENDIF(APPLE)
IF(WIN32)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${EXECUTABLE_NAME}.exe")
ENDIF(WIN32)

#SET(BU_COPY_FULL_FRAMEWORK_CONTENTS ON)

SET(BUNDLE_DIRS
         ${FMOD_LIB_DIR}
         ${Boost_LIBRARY_DIRS}
         ${OpenSG_LIBRARY_DIRS}
         ${CUDA_LIBRARY_DIRS}
         ${COLLADA_LIBRARY_DIRS}
         ${CG_LIBRARY}
         )   # directories to search for prerequisites

SET(BUNDLE_LIBS ""
         )   # Libraries to bundle

MESSAGE("${DIRS}")
INSTALL(CODE "include(BundleUtilities)


              ####### Function for resolving dependent libraries when creating an OS X Bundle
              FUNCTION(gp_resolve_item_override  CONTEXT ITEM EXEPATH DIRS RESOLVED_ITEM_VAR RESOLVED_VAR)
                  IF(NOT \${RESOLVED_VAR})
                      SET(ITEM_NAME \${ITEM})
                      GET_FILENAME_COMPONENT(ITEM_NAME \"\${ITEM_NAME}\" NAME)

                      SET(ITEM_PATH \"ITEM_PATH-NOTFOUND\")
                      FIND_FILE(ITEM_PATH \"\${ITEM_NAME}\" PATHS \${DIRS} NO_DEFAULT_PATH)
                      IF(ITEM_PATH)
                          SET(\${RESOLVED_VAR} 1 PARENT_SCOPE)
                          SET(\${RESOLVED_ITEM_VAR} \"\${ITEM_PATH}\" PARENT_SCOPE)
                      ENDIF()
                  ENDIF()
              ENDFUNCTION()

              fixup_bundle(\"${BUNDLE_APPS}\"   \"${BUNDLE_LIBS}\"   \"${BUNDLE_DIRS}\")"
        COMPONENT Runtime)

######## KabalaEngine Icons and Data

IF(APPLE)
    SET(INSTALL_BASE_DATA_DIR "${EXECUTABLE_NAME}.app/Contents/Resources/share/KabalaEngine/Data")
ELSE()
    SET(INSTALL_BASE_DATA_DIR "share/KabalaEngine/Data")
ENDIF()

OPTION(BUILD_ICONS "Build the Icon set for the Kabala Engine" ON)
OPTION(INCLUDE_APP_DATA "Include the data used by the Kabala Engine" ON)

IF(BUILD_ICONS)
    FIND_PROGRAM(INKSCAPE_EXECUTABLE inkscape)
    FIND_PROGRAM(CONVERT_EXECUTABLE convert)

    FILE(GLOB_RECURSE ICON_SVG_SOURCE_FILES ${CMAKE_SOURCE_DIR}/Data/Images/Source/Icons/*.svg)

    SET(BUILD_ICON_DIMENSION 64 CACHE STRING "Advanced: The vertical and horizontal dimenstions to use to create the icons.")
    SET(DISABLED_ICON_CONVERT_ARG_1 "-modulate" CACHE STRING "Advanced: The 1 argument to send to the convert command to generate the Disabled Icons.")
    SET(DISABLED_ICON_CONVERT_ARG_2 "100,0" CACHE STRING "Advanced: The 2 argument to send to the convert command to generate the Disabled Icons.")

    FOREACH(ICON_SVG_SOURCE_FILE ${ICON_SVG_SOURCE_FILES})
        FILE(RELATIVE_PATH ICON_SVG_NAME  ${CMAKE_SOURCE_DIR}/Data/Images/Source/Icons ${ICON_SVG_SOURCE_FILE})

        #Extract a short name for the icon svg file
        STRING(REGEX MATCH "(.*)[.]svg" ICON_SVG_NAME ${ICON_SVG_NAME})
        SET(ICON_SVG_NAME ${CMAKE_MATCH_1})

        SET(BASIC_IMG_PATH ${CMAKE_BINARY_DIR}/Data/Images/Icons/${ICON_SVG_NAME}/${ICON_SVG_NAME})

        FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Data/Images/Icons/${ICON_SVG_NAME})

        #Command for making the Normal Icons
        ADD_CUSTOM_COMMAND(OUTPUT ${BASIC_IMG_PATH}Normal.png
            COMMAND ${INKSCAPE_EXECUTABLE} ${ICON_SVG_SOURCE_FILE} -w ${BUILD_ICON_DIMENSION} -h ${BUILD_ICON_DIMENSION} --export-png=${BASIC_IMG_PATH}Normal.png
            DEPENDS ${ICON_SVG_SOURCE_FILE})
        #Add this icon as a target
        LIST(APPEND ICON_PNG_TARGETS ${BASIC_IMG_PATH}Normal.png)

        IF(CONVERT_EXECUTABLE)
            #Command for making he disabled Icons
            ADD_CUSTOM_COMMAND(OUTPUT ${BASIC_IMG_PATH}Disabled.png
                COMMAND ${CONVERT_EXECUTABLE}  ${BASIC_IMG_PATH}Normal.png ${DISABLED_ICON_CONVERT_ARG_1} ${DISABLED_ICON_CONVERT_ARG_2} ${BASIC_IMG_PATH}Disabled.png
                DEPENDS ${BASIC_IMG_PATH}Normal.png)
            #Add this icon as a target
            LIST(APPEND ICON_PNG_TARGETS ${BASIC_IMG_PATH}Disabled.png)
        ENDIF(CONVERT_EXECUTABLE)

    ENDFOREACH(ICON_SVG_SOURCE_FILE ${ICON_SVG_SOURCE_FILES})

    ADD_CUSTOM_TARGET(Icons ALL COMMENT "Building the Icons"
        DEPENDS ${ICON_PNG_TARGETS})

    IF(INCLUDE_APP_DATA)
        #Installing the Icon Set
        INSTALL(DIRECTORY ${CMAKE_BINARY_DIR}/Data/Images/Icons
            DESTINATION "${INSTALL_BASE_DATA_DIR}/Images"
            COMPONENT Data)
    ENDIF(INCLUDE_APP_DATA)
ENDIF(BUILD_ICONS)

IF(INCLUDE_APP_DATA)
    #Installing the Information 
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/README.txt
        ${CMAKE_SOURCE_DIR}/ABOUT.txt
        DESTINATION "${INSTALL_BASE_DATA_DIR}/Info"
        COMPONENT Application
        )
        
    #Installing the Model Set
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/Data/UI
        DESTINATION "${INSTALL_BASE_DATA_DIR}"
        COMPONENT Data)
        
    #Installing the UI Data
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/Data/Models
        DESTINATION "${INSTALL_BASE_DATA_DIR}"
        COMPONENT Data)
        
    #Installing the Documentation
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/Documentation
        DESTINATION "${INSTALL_BASE_DATA_DIR}"
        COMPONENT Documentation)
        
    #Installing the Scripts
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/Data/Scripts
        DESTINATION "${INSTALL_BASE_DATA_DIR}"
        COMPONENT Scirpts)
ENDIF(INCLUDE_APP_DATA)


######## Packaging
OPTION(BUILD_PACKAGING "Configure the os-specific package building." OFF)

#Windows
IF(WIN32 AND BUILD_PACKAGING)
    MESSAGE("Creating Windows NSIS packaging configuration")
    
    #Locations of binaries
    #OpenSG
    STRING(REPLACE "/" "\\" OpenSG_BINARIES_DIR ${OpenSG_BINARIES_DIR})
    
    #Boost
    STRING(REPLACE "/" "\\" Boost_SYSTEM_LIBRARY_BIN ${Boost_SYSTEM_LIBRARY_BIN})
    STRING(REPLACE "/" "\\" Boost_FILESYSTEM_LIBRARY_BIN ${Boost_FILESYSTEM_LIBRARY_BIN})
    STRING(REPLACE "/" "\\" Boost_PROGRAM_OPTIONS_LIBRARY_BIN ${Boost_PROGRAM_OPTIONS_LIBRARY_BIN})
    STRING(REPLACE "/" "\\" Boost_DATE_TIME_LIBRARY_BIN ${Boost_DATE_TIME_LIBRARY_BIN})
    
    #Lua
    STRING(REPLACE "/" "\\" LUA_BINARY ${LUA_BINARY})
    
    #Fmod
    STRING(REPLACE "/" "\\" FMOD_BINARY ${FMOD_BINARY})
    
    #ODE
    STRING(REPLACE "/" "\\" ODE_BINARY ${ODE_BINARY})
    
    #Collada
    STRING(REPLACE "/" "\\" COLLADA_BINARY ${COLLADA_BINARY})
    
    #CgFX
    STRING(REPLACE "/" "\\" CG_BINARY ${CG_BINARY})
    STRING(REPLACE "/" "\\" CG_GL_BINARY ${CG_GL_BINARY})
    
    SET(NSIS_PROJECT_NAME "${EXECUTABLE_NAME}")
    
    #Configure the NSIS script
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Packaging/Windows/KabalaEngineInstallScript.nsi.in
                  "${CMAKE_BINARY_DIR}/Packaging/Windows/KabalaEngineInstallScript.nsi"
                  IMMEDIATE @ONLY)
                  
    #Find the NSIS exe
    FIND_PROGRAM(NSIS_EXE NSIS/makensis.exe)
    
    #Create a custom command for running nsis
    ADD_CUSTOM_COMMAND(OUTPUT "${CMAKE_BINARY_DIR}/Packaging/Windows/InstallKabalaEngine.exe"
                     COMMAND "${NSIS_EXE}" ARGS "KabalaEngineInstallScript.nsi"
                     MAIN_DEPENDENCY "${CMAKE_BINARY_DIR}/Packaging/Windows/KabalaEngineInstallScript.nsi"
                     DEPENDS ${EXECUTABLE_NAME}
                     #[IMPLICIT_DEPENDS <lang1> depend1 ...]
                     WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Packaging/Windows"
                     COMMENT "Windows NSIS Packaging")
                   
    #Create a new target for the packager  
    ADD_CUSTOM_TARGET("NSIS Packaging" 
                      DEPENDS "${CMAKE_BINARY_DIR}/Packaging/Windows/InstallKabalaEngine.exe"
                      SOURCES "${CMAKE_SOURCE_DIR}/Packaging/Windows/KabalaEngineInstallScript.nsi.in")
 ENDIF()
 
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Virtual Reality application authoring tool.")
SET(CPACK_PACKAGE_VENDOR "David Kabala")

SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/WELCOME.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")


SET(CPACK_PACKAGE_VERSION_MAJOR ${KABALA_ENGINE_MAJOR_VERSION})
SET(CPACK_PACKAGE_VERSION_MINOR ${KABALA_ENGINE_MINOR_VERSION})
SET(CPACK_PACKAGE_VERSION_PATCH ${KABALA_ENGINE_PATCH_VERSION})
SET(CPACK_PACKAGE_VERSION ${KABALA_ENGINE_VERSION})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}")
SET(CPACK_PACKAGE_FILE_NAME "KabalaEngine-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")

#OS X Bundles
IF(APPLE)
    #SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/Packaging/KabalaEngine-Icon-48x48.bmp")
    #SET(CPACK_BUNDLE_PLIST "${CMAKE_SOURCE_DIR}/Packaging/OS X/Info.plist")
    #SET(CPACK_BUNDLE_NAME "KabalaEngine")
    #SET(CPACK_BUNDLE_ICON "${CPACK_PACKAGE_ICON}")
    #SET(CPACK_BUNDLE_STARTUP_COMMAND "${CMAKE_SOURCE_DIR}/Packaging/OS X/KabalaEngine.sh")
ENDIF(APPLE)

#Linux
IF(UNIX)
    SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/Packaging/KabalaEngine-Icon-48x48.bmp")
ENDIF(UNIX)

#Windows
IF(WIN32)
    SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/Packaging/KabalaEngine-Icon-48x48.bmp")
ENDIF(WIN32)


IF(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
    SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
    SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
    SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
    SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
    SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
    SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
    #SET(CPACK_STRIP_FILES "bin/KabalaEngine")
    #SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "KabalaEngine" "KabalaEngine")

INCLUDE(CPack)
