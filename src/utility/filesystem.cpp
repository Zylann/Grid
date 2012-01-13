/*
Grid
filesystem.cpp

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

#include <iostream>

#include "utility/filesystem.hpp"

#if defined(WIN32) || defined(WIN64) // Windows
    #include <windows.h>
#else // POSIX
    #include <sys/stat.h>
#endif

namespace util
{
    void adaptFilePath(std::string & path)
    {
        for(unsigned int i = 0; i < path.size(); i++)
        {
            if(path[i] == '/' || path[i] == '\\')
                path[i] = FS_DIR_CHAR;
        }
    }

#if defined(WIN32) || defined(WIN64) // Windows

    bool isPathExists(std::string path)
    {
        return (GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES);
    }

    bool makeDir(std::string path)
    {
        if(path.empty())
            return false;
        bool success = CreateDirectory(path.c_str(), NULL);
        if(success)
            return true;
        if(GetLastError() == ERROR_ALREADY_EXISTS)
            return true;
        else
            std::cout << "Error : can't create folder '" + path + "'" << std::endl;
        return false;
    }

    bool getDirContent(DirContent& content, std::string dirPath)
    {
        std::string nodeName, fileName;
        bool searchResult;
        WIN32_FIND_DATA findData;

        content.dirPath = dirPath;
        std::string path = dirPath + "\\*.*";
        HANDLE l_searchHandle = FindFirstFile(path.c_str(), & findData);

        if(l_searchHandle == INVALID_HANDLE_VALUE)
        {
            std::cout << "ERROR: INVALID_HANDLE_VALUE" << std::endl;
            return false;
        }

        while( (searchResult = FindNextFile(l_searchHandle, &findData)) == true )
        {
            bool isDirectory = false;
            if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                isDirectory = true;

            fileName = findData.cFileName;
            // not include '.' and '..' folders (current and parent)
            if(fileName != "." && fileName != "..")
            {
                nodeName = fileName;
                content.nodes.push_back(FileSysNode(nodeName.c_str(), isDirectory));
            }
        }
        FindClose(l_searchHandle);
        return true;
    }

#else // POSIX

    bool isPathExists(std::string path)
    {
        struct stat st;
        return (stat(path.c_str(), &st) == 0);
    }

    bool makeDir(std::string path)
    {
        if(path.empty())
            return false;
        // options : user : rwx searchable, group : rwx searchable, others : r-x searchable
        int result = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(result == 0)
            return true;
        if(errno = EEXIST)
            return true;
        else
            std::cout << "Error : can't create folder '" + path + "'" << std::endl;
        return false;
    }

    void getDirContent(std::vector<FileSysNode> nodes, std::string dirPath)
    {
        // TODO getDirContent for Linux POSIX
    }

#endif

    bool makeAllDirs(const FileSysPath& fsPath)
    {
        if(fsPath.isEmpty())
            return false;
        std::string path = "";
        for(unsigned int i = 0; i < fsPath.nodes.size(); i++)
        {
            if(fsPath.nodes[i].isDirectory)
            {
                path += fsPath.nodes[i].name;
                if(!makeDir(path))
                    return false;
                path += FS_DIR_CHAR;
            }
        }
        return true;
    }

    bool makeAllDirs(std::string path)
    {
        if(path.empty())
            return false;
        const FileSysPath fsPath(path);
        return makeAllDirs(fsPath);
    }

} // namespace util

