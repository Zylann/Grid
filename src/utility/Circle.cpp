/*
Grid
Circle.cpp

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

#include "utility/Circle.hpp"
#include "utility/geometry.hpp"

namespace util
{
    void Circle::offset(const Vector2f & off)
    {
        center += off;
    }

    bool Circle::collides(const Line & L) const
    {
        return Shape::getCollision(*this, L);
    }

    bool Circle::collides(const Circle & C) const
    {
        return distance2D(center, C.center) < radius + C.radius;
    }

    bool Circle::collides(const AxisAlignedBB & B) const
    {
        return Shape::getCollision(B, *this);
    }

    void Circle::print(std::ostream & os)
    {
        os << "{ center=(" << center.x << ", " << center.y << "), radius=" << radius << " }";
    }

    Vector2f Circle::getRandomPoint() const
    {
        // Note : this is not uniform
        float r = sf::Randomizer::Random(0.f, radius);
        float t = sf::Randomizer::Random(-(float)M_PI, (float)M_PI);
        return center + Vector2f(r * cos(t), r * sin(t));
    }

    // Virtual
    void Circle::setPosition(const Vector2f & pos)
    {
        center = pos;
    }

} // namespace util

