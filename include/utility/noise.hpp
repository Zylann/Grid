/*
Grid
noise.hpp

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

#ifndef NOISE_HPP_INCLUDED
#define NOISE_HPP_INCLUDED

namespace util
{
    double noise2d(int x, int y, int seed);

    double noise2dGradient(double x, double y, int seed);

    double noise2dPerlin(
        double x, double y, int seed,
        int octaves, double persistence, double period);

} // namespace util


#endif // NOISE_HPP_INCLUDED
