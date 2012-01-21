/*
Grid
Game.hpp

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

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <map>

#include "common.hpp"
#include "game/World.hpp"
#include "game/base/GameState.hpp"
#include "game/Graphics.hpp"
#include "game/DebugDisplay.hpp"

#define GRID_SCALE 32

namespace grid
{
    class Game
    {
    private :

        sf::RenderWindow m_screen;
        Graphics * m_graphics;
        sf::Sprite m_cursor;
        bool m_cursorVisible;
        std::map<int, GameState*> m_states;
        GameState * r_currentState;
        bool m_runFlag;
        DebugDisplay * m_debugDisplay;

    public :

        Game();
        ~Game();

        void run();
        void enterState(int stateID);
        GameState * getState(int stateID);

        const sf::Input & getInput() { return m_screen.GetInput(); }
        const Vector2f getSceneMouseCoords();
        Graphics * getGraphics() { return m_graphics; }
        void setCursorImage(const sf::Image & img);
        void setCursorVisible(bool visible) { m_cursorVisible = visible; }
        void quit() { m_runFlag = false; }

    private :

        void addState(GameState * state);
    };

} // namespace grid


#endif // GAME_HPP_INCLUDED
