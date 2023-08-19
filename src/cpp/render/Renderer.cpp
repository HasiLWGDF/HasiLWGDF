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

#include <render/Renderer.hpp>

#include <memory>

namespace Hasibix::HasiLWGDF::Core::Render
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("Renderer"));
	class SoftwareRenderer final : public Graphics::Renderer
	{
	private:
		SDL_Renderer *pRenderer;
		bool isInitialized = false;

	public:
		SoftwareRenderer() : Renderer()
		{
		}

		int init() override
		{
			if (this->isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is already initialized. Please de-initialize it first!");
				return -1;
			}
			this->pWindow = SDL_CreateWindow(
				"",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				100,
				100,
				SDL_WINDOW_RESIZABLE |
					SDL_WINDOW_SHOWN);
			if (Game::GameManager::config.graphics.vsync)
			{
				this->pRenderer = SDL_CreateRenderer(
					this->pWindow,
					-1,
					SDL_RENDERER_SOFTWARE |
						SDL_RENDERER_PRESENTVSYNC);
			}
			else
			{
				this->pRenderer = SDL_CreateRenderer(
					this->pWindow,
					-1,
					SDL_RENDERER_SOFTWARE);
			}
			if (!this->pWindow || !this->pRenderer)
			{
				pLogger->log(Logger::Level::ERR, "Unable to initialize renderer.");
				return -1;
			}
			this->isInitialized = true;
			return 0;
		}

		int render(float alpha) override
		{
			if (!this->isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is not initialized yet.");
				return -1;
			}
			SDL_SetRenderDrawColor(this->pRenderer, 70, 46, 151, 255);
			SDL_RenderPresent(this->pRenderer);
			SDL_Delay(4);
			return 0;
		}

		int deinit() override
		{
			if (!this->isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is not initialized yet.");
				return -1;
			}
			SDL_DestroyRenderer(this->pRenderer);
			SDL_DestroyWindow(this->pWindow);
			this->isInitialized = false;
			return 0;
		}
	};

	std::unique_ptr<Graphics::Renderer> Graphics::createRenderer()
	{
		return std::make_unique<SoftwareRenderer>(SoftwareRenderer{});
	}
}
