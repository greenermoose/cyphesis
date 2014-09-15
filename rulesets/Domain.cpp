// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2009 Alistair Riddoch
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


#include "Domain.h"
#include "TerrainProperty.h"
#include "LocatedEntity.h"
#include "OutfitProperty.h"
#include "EntityProperty.h"

#include "common/debug.h"
#include "common/const.h"

#include <Atlas/Objects/Operation.h>
#include <Atlas/Objects/Anonymous.h>


#include <iostream>
#include <unordered_set>

#include <cassert>

static const bool debug_flag = false;



using Atlas::Message::Element;
using Atlas::Message::MapType;
using Atlas::Objects::Root;
using Atlas::Objects::Entity::RootEntity;
using Atlas::Objects::Entity::Anonymous;
using Atlas::Objects::Operation::Set;
using Atlas::Objects::Operation::Sight;
using Atlas::Objects::Operation::Appearance;
using Atlas::Objects::Operation::Disappearance;


Domain::Domain(LocatedEntity& entity) : m_entity(entity), m_refCount(0)
{
}

Domain::~Domain()
{
}

float Domain::constrainHeight(LocatedEntity * parent,
                              const Point3D & pos,
                              const std::string & mode)
{
    assert(parent != 0);
    if (mode == "fixed") {
        return pos.z();
    }
    const TerrainProperty * tp = parent->getPropertyClass<TerrainProperty>("terrain");
    if (tp != 0) {
        if (mode == "floating") {
            return 0.f;
        }
        float h = pos.z();
        Vector3D normal;
        tp->getHeightAndNormal(pos.x(), pos.y(), h, normal);
        // FIXME Use a virtual movement_domain function to get the constraints
        debug(std::cout << "Fix height " << pos.z() << " to " << h
                        << std::endl << std::flush;);
        return h;
    } else if (parent->m_location.m_loc != 0) {
        static const Quaternion identity(Quaternion().identity());
        const Point3D & ppos = parent->m_location.pos();
        debug(std::cout << "parent " << parent->getId() << " of type "
                        << parent->getType() << " pos " << ppos.z()
                        << " my pos " << pos.z()
                        << std::endl << std::flush;);
        float h;
        const Quaternion & parent_orientation = parent->m_location.orientation().isValid() ? parent->m_location.orientation() : identity;
        h =  constrainHeight(parent->m_location.m_loc,
                             pos.toParentCoords(parent->m_location.pos(),
                                                parent_orientation),
                             mode) - ppos.z();
        debug(std::cout << "Correcting height from " << pos.z() << " to " << h
                        << std::endl << std::flush;);
        return h;
    }
    return pos.z();
}

void Domain::tick(double t)
{
    
}

void Domain::lookAtEntity(const LocatedEntity& observingEntity, const LocatedEntity& observedEntity, const Operation & originalLookOp, OpVector& res) const
{
    debug(std::cout << "Domain::lookAtEntity()" << std::endl << std::flush;);

    if (isEntityVisibleFor(observingEntity, observedEntity)) {
        Sight s;

        Anonymous sarg;
        observedEntity.addToEntity(sarg);
        s->setArgs1(sarg);

        if (observedEntity.m_contains != nullptr) {
            //If the entity has any outfitted or wielded entities these should always be shown.
            const OutfitProperty* outfitProperty = observedEntity.getPropertyClass<OutfitProperty>("outfit");
            std::unordered_set<std::string> outfittedEntities;
            if (outfitProperty) {
                for (auto& entry : outfitProperty->data()) {
                    auto outfittedEntity = entry.second.get();
                    if (outfittedEntity) {
                        outfittedEntities.insert(outfittedEntity->getId());
                    }
                }
            }

            const EntityProperty* rightHandWieldProperty = observedEntity.getPropertyClass<EntityProperty>("right_hand_wield");
            if (rightHandWieldProperty) {
                auto entity = rightHandWieldProperty->data().get();
                if (entity) {
                    outfittedEntities.insert(entity->getId());
                }
            }

            std::list<std::string> & contlist = sarg->modifyContains();
            contlist.clear();
            for (auto& entry : *observedEntity.m_contains) {
                //If the entity is outfitted or wielded we should include it.
                if (outfittedEntities.count(entry->getId())) {
                    contlist.push_back(entry->getId());
                } else {
                    float fromSquSize = entry->m_location.squareBoxSize();
                    //TODO: make this much smarter by only using the local position of the child along with the position of the looked at entity
                    float dist = squareDistance(observingEntity.m_location, entry->m_location);
                    float view_factor = fromSquSize / dist;
                    if (view_factor > consts::square_sight_factor) {
                        contlist.push_back(entry->getId());
                    }
                }
            }
            if (contlist.empty()) {
                sarg->removeAttr("contains");
            }
        }

        //If the observer is looking at the domain entity we should hide anything above it, since the observer won't be able to see that anyway.
        if (&m_entity == &observedEntity) {
            sarg->removeAttr("loc");
        }

        s->setTo(originalLookOp->getFrom());
        if (!originalLookOp->isDefaultSerialno()) {
            s->setRefno(originalLookOp->getSerialno());
        }
        res.push_back(s);
    }
}

bool Domain::isEntityVisibleFor(const LocatedEntity& observingEntity, const LocatedEntity& observedEntity) const
{
    if (&observedEntity == &m_entity) {
        return true;
    }

    //We need to check the distance to the entity being looked at, and make sure that both the looking entity and
    //the entity being looked at belong to the same domain
    const Location* ancestor;
    //We'll optimize for the case when a child entity is looking at the domain entity, by sending the looked at entity first, since this is the most common case.
    //The squareDistanceWithAncestor() method will first try to find the first entity being sent by walking upwards from the second entity being sent (if
    //it fails it will try other approaches).
    float distance = squareDistanceWithAncestor(observedEntity.m_location, observingEntity.m_location, &ancestor);
    if (ancestor == nullptr) {
        //No common ancestor found
        return false;
    } else {
        //Make sure that the ancestor is the domain entity, or a child entity.
        while (ancestor != &m_entity.m_location) {
            if (ancestor->m_loc == nullptr) {
                //We've reached the top of the parents chain without hitting our domain entity; the ancestor isn't a child of the domain entity.
                return false;
            }
            ancestor = &ancestor->m_loc->m_location;
        }
    }
    //If we get here we know that the ancestor is a child of the domain entity.
    //Now we need to determine if the looking entity can see the looked at entity. The default way of doing this is by comparing the size of the looked at entity with the distance,
    //but this check can be overridden if the looked at entity is either wielded or outfitted by a parent entity.
    if ((observedEntity.m_location.squareBoxSize() / distance) > consts::square_sight_factor) {
        return true;
    }
    //The entity couldn't be seen just from its size; now check if it's outfitted or wielded.
    if (observedEntity.m_location.m_loc != nullptr) {
        const OutfitProperty* outfitProperty =
                observedEntity.m_location.m_loc->getPropertyClass<OutfitProperty>(
                        "outfit");
        if (outfitProperty) {
            for (auto& entry : outfitProperty->data()) {
                auto outfittedEntity = entry.second.get();
                if (outfittedEntity && outfittedEntity == &observedEntity) {
                    return true;
                }
            }
        }
        //If the entity isn't large enough, and isn't outfitted, perhaps it's wielded?
        const EntityProperty* rightHandWieldProperty = observedEntity.m_location.m_loc->getPropertyClass<EntityProperty>("right_hand_wield");
        if (rightHandWieldProperty) {
            auto entity = rightHandWieldProperty->data().get();
            if (entity && entity == &observedEntity) {
                return true;
            }
        }
    }
    return false;
}

void Domain::calculateVisibility(std::vector<Root>& appear, std::vector<Root>& disappear, Anonymous& this_ent, const LocatedEntity& parent,
        const LocatedEntity& moved_entity, const Location& old_loc, OpVector & res) const {

    float fromSquSize = moved_entity.m_location.squareBoxSize();

    //We need to get the position of the moved entity in relation to the parent.
    const Point3D new_pos = relativePos(parent.m_location, moved_entity.m_location);
    const Point3D old_pos = relativePos(parent.m_location, old_loc);

    assert(m_entity.m_contains != nullptr);
    for (const LocatedEntity* other: *parent.m_contains) {
        if (other == &moved_entity) {
            continue;
        }

        assert(other != nullptr);
        float old_dist = squareDistance(other->m_location.pos(), old_pos),
              new_dist = squareDistance(other->m_location.pos(), new_pos),
              squ_size = other->m_location.squareBoxSize();

        // Build appear and disappear lists, and send disappear operations
        // to perceptive entities saying that we are disappearing
        if (other->isPerceptive()) {
            bool was_in_range = ((fromSquSize / old_dist) > consts::square_sight_factor),
                 is_in_range = ((fromSquSize / new_dist) > consts::square_sight_factor);
            if (was_in_range != is_in_range) {
                if (was_in_range) {
                    // Send operation to the entity in question so it
                    // knows it is losing sight of us.
                    Disappearance d;
                    d->setArgs1(this_ent);
                    d->setTo(other->getId());
                    res.push_back(d);
                }
                //Note that we don't send any Appear ops for those entities that we now move within sight range of.
                //This is because these will receive a Move op anyway as part of the broadcast, which informs them
                //that an entity has moved within sight range anyway.
            }
        }

        bool could_see = ((squ_size / old_dist) > consts::square_sight_factor),
             can_see = ((squ_size / new_dist) > consts::square_sight_factor);
        if (could_see ^ can_see) {
            Anonymous that_ent;
            that_ent->setId(other->getId());
            that_ent->setStamp(other->getSeq());
            if (could_see) {
                // We are losing sight of that object
                disappear.push_back(that_ent);
                debug(std::cout << moved_entity.getId() << ": losing sight of "
                                << other->getId() << std::endl;);
            } else /*if (can_see)*/ {
                // We are gaining sight of that object
                appear.push_back(that_ent);
                debug(std::cout << moved_entity.getId() << ": gaining sight of "
                                << other->getId() << std::endl;);
            }
        } else {
            //We've seen this entity before, and we're still seeing it. Check if there are any children that's now changing visibility.
            if (other->m_contains && !other->m_contains->empty()) {
                calculateVisibility(appear, disappear, this_ent, *other, moved_entity, old_loc, res);
            }
        }
    }
}



void Domain::processVisibilityForMovedEntity(const LocatedEntity& moved_entity, const Location& old_loc, OpVector & res) {
    debug(std::cout << "testing range" << std::endl;);
    std::vector<Root> appear, disappear;

    Anonymous this_ent;
    this_ent->setId(moved_entity.getId());
    this_ent->setStamp(moved_entity.getSeq());

    calculateVisibility(appear, disappear, this_ent, m_entity, moved_entity, old_loc, res);

    if (!appear.empty()) {
        // Send an operation to ourselves with a list of entities
        // we are gaining sight of
        Appearance a;
        a->setArgs(appear);
        a->setTo(moved_entity.getId());
        res.push_back(a);
    }
    if (!disappear.empty()) {
        // Send an operation to ourselves with a list of entities
        // we are losing sight of
        Disappearance d;
        d->setArgs(disappear);
        d->setTo(moved_entity.getId());
        res.push_back(d);
    }
}


