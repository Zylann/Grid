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

#include "utility/noise.hpp"

namespace grid
{
    RenderMap::RenderMap(int pass, entity::Map * map) : Renderer(pass)
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
    // the method used must be replaced by simpler OpenGL calls.
    void RenderMap::render(Graphics & gfx)
    {
        const sf::View & view = gfx.getCurrentView();
        const sf::FloatRect clip = view.GetRect();
        Vector2i minEdge, maxEdge, pos, up(0, -1), down(0, 1), left(-1, 0), right(1, 0);

        sf::Shape shadow;
        shadow.AddPoint(0, 0, sf::Color(0,0,0, 128));
        shadow.AddPoint(1, 0, sf::Color(0,0,0, 128));
        shadow.AddPoint(1, 0.5, sf::Color(0,0,0, 0));
        shadow.AddPoint(0, 0.5, sf::Color(0,0,0, 0));

        float lt = 0;//0.02f;

        static sf::Shape wall =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(32, 32, 32), lt,
                                 sf::Color(255, 255, 255, 64));

        static sf::Shape dirt =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(32, 32, 64), lt,
                                 sf::Color(255, 255, 255, 64));

        static sf::Shape ice =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(0, 192, 192), lt,
                                 sf::Color(0, 0, 0, 64));

        static sf::Shape ground =
            sf::Shape::Rectangle(pos.x, pos.y, pos.x+1, pos.y+1,
                                 sf::Color(96, 96, 96), lt,
                                 sf::Color(0, 0, 0, 64));

        float bt = 0.05;
        sf::Color bc(0,0,0);
        static sf::Shape lineLeft =
            sf::Shape::Line(0, 0, 0, 1, bt, bc);
        static sf::Shape lineRight =
            sf::Shape::Line(1, 0, 1, 1, bt, bc);
        static sf::Shape lineTop =
            sf::Shape::Line(0, 0, 1, 0, bt, bc);
        static sf::Shape lineBottom =
            sf::Shape::Line(0, 1, 1, 1, bt, bc);

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
                int n = 240 + 15 * util::noise2d(pos.x, pos.y, 131183);
                ground.SetColor(sf::Color(n, n, n));
                ground.SetPosition(pos.x, pos.y);


                gfx.draw(ground);
            }

            // Shadow effect
            if(t.blockType == terrain::BT_EMPTY &&
               r_map->getTerrain(pos + up).blockType != terrain::BT_EMPTY &&
               r_map->getTerrain(pos + up).blockType != terrain::BT_VOID)
            {
                shadow.SetPosition(pos.x, pos.y);
                gfx.draw(shadow);
            }
        }

        for(pos.x = minEdge.x; pos.x <= maxEdge.x; pos.x++)
        for(pos.y = minEdge.y; pos.y <= maxEdge.y; pos.y++)
        {
            if(!r_map->contains(pos))
                continue;
            t = r_map->getTerrain(pos);

            // Lines
            if(!t.getBlock().isCrossable())
            {
                if(r_map->getTerrain(pos + left).getBlock().isCrossable())
                {
                    lineLeft.SetPosition(pos.x, pos.y);
                    gfx.draw(lineLeft);
                }
                if(r_map->getTerrain(pos + right).getBlock().isCrossable())
                {
                    lineRight.SetPosition(pos.x, pos.y);
                    gfx.draw(lineRight);
                }
                if(r_map->getTerrain(pos + up).getBlock().isCrossable())
                {
                    lineTop.SetPosition(pos.x, pos.y);
                    gfx.draw(lineTop);
                }
                if(r_map->getTerrain(pos + down).getBlock().isCrossable())
                {
                    lineBottom.SetPosition(pos.x, pos.y);
                    gfx.draw(lineBottom);
                }
            }
        }
    }

} // namespace grid



