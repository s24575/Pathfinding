#include "BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish)
    : Pathfinding(board, xTiles, yTiles, start, finish) {}

void BreadthFirstSearch::checkNeighbor(int x, int y){
    std::pair<int,int> tile {x, y};
    if(visited.find(tile) == visited.end()){
        visited.insert(tile);
        if(board[y][x] == 1) return;
        if(x == finish.first && y == finish.second) found = true;
        else actions.push_back(std::vector<int>{x, y, 5});
        backtrack[tile] = std::pair<int,int> {this->x, this->y};
        queue.push(tile);
    }
}

std::vector<std::vector<int>> BreadthFirstSearch::runAlgorithm(){
    found = false;
    queue.push(start);
    visited.insert(start);
    while(!found){
        if(queue.empty()) return actions;
        x = queue.front().first;
        y = queue.front().second;
        queue.pop();
        
        if(x != start.first || y != start.second)
            actions.push_back(std::vector<int>{x, y, 4});

        if(y - 1 >= 0) checkNeighbor(x, y - 1);
        if(x + 1 < xTiles) checkNeighbor(x + 1, y);
        if(y + 1 < yTiles) checkNeighbor(x, y + 1);
        if(x - 1 >= 0) checkNeighbor(x - 1, y);
    }
    return actions;
}