#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include "Pathfinding.hpp"

class Dijkstra : public Pathfinding{
public:
    Dijkstra(Graph* graph, SquareMap* squareMap, Node* start, Node* finish, distance_function distanceFunction);

    bool runAlgorithm(int const& n) override;

    struct gCostComparator{
      bool operator()(const Node* a, const Node* b) const{ return a->g_cost > b->g_cost; }
    };
    
private:
    std::priority_queue<Node*, std::vector<Node*>, gCostComparator> priority_queue;

    void runBacktrack();
};

#endif // DIJKSTRA_H