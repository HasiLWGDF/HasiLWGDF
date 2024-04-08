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

#include <algorithm>
#include <memory>
#include "hasilwgdf/input/Joystick.hpp"
#include "hasilwgdf/math/Vector2.hpp"
#include "hasilwgdf/utils/Export.hpp"
#include "hasilwgdf/utils/Logger.hpp"
#include "SDL_events.h"
#include "SDL_gamecontroller.h"
#include "SDL_stdinc.h"
#include <unordered_map>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Input
{
	class _Joystick_ final
	{
	private:
		struct Controller
		{
			int index = -1;
			SDL_GameController *gc = nullptr;

			std::array<bool, (int)Joystick::JoystickBtn::H_JB_COUNT> buttons;
			std::array<bool, (int)Joystick::JoystickBtn::H_JB_COUNT> lastButtons;
			std::array<float, (int)Joystick::JoystickAxis::H_JA_COUNT> axes;
			std::array<float, (int)Joystick::JoystickAxis::H_JA_COUNT> lastAxes;
		};

		static _Joystick_ *pInstance;

		std::unordered_map<int, std::unique_ptr<Controller>> availableJoysticks{};
		float deadzone = 0.2F;

		_Joystick_();
		~_Joystick_();

		int getNextFreeIndex();

	public:
		static _Joystick_ *instance();
		static void release();

		void onJoystickConnected(SDL_ControllerDeviceEvent &e);
		void onJoystickDisconnected(SDL_ControllerDeviceEvent &e);
		void shutdown();

		bool isJoystickAvailable(int joystick);

		bool getJoystickDown(int joystick, Joystick::JoystickBtn btn);
		bool getJoystickPressed(int joystick, Joystick::JoystickBtn button);
		bool getJoystickReleased(int joystick, Joystick::JoystickBtn button);
		float getJoystickAxis(int joystick, Joystick::JoystickAxis axis);

		void update();
		void updatePrev();
	};
}
