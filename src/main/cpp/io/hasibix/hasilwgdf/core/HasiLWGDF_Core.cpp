#include <thread>
#include <SDL.h>
#include <HasiLWGDF_Core.h>
#include "Renderer.h"
#include <HasiLWGDF_DiscordRPC.h>

namespace Hasibix::HasiLWGDF::Core
{
    namespace Scripts
    {
    }

    namespace Game
    {
        extern "C" HASILWGDF_EXPORT void Timer::update()
        {
            float currentTime = float(SDL_GetTicks()) / 1000.0f;
            this->deltaTime = currentTime - this->lastTime;
            this->lastTime = currentTime;
            this->fpsCounter++;

            if (currentTime >= this->lastTime + 1.0f)
            {
                this->fps = this->fpsCounter;
                this->fpsCounter = 0;
            }
        }

        extern "C" HASILWGDF_EXPORT double Timer::getDeltaTime()
        {
            return this->deltaTime;
        }

        extern "C" HASILWGDF_EXPORT int Timer::getFps()
        {
            return this->fps;
        }

        extern "C" HASILWGDF_EXPORT float Timer::getTime()
        {
            return float(SDL_GetTicks()) / 1000.0f;
        }

        void update(Game *instance)
        {
            float delta = 1.0 / instance->getTargetUPS();
        }

        int loop(Game *instance, atomic<SDL_Window *> &window, Render::Renderer *renderer, atomic_bool &gameRunning)
        {
            if (renderer->getAPI() == Render::Renderer::API::Software)
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::SoftwareRenderer>> inst = Render::initSoftware(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderSoftware(alpha, window, instance, inst.second);
                }
                Render::deinitSoftware(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
            else if (renderer->getAPI() == (Render::Renderer::API::OpenGL32 || Render::Renderer::API::OpenGL33 || Render::Renderer::API::OpenGL40 || Render::Renderer::API::OpenGL41 || Render::Renderer::API::OpenGL42 || Render::Renderer::API::OpenGL43 || Render::Renderer::API::OpenGL44 || Render::Renderer::API::OpenGL45 || Render::Renderer::API::OpenGL46))
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::OpenGLRenderer>> inst = Render::initOpenGL(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderOpenGL(alpha, window, instance, inst.second);
                }
                Render::deinitOpenGL(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES)
            else if (renderer->getAPI() == (Render::Renderer::API::OpenGLES30 || Render::Renderer::API::OpenGLES31 || Render::Renderer::API::OpenGLES32))
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::OpenGLESRenderer>> inst = Render::initOpenGLES(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderOpenGLES(alpha, window, instance, inst.second);
                }
                Render::deinitOpenGLES(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
            else if (renderer->getAPI() == Render::Renderer::API::DirectX9)
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::D3D9Renderer>> inst = Render::initDirectX9(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderDirectX9(alpha, window, instance, inst.second);
                }
                Render::deinitDirectX9(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            else if (renderer->getAPI() == Render::Renderer::API::DirectX11)
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::D3D11Renderer>> inst = Render::initDirectX11(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderDirectX11(alpha, window, instance, inst.second);
                }
                Render::deinitDirectX11(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            else if (renderer->getAPI() == Render::Renderer::API::DirectX12)
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::D3D12Renderer>> inst = Render::initDirectX12(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderDirectX12(alpha, window, instance, inst.second);
                }
                Render::deinitDirectX12(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
            else if (renderer->getAPI() == Render::Renderer::API::Metal)
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::D3DRenderer>> inst = Render::initMetal(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderMetal(alpha, window, instance, inst.second);
                }
                Render::deinitMetal(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
            else if (renderer->getAPI() == (Render::Renderer::API::Vulkan10 || Render::Renderer::API::Vulkan11 || Render::Renderer::API::Vulkan12 || Render::Renderer::API::Vulkan13))
            {
                double delta;
                double accumulator = 0.0;
                double interval = 1.0 / instance->getTargetUPS();
                double alpha;

                pair<SDL_Window *, unique_ptr<Render::VulkanRenderer>> inst = Render::initVulkan(instance);
                window = inst.first;

                if (!window)
                {
                    cout << "Unable to create window" << endl;
                    return -1;
                }

                while (gameRunning)
                {
                    instance->timer.update();
                    delta = instance->timer.getDeltaTime();
                    accumulator += delta;

                    while (accumulator >= interval)
                    {
                        update(instance);
                        accumulator -= interval;
                    }

                    alpha = accumulator / interval;
                    Render::renderVulkan(alpha, window, instance, inst.second);
                }
                Render::deinitVulkan(inst.second);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
#endif
            return 0;
        }

        extern "C" HASILWGDF_EXPORT int Game::run(int currentScene)
        {
            atomic<SDL_Window *> window{nullptr};

            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                cout << "Unable to initialize SDL" << endl;
                return -1;
            }

            atomic_bool gameRunning{true};
            thread loopThread(loop, this, ref(window), ref(gameRunning));
            if (!window)
            {
                cout << "Unable to create window" << endl;
                return -1;
            }
            SDL_Event event;

            while (gameRunning)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        gameRunning = false;
                    }
                    else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        this->window.width = event.window.data1;
                        this->window.height = event.window.data2;
                    }
                    else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_MOVED)
                    {
                        this->window.x = event.window.data1;
                        this->window.y = event.window.data2;
                    }
                }
                SDL_Delay(8);
            }

            loopThread.join();
            this->running = false;

            return 0;
        }
    }
}
