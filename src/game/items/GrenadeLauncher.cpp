/*
Grid
GrenadeLauncher.cpp

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

#include "game/items/GrenadeLauncher.hpp"
#include "game/entities/EntityGrenade.hpp"
#include "game/renderers/RenderItem.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    GrenadeLauncher::GrenadeLauncher(int ID) : FireWeapon()
    {
        sf::Image & img = resources::getImage("item_grenade");
        img.SetSmooth(false);
        setRenderer(new RenderItem(this, RP_INTERFACE, img));
    }

    Entity * GrenadeLauncher::createShot(int ownerID)
    {
        return new EntityGrenade(ownerID);
    }

    Renderer * GrenadeLauncher::createDroppedRenderer()
    {
        sf::Image & img = resources::getImage("item_grenade");
        img.SetSmooth(false);
        RenderImage * r = new RenderImage(RP_EVENTS, img);
        r->setScale(0.5f / GAME_TILES_SIZE);
        r->setBindScale(false);
        return r;
    }

    void GrenadeLauncher::playShootSound() const
    {
        Entity * owner = getOwner();
        if(owner != NULL)
            Sound::instance().playSound("launch", 1, 20, owner->pos);
    }

    float GrenadeLauncher::getPropulsionSpeed() const
    {
        return 20.f;
    }

    float GrenadeLauncher::getDispersion() const
    {
        return M_PI / 60.f;
    }

    float GrenadeLauncher::getShootTime() const
    {
        return 1.5f;
    }

    float GrenadeLauncher::getRepulsion() const
    {
        return 150.f;
    }

} // namespace grid

