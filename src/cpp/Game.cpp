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

#include "../hpp/Game.hpp"
#include "../hpp/input/Joystick.hpp"
#include "../hpp/input/Keyboard.hpp"
#include "../hpp/input/Mouse.hpp"
#include "../hpp/input/Touch.hpp"
#include <thread>

#include "../hpp/graphics/Renderer.hpp"

#define SDL_MAIN_HANDLED
#include "SDL.h"

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("Game"));
	const std::unique_ptr<Logger> pDLogger = std::make_unique<Logger>(
		Logger("Discord"));

	_Game_ *_Game_::instance()
	{
		if (!pInstance)
		{
			pInstance = new _Game_();
		}
		return pInstance;
	}

	void _Game_::release()
	{
		if (!pInstance)
		{
			pLogger->log(Logger::Level::ERR, "Game is not initialized yet.");
		}
		delete pInstance;
		pInstance = nullptr;
	}

	int _Game_::loop(SDL_Event &event, std::unique_lock<std::mutex> &lock,
					 void (*initialize)(), void (*preUpdate)(float), void (*update)(float),
					 void (*postUpdate)(float), void (*destroy)())
	{
		double delta;
		double accumulator = 0.0;
		double interval = 1.0 / (60 * Game::config.timescale);
		double alpha;

		std::unique_ptr<Graphics::Renderer> &renderer = Graphics::getRenderer();
		renderer->init();

		initialize();

		while (gameRunning)
		{
			lock.lock();

			delta = timer->getDeltaTime();
			accumulator += delta;

			lock.unlock();

			Input::_Joystick_::instance()->update();
			Input::_Keyboard_::instance()->update();
			Input::_Mouse_::instance()->update();
			Input::_Touch_::instance()->update(event);

			while (accumulator >= interval)
			{
				lock.lock();

				preUpdate(delta);
				update(delta);
				postUpdate(delta);
				accumulator -= interval;

				lock.unlock();
			}

			alpha = accumulator / interval;
			renderer->render(alpha);

			timer->update();
		}

		destroy();

		Input::_Joystick_::release();
		Input::_Keyboard_::release();
		Input::_Mouse_::release();
		Input::_Touch_::release();
		renderer->destroy();
		return 0;
	}

	int _Game_::discord(std::unique_ptr<Discord::Activity> &activity,
						std::unique_lock<std::mutex> &lock)
	{
		if (!Game::config.discord.enabled)
		{
			pDLogger->log(Logger::Level::DEBUG, "Discord RPC/IPC is disabled.");
			return 0;
		}
#ifdef HASILWGDF_DISCORDRPC_SUPPORTED
#if HASILWGDF_PLATFORM == PLATFORM_WINDOWS
		discordRPC = createDiscordWin32(Game::config.discord.clientId);
#elif HASILWGDF_PLATFORM == PLATFORM_MACOS
		discordRPC = createDiscordUnix(Game::config.discord.clientId);
#elif HASILWGDF_PLATFORM == PLATFORM_LINUX
		discordRPC = createDiscordUnix(Game::config.discord.clientId);
#endif

		if (!discordRPC->init())
		{
			pDLogger->log(Logger::Level::ERR,
						  "Unable to initialize Discord RPC/IPC.");
			return -1;
		}

		while (gameRunning)
		{
			lock.lock();

			if (activity != nullptr)
			{
				discordRPC->setActivity(activity);
			}
			else
			{
				discordRPC->setActivity(nullptr);
			}

			lock.unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(32));
		}

		discordRPC->destroy();
#else
		pDLogger->log(Logger::Level::WARN, "Discord RPC/IPC is not supported on this platform.");
#endif

		return 0;
	}

	int _Game_::run(std::unique_ptr<Discord::Activity> &activity,
					void (*initialize)(), void (*preUpdate)(float), void (*update)(float),
					void (*postUpdate)(float), void (*destroy)())
	{
		std::mutex gameRunningMutex;

		{
			std::unique_lock<std::mutex> lock(gameRunningMutex);
			if (gameRunning)
			{
				pLogger->log(Logger::Level::ERR, "The game is already running.");
				return -1;
			}
			gameRunning = true;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			pLogger->log(Logger::Level::ERR, "Unable to initialize SDL.");
			return -1;
		}

		SDL_Event event;

		std::thread loopThread([&]()
							   {
		std::unique_lock<std::mutex> lock(gameRunningMutex);
		loop(event, lock, initialize, preUpdate, update, postUpdate, destroy); });

		std::thread discordThread([&]()
								  {
		std::unique_lock<std::mutex> lock(gameRunningMutex);
		discord(activity, lock); });

		while (gameRunning)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					{
						std::unique_lock<std::mutex> lock(gameRunningMutex);
						gameRunning = false;
					}
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

		{
			std::unique_lock<std::mutex> lock(gameRunningMutex);
			gameRunning = false;
		}

		return 0;
	}

	extern "C" HASILWGDF_EXPORT int Game::run()
	{
		running = true;

		void (*initialize)() = []()
		{
			Game::initialize();
		};
		void (*preUpdate)(float) = [](float delta)
		{
			Game::preUpdate(delta);
		};
		void (*update)(float) = [](float delta)
		{
			Game::update(delta);
		};
		void (*postUpdate)(float) = [](float delta)
		{
			Game::postUpdate(delta);
		};
		void (*destroy)() = []()
		{
			Game::destroy();
		};

		int exitCode = _Game_::instance()->run(Discord::currentActivity, initialize,
											   preUpdate, update, postUpdate, destroy);

		running = false;
		_Game_::release();

		return exitCode != 0 ? -1 : 0;
	}
}
