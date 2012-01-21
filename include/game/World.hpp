/*
Grid
World.hpp

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

#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "utility/AxisAlignedBB.hpp"

#include "game/base/Entity.hpp"
#include "game/RenderManager.hpp"
#include "game/entities/Map.hpp"
#include "game/entities/Player.hpp"
#include "game/Collision.hpp"
#include "game/GameException.hpp"
#include "game/SpaceDivider.hpp"

namespace grid
{
    class World
    {
    protected :

        typedef std::map<int, Entity*> EntityMapping;

        EntityMapping m_entities;       // Active entities
        EntityMapping m_nextEntities;   // entities that will come into play at next update
        entity::Map * r_map;            // Map (2D matrix commonly used for terrains)
        entity::Player * r_localPlayer;  // Local/main player

        Vector2f m_spawnPosition;       // Where players start first
        std::string m_name;             // Name of the world

        RenderManager m_renderManager;
        mutable SpaceDivider m_spaceDivider;

    public :

        World()
        {
            create();
        }

        ~World()
        {
            clear();
        }

        void create()
        {
            clear();
        }

        // Clears all the world's contents to leave it empty
        void clear()
        {
            EntityMapping::iterator it;
            for(it = m_entities.begin(); it != m_entities.end(); it++)
            {
                delete it->second;
                it->second = NULL;
            }
            for(it = m_nextEntities.begin(); it != m_nextEntities.end(); it++)
            {
                delete it->second;
                it->second = NULL;
            }
            m_nextEntities.clear();
            m_entities.clear();
            m_renderManager.clear();
            m_spaceDivider.clear();
            r_map = NULL;
            r_localPlayer = NULL;
        }

        // Adds an entity to the spawn list (nextEntities).
        // These are not effective immediately, until the next update() call.
        int spawnEntity(Entity * e);

        // Same as spawnEntity, by specifying a position (shortcut).
        inline int spawnEntity(Entity * e, const Vector2f & pos)
        {
            e->pos = pos;
            return spawnEntity(e);
        }

        // Adds an entity to the world. It is effective immediately.
        // Important : don't call it from an update during World::update !
        int addEntity(Entity * e);

        // Removes an entity from the world. It is immediately deleted.
        bool eraseEntity(int ID);

        // Returns trus if the specified entity ID is already active or will be active soon.
        bool isEntityExistOrWillSpawn(int ID) const;

        // Returns the amount of active entities
        int getEntityCount();

        // Finds an entity from its ID
        Entity * getEntity(int ID);

        // Finds the local player's entity.
        entity::Player * getLocalPlayer() { return r_localPlayer; }

        // Finds all entities within the specified radius.
        // If it finds e, it is excluded.
        void getEntitiesInRadius(
            std::list<Entity*> & entities,
            const Vector2f & pos, float radius,
            Entity * e = NULL);

        // Gets the name of the world.
        const std::string & getName() const;

        // Sets the name of the world.
        void setName(const std::string & name) { m_name = name; }

        // Tells if there is collisions to e at its position
        bool isCollisions(Entity * e);

        // Get all bounding boxes colliding with box, owned by e.
        void getCollisions(
            std::list<Collision> & collisions,
            const util::AxisAlignedBB & box,
            Entity * e);

        // Sets the spawn's position
        void setSpawnPosition(Vector2f & pos) { m_spawnPosition = pos; }

        // Returns the spawn's position
        const Vector2f & getSpawnPosition() const { return m_spawnPosition; }

        // Returns the map
        entity::Map & getMap() { return *r_map; }

        // Returns the world's space divider
        SpaceDivider & getSpaceDivider() { return m_spaceDivider; }

        // Updates the world for one frame
        void update(GameUpdate & up);

        // Draws the world on the screen
        void render(Graphics & gfx);

        /* Serialization */

        void serialize(std::ostream & os);
        void unserialize(std::istream & is) throw(GameException);

    private :

        // Adds an entity to the world without any checking.
        int addEntityNoCheck(Entity * e);
    };

} // namespace grid


#endif // WORLD_HPP_INCLUDED

