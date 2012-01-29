/*
Grid
entity::Shot.cpp

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

#include "game/entities/Shot.hpp"
#include "game/entities/ShockWave.hpp"
#include "game/renderers/RenderImage.hpp"
#include "game/GameUpdate.hpp"
#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
namespace entity
{
    Shot::Shot(int shooterID, int ID) : Entity(ID)
    {
        name = "shot";
        m_shooterID = shooterID;

        Physics * phys = new Physics();
        phys->setNoClip(true);
        phys->setNotifyCollisions(true);
        addComponent(phys);

        const sf::Image & shotImg = resources::getImage("shot");

        RenderImage * r = new RenderImage(RP_EFFECTS, shotImg);
        r->setBlendMode(sf::Blend::Add);
        r->setColor(sf::Color(255, 255, 32));

        setBoundingBox(new AxisAlignedBB(-0.01, -0.01, 0.01, 0.01));

        setRenderer(r);

        scale = 0.5;
    }

    util::AxisAlignedBB * Shot::getBoundingBox()
    {
        return &( m_boundingBox->set(-0.01, -0.01, 0.01, 0.01).offset(pos.x, pos.y) );
    }

    void Shot::updateMe(GameUpdate & up)
    {
    }

    void Shot::onCollision(const Collision & c)
    {
        sf::Color clr(255,255,255);

        if(c.entity != NULL)
        {
            // Except entities with the same team or the same type
            if(c.entity->team == team || c.entity->getType() == getType())
                return;

            if(c.entity->getType() != ENT_MAP)
            {
                // Repulsion
                Vector2f repulsion = getNormalized(speed);
                // TODO find a way to access delta here, or not have to.
                // onCollision basically doesn't access to delta, then we have to choose a value...
                c.entity->accelerate(repulsion * 80.f, 0.03f);

                // Hurting
                Message hurt(M_HEA_HURT, this);
                hurt.health = 15;
                c.entity->processMessage(hurt);

                // Bloody color
                clr.g = 0;
                clr.b = 0;
            }
        }

        // Hit particles
        r_level->spawnEntity(new entity::ShockWave(0.1, 0.8, 4, clr), pos);

        invalidate();
    }

    void Shot::onDestruction(GameUpdate & up)
    {
        Sound::instance().playSound("ricochet", sf::Randomizer::Random(0.9f, 1.1f), 20, pos);
    }

    /*
        Serialization
    */

    void Shot::serialize(std::ostream & os)
    {
        Entity::serialize(os);
        util::serialize(os, m_shooterID);
    }

    void Shot::unserialize(std::istream & is)
    {
        Entity::unserialize(is);
        util::unserialize(is, m_shooterID);
    }

} // namespace entity
} // namespace grid

