#include "Dijkstra.hpp"

Dijkstra::Dijkstra(Graph* graph, SquareMap* squareMap, Node* start, Node* finish)
    : Pathfinding(graph, squareMap, start, finish)
{
    priority_queue.push(start);
    start->g_cost = 0;
}

bool Dijkstra::runAlgorithm(int const& n){
    for(int i = 0; i < n; i++){
        if(priority_queue.empty()) return true;

        current = priority_queue.top();
        current->visited = true;
        priority_queue.pop();

        if(current == finish){
            runBacktrack();
            finished = true;
            return true;
        }

        if(current != start && current != finish)
            squareMap->setSquareColor(current->x, current->y, squareMap->visitedColor);

        for(Node* neighbor : current->neighbors){
            if (neighbor->visited || (neighbor->obstacle && neighbor != finish)) continue;
            double weight = calculateEuclideanDistance(current, neighbor);
            double g_cost = current->g_cost + weight;
            if(g_cost < neighbor->g_cost){
                neighbor->g_cost = g_cost;
                neighbor->previous = current;
                priority_queue.push(neighbor);
                if(neighbor != finish)
                    squareMap->setSquareColor(neighbor->x, neighbor->y, squareMap->searchedColor);
            }
        }
    }
    return false;
}

void Dijkstra::runBacktrack(){
    if (!finish->previous) return;
    Node* backtrack = finish->previous;
    while(backtrack != start){
        squareMap->setSquareColor(backtrack->x, backtrack->y, squareMap->backtrackingColor);
        backtrack = backtrack->previous;
    }
}