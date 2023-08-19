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

#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
namespace Hasibix::HasiLWGDF::Core::Render
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("DX11Renderer"));
	class DX11Renderer final : public Graphics::Renderer
	{
	private:
		SDL_Renderer *pRenderer;
		bool isInitialized = false;

	public:
		DX11Renderer() : Renderer()
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
			if (!this->pWindow)
			{
				pLogger->log(Logger::Level::ERR, "Failed to initialize pWindow.");
				return -1;
			}

			if (Game::GameManager::config.graphics.vsync)
				this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			else
				this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED);
			if (!this->pRenderer)
			{
				SDL_DestroyWindow(this->pWindow);
				pLogger->log(Logger::Level::ERR, "Failed to create SDL renderer.");
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
			SDL_DestroyWindow(this->pWindow);
			this->isInitialized = false;
			return 0;
		}
	};

	std::unique_ptr<Graphics::Renderer> createDX11Renderer()
	{
		return std::make_unique<DX11Renderer>(DX11Renderer{});
	}
}
#endif
