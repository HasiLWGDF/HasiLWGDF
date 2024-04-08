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
#include "box2d/box2d.h"

namespace Hasibix::HasiLWGDF::Core
{
	const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("PhysicsWorld2D"));
	class PhysicsWorld2D final : public PhysicsWorld
	{
	private:
		std::map<int, b2Body *> bodies;
		std::map<int, b2Joint *> joints;
		b2World *world;

		bool isInitialized = false;

	public:
		PhysicsWorld2D() : PhysicsWorld(), world(
											   new b2World(
												   b2Vec2{Game::config.physics.physics2D.gravity.x,
														  Game::config.physics.physics2D.gravity.y}))
		{
		}

		int init() override
		{
			if (isInitialized)
			{
				pLogger->log(Logger::Level::ERR,
							 "PhysicsWorld is already initialized. Please destroy it first!");
				return -1;
			}
			isInitialized = true;
			return 0;
		}

		void createBody(const Modules::BodyDef &bodyDef)
		{
			b2BodyDef d;
			bodies.insert(
				std::make_pair<int, b2Body *>(bodies.size(),
											  world->CreateBody(&d)));
		}

		void createJoint(const Modules::JointDef &jointDef)
		{
			b2JointDef d;
			joints.insert(
				std::make_pair<int, b2Joint *>(bodies.size(),
											   world->CreateJoint(&d)));
		}

		void destroyBody(int id)
		{
			for (std::pair<int, b2Body *> pair : bodies)
			{
				if (pair.first == id)
				{
					world->DestroyBody(pair.second);
					bodies.erase(id);
					break;
				}
			}
		}

		void destroyJoint(int id)
		{
			for (std::pair<int, b2Joint *> pair : joints)
			{
				if (pair.first == id)
				{
					world->DestroyJoint(pair.second);
					joints.erase(id);
					break;
				}
			}
		}

		int update(float delta) override
		{
			if (!isInitialized)
			{
				pLogger->log(Logger::Level::ERR,
							 "PhysicsWorld is not initialized yet.");
				return -1;
			}
			world->Step(delta, Game::config.physics.physics2D.velocityIterations,
						Game::config.physics.physics2D.positionIterations);
			return 0;
		}

		int destroy() override
		{
			if (!isInitialized)
			{
				pLogger->log(Logger::Level::ERR,
							 "PhysicsWorld is not initialized yet.");
				return -1;
			}
			isInitialized = false;
			return 0;
		}
	};

	std::unique_ptr<PhysicsWorld> createPhysicsWorld2D()
	{
		return std::make_unique<PhysicsWorld2D>(PhysicsWorld2D{});
	}
}
