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

#pragma once

#include "../Core.h"

namespace Hasibix::HasiLWGDF::Core::Render
{
	enum GraphicsAPI
	{
		Software,
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
		OpenGL32,
		OpenGL33,
		OpenGL40,
		OpenGL41,
		OpenGL42,
		OpenGL43,
		OpenGL44,
		OpenGL45,
		OpenGL46,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES)
		OpenGLES20,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_PSGL)
		PSGL,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNM)
		GNM,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_GNMX)
		GNMX,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
		DirectX9,
		DirectX11,
		DirectX12,
#endif
#if !defined(HASILWGDF_GRAPHICS_API_SUPPORTED_METAL)
		Metal,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_VULKAN)
		Vulkan10,
		Vulkan11,
		Vulkan12,
		Vulkan13,
#endif
	};
}
