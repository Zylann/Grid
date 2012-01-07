/*
Grid
RenderInventory.hpp

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

#ifndef RENDERINVENTORY_HPP_INCLUDED
#define RENDERINVENTORY_HPP_INCLUDED

#include "game/base/Renderer.hpp"
#include "game/Model.hpp"

namespace grid
{
    class Inventory;

    class RenderInventory : public Renderer
    {
    protected :

        Inventory * r_inventory;
        Model m_back;
        sf::Shape m_selection;

    public :

        RenderInventory(Inventory * inventory, int pass);

        virtual void setBlendMode(sf::Blend::Mode mode);
        virtual void setColor(const sf::Color & color);

        virtual void update();
        virtual void render(Graphics & gfx);

        static Vector2f getInventoryPosition(Graphics & gfx);
    };

} // namespace grid


#endif // RENDERINVENTORY_HPP_INCLUDED
