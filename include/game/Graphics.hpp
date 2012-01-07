/*
Grid
Graphics.hpp

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

#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED

#include "common.hpp"
#include "gui/Widget.hpp"

#define GAME_TILES_SIZE 32

namespace grid
{
    enum ViewID
    {
        VIEW_INTERFACE = 0,
        VIEW_GAME,
        VIEW_DEFAULT
    };

    class Graphics
    {
    private :

        sf::RenderWindow & r_screen;
        sf::View m_gameView;
        sf::View m_interfaceView;
        int m_gameTilesSize;
        int m_currentView;

    public :

        Graphics(sf::RenderWindow & screen, int gameTilesSize);

        void draw(const sf::Drawable & d);
        void draw(gui::Widget & w);
        void drawGrid();

        void setView(int viewID);
        void setGameViewCenter(const Vector2f & pos);
        const sf::View & getCurrentView() const;

        void onScreenSizeChange();
    };

} // namespace grid


#endif // GRAPHICS_HPP_INCLUDED
