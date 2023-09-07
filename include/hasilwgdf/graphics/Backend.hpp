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

#include "../utils/Export.hpp"

namespace Hasibix::HasiLWGDF::Core::Graphics
{
	enum Backend
	{
		SOFT = 0,
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL)
		OGL_32,
		OGL_33,
		OGL_40,
		OGL_41,
		OGL_42,
		OGL_43,
		OGL_44,
		OGL_45,
		OGL_46,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_OPENGL_ES)
		OGLES_20,
#endif
#if defined(HASILWGDF_GRAPHICS_API_SUPPORTED_DIRECTX)
		DX_9,
#endif
	};
}
