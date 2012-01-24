/*
Grid
WidgetContainer.hpp

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

#ifndef WIDGETCONTAINER_HPP_INCLUDED
#define WIDGETCONTAINER_HPP_INCLUDED

#include <list>

#include "gui/Widget.hpp"

namespace gui
{
    class WidgetContainer : public Widget
    {
    protected :

        // Children ordered by drawing
        std::list<Widget*> m_children;

        // during onEvent, widgets can be asked to popup, but this is done after iterating
        // on children, because the list would be modified at the same time.
        // Widgets are brang to front in the same order as this list.
        // They are stored as references.
        std::list<Widget*> m_widgetsToPopup;

        // True if the container is currently iterating over m_children
        bool m_isIterating;

    public :

        // Constructs an empty container
        // Note : the size is not used the WidgetContainer itself. However, it may be important
        // for its subclasses.
        WidgetContainer(int x, int y, int w, int h, WidgetContainer * parent = NULL)
        : Widget(x, y, w, h, parent)
        {
            m_isIterating = false;
        }

        // Destroys the container and its children
        virtual ~WidgetContainer()
        {
            std::list<Widget*>::iterator it;
            for(it = m_children.begin(); it != m_children.end(); it++)
                delete (*it);
        }

        // Renders children widgets and the container (if needed)
        virtual void render(sf::RenderWindow & screen);

        // Dispatch events on children and the container (if needed)
        virtual bool onEvent(const sf::Event & e, const Vector2i & mousePos);

        // Adds a widget in front of the others
        virtual void addChild(Widget * widget);

        // Executes doPopupChild after iterations over m_children
        void popupChild(Widget * w);
    };

} // namespace gui


#endif // WIDGETCONTAINER_HPP_INCLUDED
