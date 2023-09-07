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

#pragma once

#include "../utils/Export.hpp"

extern "C"
{
    namespace Hasibix::HasiLWGDF::Core::Input
    {
        class Keyboard final
        {
        public:
            // Adapted from SDL_Scancode
            enum KeyCode
            {
                H_KC_A = 4,
                H_KC_B = 5,
                H_KC_C = 6,
                H_KC_D = 7,
                H_KC_E = 8,
                H_KC_F = 9,
                H_KC_G = 10,
                H_KC_H = 11,
                H_KC_I = 12,
                H_KC_J = 13,
                H_KC_K = 14,
                H_KC_L = 15,
                H_KC_M = 16,
                H_KC_N = 17,
                H_KC_O = 18,
                H_KC_P = 19,
                H_KC_Q = 20,
                H_KC_R = 21,
                H_KC_S = 22,
                H_KC_T = 23,
                H_KC_U = 24,
                H_KC_V = 25,
                H_KC_W = 26,
                H_KC_X = 27,
                H_KC_Y = 28,
                H_KC_Z = 29,

                H_KC_1 = 30,
                H_KC_2 = 31,
                H_KC_3 = 32,
                H_KC_4 = 33,
                H_KC_5 = 34,
                H_KC_6 = 35,
                H_KC_7 = 36,
                H_KC_8 = 37,
                H_KC_9 = 38,
                H_KC_0 = 39,

                H_KC_RETURN = 40,
                H_KC_ESH_CAPE = 41,
                H_KC_BACKSPACE = 42,
                H_KC_TAB = 43,
                H_KC_SPACE = 44,

                H_KC_MINUS = 45,
                H_KC_EQUALS = 46,
                H_KC_LEFTBRACKET = 47,
                H_KC_RIGHTBRACKET = 48,
                H_KC_BACKSLASH = 49,
                H_KC_NONUSHASH = 50,
                H_KC_SEMICOLON = 51,
                H_KC_APOSTROPHE = 52,
                H_KC_GRAVE = 53,
                H_KC_COMMA = 54,
                H_KC_PERIOD = 55,
                H_KC_SLASH = 56,

                H_KC_H_CAPSLOCK = 57,

                H_KC_F1 = 58,
                H_KC_F2 = 59,
                H_KC_F3 = 60,
                H_KC_F4 = 61,
                H_KC_F5 = 62,
                H_KC_F6 = 63,
                H_KC_F7 = 64,
                H_KC_F8 = 65,
                H_KC_F9 = 66,
                H_KC_F10 = 67,
                H_KC_F11 = 68,
                H_KC_F12 = 69,

                H_KC_PRINTSCREEN = 70,
                H_KC_SCROLLLOCK = 71,
                H_KC_PAUSE = 72,
                H_KC_INSERT = 73,
                H_KC_HOME = 74,
                H_KC_PAGEUP = 75,
                H_KC_DELETE = 76,
                H_KC_END = 77,
                H_KC_PAGEDOWN = 78,
                H_KC_RIGHT = 79,
                H_KC_LEFT = 80,
                H_KC_DOWN = 81,
                H_KC_UP = 82,

                H_KC_NUMLOCH_KCLEAR = 83,
                H_KC_KP_DIVIDE = 84,
                H_KC_KP_MULTIPLY = 85,
                H_KC_KP_MINUS = 86,
                H_KC_KP_PLUS = 87,
                H_KC_KP_ENTER = 88,
                H_KC_KP_1 = 89,
                H_KC_KP_2 = 90,
                H_KC_KP_3 = 91,
                H_KC_KP_4 = 92,
                H_KC_KP_5 = 93,
                H_KC_KP_6 = 94,
                H_KC_KP_7 = 95,
                H_KC_KP_8 = 96,
                H_KC_KP_9 = 97,
                H_KC_KP_0 = 98,
                H_KC_KP_PERIOD = 99,

                H_KC_NONUSBACKSLASH = 100,
                H_KC_APPLIH_CATION = 101,
                H_KC_POWER = 102,
                H_KC_KP_EQUALS = 103,
                H_KC_F13 = 104,
                H_KC_F14 = 105,
                H_KC_F15 = 106,
                H_KC_F16 = 107,
                H_KC_F17 = 108,
                H_KC_F18 = 109,
                H_KC_F19 = 110,
                H_KC_F20 = 111,
                H_KC_F21 = 112,
                H_KC_F22 = 113,
                H_KC_F23 = 114,
                H_KC_F24 = 115,
                H_KC_EXECUTE = 116,
                H_KC_HELP = 117,
                H_KC_MENU = 118,
                H_KC_SELECT = 119,
                H_KC_STOP = 120,
                H_KC_AGAIN = 121,
                H_KC_UNDO = 122,
                H_KC_CUT = 123,
                H_KC_COPY = 124,
                H_KC_PASTE = 125,
                H_KC_FIND = 126,
                H_KC_MUTE = 127,
                H_KC_VOLUMEUP = 128,
                H_KC_VOLUMEDOWN = 129,
                H_KC_KP_COMMA = 133,
                H_KC_KP_EQUALSAS400 = 134,

                H_KC_INTERNATIONAL1 = 135,
                H_KC_INTERNATIONAL2 = 136,
                H_KC_INTERNATIONAL3 = 137,
                H_KC_INTERNATIONAL4 = 138,
                H_KC_INTERNATIONAL5 = 139,
                H_KC_INTERNATIONAL6 = 140,
                H_KC_INTERNATIONAL7 = 141,
                H_KC_INTERNATIONAL8 = 142,
                H_KC_INTERNATIONAL9 = 143,
                H_KC_LANG1 = 144,
                H_KC_LANG2 = 145,
                H_KC_LANG3 = 146,
                H_KC_LANG4 = 147,
                H_KC_LANG5 = 148,
                H_KC_LANG6 = 149,
                H_KC_LANG7 = 150,
                H_KC_LANG8 = 151,
                H_KC_LANG9 = 152,

                H_KC_ALTERASE = 153,
                H_KC_SYSREQ = 154,
                H_KC_H_CANCEL = 155,
                H_KC_CLEAR = 156,
                H_KC_PRIOR = 157,
                H_KC_RETURN2 = 158,
                H_KC_SEPARATOR = 159,
                H_KC_OUT = 160,
                H_KC_OPER = 161,
                H_KC_CLEARAGAIN = 162,
                H_KC_CRSEL = 163,
                H_KC_EXSEL = 164,

                H_KC_KP_00 = 176,
                H_KC_KP_000 = 177,
                H_KC_THOUSANDSSEPARATOR = 178,
                H_KC_DECIMALSEPARATOR = 179,
                H_KC_CURRENCYUNIT = 180,
                H_KC_CURRENCYSUBUNIT = 181,
                H_KC_KP_LEFTPAREN = 182,
                H_KC_KP_RIGHTPAREN = 183,
                H_KC_KP_LEFTBRACE = 184,
                H_KC_KP_RIGHTBRACE = 185,
                H_KC_KP_TAB = 186,
                H_KC_KP_BACKSPACE = 187,
                H_KC_KP_A = 188,
                H_KC_KP_B = 189,
                H_KC_KP_C = 190,
                H_KC_KP_D = 191,
                H_KC_KP_E = 192,
                H_KC_KP_F = 193,
                H_KC_KP_XOR = 194,
                H_KC_KP_POWER = 195,
                H_KC_KP_PERCENT = 196,
                H_KC_KP_LESS = 197,
                H_KC_KP_GREATER = 198,
                H_KC_KP_AMPERSAND = 199,
                H_KC_KP_DBLAMPERSAND = 200,
                H_KC_KP_VERTIH_CALBAR = 201,
                H_KC_KP_DBLVERTIH_CALBAR = 202,
                H_KC_KP_COLON = 203,
                H_KC_KP_HASH = 204,
                H_KC_KP_SPACE = 205,
                H_KC_KP_AT = 206,
                H_KC_KP_EXCLAM = 207,
                H_KC_KP_MEMSTORE = 208,
                H_KC_KP_MEMREH_CALL = 209,
                H_KC_KP_MEMCLEAR = 210,
                H_KC_KP_MEMADD = 211,
                H_KC_KP_MEMSUBTRACT = 212,
                H_KC_KP_MEMMULTIPLY = 213,
                H_KC_KP_MEMDIVIDE = 214,
                H_KC_KP_PLUSMINUS = 215,
                H_KC_KP_CLEAR = 216,
                H_KC_KP_CLEARENTRY = 217,
                H_KC_KP_BINARY = 218,
                H_KC_KP_OCTAL = 219,
                H_KC_KP_DECIMAL = 220,
                H_KC_KP_HEXADECIMAL = 221,

                H_KC_LCTRL = 224,
                H_KC_LSHIFT = 225,
                H_KC_LALT = 226,
                H_KC_LGUI = 227,
                H_KC_RCTRL = 228,
                H_KC_RSHIFT = 229,
                H_KC_RALT = 230,
                H_KC_RGUI = 231,

                H_KC_MODE = 257,

                H_KC_AUDIONEXT = 258,
                H_KC_AUDIOPREV = 259,
                H_KC_AUDIOSTOP = 260,
                H_KC_AUDIOPLAY = 261,
                H_KC_AUDIOMUTE = 262,
                H_KC_MEDIASELECT = 263,
                H_KC_WWW = 264,
                H_KC_MAIL = 265,
                H_KC_H_CALCULATOR = 266,
                H_KC_COMPUTER = 267,
                H_KC_AC_SEARCH = 268,
                H_KC_AC_HOME = 269,
                H_KC_AC_BACK = 270,
                H_KC_AC_FORWARD = 271,
                H_KC_AC_STOP = 272,
                H_KC_AC_REFRESH = 273,
                H_KC_AC_BOOKMARKS = 274,

                H_KC_BRIGHTNESSDOWN = 275,
                H_KC_BRIGHTNESSUP = 276,
                H_KC_DISPLAYSWITCH = 277,
                H_KC_KBDILLUMTOGGLE = 278,
                H_KC_KBDILLUMDOWN = 279,
                H_KC_KBDILLUMUP = 280,
                H_KC_EJECT = 281,
                H_KC_SLEEP = 282,

                H_KC_APP1 = 283,
                H_KC_APP2 = 284,

                H_KC_AUDIOREWIND = 285,
                H_KC_AUDIOFASTFORWARD = 286,

                H_KC_SOFTLEFT = 287,
                H_KC_SOFTRIGHT = 288,
                H_KC_H_CALL = 289,
                H_KC_ENDH_CALL = 290,
            };

        private:
            Keyboard() = delete;

        public:
            HASILWGDF_EXPORT static bool getKeyDown(KeyCode key);
            HASILWGDF_EXPORT static bool getKeyPressed(KeyCode key);
            HASILWGDF_EXPORT static bool getKeyReleased(KeyCode key);
            HASILWGDF_EXPORT static float getKeyAxis(KeyCode positive, KeyCode negative);
        };
    }
}
