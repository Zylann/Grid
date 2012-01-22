/*
Grid
MainMenu.hpp

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

#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "game/base/GameState.hpp"

namespace grid
{
    class MainMenu : public GameState
    {
    protected :

        sf::Sprite m_background;

    public :

        MainMenu(int stateID, Game * game) : GameState(stateID, game)
        {}

        virtual ~MainMenu();

        virtual void createGui();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        virtual void onEnter();
        virtual void onLeave();

        void startGame();
        void enterEditor();
    };
} // namespace grid


#endif // MAINMENU_HPP_INCLUDED
