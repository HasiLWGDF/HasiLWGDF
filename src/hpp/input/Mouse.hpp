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

#include "hasilwgdf/input/Mouse.hpp"
#include "hasilwgdf/math/Vector2.hpp"
#include "hasilwgdf/utils/Export.hpp"
#include "hasilwgdf/utils/Logger.hpp"
#include <memory>
#include "SDL_mouse.h"
#include "SDL_stdinc.h"

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Input
{
    class _Mouse_ final
    {
    private:
        static _Mouse_ *pInstance;

        Uint32 prevMouseState;
        Uint32 mouseState;

        int mousePosX;
        int mousePosY;

        _Mouse_();
        ~_Mouse_();

    public:
        static _Mouse_ *instance();
        static void release();

        bool getMouseDown(Mouse::MouseBtn btn);
        bool getMousePressed(Mouse::MouseBtn btn);
        bool getMouseReleased(Mouse::MouseBtn btn);
        Math::Vector2 getMousePos();

        void update();
        void updatePrev();
    };
}
