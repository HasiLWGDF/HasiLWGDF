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

#import "Renderer.h"
#import "../utils/Logger.h"

using namespace Hasibix::HasiUtils;

#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_METAL
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

namespace Hasibix::HasiLWGDF::Core::Render
{
    const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("MTLRenderer"));
	class MTLRenderer final : public Renderer
	{
	private:
		SDL_Renderer *pRenderer;
		CAMetalLayer *pLayer;
		bool isInitialized = false;

	public:
		MTLRenderer(std::unique_ptr<Game::Game> &pInstance) : Renderer(pInstance)
		{
		}
		int init() override
		{
			if (!this->isInitialized)
			{
                SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
				this->pWindow = SDL_CreateWindow(
					this->pInstance->getWindow()->title,
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					this->pInstance->getWindow()->width,
					this->pInstance->getWindow()->height,
					SDL_WINDOW_RESIZABLE |
						SDL_WINDOW_SHOWN |
                        SDL_WINDOW_ALLOW_HIGHDPI);
				if (this->pInstance->getConfig()->graphics.vsync)
                {
                    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
					this->pLayer = (__bridge CAMetalLayer *) SDL_RenderGetMetalLayer(pRenderer);
				}
                else
                {
                    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED);
					this->pLayer = (__bridge CAMetalLayer *) SDL_RenderGetMetalLayer(pRenderer);
				}
				this->isInitialized = true;
				return 0;
			}
			else
			{
				pLogger->log(Logger::Level::ERR, "Renderer is already initialized. Please de-initialize it first!");
				return -1;
			}
		}
		int render(float alpha) override
		{
            if (this->isInitialized)
            {
                @autoreleasepool {

                }
				SDL_Delay(4);
				return 0;
            }
            else
            {
                pLogger->log(Logger::Level::ERR, "Renderer is not initialized yet.");
				return -1;
            }
		}
		int deinit() override
		{
			if (this->isInitialized)
			{
				SDL_DestroyRenderer(this->pRenderer);
				SDL_DestroyWindow(this->pWindow);
				SDL_Quit();
				this->isInitialized = false;
				return 0;
			}
			else
			{
				pLogger->log(Logger::Level::ERR, "Renderer is not initialized yet.");
				return -1;
			}
		}
	};

	std::unique_ptr<Renderer> createMTLRenderer(std::unique_ptr<Game::Game> &pInstance)
	{
		return std::make_unique<MTLRenderer>(MTLRenderer{pInstance});
	}
}
#endif
