#include <thread>
#include <SDL.h>
#include <Renderer.h>
#include <HasiLWGDF_Core.h>
#include <HasiLWGDF_DiscordRPC.h>

namespace Hasibix::HasiLWGDF::Core
{
    namespace Scripts
    {
    }

    namespace Game
    {
        SDL_Window *createWindow(Game *instance)
        {
            SDL_Window *window;
            switch (instance->getRenderer()->getAPI())
            {
            case Render::Renderer::API::Software:
                window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN);
                break;
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
            case Render::Renderer::API::OpenGL32 || Render::Renderer::API::OpenGL33 || Render::Renderer::API::OpenGL40 || Render::Renderer::API::OpenGL41 || Render::Renderer::API::OpenGL42 || Render::Renderer::API::OpenGL43 || Render::Renderer::API::OpenGL44 || Render::Renderer::API::OpenGL45 || Render::Renderer::API::OpenGL46:
                window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN |
                                              SDL_WINDOW_OPENGL);
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES)
            case Render::Renderer::API::OpenGLES30, Render::Renderer::API::OpenGLES31, Render::Renderer::API::OpenGLES32:
                window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN |
                                              SDL_WINDOW_OPENGL);
                break;
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
            case Render::Renderer::API::DirectX9 || Render::Renderer::API::DirectX11 || Render::Renderer::API::DirectX12:
                window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN);
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
            case Render::Renderer::API::Metal:
                window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN |
                                              SDL_WINDOW_ALLOW_HIGHDPI);
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
            case Render::Renderer::API::Vulkan10 || Render::Renderer::API::Vulkan11 || Render::Renderer::API::Vulkan12 || Render::Renderer::API::Vulkan13:
                window = SDL_CreateWindow(instance->getWindow().title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance->getWindow().width, instance->getWindow().height,
                                          SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_SHOWN |
                                              SDL_WINDOW_VULKAN);
                break;
#endif
            default:
                cout << "Invalid or incompatible graphics API set." << endl;
                break;
            }
            return window;
        }

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

        unique_ptr<void> init(SDL_Window *window, Game *instance)
        {
            unique_ptr<void> value;
            switch (instance->getRenderer()->getAPI())
            {
            case Render::Renderer::API::Software:
                value = Render::initSoftware(window, instance);
                break;
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
            case Render::Renderer::API::OpenGL32 || Render::Renderer::API::OpenGL33 || Render::Renderer::API::OpenGL40 || Render::Renderer::API::OpenGL41 || Render::Renderer::API::OpenGL42 || Render::Renderer::API::OpenGL43 || Render::Renderer::API::OpenGL44 || Render::Renderer::API::OpenGL45 || Render::Renderer::API::OpenGL46:
                value = Render::initOpenGL(window, instance);
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES)
            case Render::Renderer::API::OpenGLES30, Render::Renderer::API::OpenGLES31, Render::Renderer::API::OpenGLES32:
                value = Render::initOpenGLES(window, instance);
                break;
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
            case Render::Renderer::API::DirectX9:
                value = Render::initDirectX9(window, instance);
                break;
            case Render::Renderer::API::DirectX11:
                value = Render::initDirectX11(window, instance);
                break;
            case Render::Renderer::API::DirectX12:
                value = Render::initDirectX12(window, instance);
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
            case Render::Renderer::API::Metal:
                value = Render::initMetal(window, instance);
                break;
#endif
            default:
                cout << "Invalid or incompatible graphics API set." << endl;
                break;
            }
            return value;
        }

        void render(double alpha, SDL_Window *window, Game *instance, unique_ptr<void> renderer)
        {
            switch (instance->getRenderer()->getAPI())
            {
            case Render::Renderer::API::Software:
                Render::renderSoftware(alpha, window, instance, unique_ptr<Render::SoftwareRenderer>(static_cast<Render::SoftwareRenderer *>(renderer.release())));
                break;
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
            case Render::Renderer::API::OpenGL32 || Render::Renderer::API::OpenGL33 || Render::Renderer::API::OpenGL40 || Render::Renderer::API::OpenGL41 || Render::Renderer::API::OpenGL42 || Render::Renderer::API::OpenGL43 || Render::Renderer::API::OpenGL44 || Render::Renderer::API::OpenGL45 || Render::Renderer::API::OpenGL46:
                Render::renderOpenGL(alpha, window, instance, unique_ptr<Render::OpenGLRenderer>(static_cast<Render::OpenGLRenderer *>(renderer.release())));
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES)
            case Render::Renderer::API::OpenGLES30, Render::Renderer::API::OpenGLES31, Render::Renderer::API::OpenGLES32:
                Render::renderOpenGLES(alpha, window, instance, unique_ptr<Render::OpenGLESRenderer>(static_cast<Render::OpenGLESRenderer *>(renderer.release())));
                break;
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
            case Render::Renderer::API::DirectX9:
                Render::renderDirectX9(alpha, window, instance, unique_ptr<Render::D3D9Renderer>(static_cast<Render::D3D9Renderer *>(renderer.release())));
                break;
            case Render::Renderer::API::DirectX11:
                Render::renderDirectX11(alpha, window, instance, unique_ptr<Render::D3D11Renderer>(static_cast<Render::D3D11Renderer *>(renderer.release())));
                break;
            case Render::Renderer::API::DirectX12:
                Render::renderDirectX12(alpha, window, instance, unique_ptr<Render::D3D12Renderer>(static_cast<Render::D3D12Renderer *>(renderer.release())));
                break;
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
            case Render::Renderer::API::Metal:
                Render::renderMetal(alpha, window, instance, unique_ptr<Render::MetalRenderer>(static_cast<Render::MetalRenderer *>(renderer.release())));
                break;
#endif
            default:
                cout << "Invalid or incompatible graphics API set." << endl;
                break;
            }
        }

        int loop(Game *instance, SDL_Window *window, Render::Renderer *renderer, atomic_bool &gameRunning)
        {
            double delta;
            double accumulator = 0.0;
            double interval = 1.0 / instance->getTargetUPS();
            double alpha;

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
                render(alpha, window, instance);
            }

            SDL_DestroyWindow(window);
            SDL_Quit();

            return 0;
        }

        extern "C" HASILWGDF_EXPORT int Game::run(int currentScene)
        {
            SDL_Window *window;

            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                cout << "Unable to initialize SDL" << endl;
                return -1;
            }

            window = createWindow(this);

            if (!window)
            {
                cout << "Unable to create window" << endl;
                return -1;
            }

            SDL_Event event;

            atomic_bool gameRunning{true};
            thread loopThread(loop, this, window, ref(gameRunning));

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
