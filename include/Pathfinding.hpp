#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Graph.hpp"
#include "SquareMap.hpp"
#include <vector>

class Pathfinding{
public:
    Pathfinding(Graph* graph, SquareMap* squareMap, Node* start, Node* finish)
        : graph(graph), squareMap(squareMap), start(start), finish(finish) {}

    virtual ~Pathfinding() {}

    virtual bool runAlgorithm(int const& n) = 0;

    bool hasFinished() const { return finished; }
protected:
    Graph* graph;
    SquareMap* squareMap;

    Node* current = nullptr;
    Node* start;
    Node* finish;

    bool finished = false;

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