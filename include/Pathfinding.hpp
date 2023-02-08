#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Graph.hpp"
#include "SquareMap.hpp"
#include <vector>

enum class distance_function
{
    EUCLIDEAN,
    MANHATTAN
};

class Pathfinding{
public:
    Pathfinding(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction)
        : graph(graph), squareMap(squareMap), start(start), finish(finish), distanceFunction(distanceFunction) {}

    virtual ~Pathfinding() {}

    virtual bool runAlgorithm(int const& n) = 0;

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

    distance_function distanceFunction = distance_function::EUCLIDEAN;

    double calculateManhattanDistance(Node* start, Node* finish)
    {
        return (double)abs(start->x - finish->x) + (double)abs(start->y - finish->y);
    }

    double calculateEuclideanDistance(Node* start, Node* finish)
    {
        return sqrt((double)abs(start->x - finish->x) * (double)abs(start->x - finish->x) + (double)abs(start->y - finish->y) * (double)abs(start->y - finish->y));
    }
};

#endif // PATHFINDING_H