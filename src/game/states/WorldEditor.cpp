/*
Grid
WorldEditor.cpp

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

#include <fstream>

#include "game/states/WorldEditor.hpp"
#include "game/Game.hpp"
#include "game/GameUpdate.hpp"
#include "game/Sound.hpp"
#include "game/entities/Sentinel.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/noise.hpp"
#include "utility/filesystem.hpp"

#include "gui/Button.hpp"
#include "gui/Action.hpp"
#include "gui/Console.hpp"

using namespace util;

namespace grid
{
    void WorldEditor::createGui()
    {
        m_gui = new gui::WidgetContainer(0,0,800,600);
        gui::Frame * frame = new gui::Frame(0, 0, 800, 45);

        const sf::Font & font = resources::getFont("monofont");

        gui::Button * quitBtn = new gui::Button(10, 10, 100, 24, "Quit", font);
        quitBtn->setAction(new gui::Action<WorldEditor>(this, &WorldEditor::quit));

        gui::Button * saveBtn = new gui::Button(120, 10, 100, 24, "Save", font);
        saveBtn->setAction(new gui::Action<WorldEditor>(this, &WorldEditor::saveWorld));

        gui::Button * genBtn = new gui::Button(230, 10, 100, 24, "Generate", font);
        genBtn->setAction(new gui::Action<WorldEditor>(this, &WorldEditor::generateMap));

        frame->addChild(quitBtn);
        frame->addChild(saveBtn);
        frame->addChild(genBtn);

        m_gui->addChild(frame);

        r_console = new gui::Console(10, 500, 400, 24, &font);
        m_gui->addChild(r_console);
    }

    void WorldEditor::enter()
    {
        init();
    }

    void WorldEditor::init()
    {
        if(m_world == NULL)
        {
            m_world = new World();

            Vector2i size(128, 64);
            entity::Map * map = new entity::Map(-1, size);
            m_world->addEntity(map);
        }
    }

    void WorldEditor::quit()
    {
        r_game->enterState(ST_MAIN_MENU);
    }

    void WorldEditor::saveWorld()
    {
        if(m_world != NULL)
        {
            try
            {
                std::string worldPath = "worlds/world";
                adaptFilePath(worldPath);
                std::ofstream ofs(worldPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

                if(!ofs.good())
                    throw Exception("cannot open file " + worldPath);

                m_world->serialize(ofs);
                ofs.close();
                std::cout << "World saved." << std::endl;
                Sound::instance().playSound("guiInfo", 10);
            }
            catch(std::exception & e)
            {
                std::cout << e.what() << std::endl;
                std::cout << "An error occured while saving the world." << std::endl;
                Sound::instance().playSound("guiError", 10);
            }
        }
    }

    void WorldEditor::generateMap()
    {
        Vector2i size(128, 64), pos;
        entity::Map & map = m_world->getMap();
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

    void WorldEditor::update(GameUpdate & up)
    {
        const sf::Input & input = r_game->getInput();

        Vector2f scenePos = r_game->getSceneMouseCoords();

        // TODO move the view with the mouse at screen borders

        m_scenePos = scenePos;
        m_mapPos.x = scenePos.x;
        m_mapPos.y = scenePos.y;

        if(!r_console->getTextBar().isFocused())
        {
            float speed = 15.f;
            if(input.IsKeyDown(sf::Key::Q))
                m_viewCenter.x -= speed * up.delta;
            if(input.IsKeyDown(sf::Key::D))
                m_viewCenter.x += speed * up.delta;
            if(input.IsKeyDown(sf::Key::S))
                m_viewCenter.y += speed * up.delta;
            if(input.IsKeyDown(sf::Key::Z))
                m_viewCenter.y -= speed * up.delta;
        }
    }

    void WorldEditor::render(Graphics & gfx)
    {
        gfx.setView(VIEW_GAME);
        gfx.setGameViewCenter(m_viewCenter);
        gfx.drawGrid();

        if(m_world != NULL)
            m_world->render(gfx);

        const Vector2i & mapSize = m_world->getMap().getSize();

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

        // Map range
        gfx.draw(sf::Shape::Rectangle(
            0, 0, mapSize.x, mapSize.y,
            sf::Color(0,0,0,0), 0.1, sf::Color(255,255,255,128)));

        gfx.setView(VIEW_INTERFACE);
        r_console->setPosition(
            10, RenderMinimap::getLastMinimapPosition().y - r_console->getSize().y - 12);
        gfx.draw(*m_gui);
    }

    bool WorldEditor::mouseLeftPressEvent(Vector2i pos)
    {
        entity::Map & map = m_world->getMap();
        map.setTerrain(m_mapPos, m_terrain);
        Sound::instance().playSound("editorPlace");
        return true;
    }

    bool WorldEditor::mouseRightPressEvent(Vector2i pos)
    {
        entity::Map & map = m_world->getMap();
        map.setTerrain(m_mapPos, terrain::Instance());
        Sound::instance().playSound("editorPlace");
        return false;
    }

    bool WorldEditor::mouseWheelUpEvent()
    {
        if(terrain::BT_COUNT == 0)
            return false;
        m_terrain.blockType++;
        if(m_terrain.blockType >= terrain::BT_COUNT)
            m_terrain.blockType = 0;
        std::cout << "WorldEditor terrain : "; m_terrain.print(std::cout); std::cout << std::endl;
        return true;
    }

    bool WorldEditor::mouseWheelDownEvent()
    {
        if(terrain::BT_COUNT == 0)
            return false;
        if(m_terrain.blockType == 0)
            m_terrain.blockType = terrain::BT_COUNT - 1;
        else
            m_terrain.blockType--;
        std::cout << "WorldEditor terrain : "; m_terrain.print(std::cout); std::cout << std::endl;
        return true;
    }

    bool WorldEditor::keyReleaseEvent(sf::Key::Code key, char character)
    {
//        if(key == sf::Key::E)
//        {
//            EntitySentinel * sentinel = new EntitySentinel();
//            m_world->addEntity(sentinel, m_scenePos);
//            Sound::instance().playSound("editorPlace");
//            return true;
//        }
        return false;
    }

    bool WorldEditor::mouseMoveEvent(Vector2i previous, Vector2i current)
    {
        const sf::Input & input = r_game->getInput();
        if(input.IsMouseButtonDown(sf::Mouse::Left))
        {
            entity::Map & map = m_world->getMap();
            map.setTerrain(m_mapPos, m_terrain);
        }
        else if(input.IsMouseButtonDown(sf::Mouse::Right))
        {
            entity::Map & map = m_world->getMap();
            map.setTerrain(m_mapPos, terrain::Instance());
        }
        return true;
    }

    void WorldEditor::leave()
    {
        if(m_world != NULL)
        {
            delete m_world;
            m_world = NULL;
        }
        r_console->clear();
    }

} // namespace grid

