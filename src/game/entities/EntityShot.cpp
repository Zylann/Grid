/*
Grid
EntityShot.cpp

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

#include "game/entities/EntityShot.hpp"
#include "game/entities/EntityShockWave.hpp"
#include "game/renderers/RenderImage.hpp"
#include "game/GameUpdate.hpp"
#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
    EntityShot::EntityShot(int shooterID, int ID) : Entity(ID)
    {
        name = "shot";
        m_shooterID = shooterID;

        const sf::Image & shotImg = resources::getImage("shot");

        RenderImage * r = new RenderImage(RP_EFFECTS, shotImg);
        r->setBlendMode(sf::Blend::Add);
        r->setColor(sf::Color(255, 255, 0));

        setRenderer(r);

        scale = 0.5;
    }

    void EntityShot::updateMe(GameUpdate & up)
    {
        Vector2i mpos(pos.x, pos.y);

        static AxisAlignedBB box;
        box.set(pos.x - 0.1, pos.y - 0.1, pos.x + 0.1, pos.y + 0.1);

        // Find collisions
        std::list<Collision> collisions;
        std::list<Collision>::iterator it;
        up.world->getCollisions(collisions, box, this);

        bool collided = false;

        // If collision(s) occured
        if(!collisions.empty())
        {
            // Search for colliding entities
            for(it = collisions.begin(); it != collisions.end(); it++)
            {
                Collision & c = *it;
                // Hurt all found entities
                if(c.entity != NULL)
                {
                    // Except shooters with the same team
                    if(c.entity->team == team)
                        continue;
                }
                doHit(*(up.world), c, up.delta);
                collided = true;
            }
        }

        if(collided)
            invalidate();
    }

    void EntityShot::doHit(World & world, Collision & c, float delta)
    {
        sf::Color clr(255,255,255);

        if(c.entity != NULL)
        {
            // Hurting
            Message hurt(M_HEA_HURT, this);
            hurt.health = 15;
            c.entity->processMessage(hurt);

            // Repulsion
            Vector2f rep = getNormalized(speed);
            c.entity->accelerate(rep * 80.f, delta);

            // Bloody color
            clr.g = 0;
            clr.b = 0;
        }

        // Hit particles
        world.spawnEntity(new EntityShockWave(0.1, 0.8, 4, clr), pos);
    }

    void EntityShot::onDestruction(GameUpdate & up)
    {
        Sound::instance().playSound("ricochet", sf::Randomizer::Random(0.9f, 1.1f), 20, pos);
    }

    /*
        Serialization
    */

    void EntityShot::serialize(std::ostream & os)
    {
        Entity::serialize(os);
        util::serialize(os, m_shooterID);
    }

    void EntityShot::unserialize(std::istream & is)
    {
        Entity::unserialize(is);
        util::unserialize(is, m_shooterID);
    }

} // namespace grid

