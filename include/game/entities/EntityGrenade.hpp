/*
Grid
EntityGrenade.hpp

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

#ifndef ENTITYGRENADE_HPP_INCLUDED
#define ENTITYGRENADE_HPP_INCLUDED

#include "game/base/Entity.hpp"

namespace grid
{
    class EntityGrenade : public Entity
    {
    protected :

        int m_shooterID;
        float m_remainingTime;

    public :

        EntityGrenade(int m_shooterID = -1, int ID = -1);

        virtual void onDestruction(GameUpdate & up);
        virtual void updateMe(GameUpdate & up);

        virtual util::AxisAlignedBB * getBoundingBox();

        virtual bool isPlayer() const { return false; }
        virtual int getType() const { return ENT_GRENADE; }

    protected :

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is) throw(GameException);
    };

} // namespace grid


#endif // ENTITYGRENADE_HPP_INCLUDED
