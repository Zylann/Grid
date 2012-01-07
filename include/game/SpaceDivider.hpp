/*
Grid
SpaceDivider.hpp

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

#ifndef SPACEDIVIDER_HPP_INCLUDED
#define SPACEDIVIDER_HPP_INCLUDED

#include <map>

#include "utility/Buffer2D.hpp"
#include "game/entities/Map.hpp"

#define SPACE_DIVIDER_SCALE 4

namespace grid
{
	struct SpaceDivisionCoord
	{
	    int x;
	    int y;

	    SpaceDivisionCoord()
	    {
	        x = 0;
	        y = 0;
	    }

	    SpaceDivisionCoord(const Vector2i & pos)
	    {
	        x = pos.x;
	        y = pos.y;
	    }

	    bool operator==(const SpaceDivisionCoord & other) const
	    {
	        return x == other.x && y == other.y;
	    }

	    bool operator<(const SpaceDivisionCoord & other) const
	    {
            return (x != other.x) ? (x < other.x) : (y < other.y);
	    }
	};

	struct SpaceDivision
	{
		std::map<int, Entity*> entities;
		Vector2i pos;

		bool addEntity(Entity * e);
		bool removeEntity(int ID);

		SpaceDivision(const Vector2i & p_pos)
		{
		    pos = p_pos;
		}
	};

	/*
		The SpaceDivider divides the space into squares of SPACE_DIVIDER_SCALE units.
		Every times an entity come into play, moves or leaves the game,
		its division can be updated.
		This is useful for performance improvements :
		for example, if we have a lot of entities dispersed around the map,
		we can avoid computations for entities that are too far away from each other.
		>> see World::getCollisions for an example
	*/

    class SpaceDivider
    {
	private :

		std::map<SpaceDivisionCoord, SpaceDivision*> m_divisions;

	public :

        SpaceDivider()
        {}

        ~SpaceDivider()
        {
            clear();
        }

		void clear()
		{
            std::map<SpaceDivisionCoord,SpaceDivision*>::iterator it;
            for(it = m_divisions.begin(); it != m_divisions.end(); it++)
                delete it->second;
            m_divisions.clear();
		}

		// If create is true, a space division will be created if it not exists
		// and will be returned.
		// However, it returns NULL if it doesn't exist.
		SpaceDivision * getDivision(const Vector2i & dpos, bool create = true);
		void getDivisionsFromBox(std::list<Entity*> & divs, const AxisAlignedBB & box);
		void getDivisionsFromCircle(std::list<Entity*> & divs, const Circle & circle);

		void addEntity(Entity * e);
		void updateEntityDivision(Entity * e);
		void removeEntity(Entity * e);

		void print(std::ostream & os, Vector2i min, Vector2i max);

		inline Vector2i toDivisionCoords(const Vector2i & pos) const
		{
			return pos / SPACE_DIVIDER_SCALE;
		}

		inline Vector2i toDivisionCoords(const Vector2f & pos) const
		{
			return Vector2i((int)(pos.x) / SPACE_DIVIDER_SCALE,
                            (int)(pos.y) / SPACE_DIVIDER_SCALE);
		}
    };

} // namespace grid


#endif // SPACEDIVIDER_HPP_INCLUDED
