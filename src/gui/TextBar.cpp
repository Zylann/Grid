/*
Grid
TextBar.cpp

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

#include "gui/TextBar.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    void TextBar::setText(const std::string & text)
    {
        m_text = text;
        m_renderText.SetText(text);
        m_renderText.SetSize(16);
    }

    int TextBar::getCaretPosition() const
    {
        return m_text.size();
    }

    void TextBar::executeEnterAction()
    {
        if(m_enterAction != NULL)
            m_enterAction->execute();
    }

    bool TextBar::mouseLeftPressEvent(Vector2i pos)
    {
        if(m_hovered)
        {
            setPressed(true);
            setFocused(true);
            return true;
        }
        else
            setFocused(false);
        return false;
    }

    bool TextBar::mouseMoveEvent(Vector2i previous, Vector2i current)
    {
        if(contains(current))
            setHovered(true);
        else
            setHovered(false);
        return false;
    }

    bool TextBar::keyPressEvent(sf::Key::Code key, char character)
    {
        if(!isFocused())
            return false;

        std::cout << "'" << character << "' : " << m_text << std::endl;
        if(key == sf::Key::Return)
        {
            executeEnterAction();
            return true;
        }
        else if(key == sf::Key::Back)
        {
            if(!m_text.empty())
            {
                m_text = m_text.substr(0, m_text.size() - 1);
                m_renderText.SetText(m_text);
                return true;
            }
        }
        return false;
    }

    bool TextBar::textEnteredEvent(unsigned int unicode)
    {
        if(!isFocused())
            return false;

        if(unicode >= 31 && unicode <= 126) // if the character is printable and in ASCII table
        {
            m_text += (char)unicode;
            m_renderText.SetText(m_text);
            return true;
        }
        return false;
    }

    void TextBar::render(sf::RenderWindow & screen)
    {
        Theme::getTheme().renderTextBar(*this, screen);

        const Vector2i absPos = getPositionAbsolute();
        m_renderText.SetPosition(absPos.x, absPos.y);
        screen.Draw(m_renderText);
    }

} // namespace gui

