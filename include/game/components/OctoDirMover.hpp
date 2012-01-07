/*
Grid
OctoDirMover.hpp

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

#ifndef OCTODIRMOVER_HPP_INCLUDED
#define OCTODIRMOVER_HPP_INCLUDED

#include "game/components/Mover.hpp"

namespace grid
{
    /*
        This component enables entities to move through 8 directions.
        (left + up, left + down, right + up and right + down are also directions)
    */

    class OctoDirMover : public Mover
    {
    protected :

        bool m_left;
        bool m_right;
        bool m_up;
        bool m_down;

    public :

        OctoDirMover(float acceleration, int ID = -1) : Mover(acceleration, ID)
        {
            reset();
        }

        virtual void reset()
        {
            m_left = false;
            m_right = false;
            m_up = false;
            m_down = false;
        }

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        // This is a mover used on control, no need to serialize attributes.
        virtual bool isSerializable() const { return false; }
    };

} // namespace grid


#endif // OCTODIRMOVER_HPP_INCLUDED
