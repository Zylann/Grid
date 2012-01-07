/*
Grid
Interval.hpp

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

#ifndef INTERVAL_HPP_INCLUDED
#define INTERVAL_HPP_INCLUDED

#include <iostream>

namespace grid
{
    template <typename T>
    class Interval
    {
    protected :

        T m_min;
        T m_max;

    public :

        Interval()
        {
            min = 0;
            max = 0;
        }

        Interval(const T & min, const T & max)
        {
            set(min, max);
        }

        Interval(const Interval & other)
        {
            set(other.m_min, other.m_max);
        }

        void set(const T & min, const T & max)
        {
            m_min = min < max ? min : max;
            m_max = max > m_min ? max : m_min;
        }

        void setMin(const T & min)
        {
            m_min = min < m_max ? min : m_max;
        }

        void setMax(const T & max)
        {
            m_max = max > m_min ? max : m_min;
        }

        inline const T & getMin() const
        {
            return m_min;
        }

        inline const T & getMax() const
        {
            return m_max;
        }

        const T & getSize() const
        {
            return m_max - m_min;
        }

        const T & getRandom() const
        {
            return sf::Randomizer::Random(m_min, m_max);
        }

        void print(std::ostream & os) const
        {
            os << "[" << m_min << ", " m_max << "]";
        }
    };

    typedef Interval<int> IntInterval;
    typedef Interval<float> FloatInterval;

} // namespace grid


#endif // INTERVAL_HPP_INCLUDED
