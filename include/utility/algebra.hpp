/*
Grid
algebra.hpp

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

#ifndef ALGEBRA_HPP_INCLUDED
#define ALGEBRA_HPP_INCLUDED

namespace util
{
    template <typename T>
    void swap(T & a, T & b)
    {
        static T temp;
        temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    inline T square(const T & a)
    {
        return a * a;
    }

} // namespace util


#endif // ALGEBRA_HPP_INCLUDED
