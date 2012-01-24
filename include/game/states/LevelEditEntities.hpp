/*
Grid
LevelEditEntities.hpp

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

#ifndef LEVELEDITENTITIES_HPP_INCLUDED
#define LEVELEDITENTITIES_HPP_INCLUDED

#include "game/base/GameState.hpp"

namespace grid
{
    class LevelEditor;
    class Entity;
    class Level;

    class LevelEditEntities : public GameState
    {
    protected :

        LevelEditor * r_editor;
        Entity * r_hoveredEntity;
        Entity * r_selectedEntity;

    public :

        LevelEditEntities(int stateID, Game * game, LevelEditor * parent = NULL);
        virtual ~LevelEditEntities();

        virtual void createGui();

        virtual void onEnter();
        virtual void onLeave();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        Entity * findPointedEntity(Level * level);

        virtual bool mouseLeftPressEvent(Vector2i pos);
        virtual bool keyPressEvent(sf::Key::Code key, char character = 0);
    };

} // namespace grid


#endif // LEVELEDITENTITIES_HPP_INCLUDED
