/*
Grid
Level.cpp

Copyright (c) 2011 by Marc Gilleron, <marc.gilleron@free.fr>

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sstream>

#include "utility/AxisAlignedBB.hpp"
#include "utility/serialization.hpp"
#include "utility/geometry.hpp"

#include "game/Level.hpp"
#include "game/entities/Player.hpp"
#include "game/entities/Shot.hpp"
#include "game/entities/ShockWave.hpp"
#include "game/entities/Sentinel.hpp"

using namespace util;

namespace grid
{
    bool Level::isEntityExistOrWillSpawn(int ID) const
    {
        // In entities OR in nextEntities
        return m_entities.find(ID) != m_entities.end() ||
           m_nextEntities.find(ID) != m_nextEntities.end();
    }

    int Level::spawnEntity(Entity * e)
    {
        // Make sure the ID is unique in the level
        if(isEntityExistOrWillSpawn(e->getID()))
        {
            std::stringstream ss;
            ss << "Level::spawnEntity: "
                << "Cannot insert already registered entity " << e->getID();
            Entity * e2 = getEntity(e->getID());
            if(e2 != NULL)
                ss << " (" << e2->name;
            throw(EntityException(ss.str(), e, EntityException::EX_ERROR));
        }

        // Adding entity to spawn list
        m_nextEntities.insert(std::pair<int, Entity*>( e->getID(), e ));

        return e->getID();
    }

    int Level::addEntity(Entity * e)
    {
        // Make sure the ID is unique in the level
        if(isEntityExistOrWillSpawn(e->getID()))
        {
            std::stringstream ss;
            ss << "Level::addEntity: "
                << "Cannot insert already registered entity " << e->getID();
            throw(EntityException(ss.str(), e, EntityException::EX_ERROR));
        }

        // Inserting entity
        return addEntityNoCheck(e);
    }

    int Level::addEntityNoCheck(Entity * e)
    {
        e->setLevel(this);

        // Inserting
        m_entities.insert(std::pair<int, Entity*>(e->getID(), e));

        // Updating space divider
        if(e->getType() != ENT_MAP)
            m_spaceDivider.addEntity(e);

        // Updating main player reference
        if(e->isPlayer())
            r_localPlayer = (entity::Player*)e;

        // Updating map unicity
        if(e->getType() == ENT_MAP)
        {
            std::cout << "WARNING: Level::addEntityNoCheck:"
                << " a map entity is already registered" << std::endl;
            if(r_map != NULL)
                eraseEntity(r_map->getID());
            r_map = (entity::Map*)e;
        }
        return e->getID();
    }

    int Level::getEntityCount()
    {
        return m_entities.size();
    }

    void Level::update(GameUpdate & up)
    {
        // Next entities become active
        std::map<int, Entity*>::iterator it;
        for(it = m_nextEntities.begin(); it != m_nextEntities.end(); it++)
        {
            Entity * e = it->second;
            addEntityNoCheck(e);
        }
        m_nextEntities.clear();

        std::list<int> invalid;
        std::list<int>::iterator itInv;
        Entity * e = NULL;

        // Updating
        for(it = m_entities.begin(); it != m_entities.end(); it++)
        {
            e = it->second;
            e->update(up);
            m_spaceDivider.updateEntityDivision(e);

            if(!e->isValid())
            {
                invalid.push_back(e->getID());
                e->onDestruction(up);
            }
        }
        // Removing invalid entities
        for(itInv = invalid.begin(); itInv != invalid.end(); itInv++)
        {
            eraseEntity(*itInv);
        }
    }

    void Level::render(Graphics & gfx)
    {
        m_renderManager.clear();

        if(r_map != NULL)
            r_map->registerRender(m_renderManager);

        const sf::FloatRect & viewRect = gfx.getCurrentView().GetRect();
        AxisAlignedBB clipBox(viewRect.Left, viewRect.Top, viewRect.Right, viewRect.Bottom);

        std::list<SpaceDivision*> divs;
        m_spaceDivider.getDivisionsFromBox(divs, clipBox);

        std::list<SpaceDivision*>::iterator it1;
        std::map<int,Entity*>::iterator it2;
        Entity * e;
        SpaceDivision * div;

        // Only render entities of space divisions within the view clippig rectangle
        for(it1 = divs.begin(); it1 != divs.end(); it1++)
        {
            div = *it1;
            for(it2 = div->entities.begin(); it2 != div->entities.end(); it2++)
            {
                e = it2->second;
                if(e->isDrawable() && e->getType() != ENT_MAP)
                    e->registerRender(m_renderManager);
            }
        }
        m_renderManager.render(gfx);
    }

    bool Level::eraseEntity(int ID)
    {
        // Finding entity
        std::map<int, Entity*>::iterator it = m_entities.find(ID);
        if(it != m_entities.end())
        {
            Entity * e = it->second;

            if(r_localPlayer != NULL)
            {
                if(e->getID() == r_localPlayer->getID())
                    r_localPlayer = NULL;
            }

            // Erasing it
            m_spaceDivider.removeEntity(e);
            delete e;
            m_entities.erase(it);
            return true;
        }
        else
        {
            std::cout << "WARNING: Level::eraseEntity: "
                << "entity " << ID << " not found" << std::endl;
            return false;
        }
    }

    Entity * Level::getEntity(int ID)
    {
        std::map<int, Entity*>::iterator it = m_entities.find(ID);
        if(it != m_entities.end())
            return it->second;
        else
            return NULL;
    }

    void Level::getEntitiesInRadius(
        std::list<Entity*> & entities,
        const Vector2f & pos, float radius, Entity * e)
    {
        // TODO use the space divider with a circular intersection
        // iterating on all entities
        std::map<int, Entity*>::const_iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); it++)
        {
            // Except e
            if(e == it->second) // adress comparison
                continue;

            if(distance2D(it->second->pos, pos) <= radius)
                entities.push_back(it->second);
        }
    }


    bool Level::isCollisions(Entity * e)
    {
        if(e->getBoundingBox() == NULL)
            return false;

        // Note : optimizable

        const AxisAlignedBB & box = *(e->getBoundingBox());

        std::list<Collision> collisions;
        getCollisions(collisions, box, e);

        return !collisions.empty();
    }

    void Level::getCollisions(
        std::list<Collision> & collisions,
        const AxisAlignedBB & box,
        Entity * e)
    {
        /* Searching for map collisions*/

		// Note : the map is not stored in the space divider (see below),
		// so we compute map collisions before
        r_map->getCollisions(collisions, box);

        /* Searching for entity collisions */

        // TODO use the bounding box to get less divisions
        // Computing space division area
        static Vector2i divPos;
        Vector2i minDiv = m_spaceDivider.toDivisionCoords(e != NULL ? e->pos : box.getCenter());
        minDiv.x--;
        minDiv.y--;
        Vector2i maxDiv = minDiv + Vector2i(2, 2);
        std::map<int, Entity*>::const_iterator it;
		SpaceDivision * div = NULL;

		// Iterating on found divisions :
		// For performance improvement, we don't look after all entities,
		// but only those who are in divisions around e.
        for(divPos.y = minDiv.y; divPos.y <= maxDiv.y; divPos.y++)
        for(divPos.x = minDiv.x; divPos.x <= maxDiv.x; divPos.x++)
        {
			div = m_spaceDivider.getDivision(divPos, false);

            if(div == NULL)
                continue;

            for(it = div->entities.begin(); it != div->entities.end(); it++)
            {
                // An entity cannot collide itself
                if(e == it->second) // adress comparison
                    continue;
                it->second->getCollisions(collisions, box);
            }
        }
    }

    /*
        Serialization
    */

    void Level::serialize(std::ostream & os)
    {
        // Level info
        m_levelInfo.serialize(os);

        // Serializable entity amount
        uint32 nbEntities = 0;
        std::map<int, Entity*>::iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); it++)
        {
            if(it->second->isSerializable())
                nbEntities++;
        }

        util::serialize(os, nbEntities);

        // Entities
        for(it = m_entities.begin(); it != m_entities.end(); it++)
        {
            Entity::serializeEntity(os, *(it->second));
        }
    }

    void Level::unserialize(std::istream & is) throw(GameException)
    {
        clear();

        // Level info
        m_levelInfo.unserialize(is);

        // Entity amount
        uint32 nbEntities = 0;
        util::unserialize(is, nbEntities);

        // Entities
        for(uint32 i = 0; i < nbEntities; i++)
        {
            Entity * e = NULL;

            /* Unserializing entity */

            try
            {
                e = Entity::unserializeEntity(is);
                addEntity(e);
            }
            catch(std::exception & e)
            {
                std::stringstream ss;
                ss << e.what() << std::endl;
                ss << "In Level::unserialize";
                throw GameException(ss.str());
            }

        } // end for i < nbEntities
    }

} // namespace grid

