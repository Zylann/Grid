/*
Grid
RandomSpawner.hpp

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

#ifndef RANDOMSPAWNER_HPP_INCLUDED
#define RANDOMSPAWNER_HPP_INCLUDED

#include "common.hpp"
#include "game/components/RandomEventMaker.hpp"
#include "utility/Shape.hpp"

#define SPAWNER_MAX_TRYINGS 5

namespace grid
{
    // T must be an Entity
    template <class T>
    class RandomSpawner : public RandomEventMaker
    {
    protected :

        util::Shape * m_bounds;
        int m_minSpawn;
        int m_maxSpawn;

    public :

        RandomSpawner(util::Shape * bounds,
            float minInterval, float maxInterval,
            int minSpawn, int maxSpawn, int ID = -1)
        : RandomEventMaker(minInterval, maxInterval, ID)
        {
            m_bounds = bounds;
            m_minSpawn = minSpawn >= 0 ? minSpawn : 0;
            m_maxSpawn = maxSpawn >= m_minSpawn ? maxSpawn : m_minSpawn;
        }

        virtual void doEvent(World & world)
        {
            m_bounds->setPosition(r_owner->pos);

            int spawnings = sf::Randomizer::Random(m_minSpawn, m_maxSpawn);

            // For each spawn to do
            for(int i = 0; i < spawnings; i++)
            {
                // Create a new entity
                T * e = new T();

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

        virtual void serialize(std::ostream & os)
        {
            GameObject::serialize(os);
            // TODO serialize RandomSpawner
        }

        virtual void unserialize(std::istream & is)
        {
            GameObject::unserialize(is);

        }
    };

} // namespace grid


#endif // RANDOMSPAWNER_HPP_INCLUDED
