/*
Grid
LoadingList.hpp

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

#ifndef LOADINGLIST_HPP_INCLUDED
#define LOADINGLIST_HPP_INCLUDED

#include <list>

#include "utility/ResourceManager.hpp"

namespace util
{
    struct LoadingListItem
    {
        int resourceType;
        std::string resourcePath;
        std::string resourceAlias;

        LoadingListItem() : resourceType(-1) {}

        LoadingListItem( int rtype,
            const std::string & rpath,
            const std::string & ralias)
        : resourceType(rtype),
            resourcePath(rpath),
            resourceAlias(ralias)
        {}

        void print(std::ostream & os);
    };

    class LoadingList
    {
    public :

        LoadingList()
        {}

        // Adds an item to the list by adapting it if needed (OS compatibility).
        // Returns false if the item is invalid.
        bool addItem(LoadingListItem item);

        // Adds items to the list from a text file
        bool readResourceListFile(const std::string & path);

        // Resource load handling
        bool finished() const { return m_toLoad.empty(); }
        const LoadingListItem & getNext() const throw(Exception);
        void loadNext();
        int getTotalRemaining() const { return m_toLoad.size(); }

        // Writes the list to a stream
        void print(std::ostream & os);

        // Clears the list
        void clear() { m_toLoad.clear(); }

    private :

        std::list<LoadingListItem> m_toLoad;

#ifdef LUA_VERSION
    /* LUA/Lunar interface *///{

    private :

        friend class Lunar<LoadingList>;
        static const char className[];
        static Lunar<LoadingList>::RegType methods[];

    public :

        LoadingList(lua_State * L)
        {}

        int addItem(lua_State* L);

        bool loadFromLuaScript(std::string scriptPath);

        //}
#endif
    };

} // namespace util


#endif // LOADINGLIST_HPP_INCLUDED
