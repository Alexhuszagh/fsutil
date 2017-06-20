#  :copyright: (c) 2017 Alex Huszagh.
#  :license: MIT, see LICENSE.md for more details.

cmake_minimum_required(VERSION 2.8)
project(fsutil CXX)

# FLAGS
# -----

set(CMAKE_CXX_STANDARD 14)

# OPTIONS
# -------

option(BUILD_EXAMPLES "Build example files" OFF)
option(BUILD_STATIC "Build static library" ON)
option(BUILD_TESTS "Build unittests (requires GTest)" OFF)

if(BUILD_STATIC)
    if(UNIX)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    elseif(MINGW OR MSYS)
        message(FATAL_ERROR "MinGW is currently not supported.")
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc")
    elseif(MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /O0 /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Ox /Zi /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
        set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT /Zi /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
    endif()
endif()

# LIBRARY
# -------

file(GLOB FSUTIL_SOURCES src/*.cpp)
set(FSUTIL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(FSUTIL_INCLUDE_DIRS ${FSUTIL_INCLUDE_DIR})
include_directories(${FSUTIL_INCLUDE_DIRS})

if(BUILD_STATIC)
    add_library(fsutil STATIC ${FSUTIL_SOURCES})
else()
    add_library(fsutil SHARED ${FSUTIL_SOURCES})
endif()

set(FSUTIL_LIBRARIES fsutil)
if (MSVC)
else()
    list(APPEND FSUTIL_LIBRARIES -lstdc++fs)
endif()

# EXAMPLES
# --------

file(GLOB FSUTIL_EXAMPLES example/*.cpp)

if(BUILD_EXAMPLES)
    foreach(source ${FSUTIL_EXAMPLES})
        get_filename_component(example ${source} NAME_WE)
        set(target "fsutil_${example}")
        add_executable(${target} "${source}")
        set_target_properties(${target} PROPERTIES OUTPUT_NAME ${example})
        target_link_libraries(${target} ${FSUTIL_LIBRARIES})
    endforeach(source)
endif()

# TESTS
# -----

file(GLOB FSUTIL_TESTS test/*.cpp)

if(BUILD_TESTS)
    # if we're in a dependent project, a gtest target may already exist
    if(NOT TARGET gtest)
        add_subdirectory(googletest)
    endif()

    add_executable(fsutil_tests ${FSUTIL_TESTS})
    target_link_libraries(fsutil_tests
        gtest
        gtest_main
        ${FSUTIL_LIBRARIES}
    )

     add_custom_target(check_fsutil
        COMMAND $<TARGET_FILE:fsutil_tests>
        DEPENDS fsutil_tests
    )
endif()