/*
Grid
Player.hpp

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

#ifndef PLAYERINFO_HPP_INCLUDED
#define PLAYERINFO_HPP_INCLUDED

/* Header-only */

#include "common.hpp"
#include "utility/serialization.hpp"

namespace grid
{
    struct PlayerInfo
    {
        std::string name;
        int score;
        int kills;
        int deaths;
        int lives;
        int damageTaken;
        int damageDealt;

        PlayerInfo(const std::string p_name = "Player")
        {
            name = p_name;
            score = 0;
            kills = 0;
            deaths = 0;
            lives = 3;
            damageTaken = 0;
            damageDealt = 0;
        }

        void print(std::ostream & os)
        {
            os << "Player information" << std::endl;
            os << "{" << std::endl;
            os << "name=" << name << std::endl;
            os << "score=" << score << std::endl;
            os << "kill=" << kills << std::endl;
            os << "deaths=" << deaths << std::endl;
            os << "lives=" << lives << std::endl;
            os << "damageTaken=" << damageTaken << std::endl;
            os << "damageDealt=" << damageDealt << std::endl;
            os << "}" << std::endl;
        }

        void serialize(std::ostream & os) const
        {
            util::serialize(os, name);
            util::serialize(os, score);
            util::serialize(os, kills);
            util::serialize(os, deaths);
            util::serialize(os, lives);
            util::serialize(os, damageTaken);
            util::serialize(os, damageDealt);
        }

        void unserialize(std::istream & is)
        {
            util::unserialize(is, name);
            util::unserialize(is, score);
            util::unserialize(is, kills);
            util::unserialize(is, deaths);
            util::unserialize(is, lives);
            util::unserialize(is, damageTaken);
            util::unserialize(is, damageDealt);
        }
    };

} // namespace grid


#endif // PLAYERINFO_HPP_INCLUDED
