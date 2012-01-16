/*
Grid
gui/Theme.hpp

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

#ifndef THEME_HPP_INCLUDED
#define THEME_HPP_INCLUDED

#include "gui/Button.hpp"
#include "gui/Frame.hpp"
#include "gui/TextBar.hpp"
#include "gui/Console.hpp"

namespace gui
{
    class Theme
    {
    public :

        Theme()
        {}

        virtual ~Theme()
        {}

        // Note : at the moment, there is only one theme
        static void setTheme(Theme * newTheme);
        static Theme & getTheme();
        static void freeThemes();

        virtual void renderButton(Button & button, sf::RenderWindow & screen);
        virtual void renderFrame(Frame & frame, sf::RenderWindow & screen);
        virtual void renderTextBar(TextBar & textBar, sf::RenderWindow & screen) {}

        virtual void renderConsoleLine(
            ConsoleLine & line, Console & console,
            int index, sf::RenderWindow & screen)
        {}

        virtual void playButtonHoverSound() {}
        virtual void playButtonPressSound() {}
        virtual void playShowFrameSound() {}
        virtual void playHideFrameSound() {}
    };

} // namespace gui


#endif // THEME_HPP_INCLUDED
