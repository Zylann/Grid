/*
Grid
entity::Shot.hpp

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

#ifndef ENTITYSHOT_HPP_INCLUDED
#define ENTITYSHOT_HPP_INCLUDED

#include "game/base/Entity.hpp"

namespace grid
{
namespace entity
{
    class Shot : public Entity
    {
    protected :

        int m_shooterID;

    public :

        Shot(int shooterID = -1, int ID = -1);

        virtual void doHit(World & world, Collision & c, float delta);

        virtual void updateMe(GameUpdate & up);
        virtual void onDestruction(GameUpdate & up);

        virtual int getType() const { return ENT_SHOT; }

    protected :

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace entity
} // namespace grid


#endif // ENTITYSHOT_HPP_INCLUDED
