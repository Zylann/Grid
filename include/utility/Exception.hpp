/*
Grid
Exception.hpp

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

#ifndef EXCEPTION_HPP_INCLUDED
#define EXCEPTION_HPP_INCLUDED

#include <exception>
#include <sstream>

/*
    This file is header-only
*/

namespace util
{
    class Exception : public std::exception
    {
    public:

        enum ExceptionLevel
        {
            EX_INFO = 0,
            EX_WARNING,
            EX_ERROR,
            EX_FATAL,
            EX_UNKNOWN
        };

        Exception(const std::string & msg, int level = EX_UNKNOWN) throw()
        {
            switch(level)
            {
                case EX_INFO        : m_msg = "INFO: "; break;
                case EX_WARNING     : m_msg = "WARNING: "; break;
                case EX_ERROR       : m_msg = "ERROR: "; break;
                case EX_FATAL       : m_msg = "FATAL ERROR: "; break;
                default : m_msg = "EXCEPTION: "; break;
            }
            m_msg += msg;
        }

        virtual ~Exception() throw()
        {}

        virtual const char * what() const throw()
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

} // namespace util


#endif // EXCEPTION_HPP_INCLUDED
