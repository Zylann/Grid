/*
Grid
Physics.cpp

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

#include "game/components/Physics.hpp"
#include "game/base/Entity.hpp"
#include "game/GameUpdate.hpp"

#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
    float FrictionModel::applyFriction(float x, float delta, const terrain::Ground & gp)
    {
        x -= c1 * (1 - gp.getSlipperiness()) * (x > 0 ? 1 : -1) * x * x * delta;

        if(x > 0)
        {
            x -= c2 * (1 - gp.getSlipperiness()) * delta;
            if(x < 0)
                x = 0;
        }
        else if(x < 0)
        {
            x += c2 * (1 - gp.getSlipperiness()) * delta;
            if(x > 0)
                x = 0;
        }
        return x;
    }

    void Physics::update(GameUpdate & up)
    {
        Vector2i mpos(r_owner->pos.x, r_owner->pos.y);

        const Map & map = up.world->getMap();
        terrain::Instance t = map.getTerrain(mpos);

        const terrain::Ground & gp = terrain::Ground::get(t.groundType);

        Vector2f & speedVec = r_owner->speed;

        speedVec.x = m_frictionModel.applyFriction(speedVec.x, up.delta, gp);
        speedVec.y = m_frictionModel.applyFriction(speedVec.y, up.delta, gp);

        const float maxSpeed = 16;
        float n = norm2D(speedVec);
        if(n > maxSpeed)
        {
            speedVec /= n;
            speedVec *= maxSpeed;
        }
    }

    bool Physics::processMessage(Message & msg)
    {
        return false;
    }

    // Note : don't call it in Physics::update
    Vector2f Physics::moveEntity(const Vector2f & motion, World & world)
    {
        AxisAlignedBB * boxPtr = r_owner->getBoundingBox();

        // If the owner hasn't any bounding box, there is no way
        // to apply collisions.
        if(boxPtr == NULL)
        {
            r_owner->pos += motion;
            return motion;
        }

        Vector2f newMotion = motion;
        AxisAlignedBB & box = *boxPtr;
        std::list<Collision> collisions;
        std::list<Collision>::iterator it;

        /* Find collisions */

        AxisAlignedBB expandedBox = box;
		expandedBox.expandFromVector(motion);

        world.getCollisions(collisions, expandedBox, r_owner);

        /* Resolve collisions */

        for(it = collisions.begin(); it != collisions.end(); it++)
        {
            newMotion.y = it->box.calculateYOffset(box, newMotion.y);
        }
        box.offset(0.0f, newMotion.y);

        for(it = collisions.begin(); it != collisions.end(); it++)
        {
            newMotion.x = it->box.calculateXOffset(box, newMotion.x);
        }
        box.offset(newMotion.x, 0.0f);

        // Update position
        r_owner->pos += newMotion;

        if(newMotion.x != motion.x)
            r_owner->speed.x = 0;

        if(newMotion.y != motion.y)
            r_owner->speed.y = 0;

        return newMotion;
    }

} // namespace grid

