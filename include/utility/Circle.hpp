/*
Grid
Circle.hpp

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

#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED

#include "utility/Shape.hpp"

namespace util
{
    class Circle : public Shape
    {
    public :

        Vector2f center;
        float radius;

        Circle() : Shape()
        {
            radius = 0;
        }

        Circle(const Vector2f & center, float radius)
        {
            set(center, radius);
        }

        void set(const Vector2f & p_center, float p_radius)
        {
            center = p_center;
            radius = p_radius;
        }

        virtual void offset(const Vector2f & off);
        virtual float getMaxRadius() const { return radius; }
        virtual Vector2f getRandomPoint() const;

        // Sets the center of the circle
        virtual void setPosition(const Vector2f & pos);

        virtual bool collides(const Line & L) const;
        virtual bool collides(const Circle & C) const;
        virtual bool collides(const AxisAlignedBB & B) const;

        virtual void print(std::ostream & os);

    protected :

        virtual void serialize(std::ostream & os) const
        {
            util::serialize(os, center);
            util::serialize(os, radius);
        }

        virtual void unserialize(std::istream & is)
        {
            util::unserialize(is, center);
            util::unserialize(is, radius);
        }
    };

} // namespace util


#endif // CIRCLE_HPP_INCLUDED
