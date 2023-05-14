#ifndef DFS_H
#define DFS_H

#include <stack>
#include "Pathfinding.hpp"

class DepthFirstSearch : public Pathfinding{
public:
    DepthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction);

    bool runAlgorithm(int n) override;

private:
    std::stack<Node*> stack;
};

#endif // DFS_H