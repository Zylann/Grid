/*
Grid
TreeNode.hpp

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

#ifndef TREENODE_HPP_INCLUDED
#define TREENODE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <map>

namespace util
{
    /*
        A TreeNode is any element of a tree graph.
        It can have at most one parent, and any number of children.

        This implementation stores nodes (Val_T) as pointers.
        Each node is deleted from memory when the destructor is called.
    */

    // Val_T is the children type, and must be a TreeNode.
    // Id_T is a node identifier type, and must be comparable.
    template <class Id_T, class Val_T>
    class TreeNode
    {
    protected :

        const Id_T m_ID; // Unique ID (within its parent's children)
        typename std::map<Id_T, Val_T*> m_children; // children nodes
        Val_T * r_parent; // parent node

    public :

        // Creates the tree node.
        TreeNode(Id_T ID, Val_T * parent = NULL)
        : m_ID(ID)
        {
            r_parent = parent;
        }

        // Destroys the tree node and its children.
        virtual ~TreeNode()
        {
            typename std::map<Id_T, Val_T*>::iterator it;
            for(it = m_children.begin(); it != m_children.end(); it++)
                delete it->second;
        }

        // Adds a child to the node. Returns false if it fails.
        // Warning : don't remember to free memory if an error occurs !
        bool addChild(Id_T ID, Val_T * newChild)
        {
            return m_children.insert(
                typename std::pair<Id_T, Val_T*>(ID, newChild)).second;
        }

        // Finds a child of the node. Returns NULL if it's not found.
        Val_T * getChild(int ID)
        {
            typename std::map<Id_T, Val_T*>::iterator it = m_children.find(ID);
            if(it != m_children.end())
                return it->second;
            return NULL;
        }

        // Get the node's parent. Returns NULL if the node is a root.
        Val_T * getParent()
        {
            return r_parent;
        }

        // Computes and returns the node's depth.
        int getDepth()
        {
            int d = 0;
            TreeNode<Id_T, Val_T> * n = getParent();
            while(n != NULL)
            {
                d++;
                n = n->getParent();
            }
            return d;
        }

        // Returns the node's unique ID.
        Id_T getID() const
        {
            return m_ID;
        }

        // Returns the name of the node (debug purposes)
        virtual std::string getName() const
        {
            return "TreeNode";
        }

        // Prints the node in a stream.
        virtual void print(std::ostream & os) const
        {
            os << getName();
        }

        // Prints the node's sub-tree in a stream, using indentation
        // to represent parents and children.
        // d < 0 : display at real depth
        // d = 0 : display as root node
        // d > 0 : display at specified depth
        virtual void printTree(std::ostream & os, int d = -1) const
        {
            if(d < 0)
                d = getDepth();

            // Indentation
            for(int i = 0; i < d; i++)
                std::cout << " ";

            // Printing the node
            print(os);

            // Printing children
            typename std::map<Id_T, Val_T*>::iterator it;
            for(it = m_children.begin(); it != m_children.end(); it++)
            {
                it->second->printTree(os, d + 1);
            }
        }
    };

} // namespace util


#endif // TREENODE_HPP_INCLUDED
