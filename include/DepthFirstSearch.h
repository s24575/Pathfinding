#pragma once

#include <stack>
#include "Pathfinding.h"

class DepthFirstSearch : public Pathfinding{
protected:
    std::stack<std::pair<int,int>> stack;
    
    void checkNeighbor(int x, int y) override;
    bool runBacktrack(int n) override;
public:
    DepthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish);

    bool runAlgorithm(int n) override;
};