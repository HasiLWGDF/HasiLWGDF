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

#pragma once

#include "hasilwgdf/Game.hpp"
#include "hasilwgdf/graphics/Backend.hpp"
#include "hasilwgdf/utils/Export.hpp"
#include "hasilwgdf/utils/Logger.hpp"
#include <atomic>
#include <memory>
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_quit.h"
#include "SDL_video.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Graphics {
class Renderer {
protected:
	SDL_Window *pWindow = nullptr;

public:
	explicit Renderer() {
	}
	virtual ~Renderer() = default;
	virtual int init() = 0;
	virtual int render(float alpha) = 0;
	virtual int destroy() = 0;

	virtual SDL_Window*& getWindow() final {
		return pWindow;
	}
};

std::unique_ptr<Renderer> createRenderer();
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
std::unique_ptr<Renderer> createOGLRenderer();
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES
    std::unique_ptr<Renderer> createOGLESRenderer();
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
std::unique_ptr<Renderer> createDX9Renderer();
#endif

std::unique_ptr<Renderer>& getRenderer() {
	std::unique_ptr<Renderer> renderer = nullptr;
	switch (Game::config.graphics.api) {
	case Graphics::Backend::SOFT:
		renderer = createRenderer();
		break;
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL
	case Graphics::Backend::OGL_32 | Graphics::Backend::OGL_33
			| Graphics::Backend::OGL_40 | Graphics::Backend::OGL_41
			| Graphics::Backend::OGL_42 | Graphics::Backend::OGL_43
			| Graphics::Backend::OGL_44 | Graphics::Backend::OGL_45
			| Graphics::Backend::OGL_46:
		renderer = createOGLRenderer();
		break;
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGLES
        case Graphics::Backend::OGLES_20:
            renderer = createOGLESRenderer(pInstance);
            break;
#endif
#ifdef HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX
	case Graphics::Backend::DX_9:
		renderer = createDX9Renderer();
		break;
#endif
	default:
		renderer = nullptr;
		break;
	}
	;
	if (!renderer) {
		std::make_unique<Logger>(Logger("Renderer"))->log(Logger::Level::FATAL,
				"Failed to initialize renderer.");
	}
	return std::ref(renderer);
}
}
