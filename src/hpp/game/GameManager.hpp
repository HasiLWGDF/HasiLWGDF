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
#include <hasilwgdf/Core.h>
#include <math/Timer.hpp>

namespace Hasibix::HasiLWGDF::Core::Game
{
    class _GameManager_ final
    {
    private:
        static _GameManager_ *pInstance;

        std::atomic_bool gameRunning = false;
        std::unique_ptr<Math::Timer> timer{};

        _GameManager_()
        {
        }

        int earlyUpdate(float delta);
        int update(float delta);
        int lateUpdate(float delta);

        int loop();
        int discord();

    public:
        static _GameManager_ *getInstance();

        int run(int currentScene);
    };
}
