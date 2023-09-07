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
    issues or even PERMANENT damage to your project or device.
    DO NOT MODIFY THIS FILE UNLESS IT IS NECESSARY TO DO SO.
*/

#pragma once

#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include "utils/Holder.hpp"
#include <vector>

using namespace Hasibix::HasiUtils;

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
        static std::vector<Holder<Resource>> resources;

        std::string identifier;
        std::string path;
        ResourceType type;
        std::unique_ptr<unsigned char[]> &pData;

        Resource(const std::string &identifier, const ResourceType &type, const std::string &path, std::unique_ptr<unsigned char[]> pData)
            : identifier(identifier), path(path), type(type), pData(pData) {}

    public:
        static Holder<Resource> create(const std::string &identifier, const std::string &path, const ResourceType &type, const unsigned char pData[])
        {
            std::size_t size = 0;
            while (pData[size] != 0)
            {
                size++;
            }
            std::unique_ptr<unsigned char[]> data(new unsigned char[size]);
            std::copy(pData, pData + size, data.get());

            Holder<Resource> pResource = {Holder<Resource>{Resource{identifier, type, path, std::move(data)}}};
            resources.emplace_back(pResource);
            return pResource;
        }

        static void destroy()
        {
            resources.clear();
            resources.shrink_to_fit();
        }

        const std::string &getIdentifier() const
        {
            return identifier;
        }

        const std::string &getPath() const
        {
            return path;
        }

        const ResourceType &getType() const
        {
            return type;
        }

        std::unique_ptr<unsigned char[]> &getData() const
        {
            return pData;
        }
    };
}
