/*
Grid
DebugDisplay.hpp

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

#ifndef DEBUGDISPLAY_HPP_INCLUDED
#define DEBUGDISPLAY_HPP_INCLUDED

#include "common.hpp"
#include "game/Graphics.hpp"

namespace grid
{
    class DebugDisplay
    {
    protected :

        sf::String m_fpsStr;
        sf::String m_objectsCountStr;

        float m_updateTime;
        float m_renderTime;
        float m_frameTime;
        int m_objectsCount;
        bool m_enable;

    public :

        DebugDisplay();

        inline void enable(bool e) { m_enable = e; }
        inline bool isEnabled() const { return m_enable; }

        DebugDisplay & setFrameTime(float v) { m_frameTime = v; return *this; }
        DebugDisplay & setRenderTime(float v) { m_renderTime = v; return *this; }
        DebugDisplay & setUpdateTime(float v) { m_updateTime = v; return *this; }
        DebugDisplay & setObjectsCount(int v) { m_objectsCount = v; return *this; }

        void update(float delta);
        void render(Graphics & gfx);
    };

} // namespace grid


#endif // DEBUGDISPLAY_HPP_INCLUDED
