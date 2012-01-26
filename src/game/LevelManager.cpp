/*
Grid
LevelManager.cpp

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

#include <fstream>

#include "game/LevelManager.hpp"

#include "utility/filesystem.hpp"

using namespace util;

namespace grid
{
    LevelManager * g_instance = NULL;

    /*
        Static methods
    */

    // Get the unique instance of LevelManager. If it is created if not found.
    LevelManager & LevelManager::instance()
    {
        if(g_instance != NULL)
            kill();
        g_instance = new LevelManager();
        return *g_instance;
    }

    // Destroys the unique instance
    void LevelManager::kill()
    {
        if(g_instance != NULL)
            delete g_instance;
        g_instance = NULL;
    }

    /*
        Member methods
    */

    // Creates the current level from specified information.
    // If it already exist, it is erased and replaced.
    // Returns the created level.
    Level * LevelManager::createLevel(const LevelInfo & info)
    {
        closeLevel();
        m_level = new Level(info);
        return m_level;
    }

    // Loads the current level from its name.
    // If it already exist, it is erased and replaced.
    // Returns the loaded level (if loading succeeded).
    Level * LevelManager::openLevel(std::string name) throw(GameException)
    {
        std::cout << "Loading level..." << std::endl;

        std::string levelPath = "worlds/world/" + name;
        adaptFilePath(levelPath);
        std::ifstream ifs(levelPath.c_str(), std::ios::in | std::ios::binary);
        if(ifs.good())
        {
            if(isLevel())
                closeLevel();

            m_level = new Level();
            m_level->unserialize(ifs);

            ifs.close();
        }
        else
        {
            throw GameException("LevelManager::loadLevel: Cannot load level '" + levelPath + "'");
        }
        std::cout << "Level loaded" << std::endl;
        return getLevel();
    }

    // Saves the current level.
    void LevelManager::saveLevel() throw(GameException)
    {
        if(!isLevel())
            return;

        std::cout << "Saving level..." << std::endl;

        std::string levelPath = "worlds/world/" + m_level->getInfo().name;
        adaptFilePath(levelPath);
        std::ofstream ofs(levelPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

        if(!ofs.good())
            throw Exception("LevelManager::saveLevel: cannot open file " + levelPath);

        m_level->serialize(ofs);
        ofs.close();

        std::cout << "Level saved." << std::endl;
    }

    // Closes the current level (deleted from memory).
    void LevelManager::closeLevel()
    {
        if(m_level != NULL)
            delete m_level;
        m_level = NULL;
    }

    // Get the current level. Returns NULL if there is none.
    Level * LevelManager::getLevel()
    {
        return m_level;
    }

    // Get the list of available levels to load.
    void LevelManager::getAvailableLevels(std::list<std::string> & levelNames)
    {
        // TODO getAvailableLevels
    }

} // namespace grid

