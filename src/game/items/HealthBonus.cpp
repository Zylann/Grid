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
#include "game/renderers/RenderModel.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    HealthBonus::HealthBonus(int ID) : Item(ID)
    {
        m_health = 50;
    }

    void HealthBonus::onPick(Entity * owner, Level * level)
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
        Model * m = new Model();

        sf::Shape * circle = new sf::Shape(
            sf::Shape::Circle(0, 0, 0.1f, sf::Color(0,255,0), 0.05f, sf::Color(0,128,0,192)));

        m->addShape(circle);

        RenderModel * r = new RenderModel(RP_EVENTS, m);

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

