/*
Grid
Loading.cpp

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

#include <lua.hpp>
#include <lunar.h>

#include "game/states/Loading.hpp"
#include "game/Game.hpp"
#include "game/GameUpdate.hpp"

using namespace util;

namespace grid
{
    Loading::Loading(int stateID, Game * game)
    : GameState(stateID, game),
        m_progressBar(Vector2f(0,0), Vector2f(400,16))
    {
        m_initialLoadItemsCount = 0;
    }

    void Loading::update(GameUpdate & up)
    {
        // Continue until all loadings are done
        if(m_loadingList.finished())
        {
            up.game->setCursorImage(resources::getImage("cursor"));
            up.game->enterState(ST_MAIN_MENU);
            return;
        }

        const LoadingListItem & item = m_loadingList.getNext();
        std::cout << "Loading " << item.resourcePath << std::endl;
        m_loadingList.loadNext();
    }

    void Loading::render(Graphics & gfx)
    {
        // Center progress bar
        Vector2f pos = gfx.getCurrentView().GetCenter();
        pos -= m_progressBar.getSize() * 0.5f;
        m_progressBar.setPosition(pos);

        // Update progress bar filling
        float loadRatio =
            1 - (float)m_loadingList.getTotalRemaining() / (float)m_initialLoadItemsCount;
        m_progressBar.setFillRatio(loadRatio);

        // Render progress bar
        m_progressBar.render(gfx);
    }

    void Loading::enter()
    {
        // Read resource list file
        if(!m_loadingList.loadFromLuaScript("registerResources.lua"))
        {
            std::stringstream ss;
            ss << "Loading::enter: "
                << "An error occured while reading the resource file." << std::endl;
            ss << "LoadingList content :" << std::endl;
            m_loadingList.print(ss);
            throw GameException(ss.str(), Exception::EX_ERROR);
        }
        m_initialLoadItemsCount = m_loadingList.getTotalRemaining();
    }

    void Loading::leave()
    {

    }

} // namespace grid

