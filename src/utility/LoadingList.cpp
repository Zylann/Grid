/*
Grid
LoadingList.cpp

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

// Lua dependency added for the Grid project.
// Just remove it if you don't need it.
#include <lua.hpp>
#include <lunar.h>

#include "utility/ResourceManager.hpp"
#include "utility/LoadingList.hpp"
#include "utility/ResourceListFileReader.hpp"

namespace util
{
    /*
        LoadingListItem
    */

    void LoadingListItem::print(std::ostream & os)
    {
        switch(resourceType)
        {
            case RES_IMAGE :        os << "IMAGE ";     break;
            case RES_SOUNDBUFFER :  os << "SOUND ";     break;
            case RES_FONT :         os << "FONT";       break;
            case RES_POSTFX :       os << "POSTFX";     break;
            default : break;
        }
        os << resourcePath << " " << resourceAlias;
    }

    /*
        LoadingList
    */

    bool LoadingList::addItem(LoadingListItem item)
    {
        if(item.resourceType < 0)
        {
            std::cout << "ERROR: LoadingList::addItem: "
                << "invalid resource type" << item.resourceType << std::endl;
            return false;
        }
        if(item.resourcePath.empty())
        {
            std::cout << "ERROR: LoadingList::addItem: "
                << "the resource path is empty" << item.resourceType << std::endl;
            return false;
        }

        m_toLoad.push_back(item);
        return true;
    }

    bool LoadingList::readResourceListFile(const std::string & path)
    {
        std::ifstream file(path.c_str());
        if(!file.good())
        {
            std::cout << "ERROR: LoadingList::readResourceFile: "
                << "cannot open file " << path << std::endl;
            return false;
        }

        ResourceListFileReader r(*this, file);
        return r.read();
    }

    const LoadingListItem & LoadingList::getNext() const throw(Exception)
    {
        if(!m_toLoad.empty())
            return m_toLoad.front();
        else
            throw Exception("LoadingList::getNext: there is no next item.", Exception::EX_ERROR);
    }

    void LoadingList::loadNext()
    {
        if(finished())
            return;

        const LoadingListItem & item = getNext();

        ResourceManager<sf::SoundBuffer> & sounds = resources::getSoundBufferManager();
        ResourceManager<sf::Image> & images = resources::getImageManager();
        ResourceManager<sf::Font> & fonts = resources::getFontManager();
        ResourceManager<sf::PostFX> & postFX = resources::getPostFXManager();

        switch(item.resourceType)
        {
            case RES_IMAGE :
                images.loadResource(item.resourcePath, item.resourceAlias);
                break;

            case RES_SOUNDBUFFER :
                sounds.loadResource(item.resourcePath, item.resourceAlias);
                break;

            case RES_FONT :
                fonts.loadResource(item.resourcePath, item.resourceAlias);
                break;

            case RES_POSTFX :
                postFX.loadResource(item.resourcePath, item.resourceAlias);
                break;

            default : break;
        }

        m_toLoad.pop_front();
    }

    void LoadingList::print(std::ostream & os)
    {
        std::list<LoadingListItem>::iterator it;
        for(it = m_toLoad.begin(); it != m_toLoad.end(); it++)
        {
            it->print(os);
            os << std::endl;
        }
    }

#ifdef LUA_VERSION
    /* LUA/Lunar interface *///{

    const char LoadingList::className[] = "LoadingList";
    // Methods registering
    #define method(class, name) {#name, &class::name}
    Lunar<LoadingList>::RegType LoadingList::methods[] =
    {
        method(LoadingList, addItem),
        {0, 0}
    };

    int LoadingList::addItem(lua_State* L)
    {
        int nbArgs = lua_gettop(L);
        if(nbArgs == 3)
        {
            if(lua_isstring(L, 1) &&
               lua_isstring(L, 2) &&
               lua_isstring(L, 3))
            {
                std::string resType = lua_tostring(L, 1);
                std::string resPath = lua_tostring(L, 2);
                std::string alias = lua_tostring(L, 3);

                LoadingListItem item;
                item.resourcePath = resPath;
                item.resourceAlias = alias;

                if(resType == "IMAGE")
                    item.resourceType = RES_IMAGE;
                else if(resType == "SOUND")
                    item.resourceType = RES_SOUNDBUFFER;
                else if(resType == "FONT")
                    item.resourceType = RES_FONT;
                else if(resType == "POSTFX")
                    item.resourceType = RES_POSTFX;
                else
                    std::cerr << "SCRIPT WARNING: LoadingList:addItem() :"
                        << "Unknown resource type '" << resType << "'" << std::endl;

                if(item.resourceType >= 0)
                    addItem(item);
            }
            else
            {
                std::cerr << "SCRIPT ERROR: LoadingList:addItem() :"
                    << " bad param type" << std::endl;
                return 0;
            }
        }
        else
        {
            std::cerr << "SCRIPT ERROR: LoadingList:addItem() :"
                << " the method must take 2 parameters" << std::endl;
            return 0;
        }
        return 0;
    }

    bool LoadingList::loadFromLuaScript(std::string scriptPath)
    {
        // We create the Lua execution context
        lua_State * L = luaL_newstate();

        std::cout << "1"; getchar();

        // We load the Lua libraries
        luaL_openlibs(L);

        std::cout << "2"; getchar();

        // We register LoadingList
        Lunar<LoadingList>::Register(L);

        std::cout << "3"; getchar();

        // We launch the script
        if(luaL_dofile(L, scriptPath.c_str()) != 0)
        {
            // If there is an error...
            std::cerr << "SCRIPT ERROR: LoadingList::loadFromLuaScript: "
                << lua_tostring(L, -1);
            lua_close(L);
            return false;
        }

        std::cout << "4"; getchar();
        // We launch the registerResources function
        lua_getglobal(L, "registerResources");
        if(!lua_isfunction(L, -1))
        {
            // If the function doesn't exist...
            std::cerr << "SCRIPT ERROR: LoadingList::loadFromLuaScript: "
                << "couldn't find the 'registerResources' function" << std::endl;
            lua_pop(L, 1);
            lua_close(L);
            return false;
        }
        else
        {
            // We call the function
            Lunar<LoadingList>::push(L, this);
            lua_call(L, 1, 0); // 1 parameter, 0 returns
        }
        lua_close(L);
        return true;
    }
//}
#endif

} // namespace util

