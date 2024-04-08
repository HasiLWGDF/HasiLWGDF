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

#include "../hpp/graphics/Renderer.hpp"

namespace Hasibix::HasiLWGDF::Core::Graphics
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("Renderer"));
	class SoftwareRenderer final : public Renderer
	{
	private:
		SDL_Renderer *pRenderer = nullptr;
		bool isInitialized = false;

	public:
		SoftwareRenderer() : Renderer()
		{
		}

		int init() override
		{
			if (isInitialized)
			{
				pLogger->log(Logger::Level::ERR,
							 "Renderer is already initialized. Please destroy it first!");
				return -1;
			}
			pWindow = SDL_CreateWindow("",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED, 100, 100,
									   SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
			if (Hasibix::HasiLWGDF::Core::Game::config.graphics.vsync)
			{
				pRenderer = SDL_CreateRenderer(pWindow, -1,
											   SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
			}
			else
			{
				pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_SOFTWARE);
			}
			if (!pWindow || !pRenderer)
			{
				pLogger->log(Logger::Level::ERR, "Unable to initialize renderer.");
				return -1;
			}
			isInitialized = true;
			return 0;
		}

		int render(float alpha) override
		{
			if (!isInitialized || !pRenderer)
			{
				pLogger->log(Logger::Level::ERR,
							 "Renderer is not initialized yet.");
				return -1;
			}
			SDL_SetRenderDrawColor(pRenderer, 70, 46, 151, 255);
			SDL_RenderPresent(pRenderer);
			SDL_Delay(4);
			return 0;
		}

		int destroy() override
		{
			if (!isInitialized || !pRenderer)
			{
				pLogger->log(Logger::Level::ERR,
							 "Renderer is not initialized yet.");
				return -1;
			}
			SDL_DestroyRenderer(pRenderer);
			SDL_DestroyWindow(pWindow);
			isInitialized = false;
			return 0;
		}
	};

	std::unique_ptr<Renderer> createRenderer()
	{
		return std::make_unique<SoftwareRenderer>(SoftwareRenderer{});
	}
}
