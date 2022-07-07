#include "DepthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish)
    : Pathfinding(board, xTiles, yTiles, start, finish) {}

void DepthFirstSearch::checkNeighbor(int x, int y){
    std::pair<int,int> tile {x, y};
    if(visited.find(tile) == visited.end()){
        visited.insert(tile);
        if(board[y][x] == 1) return;
        if(x == finish.first && y == finish.second) found = true;
        else actions.push_back(std::vector<int>{x, y, 5});
        backtrack[tile] = std::pair<int,int> {this->x, this->y};
        stack.push(tile);
    }
}

std::vector<std::vector<int>> DepthFirstSearch::runAlgorithm(){
    found = false;
    stack.push(start);
    visited.insert(start);
    while(!found){
        if(stack.empty()) return actions;
        x = stack.top().first;
        y = stack.top().second;
        stack.pop();
        
        if(x != start.first || y != start.second)
            actions.push_back(std::vector<int>{x, y, 4});

        if(y - 1 >= 0) checkNeighbor(x, y - 1);
        if(x + 1 < xTiles) checkNeighbor(x + 1, y);
        if(y + 1 < yTiles) checkNeighbor(x, y + 1);
        if(x - 1 >= 0) checkNeighbor(x - 1, y);
    }
    return actions;
}