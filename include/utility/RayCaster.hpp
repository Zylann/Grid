/*
Grid
utility/RayCaster.hpp

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

#ifndef UTIL_RAYCASTER_HPP_INCLUDED
#define UTIL_RAYCASTER_HPP_INCLUDED

#include "common.hpp"

#define RAYCASTER_DEFAULT_MAX_STEPS 1000

namespace util
{
    struct RayCasterOptions
    {
        Vector2f start;
        float angle;
        float maxDistance; // -1 means infinite
        int maxSteps;

        RayCasterOptions()
        {
            angle = 0;
            maxDistance = 0;
            maxSteps = RAYCASTER_DEFAULT_MAX_STEPS;
        }

        RayCasterOptions(
            const Vector2f p_start,
            float p_angle,
            float p_maxDistance = -1,
            int p_maxSteps = RAYCASTER_DEFAULT_MAX_STEPS)
        {
            start = p_start;
            angle = p_angle;
            maxDistance = p_maxDistance;
            maxSteps = p_maxSteps >= 0 ? p_maxSteps : 0;
        }
    };

    class RayCaster
    {
    protected :

        RayCasterOptions m_options;

        Vector2f m_dir;
        Vector2f m_pos;
        int m_step;
        bool m_blocked;

    public :

        RayCaster()
        {
            m_step = 0;
            m_blocked = false;
        }

        RayCaster(const RayCasterOptions & opt)
        {
            setOptions(opt);
        }

        // Sets algorithm options and clears old data
        // Note : setting new options implies the algorithm to be reset
        void setOptions(const RayCasterOptions & opt)
        {
            m_options = opt;
            initAlgorithm();
        }

        const RayCasterOptions & getOptions() const { return m_options; }

        // Initializes the algorithm without modify the options
        void initAlgorithm();

        // Executes one step of the algorithm.
        // Returns true if the algorithm ended.
        bool step();

        // Executes the entire algorithm until it stops.
        void stepAll();

        // True if the algorithm ended.
        bool isFinished() const;

        // True if the maximum distance has been reached.
        bool isMaxDistanceReached() const;

        inline bool isBlocked() const { return m_blocked; }

        // Returns the current crossed distance
        float getDistanceCrossed() const;

        // Returns the current ray position
        inline const Vector2f getPosition() const { return m_pos; }

        // Must return true if the ray can cross the specified position.
        // Note : this one must be overriden to make the algorithm work,
        // because it depends on the 2D space structure you're working with.
        virtual bool canPass(Vector2i & pos) { return false; };
    };

} // namespace util


#endif // UTIL_RAYCASTER_HPP_INCLUDED
