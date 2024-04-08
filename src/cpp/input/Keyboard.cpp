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

#include "../hpp/input/Keyboard.hpp"

namespace Hasibix::HasiLWGDF::Core::Input
{
	std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("Input.Keyboard"));
	_Keyboard_ *_Keyboard_::pInstance = new _Keyboard_();

	_Keyboard_::_Keyboard_()
	{
		pKeyboardState = SDL_GetKeyboardState(&keyLength);
		pPrevKeyboardState = new Uint8[keyLength];
		memcpy(pPrevKeyboardState, pKeyboardState, keyLength);
	}

	_Keyboard_::~_Keyboard_()
	{
		delete[] pPrevKeyboardState;
		pPrevKeyboardState = nullptr;
	}

	_Keyboard_ *_Keyboard_::instance()
	{
		return pInstance;
	}

	void _Keyboard_::release()
	{
		delete pInstance;
		pInstance = nullptr;
	}

	bool _Keyboard_::getKeyDown(Keyboard::KeyCode key)
	{
		return pKeyboardState[key];
	}

	bool _Keyboard_::getKeyPressed(Keyboard::KeyCode key)
	{
		return !pPrevKeyboardState[key] && pKeyboardState[key];
	}

	bool _Keyboard_::getKeyReleased(Keyboard::KeyCode key)
	{
		return pPrevKeyboardState[key] && !pKeyboardState[key];
	}

	float _Keyboard_::getKeyAxis(Keyboard::KeyCode positive,
								 Keyboard::KeyCode negative)
	{
		if (getKeyDown(positive) && !getKeyDown(negative))
		{
			return 1.0F;
		}
		else if (!getKeyDown(positive) && getKeyDown(negative))
		{
			return -1.0F;
		}
		else
		{
			return 0.0F;
		}
	}

	void _Keyboard_::update()
	{
		// Unused
	}

	void _Keyboard_::updatePrev()
	{
		memcpy(pPrevKeyboardState, pKeyboardState, keyLength);
	}

	extern "C" HASILWGDF_EXPORT bool Keyboard::getKeyDown(KeyCode key)
	{
		return _Keyboard_::instance()->getKeyDown(key);
	}

	extern "C" HASILWGDF_EXPORT bool Keyboard::getKeyPressed(KeyCode key)
	{
		return _Keyboard_::instance()->getKeyPressed(key);
	}

	extern "C" HASILWGDF_EXPORT bool Keyboard::getKeyReleased(KeyCode key)
	{
		return _Keyboard_::instance()->getKeyReleased(key);
	}

	extern "C" HASILWGDF_EXPORT float Keyboard::getKeyAxis(KeyCode positive,
														   KeyCode negative)
	{
		return _Keyboard_::instance()->getKeyAxis(positive, negative);
	}
}
