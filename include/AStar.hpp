#ifndef ASTAR_H
#define ASTAR_H

#include <queue>
#include "Pathfinding.hpp"

class AStar : public Pathfinding
{
public:
    AStar(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction);

    bool runAlgorithm(int n) override;

private:
    struct CostComparator
    {
        bool operator()(const Node* a, const Node* b) const { return a->g_cost + a->h_cost > b->g_cost + b->h_cost; }
    };

    std::priority_queue<Node*, std::vector<Node*>, CostComparator> priority_queue;
};

#endif // ASTAR_H