/*
Grid
RenderManager.cpp

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

#include "game/RenderManager.hpp"

namespace grid
{
    void RenderManager::addRender(Renderer * r)
    {
        if(r == NULL)
            return;

        r_renders[r->getPass()].push_back(r);
    }

    void RenderManager::render(Graphics gfx)
    {
        //int renderCount = 0;

        std::list<Renderer*>::iterator it;
        for(unsigned int i = 0; i < RP_COUNT; i++)
        {
            for(it = r_renders[i].begin(); it != r_renders[i].end(); it++)
            {
                (*it)->render(gfx);
                //renderCount++;
            }
        }
        //std::cout << renderCount << std::endl;
    }

    void RenderManager::clear()
    {
        for(unsigned int i = 0; i < RP_COUNT; i++)
            r_renders[i].clear();
    }

} // namespace grid

