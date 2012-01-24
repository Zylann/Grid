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
#include "utility/StateMachine.hpp"

#include "game/Graphics.hpp"
#include "game/GameException.hpp"

#include "gui/Frame.hpp"
#include "gui/EventListener.hpp"

namespace grid
{
    enum GameStateID
    {
        ST_ROOT = 0,
        ST_LOADING,
        ST_MAIN_MENU,
        ST_GAME_PLAY,
        ST_LEVEL_EDITOR,
        ST_LEVEL_EDIT_ENTITIES,
        ST_LEVEL_EDIT_TERRAIN
    };

    class GameUpdate;
    class Game;

    /*
        A game state is a part of the game's state machine.
        It can have sub-states that are updated and rendered at the same time of their parent.
        Ex : in the GamePlay state, when we win, the state GameWin is running too.
    */

    class GameState :
        public gui::EventListener,
        public util::State,
        public util::StateMachine<GameState>
    {
    protected :

        Game * r_game; // Root
        GameState * r_parent; // Parent
        gui::WidgetContainer * m_gui; // Integrated GUI

    public :

        GameState(int stateID, Game * game, GameState * parent = NULL);
        virtual ~GameState();

        /* State */

        virtual void init();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        /* GUI */

        // Called each time the state is entered while m_gui == NULL
        // It is called after enterState().
        virtual void createGui() {}

        // Overrides gui::EventListener::onEvent()
        virtual bool onEvent(const sf::Event & e, const Vector2i & mouse);

        gui::WidgetContainer * getGui() { return m_gui; }

        // Returns true if the gui is builded and active
        bool isGuiOpened();

        void openGui();
        void closeGui();
    };

} // namespace grid


#endif // GAMESTATE_HPP_INCLUDED




