#include <HasiLWGDF_Core.h>
#include "Renderer.h"

using namespace std;

namespace Hasibix::HasiLWGDF::Core
{
        namespace Render
        {
                pair<SDL_Window *, unique_ptr<SoftwareRenderer>> initSoftware(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN);
                        SDL_Surface *surface = SDL_GetWindowSurface(window);
                        SDL_Renderer *ctx;
                        if (instance->getRenderer()->getVsync())
                        {
                                ctx = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
                        }
                        else
                        {
                                ctx = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                        }
                        return pair<SDL_Window *, unique_ptr<SoftwareRenderer>>{window, make_unique<SoftwareRenderer>(SoftwareRenderer{ctx})};
                }
                void renderSoftware(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<SoftwareRenderer> &renderer)
                {
                        return;
                }

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
                pair<SDL_Window *, unique_ptr<OpenGLRenderer>> initOpenGL(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN |
                                                                  SDL_WINDOW_OPENGL);
                        if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL32)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL33)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL40)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL41)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL42)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL43)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL44)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL45)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGL46)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
                        }
                        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
                        SDL_GLContext ctx = SDL_GL_CreateContext(window);
                        if (instance->getRenderer()->getVsync())
                        {
                                SDL_GL_SetSwapInterval(1);
                        }
                        else
                        {
                                SDL_GL_SetSwapInterval(0);
                        }

                        return pair<SDL_Window *, unique_ptr<OpenGLRenderer>>{window, make_unique<OpenGLRenderer>(OpenGLRenderer{make_unique<SDL_GLContext>(ctx)})};
                }
                void renderOpenGL(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<OpenGLRenderer> &renderer)
                {
                        return;
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES)
                pair<SDL_Window *, unique_ptr<OpenGLESRenderer>> initOpenGLES(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN |
                                                                  SDL_WINDOW_OPENGL);
                        if (instance->getRenderer()->getAPI() == Renderer::API::OpenGLES30)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGLES31)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
                        }
                        else if (instance->getRenderer()->getAPI() == Renderer::API::OpenGLES32)
                        {
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
                        }
                        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
                        SDL_GLContext ctx = SDL_GL_CreateContext(window);
                        if (instance->getRenderer()->getVsync())
                        {
                                SDL_GL_SetSwapInterval(1);
                        }
                        else
                        {
                                SDL_GL_SetSwapInterval(0);
                        }

                        return pair<SDL_Window *, unique_ptr<OpenGLESRenderer>>{window, make_unique<OpenGLESRenderer>(OpenGLESRenderer{make_unique<SDL_GLContext>(ctx)})};
                }
                void renderOpenGLES(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<OpenGLESRenderer> &renderer)
                {
                        return;
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
                pair<SDL_Window *, unique_ptr<D3D9Renderer>> initDirectX9(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN);
                        SDL_Renderer *renderer;
                        if (instance->getRenderer()->getVsync())
                        {
                                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                        }
                        else
                        {
                                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                        }
                        IDirect3DDevice9 *ctx = SDL_RenderGetD3D9Device(renderer);
                        return pair<SDL_Window *, unique_ptr<D3D9Renderer>>{window, make_unique<D3D9Renderer>(D3D9Renderer{ctx, renderer})};
                }
                void renderDirectX9(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D9Renderer> &renderer)
                {
                        return;
                }
                pair<SDL_Window *, unique_ptr<D3D11Renderer>> initDirectX11(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN);
                        SDL_Renderer *renderer;
                        if (instance->getRenderer()->getVsync())
                        {
                                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                        }
                        else
                        {
                                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                        }
                        ID3D11Device *ctx = SDL_RenderGetD3D11Device(renderer);
                        return pair<SDL_Window *, unique_ptr<D3D11Renderer>>{window, make_unique<D3D11Renderer>(D3D11Renderer{ctx, renderer})};
                }
                void renderDirectX11(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D11Renderer> &renderer)
                {
                        return;
                }
                pair<SDL_Window *, unique_ptr<D3D12Renderer>> initDirectX12(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN);
                        SDL_Renderer *renderer;
                        if (instance->getRenderer()->getVsync())
                        {
                                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                        }
                        else
                        {
                                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                        }
                        ID3D12Device *ctx = SDL_RenderGetD3D12Device(renderer);
                        return pair<SDL_Window *, unique_ptr<D3D12Renderer>>{window, make_unique<D3D12Renderer>(D3D12Renderer{ctx, renderer})};
                }
                void renderDirectX12(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D12Renderer> &renderer)
                {
                        return;
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
                void renderMetalCpp(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<MetalRenderer> &renderer)
                {
                        return;
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
                pair<SDL_Window *, unique_ptr<VulkanRenderer>> initVulkan(Game::Game *instance)
                {
                        SDL_Window *window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                                              SDL_WINDOW_RESIZABLE |
                                                                  SDL_WINDOW_SHOWN |
                                                                  SDL_WINDOW_VULKAN);
                        uint32_t extensionCount;
                        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
                        vector<const char *> extensionNames(extensionCount);
                        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());
                        VkApplicationInfo appInfo{};
                        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                        appInfo.pApplicationName = instance->getWindow().title;
                        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
                        appInfo.pEngineName = "HasiLWGDF Renderer";
                        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
                        if (instance->getRenderer()->getAPI() == Renderer::API::Vulkan10)
                                appInfo.apiVersion = VK_API_VERSION_1_0;
                        else if (instance->getRenderer()->getAPI() == Renderer::API::Vulkan11)
                                appInfo.apiVersion = VK_API_VERSION_1_1;
                        else if (instance->getRenderer()->getAPI() == Renderer::API::Vulkan12)
                                appInfo.apiVersion = VK_API_VERSION_1_2;
                        else if (instance->getRenderer()->getAPI() == Renderer::API::Vulkan13)
                                appInfo.apiVersion = VK_API_VERSION_1_3;
                        vector<const char *> layerNames{};
                        VkInstanceCreateInfo info{};
                        info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                        info.pApplicationInfo = &appInfo;
                        info.enabledLayerCount = layerNames.size();
                        info.ppEnabledLayerNames = layerNames.data();
                        info.enabledExtensionCount = extensionNames.size();
                        info.ppEnabledExtensionNames = extensionNames.data();
                        VkResult res;
                        VkInstance vkInst;
                        res = vkCreateInstance(&info, nullptr, &vkInst);
                        if (res != VK_SUCCESS)
                        {
                                cout << "Failed to create Vulkan instance." << endl;
                                return pair<SDL_Window *, unique_ptr<VulkanRenderer>>{nullptr, nullptr};
                        }
                        VkSurfaceKHR surface;
                        if (!SDL_Vulkan_CreateSurface(window, vkInst, &surface))
                        {
                                cout << "Failed to create Vulkan surface." << endl;
                                return pair<SDL_Window *, unique_ptr<VulkanRenderer>>{nullptr, nullptr};
                        }
                        return pair<SDL_Window *, unique_ptr<VulkanRenderer>>{window, make_unique<VulkanRenderer>(VulkanRenderer{vkInst, surface})};
                }
                void renderVulkan(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<VulkanRenderer> &renderer)
                {
                        return;
                }
#endif
        }
}
