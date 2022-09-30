#ifndef BFS_H
#define BFS_H

#include <queue>
#include "Pathfinding.h"

class BreadthFirstSearch : public Pathfinding{
public:
    BreadthFirstSearch(Graph* graph, std::vector<sf::RectangleShape>* TileMap, Node* start, Node* finish);

    bool runAlgorithm(int const& n) override;

private:
    std::queue<Node*> queue;

    void runBacktrack();
};

#endif // BFS_H