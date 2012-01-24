/*
Grid
ItemPicker.cpp

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

#include "game/components/ItemPicker.hpp"
#include "game/components/Inventory.hpp"
#include "game/entities/DroppedItem.hpp"
#include "game/GameUpdate.hpp"

namespace grid
{
    void ItemPicker::update(GameUpdate & up)
    {
        std::list<Entity*> entities;
        std::list<Entity*>::iterator it;

        up.level->getEntitiesInRadius(entities, r_owner->pos, 1);

        Entity * e = NULL;
        for(it = entities.begin(); it != entities.end(); it++)
        {
            e = (*it);
            // If the entity is a valid dropped item, and if it has lived more than 1 second
            // (this delay is important, because the item would be picked immediatly after being dropped)
            if(e->isDroppedItem() && e->isValid() && e->getLifeTime() > 1.f)
            {
                pick((entity::DroppedItem*)e);
            }
        }
    }

    void ItemPicker::pick(entity::DroppedItem * e)
    {
        if(e->getItem() == NULL)
            return;

        if(e->getItem()->isInstant())
        {
            Item * item = e->pickItem(); // entity is invalidated here
            item->onPick(r_owner);
            delete item;
            return;
        }
        else if(r_inventory != NULL)
        {
            if(!r_inventory->isFull())
            {
                // the item entity is invalidated here
                r_inventory->addItem(e->pickItem());
            }
        }
    }

    bool ItemPicker::processMessage(Message & msg)
    {
        return false;
    }

} // namespace grid

