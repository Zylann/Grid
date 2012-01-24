/*
Grid
gui/Label.hpp

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

#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "common.hpp"
#include "gui/Widget.hpp"

namespace gui
{
    class Label : public Widget
    {
    protected :

        sf::Sprite m_image;
        sf::String m_renderText;
        std::string m_text;

    public :

        Label(int x, int y, int w, int h,
               WidgetContainer * parent = NULL)
        : Widget(x, y, w, h, parent)
        {}

        ~Label()
        {}

        const std::string & getText() const { return m_text; }
        const sf::String & getRenderText() const { return m_renderText; }
        Label & setText(const std::string & text);
        Label & setFont(const sf::Font & font);

        const sf::Image * getImage() { return m_image.GetImage(); }
        Label & setImage(const sf::Image & img);

        virtual void render(sf::RenderWindow & screen);
    };

} // namespace gui


#endif // LABEL_HPP_INCLUDED
