/*
Grid
LevelEditEntities.cpp

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

#include "game/states/LevelEditEntities.hpp"
#include "game/states/LevelEditor.hpp"
#include "game/entities/Sentinel.hpp"
#include "game/Game.hpp"
#include "game/Sound.hpp"

namespace grid
{
    LevelEditEntities::LevelEditEntities(
        int stateID, Game * game, LevelEditor * parent)
    : GameState(stateID, game, parent)
    {
        r_editor = parent;
        r_selectedEntity = NULL;
        r_hoveredEntity = NULL;
    }

    LevelEditEntities::~LevelEditEntities()
    {
        std::cout << "LevelEditEntities deletion" << std::endl;
    }

    void LevelEditEntities::createGui()
    {

    }

    void LevelEditEntities::onEnter()
    {

    }

    void LevelEditEntities::onLeave()
    {

    }

    void LevelEditEntities::update(GameUpdate & up)
    {
        r_hoveredEntity = findPointedEntity(r_editor->getLevel());
    }

    void LevelEditEntities::render(Graphics & gfx)
    {
        gfx.setView(VIEW_GAME);
        if(r_hoveredEntity != NULL)
            r_hoveredEntity->getRenderer()->renderBoundingBox(gfx, sf::Color(255,255,255));
        if(r_selectedEntity != NULL)
            r_selectedEntity->getRenderer()->renderBoundingBox(gfx, sf::Color(255,255,0));
    }

    Entity * LevelEditEntities::findPointedEntity(Level * level)
    {
        Vector2f scenePos = r_game->getSceneMouseCoords();

        util::AxisAlignedBB box(scenePos, 0.01f);
        std::list<Collision> collisions;
        level->getCollisions(collisions, box, NULL);

        if(!collisions.empty())
        {
            return collisions.front().entity;
        }
        else
            return NULL;
    }

    bool LevelEditEntities::mouseLeftPressEvent(Vector2i pos)
    {
        if(r_hoveredEntity != NULL)
        {
            r_selectedEntity = r_hoveredEntity;
            return true;
        }
        if(r_selectedEntity != NULL)
        {
            r_selectedEntity = NULL;
            return true;
        }

        Vector2f scenePos = r_game->getSceneMouseCoords();
        entity::Sentinel * sentinel = new entity::Sentinel();
        sentinel->setPosition(scenePos);
        r_editor->getLevel()->addEntity(sentinel);
        Sound::instance().playSound("editorPlace");
        return true;
    }

    bool LevelEditEntities::keyPressEvent(sf::Key::Code key, char character)
    {
        if(r_selectedEntity != NULL)
        {
            if(r_hoveredEntity == r_selectedEntity)
                r_hoveredEntity = NULL;
            Level * level = r_editor->getLevel();
            level->eraseEntity(r_selectedEntity->getID());
            r_selectedEntity = NULL;
            return true;
        }
        return false;
    }

} // namespace grid

