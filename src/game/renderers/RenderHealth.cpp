/*
Grid
RenderHealth.cpp

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

#include "game/renderers/RenderHealth.hpp"
#include "game/components/Health.hpp"
#include "game/base/Entity.hpp"

#define HP_BAR_WIDTH 50
#define HP_BAR_HEIGHT 4
#define HP_BAR_FADE 3.f

namespace grid
{
    RenderHealth::RenderHealth(const Health * health, int pass, bool fade) : Renderer(pass)
    {
        r_health = health;
        m_fade = fade;

        m_back = sf::Shape::Rectangle(-1, -1, HP_BAR_WIDTH + 1, HP_BAR_HEIGHT + 1, sf::Color(0,0,0,128));
        m_bar1 = sf::Shape::Rectangle(0, 0, 1, HP_BAR_HEIGHT, sf::Color(0,255,0,192));
        m_bar2 = sf::Shape::Rectangle(1, 0, HP_BAR_WIDTH, HP_BAR_HEIGHT, sf::Color(255,0,0,192));

        m_back.SetScale(1.f / GAME_TILES_SIZE, 1.f / GAME_TILES_SIZE);
        m_bar1.SetScale(1.f / GAME_TILES_SIZE, 1.f / GAME_TILES_SIZE);
        m_bar2.SetScale(1.f / GAME_TILES_SIZE, 1.f / GAME_TILES_SIZE);

        update();
    }

    void RenderHealth::setBlendMode(sf::Blend::Mode mode)
    {
    }

    void RenderHealth::setColor(const sf::Color & color)
    {
        m_back.SetColor(color);
        m_bar1.SetColor(color);
        m_bar2.SetColor(color);
    }

    void RenderHealth::update()
    {
        const float x = HP_BAR_WIDTH * r_health->getHealthRatio();

        m_bar1.SetPointPosition(1, x, 0);
        m_bar1.SetPointPosition(2, x, HP_BAR_HEIGHT);
        m_bar2.SetPointPosition(0, x, 0);
        m_bar2.SetPointPosition(3, x, HP_BAR_HEIGHT);

        if(m_fade)
            m_fadeTime.Reset();
    }

    void RenderHealth::render(Graphics & gfx)
    {
        if(r_entity == NULL)
            return;
        if(r_health == NULL)
            return;

        if(m_fade && m_fadeTime.GetElapsedTime() <= HP_BAR_FADE)
        {
            unsigned char a = 255 * (1 - m_fadeTime.GetElapsedTime() / HP_BAR_FADE);
            setColor(sf::Color(255, 255, 255, a));
        }

        if(!m_fade || (m_fade && m_fadeTime.GetElapsedTime() <= HP_BAR_FADE))
        {
            Vector2f pos = r_entity->pos - Vector2f(1, 1);
            m_back.SetPosition(pos);
            m_bar1.SetPosition(pos);
            m_bar2.SetPosition(pos);

            gfx.draw(m_back);
            gfx.draw(m_bar1);
            gfx.draw(m_bar2);
        }
    }

} // namespace grid

