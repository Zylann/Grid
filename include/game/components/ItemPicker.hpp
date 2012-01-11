/*
Grid
ItemPicker.hpp

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

#ifndef ITEMPICKER_HPP_INCLUDED
#define ITEMPICKER_HPP_INCLUDED

#include "game/base/Component.hpp"
#include "game/components/Inventory.hpp"

namespace grid
{
    /*
        The owner of this component will pick items around him.
        If the ItemPicker has a reference to the inventory (and if items are not instants),
        it will put picked items in it if possible. If not, items are not picked.
    */

    class EntityDroppedItem;

    class ItemPicker : public Component
    {
    protected :

        Inventory * r_inventory;

    public :

        ItemPicker(Inventory * inventory = NULL, int ID = -1) : Component(ID)
        {
            r_inventory = inventory;
        }

        virtual void update(GameUpdate & up);
        virtual void pick(EntityDroppedItem * e);
        virtual bool processMessage(Message & msg);

        virtual bool isSerializable() const { return false; }
    };

} // namespace grid

#endif // ITEMPICKER_HPP_INCLUDED
