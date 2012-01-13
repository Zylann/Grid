/*
Grid
Renderer.cpp

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

#include "game/base/Entity.hpp"
#include "game/base/Renderer.hpp"
#include "game/RenderManager.hpp"

namespace grid
{
    Renderer::Renderer(int pass)
    {
        m_pass = pass;
        r_entity = NULL;
        m_viewID = VIEW_GAME;

        if(pass == RP_INTERFACE)
            m_viewID = VIEW_INTERFACE;
    }

    void Renderer::registerRender(RenderManager & renderMgr)
    {
        renderMgr.addRender(this);
    }

    void Renderer::renderBoundingBox(Graphics & gfx)
    {
        util::AxisAlignedBB * boxPtr = r_entity->getBoundingBox();
        if(boxPtr != NULL)
        {
            gfx.draw(sf::Shape::Rectangle(boxPtr->minEdge, boxPtr->maxEdge,
                                          sf::Color(0,0,0,0), 0.025f,
                                          sf::Color(255,0,0)));
        }
    }

} // namespace grid

