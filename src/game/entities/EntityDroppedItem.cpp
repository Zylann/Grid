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

        if(item != NULL)
            setRenderer(item->createDroppedRenderer());
    }

    Item * EntityDroppedItem::pickItem()
    {
        Item * temp = m_item;
        m_item = NULL;
        // TODO new sounds depending on the item
        Sound::instance().playSound("item_pick", 1, 25);
        invalidate();
        return temp;
    }

    void EntityDroppedItem::updateMe(GameUpdate & up)
    {
        // The item vanishes after a while
        if(m_item == NULL || m_lifeTime > 60.f)
            invalidate();
    }

    /*
        Serialization
    */

    void EntityDroppedItem::serialize(std::ostream & os)
    {
        Entity::serialize(os);

        if(m_item != NULL)
        {
            Item::serializeItem(os, *m_item);
        }
    }

    void EntityDroppedItem::unserialize(std::istream & is) throw(GameException)
    {
        Entity::unserialize(is);

        if(m_item != NULL)
            delete m_item;
        m_item = NULL;

        try
        {
            m_item = Item::unserializeItem(is);
            setRenderer(m_item->createDroppedRenderer());
        }
        catch(std::exception & ex)
        {
            std::stringstream ss;
            ss << ex.what() << std::endl;
            ss << "In EntityDroppedItem::unserialize";
            throw GameException(ss.str());
        }
    }

} // namespace grid

