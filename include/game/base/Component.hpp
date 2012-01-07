/*
Grid
Component.hpp

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

#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include "common.hpp"

#include "game/base/Message.hpp"
#include "game/base/GameObject.hpp"
#include "game/base/Renderer.hpp"
#include "game/RenderManager.hpp"

namespace grid
{
    class Entity;
    class GameUpdate;

    /*
        A component is a game object that compose entities.
        They define behaviors, functionnalities etc.
    */

//    // Used for serialization
//    enum ComponentType
//    {
//        COMP_HEALTH = 0,
//        COMP_INVENTORY,
//        COMP_LOOK_BIND,
//        COMP_MOUSE_CONTROLLER,
//        COMP_OCTODIR_MOVER,
//        COMP_PHYSICS,
//        COMP_PLAYER_CONTROLLER,
//        COMP_RANDOM_SPAWNER
//    };

    class Component : public GameObject
    {
    protected :

        Entity * r_owner;
        Renderer * m_renderer;

    public :

        Component(int ID = -1) : GameObject(ID)
        {
            r_owner = NULL;
            m_renderer = NULL;
        }

        virtual ~Component()
        {
            if(m_renderer != NULL)
                delete m_renderer;
        }

        virtual void setOwner(Entity * e)
        {
            r_owner = e;
        }

        Entity * getOwner()
        {
            return r_owner;
        }

        virtual bool isPhysics()
        {
            return false;
        }

        virtual void update(GameUpdate & up) = 0;
        virtual bool processMessage(Message & msg) = 0;

        void setRenderer(Renderer * r)
        {
            m_renderer = r;
        }

        virtual void registerRender(RenderManager & manager)
        {
            if(m_renderer != NULL)
                manager.addRender(m_renderer);
        }
    };

} // namespace grid


#endif // COMPONENT_HPP_INCLUDED
