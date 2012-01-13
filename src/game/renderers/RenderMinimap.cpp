/*
Grid
RenderMinimap.cpp

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

#include "game/renderers/RenderMinimap.hpp"

namespace grid
{
    RenderMinimap::RenderMinimap(int pass) : Renderer(pass)
    {
    }

    void RenderMinimap::update()
    {
    }

    void RenderMinimap::setMinimapImage(const sf::Image & img)
    {
        m_minimap.SetImage(img);
        // Note : if an image was already set, the sub-rect would not update itself
        // (See sf::Sprite in SFML 1.6 source code)
        m_minimap.SetSubRect(sf::IntRect(0, 0, img.GetWidth(), img.GetHeight()));

        m_borders = sf::Shape::Rectangle(
            0, 0, img.GetWidth(), img.GetHeight(),
            sf::Color(0,0,0,192), 4, sf::Color(255,255,255,192));
    }

    void RenderMinimap::render(Graphics & gfx)
    {
        int imgHeight = 0;
        if(m_minimap.GetImage() != NULL)
        {
            imgHeight = m_minimap.GetImage()->GetHeight();
        }

        const sf::FloatRect & rect = gfx.getCurrentView().GetRect();
        Vector2f pos(rect.Left, rect.Bottom - imgHeight);
        m_minimap.SetPosition(pos);
        m_borders.SetPosition(pos);

        const sf::FloatRect & gameRect = gfx.getView(VIEW_GAME).GetRect();
        m_viewRect = sf::Shape::Rectangle(
            gameRect.Left, gameRect.Top, gameRect.Right, gameRect.Bottom,
            sf::Color(255,255,255,32), 1, sf::Color(255,255,255,128));
        m_viewRect.SetBlendMode(sf::Blend::Add);
        m_viewRect.SetPosition(pos);

        gfx.draw(m_borders);
        gfx.draw(m_minimap);
        gfx.draw(m_viewRect);

        // Draw main player position
        // TODO
    }

} // namespace grid

