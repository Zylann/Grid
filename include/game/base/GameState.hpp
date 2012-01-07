/*
Grid
GameState.hpp

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

#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "common.hpp"

#include "utility/Exception.hpp"
#include "game/Graphics.hpp"
#include "gui/Frame.hpp"
#include "gui/EventListener.hpp"
#include "game/GameException.hpp"

namespace grid
{
    enum GameStateID
    {
        ST_LOADING = 0,
        ST_MAIN_MENU,
        ST_GAME_PLAY,
        ST_WORLD_EDITOR
    };

    class GameUpdate;
    class Game;

    class GameState : public gui::EventListener
    {
    protected :

        int m_ID;
        gui::Frame * m_gui;
        Game * r_game;

    public :

        GameState(int stateID, Game * game);
        virtual ~GameState();

        inline int getID() const { return m_ID; }

        /* State */

        virtual void update(GameUpdate & up) = 0;
        virtual void render(Graphics & gfx) = 0;

        // Called when we enter the state
        virtual void enter() {}

        // Called when we leave the state
        virtual void leave() {}

        /* GUI */

        // Called each time the state is entered while m_gui == NULL
        // It is called after enterState().
        virtual void createGui() {}

        virtual bool onEvent(const sf::Event & e, const Vector2i & mouse);

        gui::Frame * getGui() { return m_gui; }

        // Returns true if the gui is builded and active
        bool isGuiOpened();

        void openGui();
        void closeGui();
    };

} // namespace grid


#endif // GAMESTATE_HPP_INCLUDED




