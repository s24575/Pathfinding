#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include "Pathfinding.hpp"

class Dijkstra : public Pathfinding{
public:
    Dijkstra(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish);

    bool runAlgorithm(int const& n) override;

    struct gCostComparator{
      bool operator()(const Node* a, const Node* b) const{ return a->g_cost > b->g_cost; }
    };
    
private:
    std::priority_queue<Node*, std::vector<Node*>, gCostComparator> priority_queue;

    void runBacktrack();

    double calculateManhattanDistance(Node* start, Node* finish);
    double calculateEuclideanDistance(Node* start, Node* finish);
};

#endif // DIJKSTRA_H