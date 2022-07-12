#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Graph.h"
#include <utility>
#include <vector>
#include <set>
#include <map>

class Pathfinding{
protected:
    Graph* graph;
    std::vector<sf::RectangleShape>* TileMap;
    
    int xTiles;
    int yTiles;

    int x;
    int y;

    std::pair<int,int> current;
    std::pair<int,int> start;
    std::pair<int,int> finish;

    bool found;

    std::vector<std::vector<int>> actions;
    std::set<std::pair<int,int>> visited;
    std::map<std::pair<int,int>,std::pair<int,int>> backtrack;
    
    virtual void checkNeighbor(int x, int y) = 0;
    virtual bool runBacktrack(int n) = 0;
public:
    Pathfinding(Graph* graph, std::vector<sf::RectangleShape>* TileMap, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish)
        : graph(graph), TileMap(TileMap), xTiles(xTiles), yTiles(yTiles), start(start), finish(finish) {}
    virtual ~Pathfinding() {}

    virtual bool runAlgorithm(int n) = 0;
};