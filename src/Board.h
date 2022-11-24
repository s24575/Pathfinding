#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "MazeGenerator.h"
#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "AStar.h"

#include "Constants.hpp"

enum class algorithm_type{
    DFS,
    BFS,
    DIJKSTRA,
    ASTAR
};

class Board{
private:
    sf::RenderWindow* _window;
    int xTiles = X_TILES;
    int yTiles = Y_TILES;
    int tileSize = TILE_SIZE;

    int maze_width = MAZE_WIDTH;
    int maze_height = MAZE_HEIGHT;
    int corridor_width = MAZE_CORRIDOR_WIDTH;

    Node* start;
    Node* finish;

    enum class WallType {
        EMPTY,
        WALL,
        START,
        FINISH
    };

    WallType placeWallType;

    // cached settings
    int graphWeight = 1;
    int distanceCalculation = 0;

    Graph graph;
    std::unique_ptr<Pathfinding> algorithm;
    algorithm_type current_algorithm_type;
    std::vector<sf::RectangleShape> tileMap;

    const sf::Color Gray {sf::Color{50, 50, 50}};
    const sf::Color Black {sf::Color::Black};
    const sf::Color Green {sf::Color::Green};
    const sf::Color Red {sf::Color::Red};
    const sf::Color Yellow {sf::Color::Yellow};
    const sf::Color White {sf::Color::White};
    const sf::Color Blue {sf::Color::Blue};
    const sf::Color Magenta {sf::Color::Magenta};

    void convertMazeToBoard(uint8_t* const maze);
public:
    Board(sf::RenderWindow* _window);
    //Board(sf::RenderWindow* _window, int& width, int& height, int& tileSize, int& maze_width, int& maze_height, int& corridor_width);
    void updateSettings(bool areDiagonalsEnabled, int graphWeight, int distanceCalculation);

    void createAlgorithm(algorithm_type type);
    void runAlgorithm(int n);

    void editWall(sf::Vector2i const& pos);
    void checkWall(sf::Vector2i const& pos);
    void drawAllSquares() const;
    void updateSquare(int const &x, int const &y);
    void reset();
    void removeAllWalls();
    void generateMaze();

    int getTotalTiles() { return xTiles * yTiles; }

    bool hasMoved = false;
};

#endif // BOARD_H