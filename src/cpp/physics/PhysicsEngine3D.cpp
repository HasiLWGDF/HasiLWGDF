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

#include <physics/PhysicsEngine.hpp>
#include <reactphysics3d/reactphysics3d.h>

namespace Hasibix::HasiLWGDF::Core::Physics
{
    const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("PhysicsEngine3D"));
    class PhysicsEngine3D final : public PhysicsEngine
    {
    private:
        bool isInitialized = false;

    public:
        PhysicsEngine3D() : PhysicsEngine()
        {
        }

        int init() override
        {
            if (isInitialized)
            {
                pLogger->log(Logger::Level::ERR, "Engine is already initialized. Please de-initialize it first!");
                return -1;
            }
            this->isInitialized = true;
            return 0;
        }

        int update() override
        {
            if (!isInitialized)
            {
                pLogger->log(Logger::Level::ERR, "Engine is not initialized yet.");
                return -1;
            }
            return 0;
        }

        int deinit() override
        {
            if (!isInitialized)
            {
                pLogger->log(Logger::Level::ERR, "Engine is not initialized yet.");
                return -1;
            }
            this->isInitialized = false;
            return 0;
        }
    };

    std::unique_ptr<PhysicsEngine> createPhysicsEngine3D()
    {
        return std::make_unique<PhysicsEngine3D>(PhysicsEngine3D{});
    }
}
