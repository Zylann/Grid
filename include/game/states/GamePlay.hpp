/*
Grid
GamePlay.hpp

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

#ifndef GAMEPLAY_HPP_INCLUDED
#define GAMEPLAY_HPP_INCLUDED

#include "game/base/GameState.hpp"
#include "game/World.hpp"

namespace grid
{
    class GamePlay : public GameState
    {
    private :

        World * m_world;
        bool m_pause;

    public :

        GamePlay(int stateID, Game * game);
        ~GamePlay();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        virtual void enter();
        virtual void leave();

        virtual void createGui();

        void init();

        virtual bool keyReleaseEvent(sf::Key::Code key, char character);

        void respawn();
        void resumeGame();
        void quitGame();
    };

} // namespace grid


#endif // GAMEPLAY_HPP_INCLUDED
