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

namespace grid
{

    GameState::GameState(int stateID, Game * game)
    {
        m_ID = stateID;
        m_gui = NULL;
        r_game = game;
    }

    GameState::~GameState()
    {
        if(m_gui != NULL)
            delete m_gui;
        std::cout << "State " << m_ID << " deleted" << std::endl;
    }

    bool GameState::onEvent(const sf::Event & e, const Vector2i & mouse)
    {
        if(m_gui != NULL)
        {
            if(m_gui->onEvent(e, mouse))
                return true;
        }
        return gui::EventListener::onEvent(e, mouse);
    }

    bool GameState::isGuiOpened()
    {
        if(m_gui == NULL)
            return false;
        return m_gui->isVisible();
    }

    void GameState::openGui()
    {
        if(m_gui != NULL)
            m_gui->setVisible(true);
    }

    void GameState::closeGui()
    {
        if(m_gui != NULL)
            m_gui->setVisible(false);
    }

} // namespace grid

