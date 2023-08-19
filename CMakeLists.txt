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
    "src/hpp/game/AudioManager.hpp"
    "src/hpp/game/GameManager.hpp"
    "src/hpp/game/InputManager.hpp"

    "src/hpp/math/Timer.hpp"

    "src/hpp/physics/PhysicsEngine.hpp"

    "src/hpp/render/Renderer.hpp"


    "src/cpp/game/AudioManager.cpp"
    "src/cpp/game/GameManager.cpp"
    "src/cpp/game/InputManager.cpp"

    "src/cpp/math/Timer.cpp"

    "src/cpp/physics/PhysicsEngine2D.cpp"
    "src/cpp/physics/PhysicsEngine3D.cpp"

    "src/cpp/render/DX9Renderer.cpp"
    "src/cpp/render/DX11Renderer.cpp"
    "src/cpp/render/DX12Renderer.cpp"
    "src/cpp/render/OGLESRenderer.cpp"
    "src/cpp/render/OGLRenderer.cpp"
    "src/cpp/render/Renderer.cpp"
    "src/cpp/render/VKRenderer.cpp"
)

if (APPLE)
    set(SOURCES ${SOURCES} "src/cpp/render/MTLRenderer.mm")
endif ()

if (${BUILD_SHARED_LIBS})
    add_library (HasiLWGDF_Core SHARED ${SOURCES})
else ()
    add_library (HasiLWGDF_Core STATIC ${SOURCES})
endif ()

include_directories (include)

include ("cmake/CPM.cmake")
CPMAddPackage ("gh:libsdl-org/SDL#release-2.28.2")
set (ALSOFT_EXAMPLES OFF)
set (ALSOFT_INSTALL OFF)
set (ALSOFT_INSTALL_CONFIG OFF)
set (ALSOFT_INSTALL_HRTF_DATA OFF)
set (ALSOFT_INSTALL_AMBDEC_PRESETS OFF)
set (ALSOFT_INSTALL_EXAMPLES OFF)
set (ALSOFT_INSTALL_UTILS OFF)
set (LIBTYPE STATIC)
CPMAddPackage ("gh:kcat/openal-soft#openal-soft-1.21.0")

set (ASSIMP_INSTALL OFF)
set (ASSIMP_BUILD_ZLIB OFF)
if (${BUILD_SHARED_LIBS})
    set (BUILD_SHARED_LIBS OFF)
    CPMAddPackage ("gh:assimp/assimp#v5.2.5")
    set (BUILD_SHARED_LIBS ON)
else ()
    CPMAddPackage ("gh:assimp/assimp#v5.2.5")
endif ()

set (BOX2D_BUILD_TESTBED OFF)
CPMAddPackage ("gh:erincatto/box2d#v2.4.1")

set (BUILD_BULLET2_DEMOS OFF)
CPMAddPackage ("gh:DanielChappuis/reactphysics3d#v0.9.0")
# CPMAddPackage ("gh:KhronosGroup/OpenXR-SDK#release-1.0.27")

set (DEPENDENCIES_PRIVATE SDL2-static assimp box2d ReactPhysics3D OpenAL)
set (DEPENDENCIES_PUBLIC pthread Vulkan::Vulkan)

set (INCLUDE_DIRS_PRIVATE
    ${SDL2_INCLUDE_DIRS}
    "${assimp_SOURCE_DIR}/include"
    "${openal-soft_SOURCE_DIR}/include"
    "${box2d_SOURCE_DIR}/include"
    "${ReactPhysics3D_SOURCE_DIR}/include"
    "${SUB_DIRS}/stb"
)
set (INCLUDE_DIRS_PUBLIC
    ${Vulkan_INCLUDE_DIR}
)

if (APPLE OR (UNIX AND NOT APPLE) OR WIN32)
    add_subdirectory ("${SUB_DIRS}/HasiLWGDF_DiscordRPC")
    set (DEPENDENCIES_PRIVATE ${DEPENDENCIES_PRIVATE} HasiLWGDF_DiscordRPC)
    set (INCLUDE_DIRS_PRIVATE ${INCLUDE_DIRS_PRIVATE} "${SUB_DIRS}/HasiLWGDF_DiscordRPC/include/")
endif ()

if (APPLE)
    set (DEPENDENCIES_PRIVATE ${DEPENDENCIES_PRIVATE} "-framework Metal" "-framework QuartzCore")
endif ()

target_link_libraries(
    HasiLWGDF_Core
    PRIVATE ${DEPENDENCIES_PRIVATE}
)

target_link_libraries(
    HasiLWGDF_Core
    PUBLIC ${DEPENDENCIES_PUBLIC}
)

target_include_directories(
    HasiLWGDF_Core
    PRIVATE ${INCLUDE_DIRS_PRIVATE}
)

target_include_directories(
    HasiLWGDF_Core
    PUBLIC ${INCLUDE_DIRS_PUBLIC}
)

if (${BUILD_SHARED_LIBS})
    target_compile_definitions (HasiLWGDF_DiscordRPC PUBLIC -DHASILWGDF_DYNAMIC_LIB)
    target_compile_definitions (HasiLWGDF_DiscordRPC PRIVATE -DHASILWGDF_BUILDING_SDK)
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
        "./include/HasiLWGDF_Core.h"
    DESTINATION "include"
)
