#include "BFS.hpp"

BreadthFirstSearch::BreadthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish)
    : Pathfinding(graph, squareMap, start, finish)
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
            squareMap->setSquareColor(current->x, current->y, squareMap->visitedColor);

        for(Node* neighbor : current->neighbors){
            if (neighbor->visited || neighbor->obstacle) continue;
            neighbor->visited = true;
            neighbor->previous = current;
            queue.push(neighbor);
            if(neighbor != finish)
                squareMap->setSquareColor(neighbor->x, neighbor->y, squareMap->searchedColor);
        }
    }
    return false;
}

void BreadthFirstSearch::runBacktrack(){
    if(!finish->previous) return;
    Node* backtrack = finish->previous;
    while(backtrack != start){
        squareMap->setSquareColor(backtrack->x, backtrack->y, squareMap->backtrackingColor);
        backtrack = backtrack->previous;
    }
}