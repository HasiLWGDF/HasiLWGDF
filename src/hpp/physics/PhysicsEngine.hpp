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

#include <hasilwgdf/Core.h>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Physics
{
    class PhysicsEngine
    {
    public:
        explicit PhysicsEngine()
        {
        }
        virtual ~PhysicsEngine() = default;
        virtual int init() = 0;
        virtual int update() = 0;
        virtual int deinit() = 0;
    };

    std::unique_ptr<PhysicsEngine> createPhysicsEngine2D();
    std::unique_ptr<PhysicsEngine> createPhysicsEngine3D();
}
