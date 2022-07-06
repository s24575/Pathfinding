#pragma once

#include <utility>
#include <stack>
#include <queue>
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
    std::stack<std::pair<int,int>> stack;
    std::queue<std::pair<int,int>> queue;
    std::set<std::pair<int,int>> visited;
    std::map<std::pair<int,int>,std::pair<int,int>> backtrack;
    
    void dfsCheck(int x, int y);
    void bfsCheck(int x, int y);
public:
    Pathfinding(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish);

    std::vector<std::vector<int>> DepthFirstSearch();
    std::vector<std::vector<int>> BreadthFirstSearch();

    std::map<std::pair<int,int>,std::pair<int,int>> getMap(){ return backtrack; }
};