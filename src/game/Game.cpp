/*
Grid
Game.cpp

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

#include "game/Game.hpp"
#include "game/Terrain.hpp"
#include "game/Sound.hpp"
#include "game/GameUpdate.hpp"
#include "game/states/GamePlay.hpp"
#include "game/states/MainMenu.hpp"
#include "game/states/Loading.hpp"
#include "game/states/WorldEditor.hpp"

#include "gui/Theme.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    Game::Game() : StateMachine<GameState>()
    {
        // Create the main window
        m_screen.Create(
            sf::VideoMode(800, 600), "Grid experimental version",
            sf::Style::Resize | sf::Style::Close,
            sf::WindowSettings(24, 8, 3));

        m_screen.UseVerticalSync(true);

        // Framerate
        m_screen.SetFramerateLimit(60);

        // Hiding mouse cursor
        m_screen.ShowMouseCursor(false);

        // Creating graphics wrapper
        m_graphics = new Graphics(m_screen, 32);

        // creating states
        addState( new Loading(ST_LOADING, this) );
        addState( new MainMenu(ST_MAIN_MENU, this) );
        addState( new GamePlay(ST_GAME_PLAY, this) );
        addState( new WorldEditor(ST_WORLD_EDITOR, this) );

        // Creating terrain types
        terrain::Ground::init();
        terrain::Block::init();

        // Creating debug display
        m_debugDisplay = new DebugDisplay();
        m_debugDisplay->enable(false);

        m_runFlag = false;
        m_cursorVisible = true;
    }

    Game::~Game()
    {
        std::cout << "Game destruction..." << std::endl;

        // Deleting graphics engine
        delete m_graphics;

        // Deleting terrain types
        terrain::Ground::freeAll();
        terrain::Block::freeAll();

        // Deleting sound engine
        Sound::kill();

        // Deleting debug display
        if(m_debugDisplay != NULL)
            delete m_debugDisplay;

        // Deleting gui themes
        gui::Theme::freeThemes();

        std::cout << "Game deleted (IC = " << GameObject::getInstanceCount() << ")" << std::endl;
    }

    void Game::init()
    {
        std::map<int, GameState*>::iterator it;
        for(it = m_states.begin(); it != m_states.end(); it++)
            it->second->init();
    }

    void Game::setCursorImage(const sf::Image & img)
    {
        m_cursor.SetImage(img);
    }

    void Game::run()
    {
        std::cout << "Game begin" << std::endl;

        // Entering first state : it must exist
        enterState(ST_LOADING);
        if(getCurrentState() == NULL)
        {
            std::cout << "ERROR: Game::run: "
                << "the game couldn't run because no starting state were specified" << std::endl;
            return;
        }

        sf::Event event;
        sf::String fpsText("FPS");
        sf::Clock timer;
        Vector2f sceneMouseCoords;
        const sf::Input & input = m_screen.GetInput();

        // Debug
        float updateTime = 0;
        float renderTime = 0;
        float frameTime = 0;

        m_runFlag = true;

        // Main loop
        while(m_screen.IsOpened() && m_runFlag)
        {
            /* Updating */

            // Get frame time (delta)
            frameTime = m_screen.GetFrameTime();
            if(frameTime > 0.05)
                frameTime = 0.05;

            GameUpdate up(frameTime);
            up.game = this;

            m_graphics->setView(VIEW_INTERFACE);

            sceneMouseCoords =
                m_screen.ConvertCoords(input.GetMouseX(), input.GetMouseY());

            // Polling input events
            while(m_screen.GetEvent(event))
            {
                if(event.Type == sf::Event::Closed)
                    m_runFlag = false;
                else if(event.Type == sf::Event::Resized)
                    m_graphics->onScreenSizeChange();
                else if(event.Type == sf::Event::KeyReleased)
                {
                    if(event.Key.Code == sf::Key::F3)
                        m_debugDisplay->enable(!m_debugDisplay->isEnabled());
                }
                else if(event.Type == sf::Event::MouseWheelMoved)
                {
                    if(event.MouseWheel.Delta > 0)
                        up.mouseWheelUp = true;
                    if(event.MouseWheel.Delta < 0)
                        up.mouseWheelDown = true;
                }

                getCurrentState()->onEvent(
                    event, Vector2i(sceneMouseCoords.x, sceneMouseCoords.y));
            }

            timer.Reset();

            // Updating current state
            getCurrentState()->update(up);

            // Updating sound
            Sound::instance().update();

            updateTime = timer.GetElapsedTime();

            /* Rendering */

            // clearing screen
            timer.Reset();
            m_screen.Clear();

            // drawing scene and interface
            r_currentState->render(*m_graphics);

            m_graphics->setView(VIEW_INTERFACE);

            // cursor
            if(m_cursor.GetImage() != NULL && m_cursorVisible)
            {
                m_cursor.SetPosition(sceneMouseCoords);
                m_graphics->draw(m_cursor);
            }

            // Debug display
            if(m_debugDisplay != NULL)
            {
                if(m_debugDisplay->isEnabled())
                {
                    // Updating debug display
                    m_debugDisplay->setFrameTime(frameTime)
                        .setObjectsCount(GameObject::getInstanceCount())
                        .setUpdateTime(updateTime)
                        .setRenderTime(renderTime);

                    m_debugDisplay->update(frameTime);

                    // Drawing debug display
                    m_screen.SetView(m_screen.GetDefaultView());
                    m_debugDisplay->render(*m_graphics);
                }
            }
            renderTime = timer.GetElapsedTime();

            // displaying all
            m_screen.Display();
        }

        m_runFlag = false;

        if(m_screen.IsOpened())
            m_screen.Close();

        std::cout << "Game end" << std::endl;
    }

    const Vector2f Game::getSceneMouseCoords()
    {
        // TODO Preserve current view
        const sf::Input & input = m_screen.GetInput();
        m_graphics->setView(VIEW_GAME);
        return m_screen.ConvertCoords(input.GetMouseX(), input.GetMouseY());
    }

} // namespace grid



