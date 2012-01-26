/*
Grid
LevelEditor.cpp

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

#include "game/states/LevelEditor.hpp"
#include "game/states/LevelEditTerrain.hpp"
#include "game/states/LevelEditEntities.hpp"
#include "game/Game.hpp"
#include "game/GameUpdate.hpp"
#include "game/Sound.hpp"
#include "game/entities/Sentinel.hpp"
#include "game/LevelManager.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/filesystem.hpp"

#include "gui/Button.hpp"
#include "gui/Action.hpp"
#include "gui/Console.hpp"
#include "gui/Menu.hpp"
#include "gui/MenuItem.hpp"

using namespace util;

namespace grid
{
    LevelEditor::LevelEditor(int stateID, Game * game) : GameState(stateID, game)
    {
        r_level = NULL;

        addState(new LevelEditTerrain(ST_LEVEL_EDIT_TERRAIN, game, this));
        addState(new LevelEditEntities(ST_LEVEL_EDIT_ENTITIES, game, this));
    }

    void LevelEditor::createGui()
    {
        m_gui = new gui::WidgetContainer(0,0,800,600);

        gui::Frame * frame = new gui::Frame(0, 0, 340, 45);
        m_gui->addChild(frame);

        const sf::Font & font = resources::getFont("monofont");

        gui::Button * quitBtn = new gui::Button(10, 10, 100, 24, "Quit", font);
        quitBtn->setAction(new gui::Action<LevelEditor>(this, &LevelEditor::quit));
        frame->addChild(quitBtn);

        gui::Button * saveBtn = new gui::Button(120, 10, 100, 24, "Save", font);
        saveBtn->setAction(new gui::Action<LevelEditor>(this, &LevelEditor::saveLevel));
        frame->addChild(saveBtn);

        r_modeMenu = new gui::Menu(230, 34, 150, 100);
        r_modeMenu->addItem("Entity mode", font,
            new gui::Action<LevelEditor>(this, &LevelEditor::enterEntityMode));
        r_modeMenu->addItem("Terrain mode", font,
            new gui::Action<LevelEditor>(this, &LevelEditor::enterTerrainMode));
        r_modeMenu->setVisible(false);
        m_gui->addChild(r_modeMenu);

        gui::Button * modeBtn = new gui::Button(230, 10, 100, 24, "Mode...", font);
        modeBtn->setAction(new gui::Action<gui::Widget>(r_modeMenu, &gui::Widget::show));
        frame->addChild(modeBtn);

//        r_console = new gui::Console(
//            10, 500, 400, 24, &font, new gui::Action<LevelEditor>(this, &LevelEditor::onCommand));
//        m_gui->addChild(r_console);
    }

    void LevelEditor::onEnter()
    {
        if(r_level == NULL)
        {
            r_level = LevelManager::instance().createLevel(LevelInfo("Level", Vector2f(5,5)));

            Vector2i size(128, 64);
            entity::Map * map = new entity::Map(-1, size);
            r_level->addEntity(map);
        }
        Renderer::setDisplayBoundingBoxes(true);
        enterState(ST_LEVEL_EDIT_TERRAIN);
    }

    void LevelEditor::onLeave()
    {
        if(r_level != NULL)
        {
            LevelManager::instance().closeLevel();
            r_level = NULL;
        }
//        r_console->clear();
        Renderer::setDisplayBoundingBoxes(false);
        finish();
    }

    void LevelEditor::quit()
    {
        r_game->enterState(ST_MAIN_MENU);
    }

    void LevelEditor::saveLevel()
    {
        if(r_level != NULL)
        {
            try
            {
                LevelManager::instance().saveLevel();
                Sound::instance().playSound("guiInfo", 10);
            }
            catch(std::exception & e)
            {
                std::cout << e.what() << std::endl;
                std::cout << "An error occured while saving the level." << std::endl;
                Sound::instance().playSound("guiError", 10);
            }
        }
    }

    void LevelEditor::enterEntityMode()
    {
        enterState(ST_LEVEL_EDIT_ENTITIES);
    }

    void LevelEditor::enterTerrainMode()
    {
        enterState(ST_LEVEL_EDIT_TERRAIN);
    }

    void LevelEditor::update(GameUpdate & up)
    {
        GameState::update(up);

        const sf::Input & input = r_game->getInput();

        Vector2f scenePos = r_game->getSceneMouseCoords();

        // TODO move the view with the mouse at screen borders

        m_scenePos = scenePos;

//        if(!r_console->getTextBar().isFocused())

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

    void LevelEditor::render(Graphics & gfx)
    {
        gfx.setView(VIEW_GAME);
        gfx.setGameViewCenter(m_viewCenter);
        gfx.drawGrid();

        if(r_level != NULL)
            r_level->render(gfx);

        gfx.setView(VIEW_GAME);

        const Vector2i & mapSize = r_level->getMap().getSize();

        // Map range
        gfx.draw(sf::Shape::Rectangle(
            0, 0, mapSize.x, mapSize.y,
            sf::Color(0,0,0,0), 0.1, sf::Color(255,255,255,128)));

        GameState::render(gfx);

        gfx.setView(VIEW_INTERFACE);
//        r_console->setPosition(
//            10, RenderMinimap::getLastMinimapPosition().y - r_console->getSize().y - 12);
        gfx.draw(*m_gui);
    }

    bool LevelEditor::mouseRightPressEvent(Vector2i pos)
    {
        return false;
    }

    bool LevelEditor::keyReleaseEvent(sf::Key::Code key, char character)
    {
        return false;
    }

//    void LevelEditor::onCommand()
//    {
//        std::string commandStr = r_console->getTextBar().getText();
//        std::cout << "onCommand " << commandStr << std::endl;
//    }

} // namespace grid

