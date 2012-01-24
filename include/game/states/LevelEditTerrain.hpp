/*
Grid
LevelEditTerrain.hpp

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

#ifndef LEVELEDITTERRAIN_HPP_INCLUDED
#define LEVELEDITTERRAIN_HPP_INCLUDED

#include "game/base/GameState.hpp"
#include "game/Terrain.hpp"

namespace grid
{
    class LevelEditor;

    class LevelEditTerrain : public GameState
    {
    protected :

        LevelEditor * r_editor;
        Vector2i m_mapPos;
        terrain::Instance m_terrain;

    public :

        LevelEditTerrain(int stateID, Game * game, LevelEditor * parent = NULL);
        virtual ~LevelEditTerrain();

        virtual void onEnter();
        virtual void onLeave();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        virtual void createGui();

        /* Events */

        virtual bool mouseLeftPressEvent(Vector2i pos);
        virtual bool mouseRightPressEvent(Vector2i pos);
        virtual bool mouseMoveEvent(Vector2i previous, Vector2i current);
        virtual bool mouseWheelUpEvent();
        virtual bool mouseWheelDownEvent();

        void generateMap();
    };

} // namespace grid


#endif // LEVELEDITTERRAIN_HPP_INCLUDED
