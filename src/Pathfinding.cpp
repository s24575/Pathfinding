#include "Pathfinding.h"

Pathfinding::Pathfinding(int** board, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish) :
    board(board), xTiles(xTiles), yTiles(yTiles), current(start), start(start), finish(finish) {}

void Pathfinding::dfsCheck(int x, int y){
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

std::vector<std::vector<int>> Pathfinding::DepthFirstSearch(){
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

        if(y - 1 >= 0) dfsCheck(x, y - 1);
        if(x + 1 < xTiles) dfsCheck(x + 1, y);
        if(y + 1 < yTiles) dfsCheck(x, y + 1);
        if(x - 1 >= 0) dfsCheck(x - 1, y);
    }
    return actions;
}

void Pathfinding::bfsCheck(int x, int y){
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

std::vector<std::vector<int>> Pathfinding::BreadthFirstSearch(){
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

        if(y - 1 >= 0) bfsCheck(x, y - 1);
        if(x + 1 < xTiles) bfsCheck(x + 1, y);
        if(y + 1 < yTiles) bfsCheck(x, y + 1);
        if(x - 1 >= 0) bfsCheck(x - 1, y);
    }
    return actions;
}