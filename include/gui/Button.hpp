/*
Grid
gui/Button.hpp

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

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "gui/Widget.hpp"
#include "gui/Action.hpp"

namespace gui
{
    class Button : public Widget
    {
    protected :

        std::string m_text;
        sf::String m_renderText;
        GenericAction * m_action;

    public :

        Button(int x, int y, int w, int h,
               const std::string & text,
               const sf::Font & font,
               Widget * parent = NULL)
        : Widget(x, y, w, h, parent)
        {
            m_renderText.SetFont(font);
            setText(text);
            m_action = NULL;
        }

        ~Button()
        {
            if(m_action != NULL)
                delete m_action;
        }

        const std::string & getText() const { return m_text; }
        const sf::String & getRenderText() const { return m_renderText; }
        void setText(const std::string & text);

        void setAction(GenericAction * a);

        virtual bool mouseLeftPressEvent(Vector2i pos);
        virtual bool mouseLeftReleaseEvent(Vector2i pos);
        virtual bool mouseMoveEvent(Vector2i previous, Vector2i current);

        virtual void onHover();
        virtual void onPress();

        virtual void render(sf::RenderWindow & screen);
    };

} // namespace gui


#endif // BUTTON_HPP_INCLUDED
