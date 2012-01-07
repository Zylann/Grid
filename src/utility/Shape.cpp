/*
Grid
Shape.cpp

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

#include "utility/Shape.hpp"
#include "utility/geometry.hpp"
#include "utility/Circle.hpp"
#include "utility/AxisAlignedBB.hpp"
#include "utility/Line.hpp"
#include "utility/algebra.hpp"

namespace util
{
    /*
        Static methods
    */

    bool Shape::getCollision(const AxisAlignedBB & B, const Line & L)
    {
        // TODO collision Box/Line (needed first)
        return false;
    }

    bool Shape::getCollision(const AxisAlignedBB & B, const Circle & C)
    {
        // TODO collision Box/Circle
        return false;
    }

    bool Shape::getCollision(const Circle & C, const Line & L)
    {
        // Method used :
        // http://paulbourke.net/geometry/sphereline/

        const float numerator =
            (C.center.x - L.start.x) * (L.end.x - L.start.x) +
            (C.center.y - L.start.y) * (L.end.y - L.start.y);

        const float denominator =
            square<float>(L.end.x - L.start.x) +
            square<float>(L.end.y - L.start.y);

        if(!isZero(denominator))
        {
            const float u = numerator / denominator;
            if(u > 0 && u < 1)
            {
                Vector2f P = L.start + u * (L.end - L.start);
                return distance2D(P, C.center) < C.radius;
            }
        }
        return false;

        // Method for an infinite line
        //        const float a =
        //            square(L.end.x - L.start.x) + square(L.end.y - L.start.y);
        //
        //        const float b =
        //            2.0f * ((L.end.x - L.start.x) * (L.start.x - C.center.x) +
        //                    (L.end.y - L.start.y) * (L.start.y - C.center.y));
        //
        //        const float c =
        //            square(C.center.x) + square(C.center.y) +
        //            square(L.start.x) + square(L.start.y) -
        //            2 * (C.center.x * L.start.x + C.center.y * L.start.y) - r*r;
        //
        //        return b * b - 4 * a * c > 0;
    }

} // namespace util

