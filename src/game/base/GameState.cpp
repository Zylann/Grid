/*
Grid
GameState.cpp

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

#include "game/base/GameState.hpp"

using namespace util;

namespace grid
{
    GameState::GameState(int stateID, Game * game, GameState * parent)
    : gui::EventListener(), State(stateID), StateMachine<GameState>()
    {
        m_gui = NULL;
        r_game = game;
        r_parent = parent;
    }

    GameState::~GameState()
    {
        // Deleting GUI
        if(m_gui != NULL)
            delete m_gui;

        std::cout << "State " << getID() << " deleted" << std::endl;
    }

    void GameState::init()
    {
        // Creating GUI
        if(getGui() == NULL)
            createGui();

        // Initializing sub-states
        std::map<int, GameState*>::iterator it;
        for(it = m_states.begin(); it != m_states.end(); it++)
            it->second->init();
    }

    bool GameState::onEvent(const sf::Event & e, const Vector2i & mouse)
    {
        if(m_gui != NULL)
        {
            // return true if the gui processed the event
            if(m_gui->onEvent(e, mouse))
                return true;
        }
        GameState * currentState = getCurrentState();
        // Or other events...
        if(gui::EventListener::onEvent(e, mouse))
            return true;
        if(currentState != NULL)
        {
            // A sub state can intercept the event
            if(currentState->onEvent(e, mouse))
                return true;
        }
        return false;
    }

    void GameState::update(GameUpdate & up)
    {
        if(getCurrentState() != NULL)
            getCurrentState()->update(up);
    }

    void GameState::render(Graphics & gfx)
    {
        if(getCurrentState() != NULL)
            getCurrentState()->render(gfx);
    }

    /* GUI */

    bool GameState::isGuiOpened()
    {
        if(m_gui == NULL)
            return false;
        return m_gui->isVisible();
    }

    void GameState::openGui()
    {
        if(m_gui == NULL)
            return;
        m_gui->setVisible(true);
        m_gui->enable(true);
    }

    void GameState::closeGui()
    {
        if(m_gui == NULL)
            return;
        m_gui->setVisible(false);
        m_gui->enable(false);
    }

} // namespace grid

