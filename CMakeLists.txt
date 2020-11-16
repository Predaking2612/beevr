cmake_minimum_required (VERSION 3.14)

project (beevr
		VERSION 0.0.1
		DESCRIPTION "Interactive repl for C99"
		LANGUAGES C)
set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED YES)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message ("Warning: in-source builds are prohibited")
	message ("Create a build directory and run 'cmake ..' from there")
	message (FATAL_ERROR "Quitting the configuration")
endif()


# Baseline settings
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message (STATUS "Setting build type to 'Debug' as none was specified.")
	set (CMAKE_BUILD_TYPE Debug
			CACHE STRING "Choose the type of build" FORCE)

	set_property (CACHE CMAKE_BUILD_TYPE
			PROPERTY STRINGS "Debug"
			"Release"
			"RelWithDebInfo")
endif()

# Build type.
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "CMAKE_BUILD_TYPE not specified, default is 'Debug'")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
else()
  message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
endif()

# Project paths
include (cmake/beever_path.cmake)
include (cmake/compile.cmake)

# load with ccache
find_program(CCACHE ccache)
if (CCACHE)
	message("Enabling ccache for the project build")
	set (CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

#export language-server settings
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set Binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package (PkgConfig)
find_package (Threads REQUIRED)

# Coverage settings : Specific to Linux
option (CODE_COVERAGE "Enable code coverage for the project" ON)
if (CODE_COVERAGE)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftest-coverage -fprofile-arcs")
	set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -ftest-coverage -fprofile-arcs")
	set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -ftest-coverage -fprofile-arcs")
endif()

set (CMAKE_SHARED_LINKER_FLAGS -Wl,--as-needed)
add_subdirectory (src)

