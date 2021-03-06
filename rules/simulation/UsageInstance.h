/*
 Copyright (C) 2018 Erik Ogenvik

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef CYPHESIS_USAGEINSTANCE_H
#define CYPHESIS_USAGEINSTANCE_H

#include "rules/entityfilter/Filter.h"
#include "rules/EntityLocation.h"
#include "modules/Ref.h"
#include "common/Property.h"
#include "external/pycxx/CXX/Objects.hxx"

#include <Atlas/Objects/RootOperation.h>

#include <boost/variant.hpp>

#include <memory>
#include <functional>

struct UsageParameter
{
    enum class Type
    {
            ENTITY,
            ENTITYLOCATION,
            POSITION,
            DIRECTION
    };

    Type type;
    std::shared_ptr<EntityFilter::Filter> constraint;
    int min = 1;
    int max = 1;

};

struct Usage
{
    std::string description;

    std::map<std::string, UsageParameter> params;

    /**
     * The Python script which will handle this op.
     */
    std::string handler;
    std::shared_ptr<EntityFilter::Filter> constraint;

};

class UsageInstance
{
    public:

        static std::function<Py::Object(UsageInstance&& usageInstance)> scriptCreator;


        typedef boost::variant<EntityLocation, WFMath::Point<3>, WFMath::Vector<3>> UsageArg;
        Usage definition;

        Ref<LocatedEntity> actor;
        Ref<LocatedEntity> tool;

        std::map<std::string, std::vector<UsageArg>> args;

        Atlas::Objects::Operation::RootOperation op;

        std::pair<bool, std::string> isValid() const;

};


#endif //CYPHESIS_USAGEINSTANCE_H
