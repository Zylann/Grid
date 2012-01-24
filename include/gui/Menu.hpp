/*
Grid
gui/Menu.hpp

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

#ifndef GUIMENU_HPP_INCLUDED
#define GUIMENU_HPP_INCLUDED

#include "gui/WidgetContainer.hpp"
#include "gui/Action.hpp"
//#include "gui/MenuItem.hpp"

namespace gui
{
    class MenuItem;

    class Menu : public WidgetContainer
    {
    protected :

        int m_itemCount;

    public :

        Menu(int x, int y, int w, int h,
             WidgetContainer * parent = NULL)
        : WidgetContainer(x, y, w, h, parent)
        {
            m_itemCount = 0;
        }

        ~Menu()
        {}

        virtual void render(sf::RenderWindow & screen);

        int addItem(MenuItem * item);
        int addItem(const std::string & text, const sf::Font & font, GenericAction * action);
        int getItemCount() const { return m_itemCount; }

        void onItemSelect(MenuItem * item);
        virtual bool mouseLeftPressEvent(Vector2i pos);
    };

} // namespace gui


#endif // GUIMENU_HPP_INCLUDED
