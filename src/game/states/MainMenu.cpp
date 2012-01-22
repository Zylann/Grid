/*
Grid
MainMenu.cpp

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

#include "game/states/MainMenu.hpp"
#include "game/GameUpdate.hpp"
#include "game/GuiTheme.hpp"

#include "gui/Button.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    MainMenu::~MainMenu()
    {
        std::cout << "MainMenu deletion" << std::endl;
    }

    void MainMenu::createGui()
    {
        // The main theme is defined here
        if(m_gui == NULL)
            gui::Theme::setTheme(new GuiTheme());

        m_gui = new gui::WidgetContainer(0,0,800,600);
        gui::Frame * frame = new gui::Frame(100, 100, 600, 400);

        const sf::Font & font = resources::getFont("monofont");

        gui::Button * startBtn = new gui::Button(100, 100, 300, 24, "Start game", font);
        startBtn->setAction(new gui::Action<MainMenu>(this, &MainMenu::startGame));

        gui::Button * editorBtn = new gui::Button(100, 130, 300, 24, "Editor", font);
        editorBtn->setAction(new gui::Action<MainMenu>(this, &MainMenu::enterEditor));

        gui::Button * quitBtn = new gui::Button(100, 160, 300, 24, "Quit game", font);
        quitBtn->setAction(new gui::Action<Game>(r_game, &Game::quit));

        frame->addChild(startBtn);
        frame->addChild(editorBtn);
        frame->addChild(quitBtn);

        m_gui->addChild(frame);
    }

    void MainMenu::startGame()
    {
        r_game->enterState(ST_GAME_PLAY);
    }

    void MainMenu::enterEditor()
    {
        r_game->enterState(ST_WORLD_EDITOR);
    }

    void MainMenu::onEnter()
    {
        m_background.SetImage(resources::getImage("main"));
    }

    void MainMenu::update(GameUpdate & up)
    {
    }

    void MainMenu::render(Graphics & gfx)
    {
        const sf::FloatRect rect = gfx.getCurrentView().GetRect();
        m_background.SetPosition(rect.Left, rect.Top);
        m_background.Resize(rect.GetWidth(), rect.GetHeight());

        gfx.draw(m_background);

        gfx.setView(VIEW_INTERFACE);
        gfx.draw(*m_gui);
    }

    void MainMenu::onLeave()
    {
    }

} // namespace grid

