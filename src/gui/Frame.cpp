/*
Grid
Frame.cpp

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

#include "gui/Frame.hpp"
#include "gui/Theme.hpp"

namespace gui
{
    void Frame::onShow()
    {
        Theme::getTheme().playShowFrameSound();
    }

    void Frame::onHide()
    {
        Theme::getTheme().playHideFrameSound();
    }

    // Virtual
    void Frame::render(sf::RenderWindow & screen)
    {
        // Render frame
        Theme::getTheme().renderFrame(*this, screen);

        // Render children
        WidgetContainer::render(screen);
    }

} // namespace gui

