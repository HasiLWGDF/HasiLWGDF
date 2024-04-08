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

#include "../../hpp/math/Timer.hpp"

namespace Hasibix::HasiLWGDF::Core::Math {
void Timer::update() {
	std::chrono::high_resolution_clock::time_point currentTime =
			std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration tickDifference = lastTime
			- currentTime;
	deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(
			tickDifference).count() * Game::config.timescale;
	lastTime = currentTime;
	fpsCounter++;

	if (currentTime >= lastTime) {
		fps = fpsCounter;
		fpsCounter = 0;
	}
}

float Timer::getDeltaTime() {
	return deltaTime;
}

int Timer::getFps() {
	return fps;
}

float Timer::getTime() {
	return std::chrono::duration_cast<std::chrono::duration<float>>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count()
			/ 1000.0F;
}
}
