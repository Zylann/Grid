/*
Grid
Model.hpp

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

#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include <vector>

#include "common.hpp"

namespace grid
{
    class Graphics;

    /*
        A model is a set of shapes.
    */

    class Model
    {
    protected :

        std::vector<sf::Shape*> m_shapes;

    public :

        Model()
        {}

        ~Model()
        {
            clear();
        }

        void clear()
        {
            for(unsigned int i = 0; i < m_shapes.size(); i++)
            {
                if(m_shapes[i] != NULL)
                    delete m_shapes[i];
            }
            m_shapes.clear();
        }

        int addShape(sf::Shape * newShape);

        void setPosition(Vector2f & pos);
        void setRotation(float t);
        void setScale(float s);
        void setColor(const sf::Color & color);

        void render(Graphics & gfx);
    };

} // namespace grid


#endif // MODEL_HPP_INCLUDED
