#ifndef ASTAR_H
#define ASTAR_H

#include <queue>
#include "Pathfinding.h"

class AStar : public Pathfinding{
public:
    AStar(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish);

    bool runAlgorithm(int const& n) override;

    struct costComparator{
      bool operator()(const Node* a, const Node* b) const{ return a->g_cost + a->h_cost > b->g_cost + b->h_cost; }
    };

private:
    std::priority_queue<Node*, std::vector<Node*>, costComparator> priority_queue;

    void runBacktrack();

    double calculateManhattanDistance(Node* start, Node* finish);
    double calculateEuclideanDistance(Node* start, Node* finish);
};

#endif // ASTAR_H