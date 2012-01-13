/*
Grid
ResourceListFileReader.cpp

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

#include "utility/ResourceListFileReader.hpp"
#include "utility/filesystem.hpp"

namespace util
{
    // File syntax :
    //
    // [DIR newDirForFilenamesBelow]
    // [IMAGE imageName alias]
    // [SOUND soundName alias]
    // [FONT fontName alias]
    //
    // Each command can be repeated any times we want.
    // Each parameter of a command is required.

    bool ResourceListFileReader::read()
    {
        if(!r_file.good())
        {
            std::cout << "ERROR: ResourceListFileReader::read: "
                << "cannot read file." << std::endl;
            return false;
        }

        std::string command, directory, fileName, alias;

        while(!r_file.eof())
        {
            command.clear();
            fileName.clear();
            alias.clear();

            r_file >> command;

            if(command == "DIR")
            {
                directory.clear();
                r_file >> directory;

                if(!directory.empty())
                {
                    adaptFilePath(directory);
                    const int i = directory.size() - 1;
                    if(directory[i] != FS_DIR_CHAR)
                        directory += FS_DIR_CHAR;
                }
                continue;
            }

            r_file >> fileName;
            r_file >> alias;

            std::string filePath = directory + fileName;

            if(command == "IMAGE")
            {
                if(!r_list.addItem(LoadingListItem(RES_IMAGE, filePath, alias)))
                    return false;
                continue;
            }

            if(command == "SOUND")
            {
                if(!r_list.addItem(LoadingListItem(RES_SOUNDBUFFER, filePath, alias)))
                    return false;
                continue;
            }

            if(command == "FONT")
            {
                if(!r_list.addItem(LoadingListItem(RES_FONT, filePath, alias)))
                    return false;
                continue;
            }

            if(command == "POSTFX")
            {
                if(!r_list.addItem(LoadingListItem(RES_POSTFX, filePath, alias)))
                    return false;
                continue;
            }
        }
        return true;
    }

} // namespace util

