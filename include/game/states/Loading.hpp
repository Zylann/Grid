/*
Grid
Loading.hpp

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

#ifndef LOADING_HPP_INCLUDED
#define LOADING_HPP_INCLUDED

#include "utility/LoadingList.hpp"

#include "game/base/GameState.hpp"
#include "game/ProgressBar.hpp"

namespace grid
{
    /*
        This is the game loading state :
        All resources are loaded here.
        Note : We shouldn't request resources before this state passed.
    */

    class Loading : public GameState
    {
    private :

        util::LoadingList m_loadingList;
        ProgressBar m_progressBar;
        int m_initialLoadItemsCount;

    public :

        Loading(int stateID, Game * game);
        virtual ~Loading();

        virtual void update(GameUpdate & up);
        virtual void render(Graphics & gfx);

        virtual void onEnter();
        virtual void onLeave();
    };

} // namespace grid


#endif // LOADING_HPP_INCLUDED
