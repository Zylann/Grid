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
            color.r = 192;
            color.g = 192;
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

        sf::Color back(128,128,128,128);
        sf::Color border(192,192,255,224);

        if(!frame.isEnabled())
        {
            border = back;
        }

        screen.Draw(sf::Shape::Rectangle(A.x, A.y, B.x, B.y, back, 3, border));
    }

    void GuiTheme::renderTextBar(TextBar & textBar, sf::RenderWindow & screen)
    {
        Vector2i A = textBar.getPositionAbsolute();
        Vector2i B = A + textBar.getSize();
        screen.Draw(sf::Shape::Rectangle(
            A.x, A.y, B.x, B.y, sf::Color(0,0,0,128), 3, sf::Color(192,192,255,224)));

        if(textBar.isFocused())
        {
            sf::Color caretColor(255,255,255);
            caretColor.a = 128.f + 64.f * (1.f + cos(8.f * m_time.GetElapsedTime()));

            int caretIndex = textBar.getCaretPosition();
            const sf::String & renderText = textBar.getRenderText();

            Vector2f caretPos1 = renderText.GetCharacterPos(caretIndex);
            caretPos1.x += A.x + 2;
            caretPos1.y += A.y + 2;
            Vector2f caretPos2 = caretPos1;
            caretPos2.y += textBar.getSize().y - 4;

            screen.Draw(sf::Shape::Line(caretPos1, caretPos2, 2, caretColor));
        }
    }

    void GuiTheme::renderConsoleLine(
        ConsoleLine & line, Console & console,
        int index, sf::RenderWindow & screen)
    {
        if(!console.getTextBar().isFocused())
            return;

        Vector2i barSize = console.getTextBar().getSize();
        Vector2i ipos = console.getPositionAbsolute();

        Vector2f A(ipos.x, ipos.y);
        A.y -= (index + 1) * (barSize.y - 6) + 6;

        Vector2f B = A;
        B.x += barSize.x;
        B.y += barSize.y - 6;

        screen.Draw(sf::Shape::Rectangle(A, B, sf::Color(0,0,0,128)));

        line.getRenderText().SetPosition(A);
        screen.Draw(line.getRenderText());
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

