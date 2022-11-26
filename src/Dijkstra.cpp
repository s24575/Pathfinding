#include "Dijkstra.hpp"

Dijkstra::Dijkstra(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish)
    : Pathfinding(graph, TileMap, start, finish)
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
            (*TileMap)[current->y * graph->xTiles + current->x].setFillColor(sf::Color::White);

        for(Node* neighbor : current->neighbors){
            if (neighbor->visited || (neighbor->obstacle && neighbor != finish)) continue;
            double weight = calculateEuclideanDistance(current, neighbor);
            double g_cost = current->g_cost + weight;
            if(g_cost < neighbor->g_cost){
                neighbor->g_cost = g_cost;
                neighbor->previous = current;
                priority_queue.push(neighbor);
                if(neighbor != finish) (*TileMap)[neighbor->y * graph->xTiles + neighbor->x].setFillColor(sf::Color::Yellow);
            }
        }
    }
    return false;
}

void Dijkstra::runBacktrack(){
    Node* backtrack = finish->previous;
    while(backtrack != start){
        (*TileMap)[backtrack->y * graph->xTiles + backtrack->x].setFillColor(sf::Color::Blue);
        backtrack = backtrack->previous;
    }
}

double Dijkstra::calculateManhattanDistance(Node* start, Node* finish){
    return (double)abs(start->x - finish->x) + (double)abs(start->y - finish->y);
}

double Dijkstra::calculateEuclideanDistance(Node* start, Node* finish){
    return sqrt((double)abs(start->x - finish->x) * (double)abs(start->x - finish->x) + (double)abs(start->y - finish->y) * (double)abs(start->y - finish->y));
}