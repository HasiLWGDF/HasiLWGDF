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

#include <iostream>
#include "Item.hpp"
#include "math/Transform.hpp"
#include <memory>
#include <string>
#include "utils/Holder.hpp"
#include <vector>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core {
class Game;
class Group final {
private:
	std::string name;
	std::vector<Holder<Item>> items;

	void initialize() {
		for (Holder<Item> item : items) {
			item.get()->initialize();
		}
	}

	void earlyUpdate(float delta) {
		for (Holder<Item> item : items) {
			item.get()->earlyUpdate(delta);
		}
	}

	void update(float delta) {
		for (Holder<Item> item : items) {
			item.get()->update(delta);
		}
	}

	void lateUpdate(float delta) {
		for (Holder<Item> item : items) {
			item.get()->lateUpdate(delta);
		}
	}

	void destroy() {
		for (Holder<Item> item : items) {
			item.get()->destroy();
		}
	}

	friend class Game;

public:
	Group(std::string name = "New Group") :
			name(name) {
	}

	~Group() {
		items.clear();
		items.shrink_to_fit();
	}

	int attachItems(Holder<Item> item ...) {
		items.emplace_back(item);
		return 0;
	}
};
}
