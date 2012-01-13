/*
Grid
Graphics.cpp

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

#include "game/Graphics.hpp"

namespace grid
{
    Graphics::Graphics(sf::RenderWindow & screen, int gameTilesSize)
    : r_screen(screen)
    {
        m_gameTilesSize = gameTilesSize;

        m_interfaceView = sf::View(screen.GetDefaultView().GetRect());

        m_gameView.SetCenter(0, 0);
        m_gameView.SetHalfSize(screen.GetWidth() / 2, screen.GetHeight() / 2);
        m_gameView.Zoom(gameTilesSize);
    }

    void Graphics::draw(const sf::Drawable & d)
    {
//        if(m_currentView == VIEW_GAME)
//        {
//            if(m_gameView.GetRect().Contains(d.GetPosition()))
//                r_screen.Draw(d);
//        }
//        else
            r_screen.Draw(d);
    }

    void Graphics::draw(gui::Widget & w)
    {
        w.render(r_screen);
    }

    void Graphics::drawGrid()
    {
        // Draw grid
        const sf::FloatRect & rect = m_gameView.GetRect();

        // Display grid if resolution is low enough
        if(fabs(rect.Top - rect.Bottom) < 200 && fabs(rect.Left - rect.Right) < 200)
        {
            sf::Color clr(255, 255, 255, 64);
            float x;

            for(x = floor(rect.Left); x < rect.Right; x++)
                draw(sf::Shape::Line(x, rect.Top, x, rect.Bottom, 0.05, clr));

            for(x = floor(rect.Top); x < rect.Bottom; x++)
                draw(sf::Shape::Line(rect.Left, x, rect.Right, x, 0.05, clr));
        }

        // Draw origin
        draw(sf::Shape::Line(0, 0, 1, 0, 0.05, sf::Color(255, 0, 0)));
        draw(sf::Shape::Line(0, 1, 0, 0, 0.05, sf::Color(0, 255, 0)));
    }

    void Graphics::setView(int viewID)
    {
        m_currentView = viewID;

        if(viewID == VIEW_GAME)
            r_screen.SetView(m_gameView);
        else if(viewID == VIEW_INTERFACE)
            r_screen.SetView(m_interfaceView);
        else
            r_screen.SetView(r_screen.GetDefaultView());
    }

    void Graphics::setGameViewCenter(const Vector2f & pos)
    {
        m_gameView.SetCenter(pos);
    }

    void Graphics::onScreenSizeChange()
    {
        Vector2f screenSize(r_screen.GetWidth(), r_screen.GetHeight());
        float k = 1;
        if(r_screen.GetWidth() > 1200 || r_screen.GetHeight() > 1000)
            k = 2;

        // Updating game view
        m_gameView.SetHalfSize(screenSize / 2.f);
        m_gameView.Zoom(k * m_gameTilesSize);

        // Updating interface view
        m_interfaceView.SetFromRect(sf::FloatRect(0, 0, screenSize.x / k, screenSize.y / k));
    }

    const sf::View & Graphics::getCurrentView() const
    {
        if(m_currentView == VIEW_GAME)
            return m_gameView;
        else if(m_currentView == VIEW_INTERFACE)
            return m_interfaceView;
        else
            return r_screen.GetDefaultView();
    }

    const sf::View & Graphics::getView(int viewID) const
    {
        if(viewID == VIEW_GAME)
            return m_gameView;
        else
            return m_interfaceView;
    }

} // namespace grid

