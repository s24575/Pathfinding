#pragma once

#include <SFML/Graphics.hpp>
#include "MazeGenerator.h"
#include "Graph.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"

class Board{
private:
    sf::RenderWindow* window;
    int xTiles;
    int yTiles;
    int tileSize;

    int maze_width;
    int maze_height;
    int corridor_width;

    int startX;
    int startY;
    int finishX;
    int finishY;

    Graph graph;
    std::unique_ptr<Pathfinding> algorithm;
    std::vector<sf::RectangleShape> tileMap;

    sf::Color Gray = sf::Color{50, 50, 50};
    sf::Color Black = sf::Color::Black;
    sf::Color Green = sf::Color::Green;
    sf::Color Red = sf::Color::Red;
    sf::Color Yellow = sf::Color::Yellow;
    sf::Color White = sf::Color::White;
    sf::Color Blue = sf::Color::Blue;
    sf::Color Magenta = sf::Color::Magenta;

    void convertMazeToBoard(uint8_t* maze);
public:
    Board(sf::RenderWindow* window, int width, int height, int tileSize, int maze_width, int maze_height, int corridor_width);
    void createDepthFirstSearch();
    void createBreadthFirstSearch();
    void runAlgorithm(int n);
    void placeWall(sf::Vector2i pos);
    void removeWall(sf::Vector2i pos);
    sf::Color& getColor(int x, int y);
    void drawAllSquares();
    void updateSquare(int x, int y);
    void reset();
};