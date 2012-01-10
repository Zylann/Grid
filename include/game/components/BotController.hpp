/*
Grid
BotController.hpp

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

#ifndef BOTCONTROLLER_HPP_INCLUDED
#define BOTCONTROLLER_HPP_INCLUDED

#include "game/base/Component.hpp"
#include "game/components/Mover.hpp"

namespace grid
{
    class BotController : public Component
    {
    protected :

        bool m_weaponTrigger;

    public :

        BotController(int ID = -1) : Component(ID)
        {
            m_weaponTrigger = false;
        }

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        // Controllers haven't to be serialized.
        virtual bool isSerializable() const { return false; }
    };

} // namespace grid


#endif // BOTCONTROLLER_HPP_INCLUDED
