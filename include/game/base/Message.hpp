/*
Grid
Message.hpp

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

#ifndef MESSAGE_HPP_INCLUDED
#define MESSAGE_HPP_INCLUDED

namespace grid
{
    class Entity;

    enum MessageType
    {
        M_ENT_INVALIDATE = 0,
        M_ENT_ENABLE,

        M_INV_LEFT,
        M_INV_RIGHT,
        M_INV_DROP,

        M_ITM_TRIGGER,
        M_ITM_ACTION,

        M_MOV_LEFT,
        M_MOV_RIGHT,
        M_MOV_UP,
        M_MOV_DOWN,

        M_HEA_HEAL,
        M_HEA_FULL_HEAL,
        M_HEA_HURT,
        M_HEA_KILL,
        M_HEA_ONDEATH,
        M_HEA_ONREVIVE
    };

    class Message
    {
    public :

        int type;
        int health;
        Entity * sender;
        bool flag;

        Message(int p_type, Entity * p_sender, bool p_flag = false)
        {
            type = p_type;
            sender = p_sender;
            flag = p_flag;
            health = 0;
        }
    };

} // namespace grid


#endif // MESSAGE_HPP_INCLUDED
