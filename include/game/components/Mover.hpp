/*
Grid
Mover.hpp

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

#ifndef MOVER_HPP_INCLUDED
#define MOVER_HPP_INCLUDED

#include "game/base/Component.hpp"

namespace grid
{
    class Mover : public Component
    {
    protected :

        float m_acceleration;

    public :

        Mover(float acceleration, int ID = -1) : Component(ID)
        {
            m_acceleration = acceleration > 0 ? acceleration : 0;
        }

        virtual void update(GameUpdate & up) = 0;
        virtual bool processMessage(Message & msg) = 0;
        virtual void reset() {};

        // For the moment, the acceleration is not serialized.
        virtual bool isSerializable() const { return false; }
    };

} // namespace grid


#endif // MOVER_HPP_INCLUDED
