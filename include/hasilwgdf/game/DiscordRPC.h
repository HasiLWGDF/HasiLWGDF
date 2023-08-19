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
#include <stdint.h>

namespace Hasibix::HasiLWGDF::Core::Game::DisocrdRPC
{
    typedef struct Timestamps
    {
        int64_t start;
        int64_t end;
    } Timestamps;

    typedef struct Assets
    {
        const char *largeImage; /* max 128 bytes */
        const char *largeText;  /* max 128 bytes */
        const char *smallImage; /* max 128 bytes */
        const char *smallText;  /* max 128 bytes */
    } Assets;

    typedef struct PartySize
    {
        int current;
        int max;
    } PartySize;

    typedef struct Party
    {
        const char *id; /* max 128 bytes */
        PartySize size;
        int privacy;
    } Party;

    typedef struct Secrets
    {
        const char *match;    /* max 128 bytes */
        const char *join;     /* max 128 bytes */
        const char *spectate; /* max 128 bytes */
    } Secrets;

    typedef struct Activity
    {
        const char *state;   /* max 128 bytes */
        const char *details; /* max 128 bytes */
        Timestamps timestamps;
        Party party;
        Secrets secrets;
        bool pInstance;
    } Activity;

    typedef struct User
    {
        const char *userId;
        const char *username;
        const char *discriminator;
        const char *avatar;
    } User;

    typedef struct EventHandlers
    {
        void (*ready)(const User *request);
        void (*disconnected)(int errorCode, const char *message);
        void (*errored)(int errorCode, const char *message);
        void (*joinGame)(const char *joinSecret);
        void (*spectateGame)(const char *spectateSecret);
        void (*joinRequest)(const User *request);
    } EventHandlers;
}
