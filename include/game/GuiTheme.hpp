/*
Grid
GuiTheme.hpp

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

#ifndef GUITHEME_HPP_INCLUDED
#define GUITHEME_HPP_INCLUDED

#include "gui/Theme.hpp"

namespace grid
{
    class GuiTheme : public gui::Theme
    {
    protected :

        sf::Clock m_time;

    public :

        GuiTheme() : gui::Theme()
        {}

        virtual ~GuiTheme()
        {}

        virtual void renderButton(gui::Button & button, sf::RenderWindow & screen);
        virtual void renderFrame(gui::Frame & frame, sf::RenderWindow & screen);
        virtual void renderTextBar(gui::TextBar & textBar, sf::RenderWindow & screen);
        virtual void renderMenu(gui::Menu & menu, sf::RenderWindow & screen);
        virtual void renderMenuItem(gui::MenuItem & item, sf::RenderWindow & screen);

        virtual void renderConsoleLine(
            gui::ConsoleLine & line, gui::Console & console,
            int index, sf::RenderWindow & screen);

        virtual void playButtonHoverSound();
        virtual void playButtonPressSound();
        virtual void playShowFrameSound();
        virtual void playHideFrameSound();
    };

} // namespace grid


#endif // GUITHEME_HPP_INCLUDED
