/*
    HasiLWGDF (Hasibix's Lightweight Game Development Framework)

    A simple, cross-platform game engine made with C++.
    Supports multiple graphics APIs and built on top of open-source
    resources.

    Copyright (c) 2023 Hasibix Hasib. All Rights Reserved.

    Thank you so much for using HasiLWGDF. Feel free to contribute our project.
    For more information, please visit https://github.com/HasiLWGDF/HasiLWGDF.

    This library is licensed under GNU Lesser General Public License version 3 (LGPLv3).
    You can find copy of the license from https://www.gnu.org/licenses.

    It is recommended NOT to modify this file. As doing such may result in compatibility
    issues or even PERMANENT damage to your project.
    DO NOT MODIFY THIS FILE UNLESS IT IS NECESSARY TO DO SO.
*/

#pragma once

#include <hasilwgdf/Core.h>
#include <atomic>
#include <memory>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_quit.h>
#include <SDL_video.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Render
{
    const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("Renderer"));
    class Graphics final
    {
    public:
        class Renderer
        {
        protected:
            std::atomic<SDL_Window *> pWindow;

        public:
            explicit Renderer()
            {
            }
            virtual ~Renderer() = default;
            virtual int init() = 0;
            virtual int render(float alpha) = 0;
            virtual int deinit() = 0;

            virtual std::atomic<SDL_Window *> &getWindow() final
            {
                return std::ref(this->pWindow);
            }
        };

    private:
        Graphics() = delete;

        static std::unique_ptr<Renderer> createRenderer();
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
        static std::unique_ptr<Renderer> createOGLRenderer();
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES
        static std::unique_ptr<Renderer> createOGLESRenderer();
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
        static std::unique_ptr<Renderer> createDX9Renderer();
        static std::unique_ptr<Renderer> createDX11Renderer();
        static std::unique_ptr<Renderer> createDX12Renderer();
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
        static std::unique_ptr<Renderer> createMTLRenderer();
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
        static std::unique_ptr<Renderer> createVKRenderer();
#endif

    public:
        static std::unique_ptr<Renderer> &getRenderer()
        {
            std::unique_ptr<Renderer> renderer = nullptr;
            switch (Game::GameManager::config.graphics.api)
            {
            case Render::GraphicsAPI::Software:
                renderer = createRenderer();
                break;
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
            case Render::GraphicsAPI::OpenGL32 |
                Render::GraphicsAPI::OpenGL33 |
                Render::GraphicsAPI::OpenGL40 |
                Render::GraphicsAPI::OpenGL41 |
                Render::GraphicsAPI::OpenGL42 |
                Render::GraphicsAPI::OpenGL43 |
                Render::GraphicsAPI::OpenGL44 |
                Render::GraphicsAPI::OpenGL45 |
                Render::GraphicsAPI::OpenGL46:
                renderer = createOGLRenderer();
                break;
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES
            case Render::GraphicsAPI::OpenGLES20:
                renderer = createOGLESRenderer(pInstance);
                break;
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
            case Render::GraphicsAPI::DirectX9:
                renderer = createDX9Renderer();
                break;
            case Render::GraphicsAPI::DirectX11:
                renderer = createDX11Renderer();
                break;
            case Render::GraphicsAPI::DirectX12:
                renderer = createDX12Renderer();
                break;
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
            case Render::GraphicsAPI::Metal:
                renderer = createMTLRenderer();
                break;
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
            case Render::GraphicsAPI::Vulkan10 |
                Render::GraphicsAPI::Vulkan11 |
                Render::GraphicsAPI::Vulkan12 |
                Render::GraphicsAPI::Vulkan13:
                renderer = createVKRenderer();
                break;
#endif
            };
            if (!renderer)
            {
                pLogger->log(Logger::Level::FATAL, "Failed to initialize renderer.");
            }
            return std::ref(renderer);
        }
    };
}
