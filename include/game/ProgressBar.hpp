/*
Grid
.hpp

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

#ifndef PROGRESSBAR_HPP_INCLUDED
#define PROGRESSBAR_HPP_INCLUDED

#include "common.hpp"
#include "game/Graphics.hpp"

namespace grid
{
    class ProgressBar
    {
    protected :

        float m_fillRatio;
        sf::Shape m_back;
        sf::Shape m_fill;
        Vector2f m_size;
        Vector2f m_pos;

    public :

        ProgressBar(const Vector2f & pos, const Vector2f & size);

        void setFillRatio(float fr);
        void setPosition(const Vector2f & pos) { m_pos = pos; }

        const Vector2f & getPosition() const { return m_pos; }
        const Vector2f & getSize() const { return m_size; }

        void render(Graphics & gfx);
    };

} // namespace grid


#endif // PROGRESSBAR_HPP_INCLUDED
