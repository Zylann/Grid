/*
Grid
OctoDirMover.cpp

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

#include "game/components/OctoDirMover.hpp"
#include "game/base/Entity.hpp"
#include "game/GameUpdate.hpp"

#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
    void OctoDirMover::update(GameUpdate & up)
    {
        /* Computing acceleration vector */

        Vector2f acc;

        if(m_left)
            acc.x = -1;
        else if(m_right)
            acc.x = 1;

        if(m_up)
            acc.y = -1;
        else if(m_down)
            acc.y = 1;

        float n = norm2D(acc);

        if(n > 0)
            acc /= norm2D(acc);

        Vector2i ipos(r_owner->pos.x, r_owner->pos.y);
        terrain::Instance t = up.world->getMap().getTerrain(ipos);
        const terrain::Ground & gp = terrain::Ground::get(t.groundType);

        acc *= m_acceleration * (1 - gp.getSlipperiness());

        /* Sending acceleration */

        r_owner->accelerate(acc, up.delta);
    }

    bool OctoDirMover::processMessage(Message & msg)
    {
        switch(msg.type)
        {
            case M_MOV_LEFT :
                m_left = msg.flag;
                return true;

            case M_MOV_RIGHT :
                m_right = msg.flag;
                return true;

            case M_MOV_UP :
                m_up = msg.flag;
                return true;

            case M_MOV_DOWN :
                m_down = msg.flag;
                return true;

            default : break;
        }
        return false;
    }

} // namespace grid

