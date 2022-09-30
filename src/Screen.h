#ifndef SCREEN_H
#define SCREEN_H

#include "Board.h"

class Screen{
public:
    Screen(int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width);
    void run();

private:
    sf::RenderWindow window;
    Board board;

    const int tiles_total;
    bool left_pressed = false;
};

#endif // SCREEN_H