/*
Grid
ProgressBar.cpp

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

#include "game/ProgressBar.hpp"

namespace grid
{
    ProgressBar::ProgressBar(const Vector2f & pos, const Vector2f & size)
    {
        m_pos = pos;
        m_size = size;

        m_back = sf::Shape::Rectangle(0, 0, size.x + 4, size.y + 4, sf::Color(64,64,64));
        m_fill = sf::Shape::Rectangle(2, 2, 2, 2 + size.y, sf::Color(64,255,0));
    }

    void ProgressBar::setFillRatio(float fr)
    {
        m_fillRatio = fr;
        float x = m_size.x * m_fillRatio;
        m_fill.SetPointPosition(1, x, 2);
        m_fill.SetPointPosition(2, x, 2 + m_size.y);
    }

    void ProgressBar::render(Graphics & gfx)
    {
        m_back.SetPosition(m_pos);
        m_fill.SetPosition(m_pos);

        gfx.draw(m_back);
        gfx.draw(m_fill);
    }

} // namespace grid

