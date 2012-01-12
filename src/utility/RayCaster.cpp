/*
Grid
RayCaster.cpp

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

#include "utility/RayCaster.hpp"
#include "utility/geometry.hpp"

namespace util
{
    // Initializes the algorithm without modify the options
    void RayCaster::initAlgorithm()
    {
        m_dir.x = cos(m_options.angle);
        m_dir.y = sin(m_options.angle);
        m_pos = m_options.start;
        m_step = 0;
        m_blocked = false;
    }

    // Executes one step of the algorithm.
    // Returns true if the algorithm ended.
    bool RayCaster::step()
    {
        if(isFinished())
            return true;
        m_step++;

        // TODO optimize RayCaster
        // The current technique is iterative and not very accurate

        m_pos += m_dir * 0.1f;
        Vector2i ipos(m_pos.x, m_pos.y);
        m_blocked = !canPass(ipos);

        return isFinished();
    }

    // Executes the entire algorithm until it stops.
    void RayCaster::stepAll()
    {
        while(!step());
    }

    // True if the algorithm ended.
    bool RayCaster::isFinished() const
    {
        return m_step >= m_options.maxSteps || isMaxDistanceReached() || m_blocked;
    }

    // True if the maximum distance has been reached.
    bool RayCaster::isMaxDistanceReached() const
    {
        if(m_options.maxDistance >= 0)
            return getDistanceCrossed() >= m_options.maxDistance;
        else
            return false;
    }

    // Returns the current crossed distance
    float RayCaster::getDistanceCrossed() const
    {
        return distance2D(m_pos, m_options.start);
    }

} // namespace util

