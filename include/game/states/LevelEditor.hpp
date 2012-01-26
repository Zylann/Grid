/*
Grid
LevelEditor.hpp

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

#ifndef WORLDEDITOR_HPP_INCLUDED
#define WORLDEDITOR_HPP_INCLUDED

#include "game/base/GameState.hpp"
#include "game/Level.hpp"

#include "utility/Area2D.hpp"

#include "gui/Console.hpp"
#include "gui/Menu.hpp"

namespace grid
{
    class LevelEditor : public GameState
    {
    private :

        Level * r_level;
        Vector2f m_scenePos;
        Vector2f m_viewCenter;
//        gui::Console * r_console;
        gui::Menu * r_modeMenu;

    public :

        LevelEditor(int stateID, Game * game);

        ~LevelEditor()
        {}

        Level * getLevel() { return r_level; }

        virtual void createGui();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        virtual void onEnter();
        virtual void onLeave();

        /* Events */

        virtual bool keyReleaseEvent(sf::Key::Code key, char character = 0);
        virtual bool mouseRightPressEvent(Vector2i pos);

        void quit();
        void saveLevel();
//        void onCommand();
        void enterEntityMode();
        void enterTerrainMode();
    };

} // namespace grid


#endif // WORLDEDITOR_HPP_INCLUDED
