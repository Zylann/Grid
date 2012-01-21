/*
Grid
DebugDisplay.cpp

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

#include <sstream>

#include "game/DebugDisplay.hpp"

namespace grid
{
    DebugDisplay::DebugDisplay()
    {
        m_fpsStr.SetPosition(0, 0);
        m_objectsCountStr.SetPosition(600, 0);
        m_enable = true;

        m_updateTime = 0;
        m_renderTime = 0;
        m_frameTime = 1;
        m_objectsCount = 0;
    }

    void DebugDisplay::update(float delta)
    {
        std::stringstream ss;
        ss << "FPS = " << (int)(1.f / m_frameTime);
        m_fpsStr.SetText(ss.str());

        ss.str("");
        ss << "OC = " << m_objectsCount;
        m_objectsCountStr.SetText(ss.str());
    }

    void DebugDisplay::render(Graphics & gfx)
    {
        gfx.draw(m_fpsStr);
        gfx.draw(m_objectsCountStr);

//        float updateRatio = m_updateTime / m_frameTime;
//        float renderRatio = m_renderTime / m_frameTime;
//        float barSize = 200;
        float barX = 200, barY = 5, barH = 8, scale = 4000;
        float updateX = barX + scale * m_updateTime;
        float renderX = barX + scale * m_renderTime;
        float remainX = barX + scale * (m_frameTime - m_updateTime - m_renderTime);
        float limitX = barX + scale * 1 / 60.f;

        // update part
        gfx.draw(sf::Shape::Line(
            barX, barY, updateX, barY, barH, sf::Color(255,0,0,192)));

        // render part
        gfx.draw(sf::Shape::Line(
            barX, barY + barH, renderX, barY + barH, barH, sf::Color(0,255,0,192)));

        // remaining part
        gfx.draw(sf::Shape::Line(
            barX, barY + 2*barH, remainX, barY + 2*barH, barH, sf::Color(128,128,128,192)));

        // limit
        gfx.draw(sf::Shape::Line(
            limitX, barY + barH/2, limitX, barY + 2*barH + barH/2, 1, sf::Color(255,255,255,192)));
    }

} // namespace grid

