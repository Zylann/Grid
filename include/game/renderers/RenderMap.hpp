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

namespace grid
{
    class Map;

    class RenderMap : public Renderer
    {
    protected :

        Map * r_map;

    public :

        RenderMap(int pass, Map * map) : Renderer(pass)
        {
            r_map = map;
        }

        virtual void update()
        {}

        virtual void render(Graphics & gfx);
    };

} // namespace grid


#endif // RENDERMAP_HPP_INCLUDED
