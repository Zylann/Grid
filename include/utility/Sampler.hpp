/*
Grid
Sampler.hpp

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

#ifndef SAMPLER_HPP_INCLUDED
#define SAMPLER_HPP_INCLUDED

namespace util
{
    /*
        Modelisation of a numeric function f(t) by storing precomputed values.
    */

    class Sampler
    {
    public :

        // Creates the table from the f function, from min to max.
        Sampler( double (*f)(double),
            float min, float max,
            bool periodic = false);

        ~Sampler();

        // Get the computed function value in t.
        // If m_periodic is true, getLookupValue(t) and
        // getLookupValue(t + (m_max-m_min)) will give the same value.
        // Note : values are not interpolated.
        const float getValue(float t);

        // Transforms t into an index
        const int index(float t);

        // Transforms an index into t
        const float convertIndex(int i);

    protected :

        float * m_data; // pre-computed values
        float m_min; // minimum t value
        float m_max; // maximum t value
        bool m_periodic; // is the sampled function periodic?
    };

} // namespace util


#endif // SAMPLER_HPP_INCLUDED
