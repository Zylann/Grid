/*
Grid
PlayerController.cpp

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

#include "game/components/PlayerController.hpp"
#include "game/GameUpdate.hpp"

#include "game/entities/EntityPlayer.hpp"

namespace grid
{
    void PlayerController::update(GameUpdate & up)
    {
        const sf::Input & input = up.game->getInput();

        /* Key controls */

        // Movement
        if(r_mover != NULL)
        {
            r_mover->reset(); // Reset movement flags

            if(input.IsKeyDown(sf::Key::Q))
            {
                Message m(M_MOV_LEFT, r_owner, true);
                r_mover->processMessage(m);
            }
            else if(input.IsKeyDown(sf::Key::D))
            {
                Message m(M_MOV_RIGHT, r_owner, true);
                r_mover->processMessage(m);
            }

            if(input.IsKeyDown(sf::Key::Z))
            {
                Message m(M_MOV_UP, r_owner, true);
                r_mover->processMessage(m);
            }
            else if(input.IsKeyDown(sf::Key::S))
            {
                Message m(M_MOV_DOWN, r_owner, true);
                r_mover->processMessage(m);
            }
        }

        /* Mouse controls */

        bool mouseLeft = input.IsMouseButtonDown(sf::Mouse::Left);
        bool mouseRight = input.IsMouseButtonDown(sf::Mouse::Right);

        // Shoot
        if(mouseLeft ^ m_lastMouseLeft)
        {
            Message msg(M_ITM_TRIGGER, r_owner, mouseLeft && !m_lastMouseLeft);
            r_owner->processMessage(msg);
        }
        // Action
        if(mouseRight ^ m_lastMouseRight)
        {
            Message msg(M_ITM_ACTION, r_owner, mouseRight && !m_lastMouseRight);
            r_owner->processMessage(msg);
        }
        // Item selection
        if(up.mouseWheelDown)
        {
            Message msg(M_INV_RIGHT, r_owner);
            r_owner->processMessage(msg);
        }
        else if(up.mouseWheelUp)
        {
            Message msg(M_INV_LEFT, r_owner);
            r_owner->processMessage(msg);
        }

        m_lastMouseLeft = mouseLeft;
        m_lastMouseRight = mouseRight;
    }

    bool PlayerController::processMessage(Message & msg)
    {
        return false;
    }

} // namespace grid

