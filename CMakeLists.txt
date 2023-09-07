cmake_minimum_required (VERSION 3.8.0 FATAL_ERROR)

project (HasiLWGDF_Core LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (SUB_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/subdirs")

include (GNUInstallDirs)

find_package(Vulkan REQUIRED)

if (NOT DEFINED BUILD_SHARED_LIBS)
    set (BUILD_SHARED_LIBS OFF)
endif ()

set (SOURCES
    "src/cpp/graphics/DX9Renderer.cpp"
    "src/cpp/graphics/OGLESRenderer.cpp"
    "src/cpp/graphics/OGLRenderer.cpp"
    "src/cpp/graphics/Renderer.cpp"

    "src/cpp/input/Joystick.cpp"
    "src/cpp/input/Keyboard.cpp"
    "src/cpp/input/Mouse.cpp"
    "src/cpp/input/Touch.cpp"

    "src/cpp/math/Timer.cpp"
    
    "src/cpp/Audio.cpp"
    "src/cpp/Discord.cpp"
    "src/cpp/Game.cpp"
    "src/cpp/PhysicsWorld2D.cpp"
    "src/cpp/PhysicsWorld3D.cpp"
)

if (WIN32)
    set (SOURCES ${SOURCES} "src/cpp/DiscordWin32.cpp")
elseif (UNIX)
    set (SOURCES ${SOURCES} "src/cpp/DiscordUnix.cpp")
endif ()

if (${BUILD_SHARED_LIBS})
    add_library (HasiLWGDF_Core SHARED ${SOURCES})
else ()
    add_library (HasiLWGDF_Core STATIC ${SOURCES})
endif ()

include_directories (include)
include ("cmake/CPM.cmake")

# set (ASSIMP_INSTALL OFF)
# set (ASSIMP_BUILD_ZLIB OFF)
# if (${BUILD_SHARED_LIBS})
#     set (BUILD_SHARED_LIBS OFF)
#     CPMAddPackage ("gh:assimp/assimp#v5.2.5")
#     set (BUILD_SHARED_LIBS ON)
# else ()
#     CPMAddPackage ("gh:assimp/assimp#v5.2.5")
# endif ()

set (BOX2D_BUILD_TESTBED OFF)
CPMAddPackage ("gh:erincatto/box2d#v2.4.1")

set (ALSOFT_EXAMPLES OFF)
set (ALSOFT_INSTALL OFF)
set (ALSOFT_INSTALL_CONFIG OFF)
set (ALSOFT_INSTALL_HRTF_DATA OFF)
set (ALSOFT_INSTALL_AMBDEC_PRESETS OFF)
set (ALSOFT_INSTALL_EXAMPLES OFF)
set (ALSOFT_INSTALL_UTILS OFF)
set (LIBTYPE STATIC)
CPMAddPackage ("gh:kcat/openal-soft#openal-soft-1.21.0")

set (BUILD_BULLET2_DEMOS OFF)
CPMAddPackage ("gh:DanielChappuis/reactphysics3d#v0.9.0")

CPMAddPackage ("gh:libsdl-org/SDL#release-2.28.2")
# CPMAddPackage ("gh:KhronosGroup/OpenXR-SDK#release-1.0.27")

set (DEPENDENCIES_PRIVATE SDL2-static box2d ReactPhysics3D OpenAL)
set (DEPENDENCIES_PUBLIC pthread Vulkan::Vulkan)

set (INCLUDE_DIRS_PRIVATE
    "src/res"
    "src/hpp"
    "${box2d_SOURCE_DIR}/include"
    "${openal-soft_SOURCE_DIR}/include"
    "${ReactPhysics3D_SOURCE_DIR}/include"
    "${SDL2_INCLUDE_DIRS}"
    "${SUB_DIRS}/stb"
)
set (INCLUDE_DIRS_PUBLIC
    ${Vulkan_INCLUDE_DIR}
)

if (APPLE)
    set (CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version")
    set (DEPENDENCIES_PRIVATE ${DEPENDENCIES_PRIVATE} "-framework Metal" "-framework QuartzCore")
endif ()

target_link_libraries (
    HasiLWGDF_Core
    PRIVATE ${DEPENDENCIES_PRIVATE}
)

target_link_libraries (
    HasiLWGDF_Core
    PUBLIC ${DEPENDENCIES_PUBLIC}
)

target_include_directories (
    HasiLWGDF_Core
    PRIVATE ${INCLUDE_DIRS_PRIVATE}
)

target_include_directories (
    HasiLWGDF_Core
    PUBLIC ${INCLUDE_DIRS_PUBLIC}
)

if (${BUILD_SHARED_LIBS})
    target_compile_definitions (HasiLWGDF_Core PUBLIC -DHASILWGDF_DYNAMIC_LIB)
    target_compile_definitions (HasiLWGDF_Core PRIVATE -DHASILWGDF_BUILDING_SDK)
endif ()

# Install
install (
    TARGETS HasiLWGDF_Core
    EXPORT "HasiLWGDF_Core"
    RUNTIME
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
    LIBRARY
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    INCLUDES
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install (
    FILES
        "./include/Core.h"
    DESTINATION "include"
)
