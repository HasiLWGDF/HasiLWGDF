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

#pragma once

#include "../Module.hpp"
#include "../math/Vector2.hpp"

namespace Hasibix::HasiLWGDF::Core::Modules
{
	enum JointType
	{
		JT_STATIC = 0,
		JT_KINEMATIC,
		JT_DYNAMIC,
	};

	struct JointDef
	{
		JointType type;
		Math::Vector2 linearVelocity;
		float angularVelocity;
		float linearDamping;
		float angularDamping;
		bool allowSleep;
		bool awake;
		bool fixedRotation;
		bool bullet;
		bool enabled;
		float gravityScale;
	};

	class Joint2D final : public Core::Module
	{
	};

	class Joint3D final : public Core::Module
	{
	};
}
