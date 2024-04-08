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

#include "../hpp/PhysicsWorld.hpp"
#include "reactphysics3d/reactphysics3d.h"

namespace Hasibix::HasiLWGDF::Core {
const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("PhysicsWorld3D"));
class PhysicsWorld3D final : public PhysicsWorld {
private:
	rp3d::PhysicsWorld *world;

	bool isInitialized = false;

public:
	PhysicsWorld3D() :
			PhysicsWorld() {
	}

	int init() override
	{
		if (isInitialized) {
			pLogger->log(Logger::Level::ERR,
					"PhysicsWorld is already initialized. Please destroy it first!");
			return -1;
		}
		isInitialized = true;
		return 0;
	}

	int update(float delta) override
	{
		if (!isInitialized) {
			pLogger->log(Logger::Level::ERR,
					"PhysicsWorld is not initialized yet.");
			return -1;
		}
		world->update(delta);
		return 0;
	}

	int destroy() override
	{
		if (!isInitialized) {
			pLogger->log(Logger::Level::ERR,
					"PhysicsWorld is not initialized yet.");
			return -1;
		}
		isInitialized = false;
		return 0;
	}
};

std::unique_ptr<PhysicsWorld> createPhysicsWorld3D() {
	return std::make_unique<PhysicsWorld3D>(PhysicsWorld3D { });
}
}
