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

#include <game/GameManager.hpp>
#include <thread>

#ifdef HASILWGDF_DISCORDRPC_SUPPORTED
#include <HasiLWGDF_DiscordRPC.h>
#endif
#include <game/InputManager.hpp>
#include <render/Renderer.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Game
{
    const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("GameManager"));
    const std::unique_ptr<Logger> pDLogger = std::make_unique<Logger>(Logger("DiscordRPC"));

    int _GameManager_::earlyUpdate(float delta)
    {
        return 0;
    }
    int _GameManager_::update(float delta)
    {
        return 0;
    }
    int _GameManager_::lateUpdate(float delta)
    {
        return 0;
    }

    int _GameManager_::loop()
    {
        double delta;
        double accumulator = 0.0;
        double interval = 1.0 / (60 * GameManager::config.timescale);
        double alpha;

        std::unique_ptr<Render::Graphics::Renderer> &renderer = Render::Graphics::getRenderer();
        renderer->init();

        while (gameRunning)
        {
            delta = timer->getDeltaTime();
            accumulator += delta;

            _InputManager_::getInstance()->update();

            while (accumulator >= interval)
            {
                earlyUpdate(delta);
                update(delta);
                lateUpdate(delta);
                accumulator -= interval;
            }

            alpha = accumulator / interval;
            renderer->render(alpha);

            timer->update();
        }

        _InputManager_::Release();
        renderer->deinit();
        return 0;
    }

    int _GameManager_::discord()
    {
#ifdef HASILWGDF_DISCORDRPC_SUPPORTED
        if (!GameManager::config.discordRpc.enabled)
        {
            pDLogger->log(Logger::Level::WARN, "DiscordRPC is disabled.");
            return 0;
        }
        Discord_Initialize(GameManager::config.discordRpc.clientId, nullptr, 1, nullptr);
        while (gameRunning)
        {
            Discord_RunCallbacks();
            std::this_thread::sleep_for(std::chrono::milliseconds(32));
        }
        Discord_Shutdown();
#else
        pDLogger->log(Logger::Level::WARN, "DiscordRPC is not supported on this platform.");
#endif
        return 0;
    }

    int _GameManager_::run(int currentScene)
    {
        if (this->gameRunning)
        {
            pLogger->log(Logger::Level::ERR, "The game is already running.");
            return -1;
        }
        this->gameRunning = true;

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            pLogger->log(Logger::Level::ERR, "Unable to initialize SDL.");
            return -1;
        }

        std::atomic<SDL_Window *> pWindow;

        std::thread loopThread(loop);
        std::thread discordThread(discord);

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
                    //     pGame->getWindow()->width = event.window.data1;
                    //     pGame->getWindow()->height = event.window.data2;
                }
                else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_MOVED)
                {
                    //     pGame->getWindow()->x = event.window.data1;
                    //     pGame->getWindow()->y = event.window.data2;
                }
            }
            SDL_Delay(4);
        }

        if (loopThread.joinable())
        {
            loopThread.join();
        }
        if (discordThread.joinable())
        {
            discordThread.join();
        }
        SDL_Quit();
        gameRunning = false;

        return 0;
    }

    extern "C" HASILWGDF_EXPORT int GameManager::run(int currentScene)
    {
        running = true;

        int exitCode = _GameManager_::getInstance()->run(currentScene);

        running = false;

        return exitCode != 0 ? -1 : 0;
    }
}
