/*
Grid
BallShooter.hpp

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

#ifndef BALLSHOOTER_HPP_INCLUDED
#define BALLSHOOTER_HPP_INCLUDED

#include "game/items/FireWeapon.hpp"

namespace grid
{
    class BallShooter : public FireWeapon
    {
    public :

        BallShooter(int ID = -1);

        virtual Entity * createShot(int ownerID);

        virtual void playShootSound() const;

        virtual int getType() const { return ITM_BALL_SHOOTER; }

        virtual float getShootTime() const;
        virtual float getRepulsion() const;
        virtual float getPropulsionSpeed() const;
        virtual float getDispersion() const;
    };

} // namespace grid


#endif // BALLSHOOTER_HPP_INCLUDED
