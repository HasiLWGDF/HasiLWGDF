#pragma once

#include <HasiLWGDF_Core.h>
#include <SDL.h>

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES)
#include <SDL_opengles2.h>
#include <GLES3/gl3.h>
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_PSGL)
// ...
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNM)
// ...
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNMX)
// ...
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
#include <windows.h>
#include <dxgi.h>
#include <d3d9.h>
#include <d3d10.h>
#include <d3d11.h>
#include <d3d12.h>
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#endif

namespace Hasibix::HasiLWGDF::Core
{
    namespace Render
    {
#ifdef __cplusplus
        extern "C"
        {
#endif
            typedef struct SoftwareRenderer
            {
                SDL_Renderer *ctx;
            } SoftwareRenderer;
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
            typedef struct OpenGLRenderer
            {
                unique_ptr<SDL_GLContext> ctx;
            } OpenGLRenderer;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES)
            typedef struct OpenGLESRenderer
            {
                unique_ptr<SDL_GLContext> ctx;
            } OpenGLESRenderer;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
            typedef struct D3D9Renderer
            {
                IDirect3DDevice9 *ctx;
                SDL_Renderer *renderer;
            } D3D9Renderer;
            typedef struct D3D11Renderer
            {
                ID3D11Device *ctx;
                SDL_Renderer *renderer;
            } D3D11Renderer;
            typedef struct D3D12Renderer
            {
                ID3D12Device *ctx;
                SDL_Renderer *renderer;
            } D3D12Renderer;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
            typedef struct MetalRenderer
            {
                const CAMetalLayer *ctx;
                SDL_Renderer *renderer;
            } MetalRenderer;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
            typedef struct VulkanRenderer
            {
                VkInstance instance;
                VkSurfaceKHR surface;
            } VulkanRenderer;
#endif
#ifdef __cplusplus
        }
#endif
        pair<SDL_Window *, unique_ptr<SoftwareRenderer>> initSoftware(Game::Game *instance);
        void deinitSoftware(unique_ptr<SoftwareRenderer> &renderer)
        {
            SDL_DestroyRenderer(renderer->ctx);
        }
        void renderSoftware(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<SoftwareRenderer> &renderer);
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
        pair<SDL_Window *, unique_ptr<OpenGLRenderer>> initOpenGL(Game::Game *instance);
        void deinitOpenGL(unique_ptr<OpenGLRenderer> &renderer)
        {
            SDL_GL_DeleteContext(&renderer->ctx);
        }
        void renderOpenGL(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<OpenGLRenderer> &renderer);
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES)
        pair<SDL_Window *, unique_ptr<OpenGLESRenderer>> initOpenGLES(Game::Game *instance);
        void deinitOpenGLES(unique_ptr<OpenGLESRenderer> &renderer)
        {
            SDL_GL_DeleteContext(&renderer->ctx);
        }
        void renderOpenGLES(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<OpenGLESRenderer> &renderer);
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
        pair<SDL_Window *, unique_ptr<D3D9Renderer>> initDirectX9(Game::Game *instance);
        void deinitDirectX9(unique_ptr<D3D9Renderer> &renderer)
        {
            renderer->ctx->Release();
            SDL_DestroyRenderer(renderer->renderer);
        }
        void renderDirectX9(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D9Renderer> &renderer);
        pair<SDL_Window *, unique_ptr<D3D11Renderer>> initDirectX11(Game::Game *instance);
        void deinitDirectX11(unique_ptr<D3D11Renderer> &renderer)
        {
            renderer->ctx->Release();
            SDL_DestroyRenderer(renderer->renderer);
        }
        void renderDirectX11(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D11Renderer> &renderer);
        pair<SDL_Window *, unique_ptr<D3D12Renderer>> initDirectX12(Game::Game *instance);
        void deinitDirectX12(unique_ptr<D3D12Renderer> &renderer)
        {
            renderer->ctx->Release();
            SDL_DestroyRenderer(renderer->renderer);
        }
        void renderDirectX12(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D12Renderer> &renderer);
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
        pair<SDL_Window *, unique_ptr<MetalRenderer>> initMetal(Game::Game *instance);
        void deinitMetal(unique_ptr<MetalRenderer> &renderer)
        {
            SDL_DestroyRenderer(renderer->renderer);
        }
        void renderMetalCpp(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<MetalRenderer> &renderer);
        void renderMetal(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<MetalRenderer> &renderer);
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
        pair<SDL_Window *, unique_ptr<VulkanRenderer>> initVulkan(Game::Game *instance);
        void deinitVulkan(unique_ptr<VulkanRenderer> &renderer)
        {
        }
        void renderVulkan(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<VulkanRenderer> &renderer);
#endif
    }
}