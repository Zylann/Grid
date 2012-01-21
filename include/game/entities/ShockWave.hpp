/*
Grid
entity::ShockWave.hpp

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

#ifndef ENTITYSHOCKWAVE_HPP_INCLUDED
#define ENTITYSHOCKWAVE_HPP_INCLUDED

#include "game/base/Entity.hpp"

namespace grid
{
namespace entity
{
    class ShockWave : public Entity
    {
    protected :

        float m_startRadius;
        float m_radius;
        float m_endRadius;
        float m_propagateSpeed;

    public :

        ShockWave(int ID = -1) : Entity(ID)
        {
            m_startRadius = 0;
            m_radius = 0;
            m_endRadius = 0;
            m_propagateSpeed = 1;
        }

        ShockWave(
            float startRadius, float endRadius, float propagateSpeed,
            sf::Color color = sf::Color(255,255,255),
            int ID = -1);

        float getFadingRatio() const;
        float getStartRadius() const { return m_startRadius; }
        float getEndRadius() const { return m_endRadius; }

        void updateMe(GameUpdate & up);

        virtual int getType() const { return ENT_SHOCKWAVE; }

        virtual bool isSerializable() const { return false; }
    };

} // namespace entity
} // namespace grid


#endif // ENTITYSHOCKWAVE_HPP_INCLUDED
