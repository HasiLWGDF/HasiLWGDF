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

#include <hasilwgdf/Core.h>
#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <AL/alc.h>
#include "../utils/Logger.h"
#include <map>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core::Game
{
    const std::unique_ptr<Logger> pLogger = std::make_unique<Logger>(Logger("AudioPlayer"));
    class AudioManager final
    {
    private:
        static AudioManager *pInstance;

        ALCdevice *pDevice = nullptr;
        ALCcontext *pCtx = nullptr;
        std::vector<ALuint> buffers;
        std::map<int, ALuint> sources;

        bool isInitialized = false;

    public:
        static AudioManager *getInstance()
        {
            if (!pInstance)
            {
                pInstance = new AudioManager();
            }

            return pInstance;
        }
        static void Release()
        {
            if (!pInstance)
            {
                return;
            }

            delete pInstance;
            pInstance = nullptr;
        }

        int init()
        {
            if (this->isInitialized)
            {
                pLogger->log(Logger::Level::ERR, "AudioManager is already initialized!");
                return -1;
            }
            this->pDevice = alcOpenDevice(NULL);
            if (!this->pDevice)
            {
                pLogger->log(Logger::Level::ERR, "Failed to open audio device.");
                return -1;
            }

            this->pCtx = alcCreateContext(this->pDevice, NULL);
            if (!this->pCtx)
            {
                pLogger->log(Logger::Level::ERR, "Failed to create audio context.");
                alcCloseDevice(this->pDevice);
                return -1;
            }
            if (!this->pCtx)
            {
                pLogger->log(Logger::Level::ERR, "Failed to make audio context current.");
                alcDestroyContext(this->pCtx);
                alcCloseDevice(this->pDevice);
                return -1;
            }
            this->isInitialized = true;
            return 0;
        }

        void attach(int uid, const unsigned char *&data)
        {
            ALuint buffer;
            alGenBuffers(1, &buffer);
            ALsizei dataSize = sizeof(data);
            ALenum format = AL_FORMAT_MONO16;                    // TODO: Change the format depending on audio data.
            alBufferData(buffer, format, data, dataSize, 44100); // TODO: Implement variable to adjust sample rate.
            this->buffers.emplace_back(buffer);

            ALuint source;
            alGenSources(1, &source);
            alSourcei(source, AL_BUFFER, buffer);
            this->sources.insert(std::make_pair(uid, source));
        }

        int deinit()
        {
            for (const auto &pair : sources)
            {
                alDeleteSources(1, &pair.second);
            }
            sources.clear();
            for (auto it = this->buffers.begin(); it != this->buffers.end(); ++it)
            {
                alDeleteBuffers(1, &*it);
                this->buffers.erase(it);
            }
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(this->pCtx);
            alcCloseDevice(this->pDevice);
            this->isInitialized = false;
        }
    };

    extern "C" HASILWGDF_EXPORT void Components::AudioPlayer::onInitialize()
    {
        AudioManager::getInstance()->attach(this->identifier, *this->pSource->getData());
    }
}
