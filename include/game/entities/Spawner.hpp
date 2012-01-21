/*
Grid
EntitySpawner.hpp

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

#ifndef ENTITYSPAWNER_HPP_INCLUDED
#define ENTITYSPAWNER_HPP_INCLUDED

#include "game/base/Entity.hpp"
#include "game/components/RandomSpawner.hpp"

namespace grid
{
    class EntitySpawner : public Entity
    {
    public :

        EntitySpawner(RandomSpawner * r = NULL, int ID = -1)
        {
            if(r != NULL)
                addComponent(r);
            else
                addComponent(new RandomSpawner());
        }

        virtual int getType() const { return ENT_SPAWNER; }
    };

} // namespace grid


#endif // ENTITYSPAWNER_HPP_INCLUDED
