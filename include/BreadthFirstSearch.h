#pragma once

#include <queue>
#include "Pathfinding.h"

class BreadthFirstSearch : public Pathfinding{
protected:
    std::queue<std::pair<int,int>> queue;
    
    void checkNeighbor(int x, int y);
public:
    BreadthFirstSearch(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish);

    std::vector<std::vector<int>> runAlgorithm();
};