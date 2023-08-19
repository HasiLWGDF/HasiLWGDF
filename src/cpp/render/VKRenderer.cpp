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

#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

namespace Hasibix::HasiLWGDF::Core::Render
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("VKRenderer"));
	class VKRenderer final : public Graphics::Renderer
	{
	private:
		bool isInitialized = false;

	public:
		VKRenderer() : Renderer()
		{
		}

		int init() override
		{
			if (this->isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is already initialized. Please de-initialize it first!");
				return -1;
			}
			if (!SDL_Vulkan_LoadLibrary(nullptr))
			{
				pLogger->log(Logger::Level::FATAL, "Unable to load Vulkan library.");
				return -1;
			}
			this->pWindow = SDL_CreateWindow(
				"",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				100,
				100,
				SDL_WINDOW_RESIZABLE |
					SDL_WINDOW_SHOWN |
					SDL_WINDOW_VULKAN);
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
			VkClearColorValue clear_color = {70.0F / 255.0F, 46.0F / 255.0F, 151.0F / 255.0F, 1.0F};
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

	std::unique_ptr<Graphics::Renderer> Graphics::createVKRenderer()
	{
		return std::make_unique<VKRenderer>(VKRenderer{});
	}
}
#endif
