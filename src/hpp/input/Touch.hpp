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

#include <memory>
#include "hasilwgdf/input/Touch.hpp"
#include "hasilwgdf/utils/Export.hpp"
#include "hasilwgdf/utils/Logger.hpp"
#include "SDL_events.h"
#include "SDL_stdinc.h"
#include "SDL_touch.h"

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Input
{
	class _Touch_ final
	{
	private:
		static _Touch_ *pInstance;

		struct TouchState final
		{
			int posX;
			int posY;
			int device;
			int finger;
			bool isTouchDown;
		};

		TouchState *pPrevTouchState = nullptr;
		TouchState *pTouchState = nullptr;
		int numTouchStates = 0;

		_Touch_();
		~_Touch_();

	public:
		static _Touch_ *instance();
		static void release();

		bool getTouchDown(int device, int finger, int posX, int posY);
		bool getTouchPressed(int device, int finger, int posX, int posY);
		bool getTouchReleased(int device, int finger, int posX, int posY);

		void update(const SDL_Event &event);
		void updatePrev();
	};
}
