/*
Grid
RenderMap.cpp

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

#include "game/renderers/RenderMap.hpp"
#include "game/entities/Map.hpp"

namespace grid
{
    RenderMap::RenderMap(int pass, Map * map) : Renderer(pass)
    {
        r_map = map;
        m_renderMinimap = new RenderMinimap(RP_INTERFACE);
        m_renderMinimap->setMinimapImage(map->getMinimap());
    }

    void RenderMap::update()
    {
        if(r_map == NULL)
            return;

        m_renderMinimap->setMinimapImage(r_map->getMinimap());
    }

    void RenderMap::onTerrainChanged(const Vector2i & pos)
    {
    }

    void RenderMap::registerRender(RenderManager & renderMgr)
    {
        Renderer::registerRender(renderMgr);
        renderMgr.addRender(m_renderMinimap);
    }

    // TODO better map rendering
    void RenderMap::render(Graphics & gfx)
    {
        const sf::View & view = gfx.getCurrentView();
        const sf::FloatRect clip = view.GetRect();
        Vector2i minEdge, maxEdge, pos, up(0, -1);

        sf::Shape shadow;
        shadow.AddPoint(0, 0, sf::Color(0,0,0, 96));
        shadow.AddPoint(1, 0, sf::Color(0,0,0, 96));
        shadow.AddPoint(1, 0.5, sf::Color(0,0,0, 0));
        shadow.AddPoint(0, 0.5, sf::Color(0,0,0, 0));

        float lt = 0.02f;

        sf::Shape wall =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(128, 128, 64), lt,
                                 sf::Color(255, 255, 255, 64));

        sf::Shape dirt =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(128, 64, 32), lt,
                                 sf::Color(255, 255, 255, 64));

        sf::Shape ice =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(0, 192, 192), lt,
                                 sf::Color(0, 0, 0, 64));

        sf::Shape ground =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(64, 64, 64), lt,
                                 sf::Color(0, 0, 0, 64));

        minEdge.x = floor(clip.Left);
        maxEdge.x = floor(clip.Right);
        minEdge.y = floor(clip.Top);
        maxEdge.y = floor(clip.Bottom);

        terrain::Instance t;

        for(pos.x = minEdge.x; pos.x <= maxEdge.x; pos.x++)
        for(pos.y = minEdge.y; pos.y <= maxEdge.y; pos.y++)
        {
            if(!r_map->contains(pos))
                continue;

            t = r_map->getTerrain(pos);

            if(t.blockType == terrain::BT_WALL)
            {
                wall.SetPosition(pos.x, pos.y);
                gfx.draw(wall);
            }
            else if(t.blockType == terrain::BT_DIRT)
            {
                dirt.SetPosition(pos.x, pos.y);
                gfx.draw(dirt);
            }
            else if(t.groundType == terrain::GT_ICE)
            {
                ice.SetPosition(pos.x, pos.y);
                gfx.draw(ice);
            }
            else if(t.groundType == terrain::GT_NORMAL && t.blockType != terrain::BT_VOID)
            {
                ground.SetPosition(pos.x, pos.y);
                gfx.draw(ground);
            }

            // Shadow effect
            if(t.blockType == terrain::BT_EMPTY &&
               r_map->getTerrain(pos + up).blockType != terrain::BT_EMPTY)
            {
                shadow.SetPosition(pos.x, pos.y);
                gfx.draw(shadow);
            }
        }
    }

} // namespace grid



