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
#include "game/entities/EntityPlayer.hpp"
#include "game/entities/EntitySentinel.hpp"
#include "game/components/RandomSpawner.hpp"
#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/noise.hpp"
#include "utility/Circle.hpp"

using namespace util;

namespace grid
{
    GamePlay::GamePlay(int stateID, Game * game) : GameState(stateID, game)
    {
        m_world = NULL;
    }

    GamePlay::~GamePlay()
    {
        std::cout << "GamePlay deletion" << std::endl;
        if(m_world != NULL)
        {
            std::cout << "World deletion" << std::endl;
            delete m_world;
            m_world = NULL;
        }
    }

    void GamePlay::update(GameUpdate & up)
    {
        up.gamePlay = this;
        up.world = m_world;

        // Bullet time (debug)
        const sf::Input & input = up.game->getInput();
        if(input.IsKeyDown(sf::Key::Space))
            up.delta /= 10.f;
        else if(input.IsKeyDown(sf::Key::Escape))
            r_game->enterState(ST_MAIN_MENU);

        EntityPlayer * player = m_world->getMainPlayer();
        if(player != NULL)
        {
            player->lookAt(r_game->getSceneMouseCoords());
        }

        m_world->update(up);
    }

    void GamePlay::render(Graphics & gfx)
    {
//        static sf::Clock timer;

        gfx.setView(VIEW_GAME);
        gfx.drawGrid();

        m_world->render(gfx);

//        sf::PostFX & effect = resources::getPostFX("wave");
//		effect.SetTexture("tex", NULL);
//		effect.SetParameter("time", 0.5 * timer.GetElapsedTime());
//		effect.SetParameter("intensity", 0.8f);
//		effect.SetParameter("center", 0.5, 0.5);
//		effect.SetParameter("wavesize", 20.0f);
//        gfx.draw(effect);
    }

    void GamePlay::enter()
    {
        init();
    }

    void GamePlay::leave()
    {
    }

    void GamePlay::init()
    {
        if(m_world != NULL)
            delete m_world;
        m_world = new World;

        std::ifstream ifs("world", std::ios::in | std::ios::binary);
        if(ifs.good())
        {
            m_world->unserialize(ifs);
            ifs.close();
        }

        for(unsigned int i = 0; i < 6; i ++)
        {
            Entity * spawner = new Entity();
            spawner->addComponent(
                new RandomSpawner<EntitySentinel>(
                    new Circle(Vector2f(), 6), 10.f, 20.f, 1, 3));

            Vector2f pos(sf::Randomizer::Random(1.f, 120.f), sf::Randomizer::Random(1.f, 60.f));
            m_world->spawnEntity(spawner, pos);
        }

        respawn();
    }

    void GamePlay::respawn()
    {
        if(m_world->getMainPlayer() == NULL)
        {
            EntityPlayer * p = new EntityPlayer();
            m_world->spawnEntity(p, Vector2f(5,5));
            Sound::instance().playSound("spawn", 1, 50);
        }
    }

    bool GamePlay::keyReleaseEvent(sf::Key::Code key, char character)
    {
        if(key == sf::Key::Back)
        {
            respawn();
            return true;
        }
        // debug
        else if(key == sf::Key::M)
        {
            std::cout << "SpaceDivider" << std::endl;
            m_world->getSpaceDivider().print(std::cout, Vector2i(0,0), Vector2i(20,20));
        }
        return false;
    }

} // namespace grid
