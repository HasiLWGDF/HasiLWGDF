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

#include "../hpp/input/Mouse.hpp"

namespace Hasibix::HasiLWGDF::Core::Input
{
    std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("Input.Mouse"));
    _Mouse_ *_Mouse_::pInstance = new _Mouse_();

    _Mouse_::_Mouse_()
    {
    }

    _Mouse_::~_Mouse_()
    {
    }

    _Mouse_ *_Mouse_::instance()
    {
        return pInstance;
    }

    void _Mouse_::release()
    {
        delete pInstance;
        pInstance = nullptr;
    }

    bool _Mouse_::getMouseDown(Mouse::MouseBtn btn)
    {
        Uint32 mask = 0;

        switch (btn)
        {
        case Mouse::MouseBtn::H_MB_LEFT:
            mask = SDL_BUTTON_LMASK;
            break;
        case Mouse::MouseBtn::H_MB_MIDDLE:
            mask = SDL_BUTTON_MMASK;
            break;
        case Mouse::MouseBtn::H_MB_RIGHT:
            mask = SDL_BUTTON_RMASK;
            break;
        case Mouse::MouseBtn::H_MB_BACK:
            mask = SDL_BUTTON_X1MASK;
            break;
        case Mouse::MouseBtn::H_MB_FORWARD:
            mask = SDL_BUTTON_X2MASK;
            break;
        };

        return (mouseState & mask);
    }

    bool _Mouse_::getMousePressed(Mouse::MouseBtn btn)
    {
        Uint32 mask = 0;

        switch (btn)
        {
        case Mouse::MouseBtn::H_MB_LEFT:
            mask = SDL_BUTTON_LMASK;
            break;
        case Mouse::MouseBtn::H_MB_MIDDLE:
            mask = SDL_BUTTON_MMASK;
            break;
        case Mouse::MouseBtn::H_MB_RIGHT:
            mask = SDL_BUTTON_RMASK;
            break;
        case Mouse::MouseBtn::H_MB_BACK:
            mask = SDL_BUTTON_X1MASK;
            break;
        case Mouse::MouseBtn::H_MB_FORWARD:
            mask = SDL_BUTTON_X2MASK;
            break;
        };

        return !(prevMouseState & mask) && (mouseState & mask);
    }

    bool _Mouse_::getMouseReleased(Mouse::MouseBtn btn)
    {
        Uint32 mask = 0;

        switch (btn)
        {
        case Mouse::MouseBtn::H_MB_LEFT:
            mask = SDL_BUTTON_LMASK;
            break;
        case Mouse::MouseBtn::H_MB_MIDDLE:
            mask = SDL_BUTTON_MMASK;
            break;
        case Mouse::MouseBtn::H_MB_RIGHT:
            mask = SDL_BUTTON_RMASK;
            break;
        case Mouse::MouseBtn::H_MB_BACK:
            mask = SDL_BUTTON_X1MASK;
            break;
        case Mouse::MouseBtn::H_MB_FORWARD:
            mask = SDL_BUTTON_X2MASK;
            break;
        };

        return (prevMouseState & mask) && !(mouseState & mask);
    }

    Math::Vector2 _Mouse_::getMousePos()
    {
        return {(float)mousePosX, (float)mousePosY};
    }

    void _Mouse_::update()
    {
        mouseState = SDL_GetMouseState(&mousePosX, &mousePosY);
    }

    void _Mouse_::updatePrev()
    {
        prevMouseState = mouseState;
    }

    extern "C" HASILWGDF_EXPORT bool Mouse::getMouseDown(MouseBtn btn)
    {
        return _Mouse_::instance()->getMouseDown(btn);
    }

    extern "C" HASILWGDF_EXPORT bool Mouse::getMousePressed(MouseBtn btn)
    {
        return _Mouse_::instance()->getMousePressed(btn);
    }

    extern "C" HASILWGDF_EXPORT bool Mouse::getMouseReleased(MouseBtn btn)
    {
        return _Mouse_::instance()->getMouseReleased(btn);
    }

    extern "C" HASILWGDF_EXPORT Math::Vector2 Mouse::getMousePos()
    {
        return _Mouse_::instance()->getMousePos();
    }
}
