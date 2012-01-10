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
#include "game/entities/EntityPlayer.hpp"
#include "game/Collision.hpp"
#include "game/GameException.hpp"
#include "game/SpaceDivider.hpp"

namespace grid
{
    class World
    {
    protected :

        typedef std::map<int, Entity*> EntityMapping;

        EntityMapping m_entities;
        EntityMapping m_nextEntities;
        Map * r_map;
        EntityPlayer * r_mainPlayer;

        Vector2f m_spawnPosition;
        std::string m_name;

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

            r_map = new Map();
            addEntity(r_map);
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
            r_mainPlayer = NULL;
        }

        // Adds an entity to the spawn list (nextEntities).
        // These are not effective immediately, until the next update() call.
        int spawnEntity(Entity * e, const Vector2f pos);
        int spawnEntity(Entity * e);

        // Adds an entity to the world. It is effective immediately.
        // Important : don't call it from an update during World::update !
        int addEntity(Entity * e, const Vector2f pos = Vector2f());

        // Removes an entity from the world. It is immediately deleted.
        bool eraseEntity(int ID);

        // Returns trus if the specified entity ID is already active or will be active soon.
        bool isEntityExistOrWillSpawn(int ID) const;

        int getEntityCount();
        Entity * getEntity(int ID);
        EntityPlayer * getMainPlayer() { return r_mainPlayer; }

        void getEntitiesInRadius(
            std::list<Entity*> & entities,
            const Vector2f & pos, float radius,
            Entity * e = NULL);

        const std::string & getName() const;
        void setName(const std::string & name) { m_name = name; }

        // Tells if there is collisions to e at its position
        bool isCollisions(Entity * e);

        // Get all bounding boxes colliding with box, owned by e.
        void getCollisions(
            std::list<Collision> & collisions,
            const util::AxisAlignedBB & box,
            Entity * e);

        void setSpawnPosition(Vector2f & pos) { m_spawnPosition = pos; }
        const Vector2f & getSpawnPosition() const { return m_spawnPosition; }

        Map & getMap() { return *r_map; }
        SpaceDivider & getSpaceDivider() { return m_spaceDivider; }

        void update(GameUpdate & up);
        void render(Graphics & gfx);

        /* Serialization */

        void serialize(std::ostream & os);
        void unserialize(std::istream & is) throw(GameException);

    private :

        // Adds an entity to the world without any checking.
        int addEntityNoCheck(Entity * e, const Vector2f pos = Vector2f());
    };

} // namespace grid


#endif // WORLD_HPP_INCLUDED

