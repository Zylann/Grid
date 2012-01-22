/*
Grid
WorldEditor.hpp

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
#include "game/World.hpp"

#include "utility/Area2D.hpp"

#include "gui/Console.hpp"

namespace grid
{
    class WorldEditor : public GameState
    {
    private :

        World * m_world;
        Vector2f m_scenePos;
        Vector2i m_mapPos;
        Vector2f m_viewCenter;
        terrain::Instance m_terrain;
        gui::Console * r_console;

    public :

        WorldEditor(int stateID, Game * game) : GameState(stateID, game)
        {
            m_world = NULL;
            m_terrain.blockType = terrain::BT_WALL;
            m_terrain.groundType = terrain::GT_NORMAL;
        }

        ~WorldEditor()
        {
            if(m_world != NULL)
                delete m_world;
        }

        virtual void createGui();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        virtual void onEnter();
        virtual void onLeave();

        virtual bool mouseLeftPressEvent(Vector2i pos);
        virtual bool mouseRightPressEvent(Vector2i pos);
        virtual bool mouseMoveEvent(Vector2i previous, Vector2i current);
        virtual bool mouseWheelUpEvent();
        virtual bool mouseWheelDownEvent();
        virtual bool keyReleaseEvent(sf::Key::Code key, char character = 0);

        void quit();
        void saveWorld();
        void generateMap();
    };

} // namespace grid


#endif // WORLDEDITOR_HPP_INCLUDED
