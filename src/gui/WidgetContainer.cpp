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

    // Virtual
    bool WidgetContainer::onEvent(const sf::Event & e, const Vector2i & mousePos)
    {
        if(!isEnabled())
            return false;

        // Children
        std::list<Widget*>::iterator it;
        for(it = m_children.begin(); it != m_children.end(); it++)
        {
            if((*it)->onEvent(e, mousePos))
                return true;
        }
        return EventListener::onEvent(e, mousePos);
    }

    // Virtual
    void WidgetContainer::render(sf::RenderWindow & screen)
    {
        // Render children
        std::list<Widget*>::iterator it;
        for(it = m_children.begin(); it != m_children.end(); it++)
        {
            (*it)->render(screen);
        }
    }

} // namespace gui

