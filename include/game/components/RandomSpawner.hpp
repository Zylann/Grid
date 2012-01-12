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

namespace grid
{
    class RandomSpawner : public RandomEventMaker
    {
    protected :

        util::Shape * m_bounds;
        int m_entityType;
        int m_minSpawn;
        int m_maxSpawn;

    public :

        RandomSpawner(int ID = -1)
        : RandomEventMaker(0, 0, ID)
        {
            m_entityType = -1;
            m_bounds = NULL;
            m_minSpawn = 0;
            m_maxSpawn = 0;
        }

        RandomSpawner(int entityType, util::Shape * bounds,
            float minInterval, float maxInterval,
            int minSpawn, int maxSpawn, int ID = -1)
        : RandomEventMaker(minInterval, maxInterval, ID)
        {
            m_entityType = entityType;
            m_bounds = bounds;
            m_minSpawn = minSpawn >= 0 ? minSpawn : 0;
            m_maxSpawn = maxSpawn >= m_minSpawn ? maxSpawn : m_minSpawn;
        }

        virtual void doEvent(World & world);

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // RANDOMSPAWNER_HPP_INCLUDED
