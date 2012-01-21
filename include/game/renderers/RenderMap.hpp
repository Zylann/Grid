/*
Grid
RenderMap.hpp

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

#ifndef RENDERMAP_HPP_INCLUDED
#define RENDERMAP_HPP_INCLUDED

#include "game/base/Renderer.hpp"
#include "game/renderers/RenderMinimap.hpp"
#include "game/Model.hpp"
#include "game/Terrain.hpp"

#include "utility/Exception.hpp"
#include "utility/Buffer2D.hpp"

namespace grid
{
    namespace entity { class Map; }

    struct MapTile
    {
        terrain::Instance data;
        bool borders[4];
        bool upShadow;
        unsigned char light; // [0,16]

        MapTile()
        {
            for(int i = 0; i < 4; i++)
                borders[i] = false;
            upShadow = false;
        }

        MapTile(const entity::Map & map, const Vector2i & pos)
        {
            update(map, pos);
        }

        void update(const entity::Map & map, const Vector2i & pos);

        // Ground and block
        void renderPass1(Graphics & gfx, Vector2i & pos);

        // Shadows and block borders
        void renderPass2(Graphics & gfx, Vector2i & pos);
    };

    class RenderMap : public Renderer
    {
    protected :

        entity::Map * r_map;
        RenderMinimap * m_renderMinimap;
        util::Buffer2D<MapTile> m_tiles;

    public :

        RenderMap(int pass, entity::Map * map);
        virtual ~RenderMap();

        virtual void update();

        void onTerrainChanged(const Vector2i & pos);

        virtual void render(Graphics & gfx);
        virtual void registerRender(RenderManager & renderMgr);

        /* Static methods */

        static void freeTerrainTiles();
        static void createTerrainTiles();

        static Model & getGroundTile(unsigned char ID) throw(util::Exception);
        static Model & getBlockTile(unsigned char ID) throw(util::Exception);
    };

} // namespace grid


#endif // RENDERMAP_HPP_INCLUDED
