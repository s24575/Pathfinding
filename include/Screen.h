#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Screen{
private:
    sf::RenderWindow window;
    int** board;

    int maze_xTiles;
    int maze_yTiles;
    int maze_width;

    int xTiles;
    int yTiles;
    int tileSize;

    int startX;
    int startY;
    int finishX;
    int finishY;

    bool isLeftPressed = false;
    bool isRightPressed = false;

    void printAllSquares();
    void drawAllSquares();
    void updateSquare(int x, int y);
    void placeWall(sf::Vector2i pos);
    void removeWall(sf::Vector2i pos);
    void convertMazeToScreen(uint8_t* maze);
    void displayDepthFirstSearch();
    void displayBreadthFirstSearch();
    void reset();
public:
    Screen();
    ~Screen();

    void run();
};