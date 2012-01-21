/*
Grid
RenderShockWave.cpp

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

#include "game/renderers/RenderShockWave.hpp"
#include "game/entities/ShockWave.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    RenderShockWave::RenderShockWave(int pass) : Renderer(pass)
    {
        r_shockWave = NULL;
        m_flashEnabled = true;

        sf::Image & img = resources::getImage("clash");
        m_flash.SetImage(img);
        m_flash.SetCenter(img.GetWidth() / 2, img.GetHeight() / 2);
        m_flash.SetBlendMode(sf::Blend::Add);

        m_wave = sf::Shape::Circle(0, 0, 0.5, sf::Color(0,0,0,0), 0.2, sf::Color(255,255,255));

        setColor(sf::Color(255,255,255));

        if(pass != RP_INTERFACE)
            m_flash.SetScale(1.f / GAME_TILES_SIZE, 1.f / GAME_TILES_SIZE);
    }

    void RenderShockWave::setEntity(Entity * e)
    {
        Renderer::setEntity(e);

        r_shockWave = NULL;
        if(e == NULL)
            return;

        if(e->getType() == ENT_SHOCKWAVE)
        {
            r_shockWave = (entity::ShockWave*)e;
            float scale = 0.5f * fabs(r_shockWave->getEndRadius() - r_shockWave->getStartRadius());
            scale /= GAME_TILES_SIZE;
            m_flash.SetScale(scale, scale);
        }
    }

    void RenderShockWave::setColor(const sf::Color & color)
    {
        m_wave.SetColor(color);
        m_flash.SetColor(sf::Color(color.r, color.g, color.b, 128));
    }

    void RenderShockWave::setBlendMode(sf::Blend::Mode mode)
    {
        m_wave.SetBlendMode(mode);
    }

    void RenderShockWave::render(Graphics & gfx)
    {
        m_wave.SetPosition(r_entity->pos);
        m_wave.SetScale(r_entity->scale, r_entity->scale);
        m_flash.SetPosition(r_entity->pos);

        if(r_shockWave != NULL)
        {
            float time = r_shockWave->getLifeTime();
            sf::Color clr;

            // Fading the flash
            if(time < 0.25f)
            {
                clr = m_flash.GetColor();
                clr.a = (float)(clr.a) * (1 - time / 0.25f);
                m_flash.SetColor(clr);
            }

            // Fading the shockwave
            clr = m_wave.GetColor();
            clr.a = 255 * r_shockWave->getFadingRatio();
            m_wave.SetColor(clr);
        }

        gfx.draw(m_wave);
        gfx.draw(m_flash);
    }

} // namespace grid

