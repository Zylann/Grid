/*
Grid
Sound.hpp

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

#ifndef SOUND_HPP_INCLUDED
#define SOUND_HPP_INCLUDED

#include <list>

#include "common.hpp"

namespace grid
{
    class Sound
    {
    protected :

        std::list<sf::Sound*> m_sounds;
        sf::Listener m_listener;
        sf::Clock m_lastSoundPlayTime;

        Sound();

    public :

        ~Sound();

        static Sound & instance();
        static void kill();

        void playSound(
            const std::string & name,
            float pitch = 1, float volume = 100);

        void playSound(
            const std::string & name,
            float pitch, float volume, Vector2f pos,
            bool relativeToListener = false);

        void setListenerPosition(const Vector2f & pos);

        void update();
        void clear();
    };

} // namespace grid


#endif // SOUND_HPP_INCLUDED
