/*
Grid
Terrain.hpp

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

#ifndef TERRAIN_HPP_INCLUDED
#define TERRAIN_HPP_INCLUDED

#include <list>

#include "common.hpp"

#include "utility/Exception.hpp"
#include "utility/AxisAlignedBB.hpp"
#include "utility/serialization.hpp"

#include "game/Collision.hpp"

namespace grid
{
namespace terrain
{
    /*
        Types ID
    */

    enum GroundType
    {
        GT_VOID = 0, // keep 0
        GT_NORMAL,
        GT_ICE,

        GT_COUNT // keep last
    };

    enum BlockType
    {
        BT_VOID = 0, // keep 0
        BT_EMPTY,
        BT_WALL,
        BT_DIRT,

        BT_COUNT // keep last
    };

    /*
        Instance
    */

    struct Instance
    {
        unsigned char groundType;
        unsigned char blockType;

        Instance()
        {
            groundType = GT_NORMAL;
            blockType = BT_EMPTY;
        }

        Instance(
            unsigned char p_groundType,
            unsigned char p_blockType)
        {
            groundType = p_groundType;
            blockType = p_blockType;
        }

//        const Ground & getGround() const
//        {
//            return Ground::get(groundType);
//        }
//
//        const Block & getBlock() const
//        {
//            return Block::get(blockType);
//        }

        void serialize(std::ostream & os) const
        {
            util::serialize(os, groundType);
            util::serialize(os, blockType);
        }

        void unserialize(std::istream & is)
        {
            util::unserialize(is, groundType);
            util::unserialize(is, blockType);
        }
    };

    /*
        Terrain element
    */

    class TerrainElement
    {
    protected :

        unsigned char m_typeID;
        std::string m_name;

    public :

        const std::string & getName() { return m_name; }
        const unsigned char getTypeID() { return m_typeID; }

    protected :

        TerrainElement(unsigned char typeID)
        {
            m_typeID = typeID;
        }

        virtual ~TerrainElement()
        {}
    };

    /*
        Ground
    */

    class Ground : public TerrainElement
    {
    protected :

        float m_slipperiness;

    public :

        static void init();
        static void freeAll();
        static Ground & get(unsigned char typeID) throw(util::Exception);

        float getSlipperiness() const { return m_slipperiness; }

    protected :

        Ground(unsigned char typeID) : TerrainElement(typeID)
        {
            m_slipperiness = 0;
        }

        virtual ~Ground()
        {}

        Ground & setSlipperiness(float s)
        {
            m_slipperiness = s;
            return *this;
        }

        Ground & setName(const std::string & name)
        {
            m_name = name;
            return *this;
        }
    };

    /*
        Block
    */

    class Block : public TerrainElement
    {
    protected :

        bool m_crossable;
        util::AxisAlignedBB m_boundingBox;

    public :

        static void init();
        static void freeAll();
        static Block & get(unsigned char typeID) throw(util::Exception);

        bool isCrossable() { return m_crossable; }

        virtual util::AxisAlignedBB getBoundingBox(const Vector2i & pos) const;

        void getCollisions(
            std::list<Collision> & collisions,
            const util::AxisAlignedBB & box,
            const Vector2i & pos) const;

    protected :

        Block(unsigned char typeID) : TerrainElement(typeID)
        {
            m_crossable = true;
            m_boundingBox = util::AxisAlignedBB(0,0, 1,1);
        }

        virtual ~Block()
        {}

        Block & setBoundingBox(const util::AxisAlignedBB box)
        {
            m_boundingBox = box;
            return *this;
        }

        Block & setName(const std::string & name)
        {
            m_name = name;
            return *this;
        }

        Block & setCrossable(bool c)
        {
            m_crossable = c;
            return *this;
        }
    };

} // namespace terrain
} // namespace grid


#endif // TERRAIN_HPP_INCLUDED
