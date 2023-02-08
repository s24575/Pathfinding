#ifndef DFS_H
#define DFS_H

#include <stack>
#include "Pathfinding.hpp"

class DepthFirstSearch : public Pathfinding{
public:
    DepthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction);

    bool runAlgorithm(int const& n) override;

private:
    std::stack<Node*> stack;
    
    void runBacktrack();
};

#endif // DFS_H