cmake_minimum_required (VERSION 3.8.0 FATAL_ERROR)

project (HasiLWGDF_Core LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (SUB_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/subdirs")
set (IDENTIFIER "io/hasibix/hasilwgdf/core")
set (SOURCE_DIR "src/main/cpp/${IDENTIFIER}")

add_definitions(-DNOMINMAX -DSDL_MAIN_HANDLED)

include (GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

find_package(Vulkan REQUIRED)

if (NOT DEFINED BUILD_SHARED_LIBS)
    set (BUILD_SHARED_LIBS OFF)
endif ()

set (SOURCES
    "include/HasiLWGDF_Core.h"
    "${SOURCE_DIR}/HasiLWGDF_Core.cpp"
    "${SOURCE_DIR}/Renderer.h"
)

if (APPLE)
    set(SOURCES ${SOURCES} "${SOURCE_DIR}/Renderer.cpp" "${SOURCE_DIR}/Renderer.mm")
else ()
    set(SOURCES ${SOURCES} "${SOURCE_DIR}/Renderer.cpp")
endif ()

if (${BUILD_SHARED_LIBS})
    add_library (HasiLWGDF_Core SHARED ${SOURCES})
else ()
    add_library (HasiLWGDF_Core STATIC ${SOURCES})
endif ()

include_directories (include)

include ("cmake/CPM.cmake")
CPMAddPackage ("gh:libsdl-org/SDL#release-2.26.5")
CPMAddPackage ("gh:assimp/assimp#v5.2.5")
CPMAddPackage ("gh:erincatto/box2d#v2.4.1")
CPMAddPackage ("gh:KhronosGroup/OpenXR-SDK#release-1.0.27")

set (DEPENDENCIES SDL2-static box2d Assimp pthread OPENXR Vulkan::Vulkan)

set (INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})

if (APPLE OR (UNIX AND NOT APPLE) OR WIN32)
    add_subdirectory ("${SUB_DIRS}/HasiLWGDF_DiscordRPC")
    set (DEPENDENCIES ${DEPENDENCIES} HasiLWGDF_DiscordRPC)
    set (INCLUDE_DIRS ${INCLUDE_DIRS} "${SUB_DIRS}/HasiLWGDF_DiscordRPC/include/")
endif ()

if (APPLE)
    set (DEPENDENCIES ${DEPENDENCIES} "-framework AppKit" "-framework QuartzCore")
endif ()

target_link_libraries (HasiLWGDF_Core PRIVATE ${DEPENDENCIES})

target_include_directories (HasiLWGDF_Core PRIVATE ${INCLUDE_DIRS})

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
