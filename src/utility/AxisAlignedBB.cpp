/*
Grid
AxisAlignedBB.cpp

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

#include "utility/AxisAlignedBB.hpp"
#include "utility/algebra.hpp"


namespace util
{
    void AxisAlignedBB::expandFromVector(const Vector2f & V)
    {
        if(V.x > 0)
            maxEdge.x += V.x;
        else if(V.x < 0)
            minEdge.x += V.x;
        if(V.y > 0)
            maxEdge.y += V.y;
        else if(V.y < 0)
            minEdge.y += V.y;
    }

    void AxisAlignedBB::pad(float px, float py)
    {
        minEdge.x += px;
        maxEdge.x += px;
        minEdge.y += py;
        maxEdge.y += py;
    }

    float AxisAlignedBB::getArea() const
    {
        return getHeight() * getWidth();
    }

    void AxisAlignedBB::correct()
    {
        if(minEdge.x > maxEdge.x)
            swap<float>(minEdge.x, maxEdge.x);

        if(minEdge.y > maxEdge.y)
            swap<float>(minEdge.y, maxEdge.y);
    }

    // Virtual
    float AxisAlignedBB::getMaxRadius() const
    {
        return sqrt(square<float>(getWidth()) + square<float>(getHeight())) / 2;
    }

    // Virtual
    bool AxisAlignedBB::collides(const AxisAlignedBB & other) const
    {
        if(other.maxEdge.x <= minEdge.x || other.minEdge.x >= maxEdge.x)
            return false;
        return other.maxEdge.y > minEdge.y && other.minEdge.y < maxEdge.y;
    }

    // Virtual
    bool AxisAlignedBB::collides(const Line & L) const
    {
        return Shape::getCollision(*this, L);
    }

    // Virtual
    bool AxisAlignedBB::collides(const Circle & C) const
    {
        return Shape::getCollision(*this, C);
    }

    bool AxisAlignedBB::contains(float x, float y)
    {
        if(x <= minEdge.x || x >= maxEdge.x)
            return false;
        return y <= minEdge.y || y >= maxEdge.y;
    }

    // Virtual
    Vector2f AxisAlignedBB::getRandomPoint() const
    {
        return Vector2f(sf::Randomizer::Random(minEdge.x, maxEdge.x),
                        sf::Randomizer::Random(minEdge.y, maxEdge.y));
    }

    // Virtual
    void AxisAlignedBB::setPosition(const Vector2f & pos)
    {
        minEdge = pos;
    }

    AxisAlignedBB & AxisAlignedBB::offset(float offX, float offY)
    {
        minEdge.x += offX;
        minEdge.y += offY;
        maxEdge.x += offX;
        maxEdge.y += offY;

        return *this;
    }

    // Virtual
    void AxisAlignedBB::offset(const Vector2f & off)
    {
        offset(off.x, off.y);
    }

    AxisAlignedBB AxisAlignedBB::cloneWithOffset(const Vector2i & off) const
    {
        return AxisAlignedBB(
            minEdge.x + off.x,
            minEdge.y + off.y,
            maxEdge.x + off.x,
            maxEdge.y + off.y);
    }

    // Virtual
    void AxisAlignedBB::print(std::ostream & os)
    {
        os << "((" << minEdge.x << ", " << minEdge.y << "), "
            << "(" << maxEdge.x << ", " << maxEdge.y << "))";
    }

    float AxisAlignedBB::calculateXOffset(const AxisAlignedBB & other, float motionX)
    {
        if(other.maxEdge.y <= minEdge.y || other.minEdge.y >= maxEdge.y)
        {
            return motionX;
        }
        if(motionX > 0.0f && other.maxEdge.x <= minEdge.x)
        {
            /*
             * A micro-offset is added here, because in some cases,
             * precision errors occurs.
             */
            float off = minEdge.x - other.maxEdge.x - 0.001f;
            if(off < motionX)
            {
                motionX = off;
            }
        }
        if(motionX < 0.0f && other.minEdge.x >= maxEdge.x)
        {
            float off = maxEdge.x - other.minEdge.x + 0.001f;
            if(off > motionX)
            {
                motionX = off;
            }
        }
        return motionX;
    }

    float AxisAlignedBB::calculateYOffset(const AxisAlignedBB & other, float motionY)
    {
        if(other.maxEdge.x <= minEdge.x || other.minEdge.x >= maxEdge.x)
        {
            return motionY;
        }
        if(motionY > 0.0f && other.maxEdge.y <= minEdge.y)
        {
            /*
             * A micro-offset is added here, because in some cases,
             * precision errors occurs.
             */
            float off = minEdge.y - other.maxEdge.y - 0.001f;
            if(off < motionY)
            {
                motionY = off;
            }
        }
        if(motionY < 0.0f && other.minEdge.y >= maxEdge.y)
        {
            float off = maxEdge.y - other.minEdge.y + 0.001f;
            if(off > motionY)
            {
                motionY = off;
            }
        }
        return motionY;
    }

} // namespace util

