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

#include "../hpp/Discord.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#ifdef UNIX
namespace Hasibix::HasiLWGDF::Core {
class DiscordUnix: public _Discord_ {
public:
	DiscordUnix(const std::string &clientId) :
			_Discord_(), clientId(clientId) {
	}

	~DiscordUnix() override;

	bool init() override;
	void setActivity(const std::unique_ptr<Discord::Activity> &activity)
			override;
	void destroy() override;

private:
	bool connect();
	void disconnect();
	bool sendData(const std::string &data);

private:
	static const char *SOCKET_PATH;
	int socketDescriptor = -1;
	std::string clientId;
};

const char *DiscordUnix::SOCKET_PATH = "/tmp/discord_rpc_socket";

DiscordUnix::~DiscordUnix() {
	destroy();
}

bool DiscordUnix::init() {
	if (!connect()) {
		std::cout << "Failed to connect to Discord IPC." << std::endl;
		return false;
	}
	auto authData = std::make_unique<JSONObject>(JSONObject());
	authData->values.insert(
			std::make_pair<const std::string, JSONValue*>("v",
					new JSONNumber(1)));
	authData->values.insert(
			std::make_pair<const std::string, JSONValue*>("client_id",
					new JSONString(clientId)));

	if (!sendData(authData->serialize())) {
		std::cout << "Failed to authenticate with Discord." << std::endl;
		disconnect();
		return false;
	}

	return true;
}

void DiscordUnix::setActivity(
		const std::unique_ptr<Discord::Activity> &activity) {
	auto presenceData = std::make_unique<JSONObject>(JSONObject());
	presenceData->values.insert(
			std::make_pair<const std::string, JSONValue*>("cmd",
					new JSONString("SET_ACTIVITY")));

	auto args = new JSONObject;
	args->values.insert(
			std::make_pair<const std::string, JSONValue*>("pid",
					new JSONString(std::to_string(GetCurrentProcessId()))));

	presenceData->values.insert(
			std::make_pair<const std::string, JSONValue*>("args", args));
	presenceData->values.insert(
			std::make_pair<const std::string, JSONValue*>("activity",
					mapActivityToJson(activity)));

	sendData(presenceData->serialize());
}

void DiscordUnix::destroy() {
	disconnect();
}

bool DiscordUnix::connect() {
	socketDescriptor = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (socketDescriptor == -1) {
		return false;
	}

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path));

	if (bind(socketDescriptor, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
		close(socketDescriptor);
		socketDescriptor = -1;
		return false;
	}

	return true;
}

void DiscordUnix::disconnect() {
	if (socketDescriptor != -1) {
		close(socketDescriptor);
		socketDescriptor = -1;
		unlink(SOCKET_PATH);
	}
}

bool DiscordUnix::sendData(const std::string &data) {
	sendto(socketDescriptor, data.c_str(), data.size(), 0, nullptr, 0);
	return true;
}

std::unique_ptr<_Discord_> createDiscordUnix(const std::string clientId) {
	return std::make_unique<_Discord_>(DiscordUnix { clientId });
}
}

