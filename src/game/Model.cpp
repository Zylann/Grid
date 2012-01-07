/*
Grid
Model.cpp

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

#include "game/Model.hpp"
#include "game/Graphics.hpp"

namespace grid
{
    int Model::addShape(sf::Shape * newShape)
    {
        m_shapes.push_back(newShape);
        return m_shapes.size() - 1;
    }

    void Model::render(Graphics & gfx)
    {
        for(unsigned int i = 0; i < m_shapes.size(); i++)
        {
            gfx.draw(*(m_shapes[i]));
        }
    }

    void Model::setPosition(Vector2f & pos)
    {
        for(unsigned int i = 0; i < m_shapes.size(); i++)
            m_shapes[i]->SetPosition(pos);
    }

    void Model::setRotation(float t)
    {
        for(unsigned int i = 0; i < m_shapes.size(); i++)
            m_shapes[i]->SetRotation(t);
    }

    void Model::setScale(float s)
    {
        for(unsigned int i = 0; i < m_shapes.size(); i++)
            m_shapes[i]->SetScale(s, s);
    }

    void Model::setColor(const sf::Color & color)
    {
        for(unsigned int i = 0; i < m_shapes.size(); i++)
            m_shapes[i]->SetColor(color);
    }

} // namespace grid

