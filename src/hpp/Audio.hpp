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

#include "AL/al.h"
#include "AL/alc.h"
#include "hasilwgdf/math/Vector3.hpp"
#include "hasilwgdf/utils/Logger.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core {
struct Listener {
	Math::Vector3 position;
	int volume;
};

struct SourceCreateInfo {
	Math::Vector3 position;
	int volume;
	int pitch;
	bool repeat;
	float radius;
	const unsigned char *data;
};

struct Source {
public:
	Source(const SourceCreateInfo createInfo) :
			position(createInfo.position), volume(createInfo.volume), pitch(
					createInfo.pitch), repeat(createInfo.repeat), radius(
					createInfo.radius), data(createInfo.data) {
	}

	Math::Vector3 position;
	int volume;
	int pitch;
	bool repeat;
	float radius;
	const unsigned char *data;
	ALuint buffer;
	ALuint sourceId;
};

class _Audio_ {
private:
	static _Audio_ *pInstance;

	ALCdevice *pDevice = nullptr;
	ALCcontext *pContext = nullptr;
	std::map<int, Source*> sources;

	bool isInitialized = false;

	_Audio_();
	~_Audio_();

public:
	static _Audio_* instance();
	static void release();

	int init();
	int destroy();
	int attach(const SourceCreateInfo createInfo);
	Source* getSource(int sourceId);
	int play(int sourceId);
	int stop(int sourceId);
	int stopAll();
};
}
