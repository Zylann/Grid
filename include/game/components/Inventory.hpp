/*
Grid
Inventory.hpp

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

#ifndef INVENTORY_HPP_INCLUDED
#define INVENTORY_HPP_INCLUDED

#include <vector>

#include "game/base/Component.hpp"
#include "game/base/Item.hpp"

#define PLAYER_INVENTORY_SIZE 8

namespace grid
{
    /*
        The owner of the inventory can store and use items (except instant items).
    */

    class Inventory : public Component
    {
    protected :

        std::vector<Item*> m_items; // slots
        int m_currentX;

    public :

        Inventory(int width = PLAYER_INVENTORY_SIZE, int ID = -1) : Component(ID)
        {
            if(width < 1)
                width = 1;

            m_items.resize(width, NULL);
            m_currentX = 0;
        }

        ~Inventory()
        {
            clear();
        }

        // Clears the inventory's content
        void clear()
        {
            for(unsigned int i = 0; i < m_items.size(); i++)
            {
                if(m_items[i] != NULL)
                {
                    delete m_items[i];
                    m_items[i] = NULL;
                }
            }
        }

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);
        virtual void registerRender(RenderManager & manager);

        // Switches the current item in use.
        // dir < 0 = left, dir > 0 = right
        void switchCurrent(int dir);

        // True if there is no items in the inventory
        bool isEmpty() const;

        // True if there is no space to store an item
        bool isFull() const;

        Item * getItem(int x);
        Item * getCurrentItem() { return m_items[m_currentX]; }
        int getItemAmount() const;

        // Adds an item to the first free place in the inventory.
        // Returns true if success, false if no place was found.
        bool addItem(Item * item);

        // Drops the item stored in the specified slot
        void dropItem(int x);

        inline int getSize() const { return m_items.size(); }
        inline int getCurrentX() const { return m_currentX; }

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is) throw(GameException);
    };

} // namespace grid


#endif // INVENTORY_HPP_INCLUDED
