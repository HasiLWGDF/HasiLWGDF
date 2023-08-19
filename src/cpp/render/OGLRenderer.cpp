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

#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <GL/gl.h>

namespace Hasibix::HasiLWGDF::Core::Render
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("OGLRenderer"));
	class OGLRenderer final : public Graphics::Renderer
	{
	private:
		std::unique_ptr<SDL_GLContext> pCtx;
		bool isInitialized = false;

	public:
		OGLRenderer() : Renderer()
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
					SDL_WINDOW_SHOWN |
					SDL_WINDOW_OPENGL);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
			switch (Game::GameManager::config.graphics.api)
			{
			case GraphicsAPI::OpenGL32:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
				break;
			case GraphicsAPI::OpenGL33:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
				break;
			case GraphicsAPI::OpenGL40:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
				break;
			case GraphicsAPI::OpenGL41:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
				break;
			case GraphicsAPI::OpenGL42:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
				break;
			case GraphicsAPI::OpenGL43:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
				break;
			case GraphicsAPI::OpenGL44:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
				break;
			case GraphicsAPI::OpenGL45:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
				break;
			case GraphicsAPI::OpenGL46:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
				break;
			}
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			this->pCtx = std::make_unique<SDL_GLContext>(SDL_GL_CreateContext(this->pWindow));
			if (Game::GameManager::config.graphics.vsync)
			{
				SDL_GL_SetSwapInterval(1);
			}
			else
			{
				SDL_GL_SetSwapInterval(0);
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
			glClearColor(70.0F / 255.0F, 46.0F / 255.0F, 151.0F / 255.0F, 1.0F);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(this->pWindow);
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
			SDL_GL_DeleteContext(&this->pCtx);
			SDL_DestroyWindow(this->pWindow);
			this->isInitialized = false;
			return 0;
		}
	};

	std::unique_ptr<Graphics::Renderer> createOGLRenderer()
	{
		return std::make_unique<OGLRenderer>(OGLRenderer{});
	}
}
#endif
