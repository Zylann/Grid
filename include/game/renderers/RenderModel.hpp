/*
Grid
RenderModel.hpp

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

#ifndef RENDERMODEL_HPP_INCLUDED
#define RENDERMODEL_HPP_INCLUDED

#include "utility/geometry.hpp"

#include "game/Model.hpp"
#include "game/base/Renderer.hpp"

namespace grid
{
    class RenderModel : public Renderer
    {
    protected :

        Model * m_model;

    public :

        RenderModel(int pass, Model * newModel) : Renderer(pass)
        {
            m_model = newModel;
        }

        ~RenderModel()
        {
            delete m_model;
        }

        virtual void setBlendMode(sf::Blend::Mode mode);
        virtual void setColor(const sf::Color & color);

        virtual void update();
        virtual void render(Graphics & gfx);
    };

} // namespace grid


#endif // RENDERMODEL_HPP_INCLUDED
