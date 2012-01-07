/*
Grid
Entity.hpp

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

#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <sstream>
#include <map>
#include <string>
#include <list>

#include "common.hpp"

#include "utility/Exception.hpp"
#include "utility/AxisAlignedBB.hpp"

#include "game/base/GameObject.hpp"
#include "game/base/Component.hpp"
#include "game/base/Renderer.hpp"
#include "game/components/Physics.hpp"
#include "game/Collision.hpp"

namespace grid
{
    class World;
    class Game;
    class Entity;
    class GameUpdate;

    // Used for serialization
    enum EntityType
    {
        ENT_MAP = 0, // Keep 0
        ENT_PLAYER,
        ENT_SENTINEL,
        ENT_SHOT,
        ENT_SHOCKWAVE,
        ENT_GRENADE
    };

    /*
        Entity exceptions
    */

    class EntityException : public util::Exception
    {
    public:
        EntityException(
            const std::string & msg,
            Entity * e = NULL,
            int level = util::Exception::EX_UNKNOWN) throw()
        : util::Exception(msg, level), r_entity(e)
        {}
    private:
        Entity * r_entity;
    };

    /*
        Entities are the main game objects : they have spatial attributes and can be rendered.
        The pattern used here is close to Entity-Component model,
        as described here :
            http://slick.cokeandcode.com/wiki/doku.php?id=entity_tutorial
    */

    class Entity : public GameObject
    {
    private :

        /* Attributes */

        bool m_isFirstUpdate;

        // All components owned by the entity
        std::list<Component*> m_components;

        // Next components of the entity. We need this second container because
        // new components may be added dynamically, particularly during the update of
        // a component stored in m_components. This results on a std::list modification
        // during the iteration (wich would lead to a segmentation fault),
        // so they are stored here until the next update.
        std::list<Component*> m_nextComponents;
        Physics * r_physics;

        // How to draw the entity
        Renderer * m_renderer;

    protected :

        // Shape used for collisions (currently a bounding box)
        util::AxisAlignedBB * m_boundingBox;

        Vector2f m_lastPos;   // position at last update

//        // World access
//        World * r_world;

    public :

        Vector2f pos;       // position in units
        Vector2f speed;     // movement in units/s
        float rotation;         // rotation in radians
        float scale;
        unsigned char team;
        std::string name;

        /* Constructors and destructor */

        Entity(int ID = -1) : GameObject(ID)
        {
            m_isFirstUpdate = true;
            rotation = 0;
            scale = 1;
            m_renderer = NULL;
            r_physics = NULL;
            m_boundingBox = NULL;
            name = "_entity_";
            team = 0;
        }

        virtual ~Entity()
        {
            // Deleting components
            std::list<Component*>::iterator it;
            for(it = m_components.begin(); it != m_components.end(); it++)
            {
                Component * c = *it;
                if(c != NULL)
                    delete c;
            }
            // Deleting next components
            for(it = m_nextComponents.begin(); it != m_nextComponents.end(); it++)
            {
                Component * c = *it;
                if(c != NULL)
                    delete c;
            }
            // deleting renderer
            if(m_renderer != NULL)
                delete m_renderer;
            // deleting bounding box
            if(m_boundingBox != NULL)
                delete m_boundingBox;
        }

        /* Methods */

        // Tells if the entity can be drawn with a renderer
        virtual bool isDrawable() const;

        virtual bool isPlayer() const { return false; }

        Entity & addComponent(Component * c);
        Entity & setRenderer(Renderer * r);
        Renderer * getRenderer();

//        void setWorld(World * w) { r_world = w; }
//        World * getWorld() const { return r_world; }

        void setBoundingBox(util::AxisAlignedBB * box);
        virtual util::AxisAlignedBB * getBoundingBox();

        virtual void getCollisions(
            std::list<Collision>& collisions,
            const util::AxisAlignedBB& box);

        virtual Entity & setPosition(const Vector2f & p_pos);
        virtual Entity & setSpeed(const Vector2f & p_pos);
        virtual Entity & setRotation(float p_rotation);

        inline const Vector2f & getLastPosition() const { return m_lastPos; };

        // Rotates the entity to face the specified point
        void lookAt(const Vector2f & target);

        // Applies an acceleration to the current speed.
        virtual void accelerate(const Vector2f & acc, float delta);

        // Moves the entity from its current speed.
        virtual void move(float delta, World & world);

        // Moves the entity. If it has a mover, the resulting motion can be different.
        // Return : resulting motion.
        virtual Vector2f move(const Vector2f & motion, World & world);

        virtual void update(GameUpdate & up);
        virtual void onFirstUpdate(GameUpdate & up) {}
        virtual void onDestruction(GameUpdate & up) {}

        virtual bool processMessage(Message & msg);

        // Renders the entity (not currently used)
        void render(Graphics & gfx);

        void registerRender(RenderManager & manager);

        // Used for serialization
        virtual int getType() const { return -1; }

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);

    protected :

        virtual void updateMe(GameUpdate & up) {}

        void updateComponents(GameUpdate & up);
    };

} // namespace grid


#endif // ENTITY_HPP_INCLUDED



