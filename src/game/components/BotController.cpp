/*
Grid
BotController.cpp

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

#include "game/components/BotController.hpp"
#include "game/base/Entity.hpp"
#include "game/GameUpdate.hpp"

#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
    void BotController::update(GameUpdate & up)
    {
        if(m_weaponTrigger)
        {
            Message msg(M_ITM_TRIGGER, r_owner, false);
            r_owner->processMessage(msg);
            m_weaponTrigger = false;
        }

        r_owner->rotation += M_PI * up.delta;

        // TODO improve bots IA
        // The current method makes them see through walls

        Entity * p = up.world->getMainPlayer();
        if(p != NULL)
        {
            float d = distance2D(p->pos, r_owner->pos);
            if(d < 10)
            {
                r_owner->lookAt(p->pos);

                if(d > 5)
                {
                    Vector2f v(cos(r_owner->rotation), sin(r_owner->rotation));
                    r_owner->accelerate(50.f * v, up.delta, up.world);
                }

                if(sf::Randomizer::Random(0.f, 1.f) < 0.02f)
                {
                    Message msg(M_ITM_TRIGGER, r_owner, true);
                    r_owner->processMessage(msg);
                    m_weaponTrigger = true;
                }
            }
        }
    }

    bool BotController::processMessage(Message & msg)
    {
        return false;
    }

} // namespace grid
