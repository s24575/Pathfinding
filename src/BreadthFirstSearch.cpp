#include "BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, int xTiles, int yTiles, std::pair<int,int> start, std::pair<int,int> finish)
    : Pathfinding(graph, TileMap, xTiles, yTiles, start, finish)
{
    found = false;
    queue.push(start);
    visited.insert(start);
}

void BreadthFirstSearch::checkNeighbor(int x, int y){
    std::pair<int,int> tile {x, y};
    if(visited.find(tile) == visited.end()){
        visited.insert(tile);
        if(graph->getNode(x, y).obstacle) return;
        if(tile == finish) found = true;
        else (*TileMap)[y * xTiles + x].setFillColor(sf::Color::Yellow);
        backtrack[tile] = {this->x, this->y};
        queue.push(tile);
    }
}

bool BreadthFirstSearch::runAlgorithm(int n){
    if(found) return runBacktrack(n);
    for(int i = 0; i < n; i++){
        if(found) break;
        if(queue.empty()) return true;
        x = queue.front().first;
        y = queue.front().second;
        queue.pop();
        
        if(x != start.first || y != start.second) (*TileMap)[y * xTiles + x].setFillColor(sf::Color::White);

        if(y - 1 >= 0) checkNeighbor(x, y - 1);
        if(x + 1 < xTiles) checkNeighbor(x + 1, y);
        if(y + 1 < yTiles) checkNeighbor(x, y + 1);
        if(x - 1 >= 0) checkNeighbor(x - 1, y);
    }
    return false;
}

bool BreadthFirstSearch::runBacktrack(int n){
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