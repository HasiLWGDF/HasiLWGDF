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

#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES
#include "SDL_opengles2.h"

namespace Hasibix::HasiLWGDF::Core::Graphics
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("OGLESRenderer"));
	class OGLESRenderer final : public Renderer
	{
	private:
		std::unique_ptr<SDL_GLContext> pCtx;
		bool isInitialized = false;

	public:
		OGLESRenderer() : Renderer()
		{
		}

		int init() override
		{
			if (isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is already initialized. Please destroy it first!");
				return -1;
			}
			pWindow = SDL_CreateWindow(
				"",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				100,
				100,
				SDL_WINDOW_RESIZABLE |
					SDL_WINDOW_SHOWN |
					SDL_WINDOW_OPENGL);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			pCtx = std::make_unique<SDL_GLContext>(SDL_GL_CreateContext(pWindow));
			if (Hasibix::HasiLWGDF::Core::Game::config.graphics.vsync)
			{
				SDL_GL_SetSwapInterval(1);
			}
			else
			{
				SDL_GL_SetSwapInterval(0);
			}
			isInitialized = true;
			return 0;
		}

		int render(float alpha) override
		{
			if (!isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is not initialized yet.");
				return -1;
			}
			glClearColor(70.0F / 255.0F, 46.0F / 255.0F, 151.0F / 255.0F, 1.0F);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(pWindow);
			SDL_Delay(4);
			return 0;
		}

		int destroy() override
		{
			if (!isInitialized)
			{
				pLogger->log(Logger::Level::ERR, "Renderer is not initialized yet.");
				return -1;
			}
			SDL_GL_DeleteContext(&pCtx);
			SDL_DestroyWindow(pWindow);
			isInitialized = false;
			return 0;
		}
	};

	std::unique_ptr<Renderer> createOGLESRenderer()
	{
		return std::make_unique<OGLESRenderer>(OGLESRenderer{});
	}
}
#endif
