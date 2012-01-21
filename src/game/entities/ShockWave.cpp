/*
Grid
entity::ShockWave.cpp

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

#include "game/entities/ShockWave.hpp"
#include "game/renderers/RenderShockWave.hpp"
#include "game/GameUpdate.hpp"

namespace grid
{
namespace entity
{
    ShockWave::ShockWave(
        float startRadius, float endRadius, float propagateSpeed,
        sf::Color color, int ID)
    : Entity(ID)
    {
        name = "shockwave";

        m_startRadius = startRadius;
        m_radius = startRadius;
        m_endRadius = endRadius;
        m_propagateSpeed = propagateSpeed;

//        Model * m = new Model();
//        m->addShape(new sf::Shape(
//            sf::Shape::Circle(pos.x, pos.y, 0.5, sf::Color(0,0,0,0), 0.2, color)));
//        RenderModel * r = new RenderModel(RP_EFFECTS, m);
        RenderShockWave * r = new RenderShockWave(RP_EFFECTS);
        r->setColor(color);
        setRenderer(r);
    }

    float ShockWave::getFadingRatio() const
    {
        return (1 - (m_radius - m_startRadius) / (m_endRadius - m_startRadius));
    }

    void ShockWave::updateMe(GameUpdate & up)
    {
        m_radius += m_propagateSpeed * up.delta;
        scale = m_radius;

        if(m_radius >= m_endRadius)
            invalidate();
    }

} // namespace entity
} // namespace grid

