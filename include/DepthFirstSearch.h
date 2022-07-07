#pragma once

#include <stack>
#include "Pathfinding.h"

class DepthFirstSearch : public Pathfinding{
protected:
    std::stack<std::pair<int,int>> stack;
    
    void checkNeighbor(int x, int y);
public:
    DepthFirstSearch(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish);

    std::vector<std::vector<int>> runAlgorithm();
};