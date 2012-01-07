/*
Grid
MouseController.hpp

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

#ifndef MOUSECONTROLLER_HPP_INCLUDED
#define MOUSECONTROLLER_HPP_INCLUDED

#include "game/base/Component.hpp"

namespace grid
{
    /*
        An entity with a MouseController will follow the mouse cursor.
    */

    class MouseController : public Component
    {
    public :

        MouseController(int ID = -1) : Component(ID) {}

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        // Note : there is none attribute to serialize.
        virtual bool isSerializable() const { return false; }
    };

} // namespace grid


#endif // MOUSECONTROLLER_HPP_INCLUDED
