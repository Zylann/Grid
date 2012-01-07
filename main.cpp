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
    grid::Game * g = new grid::Game();

    try
    {
        g->run();
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

