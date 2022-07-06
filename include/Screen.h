#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Board.h"

class Screen{
private:
    sf::RenderWindow window;
    Board board;
    int xTiles; // duplicate in board
    int yTiles; // duplicate in board
    int tileSize;

    bool isLeftPressed = false;
    bool isRightPressed = false;

    void drawAllSquares();
    void updateSquare(int x, int y);
    void placeWall(sf::Vector2i pos);
    void removeWall(sf::Vector2i pos);
    void displayDepthFirstSearch();
    void displayBreadthFirstSearch();
    void reset();
public:
    Screen();
    ~Screen();

    void run();

    static int tile_counter;
};