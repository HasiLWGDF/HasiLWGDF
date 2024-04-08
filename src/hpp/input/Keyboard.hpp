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

#include "hasilwgdf/input/Keyboard.hpp"
#include "hasilwgdf/utils/Export.hpp"
#include "hasilwgdf/utils/Logger.hpp"
#include <memory>
#include "SDL_keyboard.h"
#include "SDL_stdinc.h"

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Input {
class _Keyboard_ final {
private:
	static _Keyboard_ *pInstance;

	Uint8 *pPrevKeyboardState;
	const Uint8 *pKeyboardState;
	int keyLength;

	_Keyboard_();
	~_Keyboard_();

public:
	static _Keyboard_* instance();
	static void release();

	bool getKeyDown(Keyboard::KeyCode key);
	bool getKeyPressed(Keyboard::KeyCode key);
	bool getKeyReleased(Keyboard::KeyCode key);
	float getKeyAxis(Keyboard::KeyCode positive, Keyboard::KeyCode negative);

	void update();
	void updatePrev();
};
}
