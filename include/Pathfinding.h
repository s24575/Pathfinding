#pragma once

#include <utility>
#include <vector>
#include <set>
#include <map>

class Pathfinding{
protected:
    int** board;
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
public:
    Pathfinding(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish)
        : board(board), xTiles(xTiles), yTiles(yTiles), start(start), finish(finish) {}
    virtual ~Pathfinding() {}
    virtual std::vector<std::vector<int>> runAlgorithm() = 0;

    std::map<std::pair<int,int>,std::pair<int,int>> getMap(){ return backtrack; }
};