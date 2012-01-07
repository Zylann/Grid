/*
Grid
ResourceListFileReader.hpp

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

#ifndef RESOURCELISTFILEREADER_HPP_INCLUDED
#define RESOURCELISTFILEREADER_HPP_INCLUDED

#include <fstream>

#include "utility/LoadingList.hpp"

namespace util
{
    class ResourceListFileReader
    {
    protected :

        LoadingList & r_list;
        std::ifstream & r_file;

    public :

        ResourceListFileReader(LoadingList & loadingList, std::ifstream & ifs)
        : r_list(loadingList), r_file(ifs)
        {}

        bool read();
    };

} // namespace util


#endif // RESOURCELISTFILEREADER_HPP_INCLUDED
