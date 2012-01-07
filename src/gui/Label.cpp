/*
Grid
gui/Label.cpp

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

#include "gui/Label.hpp"

namespace gui
{
    Label & Label::setText(const std::string & text)
    {
        m_text = text;
        m_renderText.SetText(text);
        m_renderText.SetSize(16);
        return *this;
    }

    Label & Label::setImage(const sf::Image & img)
    {
        m_image.SetImage(img);
        return *this;
    }

    Label & Label::setFont(const sf::Font & font)
    {
        m_renderText.SetFont(font);
        return *this;
    }

    void Label::render(sf::RenderWindow & screen)
    {
        Vector2i absPos = getPositionAbsolute();

        m_image.SetPosition(absPos.x, absPos.y);
        m_renderText.SetPosition(absPos.x, absPos.y);

        screen.Draw(m_image);
        screen.Draw(m_renderText);
    }

} // namespace gui

