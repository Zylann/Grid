/*
Grid
Map.hpp

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

#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "utility/Buffer2D.hpp"

#include "game/Terrain.hpp"
#include "game/renderers/RenderMap.hpp"
#include "game/base/Entity.hpp"

namespace grid
{
    // Note : the map is an Entity, but none of movements must be used with it.

    class Map : public Entity
    {
    private :

        util::Buffer2D<terrain::Instance> m_data;
        sf::Image m_minimap;
        RenderMap * r_renderMap;

    public :

        Map(int ID = -1, Vector2i size = Vector2i());

        void create(Vector2i size);

        terrain::Instance getTerrain(const Vector2i & pos) const;
        void setTerrain(const Vector2i & pos, terrain::Instance t);
        void updateMinimap(const Vector2i & pos);
        const sf::Image & getMinimap() const { return m_minimap; }

        const Vector2i & getSize() const { return m_data.getArea().getSize(); }
        bool contains(const Vector2i & pos) const { return m_data.getArea().valid(pos); }

        virtual void getCollisions(
            std::list<Collision>& collisions,
            const util::AxisAlignedBB& box);

        virtual void updateMe(GameUpdate & up);

        void clear();

        virtual int getType() const { return ENT_MAP; }

        /* Disables movement */

        virtual Entity & setPosition(const Vector2f & p_pos) { return *this; }
        virtual Entity & setSpeed(const Vector2f & p_pos) { return *this; }
        virtual Entity & setRotation(float p_rotation) { return *this; }
        virtual void accelerate(const Vector2f & acc, float delta) {}
        virtual void move(float delta, World & world) {}
        virtual Vector2f move(const Vector2f & motion, World & world) { return Vector2f(); }

    protected :

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // MAP_HPP_INCLUDED
