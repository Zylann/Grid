/*
Grid
Sound.cpp

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

#include "game/Sound.hpp"

#include "utility/ResourceManager.hpp"
#include "utility/geometry.hpp"

#define MAX_SOUNDS 24

using namespace util;

namespace grid
{
    Sound * g_sound = NULL;

    /*
        Static methods
    */

    Sound & Sound::instance()
    {
        if(g_sound == NULL)
            g_sound = new Sound();
        return *g_sound;
    }

    void Sound::kill()
    {
        if(g_sound != NULL)
        {
            delete g_sound;
            g_sound = NULL;
        }
    }

    /*
        Methods
    */

    Sound::Sound()
    {
    }

    Sound::~Sound()
    {
        clear();
    }

    void Sound::clear()
    {
        std::list<sf::Sound*>::iterator it;
        for(it = m_sounds.begin(); it != m_sounds.end(); it++)
        {
            sf::Sound * s = *it;
            if(s != NULL)
                delete s;
        }
        m_sounds.clear();
    }

    void Sound::playSound(const std::string & name,float pitch, float volume)
    {
        playSound(name, pitch, volume, Vector2f(0,0), true);
    }

    void Sound::playSound(
        const std::string & name, float pitch, float volume,
        Vector2f pos, bool relativeToListener)
    {
        if(m_sounds.size() >= MAX_SOUNDS)
            return;
        const sf::Vector3f listenerPos = m_listener.GetPosition();
        if(!relativeToListener && distance2D(pos, Vector2f(listenerPos.x, listenerPos.y)) > 25)
            return;
        if(m_lastSoundPlayTime.GetElapsedTime() < 0.01)
            return;

        m_lastSoundPlayTime.Reset();

        const sf::SoundBuffer & buf = resources::getSoundBuffer(name);
        sf::Sound * s = new sf::Sound(buf, false, pitch, volume, sf::Vector3f(pos.x, pos.y, 0));
        s->SetRelativeToListener(relativeToListener);
        s->SetAttenuation(0.5);
        s->Play();
        m_sounds.push_back(s);
    }

    void Sound::setListenerPosition(const Vector2f & pos)
    {
        m_listener.SetPosition(sf::Vector3f(pos.x, pos.y, 2));
    }

    void Sound::update()
    {
        std::list<sf::Sound*>::iterator it;
        for(it = m_sounds.begin(); it != m_sounds.end(); it++)
        {
            sf::Sound * s = *it;
            if(s->GetStatus() == sf::Sound::Stopped)
            {
                delete s;
                (*it) = NULL;
            }
        }
        m_sounds.remove(NULL);
    }

} // namespace grid

