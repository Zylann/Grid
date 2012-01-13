/*
Grid
RenderInventory.cpp

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

#include "game/renderers/RenderInventory.hpp"
#include "game/components/Inventory.hpp"

namespace grid
{
    RenderInventory::RenderInventory(Inventory * inventory, int pass) : Renderer(pass)
    {
        r_inventory = inventory;

        const int size = r_inventory->getSize();
        sf::Shape * rect = new sf::Shape( sf::Shape::Rectangle(
            0, 0, size, 1, sf::Color(0,0,0,192), 0.1, sf::Color(255,255,255,192)));

        m_back.addShape(rect);

        for(int i = 1; i < size; i++)
        {
            m_back.addShape(new sf::Shape( sf::Shape::Line(
                i, 0, i, 1, 0.05, sf::Color(255,255,255,192))));
        }

        m_selection = sf::Shape::Rectangle(
            0, 0, 1, 1, sf::Color(0,0,0,0), 0.1, sf::Color(255,255,0,192));

        m_back.setScale(GAME_TILES_SIZE);
        m_selection.SetScale(GAME_TILES_SIZE, GAME_TILES_SIZE);
    }

    void RenderInventory::setBlendMode(sf::Blend::Mode mode)
    {
        //m_back.setBlendMode(mode);
        m_selection.SetBlendMode(mode);
    }

    void RenderInventory::setColor(const sf::Color & color)
    {
        m_back.setColor(color);
        m_selection.SetColor(color);
    }

    void RenderInventory::update()
    {
        const float x = r_inventory->getCurrentX();

        m_selection.SetPointPosition(0, x, 0);
        m_selection.SetPointPosition(1, x + 1, 0);
        m_selection.SetPointPosition(2, x + 1, 1);
        m_selection.SetPointPosition(3, x, 1);
    }

    void RenderInventory::render(Graphics & gfx)
    {
        Vector2f pos = getInventoryPosition(gfx);

        m_back.setPosition(pos);
        m_selection.SetPosition(pos);

        m_back.render(gfx);

        gfx.draw(m_selection);
    }

    /*
        Static methods
    */

    Vector2f RenderInventory::getInventoryPosition(Graphics & gfx)
    {
        Vector2f pos = gfx.getCurrentView().GetCenter();
        pos.x -= GAME_TILES_SIZE * (float)(PLAYER_INVENTORY_SIZE) / 2.f;
        pos.y = gfx.getCurrentView().GetRect().Bottom - 1.4f * GAME_TILES_SIZE;
        return pos;
    }

} // namespace grid

