/*
Grid
HealthBonus.hpp

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

#ifndef HEALTHBONUS_HPP_INCLUDED
#define HEALTHBONUS_HPP_INCLUDED

#include "game/base/Item.hpp"

namespace grid
{
    class HealthBonus : public Item
    {
    protected :

        int m_health;

    public :

        HealthBonus(int ID = -1);

        virtual void onPick(Entity * owner, World * world = NULL);
        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        virtual Renderer * createDroppedRenderer();

        virtual bool isInstant() const { return true; }

        virtual int getType() const { return ITM_HEALTH_BONUS; }

    protected :

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // HEALTHBONUS_HPP_INCLUDED
