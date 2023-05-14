#include "BFS.hpp"

BreadthFirstSearch::BreadthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction)
    : Pathfinding(graph, squareMap, start, finish, distanceFunction)
{
    queue.push(start);
    start->visited = true;
}

bool BreadthFirstSearch::runAlgorithm(int n){
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