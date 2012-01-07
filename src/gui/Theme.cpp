/*
Grid
Theme.cpp

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

#include "gui/Theme.hpp"

namespace gui
{
    /*
        Static methods
    */

    Theme * g_theme = NULL;

    void Theme::setTheme(Theme * newTheme)
    {
        if(g_theme != NULL)
            delete g_theme;
        g_theme = newTheme;
    }

    Theme & Theme::getTheme()
    {
        if(g_theme == NULL)
            g_theme = new Theme(); // default theme
        return *g_theme;
    }

    void Theme::freeThemes()
    {
        if(g_theme != NULL)
        {
            delete g_theme;
            g_theme = NULL;
        }
    }

    void Theme::renderButton(Button & button, sf::RenderWindow & screen)
    {
        // Test code
        Vector2i A = button.getPositionAbsolute();
        Vector2i B = A + button.getSize();
        sf::Color color(128,128,128, 192);

        if(button.isEnabled())
        {
            color.r = 0;
            color.g = 0;
            color.b = 255;

            if(button.isHovered())
                color.g = 128;
            if(button.isPressed())
                color.b = 128;
        }
        screen.Draw(sf::Shape::Rectangle(A.x, A.y, B.x, B.y, color));
    }

    void Theme::renderFrame(Frame & frame, sf::RenderWindow & screen)
    {
        // Test code
        Vector2i A = frame.getPositionAbsolute();
        Vector2i B = A + frame.getSize();
        screen.Draw(sf::Shape::Rectangle(A.x, A.y, B.x, B.y, sf::Color(0,0,128,192)));
    }

} // namespace gui

