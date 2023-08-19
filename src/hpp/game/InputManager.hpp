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

#include <hasilwgdf/game/InputManager.h>
#include <SDL_stdinc.h>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Game
{
    class _InputManager_ final
    {
    private:
        static _InputManager_ *pInstance;

        Uint8 *pPrevKeyboardState;
        const Uint8 *pKeyboardState;
        int keyLength;

        Uint32 prevMouseState;
        Uint32 mouseState;

        int mousePosX;
        int mousePosY;

        _InputManager_();
        ~_InputManager_();

    public:
        static _InputManager_ *getInstance();
        static void Release();

        bool getKeyDown(InputManager::KeyCode key);
        bool getKeyPressed(InputManager::KeyCode key);
        bool getKeyReleased(InputManager::KeyCode key);

        bool getMouseDown(InputManager::MouseBtn btn);
        bool getMousePressed(InputManager::MouseBtn btn);
        bool getMouseReleased(InputManager::MouseBtn btn);
        Math::Vector2 getMousePos();

        bool getJoystickDown(InputManager::JoystickBtn btn);
        bool getJoystickPressed(InputManager::JoystickBtn btn);
        bool getJoystickReleased(InputManager::JoystickBtn btn);
        bool getJoystickAxis(InputManager::JoystickAxis axis);

        void update();
        void updatePrev();
    };
}
