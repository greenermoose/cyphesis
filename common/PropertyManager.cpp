// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2006 Alistair Riddoch
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA


#include "PropertyManager.h"

#include "PropertyFactory.h"

#include <cassert>

using Atlas::Objects::Root;

template<> PropertyManager* Singleton<PropertyManager>::ms_Singleton = nullptr;

PropertyManager::PropertyManager() = default;

PropertyManager::~PropertyManager() = default;

PropertyKit * PropertyManager::getPropertyFactory(const std::string & name) const
{
    auto I = m_propertyFactories.find(name);
    if (I != m_propertyFactories.end()) {
        assert(I->second);
        return I->second.get();
    }
    return nullptr;
}

void PropertyManager::installFactory(const std::string & name,
                                     std::unique_ptr<PropertyKit> factory)
{
    m_propertyFactories.insert(std::make_pair(name, std::move(factory)));
}

int PropertyManager::installFactory(const std::string & type_name,
                                    const Root & type_desc,
                                    std::unique_ptr<PropertyKit> factory)
{
    installFactory(type_name, std::move(factory));

    return 0;
}

