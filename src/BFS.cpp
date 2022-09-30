#include "BFS.h"

BreadthFirstSearch::BreadthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish)
    : Pathfinding(graph, TileMap, start, finish)
{
    queue.push(start);
    start->visited = true;
}

bool BreadthFirstSearch::runAlgorithm(int const& n){
    for(int i = 0; i < n; i++){
        if(queue.empty()) return true;

        current = queue.front();
        queue.pop();

        if(current == finish){
            runBacktrack();
            finished = true;
            return true;
        }

        if(current != start && current != finish)
            (*TileMap)[current->y * graph->xTiles + current->x].setFillColor(sf::Color::White);

        for(Node* neighbor : current->neighbors){
            if (neighbor->visited || neighbor->obstacle) continue;
            neighbor->visited = true;
            neighbor->previous = current;
            queue.push(neighbor);
            if(neighbor != finish) (*TileMap)[neighbor->y * graph->xTiles + neighbor->x].setFillColor(sf::Color::Yellow);
        }
    }
    return false;
}

void BreadthFirstSearch::runBacktrack(){
    if(!finish->previous) return;
    Node* backtrack = finish->previous;
    while(backtrack != start){
        (*TileMap)[backtrack->y * graph->xTiles + backtrack->x].setFillColor(sf::Color::Blue);
        backtrack = backtrack->previous;
    }
}