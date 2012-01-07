/*
Grid
Map.cpp

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

#include "game/entities/Map.hpp"
#include "utility/serialization.hpp"

namespace grid
{
    terrain::Instance Map::getTerrain(const Vector2i & pos) const
    {
        if(m_data.getArea().valid(pos))
            return m_data.getNoEx(pos);
        else
            return terrain::Instance(terrain::GT_VOID, terrain::BT_VOID);
    }

    void Map::setTerrain(const Vector2i & pos, terrain::Instance t)
    {
        if(!m_data.getArea().valid(pos))
        {
            return;
        }
        m_data.setNoEx(pos, t);
    }

    void Map::getCollisions(
        std::list<Collision>& collisions,
        const util::AxisAlignedBB& box)
    {
        // area
        Vector2i minEdge(
            floor(box.minEdge.x),
            floor(box.minEdge.y));

        Vector2i maxEdge(
            floor(box.maxEdge.x),
            floor(box.maxEdge.y));

        unsigned char b;

        // get collisions in area
        Vector2i pos;
        for(pos.x = minEdge.x; pos.x <= maxEdge.x; pos.x++)
        {
            for(pos.y = minEdge.y; pos.y <= maxEdge.y; pos.y++)
            {
                b = getTerrain(pos).blockType;
                const terrain::Block & bp = terrain::Block::get(b); // get properties
                bp.getCollisions(collisions, box, pos);
            }
        }
    }

    void Map::updateMe(GameUpdate & up)
    {
    }

    void Map::clear()
    {
        m_data.clear();
    }

    /*
        Serialization
    */

    void Map::serialize(std::ostream & os)
    {
        Entity::serialize(os);

        Vector2i size = m_data.getArea().getSize();
        util::serialize(os, size);

        Vector2i pos;
        for(pos.y = 0; pos.y < size.y; pos.y++)
        for(pos.x = 0; pos.x < size.x; pos.x++)
        {
            m_data.getNoEx(pos).serialize(os);
        }
    }

    void Map::unserialize(std::istream & is)
    {
        clear();

        Entity::unserialize(is);

        Vector2i size;
        util::unserialize(is, size);

        create(size);

        Vector2i pos;
        terrain::Instance t;
        for(pos.y = 0; pos.y < size.y; pos.y++)
        for(pos.x = 0; pos.x < size.x; pos.x++)
        {
            t.unserialize(is);
            m_data.setNoEx(pos, t);
        }
    }

} // namespace grid

