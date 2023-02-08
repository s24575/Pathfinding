#include "DFS.hpp"

DepthFirstSearch::DepthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction)
    : Pathfinding(graph, squareMap, start, finish, distanceFunction)
{
    stack.push(start);
    start->visited = true;
}

bool DepthFirstSearch::runAlgorithm(int const& n){
    for(int i = 0; i < n; i++){
        if(stack.empty()) return true;

        current = stack.top();
        stack.pop();

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
            stack.push(neighbor);
            if(neighbor != finish)
                squareMap->setSquareColor(neighbor->x, neighbor->y, squareMap->searchedColor);
        }
    }
    return false;
}

void DepthFirstSearch::runBacktrack(){
    if(!finish->previous) return;
    Node* backtrack = finish->previous;
    while(backtrack != start){
        squareMap->setSquareColor(backtrack->x, backtrack->y, squareMap->backtrackingColor);
        backtrack = backtrack->previous;
    }
}