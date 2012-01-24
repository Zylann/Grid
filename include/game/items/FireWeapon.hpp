/*
Grid
FireWeapon.hpp

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

#ifndef FIREWEAPON_HPP_INCLUDED
#define FIREWEAPON_HPP_INCLUDED

#include "game/base/Item.hpp"
#include "game/Sound.hpp"
#include "game/GameUpdate.hpp"
#include "game/entities/Shot.hpp"

namespace grid
{
    class Level;

    class FireWeapon : public Item
    {
    protected :

        float m_nextShootTime;
        bool m_trigger;

    public :

        FireWeapon(int ID = -1) : Item(ID)
        {
            m_nextShootTime = 0;
            m_trigger = false;
        }

        inline void setTrigger(bool t) { m_trigger = t; }

        virtual float getShootTime() const;
        virtual float getRepulsion() const;
        virtual float getPropulsionSpeed() const;
        virtual float getDispersion() const;

        virtual void playShootSound() const;

        virtual void onUnselect();

        virtual void update(GameUpdate & up);

        virtual bool processMessage(Message & msg);

        virtual Entity * createShot(int ownerID);

        virtual void doShoot(Level & level, float delta);
    };

//    typedef FireWeapon<EntityShot> BallGun;

} // namespace grid


#endif // FIREWEAPON_HPP_INCLUDED
