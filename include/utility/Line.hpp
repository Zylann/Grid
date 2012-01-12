/*
Grid
Line.hpp

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

#ifndef LINE_HPP_INCLUDED
#define LINE_HPP_INCLUDED

#include "utility/Shape.hpp"

namespace util
{
    class Line : public Shape
    {
    public :

        Vector2f start;
        Vector2f end;

        Line() : Shape()
        {}

        Line(const Vector2f & p_start, const Vector2f & p_end)
        {
            set(p_start, p_end);
        }

        void set(const Vector2f & p_start, const Vector2f & p_end)
        {
            start = p_start;
            end = p_end;
        }

        float getAngle() const;
        float getLength() const;

        Vector2f getUnitVector() const;

        virtual void offset(const Vector2f & off);
        virtual float getMaxRadius() const;
        virtual Vector2f getRandomPoint() const;

        // Sets the start point of the line
        virtual void setPosition(const Vector2f & pos);

        virtual bool collides(const Line & L) const;
        virtual bool collides(const Circle & C) const;
        virtual bool collides(const AxisAlignedBB & B) const;

        virtual void print(std::ostream & os);

    protected :

        virtual void serialize(std::ostream & os) const
        {
            util::serialize(os, start);
            util::serialize(os, end);
        }

        virtual void unserialize(std::istream & is)
        {
            util::unserialize(is, start);
            util::unserialize(is, end);
        }
    };

} // namespace util


#endif // LINE_HPP_INCLUDED
