/*
Grid
FileSysPath.hpp

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

#ifndef FILESYSPATH_HPP_INCLUDED
#define FILESYSPATH_HPP_INCLUDED

/* Header-only */

#include <string>
#include <vector>

#if defined(WIN32) || defined(WIN64) // Windows
    #define FS_DIR_CHAR '\\'
#else // POSIX
    #define FS_DIR_CHAR '/'
#endif

namespace util
{
    struct FileSysNode
    {
        std::string name;
        bool isDirectory;

        FileSysNode() { isDirectory = false; }

        FileSysNode(std::string p_name, bool dir)
        : name(p_name), isDirectory(dir)
        {}
    };

    class FileSysPath
    {
    public :

        FileSysPath() {}

        FileSysPath(std::string strPath)
        {
            create(strPath);
        }

        void create(std::string strPath)
        {
            nodes.clear();

            if(strPath.empty())
                return;

            FileSysNode node;
            for(unsigned int i = 0; i < strPath.size(); i++)
            {
                if(strPath[i] != '/' && strPath[i] != '\\')
                {
                    node.isDirectory = false;
                    node.name += strPath[i];
                }
                else
                {
                    node.isDirectory = true;
                    nodes.push_back(node);
                    node.name = "";
                }
            }
            if(!node.isDirectory)
                nodes.push_back(node);
        }

        bool isEmpty() const
        {
            return nodes.empty();
        }

        bool isDirectoryPath() const
        {
            if(nodes.empty())
                return false;
            return nodes.back().isDirectory;
        }

        void appendDir(std::string dirName)
        {
            if(!nodes.empty())
            {
                if(!nodes.back().isDirectory)
                    return;
            }
            nodes.push_back(FileSysNode(dirName, true));
        }

        void appendFile(std::string fileName)
        {
            nodes.push_back(FileSysNode(fileName, false));
        }

        void appendPath(FileSysPath fsPath)
        {
            for(unsigned int i = 0; i < fsPath.nodes.size(); i++)
                nodes.push_back(fsPath.nodes[i]);
        }

        std::string toString() const
        {
            std::string path;
            for(unsigned int i = 0; i < nodes.size(); i++)
            {
                path += nodes[i].name;
                if(nodes[i].isDirectory)
                    path += FS_DIR_CHAR;
            }
            return path;
        }

        // public attribute
        std::vector<FileSysNode> nodes;
    };

} // namespace util


#endif // FILESYSPATH_HPP_INCLUDED
