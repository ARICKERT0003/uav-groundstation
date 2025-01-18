cmake_minimum_required(VERSION 3.12)
project( qt-practice
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "QT/QLM Practice"
)

#############################
# Options
#############################
#option(QTPRAC_STATIC_BUILD              "Build static library" OFF)
#option(QTPRAC_BUILD_EXTERN              "Build extern" OFF)
#option(QTPRAC_BUILD_SAMPLES             "Build samples" OFF)
#option(QTPRAC_BUILD_SAMPLE_BRUTE_FORCE  "Build sample" ON)
#option(QTPRAC_BUILD_SAMPLE_BFS          "Build sample" ON)
#option(QTPRAC_BUILD_SAMPLE_DFS          "Build sample" ON)
#option(QTPRAC_BUILD_SAMPLE_GUI          "Build sample" ON)
#option(QTPRAC_BUILD_SAMPLE_GENETIC      "Build sample" ON)

## Static or Dynamic Link
#if(QTPRAC_STATIC_BUILD)
#  set(LINK_TYPE STATIC)
#else()
#  set(LINK_TYPE SHARED)
#endif()

#############################
# Set General Variables 
#############################

set( APP_NAME qtapp )

# Library Variables
#set(LIBRARY_NAME qtprac)
#set(SH_VER 0)

## Library Output Dir
#if(NOT QTPRAC_LIBRARY_OUTPUT_DIR)
#  set( QTPRAC_LIBRARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
#endif()
#
## Library Install Dir
#if(NOT QTPRAC_LIBRARY_INSTALL_DIR)
#  set( QTPRAC_LIBRARY_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install/lib)
#endif()
#
## Header Install Dir
#if(NOT QTPRAC_HEADER_INSTALL_DIR)
#  set( QTPRAC_HEADER_INSTALL_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/install/inc)
#endif()
#
## Extern Library Output
#if(NOT QTPRAC_EXTERN_LIBRARY_OUTPUT_DIR)
#  set( QTPRAC_EXTERN_LIBRARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/lib)
#endif()
#
## Extern Library Install
#if(NOT QTPRAC_EXTERN_LIBRARY_INSTALL_DIR)
#  set( QTPRAC_EXTERN_LIBRARY_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/lib)
#endif()
#
## Extern Header Install
#if(NOT QTPRAC_EXTERN_HEADER_INSTALL_DIR)
#  set( QTPRAC_EXTERN_HEADER_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/inc)
#endif()

#############################
# Set Compiler Flags Variable
#############################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message( STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}" )
set( QT6_DIR C:/QT/6.8.0/msvc2022_64/lib/cmake/Qt6 )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/app )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/app )
#set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

set( LOGIC_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/logic )
set( UI_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/ui )

# Base Compiler Flags
set(QTPRAC_DEBUG_FLAGS 
  -Wall 
  -Wextra
  -Werror
  -W
  -DDEBUG
  -g
)

set(QTPRAC_RELEASE_FLAGS
  -pedantic
  -03
)

#############################
# Set Files and Directories
#############################
# Source Files
set(SRC_FILES
  ${LOGIC_DIR}/main.cpp
  ${LOGIC_DIR}/src/transceiver.cpp
  ${LOGIC_DIR}/src/receiver.cpp
  ${LOGIC_DIR}/src/switch_timed.cpp
  ${LOGIC_DIR}/src/ground_station.cpp
  ${UI_DIR}/src/main_window.cpp
  ${UI_DIR}/src/tab_1.cpp
  ${UI_DIR}/src/tab_2.cpp
  ${UI_DIR}/src/tab_3.cpp
  ${UI_DIR}/src/serial_config_box.cpp
  ${UI_DIR}/src/sql_config_box.cpp
)

# Header Files
set(HEADER_FILES
  ${LOGIC_DIR}/inc/transceiver.h
  ${LOGIC_DIR}/inc/receiver.h
  ${LOGIC_DIR}/inc/switch_timed.h
  ${LOGIC_DIR}/inc/ground_station.h
  ${UI_DIR}/inc/main_window.h
  ${UI_DIR}/inc/tab_1.h
  ${UI_DIR}/inc/tab_2.h
  ${UI_DIR}/inc/tab_3.h
  ${UI_DIR}/inc/serial_config_box.h
  ${UI_DIR}/inc/sql_config_box.h
)

# Include Directory
set(QTPRAC_INC_DIRS
  ${LOGIC_DIR}/inc
  ${UI_DIR}/inc
)

#############################
# Set External Files and Directories
#############################
# QT
find_package( Qt6 COMPONENTS Core Gui SerialPort Sql Widgets REQUIRED )
qt_standard_project_setup( REQUIRES 6.5 )

#list( APPEND QTPRAC_INC_DIRS
#  ${Boost_INCLUDE_DIRS}
#)

set(QTPRAC_LIBS 
  Qt6::Core
  Qt6::Gui
  Qt6::SerialPort
  Qt6::Sql
  Qt6::Widgets
)

#############################
# Recurse into Directories
#############################
#if(QTPRAC_BUILD_EXTERN)
#  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern)
#  list(APPEND PROJECT_INC_DIRS
#)
#endif()
#
## Set all Directories which contain libraries
#link_directories(${QTPRAC_LIB_DIRS})

#############################
# Make Target and Set Props
#############################

qt_add_executable( ${APP_NAME} ${SRC_FILES} ${HEADER_FILES} )

#qt_add_qml_module( ${APP_NAME} 
#  URI hello
#  QML_FILES src/qml/main.qml
#)

# Make Library Binary
#add_library( ${LIBRARY_NAME} ${LINK_TYPE} ${SRC_FILES} )
#
## Set Library Properties
#set_target_properties( ${LIBRARY_NAME} PROPERTIES
#  VERSION ${PROJECT_VERSION}
#  PUBLIC_HEADER "${HEADER_FILES}"
#  ARCHIVE_OUTPUT_DIRECTORY "${QTPRAC_LIBRARY_OUTPUT_DIR}"
#  LIBRARY_OUTPUT_DIRECTORY "${QTPRAC_LIBRARY_OUTPUT_DIR}"
#)
#
## Target Compiler Flags
#target_compile_options( ${LIBRARY_NAME}
#  PRIVATE
#  "$<$<CONFIG:Debug>:${QTPRAC_DEBUG_FLAGS}>"
#  "$<$<CONFIG:Release>:${QTPRAC_RELEASE_FLAGS}>"
#)

#############################
# Find and Link Libraries
#############################
# Target Include Directories
target_include_directories( ${APP_NAME}
  PUBLIC
  ${QTPRAC_INC_DIRS}
)

# Link External Libraries
target_link_libraries( ${APP_NAME}
  PUBLIC
  ${QTPRAC_LIBS}
)

#############################
# Set Install Options
#############################

#############################
# Samples
#############################
#if(QTPRAC_BUILD_SAMPLES)
#  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)
#endif()
