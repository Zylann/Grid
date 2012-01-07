/*
Grid
macros.hpp

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

#ifndef MACROS_HPP_INCLUDED
#define MACROS_HPP_INCLUDED

/* CALL-ONCE */

// use : simply put CALL_ONCE() at the function's beginning

#define CALL_ONCE() \
    static bool __called = false; \
    if(!__called) \
        __called = true; \
    else \
    {   \
        throw util::Exception("a call-once function has been called more than 1 time"); \
    }

/* FOREACH */

// use : FOREACH(iteratorName, containerName) { stuff...}

#define FOREACH( i, c ) \
    typedef __typeof__( c ) c##_CONTAINERTYPE; \
    for( c##_CONTAINERTYPE::iterator i = c.begin(); i != c.end(); i++ )

#define CONST_FOREACH( i, c ) \
    typedef __typeof__( c ) c##_CONTAINERTYPE; \
    for( c##_CONTAINERTYPE::const_iterator i = c.begin(); i != c.end(); i++ )

#define REVERSE_FOREACH( i, c ) \
    typedef __typeof__( c ) c##_CONTAINERTYPE; \
    for( c##_CONTAINERTYPE::reverse_iterator i = c.rbegin(); i != c.rend(); i++ )

#endif // MACROS_HPP_INCLUDED
