#  :copyright: (c) 2017 Alex Huszagh.
#  :license: MIT, see LICENSE.md for more details.

cmake_minimum_required(VERSION 2.8)
project(fsutil CXX)

# FLAGS
# -----

set(CMAKE_CXX_STANDARD 14)

# OPTIONS
# -------

option(BUILD_STATIC "Build static library" ON)

if(BUILD_STATIC)
    if(UNIX)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    elseif(${MINGW} OR ${MSYS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc")
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

# EXAMPLES
# --------


# TESTS
# -----
