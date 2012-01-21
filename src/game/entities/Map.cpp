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
namespace entity
{
    Map::Map(int ID, Vector2i size) : Entity(ID)
    {
        name = "map";

        r_renderMap = new RenderMap(RP_BACKGROUND, this);
        setRenderer(r_renderMap);

        create(size);
    }

    void Map::create(Vector2i size)
    {
        if(size.x > 0 && size.y > 0)
        {
            m_data.create(util::Area2D(size));
            m_minimap.Create(size.x, size.y, sf::Color(0,0,0));
            m_minimap.SetSmooth(false);

            if(r_renderMap != NULL)
                r_renderMap->update();

            Vector2i pos;
            for(pos.y = 0; pos.y < size.y; pos.y++)
            for(pos.x = 0; pos.x < size.x; pos.x++)
            {
                updateMinimap(pos);
            }
        }
    }

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
            return;

        m_data.setNoEx(pos, t);

        updateMinimap(pos);

        if(r_renderMap != NULL)
            r_renderMap->onTerrainChanged(pos);
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

    void Map::updateMinimap(const Vector2i & pos)
    {
        terrain::Instance t = getTerrain(pos);
        if(t.blockType != terrain::BT_EMPTY && t.blockType != terrain::BT_VOID)
        {
            m_minimap.SetPixel(pos.x, pos.y, t.getBlock().getMinimapColor());
        }
        else if(t.groundType != terrain::GT_VOID)
        {
            m_minimap.SetPixel(pos.x, pos.y, t.getGround().getMinimapColor());
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
            updateMinimap(pos);
        }
        if(m_renderer != NULL)
            m_renderer->update();
    }

} // namespace entity
} // namespace grid

