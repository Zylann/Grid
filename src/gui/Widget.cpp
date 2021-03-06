/*
Grid
Widget.cpp

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

#include "gui/Widget.hpp"
#include "gui/WidgetContainer.hpp"

namespace gui
{
    void Widget::setGeometry(int x, int y, int w, int h)
    {
        m_pos.x = x;
        m_pos.y = y;
        m_size.x = w;
        m_size.y = h;
    }

    void Widget::setPosition(int x, int y)
    {
        m_pos.x = x;
        m_pos.y = y;
    }

    void Widget::setVisible(bool visible)
    {
        if(!m_visible && visible)
            onShow();
        else if(m_visible && !visible)
            onHide();

        m_visible = visible;
    }

    void Widget::setHovered(bool h)
    {
        if(!m_hovered && h)
            onHover();
        m_hovered = h;
    }

    void Widget::setPressed(bool p)
    {
        if(!m_pressed && p)
            onPress();
        m_pressed = p;
    }

    void Widget::setFocused(bool f)
    {
        if(!m_focused && f)
            onFocus();
        m_focused = f;
    }

    const Vector2i Widget::getPositionAbsolute() const
    {
        if(r_parent != NULL)
            return m_pos + r_parent->getPositionAbsolute();
        else
            return m_pos;
    }

    bool Widget::contains(const Vector2i & pos) const
    {
        const Vector2i absPos = getPositionAbsolute();
        return pos.x >= absPos.x && pos.x < absPos.x + m_size.x &&
               pos.y >= absPos.y && pos.y < absPos.y + m_size.y ;
    }

    void Widget::popup()
    {
        if(getParent() != NULL)
            getParent()->popupChild(this);
    }

    void Widget::setParent(WidgetContainer * p)
    {
        if(r_parent == NULL)
            r_parent = p;
//        else
//        {
//            std::cerr << "WARNING: Widget::setParent: "
//                << "the widget already have a parent" << std::endl;
//        }
    }

    bool Widget::onEvent(const sf::Event & e, const Vector2i & mousePos)
    {
        if(isVisible())
            return EventListener::onEvent(e, mousePos);
        return false;
    }

    bool Widget::mouseLeftPressEvent(Vector2i pos)
    {
        m_lastMousePressPosition = pos;
        return false;
    }

} // namespace gui

