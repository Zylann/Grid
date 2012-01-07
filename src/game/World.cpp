/*
Grid
World.cpp

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

#include "game/World.hpp"
#include "game/entities/EntityPlayer.hpp"
#include "game/entities/EntityShot.hpp"
#include "game/entities/EntityShockWave.hpp"
#include "game/entities/EntitySentinel.hpp"

using namespace util;

namespace grid
{
    bool World::isEntityExistOrWillSpawn(int ID) const
    {
        // In entities OR in nextEntities
        return m_entities.find(ID) != m_entities.end() ||
           m_nextEntities.find(ID) != m_nextEntities.end();
    }

    int World::spawnEntity(Entity * e, const Vector2f pos)
    {
        // Make sure the ID is unique in the world
        if(isEntityExistOrWillSpawn(e->getID()))
        {
            std::stringstream ss;
            ss << "World::spawnEntity: "
                << "Cannot insert already registered entity " << e->getID();
            Entity * e2 = getEntity(e->getID());
            if(e2 != NULL)
                ss << " (" << e2->name;
            throw(EntityException(ss.str(), e, EntityException::EX_ERROR));
        }

        // Setting position
        e->setPosition(pos);

        // Adding entity to spawn list
        m_nextEntities.insert(std::pair<int, Entity*>( e->getID(), e ));

        return e->getID();
    }

    int World::spawnEntity(Entity * e)
    {
        return spawnEntity(e, e->pos);
    }

    int World::addEntity(Entity * e, const Vector2f pos)
    {
        // Make sure the ID is unique in the world
        if(isEntityExistOrWillSpawn(e->getID()))
        {
            std::stringstream ss;
            ss << "World::addEntity: "
                << "Cannot insert already registered entity " << e->getID();
            throw(EntityException(ss.str(), e, EntityException::EX_ERROR));
        }

        // Inserting entity
        return addEntityNoCheck(e, pos);
    }

    int World::addEntityNoCheck(Entity * e, const Vector2f pos)
    {
        e->setPosition(pos);

        // Inserting
        m_entities.insert(std::pair<int, Entity*>(e->getID(), e));

        // Updating space divider
        if(e->getType() != ENT_MAP)
            m_spaceDivider.addEntity(e);

        // Updating main player reference
        if(e->isPlayer())
            r_mainPlayer = (EntityPlayer*)e;

        //std::cout << e->name << " spawned at (" << pos.x << ", " << pos.y << ")" << std::endl;

        return e->getID();
    }

    int World::getEntityCount()
    {
        return m_entities.size();
    }

    void World::update(GameUpdate & up)
    {
        // Next entities become active
        std::map<int, Entity*>::iterator it;
        for(it = m_nextEntities.begin(); it != m_nextEntities.end(); it++)
        {
            Entity * e = it->second;
            addEntityNoCheck(e, e->pos);
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

    void World::render(Graphics & gfx)
    {
        m_renderManager.clear();

        std::map<int,Entity*>::iterator it;
        for(it = m_entities.begin(); it != m_entities.end(); it++)
        {
            if(it->second->isDrawable())
                it->second->registerRender(m_renderManager);
        }
        m_renderManager.render(gfx);
    }

    bool World::eraseEntity(int ID)
    {
        // Finding entity
        std::map<int, Entity*>::iterator it = m_entities.find(ID);
        if(it != m_entities.end())
        {
            Entity * e = it->second;

            if(r_mainPlayer != NULL)
            {
                if(e->getID() == r_mainPlayer->getID())
                    r_mainPlayer = NULL;
            }

            // Erasing it
            m_spaceDivider.removeEntity(e);
            delete e;
            m_entities.erase(it);
            return true;
        }
        else
        {
            std::cout << "WARNING: World::eraseEntity: "
                << "entity " << ID << " not found" << std::endl;
            return false;
        }
    }

    Entity * World::getEntity(int ID)
    {
        std::map<int, Entity*>::iterator it = m_entities.find(ID);
        if(it != m_entities.end())
            return it->second;
        else
            return NULL;
    }

    void World::getEntitiesInRadius(
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


    bool World::isCollisions(Entity * e)
    {
        if(e->getBoundingBox() == NULL)
            return false;

        // Note : optimizable

        const AxisAlignedBB & box = *(e->getBoundingBox());

        std::list<Collision> collisions;
        getCollisions(collisions, box, e);

        return !collisions.empty();
    }

    void World::getCollisions(
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
        // from the space divider
        static Vector2i divPos;
        Vector2i minDiv = m_spaceDivider.toDivisionCoords(e->pos);
        minDiv.x--;
        minDiv.y--;
        Vector2i maxDiv = minDiv + Vector2i(3, 3);
        std::map<int, Entity*>::const_iterator it;
		SpaceDivision * div = NULL;

		// For performance improvement, we don't look after all entities,
		// but only those who are in the nine divisions around e.
        for(divPos.y = minDiv.y; divPos.y < maxDiv.y; divPos.y++)
        for(divPos.x = minDiv.x; divPos.x < maxDiv.x; divPos.x++)
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

//        // old version
//		  // iterating on all entities
//        std::map<int, Entity*>::const_iterator it;
//        for(it = m_entities.begin(); it != m_entities.end(); it++)
//        {
//            // An entity cannot collide itself
//            if(e == it->second) // adress comparison
//                continue;
//
//            it->second->getCollisions(collisions, box);
//        }
    }

    /*
        Serialization
    */

    void World::serialize(std::ostream & os)
    {
        // World info
        util::serialize(os, m_name);
        util::serialize(os, m_spawnPosition);

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
            // Entity type
            util::serialize(os, it->second->getType());

            // Entity data
            it->second->serialize(os);
        }
    }

    void World::unserialize(std::istream & is) throw(GameException)
    {
        clear();

        // World info
        util::unserialize(is, m_name);
        util::unserialize(is, m_spawnPosition);

        // Entity amount
        uint32 nbEntities = 0;
        util::unserialize(is, nbEntities);

        // Entities
        for(uint32 i = 0; i < nbEntities; i++)
        {
            /* Creating entity from its type */

            int entityType = -1;
            util::unserialize(is, entityType);

            Entity * e = NULL;

            switch(entityType)
            {
                case ENT_MAP :
                    r_map = new Map();
                    e = r_map;
                    break;

                case ENT_PLAYER :
                    e = new EntityPlayer();
                    break;

                case ENT_SENTINEL :
                    e = new EntitySentinel();
                    break;

                case ENT_SHOCKWAVE :
                    e = new EntityShockWave();
                    break;

                case ENT_SHOT :
                    e = new EntityShockWave();
                    break;

                default :
                    std::stringstream ss;
                    ss << "World::unserialize : "
                        << "unknown entity type " << entityType;
                    throw GameException(ss.str());
                    //break;

            } // end switch(entityType)

            /* Unserializing entity */

            try
            {
                e->unserialize(is);
                addEntity(e);
            }
            catch(std::exception & e)
            {
                std::stringstream ss;
                ss << e.what() << std::endl;
                ss << "In World::unserialize";
                throw GameException(ss.str());
            }

        } // end for i < nbEntities
    }

} // namespace grid

