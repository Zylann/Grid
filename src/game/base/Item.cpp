/*
Grid
Item.cpp

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

#include "game/base/Item.hpp"
#include "game/base/Entity.hpp"

#include "game/items/BallShooter.hpp"
#include "game/items/GrenadeLauncher.hpp"
#include "game/items/HealthBonus.hpp"

#include "game/components/Inventory.hpp"

namespace grid
{
    // TODO instant items (activated/finished on pick, no need to store them in the inventory)

    Entity * Item::getOwner() const
    {
        if(r_inventory != NULL)
            return r_inventory->getOwner();
        return NULL;
    }

    void Item::registerRender(RenderManager & manager)
    {
        Entity * owner = getOwner();
        if(owner == NULL)
            return;
        if(!owner->isPlayer())
            return;

        if(m_renderer != NULL)
            m_renderer->registerRender(manager);
    }

    /*
        Serialization
    */

    // Static
    void Item::serializeItem(std::ostream & os, Item & item)
    {
        util::serialize(os, item.getType());
        item.serialize(os);
    }

    // Static
    Item * Item::unserializeItem(std::istream & is) throw(GameException)
    {
        int itemType = 0;
        Item * item = NULL;

        util::unserialize(is, itemType);

        switch(itemType)
        {
            case ITM_BALL_SHOOTER :     item = new BallShooter();       break;
            case ITM_GRENADE_LAUNCHER : item = new GrenadeLauncher();   break;
            case ITM_HEALTH_BONUS :     item = new HealthBonus();       break;

            default :
                std::stringstream ss;
                ss << "Inventory::unserialize : "
                    << "unknown item type " << itemType;
                throw GameException(ss.str());
        }

        /* Unserializing item */

        try
        {
            item->unserialize(is);
        }
        catch(std::exception & e)
        {
            std::stringstream ss;
            ss << e.what() << std::endl;
            ss << "In Item::unserializeItem";
            throw GameException(ss.str());
        }
        return item;
    }

    void Item::serialize(std::ostream & os)
    {
        GameObject::serialize(os);
        util::serialize(os, m_inventoryPosition);
    }

    void Item::unserialize(std::istream & is)
    {
        GameObject::unserialize(is);
        util::unserialize(is, m_inventoryPosition);
    }

} // namespace grid

