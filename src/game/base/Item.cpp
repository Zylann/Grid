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
            manager.addRender(m_renderer);
    }

    /*
        Serialization
    */

    void Item::serialize(std::ostream & os)
    {
        // TODO serialize Item
    }

    void Item::unserialize(std::istream & is)
    {
        // TODO unserialize Item
    }

} // namespace grid

