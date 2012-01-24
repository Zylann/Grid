/*
Grid
GameUpdate.hpp

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

#ifndef GAMEUPDATE_HPP_INCLUDED
#define GAMEUPDATE_HPP_INCLUDED

#include <list>

#include "game/Game.hpp"
#include "game/states/GamePlay.hpp"
#include "game/Level.hpp"

namespace grid
{
    struct GameUpdate
    {
        Game * game;
        GamePlay * gamePlay;
        Level * level;
        float delta;

        bool mouseWheelUp;
        bool mouseWheelDown;

        //std::list<sf::Event> events; // Not used

        GameUpdate(float p_delta)
        {
            game = NULL;
            gamePlay = NULL;
            level = NULL;
            delta = p_delta;
            mouseWheelDown = false;
            mouseWheelUp = false;
        }
    };

} // namespace grid


#endif // GAMEUPDATE_HPP_INCLUDED
