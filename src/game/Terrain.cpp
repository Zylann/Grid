/*
Grid
Terrain.cpp

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

#include <vector>

#include "game/Terrain.hpp"

using namespace util;

namespace grid
{
namespace terrain
{
    /*
        Instance
    */

    const Ground & Instance::getGround() const
    {
        return Ground::get(groundType);
    }

    const Block & Instance::getBlock() const
    {
        return Block::get(blockType);
    }

    void Instance::print(std::ostream & os)
    {
        os << "GT=" << getGround().getName()
            << ", BT=" << getBlock().getName();
    }

    /*
        Global variables
    */

    Ground * g_grounds[GT_COUNT];
    Block * g_blocks[BT_COUNT];

    Ground & setGround(Ground * g)
    {
        g_grounds[g->getTypeID()] = g;
        return *g;
    }

    Block & setBlock(Block * b)
    {
        g_blocks[b->getTypeID()] = b;
        return *b;
    }

    /*
        Ground : static methods
    */

    void Ground::init()
    {
        static bool alreadyCalled = false;
        if(alreadyCalled)
        {
            std::cout << "WARNING: Ground::init: called twice or more." << std::endl;
            return;
        }
        alreadyCalled = true;

        for(unsigned int i = 0; i < GT_COUNT; i++)
            g_grounds[i] = NULL;

        setGround(new Ground(GT_VOID))
            .setName("void_ground")
            .setMinimapColor(sf::Color(0, 0, 0));

        setGround(new Ground(GT_NORMAL))
            .setName("normal_ground")
            .setMinimapColor(sf::Color(64, 64, 64));

        setGround(new Ground(GT_ICE))
            .setName("ice_ground")
            .setSlipperiness(0.8)
            .setMinimapColor(sf::Color(0, 192, 192));
        //...
    }

    void Ground::freeAll()
    {
        for(unsigned int i = 0; i < GT_COUNT; i++)
        {
            if(g_grounds[i] != NULL)
                delete g_grounds[i];
            g_grounds[i] = NULL;
        }
    }

    Ground & Ground::get(unsigned char typeID) throw(Exception)
    {
        if(typeID < GT_COUNT)
        {
            if(g_grounds[typeID] != NULL)
                return *(g_grounds[typeID]);
        }
        std::stringstream ss;
        ss << "Ground::get: invalid index or unregistered (" << typeID << ")";
        throw Exception(ss.str(), Exception::EX_ERROR);
    }

    /*
        Block : static methods
    */

    void Block::init()
    {
        static bool alreadyCalled = false;
        if(alreadyCalled)
        {
            std::cout << "WARNING: Block::init: called twice or more." << std::endl;
            return;
        }
        alreadyCalled = true;

        for(unsigned int i = 0; i < BT_COUNT; i++)
            g_blocks[i] = NULL;

        setBlock(new Block(BT_VOID))
            .setName("void_block").setCrossable(false)
            .setMinimapColor(sf::Color(0, 0, 0));

        setBlock(new Block(BT_EMPTY))
            .setName("empty_block").setCrossable(true)
            .setMinimapColor(sf::Color(0, 0, 0));

        setBlock(new Block(BT_WALL))
            .setName("wall").setCrossable(false)
            .setMinimapColor(sf::Color(128, 128, 64));

        setBlock(new Block(BT_DIRT))
            .setName("dirt").setCrossable(false)
            .setMinimapColor(sf::Color(128, 64, 32));
        //...
    }

    void Block::freeAll()
    {
        for(unsigned int i = 0; i < BT_COUNT; i++)
        {
            if(g_blocks[i] != NULL)
                delete g_blocks[i];
            g_blocks[i] = NULL;
        }
    }

    Block & Block::get(unsigned char typeID) throw(Exception)
    {
        if(typeID < BT_COUNT)
        {
            if(g_blocks[typeID] != NULL)
                return *(g_blocks[typeID]);
        }
        std::stringstream ss;
        ss << "Block::get: invalid index or unregistered (" << typeID << ")";
        throw Exception(ss.str(), Exception::EX_ERROR);
    }

    /*
        Block methods
    */

    AxisAlignedBB Block::getBoundingBox(const Vector2i & pos) const
    {
        return m_boundingBox.cloneWithOffset(pos);
    }

    void Block::getCollisions(
        std::list<Collision> & collisions,
        const util::AxisAlignedBB & box,
        const Vector2i & pos) const
    {
        if(m_crossable)
            return;

        static util::AxisAlignedBB absBoundingBox;

        absBoundingBox.minEdge.x = m_boundingBox.minEdge.x + pos.x;
        absBoundingBox.minEdge.y = m_boundingBox.minEdge.y + pos.y;

        absBoundingBox.maxEdge.x = m_boundingBox.maxEdge.x + pos.x;
        absBoundingBox.maxEdge.y = m_boundingBox.maxEdge.y + pos.y;

        if(absBoundingBox.collides(box))
        {
            collisions.push_back(Collision(NULL, absBoundingBox));
        }
    }

} // namespace terrain
} // namespace grid

