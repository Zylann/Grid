/*
Grid
gui/MenuItem.hpp

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

#ifndef GUIMENUITEM_HPP_INCLUDED
#define GUIMENUITEM_HPP_INCLUDED

#include "gui/Button.hpp"
#include "gui/Menu.hpp"

namespace gui
{
    class MenuItem : public Button
    {
    protected :

        Menu * r_menu;
        int m_index;

    public :

        MenuItem(const std::string & text,
               const sf::Font & font,
               Menu * parent = NULL)
        : Button(0, 0, 0, 0, text, font, parent)
        {
            r_menu = parent;
            m_index = -1;
        }

        ~MenuItem()
        {}

        virtual void render(sf::RenderWindow & screen);

        virtual void onActionPerformed();

        void setMenu(Menu * menu);
        void setIndex(int index) { m_index = index; }
        int getIndex() const { return m_index; }
        bool isLast() const;
        bool isFirst() const;
    };

} // namespace gui


#endif // GUIMENUITEM_HPP_INCLUDED
