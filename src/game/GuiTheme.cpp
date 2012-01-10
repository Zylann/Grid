/*
Grid
GuiTheme.cpp

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

#include "game/GuiTheme.hpp"
#include "game/Sound.hpp"

using namespace gui;

namespace grid
{
    void GuiTheme::renderButton(Button & button, sf::RenderWindow & screen)
    {
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

    void GuiTheme::renderFrame(Frame & frame, sf::RenderWindow & screen)
    {
        Vector2i A = frame.getPositionAbsolute();
        Vector2i B = A + frame.getSize();
        screen.Draw(sf::Shape::Rectangle(A.x, A.y, B.x, B.y, sf::Color(0,0,128,192)));
    }

    void GuiTheme::playButtonHoverSound()
	{
        Sound::instance().playSound("guiSelect", 1, 30);
    }

    void GuiTheme::playButtonPressSound()
    {
        Sound::instance().playSound("guiPress");
    }

    void GuiTheme::playShowFrameSound()
    {
        Sound::instance().playSound("guiOpen");
    }

    void GuiTheme::playHideFrameSound()
    {
        Sound::instance().playSound("guiClose");
    }

} // namespace grid
