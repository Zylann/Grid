/*
Grid
EventListener.hpp

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

#ifndef EVENTLISTENER_HPP_INCLUDED
#define EVENTLISTENER_HPP_INCLUDED

#include "common.hpp"

namespace gui
{
    class EventListener
    {
    protected :

        bool m_enabled;

    public :

        EventListener()
        {
            m_enabled = true;
        }

        inline void enable(bool e) { m_enabled = e; }
        inline bool isEnabled() const { return m_enabled; }

        // these methods must return true if the event is performed

        // Mouse contains converted coordinates (view)
        virtual bool onEvent(const sf::Event & e, const Vector2i & mouse);

        virtual bool keyPressEvent(sf::Key::Code key, char character = 0)
        { return false; }

        virtual bool keyReleaseEvent(sf::Key::Code key, char character = 0)
        { return false; }

        virtual bool textEnteredEvent(unsigned int unicode)
        { return false; }

        virtual bool mouseLeftPressEvent(Vector2i pos)
        { return false; }

        virtual bool mouseLeftReleaseEvent(Vector2i pos)
        { return false; }

        virtual bool mouseRightPressEvent(Vector2i pos)
        { return false; }

        virtual bool mouseRightReleaseEvent(Vector2i pos)
        { return false; }

        virtual bool mouseMoveEvent(Vector2i previous, Vector2i current)
        { return false; }

        virtual bool mouseWheelUpEvent()
        { return false; }

        virtual bool mouseWheelDownEvent()
        { return false; }
    };

} // namespace gui


#endif // EVENTLISTENER_HPP_INCLUDED
