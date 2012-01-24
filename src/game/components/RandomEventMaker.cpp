/*
Grid
RandomEventMaker.cpp

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

#include "game/components/RandomEventMaker.hpp"
#include "game/GameUpdate.hpp"

namespace grid
{
    void RandomEventMaker::randomizeRemainingTime()
    {
        m_remainingTime = sf::Randomizer::Random(m_minInterval, m_maxInterval);
    }

    void RandomEventMaker::update(GameUpdate & up)
    {
        m_remainingTime -= up.delta;
        if(m_remainingTime < 0)
        {
            randomizeRemainingTime();
            doEvent(*(up.level));
        }
    }

    bool RandomEventMaker::processMessage(Message & msg)
    {
        return false;
    }

    /*
        Serialization
    */

    void RandomEventMaker::serialize(std::ostream & os)
    {
        GameObject::serialize(os);

        util::serialize(os, m_minInterval);
        util::serialize(os, m_maxInterval);
        util::serialize(os, m_remainingTime);
    }

    void RandomEventMaker::unserialize(std::istream & is)
    {
        GameObject::unserialize(is);

        util::unserialize(is, m_minInterval);
        util::unserialize(is, m_maxInterval);
        util::unserialize(is, m_remainingTime);
    }

} // namespace grid

