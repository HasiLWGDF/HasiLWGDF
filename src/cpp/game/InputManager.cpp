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

#include <InputManager.hpp>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_gamecontroller.h>

namespace Hasibix::HasiLWGDF::Core::Game
{
    std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("InputManager"));
    _InputManager_ *_InputManager_::pInstance = new _InputManager_();

    _InputManager_::_InputManager_()
    {
        pKeyboardState = SDL_GetKeyboardState(&keyLength);
        pPrevKeyboardState = new Uint8[keyLength];
        memcpy(pPrevKeyboardState, pKeyboardState, keyLength);
    }

    _InputManager_::~_InputManager_()
    {
        delete[] pPrevKeyboardState;
        pPrevKeyboardState = nullptr;
    }

    _InputManager_ *_InputManager_::getInstance()
    {
        if (!pInstance)
        {
            pLogger->log(Logger::Level::FATAL, "InputManager is not initialized (HOW IN THE WORLD IS THIS POSSIBLE!??).");
            return nullptr;
        }

        return pInstance;
    }

    void _InputManager_::Release()
    {
        if (!pInstance)
        {
            pLogger->log(Logger::Level::FATAL, "InputManager is not initialized (HOW IN THE WORLD IS THIS POSSIBLE!??).");
            return;
        }

        delete pInstance;
        pInstance = nullptr;
    }

    bool _InputManager_::getKeyDown(InputManager::KeyCode key)
    {
        return this->pKeyboardState[key];
    }

    bool _InputManager_::getKeyPressed(InputManager::KeyCode key)
    {
        return !this->pPrevKeyboardState[key] && this->pKeyboardState[key];
    }

    bool _InputManager_::getKeyReleased(InputManager::KeyCode key)
    {
        return this->pPrevKeyboardState[key] && !this->pKeyboardState[key];
    }

    bool _InputManager_::getMouseDown(InputManager::MouseBtn btn)
    {
        Uint32 mask = 0;

        switch (btn)
        {
        case InputManager::MouseBtn::H_MB_LEFT:
            mask = SDL_BUTTON_LMASK;
            break;
        case InputManager::MouseBtn::H_MB_MIDDLE:
            mask = SDL_BUTTON_MMASK;
            break;
        case InputManager::MouseBtn::H_MB_RIGHT:
            mask = SDL_BUTTON_RMASK;
            break;
        case InputManager::MouseBtn::H_MB_BACK:
            mask = SDL_BUTTON_X1MASK;
            break;
        case InputManager::MouseBtn::H_MB_FORWARD:
            mask = SDL_BUTTON_X2MASK;
            break;
        };

        return (this->mouseState & mask);
    }

    bool _InputManager_::getMousePressed(InputManager::MouseBtn btn)
    {
        Uint32 mask = 0;

        switch (btn)
        {
        case InputManager::MouseBtn::H_MB_LEFT:
            mask = SDL_BUTTON_LMASK;
            break;
        case InputManager::MouseBtn::H_MB_MIDDLE:
            mask = SDL_BUTTON_MMASK;
            break;
        case InputManager::MouseBtn::H_MB_RIGHT:
            mask = SDL_BUTTON_RMASK;
            break;
        case InputManager::MouseBtn::H_MB_BACK:
            mask = SDL_BUTTON_X1MASK;
            break;
        case InputManager::MouseBtn::H_MB_FORWARD:
            mask = SDL_BUTTON_X2MASK;
            break;
        };

        return (this->prevMouseState & mask) && !(this->mouseState & mask);
    }

    bool _InputManager_::getMouseReleased(InputManager::MouseBtn btn)
    {
        Uint32 mask = 0;

        switch (btn)
        {
        case InputManager::MouseBtn::H_MB_LEFT:
            mask = SDL_BUTTON_LMASK;
            break;
        case InputManager::MouseBtn::H_MB_MIDDLE:
            mask = SDL_BUTTON_MMASK;
            break;
        case InputManager::MouseBtn::H_MB_RIGHT:
            mask = SDL_BUTTON_RMASK;
            break;
        case InputManager::MouseBtn::H_MB_BACK:
            mask = SDL_BUTTON_X1MASK;
            break;
        case InputManager::MouseBtn::H_MB_FORWARD:
            mask = SDL_BUTTON_X2MASK;
            break;
        };

        return (this->prevMouseState & mask) && !(this->mouseState & mask);
    }

    Math::Vector2 _InputManager_::getMousePos()
    {
        return {(float)this->mousePosX, (float)this->mousePosY};
    }

    void _InputManager_::update()
    {
        this->mouseState = SDL_GetMouseState(&this->mousePosX, &this->mousePosY);
    }

    void _InputManager_::updatePrev()
    {
        memcpy(this->pPrevKeyboardState, this->pKeyboardState, this->keyLength);
        this->prevMouseState = this->mouseState;
    }

    extern "C" HASILWGDF_EXPORT bool InputManager::getKeyDown(KeyCode key)
    {
        return _InputManager_::getInstance()->getKeyDown(key);
    }

    extern "C" HASILWGDF_EXPORT bool InputManager::getKeyPressed(KeyCode key)
    {
        return _InputManager_::getInstance()->getKeyPressed(key);
    }

    extern "C" HASILWGDF_EXPORT bool InputManager::getKeyReleased(KeyCode key)
    {
        return _InputManager_::getInstance()->getKeyReleased(key);
    }

    extern "C" HASILWGDF_EXPORT bool InputManager::getMouseDown(MouseBtn btn)
    {
        return _InputManager_::getInstance()->getMouseDown(btn);
    }

    extern "C" HASILWGDF_EXPORT bool InputManager::getMousePressed(MouseBtn btn)
    {
        return _InputManager_::getInstance()->getMousePressed(btn);
    }

    extern "C" HASILWGDF_EXPORT bool InputManager::getMouseReleased(MouseBtn btn)
    {
        return _InputManager_::getInstance()->getMouseReleased(btn);
    }

    extern "C" HASILWGDF_EXPORT Math::Vector2 InputManager::getMousePos()
    {
        return _InputManager_::getInstance()->getMousePos();
    }
}
