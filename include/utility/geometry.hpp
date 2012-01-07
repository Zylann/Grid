/*
Grid
geometry.hpp

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

#ifndef GEOMETRY_HPP_INCLUDED
#define GEOMETRY_HPP_INCLUDED

#include <cmath>

#include "common.hpp"

#define ROUNDING_TOLERANCE_FLOAT 0.0001f

namespace util
{
    float distance2D(const Vector2f & A, const Vector2f & B);
    float norm2D(const Vector2f & A);
    float getAngle(const Vector2f & A, const Vector2f & B);
    Vector2f getNormalized(const Vector2f & V);

    inline float toDegrees(const float & t)
    {
        return t * 180.f / M_PI;
    }

    inline bool isZero(const float & a)
    {
        return fabsf(a) <= ROUNDING_TOLERANCE_FLOAT;
    }

} // namespace util


#endif // GEOMETRY_HPP_INCLUDED
