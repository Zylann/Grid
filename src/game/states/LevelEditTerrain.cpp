/*
Grid
LevelEditTerrain.cpp

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

#include "game/states/LevelEditTerrain.hpp"
#include "game/states/LevelEditor.hpp"
#include "game/Game.hpp"
#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/noise.hpp"

#include "gui/Button.hpp"
#include "gui/Action.hpp"

using namespace util;

namespace grid
{
    LevelEditTerrain::LevelEditTerrain(
        int stateID, Game * game, LevelEditor * parent)
    : GameState(stateID, game, parent)
    {
        r_editor = parent;
        m_terrain.blockType = terrain::BT_WALL;
        m_terrain.groundType = terrain::GT_NORMAL;
    }

    LevelEditTerrain::~LevelEditTerrain()
    {
        std::cout << "LevelEditTerrain deletion" << std::endl;
    }

    void LevelEditTerrain::createGui()
    {
        m_gui = new gui::WidgetContainer(0, 0, 800, 600);
        gui::Frame * frame = new gui::Frame(680, 0, 120, 45);

        const sf::Font & font = resources::getFont("monofont");

        gui::Button * genBtn = new gui::Button(10, 10, 100, 24, "Generate", font);
        genBtn->setAction(new gui::Action<LevelEditTerrain>(this, &LevelEditTerrain::generateMap));

        frame->addChild(genBtn);

        m_gui->addChild(frame);
    }

    void LevelEditTerrain::onEnter()
    {

    }

    void LevelEditTerrain::onLeave()
    {

    }

    void LevelEditTerrain::update(GameUpdate & up)
    {
        Vector2f scenePos = r_game->getSceneMouseCoords();
        m_mapPos.x = scenePos.x;
        m_mapPos.y = scenePos.y;
    }

    void LevelEditTerrain::render(Graphics & gfx)
    {
        const Vector2i & mapSize = r_editor->getLevel()->getMap().getSize();

        gfx.setView(VIEW_GAME);
        // Current cell
        if(m_mapPos.x >= 0 && m_mapPos.y >= 0 &&
           m_mapPos.x < mapSize.x && m_mapPos.y < mapSize.y)
        {
            gfx.draw(sf::Shape::Rectangle(
                m_mapPos.x, m_mapPos.y,
                m_mapPos.x + 1, m_mapPos.y + 1,
                sf::Color(0,0,0,0), 0.01, sf::Color(255,255,255,128)));
        }

        gfx.setView(VIEW_INTERFACE);
        gfx.draw(*m_gui);
    }

    void LevelEditTerrain::generateMap()
    {
        Vector2i size(128, 64), pos;
        entity::Map & map = r_editor->getLevel()->getMap();
        map.create(size);

        unsigned int seed = sf::Randomizer::Random(0, 1000);
        terrain::Instance t(terrain::GT_NORMAL, terrain::BT_EMPTY);

        for(pos.y = 0; pos.y < size.y; pos.y++)
        for(pos.x = 0; pos.x < size.x; pos.x++)
        {
            double n = noise2dPerlin(pos.x, pos.y, seed, 4, 0.5, 8);
            double n2 = noise2dPerlin(pos.x, pos.y, seed + 1, 2, 0.5, 16);

            if(n >= 0.55 && n < 0.65)
                t.blockType = terrain::BT_DIRT;
            else if(n >= 0.65)
                t.blockType = terrain::BT_WALL;
            else
                t.blockType = terrain::BT_EMPTY;

            if(n2 > 0.7)
                t.groundType = terrain::GT_ICE;
            else
                t.groundType = terrain::GT_NORMAL;

            map.setTerrain(pos, t);
        }
    }

    /* Events */

    bool LevelEditTerrain::mouseLeftPressEvent(Vector2i pos)
    {
        entity::Map & map = r_editor->getLevel()->getMap();
        map.setTerrain(m_mapPos, m_terrain);
        Sound::instance().playSound("editorPlace");
        return true;
    }

    bool LevelEditTerrain::mouseRightPressEvent(Vector2i pos)
    {
        entity::Map & map = r_editor->getLevel()->getMap();
        map.setTerrain(m_mapPos, terrain::Instance());
        Sound::instance().playSound("editorPlace");
        return true;
    }

    bool LevelEditTerrain::mouseWheelUpEvent()
    {
        if(terrain::BT_COUNT == 0)
            return false;
        m_terrain.blockType++;
        if(m_terrain.blockType >= terrain::BT_COUNT)
            m_terrain.blockType = 0;
        std::cout << "LevelEditor terrain : "; m_terrain.print(std::cout); std::cout << std::endl;
        return true;
    }

    bool LevelEditTerrain::mouseWheelDownEvent()
    {
        if(terrain::BT_COUNT == 0)
            return false;
        if(m_terrain.blockType == 0)
            m_terrain.blockType = terrain::BT_COUNT - 1;
        else
            m_terrain.blockType--;
        std::cout << "LevelEditor terrain : "; m_terrain.print(std::cout); std::cout << std::endl;
        return true;
    }

    bool LevelEditTerrain::mouseMoveEvent(Vector2i previous, Vector2i current)
    {
        const sf::Input & input = r_game->getInput();
        if(input.IsMouseButtonDown(sf::Mouse::Left))
        {
            entity::Map & map = r_editor->getLevel()->getMap();
            map.setTerrain(m_mapPos, m_terrain);
        }
        else if(input.IsMouseButtonDown(sf::Mouse::Right))
        {
            entity::Map & map = r_editor->getLevel()->getMap();
            map.setTerrain(m_mapPos, terrain::Instance());
        }
        return false;
    }

} // namespace grid
