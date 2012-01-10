/*
Grid
EntityPlayer.cpp

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

#include "game/entities/EntityPlayer.hpp"
#include "game/entities/EntityShockWave.hpp"
#include "game/entities/EntityShot.hpp"
#include "game/entities/EntityGrenade.hpp"
#include "game/components/PlayerController.hpp"
#include "game/components/MouseController.hpp"
#include "game/components/Physics.hpp"
#include "game/components/Inventory.hpp"
#include "game/components/OctoDirMover.hpp"
#include "game/components/Health.hpp"
#include "game/items/BallShooter.hpp"
#include "game/items/GrenadeLauncher.hpp"
#include "game/renderers/RenderModel.hpp"
#include "game/renderers/RenderImage.hpp"
#include "game/renderers/RenderInventory.hpp"
#include "game/renderers/RenderHealth.hpp"
#include "game/Model.hpp"
#include "game/GameUpdate.hpp"
#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"

using namespace util;

namespace grid
{
    EntityPlayer::EntityPlayer(int ID) : Entity(ID)
    {
        name = "player";
        team = 1;

        PlayerController * ctrl = new PlayerController(this);
        addComponent(ctrl);

        OctoDirMover * mover = new OctoDirMover(100);
        ctrl->setMover(mover);
        addComponent(mover);

        addComponent(new Physics());

        Health * health = new Health(500, 500, true); // true : invalidate on death
        RenderHealth * rh = new RenderHealth(health, RP_INTERFACE);
        rh->setEntity(this);
        health->setRenderer(rh);
        addComponent(health);

        Inventory * inv = new Inventory(PLAYER_INVENTORY_SIZE);
        Renderer * invRend = new RenderInventory(inv, RP_INTERFACE);
        inv->setRenderer(invRend);
        inv->addItem(new BallShooter());
        inv->addItem(new GrenadeLauncher());
        inv->setPickItems(true);
        addComponent(inv);

        Model * model = new Model();
        model->addShape( new sf::Shape(
            sf::Shape::Circle(0, 0, 0.4,
                                sf::Color(0,255,0), 0.1,
                                sf::Color(0,128,0))));
        model->addShape(new sf::Shape(
            sf::Shape::Line(0, 0, 0.4, 0, 0.1,
                            sf::Color(0,128,0))));

        setRenderer(new RenderModel(RP_EVENTS, model));

        setBoundingBox(new AxisAlignedBB(-0.4, -0.4, 0.4, 0.4));

//        m_targetID = -1;
    }

    util::AxisAlignedBB * EntityPlayer::getBoundingBox()
    {
        return &( m_boundingBox->set(-0.4, -0.4, 0.4, 0.4).offset(pos.x, pos.y) );
    }

    void EntityPlayer::updateMe(GameUpdate & up)
    {
        up.game->getGraphics()->setGameViewCenter(pos);
        Sound::instance().setListenerPosition(pos);
    }

    void EntityPlayer::onFirstUpdate(GameUpdate & up)
    {
//        sf::Image & targetImg = resources::getImage("target");
//        targetImg.SetSmooth(false);
//
//        // Creating target
//        Entity * target = new Entity();
//        target->addComponent(new MouseController());
//        RenderImage * r = new RenderImage(RP_INTERFACE, targetImg);
//        r->setColor(sf::Color(255,255,32,192));
//        r->setBlendMode(sf::Blend::Add);
//        target->setRenderer(r);
//
//        // Binding target
//        addComponent(new LookBind(target->getID()));
//
//        // Spawning target
//        m_targetID = up.world->spawnEntity(target);
    }

    void EntityPlayer::onDestruction(GameUpdate & up)
    {
        up.world->spawnEntity(new EntityShockWave(0.3, 3.5, 12, sf::Color(255,128,0)), pos);
        Sound::instance().playSound("explosion", 1, 100, pos);
    }

} // namespace grid

