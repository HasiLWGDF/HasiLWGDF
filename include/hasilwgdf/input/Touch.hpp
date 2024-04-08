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

#include "../math/Vector2.hpp"
#include "../utils/Export.hpp"

extern "C" {
namespace Hasibix::HasiLWGDF::Core::Input {
class Touch final {
private:
	Touch() = delete;

public:
	HASILWGDF_EXPORT static bool getTouchDown(int device, int finger, int posX,
			int posY);
	HASILWGDF_EXPORT static bool getTouchPressed(int device, int finger,
			int posX, int posY);
	HASILWGDF_EXPORT static bool getTouchReleased(int device, int finger,
			int posX, int posY);
};
}
}
