/*
Grid
WidgetContainer.cpp

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

#include "gui/WidgetContainer.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    void WidgetContainer::addChild(Widget * widget)
    {
        if(widget->getParent() == NULL)
        {
            widget->setParent(this);
            m_children.push_back(widget);
        }
        else
        {
            std::cout << "ERROR: WidgetContainer::addChild:"
                << "cannot add a children that have already a parent" << std::endl;
            delete widget;
        }
    }

    bool WidgetContainer::onEvent(const sf::Event & e, const Vector2i & mousePos)
    {
        if(!isEnabled() || !isVisible())
            return false;

        // Children
        // Note : for events, the list is in reverse order
        m_isIterating = true;
        std::list<Widget*>::reverse_iterator rit;
        for(rit = m_children.rbegin(); rit != m_children.rend(); rit++)
        {
            // Only one widget can intercept the event
            if((*rit)->onEvent(e, mousePos))
                return true;
        }
        m_isIterating = false;

        // Children popups
        std::list<Widget*>::iterator it;
        for(it = m_widgetsToPopup.begin(); it != m_widgetsToPopup.end(); it++)
            popupChild(*it);
        m_widgetsToPopup.clear();

        // This
        return Widget::onEvent(e, mousePos);
    }

    void WidgetContainer::render(sf::RenderWindow & screen)
    {
        if(!isVisible())
            return;
        // Render children
        // Note : the last child receives events the first, and is drawn over the others.
        std::list<Widget*>::iterator it;
        for(it = m_children.begin(); it != m_children.end(); it++)
        {
            (*it)->render(screen);
        }
    }

    void WidgetContainer::popupChild(Widget * w)
    {
        if(m_isIterating)
        {
            // The widget will popup after the onEvent iteration
            m_widgetsToPopup.push_back(w);
            return;
        }

        // Finding the widget
        std::list<Widget*>::iterator it;
        for(it = m_children.begin(); it != m_children.end(); it++)
        {
            if((*it) == w)
                break;
        }

        // Do nothing if not found
        if(it == m_children.end())
            return;

        // Remove it and place it in front
        m_children.erase(it);
        m_children.push_back(w); // see onEvent() to understand
    }

} // namespace gui

