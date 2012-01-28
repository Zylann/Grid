/*
Grid
AxisAlignedBB.hpp

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

#ifndef AXISALIGNEDBB_HPP_INCLUDED
#define AXISALIGNEDBB_HPP_INCLUDED

#include <iostream>

#include "common.hpp"

#include "utility/Shape.hpp"
#include "utility/serialization.hpp"

namespace util
{
    class AxisAlignedBB : public Shape
    {
    public :

        Vector2f minEdge;
        Vector2f maxEdge;

        AxisAlignedBB() : Shape()
        {}

        AxisAlignedBB(const Vector2f & min, const Vector2f & max) : Shape()
        {
            set(min.x, min.y, max.x, max.y);
        }

        AxisAlignedBB(float minX, float minY, float maxX, float maxY) : Shape()
        {
            set(minX, minY, maxX, maxY);
        }

        AxisAlignedBB(const Vector2f & center, float radius) : Shape()
        {
            set(center, radius);
        }

        AxisAlignedBB(const AxisAlignedBB & other) : Shape()
        {
            minEdge = other.minEdge;
            maxEdge = other.maxEdge;
        }

        AxisAlignedBB & set(float minX, float minY, float maxX, float maxY)
        {
            minEdge.x = minX;
            minEdge.y = minY;
            maxEdge.x = maxX;
            maxEdge.y = maxY;
            return *this;
        }

        AxisAlignedBB & set(const Vector2f & center, float radius)
        {
            minEdge.x = center.x - radius;
            minEdge.y = center.y - radius;
            maxEdge.x = center.x + radius;
            maxEdge.y = center.y + radius;
            return *this;
        }

        void expandFromVector(const Vector2f & V);

        void pad(float px, float py);

        inline float getWidth() const { return maxEdge.x - minEdge.x; }
        inline float getHeight() const { return maxEdge.y - minEdge.y; }

        float getArea() const;

        void correct();

        virtual bool collides(const AxisAlignedBB & other) const;
        virtual bool collides(const Line & L) const;
        virtual bool collides(const Circle & C) const;

        bool contains(float x, float y);
        virtual float getMaxRadius() const;
        virtual Vector2f getRandomPoint() const;

        virtual Vector2f getCenter() const;

        // Sets the center of the box
        virtual void setPosition(const Vector2f & pos);

        virtual void offset(const Vector2f & off);
        AxisAlignedBB & offset(float offX, float offY);
        AxisAlignedBB cloneWithOffset(const Vector2i & off) const;

        virtual void print(std::ostream & os);

        float calculateXOffset(const AxisAlignedBB & other, float motionX);
        float calculateYOffset(const AxisAlignedBB & other, float motionY);

    protected :

        virtual void serialize(std::ostream & os) const
        {
            util::serialize(os, minEdge);
            util::serialize(os, maxEdge);
        }

        virtual void unserialize(std::istream & is)
        {
            util::unserialize(is, minEdge);
            util::unserialize(is, maxEdge);
        }
    };

} // namespace util


#endif // AXISALIGNEDBB_HPP_INCLUDED
