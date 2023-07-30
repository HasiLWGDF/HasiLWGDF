#include <Renderer.h>

using namespace std;

namespace Hasibix::HasiLWGDF::Core
{
        namespace Render
        {
                unique_ptr<SoftwareRenderer> initSoftware(SDL_Window *window, Game::Game *instance)
                {
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
                        return make_unique<SoftwareRenderer>(SoftwareRenderer{ctx});
                }
                void renderSoftware(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<SoftwareRenderer> renderer)
                {
                        return;
                }

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
                unique_ptr<OpenGLRenderer> initOpenGL(SDL_Window *window, Game::Game *instance)
                {
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
                        else
                        {
                                cout << "Invalid graphics API. Please initialize the appropriate context for the selected API." << endl;
                                return nullptr;
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

                        return make_unique<OpenGLRenderer>(OpenGLRenderer{make_unique<SDL_GLContext>(ctx)});
                }
                void renderOpenGL(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<OpenGLRenderer> renderer)
                {
                        return;
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES)
                unique_ptr<OpenGLESRenderer> initOpenGLES(SDL_Window *window, Game::Game *instance)
                {
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
                        else
                        {
                                cout << "Invalid graphics API. Please initialize the appropriate context for the selected API." << endl;
                                return nullptr;
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

                        return make_unique<OpenGLESRenderer>(OpenGLESRenderer{make_unique<SDL_GLContext>(ctx)});
                }
                void renderOpenGLES(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<OpenGLESRenderer> renderer)
                {
                        return;
                }
#endif

                // #if !defined(HASILWGDF_GRAPHICS_API_SUPPORTED_PSGL)
                //                 auto *initPSGL(SDL_Window *window, Game::Game * instance)
                //                 {
                //                 }
                // #endif

                // #if !defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNM)
                //                 auto *initGNM(SDL_Window *window, Game::Game * instance)
                //                 {
                //                 }
                // #endif

                // #if !defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNMX)
                //                 auto *initGNMX(SDL_Window *window, Game::Game * instance)
                //                 {
                //                 }
                // #endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
                unique_ptr<D3D9Renderer> initDirectX9(SDL_Window *window, Game::Game *instance)
                {
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
                        return make_unique<D3D9Renderer>(D3D9Renderer{ctx, renderer});
                }
                void renderDirectX9(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D9Renderer> renderer)
                {
                        return;
                }
                unique_ptr<D3D11Renderer> initDirectX11(SDL_Window *window, Game::Game *instance)
                {
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
                        return make_unique<D3D11Renderer>(D3D11Renderer{ctx, renderer});
                }
                void renderDirectX11(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D11Renderer> renderer)
                {
                        return;
                }
                unique_ptr<D3D12Renderer> initDirectX12(SDL_Window *window, Game::Game *instance)
                {
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
                        return make_unique<D3D12Renderer>(D3D12Renderer{ctx, renderer});
                }
                void renderDirectX12(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<D3D12Renderer> renderer)
                {
                        return;
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
                void renderMetalCpp(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<MetalRenderer> renderer)
                {
                }
#endif

#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
                unique_ptr<VulkanRenderer> initVulkan(SDL_Window *window, Game::Game *instance)
                {
                        return NULL;
                }
                void renderVulkan(double alpha, SDL_Window *window, Game::Game *instance, unique_ptr<VulkanRenderer> renderer)
                {
                        return;
                }
#endif
        }
}
