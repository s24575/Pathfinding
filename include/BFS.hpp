#ifndef BFS_H
#define BFS_H

#include <queue>
#include "Pathfinding.hpp"

class BreadthFirstSearch : public Pathfinding{
public:
    BreadthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction);

    bool runAlgorithm(int n) override;

private:
    std::queue<Node*> queue;
};

#endif // BFS_H