/*
Grid
HealthBonus.cpp

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

#include "game/items/HealthBonus.hpp"
#include "game/base/Entity.hpp"
#include "game/renderers/RenderItem.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    HealthBonus::HealthBonus(int ID) : Item(ID)
    {
        m_health = 50;
        sf::Image & img = resources::getImage("item_health");
        img.SetSmooth(false);
        setRenderer(new RenderItem(this, RP_INTERFACE, img));
    }

    void HealthBonus::onPick(Entity * owner, World * world)
    {
        if(owner != NULL)
        {
            Message msg(M_HEA_HEAL, NULL);
            msg.health = m_health;
            owner->processMessage(msg);
            invalidate();
        }
    }

    void HealthBonus::update(GameUpdate & up)
    {
    }

    bool HealthBonus::processMessage(Message & msg)
    {
        return false;
    }

    Renderer * HealthBonus::createDroppedRenderer()
    {
        sf::Image & img = resources::getImage("item_health");
        img.SetSmooth(false);
        RenderImage * r = new RenderImage(RP_EVENTS, img);
        r->setScale(0.5f / GAME_TILES_SIZE);
        r->setBindScale(false);
        return r;
    }

    /*
        Serialization
    */

    void HealthBonus::serialize(std::ostream & os)
    {
        util::serialize(os, m_health);
    }

    void HealthBonus::unserialize(std::istream & is)
    {
        util::unserialize(is, m_health);
    }

} // namespace grid

