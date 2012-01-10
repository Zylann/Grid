/*
Grid
Physics.hpp

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

#ifndef PHYSICS_HPP_INCLUDED
#define PHYSICS_HPP_INCLUDED

#include "game/base/Component.hpp"
#include "game/Terrain.hpp"

namespace grid
{
    class World;

    struct FrictionModel
    {
        float c1;
        float c2;

        FrictionModel(float p_c1 = 1, float p_c2 = 16)
        {
            c1 = p_c1;
            c2 = p_c2;
        }

        float applyFriction(float x, float delta, const terrain::Ground & gp);
    };

    class Physics : public Component
    {
    protected :

        FrictionModel m_frictionModel;

    public :

        Physics(FrictionModel fmodel = FrictionModel(), int ID = -1) : Component(ID)
        {
            m_frictionModel = fmodel;
        }

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        virtual bool isPhysics()
        {
            return true;
        }

        // Moves the entity applying collisions.
        // Return value : new motion vector (speed * delta)
        virtual Vector2f moveEntity(const Vector2f & motion, World & world);

        // Adds an acceleration to the entity including ground slipperiness
        virtual void accelerate(Vector2f acc, float delta, World & world);

        // None attribute to serialize at the moment.
        virtual bool isSerializable() const { return false; }
    };

} // namespace grid


#endif // PHYSICS_HPP_INCLUDED
