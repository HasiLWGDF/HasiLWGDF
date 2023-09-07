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

#include "utils/Implementer.hpp"
#include "utils/Holder.hpp"

using namespace Hasibix::HasiUtils;

namespace Hasibix::HasiLWGDF::Core
{
    class Item;
    class Module
    {
    public:
        explicit Module(const Holder<Item> parent) : parent(parent)
        {
        }

        virtual ~Module() = default;

        virtual const Holder<Item> getParent() const final
        {
            return parent;
        }

    private:
        const Implementer<void, Item> getOnInitialize()
        {
            return onInitialize;
        }

        const Implementer<void, Item, float> getOnEarlyUpdate()
        {
            return onEarlyUpdate;
        }

        const Implementer<void, Item, float> getOnUpdate()
        {
            return onUpdate;
        }

        const Implementer<void, Item, float> getOnLateUpdate()
        {
            return onLateUpdate;
        }

        const Implementer<void, Item> getOnDestroy()
        {
            return onDestroy;
        }

        friend class Item;

    protected:
        const Holder<Item> parent;

        const Implementer<void, Item> onInitialize{};
        const Implementer<void, Item, float> onEarlyUpdate{};
        const Implementer<void, Item, float> onUpdate{};
        const Implementer<void, Item, float> onLateUpdate{};
        const Implementer<void, Item> onDestroy{};
    };
}
