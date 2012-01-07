/*
Grid
PathFinder.cpp

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

#include "game/PathFinder.hpp"

#define GRID_PATHFINDER_STEPS 1
#define GRID_PATHFINDER_TIME 1.f

namespace grid
{
    // Virtual
    bool PathFinder::canPass(const Vector2i & pos)
    {
        if(r_map == NULL)
            return false;

        terrain::Instance t = r_map->getTerrain(pos);
        terrain::Block & bp = terrain::Block::get(t.blockType);

        return bp.isCrossable();
    }

} // namespace grid

