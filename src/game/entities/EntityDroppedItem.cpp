/*
Grid
EntityDroppedItem.cpp

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

#include "game/entities/EntityDroppedItem.hpp"
#include "game/renderers/RenderImage.hpp"
#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    EntityDroppedItem::EntityDroppedItem(Item * item, int ID) : Entity(ID)
    {
        m_item = item;
        // TODO new renderers depending on the item
        sf::Image & img = resources::getImage("item_health");
        img.SetSmooth(false);
        RenderImage * r = new RenderImage(RP_EVENTS, img);
        r->setScale(0.5f / GAME_TILES_SIZE);
        r->setBindScale(false);
        setRenderer(r);
    }

    Item * EntityDroppedItem::pickItem()
    {
        Item * temp = m_item;
        m_item = NULL;
        // TODO new sounds depending on the item
        Sound::instance().playSound("item_pick", 1, 50);
        invalidate();
        return temp;
    }

} // namespace grid

