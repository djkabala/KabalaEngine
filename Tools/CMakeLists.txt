
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
PROJECT(KabalaEngineFCDCompile)

#Get a listing of the Header, source, and inline files
FILE(GLOB HEADERS [^~]*.h)
FILE(GLOB SOURCES [^~]*.cpp)

ADD_DEFINITIONS(-DFCD_TERM)

IF(UNIX)
    IF(APPLE)
        SET(EXE_FOLDER "OS X")
    ELSE(APPLE)
        SET(EXE_FOLDER "Linux")
    ENDIF(APPLE)
ENDIF(UNIX)

IF(WIN32)
    SET(EXE_FOLDER "Windows")
ENDIF(WIN32)

#Configure shared library creation
ADD_EXECUTABLE(fcdCompile ${HEADERS} ${SOURCES})

SET_PROPERTY(TARGET fcdCompile
             PROPERTY RUNTIME_OUTPUT_DIRECTORY ${EXE_FOLDER})

