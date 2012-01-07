/*
Grid
EntityShockWave.cpp

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

#include "game/entities/EntityShockWave.hpp"
#include "game/renderers/RenderModel.hpp"
#include "game/GameUpdate.hpp"

namespace grid
{
    EntityShockWave::EntityShockWave(
        float startRadius, float endRadius, float propagateSpeed,
        sf::Color color, int ID)
    : Entity(ID)
    {
        name = "shockwave";

        m_startRadius = startRadius;
        m_radius = startRadius;
        m_endRadius = endRadius;
        m_propagateSpeed = propagateSpeed;

        Model * m = new Model();
        m->addShape(new sf::Shape(
            sf::Shape::Circle(pos.x, pos.y, 0.5, sf::Color(0,0,0,0), 0.2, color)));
        RenderModel * r = new RenderModel(RP_EFFECTS, m);

        setRenderer(r);
    }

    void EntityShockWave::updateMe(GameUpdate & up)
    {
        m_radius += m_propagateSpeed * up.delta;

        Renderer * r = getRenderer();
        if(r != NULL)
        {
            unsigned char a = 0;

            if(m_radius <= m_endRadius)
                a = 255.f * (1 - (m_radius - m_startRadius) / (m_endRadius - m_startRadius));

            r->setColor(sf::Color(255,255,255, a));
        }

        scale = m_radius;

        if(m_radius >= m_endRadius)
            invalidate();
    }

} // namespace grid

