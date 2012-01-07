/*
Grid
Health.cpp

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

#include "game/components/Health.hpp"
#include "game/base/Entity.hpp"

namespace grid
{
    void Health::heal(int h)
    {
        if(h < 0)
            h = m_healthMax;

        if(m_health <= 0 && h > 0)
        {
            Message msg(M_HEA_ONREVIVE, r_owner);
            r_owner->processMessage(msg);
        }

        m_health += h;

        if(m_health > m_healthMax)
            m_health = m_healthMax;

        if(m_renderer != NULL)
            m_renderer->update();
    }

    void Health::hurt(int h)
    {
        //std::cout << r_owner->name << " has been hurt : " << h << std::endl;

        if(h < 0)
            h = m_healthMax;

        m_health -= h;

        if(m_health < 0)
            m_health = 0;

        if(m_health == 0)
        {
            Message msg(M_HEA_ONDEATH, r_owner);
            r_owner->processMessage(msg);

            std::cout << r_owner->name << " " << r_owner->getID() << " died" << std::endl;

            if(m_invalidateOnDeath)
                r_owner->invalidate();
        }

        if(m_renderer != NULL)
            m_renderer->update();
    }

    void Health::update(GameUpdate & up)
    {
    }

    bool Health::processMessage(Message & msg)
    {
        switch(msg.type)
        {
            case M_HEA_HEAL :
                heal(msg.health);
                return true;

            case M_HEA_FULL_HEAL :
                heal();
                return true;

            case M_HEA_HURT :
                hurt(msg.health);
                return true;

            case M_HEA_KILL :
                hurt();
                return true;

            default : break;
        }
        return false;
    }

    /*
        Serialization
    */

    void Health::serialize(std::ostream & os)
    {
        GameObject::serialize(os);

        util::serialize(os, m_healthMax);
        util::serialize(os, m_health);
        // Note : m_invalidateOnDeath is constant.
    }

    void Health::unserialize(std::istream & is)
    {
        GameObject::unserialize(is);

        util::unserialize(is, m_healthMax);
        util::unserialize(is, m_health);
    }

} // namespace grid

