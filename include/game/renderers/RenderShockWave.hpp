/*
Grid
RenderShockWave.hpp

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

#ifndef RENDERSHOCKWAVE_HPP_INCLUDED
#define RENDERSHOCKWAVE_HPP_INCLUDED

#include "game/base/Renderer.hpp"

namespace grid
{
    namespace entity { class ShockWave; }

    class RenderShockWave : public Renderer
    {
    protected :

        entity::ShockWave * r_shockWave;
        sf::Shape m_wave;
        sf::Sprite m_flash;
        bool m_flashEnabled;

    public :

        RenderShockWave(int pass);

        virtual ~RenderShockWave()
        {}

        virtual void update() {}

        virtual void setEntity(Entity * e);
        virtual void setColor(const sf::Color & color);
        virtual void setBlendMode(sf::Blend::Mode mode);
        virtual void setFlashEnabled(bool e) { m_flashEnabled = e; }

        virtual void render(Graphics & gfx);
    };

} // namespace grid


#endif // RENDERSHOCKWAVE_HPP_INCLUDED
