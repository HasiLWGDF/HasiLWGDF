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

#include <chrono>
#include "hasilwgdf/Core.hpp"

namespace Hasibix::HasiLWGDF::Core::Math {
class Timer final {
private:
	std::chrono::high_resolution_clock::time_point lastTime =
			std::chrono::high_resolution_clock::now();
	float deltaTime;
	int fps;
	int fpsCounter;

public:
	Timer() {
	}
	void update();
	float getDeltaTime();
	int getFps();
	float getTime();
};
}
