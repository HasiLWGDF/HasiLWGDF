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

#include "../hpp/input/Touch.hpp"

namespace Hasibix::HasiLWGDF::Core::Input
{
    std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("Input.Touch"));
    _Touch_ *_Touch_::pInstance = new _Touch_();

    _Touch_::_Touch_()
    {
    }

    _Touch_::~_Touch_()
    {
        delete[] pPrevTouchState;
        delete[] pTouchState;
        pPrevTouchState = nullptr;
        pTouchState = nullptr;
    }

    _Touch_ *_Touch_::instance()
    {
        return pInstance;
    }

    void _Touch_::release()
    {
        delete pInstance;
        pInstance = nullptr;
    }

    bool _Touch_::getTouchDown(int device, int finger, int posX, int posY)
    {
        for (int i = 0; i < numTouchStates; i++)
        {
            if (pTouchState[i].device == device && pTouchState[i].finger == finger &&
                pTouchState[i].posX == posX && pTouchState[i].posY == posY && pTouchState[i].isTouchDown)
            {
                return true;
            }
        }
        return false;
    }

    bool _Touch_::getTouchPressed(int device, int finger, int posX, int posY)
    {
        for (int i = 0; i < numTouchStates; i++)
        {
            if (pTouchState[i].device == device && pTouchState[i].finger == finger &&
                pTouchState[i].posX == posX && pTouchState[i].posY == posY && !pPrevTouchState[i].isTouchDown &&
                pTouchState[i].isTouchDown)
            {
                return true;
            }
        }
        return false;
    }

    bool _Touch_::getTouchReleased(int device, int finger, int posX, int posY)
    {
        for (int i = 0; i < numTouchStates; i++)
        {
            if (pTouchState[i].device == device && pTouchState[i].finger == finger &&
                pTouchState[i].posX == posX && pTouchState[i].posY == posY && pPrevTouchState[i].isTouchDown &&
                !pTouchState[i].isTouchDown)
            {
                return true;
            }
        }
        return false;
    }

    void _Touch_::update(const SDL_Event &event)
    {
        if (event.type == SDL_FINGERDOWN)
        {
            numTouchStates++;
            pTouchState = new TouchState[numTouchStates];
            memcpy(pPrevTouchState, pTouchState, (numTouchStates - 1) * sizeof(TouchState));

            TouchState touchState;
            touchState.posX = event.tfinger.x;
            touchState.posY = event.tfinger.y;
            touchState.device = event.tfinger.touchId;
            touchState.finger = event.tfinger.fingerId;
            touchState.isTouchDown = true;
            pTouchState[numTouchStates - 1] = touchState;
        }
        else if (event.type == SDL_FINGERUP)
        {
            for (int i = 0; i < numTouchStates; i++)
            {
                if (pTouchState[i].finger == event.tfinger.fingerId)
                {
                    pTouchState[i].isTouchDown = false;
                    break;
                }
            }
        }
    }

    void _Touch_::updatePrev()
    {
        memcpy(pPrevTouchState, pTouchState, numTouchStates * sizeof(TouchState));
    }

    extern "C" HASILWGDF_EXPORT bool Touch::getTouchDown(int device, int finger, int posX, int posY)
    {
        return _Touch_::instance()->getTouchDown(device, finger, posX, posY);
    }

    extern "C" HASILWGDF_EXPORT bool Touch::getTouchPressed(int device, int finger, int posX, int posY)
    {
        return _Touch_::instance()->getTouchPressed(device, finger, posX, posY);
    }

    extern "C" HASILWGDF_EXPORT bool Touch::getTouchReleased(int device, int finger, int posX, int posY)
    {
        return _Touch_::instance()->getTouchReleased(device, finger, posX, posY);
    }
}
