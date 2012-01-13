/*
Grid
filesystem.hpp

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

#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

#include <string>

#include "utility/FileSysPath.hpp"

namespace util
{
    // directory contents
    struct DirContent
    {
        std::vector<FileSysNode> nodes;
        std::string dirPath;

        void print()
        {
            std::cout << dirPath << " :" << std::endl;
            for(unsigned int i = 0; i < nodes.size(); i++)
            {
                if(nodes[i].isDirectory)
                    std::cout << "dir  ";
                else
                    std::cout << "file ";
                std::cout << nodes[i].name << std::endl;
            }
        }
    };

    void adaptFilePath(std::string & path);

    // get files and directories of a directory (just names)
    bool getDirContent(DirContent& content, std::string dirPath);

    // find if a file or directory exists
    bool isPathExists(std::string path);

    // create a directory
    bool makeDir(std::string fsPath);

    // create all directories contained in fsPath
    bool makeAllDirs(const FileSysPath& fsPath);

    // create all directories contained in path (based on the function above)
    bool makeAllDirs(std::string path);

    // TODO remove files function
    //bool removeFilesRecursive(std::string path);

} // namespace util


#endif // FILESYSTEM_HPP_INCLUDED
