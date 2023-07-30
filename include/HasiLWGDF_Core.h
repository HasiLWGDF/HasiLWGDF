/*
    HasiLWGDF (Hasibix's Lightweight Game Development Framework)

    A simple, cross-platform game engine made with C++.
    Supports multiple graphics APIs and built on top of open-source
    resources.

    Copyright © 2023 Hasibix Hasib. All Rights Reserved.

    Thank you so much for using HasiLWGDF. Feel free to contribute our project.
    For more information, please visit https://github.com/HasiLWGDF/HasiLWGDF.

    This library is licensed under GNU Lesser General Public License version 3 (LGPLv3).
    You can find copy of the license from https://www.gnu.org/licenses.

    It is recommended NOT to modify this file. As doing such may result in compatibility
    issues or even PERMANENT damage to your project and/or device.
    DO NOT MODIFY THIS FILE UNLESS IT IS NECESSARY TO DO SO.
*/

#pragma once

#include <atomic>
#include <iostream>
#include <list>
#include <memory>

using namespace std;

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
#define PLATFORM_ANDROIDTV 1
#define PLATFORM_FREEBSD 2
#define PLATFORM_IOS 3
#define PLATFORM_LINUX 4
#define PLATFORM_MACOS 5
#define PLATFORM_OPENBSD 6
#define PLATFORM_OPENXR 7
#define PLATFORM_PLAYSTATION 8
#define PLATFORM_SWITCH 9
#define PLATFORM_TVOS 10
#define PLATFORM_UWP 11
#define PLATFORM_WATCHOS 12
#define PLATFORM_WEAROS 13
#define PLATFORM_WEB 14
#define PLATFORM_WINDOWS 15
#define PLATFORM_XBOX 16
#define PLATFORM_3DS 17
#define HASILWGDF_PLATFORM PLATFORM_WINDOWS

#if defined(HASILWGDF_PLATFORM)
#if HASILWGDF_PLATFORM == PLATFORM_ANDROID
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_ANDROIDTV
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_FREEBSD
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_IOS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES
#define HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_LINUX
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_MACOS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_OPENBSD
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
// #elif HASILWGDF_PLATFORM == PLATFORM_OPENXR
// #elif HASILWGDF_PLATFORM == PLATFORM_PLAYSTATION
#elif HASILWGDF_PLATFORM == PLATFORM_SWITCH
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_TVOS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_UWP
#define HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
#elif HASILWGDF_PLATFORM == PLATFORM_WATCHOS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
// #elif HASILWGDF_PLATFORM == PLATFORM_WEAROS
// #elif HASILWGDF_PLATFORM == PLATFORM_WEB
#elif HASILWGDF_PLATFORM == PLATFORM_WINDOWS
#define HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#define HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
#define HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#elif HASILWGDF_PLATFORM == PLATFORM_XBOX
#define HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
// #elif HASILWGDF_PLATFORM == PLATFORM_3DS
#else
#error "Unsupported platform specified."
#endif
#else
#error "Unable to detect target platform."
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    namespace Hasibix::HasiLWGDF::Core
    {
        namespace Math
        {
            typedef struct Vector3
            {
                double *x;
                double *y;
                double *z;
            } Vector3;
            typedef struct Vector2
            {
                double *x;
                double *y;
            } Vector2;

            typedef struct Quaternion
            {
                double *yaw;
                double *pitch;
                double *roll;
            } Quaternion;

            typedef struct Transform
            {
                Vector3 position;
                Quaternion rotation;
            } Transform;
        }

        namespace DiscordRPC
        {
            typedef struct Timestamps
            {
                int64_t start;
                int64_t end;
            } Timestamps;

            typedef struct Assets
            {
                const char *largeImage; /* max 128 bytes */
                const char *largeText;  /* max 128 bytes */
                const char *smallImage; /* max 128 bytes */
                const char *smallText;  /* max 128 bytes */
            } Assets;

            typedef struct PartySize
            {
                int current;
                int max;
            } PartySize;

            typedef struct Party
            {
                const char *id; /* max 128 bytes */
                PartySize size;
                int privacy;
            } Party;

            typedef struct Secrets
            {
                const char *match;    /* max 128 bytes */
                const char *join;     /* max 128 bytes */
                const char *spectate; /* max 128 bytes */
            } Secrets;

            typedef struct Activity
            {
                const char *state;   /* max 128 bytes */
                const char *details; /* max 128 bytes */
                Timestamps timestamps;
                Party party;
                Secrets secrets;
                bool instance;
            } Activity;
        }

        namespace Scripts
        {
            class Script
            {
            public:
                virtual ~Script() = default;
                virtual void onInitialize() = 0;
                virtual void onUpdate(double delta) = 0;
                virtual void onDestroy() = 0;
            };

            class DiscordRPC final : public Script
            {
            private:
                const char *client;

            public:
                DiscordRPC(const char *clientId) : client(clientId)
                {
                }

                void onInitialize() override
                {
                }

                void onUpdate(double delta) override
                {
                }

                void updateActivity(Hasibix::HasiLWGDF::Core::DiscordRPC::Activity *activity)
                {
                }

                void onDestroy() override
                {
                }
            };
        }

        namespace Render
        {
            typedef struct Window
            {
                const char *title;
                int x;
                int y;
                int width;
                int height;
            } Window;

            class Renderer final
            {
            public:
                enum API
                {
                    Software,
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
                    OpenGL32,
                    OpenGL33,
                    OpenGL40,
                    OpenGL41,
                    OpenGL42,
                    OpenGL43,
                    OpenGL44,
                    OpenGL45,
                    OpenGL46,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES)
                    OpenGLES30,
                    OpenGLES31,
                    OpenGLES32,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_PSGL)
                    PSGL,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNM)
                    GNM,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNMX)
                    GNMX,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
                    DirectX9,
                    DirectX11,
                    DirectX12,
#endif
#if !defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
                    Metal,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
                    Vulkan10,
                    Vulkan11,
                    Vulkan12,
                    Vulkan13,
#endif
                };
            private:
                API api;
                bool vsync;

            public:
                Renderer(API api, bool vsync = false) : api(api), vsync(vsync)
                {
                }

                API getAPI() const
                {
                    return this->api;
                }

                bool getVsync() const
                {
                    return this->vsync;
                }
            };
        }

        namespace Game
        {
            class GameObject final
            {
            private:
                Math::Transform *transform;
                list<Scripts::Script *> scripts;

            public:
                GameObject(Math::Transform *transform) : transform(transform)
                {
                }

                virtual void onInitialize() final
                {
                    for (Scripts::Script *i : this->scripts)
                    {
                        i->onInitialize();
                    }
                }

                virtual void onUpdate(double delta) final
                {
                    for (Scripts::Script *i : this->scripts)
                    {
                        i->onUpdate(delta);
                    }
                }

                virtual void onDestroy() final
                {
                    for (Scripts::Script *i : this->scripts)
                    {
                        i->onDestroy();
                    }
                }

                virtual void attachScripts(Scripts::Script *script...) final
                {
                    this->scripts.push_back(script);
                }
            };

            class Scene final
            {
            private:
                list<GameObject *> gameObjects;

            public:
                Scene(list<GameObject *> gameObjects) : gameObjects(gameObjects)
                {
                }

                void onInitialize()
                {
                    for (GameObject *i : this->gameObjects)
                    {
                        i->onInitialize();
                    }
                }

                void onUpdate(double delta)
                {
                    for (GameObject *i : this->gameObjects)
                    {
                        i->onUpdate(delta);
                    }
                }

                void onDestroy()
                {
                    for (GameObject *i : this->gameObjects)
                    {
                        i->onDestroy();
                    }
                }
            };

            class Timer final
            {
            private:
                double lastTime = 0.0;
                double deltaTime;
                int fps;
                int fpsCounter;

            public:
                HASILWGDF_EXPORT void update();
                HASILWGDF_EXPORT double getDeltaTime();
                HASILWGDF_EXPORT int getFps();
                HASILWGDF_EXPORT float getTime();
            };

            class Game
            {
            private:
                int updateSpeed;
                Render::Window &window;
                Render::Renderer *renderer;
                const int targetUPS = 60 * updateSpeed;
                list<unique_ptr<Scene>> scenes;
                int currentScene = 0;
                bool running = false;

            public:
                Timer timer;
                explicit Game(Render::Window &window, Render::Renderer *renderer, int updateSpeed) : window(window), renderer(renderer), updateSpeed(updateSpeed), timer()
                {
                }

                void addScene(unique_ptr<Scene> scene)
                {
                    this->scenes.push_back(scene);
                }

                Render::Window &getWindow() const
                {
                    return this->window;
                }

                Render::Renderer *getRenderer() const
                {
                    return renderer;
                }

                const int getTargetUPS() const
                {
                    return this->targetUPS;
                }

                list<unique_ptr<Scene>> getAllScenes() const
                {
                    return this->scenes;
                }

                int getCurrentScene() const
                {
                    return this->currentScene;
                }

                bool isRunning() const
                {
                    return this->running;
                }

                virtual ~Game() = default;
                virtual HASILWGDF_EXPORT int run(int currentScene) final;
            };
        }
    }

#ifdef __cplusplus
}
#endif
