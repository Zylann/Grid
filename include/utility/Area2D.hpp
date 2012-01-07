/*
Grid
Area2D.hpp

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

#ifndef AREA2D_HPP_INCLUDED
#define AREA2D_HPP_INCLUDED

#include "common.hpp"

namespace util
{
    class Area2D
    {
    private :

        Vector2i m_size;
        Vector2i m_pos;

    public :

        Area2D();

        // constructs the area from a size. Position is (0,0).
        Area2D(const Vector2i & newSize);

        // constructs the area from a position and a size.
        Area2D(const Vector2i & newPos, const Vector2i & newSize);

        // get area's size
        inline const Vector2i & getSize() const { return m_size; }

        // get area's position
        inline const Vector2i & getPosition() const { return m_pos; }

        // sets area's position
        void setPosition(const Vector2i & newPos) { m_pos = newPos; }

        // sets area's size, with checking (no negative values)
        void setSize(const Vector2i & newSize);

        // sets area's size from minimum and maximum edges
        void setBounds(const Vector2i & minEdge, const Vector2i & maxEdge);

        // tells if a point is included in the area
        bool valid(const Vector2i & pos) const;

        // tells if another Area2D is included in the area
        // it will return false if the other is
        bool contains(const Area2D & other) const;

        // tells if a point is included in the area without look the position
        bool validRelative(const Vector2i & pos) const;

        // get minimum edge
        Vector2i getMinEdge() const;

        // get maximum edge
        Vector2i getMaxEdge() const;

        // resets the area
        void clear();

        // prevents the area to be defined with negative size
        void correct();

        // expands or reduce the area's size
        void expand(int px, int py);

        // converts area's information into a string
        void print(std::ostream & os) const;

        // get area's volume (always >= 0)
        int getVolume() const;

        /*
            These functions below are used with 2D buffers using linear data storage.
        */

        // get linear index using the position
        int index(const Vector2i & p_pos) const;

        // get linear index without use the position
        int relativeIndex(const Vector2i & p_pos) const;
    };

} // namespace util


#endif // AREA2D_HPP_INCLUDED
