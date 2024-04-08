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

#include "../utils/Export.hpp"

extern "C"
{
	namespace Hasibix::HasiLWGDF::Core::Input
	{
		class Joystick final
		{
		public:
			// Adapted from SDL_GameControllerAxis
			enum JoystickAxis
			{
				H_JA_LHORIZONTAL = 0,
				H_JA_LVERTICH_CAL,
				H_JA_RHORIZONTAL,
				H_JA_RVERTICH_CAL,
				H_JA_LTRIGGER,
				H_JA_RTRIGGER,
				H_JA_COUNT,
			};

			// Adapted from SDL_GameControllerButton
			enum JoystickBtn
			{
				H_JB_A = 0,
				H_JB_B,
				H_JB_X,
				H_JB_Y,
				H_JB_BACK,
				H_JB_GUIDE,
				H_JB_START,
				H_JB_LS,
				H_JB_RS,
				H_JB_LB,
				H_JB_RB,
				H_JB_DPAD_UP,
				H_JB_DPAD_DOWN,
				H_JB_DPAD_LEFT,
				H_JB_DPAD_RIGHT,
				H_JB_MISC1,	   /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
				H_JB_PADDLE1,  /* Xbox Elite paddle P1 */
				H_JB_PADDLE2,  /* Xbox Elite paddle P3 */
				H_JB_PADDLE3,  /* Xbox Elite paddle P2 */
				H_JB_PADDLE4,  /* Xbox Elite paddle P4 */
				H_JB_TOUCHPAD, /* PS4/PS5 touchpad button */
				H_JB_COUNT,
			};

		private:
			Joystick() = delete;

		public:
			HASILWGDF_EXPORT static bool getJoystickDown(int joystick, JoystickBtn btn);
			HASILWGDF_EXPORT static bool getJoystickPressed(int joystick,
															JoystickBtn btn);
			HASILWGDF_EXPORT static bool getJoystickReleased(int joystick,
															 JoystickBtn btn);
			HASILWGDF_EXPORT static float getJoystickAxis(int joystick,
														  JoystickAxis axis);
		};
	}
}
