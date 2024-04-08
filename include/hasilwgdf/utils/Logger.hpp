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
#include <chrono>
#include <string>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Soon there will be HasiUtils4C so its on HasiUtils namespace
namespace Hasibix::HasiUtils {
namespace LogColor {
#ifdef WIN32
const std::string RESET = "\x1B[0m";

const std::string BLACK = "\x1B[0;30m";
const std::string RED = "\x1B[0;31m";
const std::string GREEN = "\x1B[0;32m";
const std::string YELLOW = "\x1B[0;33m";
const std::string BLUE = "\x1B[0;34m";
const std::string PURPLE = "\x1B[0;35m";
const std::string CYAN = "\x1B[0;36m";
const std::string WHITE = "\x1B[0;37m";

const std::string BLACK_BOLD = "\x1B[1;30m";
const std::string RED_BOLD = "\x1B[1;31m";
const std::string GREEN_BOLD = "\x1B[1;32m";
const std::string YELLOW_BOLD = "\x1B[1;33m";
const std::string BLUE_BOLD = "\x1B[1;34m";
const std::string PURPLE_BOLD = "\x1B[1;35m";
const std::string CYAN_BOLD = "\x1B[1;36m";
const std::string WHITE_BOLD = "\x1B[1;37m";

const std::string BLACK_UNDERLINED = "\x1B[4;30m";
const std::string RED_UNDERLINED = "\x1B[4;31m";
const std::string GREEN_UNDERLINED = "\x1B[4;32m";
const std::string YELLOW_UNDERLINED = "\x1B[4;33m";
const std::string BLUE_UNDERLINED = "\x1B[4;34m";
const std::string PURPLE_UNDERLINED = "\x1B[4;35m";
const std::string CYAN_UNDERLINED = "\x1B[4;36m";
const std::string WHITE_UNDERLINED = "\x1B[4;37m";

const std::string BLACK_BACKGROUND = "\x1B[40m";
const std::string RED_BACKGROUND = "\x1B[41m";
const std::string GREEN_BACKGROUND = "\x1B[42m";
const std::string YELLOW_BACKGROUND = "\x1B[43m";
const std::string BLUE_BACKGROUND = "\x1B[44m";
const std::string PURPLE_BACKGROUND = "\x1B[45m";
const std::string CYAN_BACKGROUND = "\x1B[46m";
const std::string WHITE_BACKGROUND = "\x1B[47m";

const std::string BLACK_BRIGHT = "\x1B[0;90m";
const std::string RED_BRIGHT = "\x1B[0;91m";
const std::string GREEN_BRIGHT = "\x1B[0;92m";
const std::string YELLOW_BRIGHT = "\x1B[0;93m";
const std::string BLUE_BRIGHT = "\x1B[0;94m";
const std::string PURPLE_BRIGHT = "\x1B[0;95m";
const std::string CYAN_BRIGHT = "\x1B[0;96m";
const std::string WHITE_BRIGHT = "\x1B[0;97m";

const std::string BLACK_BOLD_BRIGHT = "\x1B[1;90m";
const std::string RED_BOLD_BRIGHT = "\x1B[1;91m";
const std::string GREEN_BOLD_BRIGHT = "\x1B[1;92m";
const std::string YELLOW_BOLD_BRIGHT = "\x1B[1;93m";
const std::string BLUE_BOLD_BRIGHT = "\x1B[1;94m";
const std::string PURPLE_BOLD_BRIGHT = "\x1B[1;95m";
const std::string CYAN_BOLD_BRIGHT = "\x1B[1;96m";
const std::string WHITE_BOLD_BRIGHT = "\x1B[1;97m";

const std::string BLACK_BACKGROUND_BRIGHT = "\x1B[0;100m";
const std::string RED_BACKGROUND_BRIGHT = "\x1B[0;101m";
const std::string GREEN_BACKGROUND_BRIGHT = "\x1B[0;102m";
const std::string YELLOW_BACKGROUND_BRIGHT = "\x1B[0;103m";
const std::string BLUE_BACKGROUND_BRIGHT = "\x1B[0;104m";
const std::string PURPLE_BACKGROUND_BRIGHT = "\x1B[0;105m";
const std::string CYAN_BACKGROUND_BRIGHT = "\x1B[0;106m";
const std::string WHITE_BACKGROUND_BRIGHT = "\x1B[0;107m";
#elif defined(UNIX)
        const std::string RESET = "\033[0m";

        const std::string BLACK = "\033[0;30m";
        const std::string RED = "\033[0;31m";
        const std::string GREEN = "\033[0;32m";
        const std::string YELLOW = "\033[0;33m";
        const std::string BLUE = "\033[0;34m";
        const std::string PURPLE = "\033[0;35m";
        const std::string CYAN = "\033[0;36m";
        const std::string WHITE = "\033[0;37m";

        const std::string BLACK_BOLD = "\033[1;30m";
        const std::string RED_BOLD = "\033[1;31m";
        const std::string GREEN_BOLD = "\033[1;32m";
        const std::string YELLOW_BOLD = "\033[1;33m";
        const std::string BLUE_BOLD = "\033[1;34m";
        const std::string PURPLE_BOLD = "\033[1;35m";
        const std::string CYAN_BOLD = "\033[1;36m";
        const std::string WHITE_BOLD = "\033[1;37m";

        const std::string BLACK_UNDERLINED = "\033[4;30m";
        const std::string RED_UNDERLINED = "\033[4;31m";
        const std::string GREEN_UNDERLINED = "\033[4;32m";
        const std::string YELLOW_UNDERLINED = "\033[4;33m";
        const std::string BLUE_UNDERLINED = "\033[4;34m";
        const std::string PURPLE_UNDERLINED = "\033[4;35m";
        const std::string CYAN_UNDERLINED = "\033[4;36m";
        const std::string WHITE_UNDERLINED = "\033[4;37m";

        const std::string BLACK_BACKGROUND = "\033[40m";
        const std::string RED_BACKGROUND = "\033[41m";
        const std::string GREEN_BACKGROUND = "\033[42m";
        const std::string YELLOW_BACKGROUND = "\033[43m";
        const std::string BLUE_BACKGROUND = "\033[44m";
        const std::string PURPLE_BACKGROUND = "\033[45m";
        const std::string CYAN_BACKGROUND = "\033[46m";
        const std::string WHITE_BACKGROUND = "\033[47m";

        const std::string BLACK_BRIGHT = "\033[0;90m";
        const std::string RED_BRIGHT = "\033[0;91m";
        const std::string GREEN_BRIGHT = "\033[0;92m";
        const std::string YELLOW_BRIGHT = "\033[0;93m";
        const std::string BLUE_BRIGHT = "\033[0;94m";
        const std::string PURPLE_BRIGHT = "\033[0;95m";
        const std::string CYAN_BRIGHT = "\033[0;96m";
        const std::string WHITE_BRIGHT = "\033[0;97m";

        const std::string BLACK_BOLD_BRIGHT = "\033[1;90m";
        const std::string RED_BOLD_BRIGHT = "\033[1;91m";
        const std::string GREEN_BOLD_BRIGHT = "\033[1;92m";
        const std::string YELLOW_BOLD_BRIGHT = "\033[1;93m";
        const std::string BLUE_BOLD_BRIGHT = "\033[1;94m";
        const std::string PURPLE_BOLD_BRIGHT = "\033[1;95m";
        const std::string CYAN_BOLD_BRIGHT = "\033[1;96m";
        const std::string WHITE_BOLD_BRIGHT = "\033[1;97m";

        const std::string BLACK_BACKGROUND_BRIGHT = "\033[0;100m";
        const std::string RED_BACKGROUND_BRIGHT = "\033[0;101m";
        const std::string GREEN_BACKGROUND_BRIGHT = "\033[0;102m";
        const std::string YELLOW_BACKGROUND_BRIGHT = "\033[0;103m";
        const std::string BLUE_BACKGROUND_BRIGHT = "\033[0;104m";
        const std::string PURPLE_BACKGROUND_BRIGHT = "\033[0;105m";
        const std::string CYAN_BACKGROUND_BRIGHT = "\033[0;106m";
        const std::string WHITE_BACKGROUND_BRIGHT = "\033[0;107m";
#else
        const std::string RESET = "";

        const std::string BLACK = "";
        const std::string RED = "";
        const std::string GREEN = "";
        const std::string YELLOW = "";
        const std::string BLUE = "";
        const std::string PURPLE = "";
        const std::string CYAN = "";
        const std::string WHITE = "";

        const std::string BLACK_BOLD = "";
        const std::string RED_BOLD = "";
        const std::string GREEN_BOLD = "";
        const std::string YELLOW_BOLD = "";
        const std::string BLUE_BOLD = "";
        const std::string PURPLE_BOLD = "";
        const std::string CYAN_BOLD = "";
        const std::string WHITE_BOLD = "";

        const std::string BLACK_UNDERLINED = "";
        const std::string RED_UNDERLINED = "";
        const std::string GREEN_UNDERLINED = "";
        const std::string YELLOW_UNDERLINED = "";
        const std::string BLUE_UNDERLINED = "";
        const std::string PURPLE_UNDERLINED = "";
        const std::string CYAN_UNDERLINED = "";
        const std::string WHITE_UNDERLINED = "";

        const std::string BLACK_BACKGROUND = "" const std::string RED_BACKGROUND = "" const std::string GREEN_BACKGROUND = "" const std::string YELLOW_BACKGROUND = "" const std::string BLUE_BACKGROUND = "" const std::string PURPLE_BACKGROUND = "" const std::string CYAN_BACKGROUND = "" const std::string WHITE_BACKGROUND = ""

            const std::string BLACK_BRIGHT = "";
        const std::string RED_BRIGHT = "";
        const std::string GREEN_BRIGHT = "";
        const std::string YELLOW_BRIGHT = "";
        const std::string BLUE_BRIGHT = "";
        const std::string PURPLE_BRIGHT = "";
        const std::string CYAN_BRIGHT = "";
        const std::string WHITE_BRIGHT = "";

        const std::string BLACK_BOLD_BRIGHT = "";
        const std::string RED_BOLD_BRIGHT = "";
        const std::string GREEN_BOLD_BRIGHT = "";
        const std::string YELLOW_BOLD_BRIGHT = "";
        const std::string BLUE_BOLD_BRIGHT = "";
        const std::string PURPLE_BOLD_BRIGHT = "";
        const std::string CYAN_BOLD_BRIGHT = "";
        const std::string WHITE_BOLD_BRIGHT = "";

        const std::string BLACK_BACKGROUND_BRIGHT = "";
        const std::string RED_BACKGROUND_BRIGHT = "";
        const std::string GREEN_BACKGROUND_BRIGHT = "";
        const std::string YELLOW_BACKGROUND_BRIGHT = "";
        const std::string BLUE_BACKGROUND_BRIGHT = "";
        const std::string PURPLE_BACKGROUND_BRIGHT = "";
        const std::string CYAN_BACKGROUND_BRIGHT = "";
        const std::string WHITE_BACKGROUND_BRIGHT = "";
#endif
}
class Logger final {
private:
	std::string originName;

	std::string getTime() {
		auto now = std::chrono::system_clock::now();
		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
		std::tm *timeInfo = std::localtime(&currentTime);
		char formattedTime[20];
		std::strftime(formattedTime, sizeof(formattedTime), "%Y/%m/%d %H:%M:%S",
				timeInfo);
		return formattedTime;
	}

public:
#ifdef WIN32
	static void enableANSIColors() {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
	}
#endif
	Logger(std::string originName) :
			originName(originName) {
#ifdef WIN32
		enableANSIColors();
#endif
	}
	enum Level {
		UNSPECIFIED = -1,
		INFO = 0,
		DEBUG = 1,
		WARN = 2,
		ERR = 3,
		TRACE = 4,
		FATAL = 5,
	};
	void log(Level logLevel, std::string message ...) {
		std::string prefix;

		switch (logLevel) {
		case Level::INFO:
			prefix = LogColor::RESET + "[" + LogColor::WHITE + getTime()
					+ LogColor::RESET + "]" + LogColor::RESET + " ["
					+ LogColor::GREEN + "Info" + LogColor::RESET + "]"
					+ LogColor::RESET + " [" + LogColor::CYAN + originName
					+ LogColor::RESET + "]: ";
			break;
		case Level::DEBUG:
			prefix = LogColor::RESET + "[" + LogColor::WHITE + getTime()
					+ LogColor::RESET + "]" + LogColor::RESET + " ["
					+ LogColor::PURPLE + "Debug" + LogColor::RESET + "]"
					+ LogColor::RESET + " [" + LogColor::CYAN + originName
					+ LogColor::RESET + "]: ";
			break;
		case Level::WARN:
			prefix = LogColor::RESET + "[" + LogColor::WHITE + getTime()
					+ LogColor::RESET + "]" + LogColor::RESET + " ["
					+ LogColor::YELLOW + "Warning" + LogColor::RESET + "]"
					+ LogColor::RESET + " [" + LogColor::CYAN + originName
					+ LogColor::RESET + "]: ";
			break;
		case Level::ERR:
			prefix = LogColor::RESET + "[" + LogColor::WHITE + getTime()
					+ LogColor::RESET + "]" + LogColor::RESET + " ["
					+ LogColor::RED + "Error" + LogColor::RESET + "]"
					+ LogColor::RESET + " [" + LogColor::CYAN + originName
					+ LogColor::RESET + "]: ";
			break;
		case Level::FATAL:
			prefix = LogColor::RESET + "[" + LogColor::WHITE + getTime()
					+ LogColor::RESET + "]" + LogColor::RESET + " ["
					+ LogColor::BLUE + "Fatal" + LogColor::RESET + "]"
					+ LogColor::RESET + " [" + LogColor::CYAN + originName
					+ LogColor::RESET + "]: ";
			break;
		default:
			prefix = LogColor::RESET;
			break;
		}

		std::string fullMsg = prefix + message + LogColor::RESET;

		printf("%s", fullMsg);
	}
};
}
