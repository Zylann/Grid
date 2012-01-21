/*
Grid
FireWeapon.cpp

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

#include "game/items/FireWeapon.hpp"

namespace grid
{
    float FireWeapon::getShootTime() const
    {
        return 0.15f;
    }

    float FireWeapon::getRepulsion() const
    {
        return 80;
    }

    float FireWeapon::getPropulsionSpeed() const
    {
        return 20;
    }

    float FireWeapon::getDispersion() const
    {
        return M_PI / 60.f;
    }

    void FireWeapon::playShootSound() const
    {
        Entity * owner = getOwner();
        if(owner != NULL)
            Sound::instance().playSound("shoot", 1, 100, owner->pos);
    }

    void FireWeapon::onUnselect()
    {
        setTrigger(false);
    }

    void FireWeapon::update(GameUpdate & up)
    {
        if(m_nextShootTime > 0)
            m_nextShootTime -= up.delta;

        if(m_trigger && m_nextShootTime <= 0)
        {
            doShoot(*(up.world), up.delta);
            m_nextShootTime = getShootTime();
        }
    }

    bool FireWeapon::processMessage(Message & msg)
    {
        if(msg.type == M_ITM_TRIGGER)
        {
            setTrigger(msg.flag);
            return true;
        }
        return false;
    }

    Entity * FireWeapon::createShot(int ownerID)
    {
        return new entity::Shot(ownerID);
    }

    void FireWeapon::doShoot(World & world, float delta)
    {
        Entity * owner = getOwner();
        if(owner == NULL)
            return;

        // The following lines will be read only if the owner has been found

        const float speedLength = getPropulsionSpeed();
        const float t = owner->rotation + sf::Randomizer::Random(-getDispersion(), getDispersion());
        Vector2f v(cos(t), sin(t));

        // Do repulsion
        owner->accelerate(-v * getRepulsion(), delta);

        // Spawning shot
        Entity * shot = createShot(owner->getID());
        shot->speed = speedLength * v;
        shot->pos = owner->pos;
        shot->team = owner->team;
        world.spawnEntity(shot);

        playShootSound();
    }

} // namespace grid

