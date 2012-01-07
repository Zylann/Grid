/*
Grid
SpaceDivider.cpp

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

#include "game/SpaceDivider.hpp"

using namespace util;

namespace grid
{
    /*
        Space division
    */

    bool SpaceDivision::addEntity(Entity * e)
    {
        return entities.insert(
            std::pair<int, Entity*>(e->getID(), e)).second;
    }

    bool SpaceDivision::removeEntity(int ID)
    {
        return entities.erase(ID) > 0;
    }

    /*
        Space divider
    */

    SpaceDivision * SpaceDivider::getDivision(const Vector2i & dpos, bool create)
    {
        // Find the division
        std::map<SpaceDivisionCoord,SpaceDivision*>::iterator it = m_divisions.find(dpos);

        if(it != m_divisions.end())
        {
            return it->second;
        }
        else if(create)
        {
            // or create it (we know that inserting is allowed)
            return m_divisions.insert
            (
                std::pair<SpaceDivisionCoord, SpaceDivision*>
                (
                    dpos, new SpaceDivision(dpos)
                )
            ).first->second;
        }
        return NULL;
    }

    void SpaceDivider::getDivisionsFromBox(std::list<Entity*> & divs, const AxisAlignedBB & box)
    {
        // TODO getDivisionsFromBox
    }

    void SpaceDivider::getDivisionsFromCircle(std::list<Entity*> & divs, const Circle & circle)
    {
        // TODO getDivisionsFromCircle
    }

    void SpaceDivider::addEntity(Entity * e)
    {
        getDivision(toDivisionCoords(e->pos))->addEntity(e);
    }

    void SpaceDivider::updateEntityDivision(Entity * e)
    {
        Vector2i divPos = toDivisionCoords(e->pos);
        Vector2i lastDivPos = toDivisionCoords(e->getLastPosition());

        if(divPos != lastDivPos)
        {
            getDivision(lastDivPos)->removeEntity(e->getID());
            getDivision(divPos)->addEntity(e);
        }
    }

    void SpaceDivider::removeEntity(Entity * e)
    {
        getDivision(toDivisionCoords(e->pos))->removeEntity(e->getID());
    }

    void SpaceDivider::print(std::ostream & os, Vector2i min, Vector2i max)
    {
        Vector2i pos;
        for(pos.y = min.y; pos.y <= max.y; pos.y++)
        {
            for(pos.x = min.x; pos.x <= max.x; pos.x++)
            {
                SpaceDivision * div = getDivision(pos, false);
                if(div != NULL)
                    std::cout << div->entities.size() << " ";
                else
                    std::cout << "- ";
            }
            std::cout << std::endl;
        }
    }

} // namespace grid

