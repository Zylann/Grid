/*
Grid
Console.hpp

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

#ifndef CONSOLE_HPP_INCLUDED
#define CONSOLE_HPP_INCLUDED

#include "common.hpp"

#include "gui/WidgetContainer.hpp"
#include "gui/TextBar.hpp"

namespace gui
{
    class Console;

    class ConsoleLine
    {
    protected :

        sf::String m_renderText;

    public :

        ConsoleLine(const std::string & text, const sf::Font & font);

        sf::String & getRenderText() { return m_renderText; }

        virtual void render(sf::RenderWindow & screen, Console & console, int index);
    };

    class Console : public WidgetContainer
    {
    protected :

        std::list<ConsoleLine*> m_lines;
        unsigned int m_linesLimit;
        TextBar * r_textBar;
        GenericAction * m_enterAction; // callback when we press 'enter'
        const sf::Font * r_font;

    public :

        Console(int x, int y, int w, int h, const sf::Font * font,
               GenericAction * enterAction = NULL,
               Widget * parent = NULL);

        virtual ~Console()
        {
            if(m_enterAction != NULL)
                delete m_enterAction;
            clear();
        }

        TextBar & getTextBar() { return *r_textBar; }

        virtual void onEnter();
        void clear();
        virtual void addLine(const std::string & text);

        virtual void render(sf::RenderWindow & screen);
    };

} // namespace gui


#endif // CONSOLE_HPP_INCLUDED
