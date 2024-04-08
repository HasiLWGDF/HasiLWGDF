/*
    HasiLWGDF (Hasibix's Lightweight Game Development Framework)

    A simple, cross-platform game engine made with C++.
    Supports multiple graphics APIs and built on top of open-source
    resources.

    Copyright (c) 2024 Hasibix Hasib. All Rights Reserved.

    Thank you so much for using HasiLWGDF. Feel free to contribute our project.
    For more information, please visit https://github.com/HasiLWGDF/HasiLWGDF.

    This library is licensed under GNU Lesser General Public License version 3 (LGPLv3).
    You can find copy of the license from https://www.gnu.org/licenses.

    It is recommended NOT to modify this file. As doing such may result in compatibility
    issues or even PERMANENT damage to your project.
    DO NOT MODIFY THIS FILE UNLESS IT IS NECESSARY TO DO SO.
*/

#pragma once

#if defined(HASILWGDF_DYNAMIC_LIB)
#if defined(_WIN32)
#if defined(HASILWGDF_BUILDING_SDK)
#define HASILWGDF_EXPORT __declspec(dllexport)
#else
#define HASILWGDF_EXPORT __declspec(dllimport)
#endif
#else
#define HASILWGDF_EXPORT __attribute__((visibility("default")))
#endif
#else
#define HASILWGDF_EXPORT
#endif

#define PLATFORM_ANDROID 0
#define PLATFORM_IOS 3
#define PLATFORM_LINUX 4
#define PLATFORM_MACOS 5
#define PLATFORM_UWP 11
#define PLATFORM_WINDOWS 15
#define HASILWGDF_PLATFORM PLATFORM_WINDOWS

#if defined(HASILWGDF_PLATFORM)
#if HASILWGDF_PLATFORM == PLATFORM_ANDROID
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_IOS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES
#define HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_LINUX
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#define HASILWGDF_DISCORDRPC_SUPPORTED
#elif HASILWGDF_PLATFORM == PLATFORM_MACOS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#define HASILWGDF_DISCORDRPC_SUPPORTED
#elif HASILWGDF_PLATFORM == PLATFORM_UWP
#define HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
#elif HASILWGDF_PLATFORM == PLATFORM_WINDOWS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#define HASILWGDF_DISCORDRPC_SUPPORTED
#else
#error "Unsupported platform specified."
#endif
#else
#error "Unable to detect target platform."
#endif
