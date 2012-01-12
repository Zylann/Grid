/*
Grid
PathFinder.cpp

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

#include "utility/PathFinder.hpp"

namespace util
{
    enum Direction
    {
        // 4-connexity
        WEST = 0,
        EAST,
        SOUTH,
        NORTH,
        // 8-connexity
        SOUTH_WEST,
        SOUTH_EAST,
        NORTH_WEST,
        NORTH_EAST
    };

    char g_oppositeDirs[] =
    {
        // 4-connexite
        EAST,
        WEST,
        NORTH,
        SOUTH,
        // 8-connexite
        NORTH_EAST,
        NORTH_WEST,
        SOUTH_EAST,
        SOUTH_WEST
    };

    // Conversion table index-vector useable for 4 and 8-connexity
    // dirVector = g_dirs[indexDirection]
    Vector2i g_dirs[] =
    {
        // 4-connexity
        Vector2i(-1, 0),    // WEST
        Vector2i(1, 0),     // EAST
        Vector2i(0, 1),     // SOUTH
        Vector2i(0, -1),    // NORTH
        // 8-connexity
        Vector2i(-1, -1),   // SOUTH-WEST
        Vector2i(-1, 1),    // SOUTH-EAST
        Vector2i(1, -1),    // NORTH-WEST
        Vector2i(1, 1)      // NORTH-EAST
    };

    void PathFinder::stepAll()
    {
        while(!step());
    }

    bool PathFinder::step()
    {
        if(m_finished)
            return true;
        m_step++;

        // Path finding method : A*
        // TODO make A* pathfinding (it is actually random-driven)

        std::vector<int> availableDirections;

        // Marks current position as visited
        m_visited.set(m_pos, true);

        /* Find available directions */

        availableDirections.clear();

        for(int dir = 0; dir < m_options.connexity; dir++)
        {
            Vector2i nextPos = m_pos + g_dirs[dir];

            // Skip if we are out of area
            if(!m_visited.getArea().valid(m_pos))
                continue;

            // Skip if already visited
            if(m_visited.get(nextPos))
                continue;

            // Skip if we can't pass
            if(!canPass(nextPos))
                continue;

            // Finally add direction
            availableDirections.push_back(dir);
        }

        /* Choose a direction, or go back */

        if(availableDirections.size() == 1) // one direction
        {
            m_path.push_back(m_pos);
            m_pos += g_dirs[availableDirections.front()];
        }
        else if(availableDirections.size() > 1) // more than one direction
        {
            m_path.push_back(m_pos);
            // Choix au hasard
            m_pos += g_dirs[availableDirections[rand() % availableDirections.size()]];
        }
        else // none directions
        {
            if(!m_path.empty())
            {
                m_pos = m_path.back(); // back to previous position
                m_path.pop_back();
            }
        }

        // If we reached the target position
        if(m_pos == m_options.target)
            m_found = true; // we won !

        // True if we found a path, or the path doesn't exist, or step limit reached
        m_finished = m_found || m_path.empty() || m_step == m_options.maxSteps;

        return m_finished;
    }

} // namespace util

