#pragma once

#include "Board.h"

class Screen{
public:
    Screen(int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width);
    void run();

private:
    sf::RenderWindow window;
    Board board;
    sf::Event event;

    bool leftPressed = false;
    bool rightPressed = false;
};