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

        std::list<Widget*> m_children;

    public :

        WidgetContainer(int x, int y, int w, int h, Widget* parent = NULL)
        : Widget(x, y, w, h, parent)
        {}

        virtual ~WidgetContainer()
        {
            std::list<Widget*>::iterator it;
            for(it = m_children.begin(); it != m_children.end(); it++)
                delete (*it);
        }

        virtual void render(sf::RenderWindow & screen);

        void addChild(Widget * widget);

        virtual bool onEvent(const sf::Event & e, const Vector2i & mousePos);
    };

} // namespace gui


#endif // WIDGETCONTAINER_HPP_INCLUDED
