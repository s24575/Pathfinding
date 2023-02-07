#ifndef BFS_H
#define BFS_H

#include <queue>
#include "Pathfinding.hpp"

class BreadthFirstSearch : public Pathfinding{
public:
    BreadthFirstSearch(Graph* graph, SquareMap* squareMap, Node* start, Node* finish);

    bool runAlgorithm(int const& n) override;

private:
    std::queue<Node*> queue;

    void runBacktrack();
};

#endif // BFS_H