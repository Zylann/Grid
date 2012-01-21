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

using namespace util;

namespace grid
{
    /*
        Global vars
    */

    enum Direction2D
    {
        DIR_WEST = 0, // keep 0
        DIR_EAST,
        DIR_SOUTH,
        DIR_NORTH
    };

    // According to a -y repere
    Vector2i g_dirs[4] =
    {
        Vector2i(-1, 0), // EAST
        Vector2i(1, 0),  // WEST
        Vector2i(0, 1),  // SOUTH
        Vector2i(0, -1), // NORTH
    };

    // Terrain models
    Model g_groundTiles[terrain::GT_COUNT];
    Model g_blockTiles[terrain::BT_COUNT];
    sf::Shape shadow;

    #define BORDERLINE_THICKNESS 0.05f
    #define BORDERLINE_COLOR sf::Color(0,0,0)
    // According to a -y repere
    sf::Shape g_borderLines[4] =
    {
        sf::Shape::Line(0, 0, 0, 1, BORDERLINE_THICKNESS, BORDERLINE_COLOR), // EAST
        sf::Shape::Line(1, 0, 1, 1, BORDERLINE_THICKNESS, BORDERLINE_COLOR), // WEST
        sf::Shape::Line(0, 1, 1, 1, BORDERLINE_THICKNESS, BORDERLINE_COLOR), // SOUTH
        sf::Shape::Line(0, 0, 1, 0, BORDERLINE_THICKNESS, BORDERLINE_COLOR)  // NORTH
    };

    /*
        RenderMap static methods
    */

    void RenderMap::freeTerrainTiles()
    {
        for(int i = 0; i < terrain::GT_COUNT; i++)
        {
            g_groundTiles[i].clear();
        }
        for(int i = 0; i < terrain::BT_COUNT; i++)
        {
            g_blockTiles[i].clear();
        }
        shadow = sf::Shape();
    }

    void RenderMap::createTerrainTiles()
    {
        freeTerrainTiles();

        float lt = 0;

        // New models for terrain types must be stored here

        /* Grounds */

        g_groundTiles[terrain::GT_NORMAL].addShape( new sf::Shape(
            sf::Shape::Rectangle(0, 0, 1, 1,
                                 sf::Color(96, 96, 96, 224), lt,
                                 sf::Color(0, 0, 0, 64)) ));

        g_groundTiles[terrain::GT_ICE].addShape( new sf::Shape(
            sf::Shape::Rectangle(0, 0, 1, 1,
                                 sf::Color(0, 192, 192), lt,
                                 sf::Color(0, 0, 0, 64)) ));

        /* Blocks */

        g_blockTiles[terrain::BT_DIRT].addShape( new sf::Shape(
            sf::Shape::Rectangle(0, 0, 1, 1,
                                 sf::Color(32, 32, 64), lt,
                                 sf::Color(255, 255, 255, 64)) ));

        g_blockTiles[terrain::BT_WALL].addShape( new sf::Shape(
            sf::Shape::Rectangle(0, 0, 1, 1,
                                 sf::Color(32, 32, 32), lt,
                                 sf::Color(255, 255, 255, 64)) ));

        /* Up shadow */

        shadow.AddPoint(0, 0, sf::Color(0,0,0, 128));
        shadow.AddPoint(1, 0, sf::Color(0,0,0, 128));
        shadow.AddPoint(1, 0.5, sf::Color(0,0,0, 0));
        shadow.AddPoint(0, 0.5, sf::Color(0,0,0, 0));
    }

    Model & RenderMap::getGroundTile(unsigned char ID) throw(Exception)
    {
        if(ID >= terrain::GT_COUNT)
        {
            std::stringstream ss;
            ss << "getGroundTile: invalid ID=" << (int)ID;
            throw Exception(ss.str(), Exception::EX_ERROR);
        }
        return g_groundTiles[ID];
    }

    Model & RenderMap::getBlockTile(unsigned char ID) throw(Exception)
    {
        if(ID >= terrain::BT_COUNT)
        {
            std::stringstream ss;
            ss << "getBlockTile: invalid ID=" << (int)ID;
            throw Exception(ss.str(), Exception::EX_ERROR);
        }
        return g_blockTiles[ID];
    }

    /*
        MapTile
    */

	void MapTile::update(const entity::Map & map, const Vector2i & pos)
	{
		data = map.getTerrain(pos);

        // No need to update a void terrain
		if(data.isVoid())
            return;

		terrain::Instance t;

        // If there is a block on the ground
        if(data.blockType != terrain::BT_EMPTY)
        {
            // Finding border lines
            for(int i = 0; i < 4; i++)
            {
                t = map.getTerrain(pos + g_dirs[i]);
                borders[i] = t.blockType == terrain::BT_EMPTY;
            }
        }
        else
        {
            // No borders
            for(int i = 0; i < 4; i++)
                borders[i] = false;
        }

        // Getting the terrain above
		t = map.getTerrain(pos + g_dirs[DIR_NORTH]);

		// Shadow of the block above
        if(data.blockType == terrain::BT_EMPTY &&
           t.blockType != terrain::BT_EMPTY && !t.isVoid())
        {
            upShadow = true;
        }
        else
            upShadow = false;
    }

	// Ground and block
	void MapTile::renderPass1(Graphics & gfx, Vector2i & pos)
	{
	    if(data.isVoid())
            return;

	    const Vector2f fpos(pos.x, pos.y);
	    if( data.blockType != terrain::BT_EMPTY &&
            data.blockType != terrain::BT_VOID)
        {
            Model & m = RenderMap::getBlockTile(data.blockType);
            m.setPosition(fpos);
            gfx.draw(m);
        }
        else if(data.groundType != terrain::GT_VOID)
        {
            Model & m = RenderMap::getGroundTile(data.groundType);
            m.setPosition(fpos);
            gfx.draw(m);
        }
	}

	// Shadows and block borders
	void MapTile::renderPass2(Graphics & gfx, Vector2i & pos)
	{
	    const Vector2f fpos(pos.x, pos.y);

	    // Drawing border lines
	    for(unsigned char i = 0; i < 4; i++)
	    {
	        if(borders[i])
	        {
	            g_borderLines[i].SetPosition(fpos);
	            gfx.draw(g_borderLines[i]);
	        }
	    }
        // Drawing shadow of the block above
        if(upShadow)
        {
            shadow.SetPosition(fpos);
            gfx.draw(shadow);
        }
	}

    /*
        RenderMap member methods
    */

    RenderMap::RenderMap(int pass, entity::Map * map) : Renderer(pass)
    {
        r_map = map;
        m_renderMinimap = new RenderMinimap(RP_INTERFACE);
        m_renderMinimap->setMinimapImage(map->getMinimap());

        createTerrainTiles();

        update();
    }

    RenderMap::~RenderMap()
    {
        delete m_renderMinimap;
    }

    void RenderMap::update()
    {
        if(r_map == NULL)
            return;

        // If the map size changed, create and update all tiles
        if(m_tiles.getArea().getSize() != r_map->getSize())
        {
            m_tiles.create(Area2D(r_map->getSize()));

            const Vector2i & size = m_tiles.getArea().getSize();
            Vector2i pos;

            for(pos.y = 0; pos.y < size.y; pos.y++)
            for(pos.x = 0; pos.x < size.x; pos.x++)
            {
                onTerrainChanged(pos);
            }
        }

        // Update minimap's reference image
        m_renderMinimap->setMinimapImage(r_map->getMinimap());
    }

    void RenderMap::onTerrainChanged(const Vector2i & pos)
    {
        // Don't update if the position is outside the map
        if(!m_tiles.getArea().valid(pos) || r_map == NULL)
            return;

        // Update the tile
        m_tiles.getRefNoEx(pos).update(*r_map, pos);

        // And its neighbors
        Vector2i npos;
        for(int i = 0; i < 4; i++)
        {
            npos = pos + g_dirs[i];
            if(m_tiles.getArea().valid(npos))
                m_tiles.getRefNoEx(npos).update(*r_map, npos);
        }
    }

    void RenderMap::registerRender(RenderManager & renderMgr)
    {
        Renderer::registerRender(renderMgr);
        renderMgr.addRender(m_renderMinimap);
    }

    void RenderMap::render(Graphics & gfx)
    {
        update();

        const sf::View & view = gfx.getCurrentView();
        Vector2i minEdge, maxEdge, pos;
        const sf::FloatRect clip = view.GetRect();

        // Finding view clipping
        minEdge.x = floor(clip.Left);
        maxEdge.x = floor(clip.Right);
        minEdge.y = floor(clip.Top);
        maxEdge.y = floor(clip.Bottom);

        terrain::Instance t;

        // First pass
        for(pos.y = minEdge.y; pos.y <= maxEdge.y; pos.y++)
        for(pos.x = minEdge.x; pos.x <= maxEdge.x; pos.x++)
        {
            if(!m_tiles.getArea().valid(pos))
                continue;
            m_tiles.getRefNoEx(pos).renderPass1(gfx, pos);
        }
        // Second pass
        for(pos.y = minEdge.y; pos.y <= maxEdge.y; pos.y++)
        for(pos.x = minEdge.x; pos.x <= maxEdge.x; pos.x++)
        {
            if(!m_tiles.getArea().valid(pos))
                continue;
            m_tiles.getRefNoEx(pos).renderPass2(gfx, pos);
        }
    }

} // namespace grid



