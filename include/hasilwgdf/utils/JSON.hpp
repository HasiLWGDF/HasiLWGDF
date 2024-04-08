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
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace Hasibix::HasiUtils::JSON {
enum class JSONType {
	Object, Array, String, Number, Boolean, Null
};

class JSONValue {
public:
	JSONType type;

	JSONValue(JSONType t) :
			type(t) {
	}
	virtual ~JSONValue() {
	}

	virtual std::string serialize() const = 0;
};

class JSONObject: public JSONValue {
public:
	std::map<std::string, JSONValue*> values;

	JSONObject() :
			JSONValue(JSONType::Object) {
	}

	~JSONObject() {
		for (auto &pair : values) {
			delete pair.second;
		}
	}

	std::string serialize() const override
	{
		std::stringstream ss;
		ss << "{";
		bool first = true;
		for (const auto &pair : values) {
			if (!first) {
				ss << ",";
			}
			ss << "\"" << pair.first << "\":" << pair.second->serialize();
			first = false;
		}
		ss << "}";
		return ss.str();
	}
};

class JSONArray: public JSONValue {
public:
	std::vector<JSONValue*> elements;

	JSONArray() :
			JSONValue(JSONType::Array) {
	}

	~JSONArray() {
		for (JSONValue *val : elements) {
			delete val;
		}
	}
	std::string serialize() const override
	{
		std::stringstream ss;
		ss << "[";
		bool first = true;
		for (const JSONValue *val : elements) {
			if (!first) {
				ss << ",";
			}
			ss << val->serialize();
			first = false;
		}
		ss << "]";
		return ss.str();
	}
};

class JSONString: public JSONValue {
public:
	std::string value;

	JSONString(const std::string &v) :
			JSONValue(JSONType::String), value(v) {
	}

	std::string serialize() const override
	{
		return "\"" + value + "\"";
	}
};

class JSONNumber: public JSONValue {
public:
	double value;

	JSONNumber(double v) :
			JSONValue(JSONType::Number), value(v) {
	}

	std::string serialize() const override
	{
		return std::to_string(value);
	}
};

class JSONBoolean: public JSONValue {
public:
	bool value;

	JSONBoolean(bool v) :
			JSONValue(JSONType::Boolean), value(v) {
	}

	std::string serialize() const override
	{
		return value ? "true" : "false";
	}
};

class JSONNull: public JSONValue {
public:
	JSONNull() :
			JSONValue(JSONType::Null) {
	}

	std::string serialize() const override
	{
		return "null";
	}
};

class JSONParser {
public:
	JSONValue* parse(const std::string &jsonString) {
		pos = 0;
		json = jsonString;
		return parseValue();
	}

private:
	std::string json;
	size_t pos;

	char currentChar() {
		return json[pos];
	}

	void skipWhitespace() {
		while (pos < json.size() && std::isspace(currentChar())) {
			pos++;
		}
	}

	JSONValue* parseValue();
	JSONObject* parseObject();
	JSONArray* parseArray();
	JSONString* parseString();
	JSONNumber* parseNumber();
	JSONBoolean* parseBoolean();
	JSONNull* parseNull();
};

JSONValue* JSONParser::parseValue() {
	skipWhitespace();

	switch (currentChar()) {
	case '{':
		return parseObject();
	case '[':
		return parseArray();
	case '"':
		return parseString();
	case 't':
	case 'f':
		return parseBoolean();
	case 'n':
		return parseNull();
	default:
		if (std::isdigit(currentChar()) || currentChar() == '-') {
			return parseNumber();
		}
		// Handle error: Unexpected character
		return nullptr;
	}
}

JSONObject* JSONParser::parseObject() {
	if (currentChar() != '{') {
		// Handle error: Expected '{' at the beginning of an object
		return nullptr;
	}

	JSONObject *object = new JSONObject();
	pos++;

	while (pos < json.size() && currentChar() != '}') {
		skipWhitespace();

		if (currentChar() != '"') {
			// Handle error: Expected key (string)
			delete object;
			return nullptr;
		}

		JSONString *key = parseString();
		if (!key) {
			delete object;
			return nullptr;
		}

		skipWhitespace();

		if (currentChar() != ':') {
			// Handle error: Expected ':' after key
			delete object;
			delete key;
			return nullptr;
		}

		pos++; // Move past ':'
		skipWhitespace();

		JSONValue *value = parseValue();
		if (!value) {
			delete object;
			delete key;
			return nullptr;
		}

		object->values[key->value] = value;

		skipWhitespace();

		if (currentChar() == ',') {
			pos++;
		} else if (currentChar() != '}') {
			// Handle error: Expected ',' or '}'
			delete object;
			delete key;
			return nullptr;
		}
	}

	if (currentChar() != '}') {
		// Handle error: Expected '}' at the end of an object
		delete object;
		return nullptr;
	}

	pos++;
	return object;
}

JSONArray* JSONParser::parseArray() {
	if (currentChar() != '[') {
		// Handle error: Expected '[' at the beginning of an array
		return nullptr;
	}

	JSONArray *array = new JSONArray();
	pos++;

	while (pos < json.size() && currentChar() != ']') {
		skipWhitespace();

		JSONValue *value = parseValue();
		if (!value) {
			delete array;
			return nullptr;
		}

		array->elements.push_back(value);

		skipWhitespace();

		if (currentChar() == ',') {
			pos++;
		} else if (currentChar() != ']') {
			// Handle error: Expected ',' or ']'
			delete array;
			return nullptr;
		}
	}

	if (currentChar() != ']') {
		// Handle error: Expected ']' at the end of an array
		delete array;
		return nullptr;
	}

	pos++;
	return array;
}

JSONString* JSONParser::parseString() {
	if (currentChar() != '"') {
		// Handle error: Expected '"' at the beginning of a string
		return nullptr;
	}

	std::string value;
	pos++; // Move past the opening '"'

	while (pos < json.size() && currentChar() != '"') {
		if (currentChar() == '\\') {
			// Handle escape sequences if needed
			pos++;
			if (pos >= json.size()) {
				// Handle error: Unexpected end of input after '\'
				return nullptr;
			}

			switch (currentChar()) {
			case '"':
				value += '"';
				break;
			case '\\':
				value += '\\';
				break;
			case '/':
				value += '/';
				break;
			case 'b':
				value += '\b';
				break;
			case 'f':
				value += '\f';
				break;
			case 'n':
				value += '\n';
				break;
			case 'r':
				value += '\r';
				break;
			case 't':
				value += '\t';
				break;
				// Handle other escape sequences as needed
			default:
				// Handle error: Invalid escape sequence
				return nullptr;
			}

			pos++;
		} else {
			value += currentChar();
			pos++;
		}
	}

	if (pos >= json.size() || currentChar() != '"') {
		// Handle error: Expected closing '"' for the string
		return nullptr;
	}

	pos++; // Move past the closing '"'
	return new JSONString(value);
}

JSONNumber* JSONParser::parseNumber() {
	size_t startPos = pos;

	while (pos < json.size()
			&& (std::isdigit(currentChar()) || currentChar() == '.'
					|| currentChar() == 'e' || currentChar() == 'E'
					|| currentChar() == '+' || currentChar() == '-')) {
		pos++;
	}

	std::string numStr = json.substr(startPos, pos - startPos);
	try {
		double numValue = std::stod(numStr);
		return new JSONNumber(numValue);
	} catch (const std::exception&) {
		// Handle error: Invalid number format
		return nullptr;
	}
}

JSONBoolean* JSONParser::parseBoolean() {
	if (json.substr(pos, 4) == "true") {
		pos += 4;
		return new JSONBoolean(true);
	} else if (json.substr(pos, 5) == "false") {
		pos += 5;
		return new JSONBoolean(false);
	} else {
		// Handle error: Invalid boolean value
		return nullptr;
	}
}

JSONNull* JSONParser::parseNull() {
	if (json.substr(pos, 4) == "null") {
		pos += 4;
		return new JSONNull();
	} else {
		// Handle error: Invalid null value
		return nullptr;
	}
}
}
