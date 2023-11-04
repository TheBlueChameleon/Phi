cmake_minimum_required(VERSION 3.5)

# ============================================================================ #
# lanugage definition

project(Phi
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set this to NO if your target does not support AVX CPU instructions
set (ENABLE_AVX YES)

# ============================================================================ #
# SDL 2 parts

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# install these with
#  sudo apt install libsdl2-dev
#  sudo apt install libsdl2-image-dev
#  sudo apt install libsdl2-ttf-dev

include_directories(${SDL2_INCLUDE_DIRS})

# ============================================================================ #
# unit test framework

enable_testing()
add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "")
endif ()

if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

# ============================================================================ #
# library definition

add_library(Phi-base STATIC
    src/base/base.h

    src/base/errors.h src/base/errors.cpp
)

target_include_directories(Phi-base PUBLIC
    src/
)

# ............................................................................ #

add_library(Phi-coords STATIC
    src/coords/coords.h

    src/coords/coordinates.h    src/coords/coordinates.txx  src/coords/coordinates.cpp

    src/coords/grid.h
    src/coords/basegrid.h       src/coords/basegrid.txx     src/coords/basegrid.cpp
)

target_include_directories(Phi-coords PUBLIC
    src/
)

target_link_libraries(Phi-coords
    Phi-base
)

# ............................................................................ #

add_library(Phi-physics STATIC
    src/physics/physics.h

    src/physics/gridfactory.h src/physics/gridfactory.cpp
    src/physics/potential/potentialgrid.h src/physics/potential/potentialgrid.cpp
)

target_include_directories(Phi-physics PUBLIC
    src/
)

set_target_properties(Phi-physics PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PUBLIC_HEADER src/physics/physics.h
)

if (NOT ENABLE_AVX)
    target_compile_definitions(Phi-physics PUBLIC NO_AVX_ACCELERATION)
endif()

# ............................................................................ #

add_library(Phi-uibase STATIC
    src/ui-base/uibase.h
    src/ui-base/base.h src/ui-base/base.cpp
)

target_include_directories(Phi-uibase PUBLIC
    src/
)

target_link_libraries(Phi-uibase
    Phi-base
)

# ============================================================================ #
# executable module definition

add_executable(Phi-game
    src/main.cpp
)

target_include_directories(Phi-game PUBLIC
    src/
)

target_link_libraries(Phi-game
    Phi-base
    Phi-coords
    Phi-physics
    Phi-uibase
    ${SDL2_LIBRARIES}
)

# ............................................................................ #
# test module

add_executable(Phi-unittest
    unittest/main.cpp
    unittest/physics/gridfactory.cpp
    unittest/physics/potential/potentialgrid.cpp
    ${GTestFiles}
)

add_test(NAME Phi-unittest COMMAND "main")

target_include_directories(Phi-unittest
    # paths relative to build directory
    PRIVATE src/
    PRIVATE unittest/
)
target_link_libraries(Phi-unittest
    PRIVATE Threads::Threads
    PRIVATE Phi-base
    PRIVATE Phi-coords
    PRIVATE Phi-physics
)

# ============================================================================ #
# information feedback

if (ENABLE_AVX)
    set (CMAKE_CXX_FLAGS "-mavx512f")
    message(STATUS "AVX EXTENSION ENABLED")
else()
    message(STATUS "AVX EXTENSION DISABLED")
endif()

message(VERBOSE CMAKE_INSTALL_LIBDIR="${CMAKE_INSTALL_LIBDIR}")
message(VERBOSE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
