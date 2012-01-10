/*
Grid
GameObject.hpp

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

#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "common.hpp"
#include "utility/serialization.hpp"

namespace grid
{
    class GameObject
    {
    protected :

        int m_ID; // unique identifier
        bool m_valid; // is the object must be deleted ?
        bool m_enable; // is the object must be ignored ?
        float m_lifeTime;

    public :

        static int makeUniqueID();
        static int getInstanceCount();
        static void updateCounter(int n);

        GameObject(int ID = -1);
        virtual ~GameObject();

        // Identification
        inline int getID() const { return m_ID; }

        // State
        inline void enable(bool e) { m_enable = e; }
        inline bool isEnabled() const { return m_enable; }
        inline void invalidate() { m_valid = false; }
        inline bool isValid() const { return m_valid; }
        inline float getLifeTime() const { return m_lifeTime; }

        // Serialization
        virtual bool isSerializable() const { return true; }
        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // GAMEOBJECT_HPP_INCLUDED
