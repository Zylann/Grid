/*
Grid
Line.cpp

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

#include "utility/Line.hpp"
#include "utility/geometry.hpp"

namespace util
{
    void Line::offset(const Vector2f & off)
    {
        start += off;
        end += off;
    }

    float Line::getMaxRadius() const
    {
        return getLength();
    }

    float Line::getLength() const
    {
        return distance2D(start, end);
    }

    bool Line::collides(const Line & L) const
    {
        // Note : the method used can also be used to find
        // the intersection point (not currently used).

        // Uses the method given at:
        // http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
        const float commonDenominator =
            (L.end.y - L.start.y) * (end.x - start.x) -
            (L.end.x - L.start.x) * (end.y - start.y);

        const float numeratorA =
            (L.end.x - L.start.x) * (start.y - L.start.y) -
            (L.end.y - L.start.y) * (start.x -L.start.x);

        const float numeratorB =
            (end.x - start.x) * (start.y - L.start.y) -
            (end.y - start.y) * (start.x -L.start.x);

        if(isZero(commonDenominator))
        {
            // The lines are either coincident or parallel
            // if both numerators are 0, the lines are coincident
            return isZero(numeratorA) && isZero(numeratorB);
        }
        return false;
    }

    bool Line::collides(const Circle & C) const
    {
        return Shape::getCollision(C, *this);
    }

    bool Line::collides(const AxisAlignedBB & B) const
    {
        return Shape::getCollision(B, *this);
    }

    void Line::print(std::ostream & os)
    {
        os << "{ start=(" << start.x << ", " << start.y << "), "
            << "end=(" << end.x << ", " << end.y << ") }";
    }

    float Line::getAngle() const
    {
        return util::getAngle(start, end);
    }

    Vector2f Line::getUnitVector() const
    {
        return getNormalized(start - end);
    }

    Vector2f Line::getRandomPoint() const
    {
        return start + sf::Randomizer::Random(0.f, 1.f) * (end - start);
    }

    // Virtual
    void Line::setPosition(const Vector2f & pos)
    {
        start = pos;
    }

} // namespace util

