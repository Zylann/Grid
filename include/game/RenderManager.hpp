/*
Grid
RenderManager.hpp

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

#ifndef RENDERMANAGER_HPP_INCLUDED
#define RENDERMANAGER_HPP_INCLUDED

#include <list>

#include "game/base/Renderer.hpp"

namespace grid
{
    class RenderManager
    {
    private :

        // m_renderers[pass][entityID]
        // Note : no memory management is done here, we just use renderers as references
        std::list<Renderer*> r_renders[RP_COUNT];

    public :

        void addRender(Renderer * r);
        void render(Graphics gfx);
        void clear();
    };

} // namespace grid


#endif // RENDERMANAGER_HPP_INCLUDED
