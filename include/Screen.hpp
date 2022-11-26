#ifndef SCREEN_H
#define SCREEN_H

#include "Board.hpp"
#include "Constants.hpp"

class Screen{
public:
    Screen();
    void run();

private:
    sf::RenderWindow window;
    Board board;
};

#endif // SCREEN_H