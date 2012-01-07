/*
Grid
.cpp

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

#include "game/renderers/RenderItem.hpp"
#include "game/renderers/RenderInventory.hpp"
#include "game/base/Item.hpp"

namespace grid
{
    RenderItem::RenderItem(const Item * item, int pass, const sf::Image & img)
    : RenderImage(pass, img)
    {
        r_item = item;
        update();
    }

    void RenderItem::update()
    {

    }

    void RenderItem::render(Graphics & gfx)
    {
        Vector2f invPos = RenderInventory::getInventoryPosition(gfx);
        invPos.x += 0.5 + r_item->getInventoryPosition();
        invPos.y += 0.5;
        m_sprite.SetPosition(invPos);
        gfx.draw(m_sprite);
    }

} // namespace grid

