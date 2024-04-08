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

#include "hasilwgdf/Discord.hpp"
#include "hasilwgdf/utils/JSON.hpp"
#include <iostream>
#include <memory>
#include <string>

using namespace Hasibix::HasiUtils::JSON;

namespace Hasibix::HasiLWGDF::Core {
class _Discord_ {
public:
	_Discord_();
	virtual ~_Discord_() = default;

	virtual bool init() {
		return false;
	}

	virtual void setActivity(
			const std::unique_ptr<Discord::Activity> &activity) {
	}

	virtual void destroy() {
	}
};

std::unique_ptr<_Discord_> createDiscordWin32(const std::string clientId);
std::unique_ptr<_Discord_> createDiscordUnix(const std::string clientId);

JSONObject* mapActivityToJson(
		const std::unique_ptr<Discord::Activity> &activity) {
	JSONObject *json = new JSONObject;
	if (activity == nullptr)
		return json;

	if (activity->state && activity->details[0]) {
		JSONString *state = new JSONString(activity->state);
		json->values.insert(
				std::make_pair<const std::string, JSONValue*>("state", state));
	}

	if (activity->details && activity->details[0]) {
		JSONString *details = new JSONString(activity->details);
		json->values.insert(
				std::make_pair<const std::string, JSONValue*>("details",
						details));
	}

	JSONObject *timestamps = new JSONObject;
	timestamps->values.insert(
			std::make_pair<const std::string, JSONValue*>("start",
					new JSONNumber(activity->timestamps.start)));
	timestamps->values.insert(
			std::make_pair<const std::string, JSONValue*>("end",
					new JSONNumber(activity->timestamps.end)));

	JSONObject *assets = new JSONObject;
	assets->values.insert(
			std::make_pair<const std::string, JSONValue*>("large_image",
					new JSONString(activity->assets.largeImage)));
	assets->values.insert(
			std::make_pair<const std::string, JSONValue*>("large_text",
					new JSONString(activity->assets.largeText)));
	assets->values.insert(
			std::make_pair<const std::string, JSONValue*>("small_image",
					new JSONString(activity->assets.smallImage)));
	assets->values.insert(
			std::make_pair<const std::string, JSONValue*>("small_text",
					new JSONString(activity->assets.smallText)));

	JSONObject *partySize = new JSONObject;
	partySize->values.insert(
			std::make_pair<const std::string, JSONValue*>("current",
					new JSONNumber(activity->party.size.current)));
	partySize->values.insert(
			std::make_pair<const std::string, JSONValue*>("max",
					new JSONNumber(activity->party.size.max)));
	JSONObject *party = new JSONObject;
	party->values.insert(
			std::make_pair<const std::string, JSONValue*>("id",
					new JSONString(activity->party.id)));
	party->values.insert(
			std::make_pair<const std::string, JSONValue*>("size", partySize));
	party->values.insert(
			std::make_pair<const std::string, JSONValue*>("privacy",
					new JSONNumber(activity->party.privacy)));

	JSONObject *secrets = new JSONObject;
	secrets->values.insert(
			std::make_pair<const std::string, JSONValue*>("match",
					new JSONString(activity->secrets.match)));
	secrets->values.insert(
			std::make_pair<const std::string, JSONValue*>("join",
					new JSONString(activity->secrets.join)));
	secrets->values.insert(
			std::make_pair<const std::string, JSONValue*>("spectate",
					new JSONString(activity->secrets.spectate)));

	json->values.insert(
			std::make_pair<const std::string, JSONValue*>("timestamps",
					timestamps));
	json->values.insert(
			std::make_pair<const std::string, JSONValue*>("assets", assets));
	json->values.insert(
			std::make_pair<const std::string, JSONValue*>("party", party));
	json->values.insert(
			std::make_pair<const std::string, JSONValue*>("secrets", secrets));

	return json;
}
}
