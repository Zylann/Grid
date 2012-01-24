/*
Grid
.hpp

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

#ifndef RANDOMEVENTMAKER_HPP_INCLUDED
#define RANDOMEVENTMAKER_HPP_INCLUDED

#include "game/base/Component.hpp"

namespace grid
{
    class Level;

    class RandomEventMaker : public Component
    {
    protected :

        float m_minInterval; // minimal time interval between events
        float m_maxInterval; // maximal time interval
        float m_remainingTime; // time before next event

    public :

        RandomEventMaker(float minInterval, float maxInterval, int ID = -1) : Component(ID)
        {
            m_minInterval = minInterval > 1.f ? minInterval : 1.f;
            m_maxInterval = maxInterval >= m_minInterval ? maxInterval : m_minInterval;

            randomizeRemainingTime();
        }

        void randomizeRemainingTime();

        virtual void doEvent(Level & level) = 0;

        virtual void update(GameUpdate & up);
        virtual bool processMessage(Message & msg);

        virtual void serialize(std::ostream & os);
        virtual void unserialize(std::istream & is);
    };

} // namespace grid


#endif // RANDOMEVENTMAKER_HPP_INCLUDED
