// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#include "Entity.h"
#include "MemMap.h"
#include "Script.h"

#include "modules/Location.h"

#include "common/log.h"
#include "common/debug.h"

#include <Atlas/Objects/Operation/Look.h>

static const bool debug_flag = false;

Entity * MemMap::addObject(Entity * object)
{
    assert(object != 0);
    assert(!object->getId().empty());

    debug(std::cout << "MemMap::addObject " << object << " " << object->getId()
                    << std::endl << std::flush;);
    m_entities[object->getId()] = object;

    debug( std::cout << this << std::endl << std::flush;);
    std::vector<std::string>::const_iterator I;
    for(I = m_addHooks.begin(); I != m_addHooks.end(); I++) {
        m_script->hook(*I, object);
    }
    return object;
}

void MemMap::readObject(Entity * object, const Element::MapType & entmap)
// Read the contents of an Atlas message into an object
{
    Element::MapType::const_iterator I = entmap.find("name");
    if (I != entmap.end() && I->second.isString()) {
        object->setName(I->second.asString());
    }
    I = entmap.find("type");
    if (I != entmap.end() && I->second.isString()) {
        object->setType(I->second.asString());
    }
    object->merge(entmap);
    I = entmap.find("loc");
    if ((I != entmap.end()) && I->second.isString()) {
        getAdd(I->second.asString());
    }
    object->getLocation(entmap, m_entities);
    addContents(entmap);
}

void MemMap::updateObject(Entity * object, const Element::MapType & entmap)
// Update contents of object an Atlas message.
{
    assert(object != 0);

    debug( std::cout << " got " << object << std::endl << std::flush;);

    readObject(object, entmap);

    std::vector<std::string>::const_iterator K;
    for(K = m_updateHooks.begin(); K != m_updateHooks.end(); K++) {
        m_script->hook(*K, object);
    }
}

Entity * MemMap::newObject(const std::string & id,
                           const Element::MapType & entmap)
// Create a new object from an Atlas message.
{
    assert(!id.empty());
    assert(m_entities.find(id) == m_entities.end());

    Entity * object = new Entity(id);

    readObject(object, entmap);

    return addObject(object);
}

RootOperation * MemMap::lookId()
// Generate a look operation to look at an entity we are interested in
{
    debug( std::cout << "MemMap::lookId" << std::endl << std::flush;);
    if (!m_additionsById.empty()) {
        const std::string & id = m_additionsById.front();
        Look * l = new Look();
        Atlas::Message::Element::MapType m;
        m["id"] = Atlas::Message::Element(id);
        l->setArgs(Atlas::Message::Element::ListType(1, m));
        l->setTo(id);
        m_additionsById.pop_front();
        return l;
    }
    return NULL;
}

Entity * MemMap::addId(const std::string & id)
// Queue the ID of an object we are interested in
{
    assert(!id.empty());
    assert(m_entities.find(id) == m_entities.end());

    debug( std::cout << "MemMap::add_id" << std::endl << std::flush;);
    m_additionsById.push_back(id);
    Entity * entity = new Entity(id);
    return addObject(entity);
}

void MemMap::del(const std::string & id)
// Delete an object from memory
{
    EntityDict::iterator I = m_entities.find(id);
    if (I != m_entities.end()) {
        Entity * obj = I->second;
        assert(obj != 0);
        m_entities.erase(I);
        std::vector<std::string>::const_iterator J;
        for(J = m_deleteHooks.begin(); J != m_deleteHooks.end(); J++) {
            m_script->hook(*J, obj);
        }
        delete obj;
    }
}

Entity * MemMap::get(const std::string & id)
// Get an object from memory
{
    debug( std::cout << "MemMap::get" << std::endl << std::flush;);
    if (id.empty()) {
        // This shouldn't really occur, and shouldn't be a problem
        log(ERROR, "MemMap::get queried for empty id string");
        return NULL;
    }
    EntityDict::const_iterator I = m_entities.find(id);
    if (I != m_entities.end()) {
        assert(I->second != 0);
        return I->second;
    }
    return NULL;
}

Entity * MemMap::getAdd(const std::string & id)
// Get an object from memory, or add it if we haven't seen it yet
{
    debug( std::cout << "MemMap::getAdd(" << id << ")" << std::endl << std::flush;);
    if (id.empty()) {
        // This shouldn't really occur, and shouldn't be a problem
        log(ERROR, "MemMap::getAdd queried for empty id string");
        return NULL;
    }
    EntityDict::const_iterator I = m_entities.find(id);
    if (I != m_entities.end()) {
        return I->second;
    }
    return addId(id);
}

void MemMap::addContents(const Element::MapType & entmap)
// Iterate over the contains attribute of a message, looking at all the contents
{
    Element::MapType::const_iterator I = entmap.find("contains");
    if (I == entmap.end()) {
        return;
    }
    if (!I->second.isList()) {
        log(ERROR, "MemMap::addContents, malformed contains is not list");
        return;
    }
    const Element::ListType & contlist = I->second.asList();
    Element::ListType::const_iterator J = contlist.begin();
    for(;J != contlist.end(); J++) {
        if (!J->isString()) {
            log(ERROR, "MemMap::addContents, malformed non-string in contains");
            continue;
        }
        getAdd(J->asString());
    }
}

Entity * MemMap::updateAdd(const Element::MapType & entmap)
// Update an object in our memory, from an Atlas message
{
    debug( std::cout << "MemMap::update" << std::endl << std::flush;);
    Element::MapType::const_iterator I = entmap.find("id");
    if (I == entmap.end()) {
        log(ERROR, "MemMap::update, Missing id in updated entity");
        return NULL;
    }
    if (!I->second.isString()) {
        log(ERROR, "MemMap::update, Malformed non-string id in updated entity");
        return NULL;
    }
    const std::string & id = I->second.asString();
    if (id.empty()) {
        log(ERROR, "MemMap::update, Empty id in updated entity");
        return NULL;
    }
    EntityDict::const_iterator J = m_entities.find(id);
    if (J == m_entities.end()) {
        return newObject(id, entmap);
    }
    Entity * object = J->second;
    updateObject(object, entmap);
    return object;
}

EntityVector MemMap::findByType(const std::string & what)
// Find an object in our memory of a certain type
{
    EntityVector res;
    EntityDict::const_iterator I;
    for(I = m_entities.begin(); I != m_entities.end(); I++) {
        Entity * item = I->second;
        debug( std::cout << "F" << what << ":" << item->getType() << ":" << item->getId() << std::endl << std::flush;);
        if (item->getType() == what) {
            res.push_back(I->second);
        }
    }
    return res;
}

EntityVector MemMap::findByLocation(const Location & loc, double radius)
// Find an object in our memory in a certain place
{
    EntityVector res;
    EntityDict::const_iterator I;
    for(I = m_entities.begin(); I != m_entities.end(); I++) {
        const Location & oloc = I->second->m_location;
        if (!loc.isValid() || !oloc.isValid()) {
            continue;
        }
        if ((oloc.m_loc->getId() == loc.m_loc->getId()) &&
            (squareDistance(loc.m_pos, oloc.m_pos) < (radius * radius))) {
            res.push_back(I->second);
        }
    }
    return res;
}

const Element MemMap::asObject()
{
    Element::MapType omap;
    EntityDict::const_iterator I = m_entities.begin();
    for(;I != m_entities.end(); I++) {
        I->second->addToObject((omap[I->first] = Element::MapType()).asMap());
    }
    return Element(omap);
}

void MemMap::flush()
{
    EntityDict::const_iterator I = m_entities.begin();
    for (; I != m_entities.end(); I++) {
        delete I->second;
    }
}
