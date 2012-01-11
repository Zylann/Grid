/*
Grid
.cpp

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

#include "game/items/BallShooter.hpp"
#include "game/entities/EntityShot.hpp"
#include "game/renderers/RenderItem.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/noise.hpp"

using namespace util;

namespace grid
{
    BallShooter::BallShooter(int ID) : FireWeapon()
    {
        setRenderer(new RenderItem(this, RP_INTERFACE, resources::getImage("item_ballshooter")));
    }

    Entity * BallShooter::createShot(int ownerID)
    {
        Entity * owner = getOwner();
        EntityShot * shot = new EntityShot(ownerID);
        if(owner != NULL)
        {
            if(owner->team == 1)
                shot->getRenderer()->setColor(sf::Color(0, 255, 255));
        }
        return shot;
    }

    void BallShooter::playShootSound() const
    {
        Entity * owner = getOwner();
        if(owner != NULL)
        {
            float pitch = 1;
            if(!owner->isPlayer())
            {
                // Slight pitch variation for better sound (useful in huge battles...).
                // Pitch is not modified for players because it would be annoying a bit.
                pitch = 0.9f + 0.2f * noise2d(0, 0, getID());
            }
            Sound::instance().playSound("shoot", pitch, 50, owner->pos);
        }
    }

    float BallShooter::getPropulsionSpeed() const
    {
        return 20.f;
    }

    float BallShooter::getDispersion() const
    {
        return M_PI / 60.f;
    }

    float BallShooter::getShootTime() const
    {
        return 0.12f;
    }

    float BallShooter::getRepulsion() const
    {
        return 80.f;
    }

} // namespace grid

