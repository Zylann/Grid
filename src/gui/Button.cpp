/*
Grid
Button.cpp

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

#include "gui/Button.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    void Button::setAction(GenericAction * a)
    {
        if(m_action != NULL)
            delete m_action;
        m_action = a;
    }

    void Button::setText(const std::string & text)
    {
        m_text = text;
        m_renderText.SetText(text);
        m_renderText.SetSize(16);
    }

    // Virtual
    bool Button::mouseLeftPressEvent(Vector2i pos)
    {
        if(m_hovered)
        {
            setPressed(true);
            return true;
        }
        return false;
    }

    // Virtual
    bool Button::mouseLeftReleaseEvent(Vector2i pos)
    {
        if(m_pressed && m_hovered)
        {
            setPressed(false);
            if(m_action != NULL)
                m_action->execute();
            return true;
        }
        setPressed(false);
        return false;
    }

    // Virtual
    bool Button::mouseMoveEvent(Vector2i previous, Vector2i current)
    {
        if(contains(current))
            setHovered(true);
        else
            setHovered(false);
        return false;
    }

    void Button::onHover()
    {
        Theme::getTheme().playButtonHoverSound();
    }

    void Button::onPress()
    {
        Theme::getTheme().playButtonPressSound();
    }

    // Virtual
    void Button::render(sf::RenderWindow & screen)
    {
        Theme::getTheme().renderButton(*this, screen);

        const Vector2i absPos = getPositionAbsolute();
        m_renderText.SetPosition(absPos.x, absPos.y);
        screen.Draw(m_renderText);
    }

} // namespace gui

