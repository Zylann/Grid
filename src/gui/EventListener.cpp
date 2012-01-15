/*
Grid
EventListener.hpp

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

#include "gui/EventListener.hpp"

namespace gui
{
    bool EventListener::onEvent(const sf::Event & e, const Vector2i & p_mousePos)
    {
        static Vector2i lastMousePos, mousePos; // Note : we know that the mouse is unique

        if(!m_enabled)
            return false;

        lastMousePos = mousePos;

        switch(e.Type)
        {
            // Key press
            case sf::Event::KeyPressed :
                return keyPressEvent(e.Key.Code, e.Key.Code);

            // Key release
            case sf::Event::KeyReleased :
                return keyReleaseEvent(e.Key.Code, e.Key.Code);

            case sf::Event::TextEntered :
                return textEnteredEvent(e.Text.Unicode);

            // Mouse press
            case sf::Event::MouseButtonPressed :
                mousePos = p_mousePos;
                if(e.MouseButton.Button == sf::Mouse::Right)
                    return mouseRightPressEvent(mousePos);
                else if(e.MouseButton.Button == sf::Mouse::Left)
                    return mouseLeftPressEvent(mousePos);
                else
                    return false;

            // Mouse release
            case sf::Event::MouseButtonReleased :
                mousePos = p_mousePos;
                if(e.MouseButton.Button == sf::Mouse::Right)
                    return mouseRightReleaseEvent(mousePos);
                else if(e.MouseButton.Button == sf::Mouse::Left)
                    return mouseLeftReleaseEvent(mousePos);
                else
                    return false;

            // Mouse wheel
            case sf::Event::MouseWheelMoved :
                if(e.MouseWheel.Delta < 0)
                    return mouseWheelDownEvent();
                else if(e.MouseWheel.Delta > 0)
                    return mouseWheelUpEvent();
                else
                    return false;

            // Mouse move
            case sf::Event::MouseMoved :
                mousePos = p_mousePos;
                return mouseMoveEvent(lastMousePos, mousePos);

            default : break;
        }
        return false;
    }

} // namespace gui
