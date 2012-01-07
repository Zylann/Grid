/*
Grid
Buffer2D.hpp

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

#ifndef BUFFER2D_HPP_INCLUDED
#define BUFFER2D_HPP_INCLUDED

#include "utility/Area2D.hpp"
#include "utility/Exception.hpp"

namespace util
{
    /*
        Buffer2D
    */

    template <typename T>
    class Buffer2D
    {
    private :

        T * m_data;		// linear data storage (NULL if empty)
        Area2D m_area;	// size and position

    public :

        // creates an empty buffer
        Buffer2D()
        {
            m_data = NULL;
        }

        // creates a buffer with the specified area
        Buffer2D(const Area2D & area)
        {
            create(area);
        }

        // creates a buffer from another (copy)
        Buffer2D(const Buffer2D & other)
        {
            clear();
            m_area = other.m_area;
            create(m_area);
            memcpy(m_data, other.m_data, m_area.getVolume() * sizeof(T));
        }

        ~Buffer2D()
        {
            clear();
        }

        // creates the buffer from the specified area.
        // old data is cleared.
        // Note : data values are not initialized, use the fill() function is necessary.
        void create(const Area2D & area)
        {
            clear();
            m_area = area;
            m_data = new T[m_area.getVolume()];
        }

        // same as create(Area2D), with an additionnal parameter for default values
        void create(const Area2D & area, const T & defaultValue)
        {
            create(area);
            fill(defaultValue);
        }

        // clears the buffer
        void clear()
        {
            if(m_data != NULL)
            {
                delete[] m_data;
                m_data = NULL;
                m_area.clear();
            }
        }

        // fills the buffer with the same value
        void fill(const T & stamp)
        {
            int vol = m_area.getVolume();
            for(int i = 0; i < vol; i++)
                m_data[i] = stamp;
        }

        const Area2D & getArea() const
        {
            return m_area;
        }

        /*
            2D-data copy optimization :
            For X, we just have a linear copy to do, so for performance improvement
            we use memcpy to do a binary copy from an index to another,
            because data is stored in a linear buffer.
            It's faster than do a classic for.
        */

        // Copy data from a source buffer limited by an area.
        // The source area must be included in the destination area.
        void copyFrom(const T srcData[], const Area2D & srcArea)
                throw(Exception)
        {
            if(!m_area.contains(srcArea))
            {
                std::stringstream ss;
                ss << "Buffer2D::copyFrom: invalid position.";
                ss << " m_area=";    m_area.print(ss);
                ss << " srcArea=";  srcArea.print(ss);
                throw Exception(ss.str(), Exception::EX_ERROR);
            }

            Vector2i pos;
            int i_src, i_dst;

            for(pos.y = 0; pos.y < srcArea.getSize().y; pos.y++)
            {
                i_src = srcArea.relativeIndex(pos);
                i_dst = m_area.index(pos + srcArea.getPosition());
                memcpy(&m_data[i_dst], &srcData[i_src], srcArea.getSize().x * sizeof(T));
            }
        }

        // Copy data from the buffer to a destination buffer limited by an area.
        // The source area must be included in the destination area.
        void copyTo(const T dstData[], const Area2D & dstArea) const
                throw(Exception)
        {
            if(!dstArea.contains(m_area))
            {
                std::stringstream ss;
                ss << "Buffer2D::copyTo: invalid position.";
                ss << " dstArea=";    dstArea.print(ss);
                ss << " m_area=";  m_area.print(ss);
                throw Exception(ss.str(), Exception::EX_ERROR);
            }

            Vector2i pos;
            int i_src, i_dst;

            for(pos.y = 0; pos.y < m_area.getSize().y; pos.y++)
            {
                i_dst = dstArea.index(pos + m_area.getPosition());
                i_src = m_area.relativeIndex(pos);
                memcpy(&dstData[i_dst], &m_data[i_src], m_area.getSize().x * sizeof(T));
            }
        }

        // Returns a reference to the element at the specified position.
        // The position must be valid !
        inline T & getRefNoEx(const Vector2i & pos)
        {
            return m_data[m_area.index(pos)];
        }

        // Returns a reference to the element at the specified position.
        // Throws an exception if the position is invalid.
        T & getRef(const Vector2i & pos)
                throw(Exception)
        {
            if(m_area.valid(pos))
                return getRefNoEx(pos);
            else
            {
                std::stringstream ss;
                ss << "Buffer2D::getRef: invalid position.";
                ss << "pos=(" << pos.x << ", " << pos.y << ")";
                throw Exception(ss.str(), Exception::EX_ERROR);
            }
        }

        // get an element without position validation (it must be valid !)
        inline const T & getNoEx(const Vector2i & pos) const
        {
            return m_data[m_area.index(pos)];
        }

        // get an element
        const T & get(const Vector2i & pos) const
                throw(Exception)
        {
            if(m_area.valid(pos))
                return getNoEx(pos);
            else
            {
                std::stringstream ss;
                ss << "Buffer2D::get: invalid position.";
                ss << "pos=(" << pos.x << ", " << pos.y << ")";
                throw Exception(ss.str(), Exception::EX_ERROR);
            }
        }

        // set an element without position validation (it must be valid !)
        inline void setNoEx(const Vector2i & pos, const T & value)
        {
            m_data[m_area.index(pos)] = value;
        }

        // set an element
        void set(const Vector2i & pos, const T & value)
                throw(Exception)
        {
            if(m_area.valid(pos))
                setNoEx(pos, value);
            else
            {
                std::stringstream ss;
                ss << "Buffer2D::set: invalid position.";
                ss << "pos=(" << pos.x << ", " << pos.y << ")";
                throw Exception(ss.str(), Exception::EX_ERROR);
            }
        }

        // Prints buffer description in an output stream (for debug purposes).
        // Note : very large buffers should not be printed, it would create
        // lines and lines of data (not very useful).
        void print(std::ostream & os) const
        {
            os << "=========== Buffer2D ==========" << std::endl;
            os << "m_area = "; m_area.print(os); os << std::endl;
            os << "m_data =" << std::endl;

            Vector2i pos;
            int i;

            for(pos.y = 0; pos.y < m_area.getSize().y; pos.y++)
            {
                os << " ";
                for(pos.x = 0; pos.x < m_area.getSize().x; pos.x++)
                {
                    i = m_area.index(pos);
                    printDataItem(os, m_data[i]);
                }
                os << std::endl;
            }
            os << "===============================" << std::endl;
        }

        // defines the way an item must be printed
        virtual void printDataItem(std::ostream & os, T & item) const
        {
            //os << item;
            os << "0";
        }
    };

} // namespace util


#endif // BUFFER2D_HPP_INCLUDED
