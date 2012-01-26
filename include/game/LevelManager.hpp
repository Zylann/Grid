/*
Grid
Level.hpp

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

#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include "game/Level.hpp"

namespace grid
{
    /*
        The LevelManager handles level creation, loading and saving.
        There is only one level managed at a time.
    */

    class LevelManager
    {
    private :

        Level * m_level; // current level

        LevelManager()
        {
            m_level = NULL;
        }

        ~LevelManager()
        {
            if(isLevel())
                closeLevel();
        }

    public :

        // Get the unique instance of LevelManager. If it is created if not found.
        static LevelManager & instance();

        // Destroys the unique instance
        static void kill();

        // Creates the current level from specified information.
        // If it already exist, it is erased and replaced.
        // Returns the created level.
        Level * createLevel(const LevelInfo & info);

        // Loads the current level from its name.
        // If it already exist, it is erased and replaced.
        // Returns the loaded level (if loading succeeded).
        Level * openLevel(std::string name) throw(GameException);

        // Saves the current level.
        void saveLevel() throw(GameException);

        // Closes the current level (deleted from memory).
        void closeLevel();

        // Returns true if a level is currently loaded
        bool isLevel() const { return m_level != NULL; }

        // Get the current level. Returns NULL if there is none.
        Level * getLevel();

        // Get the list of available levels to load.
        void getAvailableLevels(std::list<std::string> & levelNames);
    };

} // namespace grid


#endif // LEVELMANAGER_HPP_INCLUDED
