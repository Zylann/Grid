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

} // namespace util

