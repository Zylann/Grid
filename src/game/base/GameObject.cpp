/*
Grid
GameObject.cpp

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

#include "game/base/GameObject.hpp"

namespace grid
{
    /*
        Static methods
    */

    int g_counter = 0;

    int GameObject::makeUniqueID()
    {
        g_counter++;
        return g_counter;
    }

    void GameObject::updateCounter(int n)
    {
        if(n > g_counter)
            g_counter = n;
    }

    int g_instanceCount = 0; // debug purposes

    int GameObject::getInstanceCount()
    {
        return g_instanceCount;
    }

    /*
        Methods
    */

    GameObject::GameObject(int ID)
    {
        g_instanceCount++;

        if(ID < 0)
            m_ID = makeUniqueID();
        else
            m_ID = ID;

        m_valid = true;
        m_enable = true;
    }

    GameObject::~GameObject()
    {
        g_instanceCount--;
        //std::cout << "- " << g_instanceCount << std::endl;
    }

    /*
        Serialization
    */

    void GameObject::serialize(std::ostream & os)
    {
        uint8 e = m_enable;
        util::serialize(os, m_ID);
        util::serialize(os, e);
        util::serialize(os, m_lifeTime);
    }

    void GameObject::unserialize(std::istream & is)
    {
        uint8 e = 0;
        util::unserialize(is, m_ID);
        util::unserialize(is, e);
        util::unserialize(is, m_lifeTime);
        m_enable = e > 0;

        // Note : in some cases, unserialization may lead to
        // conflicting identifiers with some already created ones.
        // FIXME unserialization ID conflict : how to fix that?
        // Actually, unserialization only occurs on world loading, so
        // there is no harm at the moment.

        updateCounter(m_ID);
    }

} // namespace grid

