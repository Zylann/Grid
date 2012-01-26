/*
Grid
LevelInfo.hpp

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

#ifndef LEVELINFO_HPP_INCLUDED
#define LEVELINFO_HPP_INCLUDED

/* Header-only */

#include "common.hpp"
#include "utility/serialization.hpp"

namespace grid
{
    struct LevelInfo
    {
        std::string name; // Name of the level
        Vector2f spawnPosition; // Where players start first

        LevelInfo() : name("Level") {}
        LevelInfo(const std::string & p_name, const Vector2f & p_spawnPosition)
        {
            name = p_name;
            spawnPosition = p_spawnPosition;
        }

        void serialize(std::ostream & os)
        {
            util::serialize(os, name);
            util::serialize(os, spawnPosition);
        }

        void unserialize(std::istream & is)
        {
            util::unserialize(is, name);
            util::unserialize(is, spawnPosition);
        }

        void print(std::ostream & os)
        {
            os << "LevelInfo {"
                << "name=" << name << ", "
                << "spawnPosition=(" << spawnPosition.x << ", " << spawnPosition.y << ")}";
        }
    };

} // namespace grid


#endif // LEVELINFO_HPP_INCLUDED
