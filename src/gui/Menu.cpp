/*
Grid
Menu.cpp

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

#include "gui/Menu.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    void Menu::render(sf::RenderWindow & screen)
    {
        if(!isVisible())
            return;

        // Render menu background
        Theme::getTheme().renderMenu(*this, screen);

        // Render children
        WidgetContainer::render(screen);
    }

    int Menu::addItem(MenuItem * item)
    {
        const int itemH = 24;
        const int itemY = m_itemCount * itemH;

        item->setGeometry(0, itemY, m_size.x, itemH);
        item->setMenu(this);
        item->setIndex(m_itemCount);

        WidgetContainer::addChild(item);

        setGeometry(m_pos.x, m_pos.y, m_size.x, itemY + itemH);

        m_itemCount++;

        return m_itemCount - 1;
    }

    int Menu::addItem(const std::string & text, const sf::Font & font, GenericAction * action)
    {
        MenuItem * item = new MenuItem(text, font);
        item->setAction(action);
        return addItem(item);
    }

    void Menu::onItemSelect(MenuItem * item)
    {
        setVisible(false);
    }

    bool Menu::mouseLeftPressEvent(Vector2i pos)
    {
        if(!contains(pos) && isVisible())
        {
            setVisible(false);
            return true;
        }
        return false;
    }

} // namespace gui

