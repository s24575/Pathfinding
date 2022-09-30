#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "MazeGenerator.h"
#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "AStar.h"

enum class algorithm_type{
    DFS,
    BFS,
    DIJKSTRA,
    ASTAR
};

class Board{
private:
    sf::RenderWindow* window;
    int xTiles;
    int yTiles;
    int tileSize;

    int maze_width;
    int maze_height;
    int corridor_width;

    int placeWallState;

    Node* start;
    Node* finish;

    Graph graph;
    std::unique_ptr<Pathfinding> algorithm;
    algorithm_type current_algorithm_type;
    std::vector<sf::RectangleShape> tileMap;

    sf::Color const Gray {sf::Color{50, 50, 50}};
    sf::Color const Black {sf::Color::Black};
    sf::Color const Green {sf::Color::Green};
    sf::Color const Red {sf::Color::Red};
    sf::Color const Yellow {sf::Color::Yellow};
    sf::Color const White {sf::Color::White};
    sf::Color const Blue {sf::Color::Blue};
    sf::Color const Magenta {sf::Color::Magenta};

    void convertMazeToBoard(uint8_t* const maze);
public:
    Board(sf::RenderWindow* window, int& width, int& height, int& tileSize, int& maze_width, int& maze_height, int& corridor_width);

    void createAlgorithm(algorithm_type algorithm_type);
    void runAlgorithm(int n);

    void editWall(sf::Vector2i const& pos);
    void checkWall(sf::Vector2i const& pos);
    
    void drawAllSquares() const;
    void updateSquare(int const &x, int const &y);
    void reset();
    void removeAllWalls();
};

#endif // BOARD_H