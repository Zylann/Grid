/*
Grid
entity::Player.hpp

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

#ifndef ENTITYPLAYER_HPP_INCLUDED
#define ENTITYPLAYER_HPP_INCLUDED

#include "game/base/Entity.hpp"
#include "game/PlayerInfo.hpp"

namespace grid
{
namespace entity
{
    class Player : public Entity
    {
    protected :

        PlayerInfo * r_playerInfo;

    public :

        Player(int ID = -1);

        void setPlayerInfo(PlayerInfo * inf) { r_playerInfo = inf; }

        virtual void onFirstUpdate(GameUpdate & up);
        virtual void onDestruction(GameUpdate & up);
        virtual void updateMe(GameUpdate & up);

        virtual bool isPlayer() const { return true; }
        virtual int getType() const { return ENT_PLAYER; }

        virtual util::AxisAlignedBB * getBoundingBox();

//    protected :
//
//        virtual void serialize(std::ostream & os);
//        virtual void unserialize(std::istream & is) throw(GameException);
    };

} // namespace entity
} // namespace grid


#endif // ENTITYPLAYER_HPP_INCLUDED
