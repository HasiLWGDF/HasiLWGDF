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

#include "Config.hpp"
#include "Group.hpp"
#include <map>
#include <memory>
#include "utils/Export.hpp"
#include "utils/Holder.hpp"

using namespace Hasibix::HasiUtils;

extern "C" {
namespace Hasibix::HasiLWGDF::Core {
class Game final {
private:
	static bool running;
	static int currentGroup;
	static std::map<int, Holder<Group>> groups;
	Game() = delete;

	static void initialize() {
		groups.at(currentGroup).get()->initialize();
	}

	static void earlyUpdate(float delta) {
		groups.at(currentGroup).get()->earlyUpdate(delta);
	}

	static void update(float delta) {
		groups.at(currentGroup).get()->update(delta);
	}

	static void lateUpdate(float delta) {
		groups.at(currentGroup).get()->lateUpdate(delta);
	}

	static void destroy() {
		groups.at(currentGroup).get()->destroy();
	}

public:
	static Config &config;
	static int attachGroup(Holder<Group> group) {
		int id = groups.size();
		groups.insert(std::make_pair(id, group));
		return id;
	}
	static void moveTo(int group) {
		currentGroup = group;
	}
	HASILWGDF_EXPORT static int run();
};
}
}

namespace Hasibix::HasiLWGDF::Core {
int Game::currentGroup = 0;
}
