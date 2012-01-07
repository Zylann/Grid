/*
Grid
Entity.cpp

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

#include <iostream>
#include <list>

#include "game/base/Entity.hpp"
#include "game/World.hpp"
#include "game/Game.hpp"
#include "game/GameUpdate.hpp"

#include "utility/geometry.hpp"

using namespace util;

namespace grid
{
    /* Member methods */

    void Entity::update(GameUpdate & up)
    {
        if(!m_enable)
            return;

        if(m_isFirstUpdate)
        {
            onFirstUpdate(up);
            m_isFirstUpdate = false;
        }

        m_lastPos = pos;
        move(up.delta, *(up.world));

        updateComponents(up);
        updateMe(up);
    }

    void Entity::render(Graphics & gfx)
    {
        if(isDrawable() && m_renderer != NULL)
        {
            m_renderer->render(gfx);
        }
    }

    // Predicate for list::remove_if
    bool isComponentInvalid(Component * c)
    {
        return !c->isValid();
    }

    void Entity::updateComponents(GameUpdate & up)
    {
        std::list<Component*>::iterator it;
        std::list<Component*> invalid;

        // Activate next components
        for(it = m_nextComponents.begin(); it != m_nextComponents.end(); it++)
        {
            m_components.push_back(*it);
        }
        m_nextComponents.clear();

        m_components.remove_if(isComponentInvalid);

        // Updating components
        for(it = m_components.begin(); it != m_components.end(); it++)
        {
            Component * c = *it;
            c->update(up);

            if(!c->isValid())
                invalid.push_back(c);
        }

        // Deleting invalid components
        m_components.remove_if(isComponentInvalid);
        for(it = invalid.begin(); it != invalid.end(); it++)
        {
            Component * c = *it;

            if(c->isPhysics())
                r_physics = NULL;

            delete c;
        }
    }

    bool Entity::processMessage(Message & msg)
    {
        // Entity messages
        if(msg.type == M_ENT_INVALIDATE)
        {
            invalidate();
            return true;
        }
        else if(msg.type == M_ENT_ENABLE)
        {
            enable(msg.flag);
            return true;
        }
        else
        {
            // Component messages
            bool res = false;
            std::list<Component*>::iterator it;

            for(it = m_components.begin(); it != m_components.end(); it++)
            {
                res = res || (*it)->processMessage(msg);
            }
            return res;
        }
    }

    bool Entity::isDrawable() const
    {
        return m_renderer != NULL;
    }

    Entity & Entity::addComponent(Component * c)
    {
        c->setOwner(this);

        m_nextComponents.push_back(c);

        if(c->isPhysics())
        {
            r_physics = (Physics*)c;
        }

        return *this;
    }

    Entity & Entity::setRenderer(Renderer * r)
    {
        if(m_renderer != NULL)
            delete m_renderer;

        m_renderer = r;
        m_renderer->setEntity(this);

        return *this;
    }

    Renderer * Entity::getRenderer()
    {
        return m_renderer;
    }

    Entity & Entity::setPosition(const Vector2f & p_pos)
    {
        pos = p_pos;
        return *this;
    }

    Entity & Entity::setSpeed(const Vector2f & p_speed)
    {
        speed = p_speed;
        return *this;
    }

    Entity & Entity::setRotation(float p_rotation)
    {
        rotation = p_rotation;
        return *this;
    }

    void Entity::lookAt(const Vector2f & target)
    {
        rotation = util::getAngle(pos, target);
    }

    void Entity::accelerate(const Vector2f & acc, float delta)
    {
        speed += acc * delta;
    }

    void Entity::move(float delta, World & world)
    {
        Vector2f motion = move(speed * delta, world);

        // Using a mover can modify the resulting motion, so we update the speed.
        // (motion = speed * delta)
        if(r_physics != NULL)
            speed == motion / delta;
    }

    Vector2f Entity::move(const Vector2f & motion, World & world)
    {
        if(r_physics != NULL)
            return r_physics->moveEntity(motion, world);
        else
        {
            pos += motion;
            return motion;
        }
    }

    void Entity::setBoundingBox(util::AxisAlignedBB * box)
    {
        if(m_boundingBox != NULL)
            delete m_boundingBox;
        m_boundingBox = box;
    }

    util::AxisAlignedBB * Entity::getBoundingBox()
    {
        return m_boundingBox;
    }

    void Entity::getCollisions(
        std::list<Collision> & collisions,
        const util::AxisAlignedBB& box)
    {
        if(m_boundingBox != NULL)
        {
            if(m_boundingBox->collides(box))
                collisions.push_back(Collision(this, *m_boundingBox));
        }
    }

    void Entity::registerRender(RenderManager & manager)
    {
        if(m_renderer != NULL)
            manager.addRender(m_renderer);

        std::list<Component*>::iterator it;
        for(it = m_components.begin(); it != m_components.end(); it++)
        {
            (*it)->registerRender(manager);
        }
    }

    /*
        Serialization

        I) How to unserialize :

        We must know that we have to read an entity before all.
        Then, the first information we have to read is an entity type (EntityType enum),
        which determines what kind of entity we must create first.
        /!\ This first step is not done by entities.

        Entities are composed of basic attributes, and components.
        When an entity is created, its components must be created at the same time.
        Then, after the first initialization (done in constructors),
        we can unserialize the entity for its components to take their new values :

            1) Get entity type
            2) Create the corresponding entity
            3) unserialize game object attributes
            4) unserialize entity base
            5) unserialize components
            6) unserialize entity subclasses info

        Components are supposed to be in the same order before and after serialization.

        II) How to serialize :

        Serialization is slightly the same than unserializing, we just have to do it
        in the same order.
    */

    void Entity::serialize(std::ostream & os)
    {
        GameObject::serialize(os);

        util::serialize(os, name);
        util::serialize(os, pos);
        util::serialize(os, speed);
        util::serialize(os, rotation);
        util::serialize(os, scale);
        util::serialize(os, team);

        std::list<Component*>::iterator it;
        for(it = m_components.begin(); it != m_components.end(); it++)
        {
            if((*it)->isSerializable())
                (*it)->serialize(os);
        }
    }

    void Entity::unserialize(std::istream & is)
    {
        m_isFirstUpdate = true;

        GameObject::unserialize(is);

        util::unserialize(is, name);
        util::unserialize(is, pos);
        util::unserialize(is, speed);
        util::unserialize(is, rotation);
        util::unserialize(is, scale);
        util::unserialize(is, team);

        std::list<Component*>::iterator it;
        for(it = m_components.begin(); it != m_components.end(); it++)
        {
            if((*it)->isSerializable())
                (*it)->unserialize(is);
        }
    }

} // namespace grid




