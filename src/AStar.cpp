#include "AStar.hpp"

AStar::AStar(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction)
    : Pathfinding(graph, squareMap, start, finish, distanceFunction)
{
    priority_queue.push(start);
    start->g_cost = 0;
}

bool AStar::runAlgorithm(const int& n)
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

            double g_cost = current->g_cost + calculateDistance(current, neighbor);

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

void AStar::runBacktrack()
{
    if (!finish->previous) return;
    Node* backtrack = finish->previous;
    while (backtrack != start)
    {
        squareMap->setSquareColor(backtrack->x, backtrack->y, squareMap->backtrackingColor);
        backtrack = backtrack->previous;
    }
}