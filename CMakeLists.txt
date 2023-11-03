cmake_minimum_required(VERSION 3.5)

# ============================================================================ #
# lanugage definition

project(Phi
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS "-mavx512f")

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

add_library(PhiPhysics-lib STATIC
    src/physics/physics.h

    src/physics/gridfactory.h src/physics/gridfactory.cpp

    src/physics/base/errors.h src/physics/base/errors.cpp
    src/physics/base/coordinates.h src/physics/base/coordinates.txx src/physics/base/coordinates.cpp
    src/physics/base/grid.h
    src/physics/base/basegrid.h src/physics/base/basegrid.txx src/physics/base/basegrid.cpp

    src/physics/potential/potentialgrid.h src/physics/potential/potentialgrid.cpp
)

target_include_directories(PhiPhysics-lib PUBLIC
    src/physics/
)

set_target_properties(PhiPhysics-lib PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PUBLIC_HEADER src/physics/physics.h
)

# uncomment this if your target does not support AVX CPU instructions
# target_compile_definitions(PhiPhysics-lib PUBLIC NO_AVX_ACCELERATION)

# ............................................................................ #
# showcase code

add_executable(PhiPhysics-showcase
    src/main.cpp
)

target_include_directories(PhiPhysics-showcase PUBLIC
    src/physics/
)

target_link_libraries(PhiPhysics-showcase
    PhiPhysics-lib
)

# ............................................................................ #
# test code

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
    PRIVATE PhiPhysics-lib
)

# ============================================================================ #
# install

message(CMAKE_INSTALL_LIBDIR="${CMAKE_INSTALL_LIBDIR}")
message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
