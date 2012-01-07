/*
Grid
Sampler.cpp

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

#include <iostream>

#include "utility/Sampler.hpp"

// Sampling : 2^8 = 256
// Must be a power of 2.
#define SAMPLER_SIZE 0x000000ff

namespace util
{
    Sampler::Sampler(
        double (*f)(double),
        float min, float max,
        bool periodic)
    {
        m_min = min < max ? min : max;
        m_max = max > min ? max : min;
        m_periodic = periodic;

        // Allocating data
        m_data = new float[SAMPLER_SIZE];

        // Storing computed values
        for(int i = 0; i < SAMPLER_SIZE; i++)
        {
            m_data[i] = f(convertIndex(i));
        }
    }

    Sampler::~Sampler()
    {
        // Free data
        delete[] m_data;
    }

    const float Sampler::getValue(float t)
    {
        return m_data[index(t)];
    }

    const int Sampler::index(float t)
    {
        // Compute the index
        int i = (t - m_min) * (float)SAMPLER_SIZE / (m_max - m_min);

        /* i will be kept in [0,SAMPLER_SIZE] with the following instructions */

        // If the function is periodic
        if(m_periodic)
        {
            // Bits higher than the sampling are set to 0,
            // because SAMPLER_SIZE must be a power of 2.
            // This results in a modulo computation, even if i is negative.
            return i & SAMPLER_SIZE;
        }

        // Else, i is limited to the extremas.
        if(i >= SAMPLER_SIZE)
            return SAMPLER_SIZE - 1;
        else if(i < 0)
            return 0;

        return i;
    }

    const float Sampler::convertIndex(int i)
    {
        return m_min + (m_max - m_min) * i / SAMPLER_SIZE;
    }

} // namespace util

