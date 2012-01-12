/*
Grid
GameException.hpp

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

#ifndef GAMEEXCEPTION_HPP_INCLUDED
#define GAMEEXCEPTION_HPP_INCLUDED

#include "utility/Exception.hpp"

namespace grid
{
    class GameException : public util::Exception
    {
    public:
        GameException(
            const std::string & msg,
            int level = util::Exception::EX_UNKNOWN) throw()
        : util::Exception(msg, level)
        {}
    };

} // namespace grid


#endif // GAMEEXCEPTION_HPP_INCLUDED
