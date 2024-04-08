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

#include "../hpp/Audio.hpp"

namespace Hasibix::HasiLWGDF::Core {
const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(
		Logger("Audio"));
_Audio_ *_Audio_::pInstance = new _Audio_();

_Audio_::_Audio_() {
}

_Audio_::~_Audio_() {
}

int _Audio_::init() {
	if (isInitialized)
		return -1;

	pDevice = alcOpenDevice(nullptr);
	if (!pDevice) {
		return -1;
	}

	pContext = alcCreateContext(pDevice, nullptr);
	if (!pContext) {
		alcCloseDevice(pDevice);
		return -1;
	}

	alcMakeContextCurrent(pContext);
	alListener3f(AL_POSITION, 0.0F, 0.0F, 0.0F);

	isInitialized = true;

	return 0;
}

int _Audio_::destroy() {
	if (!isInitialized)
		return -1;

	stopAll();

	alcDestroyContext(pContext);
	alcCloseDevice(pDevice);

	isInitialized = false;

	return 0;
}

int _Audio_::attach(const SourceCreateInfo createInfo) {
	if (!isInitialized)
		return -1;

	int sourceId = 0;
	for (const auto &pair : sources) {
		sourceId++;
	}
	Source *source = new Source(createInfo);

	ALuint buffer;
	alGenBuffers(1, &buffer);
	ALsizei dataSize = sizeof(createInfo.data);
	ALenum format = AL_FORMAT_MONO16; // TODO: Change the format depending on audio data.
	alBufferData(buffer, format, createInfo.data, dataSize, 44100); // TODO: Implement variable to adjust sample rate.
	source->buffer = buffer;

	ALuint alSource;
	alGenSources(1, &alSource);
	alSourcef(alSource, AL_PITCH, static_cast<float>(source->pitch) / 1000.0F);
	alSourcef(alSource, AL_GAIN, static_cast<float>(source->volume) / 100.0F);
	alSource3f(alSource, AL_POSITION, source->position.x, source->position.y,
			source->position.z);
	if (source->repeat) {
		alSourcei(alSource, AL_LOOPING, AL_TRUE);
	} else {
		alSourcei(alSource, AL_LOOPING, AL_FALSE);
	}
	alSourcei(alSource, AL_BUFFER, buffer);

	sources.insert(std::make_pair(sourceId, source));
	return sourceId;
}

Source* _Audio_::getSource(int sourceId) {
	for (const auto &pair : sources) {
		if (pair.first == sourceId) {
			return pair.second;
		}
	}
	return nullptr;
}

int _Audio_::play(int sourceId) {
	if (!isInitialized)
		return -1;

	for (const auto &pair : sources) {
		if (pair.first != sourceId)
			return -1;
		alSourcePlay(pair.second->sourceId);
	}
	return 0;
}

int _Audio_::stop(int sourceId) {
	if (!isInitialized)
		return -1;

	for (const auto &pair : sources) {
		if (pair.first != sourceId)
			return -1;
		alSourceStop(pair.second->sourceId);
	}
	return 0;
}

int _Audio_::stopAll() {
	if (!isInitialized)
		return -1;

	alSourceStop(0);
	for (const auto &pair : sources) {
		alSourceStop(pair.second->sourceId);
	}
	return 0;
}
}
