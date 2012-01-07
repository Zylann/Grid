/*
Grid
geometry.cpp

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

#include "utility/geometry.hpp"

namespace util
{
    float distance2D(const Vector2f & A, const Vector2f & B)
    {
        return norm2D(A - B);
    }

    float norm2D(const Vector2f & A)
    {
        return sqrt(A.x * A.x + A.y * A.y);
    }

    float getAngle(const Vector2f & A, const Vector2f & B)
    {
        float d = distance2D(A, B);

        if(d > -0.001 && d < 0.001)
            return 0;

        if(B.y > A.y)
            return acos((B.x - A.x) / d);
        else
            return -acos((B.x - A.x) / d);
    }

    Vector2f getNormalized(const Vector2f & V)
    {
        return V / norm2D(V);
    }

} // namespace util

