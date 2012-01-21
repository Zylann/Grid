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
#include "game/GameException.hpp"

namespace grid
{
    class World;
    class Game;
    class Entity;
    class GameUpdate;

    enum EntityType
    {
        ENT_BASIC = 0, // Keep 0

        ENT_MAP,
        ENT_PLAYER,
        ENT_SENTINEL,
        ENT_SHOT,
        ENT_SHOCKWAVE,
        ENT_GRENADE,
        ENT_DROPPED_ITEM,
        ENT_SPAWNER,

        ENT_TYPE_COUNT // keep last
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

        bool m_isFirstUpdate; // have the entity ever been updated ?

        std::list<Component*> m_components; // All components owned by the entity

        // Next components of the entity. We need this second container because
        // new components may be added dynamically, particularly during the update of
        // a component stored in m_components. This results on a std::list modification
        // during the iteration (wich would lead to a segmentation fault),
        // so they are stored here until the next update.
        std::list<Component*> m_nextComponents;

        Physics * r_physics;    // Physics component shortcut-reference

    protected :

        Renderer * m_renderer;  // How to draw the entity

        // Shape used for collisions (currently a bounding box)
        util::AxisAlignedBB * m_boundingBox;

        Vector2f m_lastPos; // position at last update
        float m_lifeTime;   // time in seconds

        World * r_world;    // reference world

    public :

        Vector2f pos;       // position in units
        Vector2f speed;     // movement in units/s
        float rotation;     // rotation in radians
        float scale;
        unsigned char team; // team of the entity. -1 means none.
        std::string name;   // name of the entity.

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
            m_lifeTime = 0;
            r_world = NULL;
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

        // Tells if the entity can be drawn
        virtual bool isDrawable() const;

        // Returns true if the entity is a player
        virtual bool isPlayer() const { return false; }

        // Returns true if the entity is a dropped item
        virtual bool isDroppedItem() const { return false; }

        // Adds a component to the entity
        Entity & addComponent(Component * c);

        // Sets the entity's renderer
        Entity & setRenderer(Renderer * r);

        // Get the entity's renderer. Returns NULL if there are none.
        Renderer * getRenderer();

        // Sets the reference world of the entity
        inline void setWorld(World * w) { r_world = w; }

        // Returns the reference world of the entity
        inline World * getWorld() const { return r_world; }

        void setBoundingBox(util::AxisAlignedBB * box);

        // Returns the offset bounding box of the entity
        virtual util::AxisAlignedBB * getBoundingBox();

        // Returns collisions of the specified shape on the entity
        virtual void getCollisions(
            std::list<Collision>& collisions,
            const util::AxisAlignedBB& box);

        // Sets the position of the entity, and returns a reference for chaining
        virtual Entity & setPosition(const Vector2f & p_pos);

        // Sets the speed of the entity, and returns a reference for chaining
        virtual Entity & setSpeed(const Vector2f & p_pos);

        // Sets the rotation of the entity, and returns a reference for chaining
        virtual Entity & setRotation(float p_rotation);

        // Returns the entity's position at last update
        inline const Vector2f & getLastPosition() const { return m_lastPos; };

        // Returns the entity's life time in seconds
        inline float getLifeTime() const { return m_lifeTime; }

        // Rotates the entity to face the specified point
        void lookAt(const Vector2f & target);

        // Applies an acceleration to the entity's speed.
        virtual void accelerate(const Vector2f & acc, float delta, World * world = NULL);

        // Moves the entity using its current speed.
        virtual void move(float delta, World & world);

        // Moves the entity from a motion in units.
        // If the entity has a Physics component, the resulting motion can be different.
        // Return : resulting motion.
        virtual Vector2f move(const Vector2f & motion, World & world);

        // Updates the entity for one frame
        virtual void update(GameUpdate & up);

        /* Events */

        // Called on the first update before spawning
        virtual void onFirstUpdate(GameUpdate & up) {}

        // Called just before the entity to be destroyed
        virtual void onDestruction(GameUpdate & up) {}

        // Called when a message is send to the entity
        virtual bool processMessage(Message & msg);

        // Renders the entity (not currently used)
        void render(Graphics & gfx);

        // Registers the entity's rendering
        virtual void registerRender(RenderManager & manager);

        // Returns the type ID of the entity (Used for serialization and specializations)
        virtual int getType() const { return -1; }

        /* Static methods */

        // Creates an entity from a type ID
        static Entity * createEntityFromType(int type);

        // Serialization
        static void serializeEntity(std::ostream & os, Entity & entity);
        static Entity * unserializeEntity(std::istream & is) throw(GameException);

    protected :

        // Called from the update() method, for implementing very specific behaviors
        virtual void updateMe(GameUpdate & up) {}

        // Called from the update() method.
        // Updates the entity's components.
        void updateComponents(GameUpdate & up);

        // Serialization (should not be used if we don't know the type of the entity)
        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // ENTITY_HPP_INCLUDED



