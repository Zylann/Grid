/*
Grid
Health.hpp

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

#ifndef HEALTH_HPP_INCLUDED
#define HEALTH_HPP_INCLUDED

#include "game/base/Component.hpp"

namespace grid
{
    class Health : public Component
    {
    protected :

        int m_healthMax;
        int m_health;
        bool m_invalidateOnDeath;

    public :

        Health(int healthMax, int currentHealth, bool invalidateOnDeath = true)
        {
            m_healthMax = healthMax;
            m_health = currentHealth;
            m_invalidateOnDeath = invalidateOnDeath;
        }

        void heal(int h = -1);
        void hurt(int h = -1);

        inline float getHealthRatio() const { return (float)m_health / (float)m_healthMax; }

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // HEALTH_HPP_INCLUDED
