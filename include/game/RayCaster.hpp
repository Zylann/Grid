/*
Grid
RayCaster.hpp

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

#ifndef GRID_RAYCASTER_HPP_INCLUDED
#define GRID_RAYCASTER_HPP_INCLUDED

#include "utility/RayCaster.hpp"
#include "game/entities/Map.hpp"

namespace grid
{
    class RayCaster : public util::RayCaster
    {
    protected :

        entity::Map * r_map;

    public :

        RayCaster(entity::Map * map = NULL) : util::RayCaster()
        {
            r_map = map;
        }

        inline void setMap(entity::Map * map) { r_map = map; }

        virtual bool canPass(Vector2i & pos);
    };

} // namespace grid


#endif // GRID_RAYCASTER_HPP_INCLUDED
