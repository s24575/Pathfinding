#include "DepthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish)
    : Pathfinding(graph, TileMap, xTiles, yTiles, start, finish)
{
    found = false;
    stack.push(start);
    visited.insert(start);
}

void DepthFirstSearch::checkNeighbor(int x, int y){
    std::pair<int,int> tile {x, y};
    if(visited.find(tile) == visited.end()){
        visited.insert(tile);
        if(graph->getNode(x, y).obstacle) return;
        if(tile == finish) found = true;
        else (*TileMap)[y * xTiles + x].setFillColor(sf::Color::Yellow);
        backtrack[tile] = {this->x, this->y};
        stack.push(tile);
    }
}

bool DepthFirstSearch::runAlgorithm(int n){
    if(found) return runBacktrack(n);
    for(int i = 0; i < n; i++){
        if(found) break;
        if(stack.empty()) return true;
        x = stack.top().first;
        y = stack.top().second;
        stack.pop();

        if(x != start.first || y != start.second) (*TileMap)[y * xTiles + x].setFillColor(sf::Color::White);

        if(y - 1 >= 0) checkNeighbor(x, y - 1);
        if(x + 1 < xTiles) checkNeighbor(x + 1, y);
        if(y + 1 < yTiles) checkNeighbor(x, y + 1);
        if(x - 1 >= 0) checkNeighbor(x - 1, y);
    }
    return false;
}

bool DepthFirstSearch::runBacktrack(int n){
    std::pair<int,int> cords = {x, y};
    for(int i = 0; i < n; i++){
        if(cords == start) return true;
        (*TileMap)[y * xTiles + x].setFillColor(sf::Color::Blue);
        cords = backtrack.at(cords);
        x = cords.first;
        y = cords.second;
    }
    return false;
}