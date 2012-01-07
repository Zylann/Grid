/*
Grid
ResourceManager.cpp

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

namespace util
{
namespace resources
{
    /* Static variables */

    ResourceManager<sf::Image> g_images;
    ResourceManager<sf::SoundBuffer> g_soundBuffers;
    ResourceManager<sf::Font> g_fonts;
    ResourceManager<sf::PostFX> g_postFxManager;

    /* Static methods */

    ResourceManager<sf::Image> & getImageManager()
    {
        return g_images;
    }

    ResourceManager<sf::SoundBuffer> & getSoundBufferManager()
    {
        return g_soundBuffers;
    }

    ResourceManager<sf::Font> & getFontManager()
    {
        return g_fonts;
    }

    ResourceManager<sf::PostFX> & getPostFXManager()
    {
        return g_postFxManager;
    }

    sf::Image & getImage(const std::string & name) throw(ResourceManagerException)
    {
        return g_images.getResource(name);
    }

    sf::SoundBuffer & getSoundBuffer(const std::string & name) throw(ResourceManagerException)
    {
        return g_soundBuffers.getResource(name);
    }

    sf::Font & getFont(const std::string & name) throw(ResourceManagerException)
    {
        return g_fonts.getResource(name);
    }

    sf::PostFX & getPostFX(const std::string & name) throw(ResourceManagerException)
    {
        return g_postFxManager.getResource(name);
    }

} // namespace resources
} // namespace util

