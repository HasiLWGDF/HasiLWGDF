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

#include "../hpp/input/Joystick.hpp"

namespace Hasibix::HasiLWGDF::Core::Input
{
	std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("Input.Joystick"));
	_Joystick_ *_Joystick_::pInstance = new _Joystick_();

	_Joystick_::_Joystick_()
	{
	}

	_Joystick_::~_Joystick_()
	{
	}

	int _Joystick_::getNextFreeIndex()
	{
		int ret = -1;

		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (availableJoysticks.count(i) == 0)
			{
				ret = i;
				break;
			}
		}

		return ret;
	}

	_Joystick_ *_Joystick_::instance()
	{
		return pInstance;
	}

	void _Joystick_::release()
	{
		delete pInstance;
		pInstance = nullptr;
	}

	void _Joystick_::onJoystickConnected(SDL_ControllerDeviceEvent &e)
	{
		int deviceIndex = e.which;
		if (SDL_IsGameController(deviceIndex))
		{
			auto c = std::make_unique<Controller>();
			c->gc = SDL_GameControllerOpen(deviceIndex);
			if (c->gc)
			{
				c->index = deviceIndex;
				std::fill(c->buttons.begin(), c->buttons.end(), false);
				std::fill(c->lastButtons.begin(), c->lastButtons.end(), false);
				std::fill(c->axes.begin(), c->axes.end(), 0.f);
				std::fill(c->lastAxes.begin(), c->lastAxes.end(), 0.f);

				int mapIndex = getNextFreeIndex();
				pLogger->log(Logger::Level::DEBUG,
							 "Joystick connected: mapIndex(%s), deviceIndex(%s)",
							 mapIndex, deviceIndex);
				availableJoysticks[mapIndex] = std::move(c);
			}
			else
			{
				pLogger->log(Logger::Level::ERR,
							 "Error opening game controller with Device Index %s: %s",
							 deviceIndex, SDL_GetError());
			}
		}
	}

	void _Joystick_::onJoystickDisconnected(SDL_ControllerDeviceEvent &e)
	{
		int deviceIndex = e.which;
		for (auto it = availableJoysticks.begin(); it != availableJoysticks.end();
			 it++)
		{
			Controller *c = it->second.get();
			if (c->index == deviceIndex)
			{
				pLogger->log(Logger::Level::DEBUG, "Joystick disconnected: %s",
							 deviceIndex);
				SDL_GameControllerClose(c->gc);
				availableJoysticks.erase(it);
				break;
			}
		}
	}

	void _Joystick_::shutdown()
	{
		for (auto it = availableJoysticks.begin(); it != availableJoysticks.end();)
		{
			Controller *c = it->second.get();
			SDL_GameControllerClose(c->gc);
			it = availableJoysticks.erase(it);
		}
	}

	bool _Joystick_::isJoystickAvailable(int joystick)
	{
		return availableJoysticks.count(joystick) > 0;
	}

	bool _Joystick_::getJoystickDown(int joystick, Joystick::JoystickBtn btn)
	{
		auto it = availableJoysticks.find(joystick);
		if (it != availableJoysticks.end())
		{
			return it->second->buttons[btn];
		}

		pLogger->log(Logger::Level::ERR, "Joystick with id %s is not available!",
					 joystick);
		return false;
	}

	bool _Joystick_::getJoystickPressed(int joystick, Joystick::JoystickBtn btn)
	{
		auto it = availableJoysticks.find(joystick);
		if (it != availableJoysticks.end())
		{
			return it->second->buttons[btn] && !it->second->lastButtons[btn];
		}

		pLogger->log(Logger::Level::ERR, "Joystick with id %s is not available!",
					 joystick);
		return false;
	}

	bool _Joystick_::getJoystickReleased(int joystick, Joystick::JoystickBtn btn)
	{
		auto it = availableJoysticks.find(joystick);
		if (it != availableJoysticks.end())
		{
			return !it->second->buttons[btn] && it->second->lastButtons[btn];
		}

		pLogger->log(Logger::Level::ERR, "Joystick with id %s is not available!",
					 joystick);
		return false;
	}

	float _Joystick_::getJoystickAxis(int joystick, Joystick::JoystickAxis axis)
	{
		auto it = availableJoysticks.find(joystick);
		if (it != availableJoysticks.end())
		{
			float val = it->second->axes[axis];
			return abs(val) > deadzone ? val : 0.0F;
		}

		pLogger->log(Logger::Level::ERR, "Joystick with id %s is not available!",
					 joystick);
		return 0.0F;
	}

	void _Joystick_::update()
	{
		for (auto it = availableJoysticks.begin(); it != availableJoysticks.end();
			 it++)
		{
			Controller *c = it->second.get();
			if (!(c && c->gc))
			{
				pLogger->log(Logger::Level::DEBUG,
							 "Invalid game controller in availableJoysticks map.");
			}
			if (c && c->gc)
			{
				c->lastButtons = c->buttons;
				c->lastAxes = c->axes;

				for (unsigned int i = 0;
					 i < static_cast<int>(Joystick::JoystickBtn::H_JB_COUNT);
					 i++)
				{
					c->buttons[i] = SDL_GameControllerGetButton(c->gc,
																static_cast<SDL_GameControllerButton>(i));
				}

				for (unsigned int i = 0;
					 i < static_cast<int>(Joystick::JoystickAxis::H_JA_COUNT);
					 i++)
				{
					c->axes[i] = std::clamp(
						SDL_GameControllerGetAxis(c->gc,
												  static_cast<SDL_GameControllerAxis>(i)) /
							32767.f,
						-1.f, 1.f);
				}
			}
		}
	}

	void _Joystick_::updatePrev()
	{
		// Unused
	}

	extern "C" HASILWGDF_EXPORT bool Joystick::getJoystickDown(int joystick,
															   JoystickBtn btn)
	{
		return _Joystick_::instance()->getJoystickDown(joystick, btn);
	}

	extern "C" HASILWGDF_EXPORT bool Joystick::getJoystickPressed(int joystick,
																  JoystickBtn btn)
	{
		return _Joystick_::instance()->getJoystickPressed(joystick, btn);
	}

	extern "C" HASILWGDF_EXPORT bool Joystick::getJoystickReleased(int joystick,
																   JoystickBtn btn)
	{
		return _Joystick_::instance()->getJoystickReleased(joystick, btn);
	}

	extern "C" HASILWGDF_EXPORT float Joystick::getJoystickAxis(int joystick,
																JoystickAxis axis)
	{
		return _Joystick_::instance()->getJoystickAxis(joystick, axis);
	}
}
