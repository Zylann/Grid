/*
Grid
RenderImage.cpp

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

#include "game/base/Entity.hpp"
#include "game/renderers/RenderImage.hpp"
#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
    RenderImage::RenderImage(int pass, const sf::Image & img) : Renderer(pass)
    {
        m_bindRotation = true;
        m_bindScale = true;
        m_sprite.SetImage(img);
        m_sprite.SetCenter(img.GetWidth() / 2, img.GetHeight() / 2);
        m_sprite.SetScale(1.f / GAME_TILES_SIZE, 1.f / GAME_TILES_SIZE);
    }

    void RenderImage::setColor(const sf::Color & color)
    {
        m_sprite.SetColor(color);
    }

    void RenderImage::setBlendMode(sf::Blend::Mode mode)
    {
        m_sprite.SetBlendMode(mode);
    }

    void RenderImage::setScale(float s)
    {
        m_sprite.SetScale(s, s);
    }

    void RenderImage::update()
    {
    }

    void RenderImage::render(Graphics & gfx)
    {
        m_sprite.SetPosition(r_entity->pos);

        if(m_bindRotation && r_entity->rotation != 0)
            m_sprite.SetRotation(-toDegrees(r_entity->rotation));

        if(m_bindScale && r_entity->scale != m_sprite.GetScale().x)
            m_sprite.SetScale(r_entity->scale / GAME_TILES_SIZE, r_entity->scale / GAME_TILES_SIZE);

        gfx.draw(m_sprite);

        //renderBoundingBox(gfx);
    }
} // namespace grid

