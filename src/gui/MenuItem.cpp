/*
Grid
gui/MenuItem.cpp

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

#include "gui/MenuItem.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    void MenuItem::render(sf::RenderWindow & screen)
    {
        if(!isVisible())
            return;

        Theme::getTheme().renderMenuItem(*this, screen);

        const Vector2i absPos = getPositionAbsolute();
        m_renderText.SetPosition(absPos.x, absPos.y);
        screen.Draw(m_renderText);
    }

    void MenuItem::setMenu(Menu * menu)
    {
        r_menu = menu;
    }

    void MenuItem::onActionPerformed()
    {
        if(r_menu == NULL)
            return;
        r_menu->onItemSelect(this);
    }

    bool MenuItem::isFirst() const
    {
        if(r_menu == NULL)
            return false;
        return getIndex() == 0;
    }

    bool MenuItem::isLast() const
    {
        if(r_menu == NULL)
            return false;
        return getIndex() == r_menu->getItemCount();
    }

} // namespace gui

