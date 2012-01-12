/*
Grid
Inventory.cpp

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

#include "game/components/Inventory.hpp"
#include "game/GameUpdate.hpp"
#include "game/entities/EntityDroppedItem.hpp"

namespace grid
{
    void Inventory::update(GameUpdate & up)
    {
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            if(m_items[i] != NULL)
            {
                m_items[i]->update(up);
                if(!m_items[i]->isValid())
                {
                    delete m_items[i];
                    m_items[i] = NULL;
                }
            }
        }
    }

    bool Inventory::processMessage(Message & msg)
    {
        Item * current = getCurrentItem();

        // Item use
        if(current != NULL)
        {
            if(msg.type == M_INV_DROP)
            {
                // TODO Inventory drop
                return true;
            }

            if(current->processMessage(msg))
                return true;
        }

        // Item selection
        if(msg.type == M_INV_LEFT)
        {
            switchCurrent(-1);
            return true;
        }
        else if(msg.type == M_INV_RIGHT)
        {
            switchCurrent(1);
            return true;
        }
        return false;
    }

    bool Inventory::isEmpty() const
    {
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            if(m_items[i] != NULL)
                return false;
        }
        return true;
    }

    bool Inventory::isFull() const
    {
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            if(m_items[i] == NULL)
                return false;
        }
        return true;
    }

    void Inventory::switchCurrent(int dir)
    {
        if(m_items[m_currentX] != NULL)
            m_items[m_currentX]->onUnselect();

        if(dir > 1)
            dir = 1;
        if(dir < -1)
            dir = -1;

        m_currentX += dir;

        if(m_currentX >= (int)(m_items.size()))
            m_currentX = 0;
        else if(m_currentX < 0)
            m_currentX = (int)(m_items.size()) - 1;

        // If the inventory is not empty, switching to the next occupied slot
        // (ergonomy optimization)
        if(!isEmpty())
        {
            while(m_items[m_currentX] == NULL)
            {
                m_currentX += dir;

                if(m_currentX >= (int)(m_items.size()))
                    m_currentX = 0;
                else if(m_currentX < 0)
                    m_currentX = (int)(m_items.size()) - 1;
            }
        }

        if(m_renderer != NULL)
            m_renderer->update();

        std::cout << "Inventory switch " << m_currentX << " : ";
        if(m_items[m_currentX] != NULL)
        {
            m_items[m_currentX]->onSelect();
            std::cout << "item";
        }
        else
            std::cout << "NULL";
        std::cout << std::endl;
    }

    Item * Inventory::getItem(int x)
    {
        if(x >= 0 && x < (int)m_items.size())
            return m_items[x];
        else
            return NULL;
    }

    bool Inventory::addItem(Item * item)
    {
        if(item == NULL)
            return false;

        // Searching for an empty slot
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            // If we found one
            if(m_items[i] == NULL)
            {
                // We store the item in it
                m_items[i] = item;
                item->setInventory(this);
                item->setInventoryPosition(i);
                item->onPick(r_owner);
                return true;
            }
        }
        return false;
    }

    int Inventory::getItemAmount() const
    {
        int sum = 0;
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            if(m_items[i] != NULL)
                sum++;
        }
        return sum;
    }

    void Inventory::registerRender(RenderManager & manager)
    {
        Component::registerRender(manager);

        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            if(m_items[i] != NULL)
            {
                m_items[i]->registerRender(manager);
            }
        }
    }


    /*
        Serialization
    */

    void Inventory::serialize(std::ostream & os)
    {
        GameObject::serialize(os);

        // Buffer size
        util::serialize(os, m_items.size());

        // Selection
        util::serialize(os, m_currentX);

        // Item amount
        util::serialize(os, getItemAmount());

        // Items
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            Item * item = m_items[i];
            if(item != NULL)
            {
                Item::serializeItem(os, *item);
            }
        }
    }

    void Inventory::unserialize(std::istream & is) throw(GameException)
    {
        GameObject::unserialize(is);

        clear();

        // Buffer size
        unsigned int bufferSize = 0;
        util::unserialize(is, bufferSize);
        m_items.resize(bufferSize, NULL);

        // Selection
        util::unserialize(is, m_currentX);

        // Item amount
        int itemAmount = 0;
        util::unserialize(is, itemAmount);

        // Items
        for(unsigned int i = 0; i < m_items.size(); i++)
        {
            Item * item = Item::unserializeItem(is);
            m_items[item->getInventoryPosition()] = item;
        }
    }

} // namespace grid

