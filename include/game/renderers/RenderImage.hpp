/*
Grid
RenderImage.hpp

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

#ifndef RENDERIMAGE_HPP_INCLUDED
#define RENDERIMAGE_HPP_INCLUDED

#include "common.hpp"
#include "game/Graphics.hpp"
#include "game/base/Renderer.hpp"

namespace grid
{
    class RenderImage : public Renderer
    {
    protected :

        sf::Sprite m_sprite;
        bool m_bindRotation;
        bool m_bindScale;

    public :

        RenderImage(int pass, const sf::Image & img);

        inline void setBindRotation(bool b) { m_bindRotation = b; }
        inline void setBindScale(bool b) { m_bindScale = b; }

        virtual void setBlendMode(sf::Blend::Mode mode);
        virtual void setColor(const sf::Color & color);
        virtual void setScale(float s);

        virtual void update();
        virtual void render(Graphics & gfx);
    };

} // namespace grid


#endif // RENDERIMAGE_HPP_INCLUDED
