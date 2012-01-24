/*
Grid
Console.cpp

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

#include "gui/Console.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    /*
        ConsoleLine
    */

    ConsoleLine::ConsoleLine(const std::string & text, const sf::Font & font)
    {
        m_renderText.SetFont(font);
        m_renderText.SetSize(16);
        m_renderText.SetText(text);
    }

    void ConsoleLine::render(sf::RenderWindow & screen, Console & console, int index)
    {
        Theme::getTheme().renderConsoleLine(*this, console, index, screen);
    }

    /*
        Console
    */

    Console::Console(int x, int y, int w, int h, const sf::Font * font,
           GenericAction * enterAction, WidgetContainer * parent)
    : WidgetContainer(x, y, w, h, parent)
    {
        m_enterAction = enterAction;
        r_font = font;
        m_linesLimit = 16;

        r_textBar = new TextBar(0, 0, w, h, *font, new Action<Console>(this, &Console::onEnter));

        addChild(r_textBar);
    }

    void Console::onEnter()
    {
        if(r_textBar->getText().empty())
            return;

        addLine(r_textBar->getText());

        if(m_enterAction != NULL)
            m_enterAction->execute();

        r_textBar->clearText();
    }

    void Console::addLine(const std::string & text)
    {
        if(r_font == NULL)
        {
            std::cout << "WARNING: Console::addLine: no font referenced !" << std::endl;
            return;
        }
        ConsoleLine * line = new ConsoleLine(text, *r_font);
        m_lines.push_front(line);

        if(m_lines.size() > m_linesLimit)
        {
            delete m_lines.back();
            m_lines.pop_back();
        }
    }

    void Console::clear()
    {
        std::list<ConsoleLine*>::iterator it;
        for(it = m_lines.begin(); it != m_lines.end(); it++)
        {
            delete (*it);
        }
        m_lines.clear();
        r_textBar->clearText();
    }

    void Console::render(sf::RenderWindow & screen)
    {
        if(!isVisible())
            return;
        WidgetContainer::render(screen);

        std::list<ConsoleLine*>::iterator it;
        int index = 0;
        for(it = m_lines.begin(); it != m_lines.end(); it++, index++)
        {
            (*it)->render(screen, *this, index);
        }
    }

} // namespace gui

