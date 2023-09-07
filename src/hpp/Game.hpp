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

#include <atomic>
#include "../hpp/Discord.hpp"
#include "hasilwgdf/Core.hpp"
#include "../hpp/math/Timer.hpp"
#include <mutex>
#include <SDL_events.h>

namespace Hasibix::HasiLWGDF::Core
{
    class _Game_ final
    {
    private:
        static _Game_ *pInstance;

        std::atomic_bool gameRunning = false;
        std::unique_ptr<Math::Timer> timer{};
        std::unique_ptr<_Discord_> discordRPC = nullptr;

        _Game_()
        {
        }

        int loop(SDL_Event &event, std::unique_lock<std::mutex> &lock, void (*initialize)(), void (*earlyUpdate)(float), void (*update)(float), void (*lateUpdate)(float), void (*destroy)());
        int discord(std::unique_ptr<Discord::Activity> &activity, std::unique_lock<std::mutex> &lock);

    public:
        static _Game_ *instance();
        static void release();

        int run(std::unique_ptr<Discord::Activity> &activity, void (*initialize)(), void (*earlyUpdate)(float), void (*update)(float), void (*lateUpdate)(float), void (*destroy)());
    };
}
