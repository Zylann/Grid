/*
Grid
PathFinder.hpp

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

// TODO add ingame console module (chat, commands...)
// TODO improve GUI
// TODO add world selector (game state WorldSelector)
// TODO add a Player class with informations like lives, points, last death position, stats etc...

// SUGG make a fast generic entity system, because the current one depends on inheriting C++ classes

#include <iostream>
#include <cstdio>
#include <cmath>

#include "game/Game.hpp"
#include "utility/Sampler.hpp"

using namespace std;
using namespace grid;

int main()
{
    std::cout << "Main begin" << std::endl;

    int exitCode = 0;

    // Game creation
    grid::Game * g = new grid::Game();

    try
    {
        g->run(); // Game running
    }
    catch(std::exception & e)
    {
        std::cout << "MAIN EXCEPTION" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Game will exit." << std::endl;
        std::cout << "Press a key to continue...";
        getchar();
        exitCode = -1;
    }

    // Game deletion
    delete g;

    std::cout << "Main end" << std::endl;

    return exitCode;
}

//void drawOrigin(sf::RenderWindow & screen)
//{
//    screen.Draw(sf::Shape::Line(0, 0, 1, 0, 0.05, sf::Color(255, 0, 0)));
//    screen.Draw(sf::Shape::Line(0, 1, 0, 0, 0.05, sf::Color(0, 255, 0)));
//
////    glBegin(GL_LINES);
////
////    glColor3ub(255, 0, 0);
////    glVertex3i(0, 0, 0);
////    glVertex3i(1, 0, 0);
////
////    glColor3ub(0, 255, 0);
////    glVertex3i(0, 0, 0);
////    glVertex3i(0, 1, 0);
////
////    glColor3ub(0, 0, 255);
////    glVertex3i(0, 0, 0);
////    glVertex3i(0, 0, 1);
////
////    glEnd();
//}

