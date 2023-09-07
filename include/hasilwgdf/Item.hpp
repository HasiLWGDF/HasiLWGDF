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

#include "Module.hpp"
#include <iostream>
#include "math/Transform.hpp"
#include <memory>
#include <string>
#include "utils/Holder.hpp"
#include <vector>

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core
{
    class Group;
    class Item final
    {
    private:
        Holder<Math::Transform> &transform;
        std::string name;
        std::vector<Holder<Item>> children;
        std::vector<Holder<Module>> modules;

        void initialize()
        {
            for (Holder<Module> module : modules)
            {
                module.get()->getOnInitialize().run();
            }
            for (Holder<Item> child : children)
            {
                child.get()->initialize();
            }
        }

        void earlyUpdate(float delta)
        {
            for (Holder<Module> module : modules)
            {
                module.get()->getOnEarlyUpdate().run(delta);
            }
            for (Holder<Item> child : children)
            {
                child.get()->earlyUpdate(delta);
            }
        }

        void update(float delta)
        {
            for (Holder<Module> module : modules)
            {
                module.get()->getOnUpdate().run(delta);
            }
            for (Holder<Item> child : children)
            {
                child.get()->update(delta);
            }
        }

        void lateUpdate(float delta)
        {
            for (Holder<Module> module : modules)
            {
                module.get()->getOnLateUpdate().run(delta);
            }
            for (Holder<Item> child : children)
            {
                child.get()->lateUpdate(delta);
            }
        }

        void destroy()
        {
            for (Holder<Module> module : modules)
            {
                module.get()->getOnDestroy().run();
            }
            for (Holder<Item> child : children)
            {
                child.get()->destroy();
            }
        }

        friend class Group;

    public:
        Item(Holder<Math::Transform> &transform, std::string name = "New Item")
            : transform(transform), name(name) {}

        ~Item()
        {
            children.clear();
            modules.clear();
            children.shrink_to_fit();
            modules.shrink_to_fit();
        }

        int attachModules(Holder<Module> module...)
        {
            modules.emplace_back(module);
            return 0;
        }

        int attachChildren(Holder<Item> item...)
        {
            children.emplace_back(item);
            return 0;
        }
    };
}
