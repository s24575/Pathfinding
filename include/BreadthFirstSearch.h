#pragma once

#include <queue>
#include "Pathfinding.h"

class BreadthFirstSearch : public Pathfinding{
protected:
    std::queue<std::pair<int,int>> queue;
    std::pair<int,int> cords;
    
    void checkNeighbor(int x, int y) override;
    bool runBacktrack(int n) override;
public:
    BreadthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish);

    bool runAlgorithm(int n) override;
};