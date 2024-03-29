#include "AStar.hpp"

AStar::AStar(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction)
    : Pathfinding(graph, squareMap, start, finish, distanceFunction)
{
    priority_queue.push(start);
    start->g_cost = 0;
}

bool AStar::runAlgorithm(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (priority_queue.empty()) return true;

        current = priority_queue.top();
        current->visited = true;
        priority_queue.pop();

        if (current == finish)
        {
            runBacktrack();
            finished = true;
            return true;
        }

        if (current != start && current != finish)
            squareMap->setSquareColor(current->x, current->y, squareMap->visitedColor);

        for (Node* neighbor : current->neighbors)
        {
            if (neighbor->visited || (neighbor->obstacle && neighbor != finish)) continue;

            float g_cost = current->g_cost + calculateDistance(current, neighbor) * graph->getWeight() * 0.01f;

            if (g_cost < neighbor->g_cost)
            {
                neighbor->g_cost = g_cost;
                neighbor->h_cost = calculateDistance(neighbor, finish);
                neighbor->previous = current;

                priority_queue.push(neighbor);

                if (neighbor != finish)
                    squareMap->setSquareColor(neighbor->x, neighbor->y, squareMap->searchedColor);
            }
        }
    }

    return false;
}