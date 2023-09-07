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

#include "../hpp/Discord.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Hasibix::HasiLWGDF::Core
{
    class DiscordWin32 : public _Discord_
    {
    public:
        DiscordWin32(const std::string &clientId) : _Discord_(), pipeHandle(INVALID_HANDLE_VALUE), clientId(clientId)
        {
        }

        ~DiscordWin32() override;

        bool init() override;
        void setActivity(const std::unique_ptr<Discord::Activity> &activity) override;
        void destroy() override;

    private:
        bool connect();
        void disconnect();
        bool sendData(const std::string &data);

    private:
        static const std::string PIPE_NAME;
        HANDLE pipeHandle;
        std::string clientId;
    };

    const std::string DiscordWin32::PIPE_NAME = "\\\\.\\pipe\\discord_rpc_pipe";

    DiscordWin32::~DiscordWin32()
    {
        destroy();
    }

    bool DiscordWin32::init()
    {
        if (!connect())
        {
            std::cout << "Failed to connect to Discord IPC." << std::endl;
            return false;
        }
        auto authData = std::make_unique<JSONObject>(JSONObject());
        authData->values.insert(std::make_pair<const std::string, JSONValue *>("v", new JSONNumber(1)));
        authData->values.insert(std::make_pair<const std::string, JSONValue *>("client_id", new JSONString(clientId)));

        if (!sendData(authData->serialize()))
        {
            std::cout << "Failed to authenticate with Discord." << std::endl;
            disconnect();
            return false;
        }

        return true;
    }

    void DiscordWin32::setActivity(const std::unique_ptr<Discord::Activity> &activity)
    {
        auto presenceData = std::make_unique<JSONObject>(JSONObject());
        presenceData->values.insert(std::make_pair<const std::string, JSONValue *>("cmd", new JSONString("SET_ACTIVITY")));

        auto args = new JSONObject;
        args->values.insert(std::make_pair<const std::string, JSONValue *>("pid", new JSONString(std::to_string(GetCurrentProcessId()))));

        presenceData->values.insert(std::make_pair<const std::string, JSONValue *>("args", args));
        presenceData->values.insert(std::make_pair<const std::string, JSONValue *>("activity", mapActivityToJson(activity)));

        sendData(presenceData->serialize());
    }

    void DiscordWin32::destroy()
    {
        disconnect();
    }

    bool DiscordWin32::connect()
    {
        pipeHandle = CreateFileA(PIPE_NAME.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        return pipeHandle != INVALID_HANDLE_VALUE;
    }

    void DiscordWin32::disconnect()
    {
        if (pipeHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(pipeHandle);
            pipeHandle = INVALID_HANDLE_VALUE;
        }
    }

    bool DiscordWin32::sendData(const std::string &data)
    {
        DWORD bytesWritten;
        bool success = WriteFile(pipeHandle, data.c_str(), static_cast<DWORD>(data.size()), &bytesWritten, nullptr) != 0;
        return success;
    }

    std::unique_ptr<_Discord_> createDiscordWin32(const std::string clientId)
    {
        return std::make_unique<_Discord_>(DiscordWin32{clientId});
    }
}
