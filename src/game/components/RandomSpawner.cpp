/*
Grid
RandomSpawner.cpp

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

#include "game/components/RandomSpawner.hpp"
#include "game/base/Entity.hpp"
#include "game/World.hpp"

#include "utility/Shape.hpp"

#define SPAWNER_MAX_TRYINGS 5

using namespace util;

namespace grid
{
    void RandomSpawner::doEvent(World & world)
    {
        m_bounds->setPosition(r_owner->pos);

        int spawnings = sf::Randomizer::Random(m_minSpawn, m_maxSpawn);

        // For each spawn to do
        for(int i = 0; i < spawnings; i++)
        {
            // Create a new entity
            Entity * e = Entity::createEntityFromType(m_entityType);
            if(e == NULL)
            {
                std::cout << "WARNING: RandomSpawner::doEvent:"
                    << "cannot spawn entity from type " << m_entityType << std::endl;
                return;
            }

            // Try to spawn it
            for(int j = 0; j < SPAWNER_MAX_TRYINGS; j++)
            {
                // At a random position into bounds
                e->pos = m_bounds->getRandomPoint();

                // Test if there is collisions at this position
                if(!world.isCollisions(e))
                {
                    // If success, spawn e
                    world.spawnEntity(e);
                    e = NULL;
                    break; // And continue to next spawn
                }
            }
            // If e is not NULL, it means that we didn't found a place to spawn e.
            if(e != NULL)
            {
                delete e;
                e = NULL;
            }
        }
    }

    /*
        Serialization
    */

    void RandomSpawner::serialize(std::ostream & os)
    {
        RandomEventMaker::serialize(os);

        Shape::serializeShape(os, *m_bounds);
        util::serialize(os, m_entityType);
        util::serialize(os, m_minSpawn);
        util::serialize(os, m_maxSpawn);
    }

    void RandomSpawner::unserialize(std::istream & is)
    {
        RandomEventMaker::unserialize(is);

        if(m_bounds != NULL)
            delete m_bounds;
        m_bounds = NULL;

        m_bounds = Shape::unserializeShape(is);

        util::unserialize(is, m_entityType);
        util::unserialize(is, m_minSpawn);
        util::unserialize(is, m_maxSpawn);
    }

} // namespace grid

