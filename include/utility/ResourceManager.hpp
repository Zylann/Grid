/*
Grid
ResourceManager.hpp

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

#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <iostream>

#include "utility/filesystem.hpp"
#include "utility/Exception.hpp"

namespace util
{
    /*
        Resource types
    */

    enum ResourceType
    {
        RES_IMAGE = 0,
        RES_SOUNDBUFFER,
        RES_FONT,
        RES_POSTFX
    };

    /*
        Exceptions
    */

    class ResourceManagerException : public util::Exception
    {
    public:
        ResourceManagerException(
            const std::string & msg,
            int level = util::Exception::EX_UNKNOWN) throw()
        : util::Exception(msg, level)
        {}
    };

    /*
        Generic resource manager for SFML
    */

    template <class T>
    class ResourceManager
    {
    private :

        typename std::map<std::string, T*> m_resources;

    public :

        ResourceManager()
        {}

        ~ResourceManager()
        {
            freeResources();
        }

        void loadResource(std::string path, const std::string alias = "")
                throw(ResourceManagerException)
        {
            std::string name;
            if(alias.empty())
                name = path;
            else
                name = alias;

            // Makes the path work both on Windows/UNIX systems
            adaptFilePath(path);

            typename std::map<std::string, T*>::iterator it = m_resources.find(name);

            // 2 resources cannot have the same name
            if(it != m_resources.end())
            {
                std::stringstream ss;
                ss << "ResourceManager::loadResource: "
                    << "cannot register " << path << " with name " << name
                    << " because it is already registered";
                throw ResourceManagerException(ss.str(), util::Exception::EX_ERROR);
            }

            T * resource = new T();

            // Check if the loading is ok
            if(!resource->LoadFromFile(path))
            {
                std::stringstream ss;
                ss << "ResourceManager::loadResource: "
                    << "cannot load " << path;
                throw ResourceManagerException(ss.str(), util::Exception::EX_ERROR);
            }

            m_resources.insert(std::pair<std::string, T*>(name, resource));
        }

        T & getResource(const std::string & name) throw(ResourceManagerException)
        {
            typename std::map<std::string, T*>::iterator it = m_resources.find(name);
            if(it != m_resources.end())
                return *(it->second);
            else
            {
                std::stringstream ss;
                ss << "ResourceManager::getResource:"
                    << "cannot find resource from name " << name;
                throw ResourceManagerException(ss.str(), util::Exception::EX_ERROR);
            }
        }

        void freeResource(const std::string & name)
        {
            typename std::map<std::string, T*>::iterator it = m_resources.find(name);
            if(it != m_resources.end())
            {
                delete it->second;
                m_resources.erase(it);
            }
        }

        void freeResources()
        {
            typename std::map<std::string, T*>::iterator it;
            for(it = m_resources.begin(); it != m_resources.end(); it++)
            {
                delete it->second;
            }
            m_resources.clear();
        }
    };

namespace resources
{
    ResourceManager<sf::Image> & getImageManager();
    ResourceManager<sf::SoundBuffer> & getSoundBufferManager();
    ResourceManager<sf::Font> & getFontManager();
    ResourceManager<sf::PostFX> & getPostFXManager();

    sf::Image & getImage(const std::string & name) throw(ResourceManagerException);
    sf::SoundBuffer & getSoundBuffer(const std::string & name) throw(ResourceManagerException);
    sf::Font & getFont(const std::string & name) throw(ResourceManagerException);
    sf::PostFX & getPostFX(const std::string & name) throw(ResourceManagerException);

} // namespace resources
} // namespace util


#endif // RESOURCEMANAGER_H_INCLUDED
