/*
Grid
Widget.hpp

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

#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "gui/EventListener.hpp"

namespace gui
{
    class WidgetContainer;

    class Widget : public EventListener
    {
    protected :

        // Geometry
        Vector2i m_pos;
        Vector2i m_size;

        // State
        bool m_hovered; // is the cursor over the widget ?
        bool m_pressed; // is the widget activated by click or keypress ?
        bool m_visible; // is the widget visible ?
        bool m_focused; // is the widget receives keyboard events ?

        Vector2i m_lastMousePressPosition;

        // Parent
        WidgetContainer * r_parent;

    public :

        Widget(int x, int y, int w, int h, WidgetContainer * parent = NULL)
        {
            m_hovered = false;
            m_pressed = false;
            m_focused = false;
            m_visible = true;

            r_parent = parent;

            setGeometry(x, y, w, h);
        }

        virtual ~Widget()
        {}

        virtual void render(sf::RenderWindow & screen)
        {}

        /* State */

        inline bool isHovered() const { return m_hovered; }
        inline bool isPressed() const { return m_pressed; }
        inline bool isVisible() const { return m_visible; }
        inline bool isFocused() const { return m_focused; }

        inline const Vector2i & getLastMousePressPosition() const
        { return m_lastMousePressPosition; }

        void setVisible(bool visible);
        void setHovered(bool h);
        void setPressed(bool p);
        void setFocused(bool f);

        void show() { setVisible(true); }

    protected :

        /* Events */

        virtual void onShow() {}
        virtual void onHide() {}
        virtual void onHover() {}
        virtual void onPress() {}
        virtual void onFocus() {}

    public :

        virtual bool onEvent(const sf::Event & e, const Vector2i & mousePos);

        virtual bool mouseLeftPressEvent(Vector2i pos);

        /* Geometry */

        inline const Vector2i & getPosition() const { return m_pos; }
        inline const Vector2i & getSize() const { return m_size; }
        const Vector2i getPositionAbsolute() const;
        bool contains(const Vector2i & pos) const;

        void setPosition(int x, int y);
        void setGeometry(int x, int y, int w, int h);

        /* Parent */

        inline WidgetContainer * getParent() const { return r_parent; }
        void setParent(WidgetContainer * p);

        void popup();
    };

} // namespace gui


#endif // WIDGET_HPP_INCLUDED
