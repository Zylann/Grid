/*
Grid
Area2D.cpp

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

#include "utility/Area2D.hpp"

namespace util
{
    Area2D::Area2D()
    {
    }

    Area2D::Area2D(const Vector2i & newSize)
    {
        setSize(newSize);
    }

    Area2D::Area2D(const Vector2i & newPos, const Vector2i & newSize)
    {
        setPosition(newPos);
        setSize(newSize);
    }

    void Area2D::setSize(const Vector2i & newSize)
    {
        m_size.x = newSize.x >= 0 ? newSize.x : 0;
        m_size.y = newSize.y >= 0 ? newSize.y : 0;
    }

    void Area2D::setBounds(const Vector2i & minEdge, const Vector2i & maxEdge)
    {
        setSize(maxEdge - minEdge + Vector2i(1,1));
        setPosition(minEdge);
    }

    bool Area2D::valid(const Vector2i & pos) const
    {
        return validRelative(pos - m_pos);
    }

    bool Area2D::validRelative(const Vector2i & pos) const
    {
        return pos.x >= 0 &&
               pos.y >= 0 &&
               pos.x < m_size.x &&
               pos.y < m_size.y;
    }

    Vector2i Area2D::getMinEdge() const
    {
        return m_pos;
    }

    Vector2i Area2D::getMaxEdge() const
    {
        return m_pos + m_size - Vector2i(1,1);
    }

    void Area2D::clear()
    {
        m_size.x = 0;
        m_size.y = 0;

        m_pos.x = 0;
        m_pos.y = 0;
    }

    void Area2D::correct()
    {
        if(m_size.x < 0) m_size.x = 0;
        if(m_size.y < 0) m_size.y = 0;
    }

    void Area2D::expand(int px, int py)
    {
        m_size.x += 2 * px;
        m_size.y += 2 * py;

        m_pos.x -= px;
        m_pos.y -= py;

        correct();
    }

    bool Area2D::contains(const Area2D & other) const
    {
        return m_pos.x <= other.m_pos.x &&
               m_pos.y <= other.m_pos.y &&
               m_pos.x + m_size.x >= other.m_pos.x + other.m_size.x &&
               m_pos.y + m_size.y >= other.m_pos.y + other.m_size.y ;
    }

    void Area2D::print(std::ostream & os) const
    {
        os << "{pos=(" << m_pos.x << ", " << m_pos.y << "), "
            << "size=(" << m_size.x << ", " << m_size.y << ")}";
    }

    int Area2D::getVolume() const
    {
        return m_size.x * m_size.y;
    }

    int Area2D::index(const Vector2i & p_pos) const
    {
        return relativeIndex(p_pos - m_pos);
    }

    int Area2D::relativeIndex(const Vector2i & p_pos) const
    {
        return p_pos.y * m_size.x + p_pos.x;
    }

} // namespace util

