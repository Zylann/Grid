/*
Grid
PathFinder.hpp

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

#ifndef UTIL_PATHFINDER_HPP_INCLUDED
#define UTIL_PATHFINDER_HPP_INCLUDED

#include <list>

#include "utility/Buffer2D.hpp"
#include "common.hpp"

#define PATHFINDER_DEFAULT_MAX_STEPS 100

namespace util
{
    /*
        Discret binary 2D-matrix pathfinder.
        It must be inherited in order to override the canPass method
        (it will not work on its own).
    */

    struct PathFinderOptions
    {
        Vector2i start;     // start position
        Vector2i target;    // position we want to go
        Area2D area;        // 2D graph area
        int connexity;      // maximum steps
        int maxSteps;     // 2D connexity (4 or 8)

        PathFinderOptions()
        {
            connexity = 4;
            maxSteps = PATHFINDER_DEFAULT_MAX_STEPS;
        }

        PathFinderOptions(
            const Vector2i & p_start,
            const Vector2i & p_target,
            const Area2D & p_area,
            int p_connexity = 4,
            int p_maxSteps = PATHFINDER_DEFAULT_MAX_STEPS)
        {
            area = p_area;
            maxSteps = p_maxSteps >= 1 ? p_maxSteps : 1;
            start = p_start;
            target = p_target;
            connexity = p_connexity;
        }
    };

    class PathFinder
    {
    protected :

        PathFinderOptions m_options;

        Vector2i m_pos;             // current algorithm position
        Buffer2D<bool> m_visited;   // visited positions
        std::list<Vector2i> m_path; // path from start to target (if it exists)
        bool m_found;               // have we found a path?
        bool m_finished;            // true if the algorithm ended.
        int m_step;                 // current step number

    public :

        PathFinder()
        {
            m_step = 0;
            m_found = false;
        }

        PathFinder(const PathFinderOptions & opt)
        {
            setOptions(opt);
        }

        ~PathFinder()
        {}

        // Initializes the algorithm without modify the options
        void initAlgorithm()
        {
            m_step = 0;
            m_found = false;
            m_finished = false;
            m_path.clear();
            m_visited.create(m_options.area);
        }

        // Sets algorithm options and clears old data
        // Note : setting new options implies the algorithm to be reset
        void setOptions(const PathFinderOptions & opt)
        {
            m_options = opt;

            // Checking connexity
            if(m_options.connexity != 4 && m_options.connexity != 8)
            {
                std::cout << "WARNING: PathFinder:"
                    << "invalid connexity specified (" << m_options.connexity << ")" << std::endl;
                m_options.connexity = 4;
            }
            initAlgorithm();
        }

        const PathFinderOptions & getOptions() const { return m_options; }

        // Executes one step of the algorithm.
        // Returns true if the algorithm is terminated.
        bool step();

        // Executes the entire algorithm at once
        void stepAll();

        // True if a path has been found
        inline bool isFound() const { return m_found; }

        // True if we found a path, or the path doesn't exist, or step limit reached
        inline bool isFinished() const { return m_finished; }

        // Returns the found path. It will be empty if m_found is false.
        const std::list<Vector2i> & getPath() const { return m_path; }

        // Is the cell at (m_pos.x,m_pos.y) available?
        // Note : this one must be overriden to make the algorithm work,
        // because it depends on the 2D space structure you're working with.
        virtual bool canPass(const Vector2i & pos) { return false; }
    };

} // namespace util


#endif // UTIL_PATHFINDER_HPP_INCLUDED
