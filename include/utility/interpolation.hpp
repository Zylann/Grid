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

#ifndef INTERPOLATION_HPP_INCLUDED
#define INTERPOLATION_HPP_INCLUDED

#include <cmath>

namespace util
{
    // x in [0,1]
    inline double smoothCurve(double x)
    {
        return 6*pow(x,5)-15*pow(x,4)+10*pow(x,3);
    }

    /*
        Linear interpolations
    */

    inline float linearInterpolation(float x0, float x1, float t)
    {
        return x0 + (x1 - x0) * t;
    }

    float biLinearInterpolation(
        float x0y0, float x1y0,
        float x0y1, float x1y1,
        float x, float y);

    float triLinearInterpolation(
        float v000, float v100, float v010, float v110,
        float v001, float v101, float v011, float v111,
        float x, float y, float z);

    /*
        Cubic interpolations
    */

    float cubicInterpolation(float x0, float x1, float x2, float x3, float t);
    float biCubicInterpolation(float x0y[4], float x1y[4], float x2y[4], float x3y[4], float x);

} // namespace util


#endif // INTERPOLATION_HPP_INCLUDED
