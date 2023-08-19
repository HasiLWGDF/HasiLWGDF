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

#include <memory>
#include <string>
#include <vector>

namespace Hasibix::HasiLWGDF::Core
{
    class Resource final
    {
    public:
        enum ResourceType
        {
            UNKNOWN = 0,
            AUDIO,
            CONFIG,
            DATA,
            IMAGE,
            MESH,
            VIDEO,
        };

    private:
        static std::vector<std::unique_ptr<Resource> &> resources;

        std::string identifier;
        std::string path;
        ResourceType type;
        std::unique_ptr<const unsigned char *> pData;

        Resource(const std::string &identifier, const ResourceType &type, const std::string &path)
            : identifier(identifier), path(path) {}

    public:
        static std::unique_ptr<Resource> &create(const std::string &identifier, const std::string &path, const ResourceType &type, const unsigned char *&pData)
        {
            std::unique_ptr<Resource> pResource = std::make_unique<Resource>(identifier, type, path);
            pResource->pData = std::make_unique<const unsigned char *>(pData);
            resources.push_back(pResource);
            return pResource;
        }

        static void destroy()
        {
            for (auto it = resources.begin(); it != resources.end(); ++it)
            {
                resources.erase(it);
            }
        }

        const std::string &getIdentifier() const
        {
            return this->identifier;
        }

        const std::string &getPath() const
        {
            return this->path;
        }

        const ResourceType &getType() const
        {
            return this->type;
        }

        const std::unique_ptr<const unsigned char *> &getData() const
        {
            return this->pData;
        }
    };
}
