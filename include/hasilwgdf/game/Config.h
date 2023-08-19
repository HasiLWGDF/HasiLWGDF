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

#include "../Core.h"

namespace Hasibix::HasiLWGDF::Core::Game
{
    typedef struct Config
    {
    private:
        typedef struct Graphics
        {
            Render::GraphicsAPI api = Render::GraphicsAPI::Software;
            bool vsync = false;
        } Graphics;

        typedef struct Physics
        {
        private:
            typedef struct Physics2D
            {
                Math::Vector2 gravity = {0.0F, -10.0F};
            } Physics2D;

            typedef struct Physics3D
            {
                Math::Vector3 gravity = {0.0F, -10.0F, 0.0F};
            } Physics3D;

        public:
            Physics2D &physics2D;
            Physics3D &physics3D;
        } Physics;

        typedef struct DiscordRPC
        {
            bool enabled = false;
            const char *clientId;
        } DiscordRPC;

    public:
        bool debug = true;
        float timescale = 1.0F;
        Graphics &graphics;
        Physics &physics;
        DiscordRPC &discordRpc;
    } Config;
}
