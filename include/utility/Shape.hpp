/*
Grid
Shape.hpp

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

#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include "common.hpp"

namespace util
{
    class AxisAlignedBB;
    class Circle;
    class Line;

    class Shape
    {
    public :

        static bool getCollision(const AxisAlignedBB & B, const Line & L);
        static bool getCollision(const AxisAlignedBB & B, const Circle & C);
        static bool getCollision(const Circle & C, const Line & L);

        virtual void offset(const Vector2f & off) = 0;
        virtual float getMaxRadius() const = 0;

        // Set position of the shape (may differ a bit in specializations)
        virtual void setPosition(const Vector2f & pos) = 0;

        // get a random point in the shape
        virtual Vector2f getRandomPoint() const = 0;

        virtual bool collides(const Line & L) const = 0;
        virtual bool collides(const Circle & C) const = 0;
        virtual bool collides(const AxisAlignedBB & B) const = 0;

        virtual void print(std::ostream & os) = 0;
    };

} // namespace util


#endif // SHAPE_HPP_INCLUDED
