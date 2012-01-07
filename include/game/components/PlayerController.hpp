/*
Grid
PlayerController.hpp

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

#ifndef PLAYERCONTROLLER_HPP_INCLUDED
#define PLAYERCONTROLLER_HPP_INCLUDED

#include "game/base/Component.hpp"
#include "game/components/Mover.hpp"

namespace grid
{
    class EntityPlayer;

    class PlayerController : public Component
    {
    protected :

        bool m_lastMouseLeft;
        bool m_lastMouseRight;
        Mover * r_mover;
        EntityPlayer * r_player;

    public :

        PlayerController(EntityPlayer * p, int ID = -1) : Component(ID)
        {
            m_lastMouseLeft = false;
            m_lastMouseRight = false;
            r_mover = NULL;
            r_player = p;
        }

        void setMover(Mover * m) { r_mover = m; }

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        // Controllers haven't to be serialized.
        virtual bool isSerializable() const { return false; }
    };

} // namespace grid


#endif // PLAYERCONTROLLER_HPP_INCLUDED
