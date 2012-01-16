/*
Grid
TextBar.hpp

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

#ifndef TEXTBAR_HPP_INCLUDED
#define TEXTBAR_HPP_INCLUDED

#include <string>

#include "gui/Widget.hpp"
#include "gui/Action.hpp"

namespace gui
{
    /*
        A bar for entering one-line texts
    */

    class TextBar : public Widget
    {
    protected :

        std::string m_text;
        sf::String m_renderText;
        GenericAction * m_enterAction; // callback while pressing enter key

    public :

        TextBar(int x, int y, int w, int h,
                const sf::Font & font,
                GenericAction * enterAction = NULL,
                Widget * parent = NULL)
        : Widget(x, y, w, h, parent)
        {
            m_renderText.SetFont(font);
            setText("");
            m_enterAction = enterAction;
        }

        virtual ~TextBar()
        {
            if(m_enterAction != NULL)
                delete m_enterAction;
        }

        const std::string & getText() const { return m_text; }
        const sf::String & getRenderText() const { return m_renderText; }
        void setText(const std::string & text);
        int getCaretPosition() const;

        inline void clearText() { setText(""); }
        void executeEnterAction();

        virtual bool mouseMoveEvent(Vector2i previous, Vector2i current);
        virtual bool mouseLeftPressEvent(Vector2i pos);
        virtual bool keyPressEvent(sf::Key::Code key, char character = 0);
        virtual bool textEnteredEvent(unsigned int unicode);

        virtual void render(sf::RenderWindow & screen);
    };

} // namespace gui


#endif // TEXTBAR_HPP_INCLUDED
