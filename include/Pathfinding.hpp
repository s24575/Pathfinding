#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Graph.hpp"
#include "SquareMap.hpp"
#include <vector>
#include <cmath>

enum class distance_function
{
    EUCLIDEAN,
    MANHATTAN
};

class Pathfinding{
public:
    Pathfinding(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction)
        : graph(graph), squareMap(squareMap), start(start), finish(finish), distanceFunction(distanceFunction) {}

    virtual bool runAlgorithm(int n) = 0;

    bool hasFinished() const { return finished; }
    distance_function getDistanceFunction() const { return distanceFunction; }
    void setDistanceFunction(distance_function distanceFunction) { this->distanceFunction = distanceFunction; }

protected:
    Graph* graph;
    SquareMap* squareMap;

    Node* current = nullptr;
    Node* start;
    Node* finish;

    bool finished = false;

    distance_function distanceFunction;

    void runBacktrack()
    {
        if (!finish->previous) return;

        Node* backtrack = finish->previous;
        while (backtrack != start)
        {
            squareMap->setSquareColor(backtrack->x, backtrack->y, squareMap->backtrackingColor);
            backtrack = backtrack->previous;
        }
    }

    float calculateDistance(Node* start, Node* finish)
    {
        float distance = 0.0f;

        switch (distanceFunction)
        {
            case distance_function::EUCLIDEAN:
                distance = calculateEuclideanDistance(start, finish);
                break;
            case distance_function::MANHATTAN:
                distance = calculateManhattanDistance(start, finish);
                break;
        }

        return distance;
    }

    float calculateManhattanDistance(Node* start, Node* finish)
    {
        int dx = abs(start->x - finish->x);
        int dy = abs(start->y - finish->y);
        return (float)(dx + dy);
    }

    float calculateEuclideanDistance(Node* start, Node* finish)
    {
        int dx = abs(start->x - finish->x);
        int dy = abs(start->y - finish->y);
        return (float)sqrt(dx * dx + dy * dy);
    }
};

#endif // PATHFINDING_H