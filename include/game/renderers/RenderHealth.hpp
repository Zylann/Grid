/*
Grid
RenderHealth.hpp

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

#ifndef RENDERHEALTH_HPP_INCLUDED
#define RENDERHEALTH_HPP_INCLUDED

#include "game/base/Renderer.hpp"

namespace grid
{
    class Health;

    class RenderHealth : public Renderer
    {
    protected :

        const Health * r_health;
        sf::Shape m_back;
        sf::Shape m_bar1;
        sf::Shape m_bar2;
        bool m_fade;
        sf::Clock m_fadeTime;

    public :

        RenderHealth(const Health * health, int pass, bool fade = false);

        virtual void setBlendMode(sf::Blend::Mode mode);
        virtual void setColor(const sf::Color & color);

        virtual void update();
        virtual void render(Graphics & gfx);
    };

} // namespace grid


#endif // RENDERHEALTH_HPP_INCLUDED
