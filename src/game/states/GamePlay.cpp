/*
Grid
GamePlay.cpp

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

#include <iostream>
#include <fstream>

#include "game/states/GamePlay.hpp"
#include "game/GameUpdate.hpp"
#include "game/renderers/RenderImage.hpp"
#include "game/entities/Player.hpp"
#include "game/entities/Sentinel.hpp"
#include "game/components/RandomSpawner.hpp"
#include "game/Sound.hpp"

#include "gui/Button.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/noise.hpp"
#include "utility/Circle.hpp"
#include "utility/filesystem.hpp"

using namespace util;

namespace grid
{
    GamePlay::GamePlay(int stateID, Game * game) : GameState(stateID, game)
    {
        m_level = NULL;
        m_pause = false;
    }

    GamePlay::~GamePlay()
    {
        std::cout << "GamePlay deletion" << std::endl;
        if(m_level != NULL)
        {
            std::cout << "Level deletion" << std::endl;
            delete m_level;
            m_level = NULL;
        }
    }

    void GamePlay::createGui()
    {
        m_gui = new gui::WidgetContainer(0,0,800,600);
        gui::Frame * frame = new gui::Frame(100, 100, 600, 400);

        const sf::Font & font = resources::getFont("monofont");

        gui::Button * resumeBtn = new gui::Button(100, 100, 300, 24, "Resume game", font);
        resumeBtn->setAction(new gui::Action<GamePlay>(this, &GamePlay::resumeGame));

        gui::Button * quitBtn = new gui::Button(100, 130, 300, 24, "Quit game", font);
        quitBtn->setAction(new gui::Action<GamePlay>(this, &GamePlay::quitGame));

        frame->addChild(resumeBtn);
        frame->addChild(quitBtn);

        m_gui->addChild(frame);
        m_gui->setVisible(false);
        m_gui->enable(false);
    }

    void GamePlay::update(GameUpdate & up)
    {
        GameState::update(up);

        up.gamePlay = this;
        up.level = m_level;

        if(!m_pause)
        {
            // Bullet time (debug)
            const sf::Input & input = up.game->getInput();
            if(input.IsKeyDown(sf::Key::Space))
                up.delta /= 10.f;

            entity::Player * player = m_level->getLocalPlayer();
            if(player != NULL)
            {
                player->lookAt(r_game->getSceneMouseCoords());
            }
            m_level->update(up);
        }
    }

    void GamePlay::render(Graphics & gfx)
    {
        GameState::render(gfx);

        gfx.setView(VIEW_GAME);
        gfx.drawGrid();

        m_level->render(gfx);

        if(!m_pause)
        {
            m_target.SetPosition(r_game->getSceneMouseCoords());
            gfx.draw(m_target);
        }

        gfx.setView(VIEW_INTERFACE);
        if(m_gui->isVisible())
            gfx.draw(*m_gui);

        // This code is left here to remind how we could use post-effects
//        static sf::Clock timer;
//        sf::PostFX & effect = resources::getPostFX("wave");
//		effect.SetTexture("tex", NULL);
//		effect.SetParameter("time", 0.5 * timer.GetElapsedTime());
//		effect.SetParameter("intensity", 0.8f);
//		effect.SetParameter("center", 0.5, 0.5);
//		effect.SetParameter("wavesize", 20.0f);
//        gfx.draw(effect);
    }

    void GamePlay::onEnter()
    {
        if(m_target.GetImage() == NULL)
        {
            sf::Image & img = resources::getImage("target");
            img.SetSmooth(false);
            m_target.SetImage(img);
            m_target.SetCenter(img.GetWidth() / 2, img.GetHeight() / 2);
            m_target.SetScale(1.f / GAME_TILES_SIZE, 1.f / GAME_TILES_SIZE);
        }

        if(m_level != NULL)
            delete m_level;
        m_level = new Level;

        std::string levelPath = "worlds/world";
        adaptFilePath(levelPath);
        std::ifstream ifs(levelPath.c_str(), std::ios::in | std::ios::binary);
        if(ifs.good())
        {
            m_level->unserialize(ifs);
            ifs.close();
        }
        else
        {
            throw GameException("Cannot load level '" + levelPath + "'");
        }

        // This code add several spawners to the level
//        for(unsigned int i = 0; i < 6; i ++)
//        {
//            Entity * spawner = new Entity();
//            spawner->addComponent(
//                new RandomSpawner(ENT_SENTINEL,
//                    new Circle(Vector2f(), 6), 10.f, 20.f, 1, 3));
//
//            Vector2f pos(sf::Randomizer::Random(1.f, 120.f), sf::Randomizer::Random(1.f, 60.f));
//            m_level->spawnEntity(spawner, pos);
//        }

        respawn();
        resumeGame();
    }

    void GamePlay::onLeave()
    {
    }

    bool GamePlay::keyReleaseEvent(sf::Key::Code key, char character)
    {
        if(key == sf::Key::Back)
        {
            respawn();
            return true;
        }
        else if(key == sf::Key::Escape)
        {
            m_pause = !m_pause;
            m_gui->setVisible(m_pause);
            m_gui->enable(m_pause);
            r_game->setCursorVisible(m_pause);
        }

        // debug
        else if(key == sf::Key::M)
        {
            std::cout << "SpaceDivider :" << std::endl;
            m_level->getSpaceDivider().print(std::cout, Vector2i(0,0), Vector2i(20,20));
        }
        return false;
    }

    void GamePlay::respawn()
    {
        if(m_level->getLocalPlayer() == NULL)
        {
            entity::Player * p = new entity::Player();
            p->setPlayerInfo(&m_playerInfo);
            m_level->spawnEntity(p, Vector2f(5,5));
            Sound::instance().playSound("spawn", 1, 50);
        }
    }

    void GamePlay::resumeGame()
    {
        m_pause = false;
        m_gui->setVisible(false);
        m_gui->enable(false);
        r_game->setCursorVisible(false);
    }

    void GamePlay::quitGame()
    {
        if(m_level != NULL)
        {
            delete m_level;
            m_level = NULL;
        }
        r_game->enterState(ST_MAIN_MENU);
    }

} // namespace grid

