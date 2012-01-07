/*
Grid
EntitySentinel.cpp

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

#include "game/entities/EntitySentinel.hpp"

#include "game/components/Physics.hpp"
#include "game/components/Inventory.hpp"
#include "game/components/Health.hpp"
#include "game/items/BallShooter.hpp"
#include "game/renderers/RenderModel.hpp"
#include "game/renderers/RenderHealth.hpp"
#include "game/Model.hpp"
#include "game/GameUpdate.hpp"
#include "game/entities/EntityShockWave.hpp"
#include "game/entities/EntityShot.hpp"
#include "game/Sound.hpp"

#include "utility/AxisAlignedBB.hpp"

using namespace util;

namespace grid
{
    EntitySentinel::EntitySentinel(int ID) : Entity(ID)
    {
        static int instanceCount = 1;
        std::stringstream ss;
        ss << "sentinel_" << instanceCount;
        name = ss.str();
        instanceCount++;

//        OctoDirMover * mover = new OctoDirMover(100);
//        ctrl->setMover(mover);
//        addComponent(mover);

        addComponent(new Physics());

        Health * health = new Health(100, 100, true); // true : invalidate on death
        RenderHealth * renderHealth = new RenderHealth(health, RP_INTERFACE, true);
        renderHealth->setEntity(this);
        health->setRenderer(renderHealth);
        addComponent(health);

        Inventory * inv = new Inventory(1);
        inv->addItem(new BallShooter());
        addComponent(inv);

        Model * model = new Model();
        model->addShape( new sf::Shape(
            sf::Shape::Circle(0, 0, 0.4,
                                sf::Color(64,64,64), 0.1,
                                sf::Color(0,0,0))));
        model->addShape(new sf::Shape(
            sf::Shape::Line(0, 0, 0.4, 0, 0.1,
                            sf::Color(0,0,0))));

        setRenderer(new RenderModel(RP_EVENTS, model));

        setBoundingBox(new AxisAlignedBB(-0.4, -0.4, 0.4, 0.4));
    }

    void EntitySentinel::updateMe(GameUpdate & up)
    {
        Message msg(M_ITM_TRIGGER, this, false);
        processMessage(msg);

        rotation += M_PI * up.delta;

        Entity * p = up.world->getMainPlayer();
        if(p != NULL)
        {
            float d = distance2D(p->pos, pos);
            if(d < 10)
            {
                lookAt(p->pos);

                if(d > 5)
                {
                    Vector2f v(cos(rotation), sin(rotation));
                    accelerate(50.f * v, up.delta);
                }

                if(sf::Randomizer::Random(0.f, 1.f) < 0.02f)
                {
                    Message msg(M_ITM_TRIGGER, this, true);
                    processMessage(msg);
                }
            }
        }
    }

    util::AxisAlignedBB * EntitySentinel::getBoundingBox()
    {
        return &( m_boundingBox->set(-0.4, -0.4, 0.4, 0.4).offset(pos.x, pos.y) );
    }

    void EntitySentinel::onDestruction(GameUpdate & up)
    {
        up.world->spawnEntity(new EntityShockWave(0.3, 3.5, 12, sf::Color(255,128,0)), pos);
        Sound::instance().playSound("explosion", sf::Randomizer::Random(0.8f, 1.2f), 100, pos);
    }

} // namespace grid

