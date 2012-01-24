/*
Grid
Renderer.hpp

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

#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include "game/Graphics.hpp"

namespace grid
{
    enum RenderPass
    {
        RP_BACKGROUND = 0, // Keep 0
        RP_GROUND,
        RP_EVENTS,
        RP_EFFECTS,
        RP_FOREGROUND,
        RP_SCENE_INTERFACE,
        RP_INTERFACE,

        RP_COUNT // Keep last
    };

    class Entity;
    class GameUpdate;
    class RenderManager;

    class Renderer
    {
    protected :

        Entity * r_entity;
        int m_pass;
        int m_viewID;
        bool m_valid;

    public :

        Renderer(int pass);

        virtual ~Renderer()
        {}

        virtual void setEntity(Entity * e) { r_entity = e; }

        inline int getPass() const { return m_pass; }
        inline int getViewID() const { return m_viewID; }

        virtual void update() = 0;
        virtual void render(Graphics & gfx) = 0;
        virtual void registerRender(RenderManager & renderMgr);

        virtual void setColor(const sf::Color & color) {}
        virtual void setBlendMode(sf::Blend::Mode mode) {}

        // Displays the bounding box (debug purposes)
        void renderBoundingBox(Graphics & gfx, sf::Color color = sf::Color(255,0,0));

        /* Static methods */

        static void setDisplayBoundingBoxes(bool d);
        static bool isDisplayBoundingBoxes();
    };

} // namespace grid


#endif // RENDERER_HPP_INCLUDED
